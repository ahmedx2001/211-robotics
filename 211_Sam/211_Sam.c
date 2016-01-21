#pragma config(Sensor, in1,    TurnGyro,       sensorGyro)
#pragma config(Sensor, dgtl7,  LeftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  RightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl11, ShooterEncoder, sensorQuadEncoder)
#pragma config(Motor,  port1,           Intake,        tmotorVex393TurboSpeed_HBridge, openLoop)
#pragma config(Motor,  port2,           LeftShooter1,  tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           LeftShooter2,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           LeftShooter3,  tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           LeftDrive,     tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           RightDrive,    tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           RightShooter1, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           RightShooter2, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           RightShooter3, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          Index,         tmotorVex393HighSpeed_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

#include "TBH_Library.c"


void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

task autonomous()
{
	// .....................................................................................
	// Insert user code here.
	// .....................................................................................

	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

task usercontrol()
{

	// Start the flywheel control task
	startTask( FwControlTask );

	bool IntakeButton = false;
	int IntakeSpeed = 0;
	int AutoIndex = 0;
	int AutoIntake = 0;


	// Main user control loop
	while(1)
	{
		// Different speeds set by buttons
		if( vexRT[ Btn8R ] == 1 )
			FwVelocitySet( 170, 0.47 );
		if( vexRT[ Btn8U ] == 1 )
			FwVelocitySet( 100, 0.47 );
		if( vexRT[ Btn8L ] == 1 )
			FwVelocitySet( 128, 0.39 ); // Full court
		if( vexRT[ Btn8D ] == 1 ){
			FwVelocitySet( 00, 0 );
			AutoIndex = 0;
			AutoIntake = 0;
		}

		//////// DRIVE ////////
		if(abs(vexRT[Ch3]) > 10 || abs(vexRT[Ch4]) > 10 ||
			abs(vexRT[Ch1]) > 10 || abs(vexRT[Ch2]) > 10){
			motor[LeftDrive]  = ((vexRT[Ch2] + vexRT[Ch1])/2 - (vexRT[Ch3] - vexRT[Ch4]));
			motor[RightDrive]   = ((vexRT[Ch2] - vexRT[Ch1])/2 - (vexRT[Ch3] + vexRT[Ch4]));
		}
		else{
			motor[LeftDrive]  = 0;
			motor[RightDrive]  = 0;
		}

		/////// INTAKE ////////
		motor[Intake] = IntakeSpeed+AutoIntake;
		if(vexRT[Btn6U] == 1){
			IntakeSpeed = 127;
		}
		else if(vexRT[Btn6D] == 1){
			if (IntakeSpeed == 127){
				IntakeButton = true;
				AutoIntake = 0;
				IntakeSpeed = 0;
			}
			else {
				if (IntakeButton == false){
					IntakeSpeed = -127;
				}
			}
		}
		else{
			IntakeButton = false;
			if (IntakeSpeed == -127){
				IntakeSpeed = 0;
			}
		}

		/////// INDEXER ////////
		if(vexRT[Btn5U] == 1){
			motor[Index]   = 127;
		}
		else if(vexRT[Btn5D] == 1){
			motor[Index] = -127;
			AutoIntake = 0;
		}
		else {
			motor[Index] = AutoIndex;
		}

		///////////// AUTO FEED CODE /////////////////
		if (vexRT[Btn7U] == 1){
			AutoIndex = 127;
			AutoIntake = 127;
		}//AutoFeed

		// Don't hog the cpu :)
		wait1Msec(10);
	}
}
