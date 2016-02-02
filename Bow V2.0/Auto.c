///////////////// AUTO LIBRARY ////////////////////

// 8 Ball using stack in front of the alliance tiles
void FrontL(){
	// Shoot Pre-Loads
	SensorValue(RightEncoder) = 0;
	// Shoot pre loads while shooting
	BaseSpeed(100, 100);
	wait1Msec(20);
	BaseSpeed(30, 30);
	motor[Intake] = 127;
	Bow(127);
	while(SensorValue(RightEncoder) < 500){
		BaseSpeed(26, 26);
	}
	BaseSpeed(0, 0);
	Bow(0);
	motor[Intake] = -127;
	//Bow to loading position
	while(SensorValue(BowPot) > 2500 && SensorValue(BowPot) < 3000){
		Bow(100);
	}
	Bow(0);

	//Fix tension
	startTask(AutoTensionFrontMiddle);
	//Aim at stack
	TurnLeft(335);
	// Intake stack
	motor[Intake] = 127;
	Drive(11);
	DriveBACK(2);
	while(SensorValue(RightEncoder) < 350){
		BaseSpeed(60, 60);
	}
	wait1Msec(400);
	// Shoot stack
	TurnRight(460);
	Bow(110);
	wait1Msec(4000);
	Bow(0);
	motor[Intake] = 0;
}


void FrontR(){
	// Shoot Pre-Loads
	SensorValue(RightEncoder) = 0;
	// Shoot pre loads while shooting
	BaseSpeed(100, 100);
	wait1Msec(20);
	BaseSpeed(30, 30);
	motor[Intake] = 127;
	Bow(127);
	while(SensorValue(RightEncoder) < 500){
		BaseSpeed(28, 28);
	}
	BaseSpeed(0, 0);
	Bow(0);
	motor[Intake] = -127;
	//Bow to loading position
	while(SensorValue(BowPot) > 2500 && SensorValue(BowPot) < 3000){
		Bow(100);
	}
	Bow(0);

	//Fix tension
	startTask(AutoTensionFrontMiddle);
	//Aim at stack
	TurnRight(335);
	// Intake stack
	motor[Intake] = 127;
	Drive(11);
	DriveBACK(2);
	while(SensorValue(RightEncoder) < 350){
		BaseSpeed(60, 60);
	}
	wait1Msec(400);
	// Shoot stack
	TurnLeft(455);
	Bow(127);
	wait1Msec(4000);
	Bow(0);
	motor[Intake] = 0;
}
