///////////////// AUTO LIBRARY ////////////////////

// 8 Ball using stack on wall beside opposition's goal
void WalloB(){
	SensorValue(RightEncoder) = 0;
	// Shoot pre loads while shooting
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
	startTask(AutoTensionWall);
	// Go to stack
	TurnLeft(500);
	Drive(21);
	TurnLeft(920);
	// Get balls
	SensorValue(TurnGyro) = 0;
	motor[Intake] = 127;
	Drive(9);
	DriveBACK(3);
	BaseSpeed(100, 100);
	wait1Msec(800);
	BaseSpeed(0, 0);
	wait1Msec(300);
	// Backup to proper distance even if on balls
	while(SensorValue(RightEncoder) > -125){
		BaseSpeed(-100, -100);
	}
	BaseSpeed(0, 0);
	// Turn to the net but no 0 so balls can't mess up
	TurnRightNoZero(1500);
	//Shoot balls
	Bow(127);
	wait1Msec(5000);
	Bow(0);
}

void WalloR(){
	SensorValue(RightEncoder) = 0;
	// Shoot pre loads while shooting
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
	startTask(AutoTensionWall);
	// Go to stack
	TurnRight(500);
	Drive(21);
	TurnRight(920);
	// Get balls
	SensorValue(TurnGyro) = 0;
	motor[Intake] = 127;
	Drive(9);
	DriveBACK(3);
	BaseSpeed(100, 100);
	wait1Msec(800);
	BaseSpeed(0, 0);
	wait1Msec(300);
	// Backup to proper distance even if on balls
	while(SensorValue(RightEncoder) > -125){
		BaseSpeed(-100, -100);
	}
	BaseSpeed(0, 0);
	// Turn to the net but no 0 so balls can't mess up
	TurnLeftNoZero(1500);
	//Shoot balls
	Bow(127);
	wait1Msec(5000);
	Bow(0);
}

// 8 Ball using stack in front of the alliance tiles
void FrontMiddleL(){
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
void FrontMiddleR(){
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

// 8 Ball using stack between the two alliances
void SideMiddleB(){
	// Shoot Pre-Loads
	Balls(3000);
	motor[Intake] = -127;
	//Bow to loading position
	while(SensorValue(BowPot) > 2500 && SensorValue(BowPot) < 3000){
		Bow(100);
	}
	Bow(0);
	//Fix tension
	startTask(AutoTensionSideMiddle);
	//Aim and intake stack
	TurnRight(220);
	motor[Intake] = 127;
	Drive(14);
	wait1Msec(400);
	// aim at goal and shoot
	TurnLeft(250);
	wait1Msec(200);
	Bow(127);
	wait1Msec(4000);
	Bow(0);
	motor[Intake] = 0;
}
void SideMiddleR(){
	// Shoot Pre-Loads
	Balls(3000);
	motor[Intake] = -127;
	//Bow to loading position
	while(SensorValue(BowPot) > 2500 && SensorValue(BowPot) < 3000){
		Bow(100);
	}
	Bow(0);
	//Fix tension
	startTask(AutoTensionSideMiddle);
	//Aim and intake stack
	TurnLeft(220);
	motor[Intake] = 127;
	Drive(14);
	wait1Msec(400);
	// aim at goal and shoot
	TurnRight(250);
	wait1Msec(200);
	Bow(127);
	wait1Msec(4000);
	Bow(0);
	motor[Intake] = 0;
}

// auto to mess with close shooters
void Park(){
	// Zero sensors & disable base-lock
	SensorValue(BaseLock) = 0;
	SensorValue(TurnGyro) = 0;
	// Shoot first ball
	Bow(127);
	wait1Msec(200);
	Bow(0);
	wait1Msec(200);
	// Drive to middle, engage baselock
	Drive(56);
	SensorValue(BaseLock) = 1;
	BaseSpeed(-100, -100);
	wait1Msec(50);
	BaseSpeed(0, 0);
	// set tension
	while(-SensorValue(TensionEncoder) < 660){
		motor[Tension] = -127;
	}
	motor[Tension] = 0;
	// wait to get hit
	wait1Msec(3500);
	motor[Intake] = 127;
	wait1Msec(1000);
	if(abs(SensorValue(TurnGyro)) > 80){
		// oh no we turned ;)
		wait1Msec(15000);
	}
	// Shoot Last 3 balls
	Bow(127);
	wait1Msec(4000);
	Bow(0);
	motor[Intake] = 0;
	SensorValue(BaseLock) = 0;
}





// AUTO SKILLS RED SIDE
void RedSkills(){
	// RED SIDE SHOOT BALLS
	SensorValue[LED] = 1;
	motor[Intake] = 100;
	wait1Msec(200);
	Bow(100);
	wait1Msec(27000);
	// DRIVE TO OTHER SIDE
	Bow(0);
	// spit out balls
	motor[Intake] = -127;
	wait1Msec(200);
	TurnLeft(915);
	Drive(98);
	motor[Intake] = 127;
	TurnRight(890);
	// SHOOT OTHER SIDE
	wait1Msec(100);
	Bow(100);
	wait1Msec(25000);
	Bow(0);
	motor[Intake] = 0;
}
