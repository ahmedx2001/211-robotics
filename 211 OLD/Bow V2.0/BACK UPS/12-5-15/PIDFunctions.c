#include "functions.c"

void PIDMove ( int distance, int gyro, int armVal, int armDelayDistance, int baseSpeed, int timeOut, bool spit, bool ignore, bool intake = false, int intakeSpeed = 127)
{
	long error = 99999;
	long speed = 0;
	long currentEncoder = 0;
	long leftSpeed = 0;
	long rightSpeed = 0;
	long gyroError = 0;
	long previousError = 0;
	long integral = 0;
	long integralTimer = 0;
	long end = 0;
	long armSpeed = 0;
	long currentArmVal = 0;
	long armError = 99999;
	long previousArmError = 0;
	long aKp = 150; // was 150
	long aKi = 5;
	long aKd = 620;//620; // was 620
	long Kp = 20;
	long Ki = 17;
	long Kd = 11;
	long derivative;
	long armIntegral = 0;
	long armDerivative = 0;
	long armIntegralTimer = 0;
	SensorValue[LeftEncoder] = 0;
	SensorValue[RightEncoder] = 0;
	//PIDTurn ( gyro, 0, 0, 0 ) ;
	Timer_Set(6,0);
	Timer_Set(1,0);
	SensorValue[LeftEncoder] = 0;
	SensorValue[RightEncoder] = 0;
	int gyroVal = SensorValue[Gyro];

	while (( ignore ? abs(error) > 100 : ((abs(error) > 30) || (abs(gyroError) > 50)) || end < 100) && Timer_Msecs(TOTAL_TIMER) < timeOut)
	{
		//** Move Base **//

		previousError = error ;
		if(abs(error) < 150)
		{
			if(integralTimer == 0)
			{
				Timer_Set(INTEGRAL_TIMER, 0);
				integralTimer = 1;
			}
			if(Timer_Msecs(INTEGRAL_TIMER) > 50)
			{
				integral += error/10 + 1;
				integralTimer = 0;
			}
		}
		if(abs(error) <= 30)
		{
			integral = 0;
		}
		error = distance - currentEncoder ;
		derivative = SmartMotorGetSpeed(MiddleLeftDrive);
		writeDebugStreamLine("Speed %d", derivative);
		speed = ((Kp*error) + (Ki*integral) + (Kd*derivative))/100 ;
		writeDebugStreamLine("speed: %d", speed);
		writeDebugStreamLine("error: %d", error);
		currentEncoder = (SensorValue[LeftEncoder] +  SensorValue[RightEncoder]) /2 ;
		gyroError = gyroVal - SensorValue[Gyro] ;
		/*if ( previousError == error )
		{
		stallCount ++ ;
		}
		else
		{
		stallCount = 0 ;
		}*/
		if( abs(previousError) - abs(error) == 0)
		{
			end++;
		}
		else
		{
			end = 0;
		}

		if(!ignore)
		{
			if (  gyroError > 0 )
			{
				if ( speed < 0 )
				{
					rightSpeed = speed + abs(gyroError)/2 ;
					leftSpeed = speed;
				}
				else if ( speed > 0 )
				{
					leftSpeed = speed - abs(gyroError)/2;
					rightSpeed = speed ;
				}
				else {
					rightSpeed = 20;
					leftSpeed = -20;
				}
			}
			else if ( gyroError < 0 )
			{
				if ( speed < 0 )
				{
					leftSpeed = speed + abs(gyroError)/2 ;
					rightSpeed = speed ;
				}
				else if ( speed > 0 )
				{
					rightSpeed = speed - abs(gyroError)/2 ;
					leftSpeed = speed;
				}
				else {
					rightSpeed = -20;
					leftSpeed = 20;
				}
			}
			if( gyroError == 0)
			{
				leftSpeed = speed;
				rightSpeed = speed;
			}
	  }
	  else
	  {
	  	leftSpeed = speed;
			rightSpeed = speed;
	  }
		if ( leftSpeed > baseSpeed )
		{
			leftSpeed = baseSpeed ;
		}
		else if ( leftSpeed < -baseSpeed )
		{
			leftSpeed = -baseSpeed ;
		}
		if ( rightSpeed > baseSpeed )
		{
			rightSpeed = baseSpeed ;
		}
		else if ( rightSpeed < -baseSpeed )
		{
			rightSpeed = -baseSpeed ;
		}
		writeDebugStreamLine("LeftSpeed: %d", leftSpeed);
		writeDebugStreamLine("rightSpeed: %d", rightSpeed);
		writeDebugStreamLine("speed: %d", speed);
		setDriveMotors (leftSpeed, rightSpeed ) ;
		//** Move Arm **//
		if(abs(currentEncoder) >= abs(armDelayDistance))
		{
			previousArmError = armError ;
			currentArmVal = SensorValue[Pot]  ;
			armError = armVal - currentArmVal ;
			if(abs(armError) < 150)
			{
				if(armIntegralTimer == 0)
				{
					Timer_Set(ARM_INTEGRAL_TIMER, 0);
					armIntegralTimer = 1;
				}
				if(Timer_Msecs(ARM_INTEGRAL_TIMER) > 100)
				{
					armIntegral += armError/10;
					armIntegralTimer = 0;
				}
			}
			if( armError - previousArmError != 0)
			{
				armDerivative = (armError - previousArmError) ;
			}
			else
			{
				armDerivative = 0;
			}
			if(abs(armError) < 10){
				armIntegral = 0;
			}
			armSpeed = ((aKp*armError) + (aKi*armIntegral) + (aKd*armDerivative))/100 ;
			//armSpeed = getPID(currentArm, armVal, 1, dT, armPreviousError, integral, derivative) ;
		}
		if(armVal == MIN_ARM)
		{
			armSpeed = 0;
		}

		moveArm(armSpeed);
		//** Update Intake **/
		if(intake)
		{
			setIntake(-intakeSpeed);
		}
		if(Timer_Msecs(AUTO_TIMER) > 14000 && spit)
		{
			setIntake(intakeSpeed);
		}
	}
	setIntake(0);
	setDriveMotors ( 0, 0 ) ;
	//moveArm(0,0,0);
	//PrintToScreen ( "Average Gyro: %f\n" , avgGyro ) ;
	//PrintToScreen ( "Max Gyro: %d\n" , maxGyro ) ;
	//PrintToScreen ( "Min Gyro: %d\n" , minGyro ) ;
}

