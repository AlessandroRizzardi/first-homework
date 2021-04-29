#include "../include/crane.h"
#include "../include/EB_Device.h"
#include "../include/alemachine.h"

#include <iostream>
#include <cmath>
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>

using namespace std;

double std_shaftwidth2 = 20;
double std_towtruckwidth2 = 40;
double std_platformwidth2 = 20;
double std_radius2=10;
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

    double h1 = device2->length_shaft * cos(device2->rotation *(M_PI/180)) - (std_towtruckwidth2)/2 - (std_platformwidth2)/2;  //height beetween towtruck and platform
    double h2 = device1->base_height + device1->height;
    double h_ratio = h2 / h1;
    double scale = h_ratio + 0.2 ;

    machine->ratio = scale;
    machine->n = n;

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
    return 0;

}

string ale_machine_to_svg(AleMachine* machine){


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

    text += "<g transform  = \"rotate(" + to_string(machine->arr1[0]->angle) + "," + to_string(ax + 0.5 * (machine->arr1[0]->base)) + "," + to_string(ay + 0.5 * (machine->arr1[0]->base) ) + ")\">\n";
    text += "<rect x = \"" + to_string(bx) + "\" y = \"" + to_string(by) + "\" width = \"" + to_string(machine->arr1[0]->arm) + "\" height = \"" + to_string(machine->arr1[0]->base) + "\" stroke = \"black\" stroke-width = \"3\" fill = \"green\" />\n"; 
    text += "</g>\n";

    text += "<circle cx = \"" + to_string(ax + 0.5 * (machine->arr1[0]->base) ) + "\" cy = \"" + to_string(ay + 0.5 * (machine->arr1[0]->base) ) + "\" r = \"" + to_string(0.5 * (machine->arr1[0]->base) ) + "\" stroke = \"black\" stroke-width = \"3\" fill = \"grey\"/>\n";
        
    text += "<g>\n";
    text += "<rect x = \""+to_string(ax +machine->arr1[0]->base + machine->arr2[0]->sliding)+"\" y = \"" + to_string(ay + machine->arr1[0]->base) + "\" width = \"" + to_string(machine->arr2[0]->width_towtruck) +"\" height = \""+ to_string(40) + "\" stroke = \"black\" stroke-width = \"3\" fill = \"yellow\"/>\n";
    text += "</g>\n\n";

    text += "<g transform  = \"rotate(" + to_string(machine->arr2[0]->rotation) +"," + to_string(ax + machine->arr1[0]->base + eb_Xcir(machine->arr2[0])) + "," + to_string(ay + machine->arr1[0]->base + 40/2) + ")\">\n";
    text +="<rect x = \"" + to_string(ax + machine->arr1[0]->base + eb_Xcir(machine->arr2[0])-std_radius2) + "\" y = \"" + to_string(ay + machine->arr1[0]->base + 40/2) + "\" width = \"" + to_string(20) + "\" height = \"" + to_string(machine->arr2[0]->length_shaft) + "\" stroke = \"black\" stroke-width = \"3\" fill = \"orange\" />\n";
    text +="<circle cx = \"" + to_string(ax+ machine->arr1[0]->base + eb_Xcir(machine->arr2[0])) + "\" cy = \"" + to_string(ay + machine->arr1[0]->base + 40/2) + "\" r = \"" + to_string(10) + "\" stroke = \"black\" stroke-width = \"3\" fill = \"white\"/>\n";
    text +="</g>\n\n";

    text +="<g>\n";
    text +="<rect x = \"" + to_string(ax + machine->arr1[0]->base + eb_Xplatform(machine->arr2[0]) ) + "\" y = \"" + to_string(ay + machine->arr1[0]->base + 20 + machine->arr2[0]->length_shaft * cos(machine->arr2[0]->rotation * (M_PI/180)) - 20/2) + "\" width = \"" + to_string(machine->arr2[0]->width_platform )+ "\" height = \"20\"  stroke = \"black\" stroke-width = \"3\" fill = \"black\" />\n";
    text +="</g>\n\n";
    
    for(int i = 1; i < machine->n; i++){

        
        
        if(i == 1){
            X1 = ax + machine->arr1[i -1]->base + eb_Xplatform(machine->arr2[i-1]) + machine->platform_sliding;
            Y1 = ay + machine->arr1[i-1]->base + 20 + machine->arr2[i-1]->length_shaft * cos(machine->arr2[i-1]->rotation * (M_PI/180)) - 20/2 - machine->arr1[i]->base_height ;
        }else {
            X1 = ax + machine->arr1[i -1]->base + eb_Xplatform(machine->arr2[i-1]) +( (machine->platform_sliding) / ((i-1) * machine->ratio));
            Y1 = ay + machine->arr1[i -1]->base + std_towtruckwidth2/ ((i-1) * machine->ratio) + machine->arr2[i -1]->length_shaft * cos(machine->arr2[i-1]->rotation * (M_PI/180)) - std_platformwidth2/( 2 * (i -1) * machine->ratio) - machine->arr1[i]->base_height;
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
        text += "<rect x = \""+to_string(ax + machine->arr1[i]->base + machine->arr2[i]->sliding)+"\" y = \"" + to_string(ay + machine->arr1[i]->base) + "\" width = \"" + to_string(machine->arr2[i]->width_towtruck) +"\" height = \""+ to_string(std_towtruckwidth2 / (i * machine->ratio) ) + "\" stroke = \"black\" stroke-width = \"" + to_string(stroke / (i * machine->ratio)) + "\" fill = \"yellow\"/>\n";
        text += "</g>\n\n";

        text += "<g transform  = \"rotate(" + to_string(machine->arr2[i]->rotation) +"," + to_string(ax + machine->arr1[i]->base + eb_Xcir(machine->arr2[i])) + "," + to_string(ay + machine->arr1[i]->base) + ")\">\n";
        text +="<rect x = \"" + to_string(ax + machine->arr1[i]->base + eb_Xcir(machine->arr2[i])-std_radius2/ (i * machine->ratio)) + "\" y = \"" + to_string(ay + machine->arr1[i]->base + std_towtruckwidth2 / ( 2 * i * machine->ratio)) + "\" width = \"" + to_string(std_shaftwidth2 / (i * machine->ratio) ) + "\" height = \"" + to_string(machine->arr2[i]->length_shaft) + "\" stroke = \"black\" stroke-width = \"" + to_string(stroke / (i * machine->ratio)) + "\" fill = \"orange\" />\n";
        text +="<circle cx = \"" + to_string(ax + machine->arr1[i]->base + eb_Xcir(machine->arr2[i])) + "\" cy = \"" + to_string(ay + machine->arr1[i]->base + std_towtruckwidth2 / (2 *i * machine->ratio)) + "\" r = \"" + to_string(std_radius2 / (i * machine->ratio) ) + "\" stroke = \"black\" stroke-width = \"" + to_string(stroke/ (i * machine->ratio)) + "\" fill = \"white\"/>\n";
        text +="</g>\n\n";

        text +="<g>\n";
        text +="<rect x = \"" + to_string(ax + machine->arr1[i]->base + eb_Xplatform(machine->arr2[i]) ) + "\" y = \"" + to_string(ay + machine->arr1[i]->base + std_platformwidth2 / (i * machine->ratio) + machine->arr2[i]->length_shaft * cos(machine->arr2[i]->rotation * (M_PI/180)) - std_platformwidth2/(2 * i * machine->ratio) ) + "\" width = \"" + to_string(machine->arr2[i]->width_platform )+ "\" height = \"" + to_string(std_platformwidth2 / (i * machine->ratio)) + "\"  stroke = \"black\" stroke-width = \"" + to_string(stroke / (i * machine->ratio)) + "\" fill = \"black\" />\n";
        text +="</g>\n\n";

        std_radius2 = std_radius2 / (i * machine->ratio);
        std_shaftwidth2 = std_shaftwidth2/ (i * machine->ratio);
        std_platformwidth2 = std_platformwidth2 / (i * machine->ratio);
        std_towtruckwidth2 = std_towtruckwidth2 / (i * machine->ratio);
        machine->platform_sliding = machine->platform_sliding / (i * machine->ratio);
            
           
    }
    
    text += "</svg>";

    return text;
 
}


AleMachine* ale_machine_parse(string svg){

    AleCrane* device1 = ale_parse(svg);
    double difference = device1->sliding + device1->base +400;
    EbDevice* device2 = eb_new_parse(find_string(svg, "<circle cx", "fill = \"black\""), difference);

    string first_platform = find_string(svg, "fill = \"white\"", "fill = \"black\"");
    string second_svg = find_string(svg, "fill = \"black\"", "fill = \"blue\"");

    string search = "rect x = \"";
    size_t found1 = first_platform.find(search) + search.size();
    size_t found2 = first_platform.find("\"", found1);

    string read_svg = first_platform.substr(found1, found2 - found1);

    double Xplatform = stod(read_svg);
    

    string search2 = "rect x = \"";
    size_t found3 = second_svg.find(search2) + search.size();
    size_t found4 = second_svg.find("\"", found3);

    string read_svg2 = second_svg.substr(found3, found4 - found3);

    double newX1 = stod(read_svg2);

    double read_platform_sliding = newX1 - Xplatform;

    string recurring = "fill = \"blue\"";

    int instances = find_istances(recurring, svg);

    if(ale_check_machine_constraints(device1, device2, read_platform_sliding) == false){
        return NULL;
    }

    AleMachine* machine = ale_machine_init(device1, device2 , read_platform_sliding, instances);

    if(machine == NULL){
        return NULL;
    }

    return machine;


}

string find_string(string svg, string start, string end){

    string s = svg;
    string search = start;
    size_t found1 = svg.find(search,0);
    size_t found2 = svg.find(end, found1);

    string read_svg = svg.substr(found1, found2 - found1);

    return read_svg;
}

//taken from https://www.geeksforgeeks.org/frequency-substring-string/
int find_istances(string &pat, string &txt){
    int M = pat.length();
    int N = txt.length();
    int res = 0;
   
    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++){
        /* For current index i, check for
           pattern match */
        int j;
        for (j = 0; j < M; j++)
            if (txt[i+j] != pat[j])
                break;
  
        // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
        if (j == M) {
           res++;
           j = 0;
        }
    }
    return res;
}

