#pragma config(Motor,  port5,           LeftDrive,     tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           RightDrive,    tmotorVex393TurboSpeed_MC29, openLoop, reversed)

task main()
{
	while(true){
		motor[LeftDrive]  = (vexRT[Ch3] + vexRT[Ch4] - vexRT[Ch2] + vexRT[Ch1]);
		motor[RightDrive]   = (vexRT[Ch3] - vexRT[Ch4] - vexRT[Ch2] - vexRT[Ch1]);

	}
}
