<?php
session_start();
include("../db.php");

if ($_SESSION['role'] != 'admin') {
    header("Location: login.php");
    exit();
}

include("../layout.php");

$patients =
$conn->query("SELECT COUNT(*) total FROM patients")
->fetch_assoc()['total'];

$doctors =
$conn->query("SELECT COUNT(*) total FROM doctors")
->fetch_assoc()['total'];

$appointments =
$conn->query("SELECT COUNT(*) total FROM appointments")
->fetch_assoc()['total'];

$revenue =
$conn->query("
SELECT SUM(amount) total
FROM billing
WHERE payment_status='paid'
")->fetch_assoc()['total'];

if (!$revenue) $revenue = 0;
?>

<h2 class="mb-4">
Reports & Analytics
</h2>

<div class="row">

<div class="col-md-3 mb-4">

<div class="card shadow text-center p-4">

<h1><?php echo $patients; ?></h1>

<h5>Total Patients</h5>

</div>

</div>

<div class="col-md-3 mb-4">

<div class="card shadow text-center p-4">

<h1><?php echo $doctors; ?></h1>

<h5>Total Doctors</h5>

</div>

</div>

<div class="col-md-3 mb-4">

<div class="card shadow text-center p-4">

<h1><?php echo $appointments; ?></h1>

<h5>Appointments</h5>

</div>

</div>

<div class="col-md-3 mb-4">

<div class="card shadow text-center p-4">

<h1>Rs. <?php echo $revenue; ?></h1>

<h5>Revenue</h5>

</div>

</div>

</div>

</div></div></body></html>