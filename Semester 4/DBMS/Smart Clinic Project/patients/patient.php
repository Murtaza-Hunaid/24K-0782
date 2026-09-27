<?php
session_start();
if ($_SESSION['role'] != 'patient') {
    header("Location: login.php");
    exit();
}

include("../layout.php");
?>

<h2>Patient Dashboard</h2>

<div class="row">
    <?php if ($_SESSION['role'] == 'patient') { ?>
        <div class="col-md-4 mb-4">
            <a href='book_appointment.php' class="col-md-4 mb-4 text-decoration-none" color="inherit">
                <div class="card stats-card text-center">
                    <div class="card-body">
                        <i class="fas fa-calendar-plus fa-3x text-primary mb-3"></i>
                        <h5 class="card-title">Book Appointment</h5>
                        <p class="card-text">Schedule a new visit quickly</p>
                    </div>
                </div>
            </a>
        </div>
        
        <div class="col-md-4 mb-4">
            <a href='my_appointments.php' class="text-decoration-none" color="inherit">
                <div class="card stats-card text-center">
                    <div class="card-body">
                        <i class="fas fa-calendar-alt fa-3x text-info mb-3"></i>
                        <h5 class="card-title">My Appointments</h5>
                        <p class="card-text">Track your upcoming visits</p>
                    </div>
                </div>
            </a>
        </div>
        <div class="col-md-4 mb-4">
            <a href='medical_records.php' class="text-decoration-none" color="inherit">
                <div class="card stats-card text-center">
                    <div class="card-body">
                        <i class="fas fa-notes-medical fa-3x text-success mb-3"></i>
                        <h5 class="card-title">Medical Record</h5>
                        <p class="card-text">Review your health history</p>
                    </div>
                </div>
            </a>
        </div>
    <?php } ?>
</div>

</div>
</div>
</body>
</html>