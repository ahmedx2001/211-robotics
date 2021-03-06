#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    BowPot,         sensorPotentiometer)
#pragma config(Sensor, dgtl1,  TensionEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  Ramps,          sensorDigitalOut)
#pragma config(Sensor, dgtl7,  RightLift,      sensorDigitalOut)
#pragma config(Sensor, dgtl8,  LeftLift,       sensorDigitalOut)
#pragma config(Sensor, dgtl11, BowEncoder,     sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           Tension,       tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           Left1,         tmotorVex393TurboSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port3,           Left2,         tmotorVex393TurboSpeed_MC29, openLoop, reversed, driveLeft, encoderPort, I2C_1)
#pragma config(Motor,  port4,           Left3,         tmotorVex393TurboSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port5,           Right1,        tmotorVex393TurboSpeed_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port6,           Right2,        tmotorVex393TurboSpeed_MC29, openLoop, driveRight, encoderPort, I2C_2)
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


void PIDdrive(int Distance, int Speed){
	slaveMotor(Left1, Left3);
	slaveMotor(Left2, Left3);

	slaveMotor(Right1, Right3);
	slaveMotor(Right2, Right3);

	moveMotorTarget(Left3, Distance, Speed, true);
	moveMotorTarget(Right3, Distance, Speed, true);

	while(getMotorTargetCompleted(Left3) == false || getMotorTargetCompleted(Right3) == false)
	{
	}
}


void FourBall(){
	SensorValue(TensionEncoder) = 0;
	SensorValue(BowEncoder) = 0;

	while(-SensorValue(BowEncoder) < 150){
		Bow(127);
	}
	Bow(0);
	motor(Intake) = 100;
	wait1Msec(600);
	while(SensorValue(BowEncoder) > -600){
		Bow(80);
	}
	Bow(0);
	motor(Intake) = -80;
	wait1Msec(350);
	motor(Intake) = 50;
	while(SensorValue(BowEncoder) > -900){
		Bow(90);
	}
	Bow(0);
	motor(Intake) = -80;
	wait1Msec(350);
	motor(Intake) = 50;
	while(SensorValue(BowEncoder) > -1260){
		Bow(90);
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
	//PIDdrive(1000, 80);

	FourBall();
}


task usercontrol()
{
	Loader(0);
	startTask(LCD);
	startTask(TensionButtons);
	int TurnSpeed = 0;
	int TurnCycles = 0;
	int IntakeCycles = 0;

	while(1==1){

		////// DRIVE STICK //////
		motor[Left1]  = (vexRT[Ch3]+TurnSpeed);
		motor[Left2]  = (vexRT[Ch3]+TurnSpeed);
		motor[Left3]  = (vexRT[Ch3]+TurnSpeed);
		motor[Right1]   = (vexRT[Ch3]-TurnSpeed);
		motor[Right2]   = (vexRT[Ch3]-TurnSpeed);
		motor[Right3]   = (vexRT[Ch3]-TurnSpeed);

		////// TURN STICK //////
		if(vexRT[Ch4] > 15){
			TurnCycles++;
			if(TurnCycles < 1000){
				TurnSpeed = (vexRT[Ch4] * (TurnCycles * .001));
			}
			else{
				TurnSpeed = vexRT[Ch4];
			}
		}
		else if (vexRT[Ch4] < -15){
			TurnCycles++;
			if(TurnCycles < 1000){
				TurnSpeed = (vexRT[Ch4] * (TurnCycles * .001));
			}
			else{
				TurnSpeed = vexRT[Ch4];
			}
		}
		else {
			TurnCycles = 0;
			TurnSpeed = 0;
		}

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
