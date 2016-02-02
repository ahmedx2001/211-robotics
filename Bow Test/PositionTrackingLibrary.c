////////////// POSITION TRACKING LIBRARY ////////////////

// position tracking
task PositionTrack(){
	SensorValue(LeftDrive) = 0;
	SensorValue(RightDrive) = 0;
	float XChange = 0;
	float YChange = 0;
	Xpos = StartPositionX;
	Ypos = StartPositionY;
	float LastTot = 0;
	float LeftTot = 0;
	float RightTot = 0;


	while(true){
		// Calculate Angle
		Heading = GyroAngleDegGet() + StartHeading;

		// Calculate Distance traveled
		LeftTot = -(SensorValue(LeftDrive) * 0.024);
		RightTot = (SensorValue(RightDrive) * 0.024);
		DistanceTot = (LeftTot + RightTot)/2;
		Distance = DistanceTot - LastTot;
		LastTot = DistanceTot;

		XChange = Distance * (cosDegrees(Heading));
		YChange = Distance * (sinDegrees(Heading));

		Xpos += XChange;
		Ypos += YChange;

		displayLCDNumber(1, 0, Heading);
		displayLCDNumber(1, 4, DistanceTot);
		displayLCDNumber(1, 7, Ypos);
		displayLCDNumber(1, 9, Ypos);

		wait1Msec(100);
	}
}
