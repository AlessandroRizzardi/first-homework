#include "../include/crane.h"
#include "../include/EB_Device.h"
#include "../include/Ale_Machine.h"

#include <string>
#include <cmath>
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>

const double std_shaftWidth = 20;
const double std_towtruckHeight = 40;
const double std_platformHeight = 20;

AleMachine* ale_machine_init(AleCrane* device1 ,EbDevice* device2,  double platform_sliding , int n){

    AleMachine* machine = new AleMachine;

    if(ale_check_machine_constraints(device1, device2, platform_sliding) == false){
        return NULL;
    }

    machine->platform_sliding = platform_sliding;

    machine->arr1 = new AleCrane* [n];
    machine->arr2 = new EbDevice* [n];

    machine->arr1[0] = ale_init( device1->base_width, device1->base_height, device1->base, device1->height, device1->sliding, device1->arm,device1->angle); 
    machine->arr2[0] = eb_init(device2->length_shaft, device2->width_towtruck, device2->width_platform, device2->rotation, device2->sliding);

    if(machine->arr1[0] == NULL || machine->arr2[0] == NULL){
        return NULL;
    }    

    double h1 = device2->length_shaft * sin(device2->rotation *(M_PI/180)) - (std_towtruckHeight)/2 - (std_platformHeight)/2;  //height beetween towtruck and platform
    double h2 = device1->base_height + device1->height;
    double h_ratio = h2 / h1;
    double scale = h_ratio + 1;

    for(int i = 1; i < n; i++){

        machine->arr1[i] = ale_init(device1->base_width / (i * scale), device1->base_height / (i * scale), device1->base / (i * scale), device1->height / (i * scale), device1->sliding / (i * scale), device1->arm / (i * scale),device1->angle);
        machine->arr2[i] = eb_init(device2->length_shaft / (i * scale), device2->width_towtruck / (i * scale), device2->width_platform / (i * scale), device2->rotation / (i * scale), arm_sliding / scale);

    }

    return machine;
}

bool ale_check_machine_constraints(AleCrane* device1 ,EbDevice* device2, double platform_sliding){

    if(device1->angle == 0){
        return false;
    }

    if(device2->rotation < - 80 || device2->rotation > 0){
        return false;
    }

    if(eb_Xplatform(device2) < (device2->sliding)){
        return false;
    }

    if(eb_drawConstraints(device2) == false){
        return false;
    }

    if(platform_sliding > device2->width_platform){
        return false;
    }

}

int ale_set_platform_sliding(AleMachine* machine, double new_platform_sliding){

    if(ale_check_machine_constraints(machine->arr1[0], machine->arr2[0], new_platform_sliding) == false){
        return 1;
    }

    machine->platform_sliding = new_platform_sliding;


}