bool ale_are_equal(AleMachine* machine1, AleMachine* machine2){

    if(machine1->arr1[0]->base_width != machine2->arr1[0]->base_width){
        return false;
    }

    if(machine1->arr1[0]->base_height != machine2->arr1[0]->base_height){
        return false;
    }


    if(machine1->arr1[0]->base != machine2->arr1[0]->base){
        return false;
    }

    if(machine1->arr1[0]->height != machine2->arr1[0]->height){
        return false;
    }

    if(machine1->arr1[0]->sliding != machine2->arr1[0]->sliding){
        return false;
    }
    

    if(machine1->arr1[0]->arm != machine2->arr1[0]->arm){
        return false;
    }
    

    if(machine1->arr1[0]->angle != machine2->arr1[0]->angle){
        return false;
    }
    

    if(machine1->arr2[0]->length_shaft != machine2->arr2[0]->length_shaft){
        return false;
    }
    

    if(machine1->arr2[0]->width_platform != machine2->arr2[0]->width_platform){
        return false;
    }


    if(machine1->arr2[0]->width_towtruck != machine2->arr2[0]->width_towtruck){
        return false;
    }
    

    if(machine1->arr2[0]->rotation != machine2->arr2[0]->rotation){
        return false;
    }
    

    if(machine1->arr2[0]->sliding != machine2->arr2[0]->sliding){
        return false;
    }

    if( machine1->platform_sliding != machine2->platform_sliding ){
        return false;
    }

    if(machine1->n != machine2->n){
        return false;
    }

    return true;

}

