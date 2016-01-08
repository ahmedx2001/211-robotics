//////////////////// PID LIBRARY AND ALL THE FUNCTIONS TO RUN THE ROBOT ////////////////////

void Bow(int BowSpeed){
	motor[BowLeft] = BowSpeed;
	motor[BowRight] = BowSpeed;
}

////// MOVES THE DRIVE BASE //////
void BaseSpeed(int LeftSpeed, int RightSpeed) {
	motor[Left1]  = LeftSpeed;
	motor[Left2]  = LeftSpeed;
	motor[Left3]  = LeftSpeed;
	motor[Right1]   = RightSpeed;
	motor[Right2]   = RightSpeed;
	motor[Right3]   = RightSpeed;
}

void FourBall(){
	SensorValue(TensionEncoder) = 0;
	SensorValue(BowEncoder) = 0;
	int LastBowValue = 0;

	// Shoot first ball from cocked position
	Bow(127);
	wait1Msec(30);
	while(-SensorValue(BowEncoder) < 150 ){
		Bow(127);
	}
	Bow(30);

	// Shoot second ball from bottom feed position
	motor(Intake) = 127;
	wait1Msec(250);
	while(-SensorValue(BowEncoder) < 530 ){
		Bow(100);
	}
	Bow(30);


	// Shoot third ball from bottom feed position
	motor(Intake) = 127;
	wait1Msec(250);
	while(-SensorValue(BowEncoder) < 890 ){
		Bow(100);
	}
	Bow(30);

	// Shoot last ball from bottom feed position
	motor(Intake) = 127;
	wait1Msec(250);
	while(-SensorValue(BowEncoder) < 1250 ){
		Bow(100);
	}
	Bow(0);
	motor(Intake) = 0;
}

task LCD() {
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

		//Display the Backup battery voltage
		//displayLCDString(1, 0, "Backup: ");
		//sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');    //Build the value to be displayed
		//displayNextLCDString(backupBattery);

		//Sensor values
		displayLCDNumber(1, 0, -SensorValue(TensionEncoder));
		displayLCDNumber(1, 4, SensorValue(BowEncoder));


		//Short delay for the LCD refresh rate
		wait1Msec(100);
	}
}


task TensionButtons()
{
	while(true)
	{
		/////// TENSION ////////
		if(vexRT[Btn8U] == 1){
			motor[Tension]   = 100;
		}

		else if(vexRT[Btn8D] == 1){
			motor[Tension]   = -80;
		}

		else if(vexRT[Btn8L] == 1){
			wait1Msec(3000);
			if (vexRT[Btn8L] == 1){
				SensorValue(TensionEncoder) = 0;
			}
		}

		else if(vexRT[Btn5U] == 1){
			while(-SensorValue(TensionEncoder) > 0){
				motor[Tension] = 127;
			}
		}

		else if(vexRT[Btn5D] == 1){
			if (-SensorValue(TensionEncoder) < 15){
				while(-SensorValue(TensionEncoder) < 640){
					motor[Tension] = -127;
				}
			}
			else if (-SensorValue(TensionEncoder) > 420 && -SensorValue(TensionEncoder) < 780){
				motor[Tension] = -60;
				wait1Msec(1000);
				motor[Tension] = 0;
			}
			else if (-SensorValue(TensionEncoder) > 740){
				while(-SensorValue(TensionEncoder) >  720){
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
