#ifndef ALE_MACHINE_H
#define ALE_MACHINE_H

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

    double arm_sliding;
    double platform_sliding;

    AleCrane** arr1;
    EbDevice** arr2;
};

AleMachine* ale_machine_init(AleCrane* device1 ,EbDevice* devie2, double arm_sliding, double platform_sliding , int n);


#endif