#pragma config(Sensor, in1,    BowPot,         sensorPotentiometer)
#pragma config(Sensor, dgtl1,  TensionEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  Ramps,          sensorDigitalOut)
#pragma config(Sensor, dgtl7,  RightLift,      sensorDigitalOut)
#pragma config(Sensor, dgtl8,  LeftLift,       sensorDigitalOut)
#pragma config(Sensor, dgtl11, BowEncoder,     sensorQuadEncoder)
#pragma config(Motor,  port1,           Tension,       tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           Left1,         tmotorVex393TurboSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port3,           Left2,         tmotorVex393TurboSpeed_MC29, openLoop, reversed, driveLeft)
#pragma config(Motor,  port4,           Left3,         tmotorVex393TurboSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port5,           Right1,        tmotorVex393TurboSpeed_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port6,           Right2,        tmotorVex393TurboSpeed_MC29, openLoop, driveRight)
#pragma config(Motor,  port7,           Right3,        tmotorVex393TurboSpeed_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port8,           BowLeft,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           BowRight,      tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          Intake,        tmotorVex393HighSpeed_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "Functions.c"


void FourBall(){
	SensorValue(TensionEncoder) = 0;
	SensorValue(BowEncoder) = 0;
	int LastBowValue = 0;

	Bow(127);
	wait1Msec(30);
	while(-SensorValue(BowEncoder) < 150 ){
		if(-SensorValue(BowEncoder) - LastBowValue < 10){
			Bow(127);
		}
		else{
			Bow(0);
		}
		LastBowValue = -SensorValue(BowEncoder);
		wait1Msec(30);
	}
	Bow(0);


	motor(Intake) = 127;
	wait1Msec(400);
	LastBowValue = -SensorValue(BowEncoder);
	Bow(127);
	wait1Msec(30);
	while(-SensorValue(BowEncoder) < 510 ){
		if(-SensorValue(BowEncoder) - LastBowValue > 10){
			Bow(127);
		}
		else{
			Bow(0);
		}
		LastBowValue = -SensorValue(BowEncoder);
		wait1Msec(30);
	}
	Bow(0);


	motor(Intake) = 0;
}





void pre_auton()
{
	bStopTasksBetweenModes = true;

}





task autonomous()
{
	FourBall();
}


task usercontrol()
{
	Loader(0);
	startTask(LCD);
	startTask(TensionButtons);
	int IntakeCycles = 0;

	while(1==1){

		////// DRIVE STICK //////
		motor[Left1]  = (vexRT[Ch3]+vexRT[Ch4]);
		motor[Left2]  = (vexRT[Ch3]+vexRT[Ch4]);
		motor[Left3]  = (vexRT[Ch3]+vexRT[Ch4]);
		motor[Right1]   = (vexRT[Ch3]-vexRT[Ch4]);
		motor[Right2]   = (vexRT[Ch3]-vexRT[Ch4]);
		motor[Right3]   = (vexRT[Ch3]-vexRT[Ch4]);

		////// Bow //////
		motor[BowLeft]  = (vexRT[Ch2]);
		motor[BowRight]  = (vexRT[Ch2]);


		/////// INTAKE ////////
		if(vexRT[Btn6U] == 1){
			motor[Intake]   = 127;
		}
		else if(vexRT[Btn6D] == 1){
			if (IntakeCycles < 500){
				motor[Intake] = 0;
			}
			IntakeCycles++;
			if (IntakeCycles > 500){
				motor[Intake]   = -127;
			}
		}
		else{
			if(IntakeCycles > 250){
				motor[Intake]   = 0;
			}
			IntakeCycles = 0;
		}




		if(vexRT[Btn7U] == 1 && vexRT[Btn7L] == 1){
			SensorValue(Ramps) = 1;
		}
		else if (vexRT[Btn7U] == 1){
			SensorValue(Ramps) = 0;
		}
		else if(vexRT[Btn7R] == 1 && vexRT[Btn7D] == 1){
			SensorValue(LeftLift) = 1;
			SensorValue(RightLift) = 1;
		}
		else if (vexRT[Btn7R] == 1){
			SensorValue(LeftLift) = 0;
			SensorValue(RightLift) = 0;
		}
	}
}
