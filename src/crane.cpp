#include "crane.h"

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>


using namespace std;




Crane* ale_init(double starting_base_width, double starting_base_height, double starting_base, double starting_height, double starting_sliding, double starting_arm, double starting_angle){

    Crane* crane = new Crane;

    if(ale_check_constraints(starting_base_width, starting_base_height, starting_base, starting_height, starting_sliding, starting_arm, starting_angle) == false){
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

string ale_to_svg(Crane* device){

    string text = "";

    text += "<svg  width = \"1000\" height = \"900\">";
    text += "<g>";
    text += "<rect x = \"400\" y = \"800\" width =\"";
    text += string(device->base_width);
    text += "\" height = \"";
    text += string(device->base_height);
    text += "\"  stroke = \"black\" stroke-width = \"3\" fill = \"blue\" />";
    text += "<rect x = \"";
    int ax = 400 + device->sliding;
    text += string(ax);
    text += "\" y = \"";
    int ay = 400 + device->sliding;
    text += string(ay);
    text += "\" width = \"";
    text += string(device->base);
    text += "\" height = \"";
    text += string(device->height);
    text += "\" stroke = \"black\" stroke-width = \"3\" fill = \"red\" />";
    text += "<rect x = \"";
    int bx = ax + (device->base)*(1/2) - (1/4) * (device->arm);
    text += string(bx);
    text += "\" y = \"";
    int by = ay;
    text += string(by);
    text += "\" width = \""; 
    text += string(device->arm);
    text += "\" height = \"";
    text += string(device->base);
    text += "\" stroke = \"black\" stroke-width = \"3\" fill = \"green\" transform  = \"rotate(";
    text += string(device->angle);
    text += ",";
    text += string(ax + (1/2)*device->base);
    text += ",";
    text += string(ay + (1/2)*device->base);
    text += ")\"/>";
    text += "<circle cx = \"";
    text += string(ax + (1/2)*device->base);
    text += "\" cy = \"";
    text += string(ay + (1/2)*device->base);
    text += "\" r = \"";
    text += string((1/2)*device->base);
    text += "\" stroke = \"black\" stroke-width = \"3\" fill = \"grey\"/>";
    text += "</svg>"; 

}

int ale_set_base_width(Crane* device, double new_base_width){ 

    if(ale_check_constraints(new_base_width, device->base_height, device->base, device->height, device->sliding,device->arm, device->angle) == false){
        return 1;
    }

    device->base_width = new_base_width;

    return 0;

}


int ale_set_base_height(Crane* device, double new_base_height){ 

    if(ale_check_constraints(device->base_width, new_base_height, device->base, device->height, device->sliding,device->arm, device->angle) == false){
        return 1;
    }

    device->base_height = new_base_height;

    return 0;

}


int ale_set_base(Crane* device, double new_base){ 

    if(ale_check_constraints(device->base_width, device->base_height, new_base, device->height, device->sliding,device->arm, device->angle) == false){
        return 1;
    }

    device->base = new_base;

    return 0;

}


int ale_set_height(Crane* device, double new_height){ 

    if(ale_check_constraints(device->base_width, device->base_height, device->base, new_height, device->sliding,device->arm, device->angle) == false){
        return 1;
    }

    device->height = new_height;

    return 0;

}

int ale_set_sliding(Crane* device, double new_sliding){ 

    if(ale_check_constraints(device->base_width, device->base_height, device->base, device->height, new_sliding,device->arm, device->angle) == false){
        return 1;
    }

    device->sliding = new_sliding;

    return 0;

}

int ale_set_arm(Crane* device, double new_arm){ 

    if(ale_check_constraints(device->base_width, device->base_height, device->base, device->height, device->sliding, new_arm, device->angle) == false){
        return 1;
    }

    device->arm = new_arm;

    return 0;

}

int ale_set_angle(Crane* device, double new_angle){ 

    if(ale_check_constraints(device->base_width, device->base_height, device->base, device->height, device->sliding,device->arm, new_angle) == false){
        return 1;
    }

    device->angle = new_angle;

    return 0;

}

void ale_save_to_file(string text, const char* file_name){

    ofstream ale_File(file_name);
 
    string string_to_write = text;
    
    
    ale_File << string_to_write;
    
    
    ale_File.close();

}