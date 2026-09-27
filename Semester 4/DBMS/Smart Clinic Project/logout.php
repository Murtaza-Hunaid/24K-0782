<?php
/**
 * Logout Handler
 * Destroys user session and redirects to login page
 */

session_start();        // Start session if not already started
session_destroy();      // Destroy all session data
header("Location: login.php");  // Redirect to login page
exit();                 // Ensure no further code execution
?>