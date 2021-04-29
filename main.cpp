#include "crane.h"
#include "EB_Device.h"
#include "alemachine.h"

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>

using namespace std;

string error_message = "ERROR: constraints not respected!";

int main() {
   
    double base_width;
    double base_height;
    double base;
    double height;
    double sliding;
    double arm;
    double angle;

    cout<< "Crane creation, please insert the lengths:" << endl;

    cout << "Base width: ";
    cin >> base_width;
    cout << endl;

    cout << "Base height: ";
    cin >> base_height;
    cout << endl;

    cout << "Base: ";
    cin >> base;
    cout << endl;

    cout << "Height: ";
    cin >> height;
    cout << endl;

    cout << "Sliding: ";
    cin >> sliding;
    cout << endl;

    cout << "Arm: ";
    cin >> arm;
    cout << endl;

    cout << "Angle: ";
    cin >> angle;
    cout << endl;
    
    AleCrane* device = ale_init(base_width, base_height, base, height, sliding, arm, angle);

    if(device == NULL){
        cout << error_message << endl;
        exit(1);
    }

    bool with_meausures;
    
    cout << "Do you want to add measures to you drawing? Press 1 if yo do, press 0 if you don't: ";
    cin >> with_meausures;
    cout << endl;

    string file1;
    cout << "Please enetr the file name you want to save the file in: ";
    cin >> file1;
    cout << endl;

    string svg_code = ale_to_svg(device,with_meausures);

    ale_save_to_file(svg_code,file1);

    cout << "Svg file has been created" << endl;

    char choice ;

    do{
        

        cout << "You can change legths:" << endl;
        cout << "Press 1 to change base_width;" << endl;
        cout << "Press 2 to change base_height;" << endl;
        cout << "Press 3 to change base;" << endl;
        cout << "Press 4 to change height;" << endl;
        cout << "Press 5 to change sliding;" << endl;
        cout << "Press 6 to change arm;" << endl;
        cout << "Press 7 to change angle;" << endl;
        cout << "Press any other keys if you are satisfied of the drawing"<< endl;

            
        cin >> choice;

        if(choice == '1'){

            double new_base_width;

            cout << "New base_width:";

            cin >> new_base_width;

            ale_set_base_width(device, new_base_width);

            if( ale_set_base_width(device, new_base_width) == 1){
                cout << error_message << endl;
                exit(1);
            }

            string svg_code = ale_to_svg(device,with_meausures);

            ale_save_to_file(svg_code, file1);

        }

        if(choice == '2'){

            double new_base_height;

            cout << "New base_height:";

            cin >> new_base_height;

            ale_set_base_height(device, new_base_height);

            if(ale_set_base_height(device, new_base_height) == 1){
                cout << error_message << endl;
                exit(1);
            }

            string svg_code = ale_to_svg(device,with_meausures);

            ale_save_to_file(svg_code, file1);

        }

        if(choice == '3'){

            double new_base;

            cout << "New base:";

            cin >> new_base;

            ale_set_base(device, new_base);
            
            if( ale_set_base(device, new_base) == 1){
                cout << error_message << endl;
                exit(1);
            }

            string svg_code = ale_to_svg(device,with_meausures);

            ale_save_to_file(svg_code, file1);

        }

        if(choice == '4'){

            double new_height;

            cout << "New height:";

            cin >> new_height;

            ale_set_height(device, new_height);

            if(ale_set_height(device, new_height) == 1){
                cout << error_message << endl;
                exit(1);  
            }

            string svg_code = ale_to_svg(device,with_meausures);

            ale_save_to_file(svg_code, file1);

        }

        if(choice == '5'){

            double new_sliding;

            cout << "New sliding:";

            cin >> new_sliding;

            ale_set_sliding(device, new_sliding);

            if(ale_set_sliding(device, new_sliding) == 1){
                cout << error_message << endl;
                exit(1);
            }

            string svg_code = ale_to_svg(device,with_meausures);

            ale_save_to_file(svg_code, file1);

        }

        if(choice == '6'){

            double new_arm;

            cout << "New arm:";

            cin >> new_arm;

            ale_set_arm(device, new_arm);

            if(ale_set_arm(device, new_arm) == 1){
                cout << error_message << endl;
                exit(1);
            }

            string svg_code = ale_to_svg(device,with_meausures);

            ale_save_to_file(svg_code, file1);

        }

        if(choice == '7'){

            double new_angle;

            cout << "New angle:";

            cin >> new_angle;

            ale_set_angle(device, new_angle);

            if(ale_set_angle(device, new_angle) == 1){
                cout << error_message << endl;
                exit(1);
            }

            string svg_code = ale_to_svg(device,with_meausures);

            ale_save_to_file(svg_code, file1);

        }
        
    } while(choice == '1' || choice == '2' || choice == '3' || choice == '4' || choice == '5' || choice == '6' || choice == '7' );

    
    cout << "your drawing legths are:" << endl;
    cout << "base_width: " << device->base_width << endl;
    cout << "base_height: " << device->base_height << endl;
    cout << "base: " << device->base << endl;
    cout << "height: " << device->height << endl;
    cout << "sliding: " << device->sliding << endl;
    cout << "arm: " << device->arm << endl;
    cout << "angle: " << device->angle << endl;


    cout << "You can now create a machine made of a crane and a carrello-gru, please insert carrello gru lengths: " << endl;

    double lenght_shaft;
    double width_towtruck;
    double width_platform;
    double rotation;
    double sliding2;

    cout << "insert lenght_shaft: ";
    cin >> lenght_shaft;
    cout << endl;

    cout << "insert width_towtruck: ";
    cin >> width_towtruck;
    cout << endl;

    cout << "insert width_platform: ";
    cin >> width_platform;
    cout << endl;

    cout << "insert rotation: ";
    cin >> rotation;
    cout << endl;

    cout << "sliding of carrello: ";
    cin >> sliding2;
    cout << endl;

    EbDevice* device2 = eb_init(lenght_shaft,width_towtruck,width_platform,rotation,sliding);

    if(device == NULL){
        cout << error_message << endl;
        exit(1);
    }

    int istances;
    cout << "how many istances of the machine you want? " ;
    cin >> istances;
    cout << endl;

    double platform_sliding;
    cout << "You can choice the sliding of the platform on the crane's arm: ";
    cin >> platform_sliding;
    cout << endl;


    AleMachine* machine = ale_machine_init(device, device2,platform_sliding,istances );

    if(machine == NULL){
        cout << error_message << endl;
        exit(1);
    }

    string file2;
    cout << "Please insert the file name you want to save machine in: ";
    cin >> file2;
    cout << endl;

    string svg_machine = ale_machine_to_svg(machine);

    eb_save_to_file(svg_machine, file2);

    cout << "Machine svg file has been created!" << endl;

    char choice2;
    cout <<"Do you want to see if two machine you save are the same?" << endl;
    cout << "Press y if you want , any other differnt keys if you don't" <<endl;
    cin >> choice2;

    if(choice2 == 'y'){

        string read1;
        string read2;

        cout << "First machine file name: ";
        cin >> read1;
        cout << endl;

        cout << "Second machine file name: ";
        cin >> read2;
        cout << endl;

        string w = eb_read_from_file(read1);
        string v = eb_read_from_file(read2);

        AleMachine* machine2 = ale_machine_parse(w);
        AleMachine* machine3 = ale_machine_parse(v);

        if(ale_are_equal(machine2,machine3) == true){

            cout << "The machines are equal!!" << endl;

        } 

        cout << "The machines are NOT equal" << endl;

        ale_destroy(machine2);
        ale_destroy(machine3);
    }


    cout << "END" << endl;
















    ale_destroy(machine);
    

    delete device;
    delete device2;



   


   
    
}
