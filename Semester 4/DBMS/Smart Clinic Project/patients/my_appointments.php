<?php
session_start();
include("../db.php");

// Security check
if ($_SESSION['role'] != 'patient') {
    header("Location: login.php");
    exit();
}

if (isset($_POST['cancel_id'])) {

    $appointment_id = $_POST['cancel_id'];

    // Get patient_id from session
    $user_id = $_SESSION['user_id'];

    $stmt = $conn->prepare("SELECT patient_id FROM patients WHERE user_id = ?");
    $stmt->bind_param("i", $user_id);
    $stmt->execute();
    $result = $stmt->get_result();
    $row = $result->fetch_assoc();

    $patient_id = $row['patient_id'];

    // Cancel appointment (only if it belongs to this patient)
    $stmt2 = $conn->prepare("
        UPDATE appointments 
        SET status = 'cancelled' 
        WHERE appointment_id = ? AND patient_id = ?
    ");
    $stmt2->bind_param("ii", $appointment_id, $patient_id);
    $stmt2->execute();

    header("Location: my_appointments.php");
    exit();
}


// Get patient_id from user_id
$user_id = $_SESSION['user_id'];

$stmt = $conn->prepare("SELECT patient_id FROM patients WHERE user_id = ?");
$stmt->bind_param("i", $user_id);
$stmt->execute();
$result = $stmt->get_result();

if ($result->num_rows == 0) {
    die("Patient not found.");
}

$row = $result->fetch_assoc();
$patient_id = $row['patient_id'];

// Fetch appointments with doctor info
$query = "
    SELECT a.*, d.first_name, d.last_name, d.specialization
    FROM appointments a
    JOIN doctors d ON a.doctor_id = d.doctor_id
    WHERE a.patient_id = ?
    ORDER BY a.appointment_date DESC, a.appointment_time DESC
";

$stmt2 = $conn->prepare($query);
$stmt2->bind_param("i", $patient_id);
$stmt2->execute();
$appointments = $stmt2->get_result();
?>

<?php include("../layout.php"); ?>

<h2 class="mb-4">My Appointments</h2>

<div class="card shadow p-4">

<?php if ($appointments->num_rows > 0) { ?>

    <table class="table table-hover">
        <thead class="table-dark">
            <tr>
                <th>Doctor</th>
                <th>Specialization</th>
                <th>Date</th>
                <th>Time</th>
                <th>Reason</th>
                <th>Status</th>
                <th>Action</th>
                <th>Payment</th>
                <th>Invoice</th>
            </tr>
        </thead>

        <tbody>

        <?php while ($row = $appointments->fetch_assoc()) { ?>

            <tr>
                <td>Dr. <?php echo $row['first_name'] . " " . $row['last_name']; ?></td>
                <td><?php echo $row['specialization']; ?></td>
                <td><?php echo $row['appointment_date']; ?></td>
                <td><?php echo $row['appointment_time']; ?></td>
                <td><?php echo $row['reason']; ?></td>

                <td>
                    <?php
                    $status = $row['status'];

                    if ($status == 'pending') {
                        echo "<span class='badge bg-warning'>Pending</span>";
                    } elseif ($status == 'confirmed') {
                        echo "<span class='badge bg-success'>Confirmed</span>";
                    } elseif ($status == 'completed') {
                        echo "<span class='badge bg-primary'>Completed</span>";
                    } else {
                        echo "<span class='badge bg-danger'>Cancelled</span>";
                    }
                    ?>
                </td>
                <td>
                    <?php if ($row['status'] == 'pending' || $row['status'] == 'confirmed') { ?>

                        <form method="POST" style="display:inline;">
                            <input type="hidden" name="cancel_id" value="<?php echo $row['appointment_id']; ?>">
                            <button type="submit" class="btn btn-danger btn-sm"
                                onclick="return confirm('Cancel this appointment?');">
                                Cancel
                            </button>
                        </form>

                    <?php } else { ?>
                        <span class="text-muted">N/A</span>
                    <?php } ?>
                </td>
                <td>
                    <?php

                    if ($row['payment_status'] == 'paid') {

                        echo "<span class='badge bg-success'>
                                Paid
                            </span>";

                    } else {

                        echo "<span class='badge bg-danger'>
                                Unpaid
                            </span>";
                    }

                    ?>

                </td>
                <td>
                    <a
                    href="/Project_DBMS/invoice.php?appointment_id=<?php echo $row['appointment_id']; ?>"
                    class="btn btn-sm btn-dark"
                    >

                    View Invoice

                    </a>

                </td>
            </tr>   

        <?php } ?>

        </tbody>
    </table>

<?php } else { ?>

    <div class="alert alert-info">
        <i class="fas fa-info-circle"></i>
        You have no appointments yet.
    </div>

<?php } ?>

</div>

</div>
</div>
</body></html>