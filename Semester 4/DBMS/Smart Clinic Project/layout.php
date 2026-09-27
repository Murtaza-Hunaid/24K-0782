<?php
if (!isset($_SESSION)) session_start();
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>SmartClinic Dashboard</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">
    <link href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css" rel="stylesheet">
    <style>
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            margin: 0;
        }
        .navbar {
            background: linear-gradient(90deg, #4facfe 0%, #00f2fe 100%);
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
        }
        .sidebar {
            background: rgba(255, 255, 255, 0.95);
            backdrop-filter: blur(10px);
            border-right: 1px solid rgba(0, 0, 0, 0.1);
            box-shadow: 2px 0 5px rgba(0, 0, 0, 0.1);
        }
        .sidebar .nav-link {
            color: #333;
            font-weight: 500;
            padding: 12px 20px;
            border-radius: 8px;
            margin-bottom: 5px;
            transition: all 0.3s ease;
        }
        .sidebar .nav-link:hover {
            background: linear-gradient(90deg, #667eea 0%, #764ba2 100%);
            color: white;
            transform: translateX(5px);
        }
        .sidebar .nav-link i {
            margin-right: 10px;
            width: 20px;
        }
        @media (max-width: 991px) {
            .sidebar {
                position: absolute;
                top: 0;
                left: 0;
                width: 100%;
                z-index: 1050;
                min-height: 100vh;
                padding-bottom: 20px;
            }
            .main-content {
                margin-top: 20px;
                padding: 20px;
            }
        }
        .main-content {
            background: rgba(255, 255, 255, 0.9);
            backdrop-filter: blur(10px);
            border-radius: 15px;
            margin: 20px;
            padding: 30px;
            box-shadow: 0 8px 32px rgba(0, 0, 0, 0.1);
        }
        .welcome-card {
            background: linear-gradient(135deg, #f093fb 0%, #f5576c 100%);
            color: white;
            border: none;
            border-radius: 15px;
        }
        .stats-card {
            background: white;
            border: none;
            border-radius: 15px;
            box-shadow: 0 4px 15px rgba(0, 0, 0, 0.1);
            transition: transform 0.3s ease;
        }
        .stats-card:hover {
            transform: translateY(-5px);
        }
    </style>
</head>

<body>

<!-- NAVBAR -->
<nav class="navbar navbar-expand-lg navbar-dark px-4 py-3">
    <div class="d-flex align-items-center">
        <i class="fas fa-clinic-medical fa-2x me-3 text-white"></i>
        <span class="navbar-brand mb-0 h1">SmartClinic</span>
        <button class="navbar-toggler ms-3 border-0" type="button" data-bs-toggle="collapse" data-bs-target="#sidebarMenu" aria-controls="sidebarMenu" aria-expanded="false" aria-label="Toggle navigation">
            <span class="navbar-toggler-icon"></span>
        </button>
    </div>
    <div class="ms-auto d-flex align-items-center">
        <span class="text-white me-3">
            <i class="fas fa-user-circle me-2"></i>
            <?php echo $_SESSION['username']; ?>
        </span>
        <a href="/Project_DBMS_TEST/logout.php" class="btn btn-outline-light btn-sm">
            <i class="fas fa-sign-out-alt me-1"></i>Logout
        </a>
    </div>
</nav>

<div class="d-flex">

    <!-- SIDEBAR -->
    <div class="collapse d-lg-block sidebar p-4 position-relative" id="sidebarMenu" style="width: 280px; min-height: 100vh;">
        <button class="btn btn-sm btn-outline-secondary d-lg-none position-absolute top-0 end-0 mt-3 me-3" type="button" data-bs-toggle="collapse" data-bs-target="#sidebarMenu" aria-label="Close sidebar">
            <i class="fas fa-times"></i>
        </button>
        <h5 class="mb-4 text-center">
            <i class="fas fa-bars me-2"></i>Menu
        </h5>
        <ul class="nav flex-column">

            <?php if ($_SESSION['role'] == 'admin') { ?>
                <li class="nav-item">
                    <a class="nav-link" href="/Project_DBMS_TEST/Admin/admin_doctors.php" data-bs-toggle="collapse" data-bs-target="#sidebarMenu" onclick="event.stopPropagation()">
                        <i class="fas fa-user-md"></i>Manage Doctors
                    </a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="/Project_DBMS_TEST/Admin/admin_patients.php" data-bs-toggle="collapse" data-bs-target="#sidebarMenu" onclick="event.stopPropagation()">
                        <i class="fas fa-users"></i>View Patients
                    </a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="/Project_DBMS_TEST/Admin/admin_appointments.php" data-bs-toggle="collapse" data-bs-target="#sidebarMenu" onclick="event.stopPropagation()">
                        <i class="fas fa-calendar-check"></i>Appointments
                    </a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="/Project_DBMS_TEST/Admin/admin_billing.php" data-bs-toggle="collapse" data-bs-target="#sidebarMenu" onclick="event.stopPropagation()">
                        <i class="fas fa-file-invoice-dollar"></i>Billing
                    </a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="/Project_DBMS_TEST/Admin/admin_reports.php" data-bs-toggle="collapse" data-bs-target="#sidebarMenu" onclick="event.stopPropagation()">
                        <i class="fas fa-chart-line"></i>Reports
                    </a>
                </li>
            <?php } ?>

            <?php if ($_SESSION['role'] == 'doctor') { ?>
                <li class="nav-item">
                    <a class="nav-link" href="/Project_DBMS_TEST/Doctor/doctor_my_appointment.php" data-bs-toggle="collapse" data-bs-target="#sidebarMenu" onclick="event.stopPropagation()">
                        <i class="fas fa-calendar-alt"></i>My Appointments
                    </a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="/Project_DBMS_TEST/Doctor/doctor_medical_records.php" data-bs-toggle="collapse" data-bs-target="#sidebarMenu" onclick="event.stopPropagation()">
                        <i class="fas fa-file-medical"></i>Medical Records
                    </a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="/Project_DBMS_TEST/Doctor/doctor_prescription_page.php" data-bs-toggle="collapse" data-bs-target="#sidebarMenu" onclick="event.stopPropagation()">
                        <i class="fas fa-prescription-bottle-alt"></i>Prescriptions
                    </a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="/Project_DBMS_TEST/Doctor/doctor_schedule.php" data-bs-toggle="collapse" data-bs-target="#sidebarMenu" onclick="event.stopPropagation()">
                        <i class="fas fa-calendar-day"></i>Schedule
                    </a>
                </li>
            <?php } ?>

            <?php if ($_SESSION['role'] == 'patient') { ?>
                <li class="nav-item">
                    <a class="nav-link" href="/Project_DBMS_TEST/patients/book_appointment.php">
                        <i class="fas fa-calendar-plus"></i>Book Appointment
                    </a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="/Project_DBMS_TEST/patients/my_appointments.php" >
                        <i class="fas fa-calendar-alt"></i>My Appointments
                    </a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="/Project_DBMS_TEST/patients/medical_records.php"  >
                        <i class="fas fa-notes-medical"></i>Medical Record
                    </a>
                </li>
            <?php } ?>

        </ul>
    </div>

    <!-- MAIN CONTENT -->
    <div class="main-content flex-grow-1">            
           <div class="row">
                <div class="col-12 mb-4">
                    <div class="card welcome-card">
                        <div class="card-body text-center py-5">
                            <h2 class="card-title">
                                <i class="fas fa-heartbeat me-2"></i>
                                Welcome to SmartClinic Dashboard
                            </h2>
                            <p class="card-text">Manage your healthcare needs efficiently and securely.</p>
                        </div>
                    </div>
                </div>
            </div> 
    <!-- </div>
</div> -->

<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/js/bootstrap.bundle.min.js"></script>
<!-- </body>
</html> -->