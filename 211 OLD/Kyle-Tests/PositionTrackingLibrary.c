////////////// POSITION TRACKING LIBRARY ////////////////
// Position Tracking Variables
float NewDistance = 0;
int NewAngle = 0;




void GoTo(float Xnew, float Ynew, int FinalHeading){



}


void GetDistance(float Xnew, float Ynew){
	float Xdiff;
	float Ydiff;

	Xdiff = Xnew - Xpos;
	Ydiff = Ynew - Ypos;

	// Distance to target
	NewDistance = sqrt(pow(Xdiff,2) + pow(Ydiff,2));

	// Angle to target
	atan2(Xdiff, Ydiff) * 180/PI;
}




// position tracking
task PositionTrack(){
	SensorValue(LeftEncoder) = 0;
	SensorValue(RightEncoder) = 0;
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
		LeftTot = (SensorValue(LeftDrive) * 0.024);
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

		wait1Msec(25);
	}
}
