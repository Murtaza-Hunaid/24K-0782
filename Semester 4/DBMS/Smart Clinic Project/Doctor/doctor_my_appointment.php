<?php
session_start();
include("../db.php");

if ($_SESSION['role'] != 'doctor') {
    header("Location: login.php");
    exit();
}

$user_id = $_SESSION['user_id'];

// Get doctor_id
$stmt = $conn->prepare("SELECT doctor_id FROM doctors WHERE user_id = ?");
$stmt->bind_param("i", $user_id);
$stmt->execute();
$result = $stmt->get_result();
$row = $result->fetch_assoc();
$doctor_id = $row['doctor_id'];

// Handle confirm/reject
if (isset($_POST['action'])) {

    $appointment_id = $_POST['appointment_id'];
    $action = $_POST['action'];

    if ($action == 'confirm') {
        $status = 'confirmed';
    } elseif ($action == 'reject') {
        $status = 'cancelled';
    }

    $stmt2 = $conn->prepare("
        UPDATE appointments 
        SET status = ? 
        WHERE appointment_id = ? AND doctor_id = ?
    ");
    $stmt2->bind_param("sii", $status, $appointment_id, $doctor_id);
    $stmt2->execute();

    header("Location: doctor_my_appointment.php");
    exit();
}

// Fetch appointments
$query = "
    SELECT a.*, p.first_name, p.last_name
    FROM appointments a
    JOIN patients p ON a.patient_id = p.patient_id
    WHERE a.doctor_id = ?
    ORDER BY a.appointment_date DESC
";

$stmt3 = $conn->prepare($query);
$stmt3->bind_param("i", $doctor_id);
$stmt3->execute();
$result = $stmt3->get_result();

include("../layout.php");
?>

<h2 class="mb-4">My Appointments</h2>

<div class="card p-4 shadow">

<table class="table table-hover">
    <thead class="table-dark">
        <tr>
            <th>Patient</th>
            <th>Date</th>
            <th>Time</th>
            <th>Reason</th>
            <th>Status</th>
            <th>Action</th>
        </tr>
    </thead>

    <tbody>

    <?php while ($row = $result->fetch_assoc()) { ?>

        <tr>
            <td><?php echo $row['first_name'] . " " . $row['last_name']; ?></td>
            <td><?php echo $row['appointment_date']; ?></td>
            <td><?php echo $row['appointment_time']; ?></td>
            <td><?php echo $row['reason']; ?></td>

            <td>
                <?php
                if ($row['status'] == 'pending') echo "<span class='badge bg-warning'>Pending</span>";
                elseif ($row['status'] == 'confirmed') echo "<span class='badge bg-success'>Confirmed</span>";
                elseif ($row['status'] == 'cancelled') echo "<span class='badge bg-danger'>Cancelled</span>";
                else echo "<span class='badge bg-primary'>Completed</span>";
                ?>
            </td>

            <td>

                <?php if ($row['status'] == 'pending') { ?>

                    <form method="POST" style="display:inline;">
                        <input type="hidden" name="appointment_id" value="<?php echo $row['appointment_id']; ?>">
                        <button name="action" value="confirm" class="btn btn-success btn-sm">Confirm</button>
                    </form>

                    <form method="POST" style="display:inline;">
                        <input type="hidden" name="appointment_id" value="<?php echo $row['appointment_id']; ?>">
                        <button name="action" value="reject" class="btn btn-danger btn-sm">Reject</button>
                    </form>

                <?php } ?>

                <?php if ($row['status'] == 'confirmed') { ?>
                    <a href="doctor_medical_record.php?appointment_id=<?php echo $row['appointment_id']; ?>"
                       class="btn btn-primary btn-sm">
                        Add Record
                    </a>
                <?php } ?>

            </td>
        </tr>

    <?php } ?>

    </tbody>
</table>

</div>

</div></div></body></html>