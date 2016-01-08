
////////////// SHOOTER AND OTHER PID FUNCTIONS ///////////////

////// MOVES THE SHOOTER //////
void ShooterSpeed(int Speed) {
	motor[LeftShooter1]  = Speed;
	motor[LeftShooter2]  = Speed;
	motor[LeftShooter3]  = Speed;
	motor[RightShooter1]   = Speed;
	motor[RightShooter2]   = Speed;
	motor[RightShooter3]   = Speed;
}








task ShooterRPM(){
	int RPM = 0;
	SensorValue(ShooterEncoder) = 0;
	while(true){
		RPM = SensorValue(ShooterEncoder) * 6.66;
		writeDebugStreamLine("RPM: %d", RPM);
		SensorValue(ShooterEncoder) = 0;
		wait1Msec(25);
	}
}
