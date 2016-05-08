void shooter(int value){
	motor[ LeftShooter1 ] = abs(value);
	motor[ LeftShooter2 ] = abs(value);
	motor[ LeftShooter3 ] = abs(value);

	motor[ RightShooter1 ] = abs(value);
	motor[ RightShooter2 ] = abs(value);
	motor[ RightShooter3 ] = abs(value);
}
