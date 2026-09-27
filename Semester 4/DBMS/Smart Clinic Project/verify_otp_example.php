<?php

session_start();
include("db.example.php");

$error = "";
$success = "";

if(isset($_POST['verify'])) {

    $otp = $_POST['otp'];
    $email = $_SESSION['email'];
    $stmt = $conn->prepare("SELECT * FROM users WHERE email=? AND otp_code=?");
    $stmt->bind_param("ss", $email, $otp);
    $stmt->execute();
    $result = $stmt->get_result();
    if($result->num_rows > 0) {
        $update = $conn->prepare("UPDATE users SET status='active', otp_code='' WHERE email=?");
        $update->bind_param("s", $email);
        $update->execute();
        $success = "OTP verified successfully! Redirecting to login...";
        // Redirect after showing message
        echo "<script>
            setTimeout(function() {
                window.location.href = 'login.php';
            }, 3000); // 3 seconds delay
        </script>";
    } else {

        $error = "Invalid OTP.";
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>SmartClinic - Verify OTP</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">
    <link href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css" rel="stylesheet">
    <style>
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            display: flex;
            align-items: center;
            justify-content: center;
            margin: 0;
        }
        .verify-card {
            background: rgba(255, 255, 255, 0.95);
            backdrop-filter: blur(10px);
            border-radius: 20px;
            box-shadow: 0 15px 35px rgba(0, 0, 0, 0.1);
            padding: 40px;
            max-width: 400px;
            width: 100%;
        }
        .verify-header {
            text-align: center;
            margin-bottom: 30px;
        }
        .verify-header i {
            font-size: 3rem;
            color: #667eea;
            margin-bottom: 15px;
        }
        .form-floating {
            margin-bottom: 20px;
        }
        .form-control {
            border-radius: 10px;
            border: 1px solid #ddd;
            padding: 12px 15px;
        }
        .form-control:focus {
            border-color: #667eea;
            box-shadow: 0 0 0 0.2rem rgba(102, 126, 234, 0.25);
        }
        .btn-verify {
            background: linear-gradient(90deg, #667eea 0%, #764ba2 100%);
            border: none;
            border-radius: 10px;
            padding: 12px;
            font-weight: 600;
            transition: transform 0.3s ease;
            width: 100%;
        }
        .btn-verify:hover {
            transform: translateY(-2px);
            box-shadow: 0 5px 15px rgba(0, 0, 0, 0.2);
        }
        .error-message {
            background: #fee;
            color: #c33;
            border: 1px solid #fcc;
            border-radius: 8px;
            padding: 10px;
            margin-bottom: 20px;
            text-align: center;
        }
        .success-message {
            background: #efe;
            color: #363;
            border: 1px solid #cfc;
            border-radius: 8px;
            padding: 10px;
            margin-bottom: 20px;
            text-align: center;
        }
    </style>
</head>
<body>

<div class="container">
    <div class="row justify-content-center">
        <div class="col-md-6 col-lg-4">
            <div class="verify-card">
                <div class="verify-header">
                    <i class="fas fa-shield-alt"></i>
                    <h2 class="h4 mb-0">Verify Your Account</h2>
                    <p class="text-muted mt-2">Enter the OTP sent to your email</p>
                </div>

                <?php if (!empty($error)) { ?>
                    <div class="error-message">
                        <i class="fas fa-exclamation-triangle me-2"></i>
                        <?php echo $error; ?>
                    </div>
                <?php } ?>

                <?php if (!empty($success)) { ?>
                    <div class="success-message">
                        <i class="fas fa-check-circle me-2"></i>
                        <?php echo $success; ?>
                    </div>
                <?php } ?>

                <form method="POST" action="verify_otp.php">
                    <div class="form-floating">
                        <input type="text" class="form-control" id="otp" name="otp" placeholder="Enter OTP" required maxlength="6">
                        <label for="otp">OTP Code</label>
                    </div>

                    <button type="submit" name="verify" class="btn btn-primary btn-verify">
                        <i class="fas fa-check me-2"></i>Verify Account
                    </button>
                </form>

                <div class="text-center mt-3">
                    <a href="login.php" class="text-muted">Back to Login</a>
                </div>
            </div>
        </div>
    </div>
</div>

<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>