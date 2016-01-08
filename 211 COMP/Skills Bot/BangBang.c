
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
	int CurrentEncoder = 0;
	int PreviousEncoder = 0;
	int EncoderChange = 0;
	int CurrentRPM = 0;
	int OldRPM[5];
	int TotalRPM = 0;
	float MinFactor = 1;
	SensorValue(ShooterEncoder) = 0;
	while (true)
	{
		//Calculate the speed the flywheel is spinning at
		CurrentEncoder = -SensorValue(ShooterEncoder);
		EncoderChange = CurrentEncoder - PreviousEncoder;
		CurrentRPM = EncoderChange *40*60*25/360;
		PreviousEncoder = CurrentEncoder;

		for(int i=4; i>0; i--){
			OldRPM[i] = OldRPM[i-1];
		}
		OldRPM[0] = CurrentRPM;
		for(int i=0; i<=4; i++){
			TotalRPM = TotalRPM + OldRPM[i];
		}
		RPM = TotalRPM / 5;

		writeDebugStreamLine("CurrentRPM: %d", CurrentRPM);
		writeDebugStreamLine("TotalRPM: %d", TotalRPM);
		writeDebugStreamLine("Speed: %d", RPM);

		TotalRPM = 0;
		//writeDebugStreamLine("Guess: %d", Guess);
		wait1Msec(25);

		// Shooter RPM control
		if (Target > 1){

			if (RPM < Target){
				ShooterSpeed(127);
			}
			else {
				ShooterSpeed(Target / 100 * MinFactor);
			//ShooterSpeed(60);
			}


		}
		// STOP SHOOTER
		else {
			ShooterSpeed(0+Guess);
		}
	}
}
