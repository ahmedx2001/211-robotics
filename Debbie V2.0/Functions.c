///////////// FUNCTIONS //////////////////

void BaseSpeed(int LeftSpeed, int RightSpeed){
	motor[LeftDrive1] = LeftSpeed;
	motor[LeftDrive2] = LeftSpeed;
	motor[RightDrive1] = RightSpeed;
	motor[RightDrive2] = RightSpeed;
}
