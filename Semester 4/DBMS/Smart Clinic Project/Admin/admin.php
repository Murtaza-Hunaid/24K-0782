<?php
session_start();
include("../db.php");

if ($_SESSION['role'] != 'admin') {
    header("Location: login.php");
    exit();
}

include("../layout.php");

/* =========================
   COUNTS
========================= */

$doctors =
$conn->query("SELECT COUNT(*) AS total FROM doctors")
->fetch_assoc()['total'];

$patients =
$conn->query("SELECT COUNT(*) AS total FROM patients")
->fetch_assoc()['total'];

$appointments =
$conn->query("SELECT COUNT(*) AS total FROM appointments")
->fetch_assoc()['total'];

$revenue =
$conn->query("
SELECT SUM(amount) AS total 
FROM billing 
WHERE payment_status='paid'
")->fetch_assoc()['total'];

if (!$revenue) {
    $revenue = 0;
}
?>

<h2 class="mb-4">
    Admin Dashboard
</h2>

<div class="row">

<!-- DOCTORS -->
<div class="col-md-3 mb-4">

<a href="admin_doctors.php"
class="text-decoration-none text-dark">

<div class="card stats-card text-center p-4">

<i class="fas fa-user-md fa-3x text-primary mb-3"></i>

<h3><?php echo $doctors; ?></h3>

<h5>Doctors</h5>

</div>

</a>

</div>

<!-- PATIENTS -->
<div class="col-md-3 mb-4">

<a href="admin_patients.php"
class="text-decoration-none text-dark">

<div class="card stats-card text-center p-4">

<i class="fas fa-users fa-3x text-success mb-3"></i>

<h3><?php echo $patients; ?></h3>

<h5>Patients</h5>

</div>

</a>

</div>

<!-- APPOINTMENTS -->
<div class="col-md-3 mb-4">

<a href="admin_appointments.php"
class="text-decoration-none text-dark">

<div class="card stats-card text-center p-4">

<i class="fas fa-calendar-check fa-3x text-warning mb-3"></i>

<h3><?php echo $appointments; ?></h3>

<h5>Appointments</h5>

</div>

</a>

</div>

<!-- REVENUE -->
<div class="col-md-3 mb-4">

<a href="admin_billing.php"
class="text-decoration-none text-dark">

<div class="card stats-card text-center p-4">

<i class="fas fa-money-bill-wave fa-3x text-danger mb-3"></i>

<h3>Rs. <?php echo $revenue; ?></h3>

<h5>Revenue</h5>

</div>

</a>

</div>

</div>

<!-- QUICK ACTIONS -->

<div class="card shadow p-4">

<h4 class="mb-4">
    Quick Actions
</h4>

<div class="row">

<div class="col-md-4 mb-3">

<a href="admin_doctors.php"
class="btn btn-primary w-100 p-3">

<i class="fas fa-user-md me-2"></i>

Manage Doctors

</a>

</div>

<div class="col-md-4 mb-3">

<a href="admin_patients.php"
class="btn btn-success w-100 p-3">

<i class="fas fa-users me-2"></i>

View Patients

</a>

</div>

<div class="col-md-4 mb-3">

<a href="admin_appointments.php"
class="btn btn-warning w-100 p-3">

<i class="fas fa-calendar-check me-2"></i>

Appointments

</a>

</div>

<div class="col-md-6 mb-3">

<a href="admin_billing.php"
class="btn btn-danger w-100 p-3">

<i class="fas fa-file-invoice-dollar me-2"></i>

Billing

</a>

</div>

<div class="col-md-6 mb-3">

<a href="admin_reports.php"
class="btn btn-dark w-100 p-3">

<i class="fas fa-chart-line me-2"></i>

Reports & Analytics

</a>

</div>

</div>

</div>

</div></div></body></html>