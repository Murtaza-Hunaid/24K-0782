<?php
session_start();
include("../db.php");

if ($_SESSION['role'] != 'doctor') {
    header("Location: login.php");
    exit();
}

$id = $_GET['id'];

// fetch existing
$stmt = $conn->prepare("SELECT * FROM prescriptions WHERE prescription_id = ?");
$stmt->bind_param("i", $id);
$stmt->execute();
$data = $stmt->get_result()->fetch_assoc();

if (isset($_POST['update'])) {

    $medicine = $_POST['medicine'];
    $dosage = $_POST['dosage'];

    $update = $conn->prepare("
        UPDATE prescriptions 
        SET medicine_name = ?, dosage = ?, is_updated = 1
        WHERE prescription_id = ?
    ");
    $update->bind_param("ssi", $medicine, $dosage, $id);
    $update->execute();

    // notify patient (simple version)
    $conn->query("
        INSERT INTO notifications (message, created_at)
        VALUES ('Your prescription has been updated', NOW())
    ");

    header("Location: doctor_prescription_page.php");
    exit();
}

include("../layout.php");
?>

<h2>Edit Prescription</h2>

<form method="POST" class="card p-4">

    <label>Medicine</label>
    <input type="text" name="medicine" 
           value="<?= $data['medicine_name'] ?>" class="form-control mb-3">

    <label>Dosage</label>
    <input type="text" name="dosage" 
           value="<?= $data['dosage'] ?>" class="form-control mb-3">

    <button name="update" class="btn btn-primary">Update</button>

</form>

</div></div></body></html>