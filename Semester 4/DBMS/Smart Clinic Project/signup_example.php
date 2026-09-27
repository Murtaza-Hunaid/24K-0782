<?php
/**
 * SmartClinic Signup Page
 * Registers new users and keeps the login style consistent
 */

use PHPMailer\PHPMailer\PHPMailer;
use PHPMailer\PHPMailer\Exception;

require 'vendor/autoload.php';

session_start();
include("db.example.php");

$opt_str = str_shuffle("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
$otp = substr($opt_str, 0, 5);

$act_str = rand(100000, 999999);
$activation_code = str_shuffle("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ".$act_str);



$error = "";
$success = "";

if (isset($_POST['signup'])) {
    $username = trim($_POST['username'] ?? '');
    $email = trim($_POST['email'] ?? '');
    $password = $_POST['password'] ?? '';
    $confirm_password = $_POST['confirm_password'] ?? '';


    if (empty($username) || empty($email) || empty($password) || empty($confirm_password)) {
        $error = "All fields are required.";
    } elseif (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
        $error = "Please enter a valid email address.";
    } elseif ($password !== $confirm_password) {
        $error = "Password and confirm password do not match.";
    } elseif (strlen($password) < 6) {
        $error = "Password must be at least 6 characters.";
    } else {
        $stmt = $conn->prepare("SELECT * FROM users WHERE username = ? OR email = ?");
        $stmt->bind_param("ss", $username, $email);
        $stmt->execute();
        $result = $stmt->get_result();

        if ($result->num_rows > 0) {
            $error = "Username or email already exists.";
        } else {
            $hashedPassword = password_hash($password, PASSWORD_DEFAULT);
            $role = "patient";
            $otp = rand(10000, 99999);
            $activation_code = md5(rand());
            $status = "inactive";

            $stmt = $conn->prepare("INSERT INTO users 
                (username, email, password, role, otp_code, activation_code, status) 
                VALUES (?, ?, ?, ?, ?, ?, ?)");
            $stmt->bind_param(
                "sssssss",
                $username,
                $email,
                $hashedPassword,
                $role,
                $otp,
                $activation_code,
                $status
            );

            if ($stmt->execute()) {
                $mail = new PHPMailer(true);
                try {
                    $mail->isSMTP();
                    $mail->Host = 'YOUR HOST NAME';
                    $mail->SMTPAuth = true;
                    $mail->Port = "YOUR PORT NUMBER";
                    $mail->Username = 'YOUR USERNAME';

                    $mail->Password = 'YOUR PASSWORD';
                    $mail->SMTPSecure = 'tls';
                    $mail->Port       = "YOUR PORT NUMBER";
                    $mail->setFrom('YOUR EMAIL', 'YOUR DATABASE NAME');
                    $mail->addAddress($email);
                    $mail->isHTML(true);
                    $mail->Subject = 'DATABASE OTP Verification';
                    $mail->Body = "
                        <h2>Email Verification</h2>
                        <p>Your OTP code is:</p>
                        <h1>$otp</h1>
                    ";
                    $mail->send();
                    $_SESSION['email'] = $email;
                    header("Location: verify_otp.php");
                    exit();

                } catch (Exception $e) {
                    $error = "Email could not be sent.";
                }
            } else {
                $error = "Unable to create account. Please try again.";
            }
        }
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>SmartClinic Signup</title>
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
        .login-card {
            background: rgba(255, 255, 255, 0.95);
            backdrop-filter: blur(10px);
            border-radius: 20px;
            box-shadow: 0 15px 35px rgba(0, 0, 0, 0.1);
            padding: 40px;
            max-width: 420px;
            width: 100%;
        }
        .login-header {
            text-align: center;
            margin-bottom: 30px;
        }
        .login-header i {
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
        .btn-login {
            background: linear-gradient(90deg, #667eea 0%, #764ba2 100%);
            border: none;
            border-radius: 10px;
            padding: 12px;
            font-weight: 600;
            transition: transform 0.3s ease;
        }
        .btn-login:hover {
            transform: translateY(-2px);
            box-shadow: 0 5px 15px rgba(0, 0, 0, 0.2);
        }
        .message-box {
            border-radius: 12px;
            padding: 14px 18px;
            margin-bottom: 20px;
            text-align: center;
        }
        .message-box.error {
            background: #fee;
            color: #c33;
            border: 1px solid #fcc;
        }
        .message-box.success {
            background: #e9f8ec;
            color: #2f6b2a;
            border: 1px solid #c8e6c9;
        }
    </style>
</head>
<body>

<div class="container">
    <div class="row justify-content-center">
        <div class="col-md-6 col-lg-5">
            <div class="login-card">
                <div class="login-header">
                    <i class="fas fa-user-plus"></i>
                    <h2 class="h4 mb-0">SmartClinic Signup</h2>
                    <p class="text-muted mt-2">Create your account to access the patient portal</p>
                </div>

                <?php if (!empty($error)) { ?>
                    <div class="message-box error">
                        <i class="fas fa-exclamation-triangle me-2"></i>
                        <?php echo $error; ?>
                    </div>
                <?php } elseif (!empty($success)) { ?>
                    <div class="message-box success">
                        <i class="fas fa-check-circle me-2"></i>
                        <?php echo $success; ?>
                    </div>
                <?php } ?>

                <form method="POST" action="signup.php">
                    <div class="form-floating">
                        <input type="text" class="form-control" id="username" name="username" placeholder="Username" value="<?php echo isset($username) ? htmlspecialchars($username) : ''; ?>" required>
                        <label for="username">
                            <i class="fas fa-user me-2"></i>Username
                        </label>
                    </div>

                    <div class="form-floating">
                        <input type="email" class="form-control" id="email" name="email" placeholder="Email" value="<?php echo isset($email) ? htmlspecialchars($email) : ''; ?>" required>
                        <label for="email">
                            <i class="fas fa-envelope me-2"></i>Email
                        </label>
                    </div>

                    <div class="form-floating">
                        <input type="password" class="form-control" id="password" name="password" placeholder="Password" required>
                        <label for="password">
                            <i class="fas fa-lock me-2"></i>Password
                        </label>
                    </div>

                    <div class="form-floating mb-4">
                        <input type="password" class="form-control" id="confirm_password" name="confirm_password" placeholder="Confirm Password" required>
                        <label for="confirm_password">
                            <i class="fas fa-lock me-2"></i>Confirm Password
                        </label>
                    </div>

                    <button type="submit" name="signup" class="btn btn-primary btn-login w-100">
                        <i class="fas fa-user-check me-2"></i>Sign Up
                    </button>
                </form>

                <p class="text-center text-muted mt-4 mb-0">Already have an account? <a href="login.php">Login here</a></p>
            </div>
        </div>
    </div>
</div>

<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>
