#pragma config(Sensor, in1,    TurnGyro,       sensorGyro)
#pragma config(Sensor, in2,    BowPot,         sensorGyro)
#pragma config(Sensor, dgtl1,  TensionEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  Ramps,          sensorDigitalOut)
#pragma config(Sensor, dgtl4,  LiftLeft,       sensorDigitalOut)
#pragma config(Sensor, dgtl5,  LiftRight,      sensorDigitalOut)
#pragma config(Sensor, dgtl6,  RightDrive,     sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  LeftDrive,      sensorQuadEncoder)
#pragma config(Sensor, dgtl10, BaseLock,       sensorDigitalOut)
#pragma config(Sensor, dgtl11, LED,            sensorDigitalOut)
#pragma config(Motor,  port1,           Tension,       tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           Left1,         tmotorVex393TurboSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port3,           Left2,         tmotorVex393TurboSpeed_MC29, openLoop, reversed, driveLeft)
#pragma config(Motor,  port4,           Left3,         tmotorVex393TurboSpeed_MC29, openLoop, driveLeft, encoderPort, dgtl6)
#pragma config(Motor,  port5,           Right1,        tmotorVex393TurboSpeed_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port6,           Right2,        tmotorVex393TurboSpeed_MC29, openLoop, driveRight)
#pragma config(Motor,  port7,           Right3,        tmotorVex393TurboSpeed_MC29, openLoop, reversed, driveRight, encoderPort, dgtl8)
#pragma config(Motor,  port8,           BowLeft,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           BowRight,      tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          Intake,        tmotorVex393HighSpeed_HBridge, openLoop, reversed)



#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "GlobalVariables.c"
#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "GyroLib.c"
#include "PositionTrackingLibrary.c"
#include "Functions.c"



/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
	Bow(0);
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = false;

	GyroInit();
	startTask(PositionTrack);
	startTask(LCD);
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{

}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	int LeftDrive = 0;
	int RightDrive = 0;
	while (true)
	{
		////// DRIVE STICK //////
		LeftDrive  = (vexRT[Ch3] + vexRT[Ch4]);
		RightDrive   = (vexRT[Ch3] - vexRT[Ch4]);
		BaseSpeed(LeftDrive, RightDrive);



	}
}
