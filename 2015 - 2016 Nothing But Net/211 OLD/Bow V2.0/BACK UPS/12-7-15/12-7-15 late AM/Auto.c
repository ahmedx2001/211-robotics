

void Balls(int Time){
	motor[Intake] = 127;
	wait1Msec(200);
	Bow(127);
	wait1Msec(Time);
	Bow(0);
}

void Skills(){
	Balls(4000);
	RightTurn(980);
	Drive(3950);
	LeftTurn(815);
	motor[Intake] = 127;
	wait1Msec(100);
	Balls(4000);
	}
