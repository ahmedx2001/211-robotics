

void FourBall(){
	SensorValue(TensionEncoder) = 0;
	SensorValue(BowEncoder) = 0;

	// Shoot first ball from cocked position
	while(-SensorValue(BowEncoder) < 80 ){
		Bow(127);
	}
	Bow(0);
	wait1Msec(300);
	while(-SensorValue(BowEncoder) < 150 ){
		Bow(127);
	}
	Bow(30);

	// Shoot second ball from bottom feed position
	motor(Intake) = 127;
	wait1Msec(250);
	while(-SensorValue(BowEncoder) < 430 ){
		Bow(127);
	}
	Bow(0);
	wait1Msec(300);
	while(-SensorValue(BowEncoder) < 530 ){
		Bow(127);
	}
	Bow(30);

	// Shoot 3 ball from bottom feed position
	motor(Intake) = 127;
	wait1Msec(250);
	while(-SensorValue(BowEncoder) < 790 ){
		Bow(127);
	}
	Bow(0);
	wait1Msec(300);
	while(-SensorValue(BowEncoder) < 890 ){
		Bow(127);
	}
	Bow(30);

	// Shoot 4 ball from bottom feed position
	motor(Intake) = 127;
	wait1Msec(250);
	while(-SensorValue(BowEncoder) < 1150 ){
		Bow(127);
	}
	Bow(0);
	wait1Msec(300);
	while(-SensorValue(BowEncoder) < 1250 ){
		Bow(127);
	}
	Bow(0);
}
