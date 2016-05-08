///////////// FUNCTIONS //////////////////

void BaseSpeed(int LeftSpeed, int RightSpeed){
	motor[LeftDrive1] = LeftSpeed;
	motor[LeftDrive2] = LeftSpeed;
	motor[RightDrive1] = RightSpeed;
	motor[RightDrive2] = RightSpeed;
}

void BowSpeed(int Speed){
	motor[LeftBow1] = Speed;
	motor[LeftBow2] = Speed;
	motor[RightBow1] = Speed;
	motor[RightBow2] = Speed;
}
