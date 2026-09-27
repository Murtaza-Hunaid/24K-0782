<?php
session_start();
include("../db.php");

if ($_SESSION['role'] != 'doctor') {
    header("Location: login.php");
    exit();
}

$user_id = $_SESSION['user_id'];

// get doctor_id
$stmt = $conn->prepare("SELECT doctor_id FROM doctors WHERE user_id = ?");
$stmt->bind_param("i", $user_id);
$stmt->execute();
$res = $stmt->get_result();
$doctor_id = $res->fetch_assoc()['doctor_id'];

// fetch prescriptions
$query = "
SELECT 
    pr.prescription_id,
    pr.medicine_name,
    pr.dosage,
    pr.updated_at,
    p.first_name,
    p.last_name
FROM prescriptions pr
JOIN medical_records mr ON pr.record_id = mr.record_id
JOIN patients p ON mr.patient_id = p.patient_id
WHERE mr.doctor_id = ?
ORDER BY pr.updated_at DESC
";

$stmt2 = $conn->prepare($query);
$stmt2->bind_param("i", $doctor_id);
$stmt2->execute();
$result = $stmt2->get_result();

include("../layout.php");
?>

<h2>Prescriptions</h2>

<table class="table table-bordered">
    <thead class="table-dark">
        <tr>
            <th>Patient</th>
            <th>Medicine</th>
            <th>Dosage</th>
            <th>Last Updated</th>
            <th>Action</th>
        </tr>
    </thead>

    <tbody>
        <?php while($row = $result->fetch_assoc()) { ?>
        <tr>
            <td><?= $row['first_name'] . " " . $row['last_name'] ?></td>
            <td><?= $row['medicine_name'] ?></td>
            <td><?= $row['dosage'] ?></td>
            <td><?= $row['updated_at'] ?></td>
            <td>
                <a href="edit_prescription_page.php?id=<?= $row['prescription_id'] ?>" 
                   class="btn btn-sm btn-warning">
                   Edit
                </a>
            </td>
        </tr>
        <?php } ?>
    </tbody>
</table>

</div></div></body></html>