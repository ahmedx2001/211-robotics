//////////////////////////////////////////////////////////////////////////////////////////////////////
//																																																	//
//                       VEX Competition Control Include File																				//
//																																																	//
// This file provides control over a VEX Competition Match. It should be included in the user's			//
// program with the following line located near the start of the user's program											//
//        #include "VEX_Competition_Includes.h"																											//
// The above statement will cause this program to be included in the user's program.								//
//																																																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////

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
		displayLCDPos(0, 0);

		//Display the Primary Robot battery voltage
		displayLCDString(0, 0, "Primary: ");
		sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
		displayNextLCDString(mainBattery);

		if (bIfiAutonomousMode){
			displayLCDString(1, 0, "AUTO:");
			displayLCDString(1, 6, AutoName);
		}
		else{
			displayLCDNumber(1, 0, abs(SensorValue(TensionEncoder)));
			displayLCDNumber(1, 4, AutoSelect);
			displayLCDString(1, 6, AutoName);


			if (nLCDButtons == 1){
				wait1Msec(1000);
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
				if (AutoSelect < 20 && ButtonPressed == false){
					AutoSelect++;
				}
				ButtonPressed = true;
			}
			else {
				ButtonPressed = false;
			}

			switch(AutoSelect)
			{
				// SKILLS
			case 1:
				AutoName = "SKILLS";
				break;

				// AUTO'S
			case 2:
				AutoName = "BALL AUTO";
				break;
			case 3:
				AutoName = "FrontL";
				break;
			case 4:
				AutoName = "FrontR";
				break;

				//TEST CODE
			case 17:
				AutoName = "PID TURN";
				break;
			case 18:
				AutoName = "PID DRIVE";
				break;
			case 19:
				AutoName = "LEFT Test";
				break;
			case 20:
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
task autonomous();
task usercontrol();

task main()
{
	// Master CPU will not let competition start until powered on for at least 2-seconds
	clearLCDLine(0);
	clearLCDLine(1);
	displayLCDPos(0, 0);
	displayNextLCDString("Startup");
	GyroInit(); // Initilize the Gyro
	wait1Msec(2000);
	startTask(LCD);


	while (true)
	{
		// AUTONOMOUS
		if (bIfiAutonomousMode)
		{
			// Stop user contol tasks
			stopTask(usercontrol);
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
		}
		// DISABLED
		else if (bIfiRobotDisabled)
		{
			// stop tasks that let the robot move
			stopTask(autonomous);
			stopTask(usercontrol);
		}
		// DRIVER CONTROL
		else
		{
			// start user control tasks
			stopTask(autonomous);
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
