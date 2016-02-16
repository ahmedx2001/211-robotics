void
shooter( int value )
{
	motor[TLShooter] = value;
	motor[TRShooter] = value;

	motor[MLShooter] = value;
	motor[MRShooter] = value;

	motor[BLShooter] = value;
	motor[BRShooter] = value;

}


const int full = 3350;
const int half = 2300;

const bool debug = true;

//pid values
const float pVal = 0.7;
const float iVal = 0.003;
const float dVal = 0.6;

//PID variables
int error = 0;
int sumError = 0;
int slope = 0;
int lastError = 0;

int pChange = 0; //P Change
int iChange = 0; //I Change
int dChange = 0; //D Change
int tChange = 0; //Total Change

//RPM Calculation Variables
int targetRPM = 0;
int lastVal = 0;
int val = 0;
int diff = 0;
int currentRPM;

void getRPM(){
	val = SensorValue[ShooterEncoder];
	diff = val - lastVal;
	currentRPM = diff*100*60*25/360;
	lastVal = val;
}

void getChange(){
	//get error
	error = targetRPM - currentRPM;
	if (debug) writeDebugStreamLine("Error: %d", error);

	//p calculations
	pChange = error * pVal;
	if (debug) writeDebugStreamLine("P Change: %d", pChange);


	//i calculations
	sumError = sumError + error;
	iChange = sumError * iVal;
	if (debug) writeDebugStreamLine("I Change: %d", iChange);


	//d calculations
	slope = error - lastError;
	dChange = slope * dVal;
	lastError = error;
	if (debug) writeDebugStreamLine("D Change: %d", dChange);


	//Total pid changes
	tChange = pChange + iChange + dChange;
	if (debug) writeDebugStreamLine("Total Change: %d\n", tChange);

}

task pid(){											//PID task
	while(true){
		if (!vexRT[Btn6UXmtr2]){

			//get current RPM
			getRPM();

			//write to debug stream
			if (debug) writeDebugStreamLine("Current RPM: %d", currentRPM);
			if (debug) writeDebugStreamLine("Tagrget RPM: %d", targetRPM);

			//get changes
			getChange();

			//Make sure motors doesnt run
			if(tChange<0) tChange = 0;

			//Update Motor
			shooter(tChange);
			wait1Msec(10);
		}
	}//while loop
}//task
