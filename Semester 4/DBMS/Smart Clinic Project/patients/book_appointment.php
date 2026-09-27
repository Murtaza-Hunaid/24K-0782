<?php
session_start();
include("../db.php");
include("../layout.php");

if ($_SESSION['role'] != 'patient') {
    header("Location: login.php");
    exit();
}

$message = "";

/* =========================
   GET PATIENT ID
========================= */
$user_id = $_SESSION['user_id'];

$stmt2 = $conn->prepare("SELECT patient_id FROM patients WHERE user_id = ?");
$stmt2->bind_param("i", $user_id);
$stmt2->execute();
$res2 = $stmt2->get_result();

if ($res2->num_rows == 1) {
    $patient_id = $res2->fetch_assoc()['patient_id'];
} else {
    die("Patient not found");
}

/* =========================
   BOOK APPOINTMENT
========================= */
if (isset($_POST['book'])) {

    $doctor_id = $_POST['doctor_id'];
    $date = $_POST['date'];
    $time = $_POST['time'];
    $reason = $_POST['reason'];

    $payment_method = $_POST['payment_method'];

    if ($payment_method == "online") {

        $payment_status = "paid";
        $status = "confirmed";

    } else {

        $payment_status = "unpaid";
        $status = "pending";
    }


    // CHECK SLOT ALREADY BOOKED
    $check = $conn->prepare("
        SELECT * FROM appointments 
        WHERE doctor_id = ? 
        AND appointment_date = ? 
        AND appointment_time = ?
    ");
    $check->bind_param("iss", $doctor_id, $date, $time);
    $check->execute();

    if ($check->get_result()->num_rows > 0) {
        $message = "<div class='alert alert-danger'>Slot already booked!</div>";
    } else {

        $stmt = $conn->prepare("
            INSERT INTO appointments 
            (
                patient_id,
                doctor_id,
                appointment_date,
                appointment_time,
                reason,
                status,
                payment_method,
                payment_status,
                payment_date
            )
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, NOW())
        ");

        $stmt->bind_param(
            "iissssss",
            $patient_id,
            $doctor_id,
            $date,
            $time,
            $reason,
            $status,
            $payment_method,
            $payment_status
        );
        if ($stmt->execute()) {
            $appointment_id = $stmt->insert_id;

            /*
            |--------------------------------------------------------------------------
            | BILLING
            |--------------------------------------------------------------------------
            */

            $amount = 2500; // fixed fee for now

            $stmtBill = $conn->prepare("
                INSERT INTO billing
                (
                    appointment_id,
                    patient_id,
                    amount,
                    payment_method,
                    payment_status
                )
                VALUES (?, ?, ?, ?, ?)
            ");

            $stmtBill->bind_param(
                "iidss",
                $appointment_id,
                $patient_id,
                $amount,
                $payment_method,
                $payment_status
            );

            if ($stmtBill->execute()) {
                $message = "<div class='alert alert-success'>Appointment booked successfully!</div>";
            } else {
                $message = "<div class='alert alert-danger'>Appointment created, but invoice generation failed: " . $stmtBill->error . "</div>";
            }
        } else {
            $message = "<div class='alert alert-danger'>Error: " . $stmt->error . "</div>";
        }
    }
}
?>

<!-- =========================
     UI
========================= -->
<div class="row justify-content-center">
<div class="col-lg-8">

<div class="card p-4 shadow" style="border-radius: 15px;">

    <h3 class="mb-3 text-center">
        <i class="fas fa-calendar-plus text-primary"></i>
        Book Appointment
    </h3>

    <?php echo $message; ?>

    <form method="POST">

        <!-- DOCTOR -->
        <label class="form-label">Select Doctor</label>
        <select name="doctor_id" id="doctor" class="form-control mb-3" required>
            <option value="">-- Choose Doctor --</option>
            <?php
            $docs = $conn->query("SELECT * FROM doctors");
            while ($d = $docs->fetch_assoc()) {
                echo "<option value='{$d['doctor_id']}'>
                        Dr. {$d['first_name']} ({$d['specialization']})
                      </option>";
            }
            ?>
        </select>

        <!-- DATE -->
        <label class="form-label">Select Date</label>
        <input type="text" name="date" id="date" class="form-control mb-3" placeholder="Select date" required>

        <!-- TIME SLOTS (DYNAMIC) -->
        <label class="form-label">Available Slots</label>
        <select name="time" id="slots" class="form-control mb-3" required>
            <option value="">Select slot</option>
        </select>

        <!-- REASON -->
        <label class="form-label">Reason</label>
        <textarea name="reason" class="form-control mb-3" required></textarea>

        <!-- PAYMENT METHOD -->
        <label class="form-label mt-3">
            Payment Method
        </label>

        <select
            name="payment_method"
            id="payment_method"
            class="form-control mb-3"
            required
        >
            <option value="">Select Payment Method</option>

            <option value="cash">
                Pay By Cash
            </option>

            <option value="online">
                Pay Online
            </option>

        </select>

        <!-- QR SECTION -->
        <div
            id="qrSection"
            style="display:none;"
            class="text-center mb-4"
        >

            <h5 class="mb-3">
                Scan QR to Pay
            </h5>

            <img
                src="../assets/qrcode.png"
                width="250"
                class="img-fluid border rounded shadow"
            >

            <p class="mt-3 text-muted">
                After scanning, click confirm payment.
            </p>

        </div>

        <button
            class="btn btn-primary w-100"
            name="book"
        >
            Book Appointment
        </button>

    </form>

</div>

</div>
</div>

<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/flatpickr/dist/flatpickr.min.css">

<!-- =========================
     JAVASCRIPT (SLOT LOADER)
========================= -->
<script src="https://cdn.jsdelivr.net/npm/flatpickr"></script>
<script>
flatpickr("#date", {
    minDate: "today",
    dateFormat: "Y-m-d"
});

document.getElementById("doctor").addEventListener("change", loadSlots);
document.getElementById("date").addEventListener("change", loadSlots);

function loadSlots() {

    let doctor = document.getElementById("doctor").value;
    let date = document.getElementById("date").value;

    if (!doctor || !date) return;

    fetch("../Doctor/get_slots.php?doctor_id=" + doctor + "&date=" + date)
    .then(res => res.json())
    .then(data => {

        let slotBox = document.getElementById("slots");
        slotBox.innerHTML = "<option value=''>Select slot</option>";

        data.forEach(time => {
            slotBox.innerHTML += `<option value="${time}">${time}</option>`;
        });

    });
}

let paymentSelect =
document.getElementById("payment_method");

paymentSelect.addEventListener("change", function() {

    let qr =
    document.getElementById("qrSection");

    if (this.value === "online") {
        qr.style.display = "block";
    }
    else {
        qr.style.display = "none";
    }

});


</script>

</div></div></body></html>