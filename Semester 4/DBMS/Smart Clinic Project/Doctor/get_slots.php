<?php

include("../db.php");

header('Content-Type: application/json');

$doctor_id = $_GET['doctor_id'];
$date = $_GET['date'];

$day = date('l', strtotime($date));

/* =========================
   CHECK DOCTOR LEAVE
========================= */

$leave = $conn->prepare("
    SELECT * FROM doctor_leaves
    WHERE doctor_id = ? AND leave_date = ?
");

$leave->bind_param("is", $doctor_id, $date);
$leave->execute();

if ($leave->get_result()->num_rows > 0) {
    echo json_encode([]);
    exit();
}

/* =========================
   GET SCHEDULE
========================= */

$stmt = $conn->prepare("
    SELECT * FROM doctor_schedule
    WHERE doctor_id = ? AND day_of_week = ?
");

$stmt->bind_param("is", $doctor_id, $day);
$stmt->execute();

$schedule = $stmt->get_result()->fetch_assoc();

if (!$schedule) {
    echo json_encode([]);
    exit();
}

/* =========================
   TIMES
========================= */

$start = strtotime($schedule['start_time']);
$end = strtotime($schedule['end_time']);

$break_start = strtotime($schedule['break_start']);
$break_end = strtotime($schedule['break_end']);

$duration = $schedule['slot_duration'] * 60;

/* =========================
   GET BOOKED SLOTS
========================= */

$stmt2 = $conn->prepare("
    SELECT appointment_time
    FROM appointments
    WHERE doctor_id = ?
    AND appointment_date = ?
    AND status != 'cancelled'
");

$stmt2->bind_param("is", $doctor_id, $date);
$stmt2->execute();

$res = $stmt2->get_result();

$booked = [];

while ($row = $res->fetch_assoc()) {
    $booked[] = $row['appointment_time'];
}

/* =========================
   GENERATE SLOTS
========================= */

$slots = [];

for ($time = $start; $time < $end; $time += $duration) {

    // skip break time
    if ($time >= $break_start && $time < $break_end) {
        continue;
    }

    $slot = date("H:i:s", $time);

    // skip booked slot
    if (in_array($slot, $booked)) {
        continue;
    }

    $slots[] = $slot;
}

echo json_encode($slots);