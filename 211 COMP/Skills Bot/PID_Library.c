
//pid vlaues
const long pVal = 1;
const long iVal = 0.045;
const long dVal = 0;

//cm pre encoder ticks
const long cmPreTick = 25/360;

//target distance
int targetDis;


//left current distance traveled
long left_currentDis;

// left error values
long left_error;
long left_sumError;
long left_slope;
long left_lastError;

//left change values
int left_pChange;
int left_iChange;
int left_dChange;
int left_tChange;

//right current distance traveled
long right_currentDis;

//right error values
long right_error;
long right_sumError;
long right_slope;
long right_lastError;

//right change values
int right_pChange;
int right_iChange;
int right_dChange;
int right_tChange;

//task for left pid control
task pidLeft(){
	while(true){

		//current distance calculation
		left_currentDis = SensorValue[LeftEncoder] * cmPreTick;

		//error
		left_error = targetDis - left_currentDis;
		left_sumError = left_sumError + left_error;

		//p change
		left_pChange = left_error * pVal;

		//i change
		left_iChange = left_sumError * iVal;

		//d change
		left_slope = left_error - left_lastError;
		left_dChange = left_slope * dVal;

		//total change
		left_tChange = left_pChange + left_iChange + left_dChange;

		//update motor
		motor[LeftDrive] = left_tChange;


		left_lastError = left_error;
		wait1Msec(50);
	}//while loop
}//left pid task

//task for right pid control
task pidRight(){
	while(true){

		//current distance calculation
		right_currentDis = SensorValue[RightEncoder] * cmPreTick;

		//error
		right_error = targetDis - right_currentDis;
		right_sumError = right_sumError + right_error;

		//p change
		right_pChange = right_error * pVal;

		//i change
		right_iChange = right_sumError * iVal;

		//d change
		right_slope = right_error - right_lastError;
		right_dChange = right_slope * dVal;

		//total change
		right_tChange = right_pChange + right_iChange + right_dChange;

		//update motor
		motor[RightDrive] = right_tChange;


		right_lastError = right_error;
		wait1Msec(50);
	}//while loop
}//right pid task

//set target distance
void setTarget(int target){
	targetDis = target;
}

//clear all values;
void clearVals(){
	left_error = 0;
	left_sumError = 0;
	left_slope = 0;
	left_lastError = 0;

	left_pChange = 0;
	left_iChange = 0;
	left_dChange = 0;
	left_tChange = 0;

	left_currentDis = 0;

	SensorValue[LeftEncoder] = 0;

	right_error = 0;
	right_sumError = 0;
	right_slope = 0;
	right_lastError = 0;

	right_pChange = 0;
	right_iChange = 0;
	right_dChange = 0;
	right_tChange = 0;

	right_currentDis = 0;

	SensorValue[RightEncoder] = 0;
}
