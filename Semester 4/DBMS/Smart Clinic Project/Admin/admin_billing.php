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

billing.*,

patients.first_name

FROM billing

JOIN patients
ON billing.patient_id = patients.patient_id

";

$res = $conn->query($query);
?>

<h2 class="mb-4">
Billing Management
</h2>

<div class="card shadow p-4">

<table class="table table-hover">

<thead class="table-dark">

<tr>
<th>Bill ID</th>
<th>Patient</th>
<th>Amount</th>
<th>Method</th>
<th>Status</th>
<th>Invoice</th>
</tr>

</thead>

<tbody>

<?php while ($b = $res->fetch_assoc()) { ?>

<tr>

<td><?php echo $b['bill_id']; ?></td>

<td><?php echo $b['first_name']; ?></td>

<td>Rs. <?php echo $b['amount']; ?></td>

<td>
<?php echo ucfirst($b['payment_method']); ?>
</td>

<td>

<?php

if ($b['payment_status'] == 'paid') {

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

<td>

<a
href="/Project_DBMS/invoice.php?appointment_id=<?php echo $b['appointment_id']; ?>"
class="btn btn-dark btn-sm"
>

Invoice

</a>

</td>

</tr>

<?php } ?>

</tbody>

</table>

</div>

</div></div></body></html>