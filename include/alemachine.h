#ifndef ALEMACHINE_H
#define ALEMACHINE_H

#include <string>
#include <cmath>
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>

#include "crane.h"
#include "EB_Device.h"

//struct which contains parameters of machine and references to the devices which make the machine
struct AleMachine{
    
    double ratio;
    int n;
    double platform_sliding;

    AleCrane** arr1;
    EbDevice** arr2;
};

AleMachine* ale_machine_init(AleCrane* device1 ,EbDevice* devie2,  double platform_sliding , int n);

bool ale_check_machine_constraints(AleCrane* device1 ,EbDevice* device2,  double platform_sliding);

int ale_set_platform_sliding(AleMachine* machine, double new_platform_sliding);

string ale_machine_to_svg(AleMachine* machine);

AleMachine* ale_machine_parse(string svg);

string find_string(string svg, string start, string end);

int find_istances(string &pat, string &txt);

bool ale_are_equal(AleMachine* machine1, AleMachine* machine2);

int ale_destroy(AleMachine* machine);

EbDevice* eb_new_parse(string svg, double difference );


#endif