<?php
/**
 * Admin Patient Management
 * Handles adding and managing patient records
 */

session_start();
include("../db.php");

// Security check - only admins can access
if ($_SESSION['role'] != 'admin') {
    header("Location: login.php");
    exit();
}

$message = "";

/* =========================
   ADD PATIENT
========================= */
if (isset($_POST['add_patient'])) {
    $username = $_POST['username'];
    $password = password_hash($_POST['password'], PASSWORD_DEFAULT);

    $first_name = $_POST['first_name'];
    $last_name = $_POST['last_name'];
    $email = $_POST['email'];
    $phone = $_POST['phone'];
    $gender = strtolower($_POST['gender']); // Normalize to lowercase

    /* 1. INSERT USER */
    $stmt = $conn->prepare("
        INSERT INTO users (username, password, role)
        VALUES (?, ?, 'patient')
    ");

    $stmt->bind_param("ss", $username, $password);

    if ($stmt->execute()) {
        $user_id = $conn->insert_id;

        /* 2. INSERT PATIENT (MATCH YOUR SCHEMA) */
        $stmt2 = $conn->prepare("
            INSERT INTO patients
            (user_id, first_name, last_name, age, gender, contact, email, address, blood_group)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
        ");

        // Default values for optional fields
        $age = 0;
        $address = "";
        $blood_group = "N/A";

        $stmt2->bind_param("ississsss",
            $user_id,
            $first_name,
            $last_name,
            $age,
            $gender,
            $phone,
            $email,
            $address,
            $blood_group
        );

        if ($stmt2->execute()) {
            $message = "<div class='alert alert-success'>Patient added successfully.</div>";
        } else {
            $message = "<div class='alert alert-danger'>Patient error: " . $stmt2->error . "</div>";
        }

    } else {
        $message = "<div class='alert alert-danger'>User error: " . $stmt->error . "</div>";
    }
}
/* =========================
   DELETE PATIENT
========================= */
if (isset($_GET['delete'])) {
    $id = $_GET['delete'];

    // Note: Using direct query for simplicity, but prepared statements are recommended for production
    $conn->query("DELETE FROM patients WHERE patient_id=$id");

    $message = "
    <div class='alert alert-success'>
        Patient deleted successfully.
    </div>";
}

include("../layout.php");
?>

<h2 class="mb-4">Manage Patients</h2>

<?php echo $message; ?>

<!-- ADD PATIENT FORM -->
<div class="card shadow p-4 mb-5">

<h4 class="mb-4">Add Patient</h4>

<form method="POST">

<div class="row">

<div class="col-md-6 mb-3">
<label>Username</label>
<input type="text" name="username"
class="form-control" required>
</div>

<div class="col-md-6 mb-3">
<label>Password</label>
<input type="password" name="password"
class="form-control" required>
</div>

<div class="col-md-6 mb-3">
<label>First Name</label>
<input type="text" name="first_name"
class="form-control" required>
</div>

<div class="col-md-6 mb-3">
<label>Last Name</label>
<input type="text" name="last_name"
class="form-control" required>
</div>

<div class="col-md-6 mb-3">
<label>Email</label>
<input type="email" name="email"
class="form-control">
</div>

<div class="col-md-6 mb-3">
<label>Phone</label>
<input type="text" name="phone"
class="form-control">
</div>

<div class="col-md-6 mb-3">
<label>Gender</label>

<select name="gender"
class="form-control">

<option value="Male">Male</option>
<option value="Female">Female</option>

</select>

</div>

</div>

<button class="btn btn-success"
name="add_patient">

Add Patient

</button>

</form>

</div>

<!-- PATIENT TABLE -->
<div class="card shadow p-4">

<h4 class="mb-4">Patient List</h4>

<table class="table table-hover">

<thead class="table-dark">

<tr>
<th>ID</th>
<th>Name</th>
<th>Email</th>
<th>Phone</th>
<th>Gender</th>
<th>Action</th>
</tr>

</thead>

<tbody>

<?php

$res = $conn->query("SELECT * FROM patients");

while ($p = $res->fetch_assoc()) {

?>

<tr>

<td><?php echo $p['patient_id']; ?></td>

<td>
<?php
echo $p['first_name'] . " " .
     $p['last_name'];
?>
</td>

<td><?php echo $p['email']; ?></td>

<td><?php echo $p['contact']; ?></td>

<td><?php echo $p['gender']; ?></td>

<td>

<a href="?delete=<?php echo $p['patient_id']; ?>"
class="btn btn-danger btn-sm"
onclick="return confirm('Delete patient?')">

Delete

</a>

</td>

</tr>

<?php } ?>

</tbody>

</table>

</div>

</div></div></body></html>