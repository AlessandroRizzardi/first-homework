#ifndef CRAINE_H
#define CRAINE_H


#include <string>


using namespace std;

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

string ale_to_svg(Crane* device);

int ale_set_base_width(Crane* device, double new_base_width);

int ale_set_base_height(Crane* device, double new_base_height);

int ale_set_base(Crane* device, double new_base);

int ale_set_height(Crane* device, double new_height);

int ale_set_sliding(Crane* device, double new_sliding);

int ale_set_arm(Crane* device, double new_arm);

int ale_set_angle(Crane* device, double new_angle);

void ale_save_to_file(string text);

void ale_load_from_file(string text);



































#endif