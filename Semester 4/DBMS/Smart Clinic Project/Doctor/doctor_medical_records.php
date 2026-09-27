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

if (!isset($_GET['appointment_id'])) {
    echo "<div class='alert alert-danger'>Invalid request. No appointment selected.</div>";
}
    include("../layout.php");
exit();


$appointment_id = $_GET['appointment_id'];

// Get patient
$stmt2 = $conn->prepare("
    SELECT patient_id FROM appointments 
    WHERE appointment_id = ? AND doctor_id = ?
");
$stmt2->bind_param("ii", $appointment_id, $doctor_id);
$stmt2->execute();
$res = $stmt2->get_result();

if ($res->num_rows == 0) {
    die("Unauthorized access.");
}

$data = $res->fetch_assoc();
$patient_id = $data['patient_id'];

$message = "";

if (isset($_POST['save'])) {

    $diagnosis = $_POST['diagnosis'];
    $notes = $_POST['notes'];
    $medicine = $_POST['medicine'];
    $dosage = $_POST['dosage'];

    // 1. Insert medical record
    $stmt3 = $conn->prepare("
        INSERT INTO medical_records (patient_id, doctor_id, diagnosis, notes, record_date)
        VALUES (?, ?, ?, ?, NOW())
    ");
    $stmt3->bind_param("iiss", $patient_id, $doctor_id, $diagnosis, $notes);

    if ($stmt3->execute()) {

        $record_id = $stmt3->insert_id;

        // 2. Insert prescription (THIS WAS MISSING)
        $stmt4 = $conn->prepare("
            INSERT INTO prescriptions (record_id, medicine_name, dosage)
            VALUES (?, ?, ?)
        ");
        $stmt4->bind_param("iss", $record_id, $medicine, $dosage);
        $stmt4->execute();

        // 3. Mark appointment completed
        $conn->query("
            UPDATE appointments 
            SET status = 'completed'
            WHERE appointment_id = $appointment_id
        ");

        $message = "<div class='alert alert-success'>Record saved successfully!</div>";

    } else {
        $message = "<div class='alert alert-danger'>Error saving record.</div>";
    }
}

include("../layout.php");
?>

<h2>Add Medical Record</h2>

<?php echo $message; ?>

<form method="POST" class="card p-4 shadow">

    <label>Diagnosis</label>
    <input type="text" name="diagnosis" class="form-control mb-3" required>

    <label>Notes</label>
    <textarea name="notes" class="form-control mb-3"></textarea>

    <h5>Prescription</h5>

    <label>Medicine</label>
    <input type="text" name="medicine" class="form-control mb-3" required>

    <label>Dosage</label>
    <input type="text" name="dosage" class="form-control mb-3" required>

    <button type="submit" name="save" class="btn btn-primary">
        Save Record
    </button>

</form>

</div></div></body></html>