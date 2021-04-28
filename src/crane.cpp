#include "../include/crane.h"

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>


using namespace std;




AleCrane* ale_init(double starting_base_width, double starting_base_height, double starting_base, double starting_height, double starting_sliding, double starting_arm, double starting_angle){

    AleCrane* crane = new AleCrane;

    if(ale_check_constraints(starting_base_width, starting_base_height, starting_base, starting_height, starting_sliding, starting_arm, starting_angle) == false){
        return NULL;
    }

    crane->base_width = starting_base_width;
    crane->base_height = starting_base_height;
    crane->base = starting_base;
    crane->sliding = starting_sliding;
    crane->height = starting_height;
    crane->arm = starting_arm;
    crane->angle = starting_angle;

    return crane;
     
}

bool ale_check_constraints (double base_width, double base_height, double base, double height, double sliding, double arm, double angle){
    
    if(base_width < 0 || base_height < 0 || base < 0 || height < 0 || sliding < 0 || arm < 0 ){
        return false;
    }

    if((800 - (height + arm * 0.25) < 0)){
        return false;
    }

    if((base_height) > 100){
        return false;
    }

    if(base_width > 600){
        return false;
    }


    if(angle > 90 || angle < -90 ){
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

string ale_to_svg(AleCrane* device, bool with_measures){

    string text = "";

    if(with_measures == true){

        text += "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n\n";
        text += "<svg xmlns=\"http://www.w3.org/2000/svg\"  width = \"1000\" height = \"900\">\n\n";

        text += "<g>\n";
        text += "<rect x = \"400\" y = \"800\" width =\"";
        text += to_string(device->base_width);
        text += "\" height = \"";
        text += to_string(device->base_height);
        text += "\"  stroke = \"black\" stroke-width = \"3\" fill = \"blue\" />\n";
        text += "<text x = \"" + to_string(400 + (device->base_width)/2) + "\" y = \"" + to_string(800 + device->base_height + 40) + "\" fill = \"black\">" + to_string(device->base_width) + "m </text>\n";
        text += "<line x1 = \"400\" y1 = \"" + to_string(800 + device->base_height + 20) + "\" x2 = \"" + to_string(400 + device->base_width) + "\" y2 = \"" + to_string(800 + device->base_height + 20) + "\"  stroke = \"black\" stroke-width  = \"2\"/>\n";
        text += "<text x = \"" + to_string(400 + (device->base_width) + 50) + "\" y = \"" + to_string(800 + (device->base_height)/2) + "\" fill = \"black\">" + to_string(device->base_height) + "m </text>";
        text += "<line x1 = \"" + to_string(400 + device->base_width + 10) + "\" y1 = \"" + to_string(800) + "\" x2 = \"" + to_string(400 + device->base_width  + 10) + "\" y2 = \"" + to_string(800 + device->base_height) + "\"  stroke = \"black\" stroke-width  = \"2\"/>\n";
        text += "</g>\n\n";

        text += "<g>\n";
        text += "<rect x = \"";
        double ax = 400 + device->sliding;
        text += to_string(ax);
        text += "\" y = \"";
        double ay = 800 - device->height;
        text += to_string(ay);
        text += "\" width = \"";
        text += to_string(device->base);
        text += "\" height = \"";
        text += to_string(device->height);
        text += "\" stroke = \"black\" stroke-width = \"3\" fill = \"red\" />\n";
        text += "<text x = \"" + to_string(400 + device->sliding + (device->base)/2) + "\" y = \"" + to_string(800 + 30) + "\" fill = \"black\">" + to_string(device->base) + "m </text>\n";
        text += "<line x1 = \"" + to_string(400 + device->sliding) + "\" y1 = \"" + to_string(800 + 10) + "\" x2 = \"" + to_string(400 + device->sliding + device->base) + "\" y2 = \"" + to_string(800 + 10) + "\"  stroke = \"black\" stroke-width  = \"2\"/>\n";
        text += "<text x = \"" + to_string(400 - 200) + "\" y = \"" + to_string(800 - (device->height)/2) + "\" fill = \"black\">" + to_string(device->height) + "m </text>";
        text += "<line x1 = \"" + to_string(400 - 100) + "\" y1 = \"" + to_string(800 - device->height) + "\" x2 = \"" + to_string(400 - 100) + "\" y2 = \"" + to_string(800) + "\"  stroke = \"black\" stroke-width  = \"2\"/>\n";
        text += "</g>\n\n";

        text += "<g>\n";
        text += "<line x1 = \"" + to_string(400) + "\" y1 = \"" + to_string(800 - 10) + "\" x2 = \"" + to_string(400 + device->sliding) + "\" y2 = \"" + to_string(800 - 10) + "\"  stroke = \"black\" stroke-width  = \"2\"/>\n";
        text += "<text x = \"" + to_string(400 + (device->sliding)/4) + "\" y = \"" + to_string(800 - 20) + "\" fill = \"black\">" + to_string(device->sliding) + "m </text>";
        text += "</g>\n\n";


        text += "<g transform  = \"rotate(" + to_string(device->angle) + "," + to_string(ax + 0.5*device->base) + "," +  to_string(ay + 0.5*device->base) + ")\">\n";
        text += "<rect x = \"";
        double bx = ax + (device->base)*0.5 - 0.25 * (device->arm);
        text += to_string(bx);
        text += "\" y = \"";
        double by = ay;
        text += to_string(by);
        text += "\" width = \""; 
        text += to_string(device->arm);
        text += "\" height = \"";
        text += to_string(device->base);
        text += "\" stroke = \"black\" stroke-width = \"3\" fill = \"green\" />\n";
        text += "<text x = \"" + to_string(bx + (device->arm)/2) + "\" y = \"" + to_string(by - 30) + "\" fill = \"black\">" + to_string(device->arm) + "m </text>\n";
        text += "<line x1 = \"" + to_string(bx) + "\" y1 = \"" + to_string(by - 20) + "\" x2 = \"" + to_string(bx + device->arm) + "\" y2 = \"" + to_string(by - 20) + "\"  stroke = \"black\" stroke-width  = \"2\"/>\n";
        text += "</g>\n\n";
        
        text += "<circle cx = \"";
        text += to_string(ax + 0.5*device->base);
        text += "\" cy = \"";
        text += to_string(ay + 0.5*device->base);
        text += "\" r = \"";
        text += to_string(0.5*device->base);
        text += "\" stroke = \"black\" stroke-width = \"3\" fill = \"grey\"/>\n\n";
        text += "</svg>"; 

        return text;

    }else{

        text += "<svg  width = \"1000\" height = \"900\">\n";

        text += "<rect x = \"400\" y = \"800\" width =\"";
        text += to_string(device->base_width);
        text += "\" height = \"";
        text += to_string(device->base_height);
        text += "\"  stroke = \"black\" stroke-width = \"3\" fill = \"blue\" />\n";

        text += "<rect x = \"";
        double ax = 400 + device->sliding;
        text += to_string(ax);
        text += "\" y = \"";
        double ay = 800 - device->height;
        text += to_string(ay);
        text += "\" width = \"";
        text += to_string(device->base);
        text += "\" height = \"";
        text += to_string(device->height);
        text += "\" stroke = \"black\" stroke-width = \"3\" fill = \"red\" />\n";

        text += "<rect x = \"";
        double bx = ax + (device->base)*0.5 - 0.25 * (device->arm);
        text += to_string(bx);
        text += "\" y = \"";
        double by = ay;
        text += to_string(by);
        text += "\" width = \""; 
        text += to_string(device->arm);
        text += "\" height = \"";
        text += to_string(device->base);
        text += "\" stroke = \"black\" stroke-width = \"3\" fill = \"green\" transform  = \"rotate(";
        text += to_string(device->angle);
        text += ",";
        text += to_string(ax + 0.5*device->base);
        text += ",";
        text += to_string(ay + 0.5*device->base);
        text += ")\"/>\n";
        
        text += "<circle cx = \"";
        text += to_string(ax + 0.5*device->base);
        text += "\" cy = \"";
        text += to_string(ay + 0.5*device->base);
        text += "\" r = \"";
        text += to_string(0.5*device->base);
        text += "\" stroke = \"black\" stroke-width = \"3\" fill = \"grey\"/>\n";
        text += "</svg>"; 

        return text;
    }

}

int ale_set_base_width(AleCrane* device, double new_base_width){ 

    if(ale_check_constraints(new_base_width, device->base_height, device->base, device->height, device->sliding,device->arm, device->angle) == false){
        return 1;
    }

    device->base_width = new_base_width;

    return 0;

}


int ale_set_base_height(AleCrane* device, double new_base_height){ 

    if(ale_check_constraints(device->base_width, new_base_height, device->base, device->height, device->sliding,device->arm, device->angle) == false){
        return 1;
    }

    device->base_height = new_base_height;

    return 0;

}


int ale_set_base(AleCrane* device, double new_base){ 

    if(ale_check_constraints(device->base_width, device->base_height, new_base, device->height, device->sliding,device->arm, device->angle) == false){
        return 1;
    }

    device->base = new_base;

    return 0;

}


int ale_set_height(AleCrane* device, double new_height){ 

    if(ale_check_constraints(device->base_width, device->base_height, device->base, new_height, device->sliding,device->arm, device->angle) == false){
        return 1;
    }

    device->height = new_height;

    return 0;

}

int ale_set_sliding(AleCrane* device, double new_sliding){ 

    if(ale_check_constraints(device->base_width, device->base_height, device->base, device->height, new_sliding,device->arm, device->angle) == false){
        return 1;
    }

    device->sliding = new_sliding;

    return 0;

}

int ale_set_arm(AleCrane* device, double new_arm){ 

    if(ale_check_constraints(device->base_width, device->base_height, device->base, device->height, device->sliding, new_arm, device->angle) == false){
        return 1;
    }

    device->arm = new_arm;

    return 0;

}

int ale_set_angle(AleCrane* device, double new_angle){ 

    if(ale_check_constraints(device->base_width, device->base_height, device->base, device->height, device->sliding,device->arm, new_angle) == false){
        return 1;
    }

    device->angle = new_angle;

    return 0;

}

void ale_save_to_file(string text, string file_name){

    ofstream ale_File("../../" + file_name);
 
    string string_to_write = text;
    
    
    ale_File << string_to_write;
    
    
    ale_File.close();

}


string ale_load_from_file( string file_name ){

    ifstream t("../../" + file_name);
    stringstream buffer;
    buffer << t.rdbuf();
    string text = buffer.str();
    
    return text;

}

AleCrane* ale_parse(string svg){

    double read_base_width;
    double read_base_height;
    double read_base;
    double read_height;
    double read_sliding;
    double read_arm;
    double read_angle;


    //getting base_width length

    string search = "rect x = \"400\" y = \"800\" width = \"";
    size_t found1 = svg.find(search) + search.size();
    size_t found2 = svg.find("\"", found1);

    string read_svg = svg.substr(found1, found2 - found1);

    read_base_width = stod(read_svg);

    //getting base_height length

    search = "height = \"";
    size_t found3 = svg.find(search, found1) + search.size();
    size_t found4 = svg.find("\"", found3);

    read_svg = svg.substr(found3, found4 - found3);

    read_base_height = stod(read_svg);


    //getting sliding length

    search = "rect x = \"";
    size_t found5 = svg.find(search, found3) + search.size();
    size_t found6 = svg.find("\"", found5);

    read_svg = svg.substr(found5, found6 - found5);

    read_sliding = stod(read_svg) -400 ;


    //getting base length

    search = "\" width = \"";
    size_t found7 = svg.find(search, found5) + search.size();
    size_t found8 = svg.find("\"", found7);

    read_svg = svg.substr(found7, found8 - found7);

    read_base = stod(read_svg);


    //getting height length

    search = "\" height = \"";
    size_t found9 = svg.find(search, found7) + search.size();
    size_t found10 = svg.find("\"", found9);

    read_svg = svg.substr(found9, found10 - found9);

    read_height = stod(read_svg);

    //getting angle length

    search = "rotate(";
    size_t found11 = svg.find(search, found9) + search.size();
    size_t found12 = svg.find(",", found11);

    read_svg = svg.substr(found11, found12 - found11);

    read_angle = stod(read_svg);

    cout << read_angle;

     //getting arm length

    search = "\" width = \"";
    size_t found13 = svg.find(search, found11) + search.size();
    size_t found14 = svg.find("\"", found13);

    read_svg = svg.substr(found13, found14 - found13);

    read_arm = stod(read_svg);

    if(ale_check_constraints(read_base_width, read_base_height, read_base, read_height, read_sliding, read_arm, read_angle) == false){
        return NULL;
    }

    AleCrane* device = ale_init(read_base_width, read_base_height, read_base, read_height, read_sliding, read_arm, read_angle);

    return device;
   

}