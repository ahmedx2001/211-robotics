
#include "functions.c"
const int full = 2800;
const int half = 2100;
const int skill = 2200;

//++++++++++++++++++++PID Stuff++++++++++++++++++++
const bool debug = false;

//pid values
const float pVal = 6;
const float iVal = 0;
const float dVal = 6;

//PID variables
int error = 0;
int sumError = 0;
int slope = 0;
int lastError = 0;

int pChange = 0;
int iChange = 0;
int dChange = 0;
int tChange = 0;
int lastTotal = 0;

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
			error = (targetRPM - currentRPM)/10;
			if (debug) writeDebugStreamLine("Error: %d", error);
			sumError = sumError + error;

			//p calculations
			pChange = error * pVal;
			if (debug) writeDebugStreamLine("P Change: %d", pChange);

			//i calculations
			iChange = sumError * iVal;
			if (debug) writeDebugStreamLine("I Change: %d", iChange);

			//d calculations
			slope = error - lastError;
			dChange = slope * dVal;
			if (debug) writeDebugStreamLine("D Change: %d", dChange);

			//Total pid changes
			tChange = pChange + iChange + dChange;
			if (debug) writeDebugStreamLine("Total Change: %d\n", tChange);

			//Make sure motors doesnt run backwards
			if(tChange<0) tChange = 0;

			shooter(tChange);

			if(currentRPM >= targetRPM){
				SensorValue[ledSpeed] = 0;
			}
			else{
				SensorValue[ledSpeed] = 1;
			}

			if (targetRPM == full){
				SensorValue[ledFull] = 0;
				SensorValue[ledHalf] = 1;
			}
			else if(targetRPM == half){
				SensorValue[ledFull] = 1;
				SensorValue[ledHalf] = 0;
			}
			else{
				SensorValue[ledFull] = 1;
				SensorValue[ledHalf] = 1;
			}

			lastError = error;
			lastVal = val;
			lastTotal = tChange;
			wait1Msec(10);
		}
	}//while loop
}//task
