<?php
session_start();
include("../db.php");

// Security check
if ($_SESSION['role'] != 'patient') {
    header("Location: login.php");
    exit();
}

// Get patient_id
$user_id = $_SESSION['user_id'];

$stmt = $conn->prepare("SELECT patient_id FROM patients WHERE user_id = ?");
$stmt->bind_param("i", $user_id);
$stmt->execute();
$result = $stmt->get_result();
$row = $result->fetch_assoc();

$patient_id = $row['patient_id'];

// Fetch medical records with doctor info
$query = "
    SELECT mr.*, d.first_name, d.last_name, d.specialization
    FROM medical_records mr
    JOIN doctors d ON mr.doctor_id = d.doctor_id
    WHERE mr.patient_id = ?
    ORDER BY mr.record_date DESC
";

$stmt2 = $conn->prepare($query);
$stmt2->bind_param("i", $patient_id);
$stmt2->execute();
$records = $stmt2->get_result();
?>

<?php include("../layout.php"); ?>

<h2 class="mb-4">My Medical Records</h2>

<div class="card shadow p-4">

<?php if ($records->num_rows > 0) { ?>

    <?php while ($row = $records->fetch_assoc()) { ?>

        <div class="card mb-3 p-3">

            <h5>
                Dr. <?php echo $row['first_name'] . " " . $row['last_name']; ?>
                <small class="text-muted">(<?php echo $row['specialization']; ?>)</small>
            </h5>

            <p><strong>Date:</strong> <?php echo $row['record_date']; ?></p>
            <p><strong>Diagnosis:</strong> <?php echo $row['diagnosis']; ?></p>
            <p><strong>Notes:</strong> <?php echo $row['notes']; ?></p>

            <!-- PRESCRIPTIONS -->
            <h6 class="mt-3">Prescriptions:</h6>

            <ul>
                <?php
                $record_id = $row['record_id'];

                $pres = $conn->query("
                    SELECT * FROM prescriptions 
                    WHERE record_id = $record_id
                ");

                while ($p = $pres->fetch_assoc()) {
                    echo "<li>{$p['medicine_name']} - {$p['dosage']}</li>";
                }
                ?>
            </ul>

        </div>

    <?php } ?>

<?php } else { ?>

    <div class="alert alert-info">
        No medical records found.
    </div>

<?php } ?>

</div>

</div></div></body></html>