# ROBO-RUGBY-7-S
echo "# ROBO-RUGBY-7-S" >> README.md**Disclamer- This code is being used for Abu-Robocon-2020 Asia Pacific Robotics Contest by the team Sardar Vallabhai National Institute of Technology, Surat.
	     This code is not to be shared on any public platform (open-source), please respect the privacy of this document.

This file consists of Arduino code for both the robots (Pass Robot and Try Robot)  desined by the Team.
The 1] Pass Robot and 2] Try Robot Cosist of a Two Layer System.
Two-Layer - Upper Control and Lower Control 

A]Upper Control - 
It consists of an Arduino Mega(ATmega32). 
The major components included in Upper Control are:
-Basic Functions
-Communication (Easy_Transfer Libarary)
-Curve functins
-Drive control of the Robot
-Mpu6050
-PID Control 
-Shagai Control(for effective Throwing of Shagai)
-Line Following(LSA08)
-PS2 Controller

B]Lower Control-
It consists of an Arduino Due(ARM Controller)
The major components included in Lower Control Are:
-PID Control
-Drive Initialisation 
-Encoder Interrupts
-Inverse Kinematic Model

3]It also consists Python files used for real time ploting of the position of the robot and python scripts for testing PathPlanning Algorithm.
 
4]The file consists of PS3 codes for Manual control of the robot.