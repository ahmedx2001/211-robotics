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


void DriveTest(int Distance){
	SensorValue(TurnGyro) = 0;
	while(SensorValue(RightEncoder) < Distance){
		BaseSpeed(127-(SensorValue(TurnGyro)*10), 127+(SensorValue(TurnGyro)*10));
	}
}




////// PID drive //////
void Drive (int Distance) {
	long error = 99999;
	float KP = .35;
	float KD = 2.1;
	float KG = 10;
	long Velocity = 0;
	long MotorSpeed = 127;
	long CurrentDistance;
	long PreviousDistance = 0;
	SensorValue(LeftEncoder) = 0;
	SensorValue(RightEncoder) = 0;
	SensorValue(TurnGyro) = 0;
	int GyroCorrect = 0;
	int TurnSpeed = 0;
	int cycle = 0;

	while (cycle < 20) {
		CurrentDistance = ((SensorValue(RightEncoder)-SensorValue(LeftEncoder))/2);

		GyroCorrect = (abs(SensorValue(TurnGyro))*KG);

		// P = calculate the error
		error = Distance - CurrentDistance;

		// D = Calculate the speed
		Velocity = CurrentDistance - PreviousDistance;

		// I = how long we have been away
		if (abs(error) < 5){
			// If we are close add to cycle
			cycle = cycle + 1;
		}
		else if (abs(Velocity) < 5){
			// If we are going slow
			cycle = cycle + 1;
		}

		// Calculates how fast to move the robot
		MotorSpeed = (error * KP) - (Velocity * KD);
		TurnSpeed = ((pow(1.1, abs(SensorValue(TurnGyro))))-1);







		if (SensorValue(TurnGyro) > 50 && MotorSpeed > 127){
			BaseSpeed(127 - 20, 127 + 20);
			motor[Intake] = 127;
		}
		else if (SensorValue(TurnGyro) < -50 && MotorSpeed > 127){
			BaseSpeed(127 + 20, 127 - 20);
			motor[Intake] = -127;
		}
		if (SensorValue(TurnGyro) > 50 && MotorSpeed < 127){
			BaseSpeed(MotorSpeed - 20, MotorSpeed + 20);
			motor[Intake] = 127;
		}
		else if (SensorValue(TurnGyro) < -50 && MotorSpeed < 127){
			BaseSpeed(MotorSpeed + 20, MotorSpeed - 20);
			motor[Intake] = -127;
		}
		else{
			BaseSpeed(MotorSpeed, MotorSpeed);
			motor[Intake] = 0;
		}

		writeDebugStreamLine("Cycle: %d", cycle);

		// Save the distance for the next cycle
		PreviousDistance = CurrentDistance;

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
			motor[Tension]   = 0;
			wait1Msec(2000);
			if (vexRT[Btn8U] == 1 && vexRT[Btn8R] == 1){
				SensorValue(TensionEncoder) = 0;
			}
		}
		else if(vexRT[Btn8R] == 1){
			motor[Tension]   = 100;
		}
		else if(vexRT[Btn8L] == 1){
			motor[Tension]   = -80;
		}

		else if(vexRT[Btn8U] == 1){
			while(-SensorValue(TensionEncoder) > 0){
				motor[Tension] = 127;
			}
		}

		else if(vexRT[Btn8D] == 1){
			if (-SensorValue(TensionEncoder) < 15){
				while(-SensorValue(TensionEncoder) < 700){
					motor[Tension] = -127;
				}
			}
			else if (-SensorValue(TensionEncoder) > 480 && -SensorValue(TensionEncoder) < 840){
				motor[Tension] = -100;
				wait1Msec(1000);
				motor[Tension] = 0;
			}
			else if (-SensorValue(TensionEncoder) > 800){
				while(-SensorValue(TensionEncoder) >  725){
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
