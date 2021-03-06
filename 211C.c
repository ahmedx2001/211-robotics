#pragma config(Motor,  port1,           FR,            tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           Left,          tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           Right,         tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           Back,          tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           CR,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           BR,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           CL,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           BL,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          FL,            tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
  // ..........................................................................
  // Insert user code here.
  // ..........................................................................

  // Remove this function call once you have "real" code.
  AutonomousCodePlaceholderForTesting();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
  // User control code here, inside the loop.l

  while (true)
  {
    if (vexRT[Btn6U]== 1) {
    	motor[FR] = 1700;
    	motor[FL] = 1700;
    	motor[BR] = 1700;
    	motor[BL] = 1700;
    	motor[CR] = 1700;
    	motor[CL] = 1700;
    }
  	 else {
  		motor[FR] = 0;
    	motor[FL] = 0;
    	motor[BR] = 0;
    	motor[BL] = 0;
    	motor[CR] = 0;
    	motor[CL] = 0;
  	}

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

		motor[Left] = vexRT[Ch3] + sqrt(3)/2 * vexRT[Ch4] + vexRT[Ch1];
		motor[Right] = -vexRT[Ch3] + sqrt(3)/2 * vexRT[Ch4] + vexRT[Ch1];
		motor[Back] = vexRT[Ch4] - vexRT[Ch1];
}

    UserControlCodePlaceholderForTesting();
  }
