<?php
/**
 * Invoice Generation Page
 * Displays billing information for a specific appointment
 */

session_start();
include("db.php");

// Validate required parameters
if (!isset($_GET['appointment_id'])) {
    die("Invalid invoice request - no appointment ID provided.");
}

if (!isset($_SESSION['user_id'])) {
    header("Location: login.php");
    exit();
}

$appointment_id = $_GET['appointment_id'];

// Build comprehensive invoice query with joins
$query = "
    SELECT
        billing.*,
        appointments.appointment_date,
        appointments.appointment_time,
        patients.first_name AS patient_fname,
        patients.last_name AS patient_lname,
        doctors.first_name AS doctor_fname,
        doctors.specialization
    FROM billing
    JOIN appointments ON billing.appointment_id = appointments.appointment_id
    JOIN patients ON billing.patient_id = patients.patient_id
    JOIN doctors ON appointments.doctor_id = doctors.doctor_id
    WHERE billing.appointment_id = ?
";

// Execute query
$stmt = $conn->prepare($query);
$stmt->bind_param("i", $appointment_id);
$stmt->execute();
$result = $stmt->get_result();

// Check if invoice exists
if ($result->num_rows == 0) {
    die("Invoice not found for the specified appointment.");
}

$data = $result->fetch_assoc();
?>

<!DOCTYPE html>
<html>
<head>

<title>Invoice</title>

<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">

<style>

body{
    background:#f4f7fb;
    font-family:Arial;
}

.invoice-box{
    background:white;
    padding:40px;
    border-radius:15px;
    box-shadow:0 5px 20px rgba(0,0,0,0.1);
}

.print-btn{
    float:right;
}

</style>

</head>
<body>

<div class="container mt-5">

<div class="invoice-box">

<button onclick="window.print()" class="btn btn-primary print-btn">
    Print Receipt
</button>

<h1 class="mb-4">
    SmartClinic Invoice
</h1>

<hr>

<div class="row">

<div class="col-md-6">

<h5>Patient Info</h5>

<p>
<strong>Name:</strong>

<?php
echo $data['patient_fname'] . " " .
     $data['patient_lname'];
?>
</p>

<p>
<strong>Appointment Date:</strong>
<?php echo $data['appointment_date']; ?>
</p>

<p>
<strong>Appointment Time:</strong>
<?php echo $data['appointment_time']; ?>
</p>

</div>

<div class="col-md-6">

<h5>Doctor Info</h5>

<p>
<strong>Doctor:</strong>

Dr.
<?php echo $data['doctor_fname']; ?>
</p>

<p>
<strong>Specialization:</strong>
<?php echo $data['specialization']; ?>
</p>

</div>

</div>

<hr>

<h4 class="mb-3">Billing Details</h4>

<table class="table table-bordered">

<tr>
<th>Consultation Fee</th>
<td>Rs. <?php echo $data['amount']; ?></td>
</tr>

<tr>
<th>Payment Method</th>
<td>
<?php echo ucfirst($data['payment_method']); ?>
</td>
</tr>

<tr>
<th>Payment Status</th>
<td>

<?php

if ($data['payment_status'] == 'paid') {

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
</tr>

<tr>
<th>Invoice Date</th>
<td><?php echo $data['invoice_date']; ?></td>
</tr>

</table>

<div class="mt-5 text-center">

<h5>
Thank you for choosing SmartClinic ❤️
</h5>

<p class="text-muted">
This is a computer-generated receipt.
</p>

</div>

</div>

</div>

</body>
</html>