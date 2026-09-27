<?php
session_start();
include("../db.php");

if ($_SESSION['role'] != 'admin') {
    header("Location: login.php");
    exit();
}

$message = "";

/* =========================
   DELETE DOCTOR (SAFE)
========================= */
if (isset($_GET['delete'])) {

    $doctor_id = $_GET['delete'];

    // STEP 1: get user_id first
    $stmt = $conn->prepare("SELECT user_id FROM doctors WHERE doctor_id = ?");
    $stmt->bind_param("i", $doctor_id);
    $stmt->execute();
    $res = $stmt->get_result();

    if ($res->num_rows > 0) {

        $row = $res->fetch_assoc();
        $user_id = $row['user_id'];

        // STEP 2: delete from users (CASCADE will remove doctor too)
        $stmt2 = $conn->prepare("DELETE FROM users WHERE user_id = ?");
        $stmt2->bind_param("i", $user_id);

        if ($stmt2->execute()) {
            $message = "<div class='alert alert-success'>Doctor fully deleted (user + doctor).</div>";
        } else {
            $message = "<div class='alert alert-danger'>Delete failed.</div>";
        }

    } else {
        $message = "<div class='alert alert-danger'>Doctor not found.</div>";
    }
}

/* =========================
   ADD DOCTOR (FIXED)
========================= */
if (isset($_POST['add_doctor'])) {

    $username = $_POST['username'];
    $password = password_hash($_POST['password'], PASSWORD_DEFAULT); // secure hashing

    $first_name = $_POST['first_name'];
    $last_name = $_POST['last_name'];
    $specialization = $_POST['specialization'];
    $email = $_POST['email'];
    $phone = $_POST['phone'];

    /* 1. CREATE USER */
    $stmt1 = $conn->prepare("
        INSERT INTO users (username, password, role)
        VALUES (?, ?, 'doctor')
    ");

    $stmt1->bind_param("ss", $username, $password);

    if ($stmt1->execute()) {

        $user_id = $conn->insert_id;

        /* 2. CREATE DOCTOR (FIXED SCHEMA) */
        $stmt2 = $conn->prepare("
            INSERT INTO doctors
            (user_id, first_name, last_name, specialization, experience_years, contact, email, consultation_fee)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?)
        ");

        $experience = $_POST['experience'] ?? 0;
        $fee = $_POST['consultation_fee'] ?? 2000;

        $stmt2->bind_param(
            "isssissd",
            $user_id,
            $first_name,
            $last_name,
            $specialization,
            $experience,
            $phone,
            $email,
            $fee
        );

        if ($stmt2->execute()) {
            $message = "<div class='alert alert-success'>Doctor added successfully.</div>";
        } else {
            $message = "<div class='alert alert-danger'>Doctor insert error: " . $stmt2->error . "</div>";
        }

    } else {
        $message = "<div class='alert alert-danger'>User creation failed: " . $stmt1->error . "</div>";
    }
}

include("../layout.php");
?>

<h2 class="mb-4">Manage Doctors</h2>

<?php echo $message; ?>

<!-- ADD DOCTOR FORM -->
<div class="card shadow p-4 mb-5">

<h4 class="mb-4">Add Doctor</h4>

<form method="POST">

<div class="row">

<div class="col-md-6 mb-3">
<label>Username</label>
<input type="text" name="username" class="form-control" required>
</div>

<div class="col-md-6 mb-3">
<label>Password</label>
<input type="password" name="password" class="form-control" required>
</div>

<div class="col-md-6 mb-3">
<label>First Name</label>
<input type="text" name="first_name" class="form-control" required>
</div>

<div class="col-md-6 mb-3">
<label>Last Name</label>
<input type="text" name="last_name" class="form-control" required>
</div>

<div class="col-md-6 mb-3">
<label>Specialization</label>
<input type="text" name="specialization" class="form-control" required>
</div>

<div class="col-md-6 mb-3">
<label>Email</label>
<input type="email" name="email" class="form-control">
</div>

<div class="col-md-6 mb-3">
<label>Experience (Years)</label>
<input type="number" name="experience" class="form-control" min="0">
</div>

<div class="col-md-6 mb-3">
<label>Phone</label>
<input type="text" name="phone" class="form-control">
</div>

<div class="col-md-6 mb-3">
<label>Consultation Fee</label>
<input type="number" name="consultation_fee" class="form-control" min="0" step="0.01">
</div>

</div>

<button class="btn btn-primary" name="add_doctor">
Add Doctor
</button>

</form>

</div>

<!-- DOCTOR LIST -->
<div class="card shadow p-4">

<h4 class="mb-4">Doctor List</h4>

<table class="table table-hover">

<thead class="table-dark">
<tr>
<th>ID</th>
<th>Name</th>
<th>Specialization</th>
<th>Email</th>
<th>Contact</th>
<th>Experience</th>
<th>Consultation Fee</th>
<th>Action</th>
</tr>
</thead>

<tbody>

<?php
$docs = $conn->query("SELECT * FROM doctors");

while ($d = $docs->fetch_assoc()) {
?>

<tr>
<td><?php echo $d['doctor_id']; ?></td>

<td>
Dr. <?php echo $d['first_name'] . " " . $d['last_name']; ?>
</td>

<td><?php echo $d['specialization']; ?></td>

<td><?php echo $d['email']; ?></td>

<td><?php echo $d['contact']; ?></td>

<td><?php echo $d['experience_years']; ?></td>

<td>₹<?php echo number_format($d['consultation_fee'], 2); ?></td>

<td>
<a href="?delete=<?php echo $d['doctor_id']; ?>"
class="btn btn-danger btn-sm"
onclick="return confirm('Delete doctor?')">
Delete
</a>
</td>

</tr>

<?php } ?>

</tbody>
</table>

</div>

</div></div></body></html>