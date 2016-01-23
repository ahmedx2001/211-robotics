//
//                       VEX Competition Control Include File
//
// This file provides control over a VEX Competition Match. It should be included in the user's
// program with the following line located near the start of the user's program
//        #include "VEX_Competition_Includes.h"
// The above statement will cause this program to be included in the user's program. There's no
// need to modify this program.
//
// The program displays status information on the new VEX LCD about the competition state. You don't
// need the LCD, the program will work fine whether or not the LCD is actually provisioned.
//
// The status information is still useful without the LCD. The ROBOTC IDE debugger has a "remote screen"
// that contains a copy of the status information on the LCD. YOu can use this to get a view of the
// status of your program. The remote screen is shown with the menu command
//   "Robot -> Debugger Windows -> VEX Remote Screen"
//
// The LCD is 2 lines x 16 characters. There are three display formats to look for:
//
//        State          Description
//
//    ----------------
//   |Disabled        |  The robot is idle. This occurs before both the autonomous and user
//   |Time mm:ss.s    |  control states. The time display is minutes and seconds it has been idle.
//    ----------------
//
//    ----------------
//   |Autonomous      |  The robot is running autonomous code.
//   |Time mm:ss.s    |  control states. The time display is minutes and seconds it has been running.
//    ----------------
//
//    ----------------
//   |User Control    |  The robot is running user control code.
//   |Time mm:ss.s    |  control states. The time display is minutes and seconds it has been running.
//    ----------------
//////////////////////////////////////////////////////////////////////////////////////////////////////


/// DEFULT TO 4 BALL AUTO ///
int AutoSelect = 5;


////// Display stuff on the LCD //////
task LCD() {
	bool ButtonPressed = false;
	string AutoName = "Nothing";
	bLCDBacklight = true;                                    // Turn on LCD Backlight
	string mainBattery, backupBattery;

	while(true)                                                        // An infinite loop to keep the program running until you terminate it
	{
		clearLCDLine(0);                                            // Clear line 1 (0) of the LCD
		clearLCDLine(1);                                            // Clear line 2 (1) of the LCD

		//Display the Primary Robot battery voltage
		displayLCDString(0, 0, "Primary: ");
		sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
		displayNextLCDString(mainBattery);

		if (bIfiAutonomousMode){
			displayLCDString(1, 0, "AUTO:");
			displayLCDString(1, 6, AutoName);
		}
		else{
			//displayLCDNumber(1, 0, SensorValue(TurnGyro));
			//displayLCDNumber(1, 0, SensorValue(BowEncoder));
			//displayLCDNumber(1, 0, SensorValue(RightEncoder));
			displayLCDNumber(1, 0, abs(SensorValue(TensionEncoder)));
			displayLCDNumber(1, 4, AutoSelect);
			displayLCDString(1, 6, AutoName);


			if (nLCDButtons == 1){
				wait1Msec(2000);
				if (nLCDButtons == 1){
					SensorValue(TensionEncoder) = 0;
				}
			}

			else if (nLCDButtons == 2){
				if (AutoSelect > 0 && ButtonPressed == false){
					AutoSelect--;
				}
				ButtonPressed = true;
			}
			else if (nLCDButtons == 4){
				if (AutoSelect < 9 && ButtonPressed == false){
					AutoSelect++;
				}
				ButtonPressed = true;
			}
			else {
				ButtonPressed = false;
			}

			switch(AutoSelect)
			{
			case 1:
				AutoName = "BALL AUTO";
				break;

			case 5:
				AutoName = "SKILLS";
				break;
			case 6:
				AutoName = "PID TURN";
				break;
			case 7:
				AutoName = "PID TEST";
				break;
			case 8:
				AutoName = "LEFT Test";
				break;
			case 9:
				AutoName = "RIGHT TEST";
				break;
			default:
				AutoName = "NOTHING";
			}
		}

		//Short delay for the LCD refresh rate
		wait1Msec(100);
	}
}


void allMotorsOff();
void allTasksStop();
task autonomous();
task usercontrol();

int nTimeXX = 0;
bool bStopTasksBetweenModes = true;
bool JustDisabled = true;


task main()
{
	// Master CPU will not let competition start until powered on for at least 2-seconds
	clearLCDLine(0);
	clearLCDLine(1);
	displayLCDPos(0, 0);
	displayNextLCDString("Startup");
	wait1Msec(2000);


	while (true)
	{
		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDPos(0, 0);

		while (bIfiRobotDisabled)
		{
			if (JustDisabled == true){
				startTask(LCD);
				SensorType[ in2 ] = sensorNone;
				wait1Msec(1000);
				SensorType[ in2 ] = sensorGyro;
				wait1Msec(2000);
			}
			else {
				wait1Msec(25);
			}
			JustDisabled = false;
		}

		JustDisabled = true;

		nTimeXX = 0;
		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDPos(0, 0);
		if (bIfiAutonomousMode)
		{
			displayNextLCDString("Autonomous");
			startTask(autonomous);

			// Waiting for autonomous phase to end
			while (bIfiAutonomousMode && !bIfiRobotDisabled)
			{
				if (!bVEXNETActive)
				{
					if (nVexRCReceiveState == vrNoXmiters) // the transmitters are powered off!!
						allMotorsOff();
				}
				wait1Msec(25);               // Waiting for autonomous phase to end
			}
			allMotorsOff();
			if(bStopTasksBetweenModes)
			{
				allTasksStop();
			}
		}

		else
		{
			displayNextLCDString("User Control");
			startTask(usercontrol);

			// Here we repeat loop waiting for user control to end and (optionally) start
			// of a new competition run
			while (!bIfiAutonomousMode && !bIfiRobotDisabled)
			{
				if (nVexRCReceiveState == vrNoXmiters) // the transmitters are powered off!!
					allMotorsOff();
				wait1Msec(25);
			}
			allMotorsOff();
			if(bStopTasksBetweenModes)
			{
				allTasksStop();
			}
		}
	}
}


void allMotorsOff()
{
	motor[port1] = 0;
	motor[port2] = 0;
	motor[port3] = 0;
	motor[port4] = 0;
	motor[port5] = 0;
	motor[port6] = 0;
	motor[port7] = 0;
	motor[port8] = 0;
#if defined(VEX2)
	motor[port9] = 0;
	motor[port10] = 0;
#endif
}

void allTasksStop()
{
	stopTask(1);
	stopTask(2);
	stopTask(3);
	stopTask(4);
#if defined(VEX2)
	stopTask(5);
	stopTask(6);
	stopTask(7);
	stopTask(8);
	stopTask(9);
	stopTask(10);
	stopTask(11);
	stopTask(12);
	stopTask(13);
	stopTask(14);
	stopTask(15);
	stopTask(16);
	stopTask(17);
	stopTask(18);
	stopTask(19);
#endif
}
