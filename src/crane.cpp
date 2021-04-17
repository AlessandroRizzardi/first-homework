#include "crane.h"




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