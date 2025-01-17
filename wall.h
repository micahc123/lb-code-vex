#ifndef WALL_H
#define WALL_H

#include "pros/motors.hpp"

namespace subsystems {

class Wall {
public:
    Wall(int left_port, int right_port);
    void run();

    static constexpr int START_POS = 0;     
    static constexpr int STOW_POS = -50;   
    static constexpr int SCORE_POS = 180;   

    static constexpr double GEAR_RATIO = 3.0;

private:
    pros::Motor left_wall_motor;
    pros::Motor right_wall_motor;
    int target_position;
    
    void move_to_position(int position);
};

}

#endif // WALL_H