void PIDMove ( int distance, int baseSpeed)
{
	long error = 99999;
	long speed = 0;
	long currentEncoder = 0;
	long previousEncoder = 0;
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
	Timer_Set(INTEGRAL_TIMER,0);
	Timer_Set(TOTAL_TIMER,0);
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
		// P
		error = distance - currentEncoder ;
		// D = Calculate the speed
		derivative = = currentEncoder - ;
		currentEncoder = (SensorValue[LeftEncoder] +  SensorValue[RightEncoder]) /2 ;
		gyroError = gyroVal - SensorValue[Gyro] ;
		if (abs(previousError - error) < 5)
		{
			stallCount ++ ;
		}
		else
		{
			stallCount = 0 ;
		}

		if( abs(previousError) - abs(error) == 0)
		{
			end++;
		}
		else
		{
			end = 0;
		}



