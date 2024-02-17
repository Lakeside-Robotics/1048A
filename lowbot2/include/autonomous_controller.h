#pragma once

#include <vector>
#include <functional>
#include <string>
#include <utility> 
#include <sstream>

#include "v5.h"
#include "v5_vcs.h"

#include "globals.h"

#define M_PI 3.14159265358979323846

#if false

namespace ls {

    template <typename T>
    static std::string to_string(T value)
    {
        std::stringstream os ;
        os << value ;
        return os.str() ;
    }

    struct Action {
        
        std::function<void()> action;
        std::string name;

        inline void operator()() {
            action();
        }

    };


    class autonomous_controller {

    private:

        std::vector<Action> actions;

    public:

        //1 rot to 5
        static inline int gearRatio = 20;
        static inline float wheelCircumfrence = 3.25 * M_PI;
        static inline int turnRad = 13;

        static inline float speed = 30;

        inline void add_action(const Action& action) {

            actions.push_back(action);

        }

        inline void run() {

            for (Action& action : actions) {
                
                action();

            }
        }

        static inline Action turnBy(int degrees) {
            
            Action action;
            action.name = std::string("turnBy:") + to_string(degrees);

            action.action = [degrees]() mutable {

                vex::directionType dir = vex::directionType::fwd;

                if (degrees < 0) {
                    degrees = -degrees;
                    dir = vex::directionType::rev;
                }

                double inToMove = (turnRad * turnRad * M_PI) * ((double)degrees/360);
                double rot = inToMove / wheelCircumfrence / gearRatio;
                left.stop(vex::brakeType::hold);
                right.spinFor(dir, rot, vex::rotationUnits::deg, speed, vex::velocityUnits::pct);
 
            };
            
            return action;

        }

        static inline Action moveBy(double in) {

            Action action;
            action.name = std::string("move:") + to_string(in);

            action.action = [in]() mutable {

                vex::directionType dir = vex::directionType::fwd;

                if (in < 0) {
                    in = -in;
                    dir = vex::directionType::rev;
                }

                double dist = (double)in / wheelCircumfrence;
                double revolutions = dist / gearRatio;

                double rot = revolutions * 360;

                all.spinFor(dir, rot, vex::rotationUnits::deg,  speed, vex::velocityUnits::pct);

            };

            return action;
        };

        static inline Action spinForever(vex::directionType dir, double pct, vex::motor_group& actee) {

            Action action;
            action.name = std::string("spinforever");

            action.action = [dir, pct, &actee]() {
                actee.spin(dir, pct, vex::velocityUnits::pct);
                
            };

            return action;

        }

        static inline Action outtake(vex::motor& outtake) {
            Action action;
            action.name = std::string("outtaked");

            action.action = [&outtake]() {
                outtake.spinFor(1.5, vex::timeUnits::sec,  100, vex::velocityUnits::pct);
            };

            return action;
        }


    };




};

#endif