
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
task Shooter(){
	long error = 0;
	long change = 0;
	float KP = 0.5;
	int MotorSpeed = 0;
	int CurrentEncoder = 0;
	int PreviousEncoder = 0;
	int EncoderChange = 0;
	SensorValue(ShooterEncoder) = 0;
	while (true)
	{
		//Calculate the speed the flywheel is spinning at
		CurrentEncoder = -SensorValue(ShooterEncoder);
		EncoderChange = CurrentEncoder - PreviousEncoder;
		RPM = EncoderChange *10*60*25/360;
		PreviousEncoder = CurrentEncoder;
		writeDebugStreamLine("Speed: %d", RPM);
		wait1Msec(100);

		// Shooter RPM control
		if (Target > 1){
			// P = calculate the error
			error = Target - RPM;

			// Calculate the change to motor power
			change = error * KP;

			// Calculates how fast to move the robot
			MotorSpeed = change;

			// Don't let the shooter run backwards
			if (MotorSpeed < 0) ShooterSpeed(0);
			else ShooterSpeed(MotorSpeed);

		}
		// STOP SHOOTER
		else {
			ShooterSpeed(0);
		}
	}
}
