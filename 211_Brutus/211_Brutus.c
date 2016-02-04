#pragma config(Sensor, in1,    TurnGyro,       sensorGyro)
#pragma config(Sensor, dgtl1,  ledSpeed,       sensorDigitalIn)
#pragma config(Sensor, dgtl2,  ledFull,        sensorDigitalIn)
#pragma config(Sensor, dgtl3,  ledHalf,        sensorDigitalIn)
#pragma config(Sensor, dgtl7,  LeftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  RightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl11, ShooterEncoder, sensorQuadEncoder)
#pragma config(Motor,  port1,           Intake,        tmotorVex393TurboSpeed_HBridge, openLoop)
#pragma config(Motor,  port2,           LeftShooter1,  tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           LeftShooter2,  tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           LeftShooter3,  tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           LeftDrive,     tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           RightDrive,    tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           RightShooter1, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           RightShooter2, tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           RightShooter3, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port10,          Index,         tmotorVex393HighSpeed_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

#include "PID_Library.c"

void pre_auton()
{
	bStopTasksBetweenModes = true;
}

task autonomous()
{
	startTask( pid );
	targetRPM = full;

	wait1Msec(2500);

	while(true){
		motor[Index] = 127;
		motor[Intake] = 127;
		wait1Msec(400);
		motor[Index] = 0;
		motor[Intake] = 0;
		wait1Msec(1000);
	}
}

task usercontrol()
{
	// Start the flywheel control task
	startTask( pid );
	targetRPM = 0;

	// Main user control loop
	while(1)
	{
		/////////SHOOTER/////////
		if (vexRT[Btn8UXmtr2]) targetRPM = full;
		else if (vexRT[Btn8LXmtr2])targetRPM = 1000;
		else if (vexRT[Btn8RXmtr2])targetRPM = half;
		else if (vexRT[Btn8DXmtr2])targetRPM = 0;

		if (vexRT[Btn6UXmtr2]) shooter(vexRT[Ch2Xmtr2]);

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

		///////// INTAKE ////////
		if(vexRT[Btn6U])motor[Intake]=127;
		else if(vexRT[Btn6D])motor[Intake]=-127;
		else motor[Intake]=0;

		///////// INDEXER ////////
		if(vexRT[Btn5UXmtr2]) motor[Index] = 127;
		else if(vexRT[Btn5DXmtr2]) motor[Index] = -127;
		else motor[Index] = 0;

		////////AUTOFEED/////////

		///////////LED///////////
			if (vexRT[Btn8UXmtr2]){
				if (currentRPM >= targetRPM)
					SensorValue[ledSpeed]=1;
				else if (currentRPM == 0)
					SensorValue[ledSpeed]=0;
				else
					SensorValue[ledSpeed]=0;
			}

			//speed leds
			if (targetRPM == full)
				SensorValue[ledFull]=1;
			else if(targetRPM == half)
				SensorValue[ledHalf]=1;
			else
				SensorValue[ledFull]=0;
				SensorValue[ledHalf]=0;


		// Don't hog the cpu :)
		wait1Msec(10);
	}
}
