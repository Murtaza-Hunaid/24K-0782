<?php
session_start();
include("../db.php");

if ($_SESSION['role'] != 'doctor') {
    header("Location: login.php");
    exit();
}

$user_id = $_SESSION['user_id'];

/* =========================
   GET DOCTOR ID
========================= */

$stmt = $conn->prepare("
    SELECT doctor_id 
    FROM doctors 
    WHERE user_id = ?
");

$stmt->bind_param("i", $user_id);
$stmt->execute();

$result = $stmt->get_result();
$data = $result->fetch_assoc();

$doctor_id = $data['doctor_id'];

$message = "";

/* =========================
   ADD SCHEDULE
========================= */

if (isset($_POST['save_schedule'])) {

    $day = $_POST['day'];
    $start = $_POST['start_time'];
    $end = $_POST['end_time'];

    $break_start = $_POST['break_start'];
    $break_end = $_POST['break_end'];

    $duration = $_POST['slot_duration'];

    // CHECK EXISTING DAY
    $check = $conn->prepare("
        SELECT * FROM doctor_schedule
        WHERE doctor_id = ? AND day_of_week = ?
    ");

    $check->bind_param("is", $doctor_id, $day);
    $check->execute();

    if ($check->get_result()->num_rows > 0) {

        $message = "
        <div class='alert alert-danger'>
            Schedule already exists for $day
        </div>";

    } else {

        $insert = $conn->prepare("
            INSERT INTO doctor_schedule
            (doctor_id, day_of_week, start_time, end_time, break_start, break_end, slot_duration)
            VALUES (?, ?, ?, ?, ?, ?, ?)
        ");

        $insert->bind_param(
            "isssssi",
            $doctor_id,
            $day,
            $start,
            $end,
            $break_start,
            $break_end,
            $duration
        );

        if ($insert->execute()) {

            $message = "
            <div class='alert alert-success'>
                Schedule added successfully!
            </div>";

        } else {

            $message = "
            <div class='alert alert-danger'>
                Error adding schedule
            </div>";
        }
    }
}

/* =========================
   DELETE SCHEDULE
========================= */

if (isset($_GET['delete'])) {

    $schedule_id = $_GET['delete'];

    $delete = $conn->prepare("
        DELETE FROM doctor_schedule
        WHERE schedule_id = ? AND doctor_id = ?
    ");

    $delete->bind_param("ii", $schedule_id, $doctor_id);
    $delete->execute();

    header("Location: doctor_schedule.php");
    exit();
}

/* =========================
   GET SCHEDULES
========================= */

$get = $conn->prepare("
    SELECT * FROM doctor_schedule
    WHERE doctor_id = ?
    ORDER BY FIELD(
        day_of_week,
        'Monday',
        'Tuesday',
        'Wednesday',
        'Thursday',
        'Friday',
        'Saturday',
        'Sunday'
    )
");

$get->bind_param("i", $doctor_id);
$get->execute();

$schedules = $get->get_result();

include("../layout.php");
?>

<div class="container-fluid">

<div class="card shadow p-4">

    <h2 class="mb-4">
        <i class="fas fa-calendar-alt text-primary"></i>
        Manage Schedule
    </h2>

    <?php echo $message; ?>

    <!-- =========================
         ADD FORM
    ========================= -->

    <form method="POST">

        <div class="row">

            <div class="col-md-4 mb-3">
                <label>Day</label>

                <select name="day" class="form-control" required>
                    <option value="">Select Day</option>

                    <option>Monday</option>
                    <option>Tuesday</option>
                    <option>Wednesday</option>
                    <option>Thursday</option>
                    <option>Friday</option>
                    <option>Saturday</option>
                    <option>Sunday</option>

                </select>
            </div>

            <div class="col-md-4 mb-3">
                <label>Start Time</label>
                <input type="time" name="start_time" class="form-control" required>
            </div>

            <div class="col-md-4 mb-3">
                <label>End Time</label>
                <input type="time" name="end_time" class="form-control" required>
            </div>

            <div class="col-md-4 mb-3">
                <label>Break Start</label>
                <input type="time" name="break_start" class="form-control">
            </div>

            <div class="col-md-4 mb-3">
                <label>Break End</label>
                <input type="time" name="break_end" class="form-control">
            </div>

            <div class="col-md-4 mb-3">
                <label>Slot Duration (minutes)</label>

                <select name="slot_duration" class="form-control">
                    <option value="15">15 Minutes</option>
                    <option value="30" selected>30 Minutes</option>
                    <option value="60">1 Hour</option>
                </select>
            </div>

        </div>

        <button class="btn btn-primary" name="save_schedule">
            Save Schedule
        </button>

    </form>

</div>

<!-- =========================
     SCHEDULE TABLE
========================= -->

<div class="card shadow p-4 mt-4">

    <h4 class="mb-3">
        Current Schedule
    </h4>

    <?php if ($schedules->num_rows > 0) { ?>

    <table class="table table-bordered table-hover">

        <thead class="table-dark">
            <tr>
                <th>Day</th>
                <th>Working Time</th>
                <th>Break</th>
                <th>Slot Duration</th>
                <th>Action</th>
            </tr>
        </thead>

        <tbody>

        <?php while ($row = $schedules->fetch_assoc()) { ?>

        <tr>

            <td>
                <?php echo $row['day_of_week']; ?>
            </td>

            <td>
                <?php echo $row['start_time']; ?>
                -
                <?php echo $row['end_time']; ?>
            </td>

            <td>

                <?php
                if ($row['break_start']) {
                    echo $row['break_start'] . " - " . $row['break_end'];
                } else {
                    echo "No Break";
                }
                ?>

            </td>

            <td>
                <?php echo $row['slot_duration']; ?> mins
            </td>

            <td>

                <a
                    href="?delete=<?php echo $row['schedule_id']; ?>"
                    class="btn btn-danger btn-sm"
                    onclick="return confirm('Delete schedule?')"
                >
                    Delete
                </a>

            </td>

        </tr>

        <?php } ?>

        </tbody>

    </table>

    <?php } else { ?>

    <div class="alert alert-info">
        No schedule added yet.
    </div>

    <?php } ?>

</div>

</div>