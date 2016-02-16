//////////////////// PID LIBRARY AND ALL THE FUNCTIONS TO RUN THE ROBOT ////////////////////


////// MOVES Bow //////
void Bow(int BowSpeed){
	motor[BowLeft] = BowSpeed;
	motor[BowRight] = BowSpeed;
}

////// MOVES THE DRIVE BASE //////
void BaseSpeed(int LeftSpeed, int RightSpeed) {
	motor[Left1] = LeftSpeed;
	motor[Left2] = LeftSpeed;
	motor[Left3] = LeftSpeed;

	motor[Right1] = RightSpeed;
	motor[Right2] = RightSpeed;
	motor[Right3] = RightSpeed;
}

////// Display stuff on the LCD //////
task LCD() {
	string AutoName = "Nothing";
	bLCDBacklight = true;                                    // Turn on LCD Backlight
	string mainBattery;

	while(true)                                                        // An infinite loop to keep the program running until you terminate it
	{
		clearLCDLine(0);                                            // Clear line 1 (0) of the LCD
		clearLCDLine(1);                                            // Clear line 2 (1) of the LCD
		displayLCDPos(0, 0);

		displayLCDString(0, 0, "X:");
		displayLCDNumber(0, 3, Xpos);

		displayLCDString(0, 6, "Y:");
		displayLCDNumber(0, 9, Ypos);

		displayLCDString(1, 0, "Angle:");
		displayLCDNumber(1, 7, Heading);

		//Short delay for the LCD refresh rate
		wait1Msec(100);
	}
}
