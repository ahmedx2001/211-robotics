/********************************************************/
/*                      timers.h                        */
/*                        v1.0                          */
/*                                                      */
/* This file was originally developed by:               */
/* Kristaps Berzinch                                    */
/* Programmer for Team 2105A                            */
/* Ware County High School                              */
/* Waycross, Georgia, USA                               */
/*                                                      */
/* Please drop me a line with questions or comments!    */
/* kberzinch@live.com                                   */
/* or on the VEX Forums: WCHS Programmer                */
/*                                                      */
/* You can do whatever you want with these files, but   */
/* please leave this and other credits sections intact. */
/*                                                      */
/* Neither I nor Ware County High School is responsible */
/* for any consequences.                                */
/********************************************************/

#ifdef timers.h
#warning ("Attempted to include timers.h more than once. Only the first #include has taken effect.")
#else
#define timers.h

#pragma systemFile

const char Timers_Count = 10;
float Timers[Timers_Count];

bool Timer_BoundsCheck(const char Timer)
{
  if (Timer < 0 || Timer > Timers_Count)
  {
#ifdef lcd.h  // If LCD.h is also included, it will prompt you when out of bounds. If not, this code is not compiled.
#ifndef LCD_NotUsing_Prompt // Checks to see if you requested that LCD_Prompt NOT be included.
    if (LCD_Prompt("Timer bounds error."," Check code! ","","Skip","Stop",2,5) == 3) {StopAllTasks();};
#endif
#endif
    return false;
    } else {
    return true;
  };
};

void Timer_Set(const char Timer, const float Value = 0)
{
  if (!Timer_BoundsCheck(Timer)) {return;};
  Timers[Timer] = nSysTime - Value;
};

float Timer_Hours(const char Timer)
{
  if (!Timer_BoundsCheck(Timer)) {return -1;};
  return (nSysTime - Timers[Timer]) / 3600000;
};

float Timer_Mins(const char Timer, const bool SubtractHigherUnit = false)
{
  if (!Timer_BoundsCheck(Timer)) {return -1;};
  const float Time = (nSysTime - Timers[Timer]) / 1000;
  if (SubtractHigherUnit)
  {
    return (Time - (floor(Timer_Hours(Timer)) * 3600)) / 60;
    } else {
    return Time / 60;
  };
};

float Timer_Secs(const char Timer, const bool SubtractHigherUnit = false)
{
  if (!Timer_BoundsCheck(Timer)) {return -1;};
  const float Time = (nSysTime - Timers[Timer]) / 1000;
  if (SubtractHigherUnit)
  {
    return Time - (floor(Timer_Mins(Timer)) * 60);
    } else {
    return Time;
  };
};

float Timer_Msecs(const char Timer, const bool SubtractHigherUnit = false)
{
  if (!Timer_BoundsCheck(Timer)) {return -1;};
  const float Time = (nSysTime - Timers[Timer]);
  if (SubtractHigherUnit)
  {
    return Time - (floor(Timer_Secs(Timer)) * 1000);
    } else {
    return Time;
  };
};

void Timer_WaitUntil(const char Timer, const float Value)
{
  if (!Timer_BoundsCheck(Timer)) {return;};
  while (Timer_Msecs(Timer) < Value)
  {
    wait1Msec(1);
  };
};

#endif
