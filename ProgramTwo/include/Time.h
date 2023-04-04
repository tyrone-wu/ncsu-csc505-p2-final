/** @file Time.h - static class for timing
 *  $Id: Time.h 168 2015-04-02 00:40:36Z mfms $
 *  @author Matt Stallmann @date 2005/06/20
 */

#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <sys/time.h>
#include <sys/resource.h>

using namespace std;

/// Encapsulates global timing information based on user time in getrusage()
class Time {
  /// start time of the program
  static double start_time;
  /// time when program should be timed out
  static double stop_time;
  /// time of last checkpoint
  static double checkpoint_time;
 public:

  /// return number of "user" CPU seconds used by this process so far
  /// (accurate to whatever the system clock allows, usually the nearest
  /// 1/60-th of a second).
  static double getUserSeconds();

  /// set current time as start time for the current program
  static void setStartTime() {
    start_time = getUserSeconds();
  }

  /// set a time limit (in seconds)
  static void setTimeLimit(double seconds) {
    if( start_time < 0 ) setStartTime();
    stop_time = start_time + seconds;
  }

  /// return the elapsed time in seconds
  static double elapsedTime() {
    return getUserSeconds() - start_time;
  }

  /// check to see if time has run out
  static bool timeLimitReached() {
    return getUserSeconds() >= stop_time;
  }

  /// set a time checkpoint
  static void setCheckPoint() {
    checkpoint_time = getUserSeconds();
  }

  /// return elapsed time since last checkpoint
  static double timeSinceCheckPoint() {
    if( checkpoint_time < 0 ) {
      cerr << "Warning from timeSinceCheckPoint(): No checkpoint set." << endl;
      return 0;
    }
    return getUserSeconds() - checkpoint_time;
  }
};

/// Allows creation of individual timers
class Timer {
 public:
  Timer() { my_elapsed_time = 0; my_last_checkpoint = Time::getUserSeconds(); }
  void reset() { my_elapsed_time = 0; }
  void start() { my_last_checkpoint = Time::getUserSeconds(); }
  void stop() {
    my_elapsed_time += Time::getUserSeconds() - my_last_checkpoint;
  }
  double getTotalTime() const { return my_elapsed_time; }
 private:
  double my_elapsed_time;
  double my_last_checkpoint;
};

#endif

// Local Variables: ***
//  mode:c++ ***
// End: ***

//  [Last modified: 2015 04 01 at 23:53:01 GMT]
