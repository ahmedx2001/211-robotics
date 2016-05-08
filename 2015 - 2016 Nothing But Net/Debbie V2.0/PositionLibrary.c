////////////// POSITION TRACKING LIBRARY ////////////////

// VARIABLES
bool AtTarget = true;
bool AtHeading = true;
float GoX;
float GoY;
float XDiff;
float YDiff;
float GoAngle;
float TargetDistance;
float TargetHeading;


task AutoMove(){
	float InitialDistance;
	float InitialAngle;
	while(1==1){

		//Heading
		if(AtHeading == false){
			InitialAngle = TargetHeading;
			while(abs(InitialAngle - TargetHeading) > 25){
				if(InitialAngle < TargetHeading){
					BaseSpeed(100, -100);
				}
				else if(InitialAngle > TargetHeading){
					BaseSpeed(-100, 100);
				}
			}
			AtHeading = true;
		}//At

		//Distance
		else if(AtTarget == false){
			InitialDistance = TargetDistance;
			while(abs(InitialDistance - TargetDistance) > 25){
				if(InitialDistance > TargetDistance){
					BaseSpeed(100, 100);
				}
				else if(InitialDistance < TargetDistance ){
					BaseSpeed(-100, -100);
				}
			}
			AtTarget = true;
		}//At

	}//Loop
}//Task

void Go(int X, int Y, int Angle){
	AtTarget = false;
	AtHeading = false;
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

		XChange = Distance * (sinDegrees(Heading));
		YChange = Distance * (cosDegrees(Heading));

		Xpos += XChange;
		Ypos += YChange;

		// Calculate distance to target for auto use
		XDiff = (GoX-Xpos);
		YDiff = (GoX-Xpos);
		TargetDistance = sqrt(pow(XDiff,2)+pow(YDiff,2));
		TargetHeading = atan2(XDiff, YDiff);
		TargetHeading = radiansToDegrees(TargetHeading);

		wait1Msec(50);
	}
}
