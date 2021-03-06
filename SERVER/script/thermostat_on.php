<?php

  include "../class/Config.class.php";
  include "../class/Database.class.php";

  $database = new Database();
  $database->connect();

  if (!isset($_POST['thermopass']) || ($_POST['thermopass'] != Config::$passwd && $_SERVER['REMOTE_ADDR'] != Config::$ipaddress)) {print Config::$wrongpasswd; exit(); };
  if (!isset($_POST['max'])) $max = Config::$defaultmax; else $max = $_POST['max'];
  $min = $max - Config::$hysteresis;

  $max = mysqli_real_escape_string($database->conn, $max);
  $min = mysqli_real_escape_string($database->conn, $min);
  
  //Import
  $sql = "
    START TRANSACTION;
    DELETE FROM program WHERE production = 0;
    CREATE TEMPORARY TABLE temp_import SELECT * FROM program WHERE production = 1;
    UPDATE temp_import SET id = NULL, timestamp = NULL, production = 0;
    INSERT INTO program SELECT * FROM temp_import;
    DROP TEMPORARY TABLE IF EXISTS temp_import;
    COMMIT;
  ";
  //Change  
  $sql.= "UPDATE program SET max=$max, min=$min, priority = 0 WHERE production = 0 AND title='".Config::$poweron."';";
  $sql.= "UPDATE program SET priority = 6 WHERE production = 0 AND title='".Config::$poweroff."';";
  //Export
  $sql.= "
    START TRANSACTION;
    DELETE FROM program WHERE production = 1;
    CREATE TEMPORARY TABLE temp_export SELECT * FROM program WHERE production = 0;
    UPDATE temp_export SET id = NULL, timestamp = NULL, production = 1;
    INSERT INTO program SELECT * FROM temp_export;
    DROP TEMPORARY TABLE IF EXISTS temp_export;
    COMMIT;
  ";
   
  $database->conn->multi_query($sql);
	$database->conn->close();   