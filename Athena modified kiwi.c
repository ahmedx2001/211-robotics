#pragma config(Motor,  port2,           w1_front_right, tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           w2_back,       tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           w3_front_left, tmotorVex393TurboSpeed_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

void pre_auton(){
	bStopTasksBetweenModes = true;
}

task autonomous(){

}


task usercontrol()
{
	int X, Y, R, S = 0;
	while (true)
	{
		X = vexRT[Ch3];
		Y = vexRT[Ch2];
		R = vexRT[Ch1];


		motor[w1_front_right] = -1/2 * X - sqrt(3)/2 * Y + R;//why do you need a -
		motor[w3_front_left] = -1/2 * X + sqrt(3)/2 * Y + R;
		motor[w2_back] = X + R;

	}
}
