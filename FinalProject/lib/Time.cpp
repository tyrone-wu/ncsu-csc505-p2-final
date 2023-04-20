/// @file Time.cpp
/// @brief For definitions of the static variables of class Time.
/// @author Matt Stallmann
/// @date 2005/11/01

#include <float.h>
#include "../include/Time.h"

double Time::start_time = -1.0; // this implies "uninitialized"
double Time::checkpoint_time = -1.0;
double Time::stop_time = DBL_MAX;

double Time::getUserSeconds() {
  struct rusage ru;
  getrusage( RUSAGE_SELF, &ru );
  return ( ru.ru_utime.tv_sec + 
           static_cast<double>( ru.ru_utime.tv_usec ) / 1000000.0 );
}

//  [Last modified: 2005 11 02 at 01:58:15 GMT]
