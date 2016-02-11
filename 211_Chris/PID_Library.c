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

task pid(){											//PID task
	while(true){
		if (!vexRT[Btn6UXmtr2]){
			//++++++++++++++++++++Current RPM++++++++++++++++++++
			val = SensorValue[ShooterEncoder];
			diff = val - lastVal;
			currentRPM = diff*100*60*25/360;
			//-----------------End Current RPM ------------------

			//write to debug stream
			if (debug) writeDebugStreamLine("Current RPM: %d", currentRPM);
			if (debug) writeDebugStreamLine("Tagrget RPM: %d", targetRPM);

			//get error
			error = targetRPM - currentRPM;
			if (debug) writeDebugStreamLine("Error: %d", error);
			sumError = sumError + error;

			datalogDataGroupStart();

			//p calculations
			pChange = error * pVal;
			if (debug) writeDebugStreamLine("P Change: %d", pChange);
			datalogAddValue(0, pChange);

			//i calculations
			iChange = sumError * iVal;
			if (debug) writeDebugStreamLine("I Change: %d", iChange);
			datalogAddValue(1, iChange);

			//d calculations
			slope = error - lastError;
			dChange = slope * dVal;
			if (debug) writeDebugStreamLine("D Change: %d", dChange);
			datalogAddValue(2, dChange);

			//Total pid changes
			tChange = pChange + iChange + dChange;
			if (debug) writeDebugStreamLine("Total Change: %d\n", tChange);
			datalogAddValue(3, tChange);

			datalogDataGroupEnd();


			//Make sure motors doesnt run backwards
			if(tChange<0) tChange = 0;

			//Update Motor
			shooter(tChange);

			lastError = error;
			lastVal = val;
			wait1Msec(10);
		}
	}//while loop
}//task
