///////////////// AUTO LIBRARY ////////////////////

void WalloB(){

}

void WalloR(){
	// Shoot pre loads
	Balls(3000);
	//Bow to loading position
	while(SensorValue(BowPot) > 1000 && SensorValue(BowPot) < 1500){
		Bow(100);
	}
	Bow(0);
	//Fix tension
	startTask(AutoTensionWall);
	// Go to stack
	Drive(12);
	TurnRight(500);
	Drive(21);
	TurnRight(920);
	// Get balls
	SensorValue(TurnGyro) = 0;
	motor[Intake] = 127;
	Drive(9);
	DriveBACK(3);
	wait1Msec(50);
	BaseSpeed(60, 60);
	wait1Msec(800);
	BaseSpeed(0, 0);
	wait1Msec(300);
	// Backup to proper distance even if on balls
	while(SensorValue(RightEncoder) > -125){
		BaseSpeed(-100, -100);
	}
	BaseSpeed(0, 0);
	wait1Msec(50);
	// Turn to the net but no 0 so balls can't mess up
	TurnLeftNoZero(1530);
	//Shoot balls
	Bow(127);
	wait1Msec(4000);
	Bow(0);

}

void FrontMiddleL(){
	// Shoot Pre-Loads
	//Bow to loading position

	//Fix tension
	startTask(AutoTensionFrontMiddle);
	//Aim at stack
	TurnLeft(400);
	Drive(26);
	TurnRight(450);
	// Intake stack
	motor[Intake] = 127;
	Drive(14);
	wait1Msec(400);
	// Shoot stack
	Bow(127);
	wait1Msec(4000);
	Bow(0);
	motor[Intake] = 0;
}
void FrontMiddleR(){

}

void SideMiddleB(){

}
void SideMiddleR(){
	// Shoot Pre-Loads
	//Bow to loading position

	//Fix tension
	startTask(AutoTensionSideMiddle);
	//Aim and intake stack
	TurnRight(150);
	motor[Intake] = 127;
	Drive(14);
	wait1Msec(400);
	// aim at goal and shoot
	TurnLeft(150);
	wait1Msec(200);
	Bow(127);
	wait1Msec(4000);
	Bow(0);
	motor[Intake] = 0;
}


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
	motor[Intake] = 127;
	wait1Msec(200);
	Bow(127);
	wait1Msec(20000);
	//// WARNING LIGHTS /////
	SensorValue[LED] = 0;
	wait1Msec(4000);
	for(int i=0; i <= 15; i++)
	{
		if(SensorValue[LED] == 1){
			SensorValue[LED] = 0;
		}
		else if(SensorValue[LED] == 0){
			SensorValue[LED] = 1;
		}
		wait1Msec(150);
	}
	SensorValue[LED] = 1;
	// DRIVE TO OTHER SIDE
	Bow(0);
	// spit out balls
	motor[Intake] = -127;
	wait1Msec(200);
	TurnLeft(912);
	Drive(98);
	motor[Intake] = 127;
	TurnRight(892);
	// SHOOT OTHER SIDE
	wait1Msec(100);
	Bow(127);
	wait1Msec(25000);
	Bow(0);
	motor[Intake] = 0;
}
