////// PID drive //////
void DriveCorrection(int Distance) {
	long error = 99999;
	float KP = 0.35;
	float KD = 2.1;
	float KI = 1;
	long Velocity = 0;
	long Integral = 0;
	long CurrentDistance;
	long PreviousDistance = 0;
	SensorValue(LeftEncoder) = 0;
	SensorValue(RightEncoder) = 0;
	SensorValue(TurnGyro) = 0;
	int SpeedTweak = 0;
	int MotorSpeed = 0;
	int cycle = 0;

	while (abs(error) > 5) {
		CurrentDistance = ((SensorValue(RightEncoder)-SensorValue(LeftEncoder))/2);

		if (Velocity < 10){
			if(error > 0){
				Integral++;
			}
			else {
				Integral = 0;
			}
		}
		else {
			Integral = 0;
		}


		// P = calculate the error
		error = Distance - CurrentDistance;

		// D = Calculate the speed
		Velocity = CurrentDistance - PreviousDistance;

		if (SensorValue(TurnGyro) < -10){
			// Edit how much is added to change how fast it reacts
			SpeedTweak--;
		}
		else if (SensorValue(TurnGyro) > 10){
			SpeedTewak++;
		}

		// Calculates how fast to move the robot
		MotorSpeed = (error * KP) + (Integral * KI) - (Velocity * KD);

		BaseSpeed(MotorSpeed - SpeedTeweak, MotorSpeed + SpeedTewak);

		writeDebugStreamLine("Cycle: %d", cycle);

		// Save the distance for the next cycle
		PreviousDistance = CurrentDistance;

		wait1Msec(25);
	}
	BaseSpeed(0,0);
}
