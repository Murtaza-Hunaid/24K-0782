<?php
session_start();
include("../db.php");

if ($_SESSION['role'] != 'admin') {
    header("Location: login.php");
    exit();
}

include("../layout.php");

$query = "

SELECT 

a.*,

p.first_name AS patient_name,

d.first_name AS doctor_name

FROM appointments a

JOIN patients p
ON a.patient_id = p.patient_id

JOIN doctors d
ON a.doctor_id = d.doctor_id

ORDER BY a.appointment_date DESC

";

$res = $conn->query($query);
?>

<h2 class="mb-4">
All Appointments
</h2>

<div class="card shadow p-4">

<table class="table table-hover">

<thead class="table-dark">

<tr>
<th>ID</th>
<th>Patient</th>
<th>Doctor</th>
<th>Date</th>
<th>Time</th>
<th>Status</th>
<th>Payment</th>
</tr>

</thead>

<tbody>

<?php while ($a = $res->fetch_assoc()) { ?>

<tr>

<td><?php echo $a['appointment_id']; ?></td>

<td><?php echo $a['patient_name']; ?></td>

<td>
Dr. <?php echo $a['doctor_name']; ?>
</td>

<td><?php echo $a['appointment_date']; ?></td>

<td><?php echo $a['appointment_time']; ?></td>

<td><?php echo ucfirst($a['status']); ?></td>

<td>

<?php

if ($a['payment_status'] == 'paid') {

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

<?php } ?>

</tbody>

</table>

</div>

</div></div></body></html>