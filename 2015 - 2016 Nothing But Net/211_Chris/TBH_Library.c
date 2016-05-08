
// Update inteval (in mS) for the flywheel control loop
#define FW_LOOP_SPEED              25

// Maximum power we want to send to the flywheel motors
#define FW_MAX_POWER              127

// encoder tick per revolution
float           ticks_per_rev;          ///< encoder ticks per revolution

// Encoder
long            encoder_counts;         ///< current encoder count
long            encoder_counts_last;    ///< current encoder count

// velocity measurement
float           motor_velocity;         ///< current velocity in rpm
long            nSysTime_last;          ///< Time of last velocity calculation

// TBH control algorithm variables
long            target_velocity;        ///< target_velocity velocity
float           current_error;          ///< error between actual and target_velocity velocities
float           last_error;             ///< error last time update called
float           gain;                   ///< gain
float           drive;                  ///< final drive out of TBH (0.0 to 1.0)
float           drive_at_zero;          ///< drive at last zero crossing
long            first_cross;            ///< flag indicating first zero crossing
float           drive_approx;           ///< estimated open loop drive

// final motor drive
long            motor_drive;            ///< final motor control value

/*-----------------------------------------------------------------------------*/
/** @brief      Set the flywheen motors                                        */
/** @param[in]  value motor control value                                      */
/*-----------------------------------------------------------------------------*/
void
FwMotorSet( int value )
{
	motor[ Shooter1 ] = value;
	motor[ Shooter2 ] = value;
	motor[ Shooter3 ] = value;
	motor[ Shooter4 ] = value;
}

/*-----------------------------------------------------------------------------*/
/** @brief      Get the flywheen motor encoder count                           */
/*-----------------------------------------------------------------------------*/
long
FwMotorEncoderGet()
{
	return( SensorValue(ShooterEncoder));
}

/*-----------------------------------------------------------------------------*/
/** @brief      Set the controller position                                    */
/** @param[in]  desired velocity                                               */
/** @param[in]  predicted_drive estimated open loop motor drive                */
/*-----------------------------------------------------------------------------*/
void
FwVelocitySet( int velocity, float predicted_drive )
{
	// set target_velocity velocity (motor rpm)
	target_velocity = velocity;

	// Set error so zero crossing is correctly detected
	current_error = target_velocity - motor_velocity;
	last_error    = current_error;

	// Set predicted open loop drive value
	drive_approx  = predicted_drive;
	// Set flag to detect first zero crossing
	first_cross   = 1;
	// clear tbh variable
	drive_at_zero = 0;
}

/*-----------------------------------------------------------------------------*/
/** @brief      Calculate the current flywheel motor velocity                  */
/*-----------------------------------------------------------------------------*/
void
FwCalculateSpeed()
{
	int     delta_ms;
	int     delta_enc;

	// Get current encoder value
	encoder_counts = FwMotorEncoderGet();

	// This is just used so we don't need to know how often we are called
	// how many mS since we were last here
	delta_ms = nSysTime - nSysTime_last;
	nSysTime_last = nSysTime;

	// Change in encoder count
	delta_enc = (encoder_counts - encoder_counts_last);

	// save last position3

	encoder_counts_last = encoder_counts;

	// Calculate velocity in rpm
	if (delta_enc != 0){
	motor_velocity = (1000.0 / delta_ms) * delta_enc * 60.0 / ticks_per_rev;
}
}

/*-----------------------------------------------------------------------------*/
/** @brief      Update the velocity tbh controller variables                   */
/*-----------------------------------------------------------------------------*/
void
FwControlUpdateVelocityTbh()
{
	// calculate error in velocity
	// target_velocity is desired velocity
	// current is measured velocity
	current_error = target_velocity - motor_velocity;

	// Calculate new control value
	drive =  drive + (current_error * gain);

	// Clip to the range 0 - 1.
	// We are only going forwards
	if( drive > 1 )
		drive = 1;
	if( drive < 0 )
		drive = 0;

	// Check for zero crossing
	if( sgn(current_error) != sgn(last_error) ) {
		// First zero crossing after a new set velocity command
		if( first_cross ) {
			// Set drive to the open loop approximation
			drive = drive_approx;
			first_cross = 0;
		}
		else
			drive = 0.5 * ( drive + drive_at_zero );

		// Save this drive value in the "tbh" variable
		drive_at_zero = drive;
	}

	// Save last error
	last_error = current_error;
}

/*-----------------------------------------------------------------------------*/
/** @brief     Task to control the velocity of the flywheel                    */
/*-----------------------------------------------------------------------------*/
task
FwControlTask()
{
	// Set the gain
	gain = 0.004;

	// We are using Speed geared motors
	// Set the encoder ticks per revolution
	ticks_per_rev = 360;

	while(1)
	{
		// Calculate velocity
		FwCalculateSpeed();

		// Do the velocity TBH calculations
		FwControlUpdateVelocityTbh() ;

		// Scale drive into the range the motors need
		motor_drive  = (drive * FW_MAX_POWER) + 0.5;

		// Final Limit of motor values - don't really need this
		if( motor_drive >  127 ) motor_drive =  127;
		if( motor_drive < -127 ) motor_drive = -127;

		// and finally set the motor control value
		FwMotorSet( motor_drive );

		// Run at somewhere between 20 and 50mS
		wait1Msec( FW_LOOP_SPEED );
	}
}

// Main user task
