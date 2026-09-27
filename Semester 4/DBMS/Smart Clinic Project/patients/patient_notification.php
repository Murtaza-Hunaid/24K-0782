<?php
session_start();
include("../db.php");

$patient_id = $_SESSION['patient_id'];

$result = $conn->query("
    SELECT * FROM notifications 
    WHERE patient_id = $patient_id OR patient_id IS NULL
    ORDER BY created_at DESC
");

include("../layout.php");
?>

<h2>Notifications</h2>

<?php while($row = $result->fetch_assoc()) { ?>

<div class="alert alert-info">
    <?= $row['message'] ?>
    <small class="text-muted d-block">
        <?= $row['created_at'] ?>
    </small>
</div>

<?php } ?>

</div></div></body></html>