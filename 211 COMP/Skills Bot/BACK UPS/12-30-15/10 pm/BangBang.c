
////////////// SHOOTER AND OTHER PID FUNCTIONS ///////////////

////// MOVES THE SHOOTER //////
void ShooterSpeed(int Speed) {
	motor[LeftShooter1]  = abs(Speed);
	motor[LeftShooter2]  = abs(Speed);
	motor[LeftShooter3]  = abs(Speed);
	motor[RightShooter1]   = abs(Speed);
	motor[RightShooter2]   = abs(Speed);
	motor[RightShooter3]   = abs(Speed);
}

///// RUN THE PID FOR THE SHOOTER ///////
task ShooterBangBang(){
	long FullFactor = 1;
	long MinFactor = 1.7;
	int CurrentEncoder = 0;
	int PreviousEncoder = 0;
	int EncoderChange = 0;
	SensorValue(ShooterEncoder) = 0;
	while (true)
	{
		//Calculate the speed the flywheel is spinning at
		CurrentEncoder = -SensorValue(ShooterEncoder);
		EncoderChange = CurrentEncoder - PreviousEncoder;
		RPM = EncoderChange *40*60*25/360;
		PreviousEncoder = CurrentEncoder;
		writeDebugStreamLine("Speed: %d", RPM);
		writeDebugStreamLine("Guess: %d", Guess);
		wait1Msec(25);

		// Shooter RPM control
		if (Target > 1){

			if (RPM < Target){
				ShooterSpeed(127 * FullFactor);
			}
			else {
				ShooterSpeed(Target / 100 * MinFactor);
			}


		}
		// STOP SHOOTER
		else {
			ShooterSpeed(0+Guess);
		}
	}
}
