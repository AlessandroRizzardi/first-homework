#ifndef CRAINE_H
#define CRAINE_H


#include <string>

using namespace std;

/**
 * 
 * 
*/
struct AleCrane{

    double base_width;
    double base_height;

    double sliding;

    double base;
    double height;

    double arm;

    double angle;

};

/**
 * Initializes dinamically a Crane structure and assings to it the given parameters
 * 
 * @param starting_base_width value of the width's length of the base support
 * @param starting_base_height value of the height's length of the base support
 * @param starting_base value of the crane base's length 
 * @param starting_height value of the crane's height
 * @param starting_sliding value of the sliding of the crane along the base support
 * @param starting_arm value of the length of the crane's arm
 * @param starting_angle value in degree of the arm's rotation
 * @return a pointer pointing to the Crane structure initialized with parameters
*/
AleCrane* ale_init(double starting_base_width, double starting_base_height, double starting_base, double starting_height, double starting_sliding, double starting_arm, double starting_angle);

/**
 * Checks if all the constraints of the device are respected
 * 
 * @param base_width value of the width's length of the base support
 * @param base_height value of the height's length of the base support
 * @param base value of the crane base's length 
 * @param height value of the crane's height
 * @param sliding value of the sliding of the crane along the base support
 * @param arm value of the length of the crane's arm
 * @param angle value in degree of the arm's rotation
 * @return true if the constraints are respected, false otherwise
*/
bool ale_check_constraints(double base_width, double base_height, double base, double height, double sliding, double arm, double angle);

/**
 * Generates a string which contains the svg code 
 * 
 * @param device Crane structure with the length assigned
 * @param with_measures bool parameters to introdice measures (added measures if true)
 * @return a string with svg code 
*/
string ale_to_svg(AleCrane* device, bool with_measures);

/**
 * Given a new base-support width value checks if it respects constraints and assigns the new value to the device
 * 
 * @param device Crane structure which want to be modified with new length
 * @param new_base_width new length is wanted to set
 * @return 1 if the new device's new leght does not respects constraints, 0 if it respects them  
*/
int ale_set_base_width(AleCrane* device, double new_base_width);

/**
 * Given a new base-support height value checks if it respects constraints and assigns the new value to the device
 * 
 * @param device Crane structure which want to be modified with new length
 * @param new_base_width new lenght is wanted to set
 * @return 1 if the new device's new leght does not respects constraints, 0 if it respects them  
*/
int ale_set_base_height(AleCrane* device, double new_base_height);

/**
 * Given a new crane-base width value checks if it respects constraints and assigns the new value to the device
 * 
 * @param device Crane structure which want to be modified with new length
 * @param new_base_width new lenght is wanted to set
 * @return 1 if the new device's new leght does not respects constraints, 0 if it respects them  
*/
int ale_set_base(AleCrane* device, double new_base);

/**
 * Given a new crane height value checks if it respects constraints and assigns the new value to the device
 * 
 * @param device Crane structure which want to be modified with new length
 * @param new_base_width new lenght is wanted to set
 * @return 1 if the new device's new leght does not respects constraints, 0 if it respects them  
*/
int ale_set_height(AleCrane* device, double new_height);

/**
 * Given a new crane's sliding value checks if it respects constraints and assigns the new value to the device
 * 
 * @param device Crane structure which want to be modified with new length
 * @param new_base_width new lenght is wanted to set
 * @return 1 if the new device's new leght does not respects constraints, 0 if it respects them  
*/
int ale_set_sliding(AleCrane* device, double new_sliding);

/**
 * Given a new arm's length value checks if it respects constraints and assigns the new value to the device
 * 
 * @param device Crane structure which want to be modified with new length
 * @param new_base_width new lenght is wanted to set
 * @return 1 if the new device's new leght does not respects constraints, 0 if it respects them  
*/
int ale_set_arm(AleCrane* device, double new_arm);

/**
 * Given a new ratation's angle value checks if it respects constraints and assigns the new value to the device
 * 
 * @param device Crane structure which want to be modified with new length
 * @param new_base_width new lenght is wanted to set
 * @return 1 if the new device's new leght does not respects constraints, 0 if it respects them  
*/
int ale_set_angle(AleCrane* device, double new_angle);

/**
 * Given a string of svg code it stores the code in a given file-name
 * 
 * @param text string which contains the svg code of the device
 * @param file_name name of the file is wanted to store the svg code
*/
void ale_save_to_file(string text,string file_name);


/**
 * Given a file-name the function store its contents in a given string 
 * 
 *  
 * @param file_name name of the file is wanted to load  
 * @return text   string in which is wanted to store the svg code loaded from the file
*/
string ale_load_from_file(string file_name);

/**
 * ale_parse get a string with svg code and parse it to get the length data and create a new Crane structure
 * 
 * @param svg string which contains the svg code
 * @return NULL if the lengths dont respect cobnstraints, otherwise a pointer to a a Crane structure 
*/
AleCrane* ale_parse(string svg);




































#endif