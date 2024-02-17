#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"
#include "globals.h"

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)


namespace ls {

template <typename... T>
void switchState(T&... it) {
  (it.set(!it.value()), ...);
} 

template <typename T> 
inline T clamp(T toClamp, T min, T max) {

  if (toClamp > max)
    return max;
  else if (toClamp < min)
    return min;
  else 
    return toClamp;

}

template <typename T>
inline T abs(T it) {
  return (it > 0 ? it : -it);
}

};

inline double spingInToDeg(vex::motor_group& group, double in) {

  const static double magicConstant = 0.3f;

  vex::directionType dir = vex::directionType::fwd;

  if (in < 0) {
      in = -in;
      dir = vex::directionType::rev;
  }

  double dist = (double)in / 3.5 * M_PI;
  double revolutions = dist / 5;
  double rot = revolutions * 360;
  rot *= magicConstant;

  group.spinFor(dir, rot, vex::rotationUnits::deg, 70, vex::velocityUnits::pct);


}