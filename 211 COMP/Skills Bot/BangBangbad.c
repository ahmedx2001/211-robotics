
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
	long MinFactor = 1.9;
	int CurrentEncoder = 0;
	int PreviousEncoder = 0;
	int EncoderChange = 0;
	int ShooterRPM = 0;
	SensorValue(ShooterEncoder) = 0;
	while (true)
	{
		//Calculate the speed the flywheel is spinning at
		CurrentEncoder = -SensorValue(ShooterEncoder);
		EncoderChange = CurrentEncoder - PreviousEncoder;
		PreviousEncoder = CurrentEncoder;
		ShooterRPM = EncoderChange *40*60*25/360;
		wait1Msec(25);

		// Shooter RPM control
		if (Target > 1){

			if (ShooterRPM < Target){
				ShooterSpeed(127);
			}
			else {
				ShooterSpeed(60);
			}


		}
		// STOP SHOOTER
		else {
			ShooterSpeed(0+Guess);
		}
	}
}


///// RUN THE PID FOR THE SHOOTER ///////
task ShooterPID(){
	bool Recovery = true;
	long KP = 1;
	long KD = 0;
	int error = 0;
	int PChange = 0;
	int DChange = 0;
	int LastError = 0;
	int Acceleration = 0;
	int MotorSpeed = 0;
	int CurrentEncoder = 0;
	int PreviousEncoder = 0;
	int EncoderChange = 0;
	int currentRPM = 0;
	int prevoiusRPM = 0;
	int AdverageRPM = 0;
	SensorValue(ShooterEncoder) = 0;

	while (true)
	{
		//Calculate the speed the flywheel is spinning at
		CurrentEncoder = -SensorValue(ShooterEncoder);
		EncoderChange = CurrentEncoder - PreviousEncoder;
		PreviousEncoder = CurrentEncoder;

		currentRPM = EncoderChange *10*60*25/360;
		RPM = (prevoiusRPM + currentRPM)/2;
		error = (Target - RPM);

		AdverageRPM = 0;
		prevoiusRPM = currentRPM;
		writeDebugStreamLine("Speed: %d", RPM);
		writeDebugStreamLine("P Change: %d", PChange);
		writeDebugStreamLine("D Change: %d", DChange);
		//writeDebugStreamLine("Error: %d", error);

		// Calculate P
		error = Target - RPM;
		// Calculate D
		Acceleration = error - LastError;
		LastError = error;

		// Shooter RPM control
		if (Target > 1){

			// Spooling up
			if (error > 200){
				Recovery = true;
				MotorSpeed = 127;
			}
			// Maintaining
			else{
				// Calculate the maintaining value
					PChange = error / KP;
					DChange = Acceleration * KD;
					MotorSpeed = MotorSpeed + PChange - DChange;
			}

			// Run the shooter
			ShooterSpeed(MotorSpeed);

		}
		// STOP SHOOTER
		else {
			ShooterSpeed(0+Guess);
		}
		// Dalay for the RPM
		wait1Msec(100);
	}
}





task FlywheelVelocity(){
	int CurrentEncoder = 0;
	int PreviousEncoder = 0;
	int EncoderChange = 0;
	int currentRPM = 0;
	int prevoiusRPM = 0;
	int AdverageRPM = 0;
	int error = 0;
	SensorValue(ShooterEncoder) = 0;

	while (true)
	{
		//Calculate the speed the flywheel is spinning at
		CurrentEncoder = -SensorValue(ShooterEncoder);
		EncoderChange = CurrentEncoder - PreviousEncoder;
		PreviousEncoder = CurrentEncoder;

		currentRPM = EncoderChange *10*60*25/360;
		RPM = (prevoiusRPM + currentRPM)/2;
		error = (Target - RPM);

		AdverageRPM = 0;
		prevoiusRPM = currentRPM;
		writeDebugStreamLine("Speed: %d", RPM);
		writeDebugStreamLine("Error: %d", error);
		wait1Msec(100);

	}
}
