///////////////// AUTO LIBRARY ////////////////////







// AUTO SKILLS
void RedSkills(){
	// Code for red side first skills run
	motor[Intake] = 127;
	wait1Msec(200);
	Bow(100);
	wait1Msec(25000);
	Bow(0);
	TurnLeft(911);
	Drive(4000);
	TurnRight(870);
	motor[Intake] = 127;
	wait1Msec(100);
	Bow(100);
	wait1Msec(25000);
	Bow(0);
	motor[Intake] = 0;
}