int ale_destroy(AleMachine* machine){

    if(machine == NULL){
        return 1;
    }

    for(int i = 0; i < machine->n; i++){
        delete machine->arr1[i];
        delete machine->arr2[i];
    }

    delete[] machine->arr1;
    delete[] machine->arr2;

    return 0;
}

EbDevice* eb_new_parse(string svg, double difference ){
    
    double length_shaft;
    double width_towtruck;
    double width_platform;
    double rotation;
    double sliding;
    
    
    //getting sliding
    string search = "rect x = \"";
    size_t find1 = svg.find(search) + search.size();
    size_t find2= svg.find("\"", find1);
    string element = svg.substr(find1, find2-find1);
    sliding = stod(element) - difference;


    //getting width_towtruck
    search = " width = \"";
    size_t find3 = svg.find(search,find1) + search.size();
    size_t find4= svg.find("\"", find3);
    element = svg.substr(find3, find4-find3);
    width_towtruck = stod(element);

    
    //getting rotation
    search = "g transform  = \"rotate(";
    size_t find5 = svg.find(search,find3) + search.size();
    size_t find6= svg.find(",", find5);
    element = svg.substr(find5, find6-find5);
    rotation = stod(element);
    
    //getting length_shaft
    search = " height = \"";
    size_t find7 = svg.find(search,find5) + search.size();
    size_t find8= svg.find("\"", find7);
    element = svg.substr(find7, find8-find7);
    length_shaft = stod(element);

    //getting width_platform
    search = " width = \"";
    size_t find9 = svg.find(search,find7) + search.size();
    size_t find10= svg.find("\"", find9);
    element = svg.substr(find9, find10-find9);
    width_platform = stod(element);


    EbDevice* device = new EbDevice;

    if(eb_checkConstraints(length_shaft,width_towtruck,width_platform,rotation,sliding) == false){
        return NULL;
    }
    
    device=eb_init(length_shaft,width_towtruck,width_platform,rotation,sliding);
    
    return device;
}




