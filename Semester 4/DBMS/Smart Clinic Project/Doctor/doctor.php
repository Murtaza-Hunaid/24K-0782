<?php
session_start();
include("../db.php");

if ($_SESSION['role'] != 'doctor') {
    header("Location: login.php");
    exit();
}

include("../layout.php");
?>

<h2 class="mb-4">Doctor Dashboard</h2>

<div class="row">

    <!-- APPOINTMENTS -->
    <div class="col-md-6 mb-4">
        <a href="doctor_my_appointment.php" class="text-decoration-none text-dark">
            <div class="card stats-card text-center">
                <div class="card-body">
                    <i class="fas fa-calendar-alt fa-3x text-primary mb-3"></i>
                    <h5>My Appointments</h5>
                    <p>View and manage patient appointments</p>
                </div>
            </div>
        </a>
    </div>

    <!-- PLACEHOLDERS -->
    <div class="col-md-6 mb-4">
        <a href="doctor_prescription_page.php" class="text-decoration-none text-dark">
            <div class="card stats-card text-center">
                <div class="card-body">
                    <i class="fas fa-prescription-bottle-alt fa-3x text-warning mb-3"></i>
                    <h5>Prescriptions</h5>
                    <p>Manage medicines</p>
                </div>
            </div>
        </a>
    </div>

    <div class="col-md-6 mb-4">
        <a href="doctor_schedule.php">
            <div class="card stats-card text-center">
                <div class="card-body">
                    <i class="fas fa-calendar-day fa-3x text-info mb-3"></i>
                    <h5>Schedule</h5>
                    <p>View daily schedule</p>
                </div>
            </div>
        </a>
    </div>

</div>

</div></div></body></html>