void shooter(int value){
	motor[ LeftShooter1 ] = abs(value);
	motor[ LeftShooter2 ] = abs(value);
	motor[ LeftShooter3 ] = abs(value);

	motor[ RightShooter1 ] = abs(value);
	motor[ RightShooter2 ] = abs(value);
	motor[ RightShooter3 ] = abs(value);
}

float map(float ival, float imin, float imax, float omin, float omax){return (omax-omin) * (ival-imin)/(imax-imin) + omin;}

const int full = 3100;
const int half = 2300;

//++++++++++++++++++++PID Stuff++++++++++++++++++++
const bool debug = false;

//pid values
float pVal = 0.7;
float iVal = 0;
float dVal = 0;

//PID variables
int error = 0;
int sumError = 0;
int slope = 0;
int lastError = 0;

int pChange = 0;
int iChange = 0;
int dChange = 0;
int tChange = 0;

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

			//++++++++++++++++++++PID Value++++++++++++++++++++
			pVal = map(SensorValue[p],0,127,0,1);
			iVal = map(SensorValue[i],0,127,0,1);
			dVal = map(SensorValue[d],0,127,0,1);

			if (debug) writeDebugStreamLine("P Value: %d", pVal);
			if (debug) writeDebugStreamLine("I Value: %d", iVal);
			if (debug) writeDebugStreamLine("D Value: %d", dVal);

			//-----------------End PID Value ------------------

			//write to debug stream
			if (debug) writeDebugStreamLine("Current RPM: %d", currentRPM);
			if (debug) writeDebugStreamLine("Tagrget RPM: %d", targetRPM);

			//get error
			error = targetRPM - currentRPM;
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

			//Update Motor
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
			wait1Msec(10);
		}
	}//while loop
}//task

//---------------------End PID---------------------
