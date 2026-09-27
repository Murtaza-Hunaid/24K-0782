<?php
/**
 * SmartClinic Forgot Password Page
 * Handles password reset with email verification
 */

session_start();
include("db.example.php");
require 'vendor/autoload.php';

use PHPMailer\PHPMailer\PHPMailer;
use PHPMailer\PHPMailer\Exception;

$error = "";
$success = "";
$step = isset($_GET['step']) ? $_GET['step'] : 1;

// Step 1: Enter email
if ($step == 1 && isset($_POST['send_otp'])) {
    $email = $_POST['email'];

    // Check if email exists
    $stmt = $conn->prepare("SELECT * FROM users WHERE email = ?");
    $stmt->bind_param("s", $email);
    $stmt->execute();
    $result = $stmt->get_result();

    if ($result->num_rows > 0) {
        // Generate OTP
        $otp = rand(100000, 999999);

        // Store OTP in database
        $update = $conn->prepare("UPDATE users SET otp_code = ? WHERE email = ?");
        $update->bind_param("ss", $otp, $email);
        $update->execute();

        // Store email in session
        $_SESSION['reset_email'] = $email;

        // Send email
        $mail = new PHPMailer(true);
        try {
            $mail->isSMTP();
            $mail->Host = 'YOUR SMTP_HOST';
            $mail->SMTPAuth = true;

            $mail->Username = 'YOUR SMTP_USERNAME';
            $mail->Password = 'YOUR SMTP_PASSWORD';

            $mail->Port = 2525;
            $mail->setFrom('YOUR EMAIL', 'YOUR DATABASE NAME');
            $mail->addAddress($email);

            $mail->isHTML(true);
            $mail->Subject = 'Password Reset OTP - SmartClinic';
            $mail->Body = "Your OTP for password reset is: <b>$otp</b><br>This code will expire in 10 minutes.";

            $mail->send();
            $success = "OTP sent to your email. Please check your inbox.";
            $step = 2;
        } catch (Exception $e) {
            $error = "Failed to send email. Please try again.";
        }
    } else {
        $error = "Email not found in our records.";
    }
}

// Step 2: Verify OTP
if ($step == 2 && isset($_POST['verify_otp'])) {
    $otp = $_POST['otp'];
    $email = $_SESSION['reset_email'];

    $stmt = $conn->prepare("SELECT * FROM users WHERE email = ? AND otp_code = ?");
    $stmt->bind_param("ss", $email, $otp);
    $stmt->execute();
    $result = $stmt->get_result();

    if ($result->num_rows > 0) {
        $success = "OTP verified successfully. Please set your new password.";
        $step = 3;
    } else {
        $error = "Invalid OTP.";
    }
}

// Step 3: Reset password
if ($step == 3 && isset($_POST['reset_password'])) {
    $password = $_POST['password'];
    $confirm_password = $_POST['confirm_password'];
    $email = $_SESSION['reset_email'];

    if ($password === $confirm_password) {
        if (strlen($password) >= 6) {
            $hashed_password = password_hash($password, PASSWORD_DEFAULT);

            $update = $conn->prepare("UPDATE users SET password = ?, otp_code = '' WHERE email = ?");
            $update->bind_param("ss", $hashed_password, $email);
            $update->execute();

            unset($_SESSION['reset_email']);
            $success = "Password reset successfully! Redirecting to login...";

            echo "<script>
                setTimeout(function() {
                    window.location.href = 'login.php';
                }, 3000);
            </script>";
        } else {
            $error = "Password must be at least 6 characters long.";
        }
    } else {
        $error = "Passwords do not match.";
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>SmartClinic - Forgot Password</title>
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
        .reset-card {
            background: rgba(255, 255, 255, 0.95);
            backdrop-filter: blur(10px);
            border-radius: 20px;
            box-shadow: 0 15px 35px rgba(0, 0, 0, 0.1);
            padding: 40px;
            max-width: 400px;
            width: 100%;
        }
        .reset-header {
            text-align: center;
            margin-bottom: 30px;
        }
        .reset-header i {
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
        .btn-reset {
            background: linear-gradient(90deg, #667eea 0%, #764ba2 100%);
            border: none;
            border-radius: 10px;
            padding: 12px;
            font-weight: 600;
            transition: transform 0.3s ease;
            width: 100%;
        }
        .btn-reset:hover {
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
            <div class="reset-card">
                <div class="reset-header">
                    <i class="fas fa-key"></i>
                    <h2 class="h4 mb-0">Reset Password</h2>
                    <p class="text-muted mt-2">
                        <?php
                        if ($step == 1) echo "Enter your email to receive reset code";
                        elseif ($step == 2) echo "Enter the OTP sent to your email";
                        elseif ($step == 3) echo "Set your new password";
                        ?>
                    </p>
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

                <?php if ($step == 1) { ?>
                    <form method="POST" action="forget_pass.php?step=1">
                        <div class="form-floating">
                            <input type="email" class="form-control" id="email" name="email" placeholder="Email" required>
                            <label for="email">
                                <i class="fas fa-envelope me-2"></i>Email Address
                            </label>
                        </div>

                        <button type="submit" name="send_otp" class="btn btn-primary btn-reset">
                            <i class="fas fa-paper-plane me-2"></i>Send Reset Code
                        </button>
                    </form>
                <?php } elseif ($step == 2) { ?>
                    <form method="POST" action="forget_pass.php?step=2">
                        <div class="form-floating">
                            <input type="text" class="form-control" id="otp" name="otp" placeholder="OTP" required maxlength="6">
                            <label for="otp">
                                <i class="fas fa-shield-alt me-2"></i>OTP Code
                            </label>
                        </div>

                        <button type="submit" name="verify_otp" class="btn btn-primary btn-reset">
                            <i class="fas fa-check me-2"></i>Verify OTP
                        </button>
                    </form>
                <?php } elseif ($step == 3) { ?>
                    <form method="POST" action="forget_pass.php?step=3">
                        <div class="form-floating">
                            <input type="password" class="form-control" id="password" name="password" placeholder="New Password" required minlength="6">
                            <label for="password">
                                <i class="fas fa-lock me-2"></i>New Password
                            </label>
                        </div>

                        <div class="form-floating">
                            <input type="password" class="form-control" id="confirm_password" name="confirm_password" placeholder="Confirm Password" required minlength="6">
                            <label for="confirm_password">
                                <i class="fas fa-lock me-2"></i>Confirm Password
                            </label>
                        </div>

                        <button type="submit" name="reset_password" class="btn btn-primary btn-reset">
                            <i class="fas fa-save me-2"></i>Reset Password
                        </button>
                    </form>
                <?php } ?>

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