void PIDTurn ( int gyroVal, int maxSpeed = 127)
{
	long dT = 0;
	long error = 99999;
	long previousError = 0;
	long currentGyro = 0;
	long speed = 0;
	long Rspeed = 0;
	long Lspeed = 0;
	long integral = 0;
	long derivative = 0;
	long integralTimer = 0;
	long totalTime = 0;
	Timer_Set(INTEGRAL_TIMER,0);
	Timer_Set(TOTAL_TIMER,0);
	long end = 0;
	while ( Abs(error) >= 30  || end < 50)
	{
		dT = Timer_Msecs(TOTAL_TIMER) ;
		totalTime += dT ;
		Timer_Set(1,0);
		if(abs(error) < 450)
		{
			if(integralTimer == 0)
			{
				Timer_Set(INTEGRAL_TIMER, 0);
				integralTimer = 1;
			}
			if(Timer_Msecs(INTEGRAL_TIMER) > 50)
			{
				if(error > 0){
					integral += error/10 + 1;
				}
				else if (error < 0){
					integral += error/10 - 1;
				}
				integralTimer = 0;
			}
		}
		if(abs(error) < 20){
			integral = 0;
		}
		previousError = error ;
		error = gyroVal - SensorValue[Gyro];
		derivative = SmartMotorGetSpeed(MiddleLeftDrive);
		if(Abs(derivative) <= 1){
			end++;
			} else {
			end = 0;
		}
		speed = (((200*error) + (200*integral) + (310*derivative))/1000  ;

		writeDebugStreamLine("Error: %d", error);
		if ( speed > maxSpeed )
		{
			speed = maxSpeed ;
		}
		else if ( speed < -maxSpeed )
		{
			speed = -maxSpeed ;
		}
		/*if ( speed > 0 && speed < 30 )
		{
		speed = 30 ;
		}
		else if ( speed < 0 && speed > -30 )
		{
		speed = -30 ;
		}*/
		writeDebugStreamLine("Speed: %d", speed);
		if ( error > 0 )
		{
			Rspeed = Abs(speed) ;
			Lspeed = -Abs(speed) ;
		}
		else if ( error < 0 )
		{
			Rspeed =  -Abs(speed) ;
			Lspeed =  Abs(speed) ;
		}
		setDriveMotors ( Lspeed, Rspeed ) ;
	}
	setDriveMotors ( 0, 0 ) ;
}


void moveArmStab ( int joystick, int leftPot, int rightPot, int fixedVal )
{
	int speed = joystick;
	int leftSpeed = speed;
	int rightSpeed = speed;
	int ratio = 1;
	int testing = 0;
	if(testing == 1)
	{
		//PrintToScreen("Hold Position: %d", holdPosition);
		//SetLCDText(1,1,"Hold Position: %d", holdPosition);
	}
	if(holdPosition == -1)
	{
		holdPosition = (leftPot + rightPot)/2;
	}
	if(fixedVal != -1){
		holdPosition = fixedVal;
	} else if(Abs(speed) > 10)
	{
		holdPosition = (leftPot + rightPot)/2;
	}
	if ( speed > 15 )
	{
		if ( leftPot > rightPot + 5 )
		{
			leftSpeed = speed - (leftPot - rightPot)*ratio;
		}
		else if ( leftPot < rightPot - 5 )
		{
			rightSpeed = speed - (rightPot - leftPot)*ratio;
		}

		if ( leftSpeed > 10 && leftPot > MAX_ARM )
		{
			leftSpeed = 10;
		}
		else if ( leftSpeed < 0 && leftPot < MIN_ARM )
		{
			leftSpeed = -15;
		}
		if ( rightSpeed > 10 && rightPot > MAX_ARM )
		{
			rightSpeed = 10;
		}
		else if ( rightSpeed < 0 && rightPot < MIN_ARM )
		{
			rightSpeed = -15;
		}
	}
	else if ( speed < -15 )
	{
		if ( leftPot < rightPot - 5 )
		{
			leftSpeed = speed + (rightPot - leftPot)*ratio;
		}
		else if ( leftPot > rightPot + 5 )
		{
			rightSpeed = speed + (leftPot - rightPot)*ratio;
		}

		if ( leftSpeed > 10 && leftPot > MAX_ARM )
		{
			leftSpeed = 10;
		}
		else if ( leftSpeed < 0 && leftPot < MIN_ARM )
		{
			leftSpeed = -15;
		}
		if ( rightSpeed > 10 && rightPot > MAX_ARM )
		{
			rightSpeed = 10;
		}
		else if ( rightSpeed < 0 && rightPot < MIN_ARM )
		{
			rightSpeed = -15;
		}
	}
	else
	{
		if((leftPot + rightPot)/2 < 350){
			leftSpeed = -15 + (holdPosition - leftPot)*ratio;
			rightSpeed = -15 + (holdPosition - rightPot)*ratio;
		}
		else{
			leftSpeed = 10 + (holdPosition - leftPot)*ratio;
			rightSpeed = 10 + (holdPosition - rightPot)*ratio;
		}
		if ( leftSpeed > 10 && leftPot > MAX_ARM )
		{
			leftSpeed = 10;
		}
		else if ( leftSpeed < 0 && leftPot < MIN_ARM )
		{
			leftSpeed = -15;
		}
		if ( rightSpeed > 10 && rightPot > MAX_ARM )
		{
			rightSpeed = 10;
		}
		else if ( rightSpeed < 0 && rightPot < MIN_ARM )
		{
			rightSpeed = -15;
		}
		//leftSpeed = 10;
		//rightSpeed = 10;
	}
	if ( leftSpeed > 127 )
	{
		leftSpeed = 127;
	}
	if ( rightSpeed > 127 )
	{
		rightSpeed = 127;
	}
	if ( leftSpeed < -127 )
	{
		leftSpeed = -127;
	}
	if ( rightSpeed < -127 )
	{
		rightSpeed = -127;
	}
	//ClearGD ( 2 , 0 , 2 , 79 , 0) ;
	//PrintTextToGD ( 2 , 0 , 0 , "Left Speed: %d\n                 " , leftSpeed ) ;
	//ClearGD ( 3 , 0 , 3 , 79 , 0) ;
	//PrintTextToGD ( 3 , 0 , 0 , "Right Speed: %d\n                 " , rightSpeed ) ;
	//ClearGD ( 4 , 0 , 4 , 79 , 0) ;
	//PrintTextToGD ( 4 , 0 , 0 , "Joystick: %d\n                    " , speed ) ;
	moveArm(leftSpeed, rightSpeed);
	//PrintToScreen("Left Speed: %d Right Speed: %d\n", leftSpeed, rightSpeed);
}

void LiftArm(int val)
{
	while(SensorValue[Pot] < val){
		moveArmStab(127, SensorValue[Pot], SensorValue[Pot], -1);
	}
}
