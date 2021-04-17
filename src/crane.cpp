#include "crane.h"
#include <iostream>
#include <string>



Crane* ale_init(double starting_base_width, double starting_base_height, double starting_base, double starting_height, double starting_sliding, double starting_arm, double starting_angle){

    Crane* crane = new Crane;

    if(ale_check_constrains(starting_base_width, starting_base_height, starting_base, starting_height, starting_sliding, starting_arm, starting_angle) == false){
        return NULL;
    }

    crane->base_width = starting_base_width;
    crane->base_height = starting_height;
    crane->base = starting_base;
    crane->sliding = starting_sliding;
    crane->height = starting_height;
    crane->arm = starting_arm;
    crane->angle = starting_angle;

    return crane;
     
}

bool ale_check_constraints (double base_width, double base_height, double base, double height, double sliding, double arm, double angle){
    
    if(base_width < 0 || base_height < 0 || base < 0 || height < 0 || sliding < 0 || arm < 0 || angle < 0){
        return false;
    }

    if(base_height > base_width){
        return false;
    }

    if(base > base_width){
        return false;
    }

    if(height <= base_width){
        return false;
    }

    if(sliding > (base_width - base)){
        return false;
    }

    if(height <= base){
        return false;
    }

    if(arm > height){
        return false;
    }

    return true;
}