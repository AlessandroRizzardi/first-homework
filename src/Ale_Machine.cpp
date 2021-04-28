#include "../include/crane.h"
#include "../include/EB_Device.h"
#include "../include/Ale_Machine.h"

#include <iostream>
#include <cmath>
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>

using namespace std;

double std_shaftWidth = 20;
double std_towtruckHeight = 40;
double std_platformHeight = 20;
double std_radius=10;
double stroke = 3;

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

    double h1 = device2->length_shaft * cos(device2->rotation *(M_PI/180)) - (std_towtruckHeight)/2 - (std_platformHeight)/2;  //height beetween towtruck and platform
    double h2 = device1->base_height + device1->height;
    double h_ratio = h2 / h1;
    double scale = h_ratio + 0.2 ;

    machine->ratio = scale;

    for(int i = 1; i < n; i++){

        machine->arr1[i] = ale_init(machine->arr1[i-1]->base_width / (i * scale), machine->arr1[i-1]->base_height / (i * scale), machine->arr1[i-1]->base / (i * scale), machine->arr1[i-1]->height / (i * scale), machine->arr1[i-1]->sliding / (i * scale), machine->arr1[i-1]->arm / (i * scale),device1->angle);
        machine->arr2[i] = eb_init(machine->arr2[i-1]->length_shaft / (i * scale), machine->arr2[i-1]->width_towtruck / (i * scale), machine->arr2[i-1]->width_platform / (i * scale), device2->rotation , machine->arr2[i-1]->sliding / (i * scale));

    }

    return machine;
}

bool ale_check_machine_constraints(AleCrane* device1 ,EbDevice* device2, double platform_sliding){
    
    if(device1->angle != 0){
        return false;
    }

    if(device2->rotation < - 80 || device2->rotation > 0){
        return false;
    }
    
    if(400 + device1->sliding + device1->base +eb_Xplatform(device2) < 400 + device1->sliding + device1->base){
        return false;
    }
    
    
    if(eb_drawConstraints(device2) == false){
        
        return false;
    }

    if(platform_sliding > device2->width_platform){
        
        return false;
    }

    if((device2->sliding + device2->width_towtruck) > 0.75 * device1->arm){
        
        return false;
    }
    

    return true;
    
}

int ale_set_platform_sliding(AleMachine* machine, double new_platform_sliding){

    if(ale_check_machine_constraints(machine->arr1[0], machine->arr2[0], new_platform_sliding) == false){
        return 1;
    }

    machine->platform_sliding = new_platform_sliding;

}

