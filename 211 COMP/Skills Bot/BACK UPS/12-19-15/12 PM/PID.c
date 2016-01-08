
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



task Shooter(){
	long error = 99999;
	float KP = 0;
	long Velocity = 0;
	SensorValue(ShooterEncoder) = 0;
	int OldMotorSpeed = 0;
	int ShooterSpeedIn = 0;

	while (true)
	{
		// Get speed from joysick
		if (vexRT(Btn8L) == 1){
			ShooterSpeedIn  = 50;
		}
		else if (vexRT(Btn8U) == 1){
			ShooterSpeedIn  = 90;
		}
		else if (vexRT(Btn8R) == 1){
			ShooterSpeedIn  = 127;
		}
		else if (vexRT(Btn8D) == 1){
			ShooterSpeedIn  = 0;
		}

		//Calculate the speed the flywheel is spinning at
		Velocity = SensorValue(ShooterEncoder);
		SensorValue(ShooterEncoder) = 0;

		// Run Speed Control
		if (ShooterSpeedIn > 10){

			// P = calculate the error
			error = ShooterSpeedIn - Velocity;

			// Calculates how fast to move the robot
			ShooterSpeed(error * KP);

			OldMotorSpeed = (error * KP);

			wait1Msec(25);
		}
		else {
			if (Velocity < 30){
				ShooterSpeed(0);
			}
			else{
				OldMotorSpeed = (OldMotorSpeed - 3);
				ShooterSpeed(OldMotorSpeed);
			}
		}

	}
}
