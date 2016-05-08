//////////////////// PID LIBRARY AND ALL THE FUNCTIONS TO RUN THE ROBOT ////////////////////


////// MOVES Bow //////
void Bow(int BowSpeed){
	motor[BowLeft] = BowSpeed;
	motor[BowRight] = BowSpeed;
}

////// MOVES THE DRIVE BASE //////
void BaseSpeed(int LeftSpeed, int RightSpeed) {
	motor[Left1]  = LeftSpeed;
	motor[Left2]  = LeftSpeed;
	motor[Left3]  = LeftSpeed;
	motor[Right1]   = RightSpeed;
	motor[Right2]   = RightSpeed;
	motor[Right3]   = RightSpeed;
}

/////// SHOOT BALLS ///////
void Balls(int Time){
	motor[Intake] = 127;
	wait1Msec(200);
	Bow(127);
	wait1Msec(Time);
	Bow(0);
}

////// LEFT TEST ///////
void LeftTest(){
	motor[Left1] = 127;
	wait1Msec(1000);
	motor[Left1] = 0;
	motor[Left2] = 127;
	wait1Msec(1000);
	motor[Left2] = 0;
	motor[Left3] = 127;
	wait1Msec(1000);
	motor[Left3] = 0;
	wait1Msec(2000);
	motor[BowLeft] = 127;
	wait1Msec(500);
	motor[BowLeft] = 0;
}

////// RIGHT TEST //////
void RightTest(){
	motor[Right1] = 127;
	wait1Msec(1000);
	motor[Right1] = 0;
	motor[Right2] = 127;
	wait1Msec(1000);
	motor[Right2] = 0;
	motor[Right3] = 127;
	wait1Msec(1000);
	motor[Right3] = 0;
	wait1Msec(2000);
	motor[BowRight] = 127;
	wait1Msec(500);
	motor[BowRight] = 0;
}




////// PID drive //////
void Drive(int DistanceIN) {
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
	int Distance;
	int SpeedCorrect = 0;
	int MotorSpeed = 0;
	int cycle = 0;

	Distance = DistanceIN / 0.024;

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

		if (SensorValue(TurnGyro) < -2){
			// Edit how much is added to change how fast it reacts
			SpeedCorrect = SpeedCorrect - 0.7;
		}
		else if (SensorValue(TurnGyro) > 2){
			SpeedCorrect = SpeedCorrect + 0.7;
		}

		// Calculates how fast to move the robot
		MotorSpeed = (error * KP) + (Integral * KI) - (Velocity * KD);

		BaseSpeed(MotorSpeed - SpeedCorrect, MotorSpeed + SpeedCorrect);

		writeDebugStreamLine("Cycle: %d", cycle);

		// Save the distance for the next cycle
		PreviousDistance = CurrentDistance;

		wait1Msec(25);
	}
	BaseSpeed(0,0);
}


////// PID drive //////
void DriveBACK(int DistanceIN) {
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
	int Distance;
	int SpeedCorrect = 0;
	int MotorSpeed = 0;
	int cycle = 0;

	Distance = abs(DistanceIN / 0.024);

	while (abs(error) > 5) {
		CurrentDistance = (abs((SensorValue(RightEncoder)-SensorValue(LeftEncoder))/2));

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

		if (SensorValue(TurnGyro) < -2){
			// Edit how much is added to change how fast it reacts
			SpeedCorrect = SpeedCorrect + 0.7;
		}
		else if (SensorValue(TurnGyro) > 2){
			SpeedCorrect = SpeedCorrect - 0.7;
		}

		// Calculates how fast to move the robot
		MotorSpeed = (error * KP) + (Integral * KI) - (Velocity * KD);

		BaseSpeed(-MotorSpeed + SpeedCorrect, -MotorSpeed - SpeedCorrect);

		writeDebugStreamLine("Cycle: %d", cycle);

		// Save the distance for the next cycle
		PreviousDistance = CurrentDistance;

		wait1Msec(25);
	}
	BaseSpeed(0,0);
}

////// PID TURN //////
void TurnRight (int Angle) {
	long error = 99999;
	float KP = 0.35;
	float KD = 1.5;
	float KI = 1;
	long Velocity = 0;
	long Integral = 0;
	long PreviousAngle = 0;
	SensorValue(TurnGyro) = 0;
	int MotorSpeed = 0;
	int cycle = 0;

	while (abs(error) > 10) {
		// P = calculate the error
		error = Angle - SensorValue(TurnGyro);

		// D = Calculate the speed
		Velocity = SensorValue(TurnGyro) - PreviousAngle;

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

		// I = how long we have been away
		if (abs(error) < 10){
			// If we are close add to cycle
			cycle = cycle + 1;
		}
		else if (abs(Velocity) < 10){
			// If we are going slow
			cycle = cycle + 1;
		}

		// Calculates how fast to move the robot
		MotorSpeed = (error * KP) + (Integral * KI) - (Velocity * KD);

		BaseSpeed(MotorSpeed, -MotorSpeed);

		writeDebugStreamLine("Cycle: %d", cycle);

		// Save the distance for the next cycle
		PreviousAngle = SensorValue(TurnGyro);

		wait1Msec(25);
	}
	BaseSpeed(0,0);
}


