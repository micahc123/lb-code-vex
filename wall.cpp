#include "robot/wall.h"
#include "globals.h"

namespace subsystems {

Wall::Wall(int left_port, int right_port) 
    : left_wall_motor(left_port, pros::E_MOTOR_GEAR_GREEN),
      right_wall_motor(right_port, pros::E_MOTOR_GEAR_GREEN),
      target_position(START_POS) {
    left_wall_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    right_wall_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    
    
    left_wall_motor.tare_position();
    right_wall_motor.tare_position();
    
    left_wall_motor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
    right_wall_motor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
}

void Wall::move_to_position(int position) {
    target_position = position * GEAR_RATIO;
    
    double current_pos = ((left_wall_motor.get_position() + right_wall_motor.get_position()) / 2.0) * GEAR_RATIO;
    double error = target_position - current_pos;
    
    double kp = 0.5;
    double velocity = kp * error;
    
    left_wall_motor.move(velocity);
    right_wall_motor.move(velocity);
}

void Wall::run() {
    if (master.get_digital_new_press(DIGITAL_R1)) {
        move_to_position(SCORE_POS);
    }
    else if (master.get_digital_new_press(DIGITAL_X)) {
        move_to_position(STOW_POS);
    }
    else if (master.get_digital(DIGITAL_R2)) {
        move_to_position(START_POS);
    }
    
    move_to_position(target_position);
}

}