string ale_machine_to_svg(AleMachine* machine, int n){


    string text = "";

    if(machine == NULL){
        text += "ERRORE";
        return text;
    }

    text += "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n\n";
    text += "<svg xmlns=\"http://www.w3.org/2000/svg\"  width = \"3000\" height = \"900\">\n\n";

    double X1 = 400;
    double Y1 = 800;

    
    text += "<rect x = \"" + to_string(X1) +"\" y = \"" + to_string(Y1) + "\" width =\"" + to_string(machine->arr1[0]->base_width) + "\" height = \"" + to_string(machine->arr1[0]->base_height) + "\"  stroke = \"black\" stroke-width = \"3\" fill = \"blue\" />\n";


    double ax = X1 + machine->arr1[0]->sliding;
    double ay = Y1 - machine->arr1[0]->height;

    text += "<rect x = \"" + to_string(ax) + "\" y = \"" + to_string(ay) + "\" width = \"" +  to_string(machine->arr1[0]->base) + "\" height = \"" + to_string(machine->arr1[0]->height) + "\" stroke = \"black\" stroke-width = \"3\" fill = \"red\" />\n";

    double bx = ax + (machine->arr1[0]->base)*0.5 - 0.25 * (machine->arr1[0]->arm);
    double by = ay;

    text += "<rect x = \"" + to_string(bx) + "\" y = \"" + to_string(by) + "\" width = \"" + to_string(machine->arr1[0]->arm) + "\" height = \"" + to_string(machine->arr1[0]->base) + "\" stroke = \"black\" stroke-width = \"3\" fill = \"green\" transform  = \"rotate(" + to_string(machine->arr1[0]->angle) + "," + to_string(ax + 0.5 * (machine->arr1[0]->base)) + "," + to_string(ay + 0.5 * (machine->arr1[0]->base) ) + ")\"/>\n";
     
    text += "<circle cx = \"" + to_string(ax + 0.5 * (machine->arr1[0]->base) ) + "\" cy = \"" + to_string(ay + 0.5 * (machine->arr1[0]->base) ) + "\" r = \"" + to_string(0.5 * (machine->arr1[0]->base) ) + "\" stroke = \"black\" stroke-width = \"3\" fill = \"grey\"/>\n";
        
    text += "<g>\n";
    text += "<rect x = \""+to_string(ax +machine->arr1[0]->base + machine->arr2[0]->sliding)+"\" y = \"" + to_string(ay + machine->arr1[0]->base) + "\" width = \"" + to_string(machine->arr2[0]->width_towtruck) +"\" height = \""+ to_string(40) + "\" stroke = \"black\" stroke-width = \"3\" fill = \"yellow\"/>\n";
    text += "</g>\n\n";

    text += "<g transform  = \"rotate(" + to_string(machine->arr2[0]->rotation) +"," + to_string(ax + machine->arr1[0]->base + eb_Xcir(machine->arr2[0])) + "," + to_string(ay + machine->arr1[0]->base + 40/2) + ")\">\n";
    text +="<rect x = \"" + to_string(ax + machine->arr1[0]->base + eb_Xcir(machine->arr2[0])-std_radius) + "\" y = \"" + to_string(ay + machine->arr1[0]->base + 40/2) + "\" width = \"" + to_string(20) + "\" height = \"" + to_string(machine->arr2[0]->length_shaft) + "\" stroke = \"black\" stroke-width = \"3\" fill = \"orange\" />\n";
    text +="<circle cx = \"" + to_string(ax+ machine->arr1[0]->base + eb_Xcir(machine->arr2[0])) + "\" cy = \"" + to_string(ay + machine->arr1[0]->base + 40/2) + "\" r = \"" + to_string(10) + "\" stroke = \"black\" stroke-width = \"3\" fill = \"white\"/>\n";
    text +="</g>\n\n";

    text +="<g>\n";
    text +="<rect x = \"" + to_string(ax + machine->arr1[0]->base + eb_Xplatform(machine->arr2[0]) ) + "\" y = \"" + to_string(ay + machine->arr1[0]->base + 20 + machine->arr2[0]->length_shaft * cos(machine->arr2[0]->rotation * (M_PI/180)) - 20/2) + "\" width = \"" + to_string(machine->arr2[0]->width_platform )+ "\" height = \"20\"  stroke = \"black\" stroke-width = \"3\" fill = \"black\" />\n";
    text +="</g>\n\n";
    
    for(int i = 1; i < n; i++){

        
        
        if(i == 1){
            X1 = ax + machine->arr1[i -1]->base + eb_Xplatform(machine->arr2[i-1]) + machine->platform_sliding;
            Y1 = ay + machine->arr1[i-1]->base + 20 + machine->arr2[i-1]->length_shaft * cos(machine->arr2[i-1]->rotation * (M_PI/180)) - 20/2 - machine->arr1[i]->base_height ;
        }else {
            X1 = ax + machine->arr1[i -1]->base + eb_Xplatform(machine->arr2[i-1]) +( (machine->platform_sliding) / ((i-1) * machine->ratio));
            Y1 = ay + machine->arr1[i -1]->base + std_towtruckHeight/ ((i-1) * machine->ratio) + machine->arr2[i -1]->length_shaft * cos(machine->arr2[i-1]->rotation * (M_PI/180)) - std_platformHeight/( 2 * (i -1) * machine->ratio) - machine->arr1[i]->base_height;
        }    

        //crane drawing

        text += "<rect x = \"" + to_string(X1) +"\" y = \"" + to_string(Y1) + "\" width =\"" + to_string(machine->arr1[i]->base_width) + "\" height = \"" + to_string(machine->arr1[i]->base_height) + "\"  stroke = \"black\" stroke-width = \"" + to_string(stroke / (i * machine->ratio)) +"\" fill = \"blue\" />\n";


        ax = X1 + machine->arr1[i]->sliding;
        ay = Y1 - machine->arr1[i]->height;

        text += "<rect x = \"" + to_string(ax) + "\" y = \"" + to_string(ay) + "\" width = \"" +  to_string(machine->arr1[i]->base) + "\" height = \"" + to_string(machine->arr1[i]->height) + "\" stroke = \"black\" stroke-width = \"" +  to_string(stroke/ (i * machine->ratio)) + "\" fill = \"red\" />\n";

        double bx = ax + (machine->arr1[i]->base)*0.5 - 0.25 * (machine->arr1[i]->arm);
        double by = ay;

        text += "<rect x = \"" + to_string(bx) + "\" y = \"" + to_string(by) + "\" width = \"" + to_string(machine->arr1[i]->arm) + "\" height = \"" + to_string(machine->arr1[i]->base) + "\" stroke = \"black\" stroke-width = \"" +  to_string(stroke / (i * machine->ratio)) + "\" fill = \"green\" transform  = \"rotate(" + to_string(machine->arr1[i]->angle) + "," + to_string(ax + 0.5 * (machine->arr1[i]->base)) + "," + to_string(ay + 0.5 * (machine->arr1[i]->base) ) + ")\"/>\n";
        
        text += "<circle cx = \"" + to_string(ax + 0.5 * (machine->arr1[i]->base) ) + "\" cy = \"" + to_string(ay + 0.5 * (machine->arr1[i]->base) ) + "\" r = \"" + to_string(0.5 * (machine->arr1[i]->base) ) + "\" stroke = \"black\" stroke-width = \"" + to_string(stroke / (i * machine->ratio)) + "\" fill = \"grey\"/>\n";
        
        // carrello drawing

        text += "<g>\n";
        text += "<rect x = \""+to_string(ax + machine->arr1[i]->base + machine->arr2[i]->sliding)+"\" y = \"" + to_string(ay + machine->arr1[i]->base) + "\" width = \"" + to_string(machine->arr2[i]->width_towtruck) +"\" height = \""+ to_string(std_towtruckHeight / (i * machine->ratio) ) + "\" stroke = \"black\" stroke-width = \"" + to_string(stroke / (i * machine->ratio)) + "\" fill = \"yellow\"/>\n";
        text += "</g>\n\n";

        text += "<g transform  = \"rotate(" + to_string(machine->arr2[i]->rotation) +"," + to_string(ax + machine->arr1[i]->base + eb_Xcir(machine->arr2[i])) + "," + to_string(ay + machine->arr1[i]->base) + ")\">\n";
        text +="<rect x = \"" + to_string(ax + machine->arr1[i]->base + eb_Xcir(machine->arr2[i])-std_radius/ (i * machine->ratio)) + "\" y = \"" + to_string(ay + machine->arr1[i]->base + std_towtruckHeight / ( 2 * i * machine->ratio)) + "\" width = \"" + to_string(std_shaftWidth / (i * machine->ratio) ) + "\" height = \"" + to_string(machine->arr2[i]->length_shaft) + "\" stroke = \"black\" stroke-width = \"" + to_string(stroke / (i * machine->ratio)) + "\" fill = \"orange\" />\n";
        text +="<circle cx = \"" + to_string(ax + machine->arr1[i]->base + eb_Xcir(machine->arr2[i])) + "\" cy = \"" + to_string(ay + machine->arr1[i]->base + std_towtruckHeight / (2 *i * machine->ratio)) + "\" r = \"" + to_string(std_radius / (i * machine->ratio) ) + "\" stroke = \"black\" stroke-width = \"" + to_string(stroke/ (i * machine->ratio)) + "\" fill = \"white\"/>\n";
        text +="</g>\n\n";

        text +="<g>\n";
        text +="<rect x = \"" + to_string(ax + machine->arr1[i]->base + eb_Xplatform(machine->arr2[i]) ) + "\" y = \"" + to_string(ay + machine->arr1[i]->base + std_platformHeight / (i * machine->ratio) + machine->arr2[i]->length_shaft * cos(machine->arr2[i]->rotation * (M_PI/180)) - std_platformHeight/(2 * i * machine->ratio) ) + "\" width = \"" + to_string(machine->arr2[i]->width_platform )+ "\" height = \"" + to_string(std_platformHeight / (i * machine->ratio)) + "\"  stroke = \"black\" stroke-width = \"" + to_string(stroke / (i * machine->ratio)) + "\" fill = \"black\" />\n";
        text +="</g>\n\n";

        std_radius = std_radius / (i * machine->ratio);
        std_shaftWidth = std_shaftWidth/ (i * machine->ratio);
        std_platformHeight = std_platformHeight / (i * machine->ratio);
        std_towtruckHeight = std_towtruckHeight / (i * machine->ratio);
        machine->platform_sliding = machine->platform_sliding / (i * machine->ratio);
            
           
    }
    
    text += "</svg>";

    return text;
 
}