////// PID TURN //////
void TurnLeft (int Angle) {
	long error = 99999;
	float KP = 0.35;
	float KD = 1.5;
	float KI = 1;
	long Velocity = 0;
	long Integral = 0;
	long PreviousAngle = 0;
	SensorValue(TurnGyro) = 0;
	int MotorSpeed = 0;
	int cycle = 0;

	while (abs(error) > 10) {
		// P = calculate the error
		error = Angle + SensorValue(TurnGyro);

		// D = Calculate the speed
		Velocity = -SensorValue(TurnGyro) - PreviousAngle;

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

		// I = how long we have been away
		if (abs(error) < 10){
			// If we are close add to cycle
			cycle = cycle + 1;
		}
		else if (abs(Velocity) < 10){
			// If we are going slow
			cycle = cycle + 1;
		}

		// Calculates how fast to move the robot
		MotorSpeed = (error * KP) + (Integral * KI) - (Velocity * KD);

		BaseSpeed(-MotorSpeed, MotorSpeed);

		writeDebugStreamLine("Cycle: %d", cycle);

		// Save the distance for the next cycle
		PreviousAngle = -SensorValue(TurnGyro);

		wait1Msec(25);
	}
	BaseSpeed(0,0);
}


////// PID TURN //////
void TurnLeftNoZero(int Angle) {
	long error = 99999;
	float KP = 0.35;
	float KD = 1.5;
	float KI = 1;
	long Velocity = 0;
	long Integral = 0;
	long PreviousAngle = 0;
	int MotorSpeed = 0;
	int cycle = 0;

	while (abs(error) > 10) {
		// P = calculate the error
		error = Angle + SensorValue(TurnGyro);

		// D = Calculate the speed
		Velocity = -SensorValue(TurnGyro) - PreviousAngle;

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

		// I = how long we have been away
		if (abs(error) < 10){
			// If we are close add to cycle
			cycle = cycle + 1;
		}
		else if (abs(Velocity) < 10){
			// If we are going slow
			cycle = cycle + 1;
		}

		// Calculates how fast to move the robot
		MotorSpeed = (error * KP) + (Integral * KI) - (Velocity * KD);

		BaseSpeed(-MotorSpeed, MotorSpeed);

		writeDebugStreamLine("Cycle: %d", cycle);

		// Save the distance for the next cycle
		PreviousAngle = -SensorValue(TurnGyro);

		wait1Msec(25);
	}
	BaseSpeed(0,0);
}




////// Set the tension to values while driving //////
task TensionButtons()
{
	while(true)
	{
		/////// TENSION ///////
		if(vexRT[Btn8U] == 1 && vexRT[Btn8R] == 1){
			motor[Tension] = 0;
			wait1Msec(1000);
			if(vexRT[Btn8U] == 1 && vexRT[Btn8R] == 1){
				SensorValue(TensionEncoder) = 0;
			}
		}
		if(vexRT[Btn8R] == 1){
			motor[Tension]   = 100;
		}
		else if(vexRT[Btn8L] == 1){
			motor[Tension]   = -80;
		}

		else if(vexRT[Btn8U] == 1){
			while(-SensorValue(TensionEncoder) > 0 && vexRT[Btn8R] == 0){
				motor[Tension] = 127;
			}
		}

		else if(vexRT[Btn8D] == 1){
			if (-SensorValue(TensionEncoder) < 15){
				while(-SensorValue(TensionEncoder) < 700 && vexRT[Btn8R] == 0){
					motor[Tension] = -127;
				}
			}
			else if (-SensorValue(TensionEncoder) > 480 && -SensorValue(TensionEncoder) < 840){
				motor[Tension] = -100;
				wait1Msec(1000);
				motor[Tension] = 0;
			}
			else if (-SensorValue(TensionEncoder) > 800){
				while(-SensorValue(TensionEncoder) >  725 && vexRT[Btn8R] == 0){
					motor[Tension] = 127;
				}
			}
			else {
				motor[Tension]   = 0;
			}
		}

		else {
			motor[Tension]   = 0;
		}


	}
}


task AutoTension(){
	while(-SensorValue(TensionEncoder) < 285){
		motor[Tension] = -127;
	}
	motor[Tension] = 0;
}
