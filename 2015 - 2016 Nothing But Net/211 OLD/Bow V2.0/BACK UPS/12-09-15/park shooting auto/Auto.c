///////////////// AUTO LIBRARY ////////////////////

void WalloB(){

}

void WalloR(){
	startTask(AutoTension);
	Drive(12);
	TurnRight(500);
	Drive(21);
	TurnRight(920);
	SensorValue(TurnGyro) = 0;
	motor[Intake] = 127;
	Drive(9);
	DriveBACK(3);
	wait1Msec(50);
	BaseSpeed(60, 60);
	wait1Msec(800);
	BaseSpeed(0, 0);
	wait1Msec(300);
	DriveBACK(6);
	TurnLeftNoZero(1530);
	Bow(127);
	wait1Msec(4000);
	Bow(0);

}

void Park(){
	SensorValue(BaseLock) = 0;
	SensorValue(TurnGyro) = 0;
	Bow(127);
	wait1Msec(200);
	Bow(0);
	wait1Msec(200);
	Drive(56);
	SensorValue(BaseLock) = 1;
	BaseSpeed(-100, -100);
	wait1Msec(50);
	BaseSpeed(0, 0);
	while(-SensorValue(TensionEncoder) < 660){
		motor[Tension] = -127;
	}
	motor[Tension] = 0;
	wait1Msec(3500);
	motor[Intake] = 127;
	wait1Msec(1000);
	if(abs(SensorValue(TurnGyro)) > 80){
		wait1Msec(15000);
	}
	Bow(127);
	wait1Msec(5000);
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
