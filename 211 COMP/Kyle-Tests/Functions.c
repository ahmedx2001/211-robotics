//////////////////// PID LIBRARY AND ALL THE FUNCTIONS TO RUN THE ROBOT ////////////////////

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
			//Put test variables here
			displayLCDNumber(1, 4, AutoSelect);
			displayLCDString(1, 6, AutoName);


			if (nLCDButtons == 2){
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
				AutoName = "Park AUTO";
				break;
			case 4:
				AutoName = "WalloB";
				break;
			case 5:
				AutoName = "WalloR";
				break;
			case 6:
				AutoName = "Front L";
				break;
			case 7:
				AutoName = "Front R";
				break;
				case 8:
				AutoName = "SideMid B";
				break;
			case 9:
				AutoName = "SideMid R";
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
