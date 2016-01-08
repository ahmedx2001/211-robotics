//////////////////// PID LIBRARY AND ALL THE FUNCTIONS TO RUN THE ROBOT ////////////////////


////// MOVES Bow //////
void Bow(int BowSpeed){
	motor[BowLeft] = BowSpeed;
	motor[BowRight] = BowSpeed;
}

////// MOVES THE DRIVE BASE //////
void BaseSpeed(int LeftSpeed, int RightSpeed) {
	setMotor(Left1, LeftSpeed);
	setMotor(Left2, LeftSpeed);
	setMotor(Left3, LeftSpeed);
	setMotor(Right1, RightSpeed);
	setMotor(Right2, RightSpeed);
	setMotor(Right3, RightSpeed);
}

/////// SHOOT BALLS ///////
void Balls(int Time){
	motor[Intake] = 127;
	wait1Msec(200);
	Bow(100);
	wait1Msec(Time);
	Bow(0);
}

////// LEFT TEST ///////
void LeftTest(){
	motor[Left1] = 127;
	wait1Msec(1000);
	motor[Left1] = 0;
	motor[Left2] = 127;
	wait1Msec(1000);
	motor[Left2] = 0;
	motor[Left3] = 127;
	wait1Msec(1000);
	motor[Left3] = 0;
	wait1Msec(2000);
	motor[BowLeft] = 127;
	wait1Msec(500);
	motor[BowLeft] = 0;
}

////// RIGHT TEST //////
void RightTest(){
	motor[Right1] = 127;
	wait1Msec(1000);
	motor[Right1] = 0;
	motor[Right2] = 127;
	wait1Msec(1000);
	motor[Right2] = 0;
	motor[Right3] = 127;
	wait1Msec(1000);
	motor[Right3] = 0;
	wait1Msec(2000);
	motor[BowRight] = 127;
	wait1Msec(500);
	motor[BowRight] = 0;
}

////// Set the tension to values while driving //////
task TensionButtons()
{
	int DT = 720;  // wants 625
	while(true)
	{
		/////// TENSION ///////
		if(vexRT[Btn8U] == 1 && vexRT[Btn8R] == 1){
			motor[Tension] = 0;
			wait1Msec(1000);
			if(vexRT[Btn8U] == 1 && vexRT[Btn8R] == 1){
				SensorValue(TensionEncoder) = 0;
			}
		}
		if(vexRT[Btn8R] == 1){
			motor[Tension]   = 100;
		}
		else if(vexRT[Btn8L] == 1){
			motor[Tension]   = -80;
		}

		else if(vexRT[Btn8U] == 1){
			while(-SensorValue(TensionEncoder) > 0 && vexRT[Btn8R] == 0){
				motor[Tension] = 127;
			}
		}

		else if(vexRT[Btn8D] == 1){
			if (-SensorValue(TensionEncoder) < 15){
				while(-SensorValue(TensionEncoder) < (DT - 20) && vexRT[Btn8R] == 0){
					motor[Tension] = -127;
				}
			}
			else if (-SensorValue(TensionEncoder) > (DT - 240) && -SensorValue(TensionEncoder) < (DT + 120)){
				motor[Tension] = -100;
				wait1Msec(1000);
				motor[Tension] = 0;
			}
			else if (-SensorValue(TensionEncoder) > (DT + 80)){
				while(-SensorValue(TensionEncoder) >  (DT + 5) && vexRT[Btn8R] == 0){
					motor[Tension] = 127;
				}
			}
			else {
				motor[Tension]   = 0;
			}
		}

		else {
			motor[Tension]   = 0;
		}


	}
}




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
			//displayLCDNumber(1, 0, SensorValue(BowEncoder));
			//displayLCDNumber(1, 0, SensorValue(RightEncoder));
			//displayLCDNumber(1, 0, SensorValue(BowPot));
			//displayLCDNumber(1, 0, abs(SensorValue(TensionEncoder)));
			//displayLCDNumber(1, 0, GyroAngleDegGet());
			//displayLCDNumber(1, 0, SmartMotorGetTemperature(Left1));
			//displayLCDNumber(1, 4, AutoSelect);
			//displayLCDString(1, 6, AutoName);


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
