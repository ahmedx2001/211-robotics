
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
	float KP = 1;
	SensorValue(ShooterEncoder) = 0;
	int MotorSpeed = 0;
	while (true)
	{
		//Calculate the speed the flywheel is spinning at
		RPM = -SensorValue(ShooterEncoder)*10*60*25/360;
		SensorValue(ShooterEncoder) = 0;
		writeDebugStreamLine("Speed: %d", RPM);

		// Run Speed Control
		if (Target > 1){

			// P = calculate the error
			error = Target - RPM;

			// Calculate the change to motor power
			change = error * KP;

			// Calculates how fast to move the robot
			MotorSpeed = MotorSpeed + change;

			// Don't let the shooter run backwards
			if (MotorSpeed < 0) ShooterSpeed(0);
			else ShooterSpeed(MotorSpeed);

			// Delay to allow calculations to have change
			wait1Msec(100);
		}
		else {
			// Flywheel Stopped
			ShooterSpeed(0);
			error = 0;
		}
	}
}




task ShooterRPM(){
	int Encoder = 0;
	int LastEncoder = 0;
	SensorValue(ShooterEncoder) = 0;
	while(true){
		Encoder = SensorValue(ShooterEncoder);
		RPM = (Encoder - LastEncoder) * 6.66;
		LastEncoder = Encoder;
		writeDebugStreamLine("RPM: %d", RPM);
		wait1Msec(100);
	}
}
