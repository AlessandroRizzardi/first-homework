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


/**
 * 
 * @param device1 is a Crane structure pointer
 * @param device2 is a EbDevice structure pointer
 * @param platform_sliding is the distance of the carrello on the crane's arm
 * @param n number of instances
 * @return a NULL pointer if machine constraints not respected, a pointer to a AleMachine struct othewise
 * 
*/
AleMachine* ale_machine_init(AleCrane* device1 ,EbDevice* devie2,  double platform_sliding , int n);

/**
 *  
 * @param device1 is a Crane structure pointer
 * @param device2 is a EbDevice structure pointer
 * @param platform_sliding is the distance of the carrello on the crane's arm
 * 
 * 
*/
bool ale_check_machine_constraints(AleCrane* device1 ,EbDevice* device2,  double platform_sliding);

/**
 * 
 * @param machineis a poiter to a AleMachine struct
 * @param new_platform_sliding new distance of the carrello on the crane's arm
 * 
*/
int ale_set_platform_sliding(AleMachine* machine, double new_platform_sliding);

/**
 * 
 * @param machineis a poiter to a AleMachine struct
 * @return an error string if the constraints of the machine are not respected, a string with svg code otherwise
 * 
*/
string ale_machine_to_svg(AleMachine* machine);

/**
 * @param svg string that must be parsed
 * @return a pointer to a AleMachine if constraints are respected, a NULLL pointer if constraints are not respected
 * 
*/
AleMachine* ale_machine_parse(string svg);

/**
 * @param svg a string
 * @param start string from which we want to start to extrapolate
 * @param end string of the end of extrapolation
 * 
*/
string find_string(string svg, string start, string end);

/**
 * @param pat is the string of wich is request to find occurency
 * @param txt string in which is find pat 
 * 
*/
int find_istances(string &pat, string &txt);

/**
 * @param machine1  poiter to a AleMachine struct
 * @param machine2  poiter to a AleMachine struct
 * @return true if the two machine are equal, false if not
 * 
*/
bool ale_are_equal(AleMachine* machine1, AleMachine* machine2);

/**
 * @param machineis a poiter to a AleMachine struct
 * @return 1 if machine pointer is NULL, 0 if the deallocation operation are been completed succcesfully
 * 
*/
int ale_destroy(AleMachine* machine);

/**
 * @param svg string is required to be parsed
 * @param differences is a geometrical parameter to find the carrello-gru sliding correctly
 * 
 * Function taken from EB_Device and changed a bit
 * 
*/
EbDevice* eb_new_parse(string svg, double difference );


#endif