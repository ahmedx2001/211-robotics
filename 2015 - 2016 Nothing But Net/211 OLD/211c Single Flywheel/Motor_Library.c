/*
2015 - 2016 SWC Robotics Team 211c
Motor library.

*/

void runLeft(int val);
void runRight(int val);
void moveStright(int val);
void drive(int leftPow, int rightPow);
void shooter(int val);
void intake(int val);
void speedLed(bool val);
void ledRGY(bool R, bool G, bool Y);




void runLeft(int val){  								//runs left side of the drive base
	motor[left1] = val;
	motor[left2] = val;
	motor[left3] = val;
}

void runRight(int val){									//runs right side of the drive base
	motor[right1] = val;
	motor[right2] = val;
	motor[right3] = val;
}

void moveStright(int val){									//moves stright forward or backward
	runLeft(val);
	runRight(val);
}

void drive(int leftPow, int rightPow){
	runLeft(leftPow);
	runRight(rightPow);
}
void shooter(int val){									//runs the shooter, and makes sure it doesn't go back wards
	motor[shooter1]=abs(val);
	motor[shooter2]=abs(val);
	motor[shooter3]=abs(val);
}

void intake(int val){									//runs intake motor
	motor[intake1]=val;
}

void speedLed(bool val){
	if (val) SensorValue[speedLed1] = 0;//on
	else SensorValue[speedLed2] = 1;		//off
}

void ledRGY(bool R, bool G, bool Y){
	SensorValue[ledR] = !(R);
	SensorValue[ledG] = !(G);
	SensorValue[ledY] = !(Y);
}
