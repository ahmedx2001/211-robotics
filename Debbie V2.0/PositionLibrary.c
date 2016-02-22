////////////// POSITION TRACKING LIBRARY ////////////////
// VARIABLES
float GoX;
float GoY;
float GoAngle;


task AutoMove(){

}

void Go(int X, int Y, int Angle){
	GoX = X;
	GoY = Y;
	GoAngle = Angle;
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
		LeftTot = (SensorValue(LeftEncoder) * 0.035);
		RightTot = (SensorValue(RightEncoder) * 0.035);
		DistanceTot = (LeftTot + RightTot)/2;
		Distance = DistanceTot - LastTot;
		LastTot = DistanceTot;

		XChange = Distance * (cosDegrees(Heading));
		YChange = Distance * (sinDegrees(Heading));

		Xpos += XChange;
		Ypos += YChange;

		wait1Msec(10);
	}
}
