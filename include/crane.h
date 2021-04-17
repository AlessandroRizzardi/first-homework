#ifndef CRAINE_H
#define CRAINE_H


struct Crane{

    double base_width;
    double base_height;

    double sliding;

    double base;
    double height;

    double arm;

    double angle;

};


Crane* ale_init(double starting_base_width, double starting_base_height, double starting_base, double starting_height, double starting_sliding, double starting_arm, double starting_angle);

bool ale_check_constraints(double base_width, double base_height, double base, double height, double sliding, double arm, double angle);



































#endif