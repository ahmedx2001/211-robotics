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
			stopTask(TensionButtons);
			SensorValue(BaseLock) = 0;
		}
		// DRIVER CONTROL
		else
		{
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
