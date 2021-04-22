#include "crane.h"

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>

using namespace std;

int main() {

    double base_width;
    double base_height;
    double base;
    double height;
    double sliding;
    double arm;
    double angle;

    cout<< "Device creation, please insert the lengths:" << endl;

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
    cin >> base_height;
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

    Crane* device = ale_init(base_width, base_height, base, height, sliding, arm, angle);

    string svg_code = ale_to_svg(device);

    ale_save_to_file(svg_code,"newcrane.svg");

    cout << "Svg file has been created" << endl;

    cout << "You can change legths:" << endl;
    cout << "Press 1 to change base_width;" << endl;
    cout << "Press 2 to change base_height;" << endl;
    cout << "Press 3 to change base;" << endl;
    cout << "Press 4 to change height;" << endl;
    cout << "Press 5 to change sliding;" << endl;
    cout << "Press 6 to change arm;" << endl;
    cout << "Press 7 to change angle;" << endl;
    cout << "Press any different key if you are satisfied of the drawing"<< endl;

    int choice;

    while(choice != 1 && 2 && 3 && 4 && 5 && 6 && 7){

        cin >> choice;

        if(choice = 1){

            double new_base_width;

            cout << "New base_width:";

            cin >> new_base_width;

            ale_set_base_width(device, new_base_width);

            string svg_code = ale_to_svg(device);

            ale_save_to_file(svg_code, "newcrane.svg");

        }

        if(choice = 2){

            double new_base_height;

            cout << "New base_height:";

            cin >> new_base_height;

            ale_set_base_height(device, new_base_height);

            string svg_code = ale_to_svg(device);

            ale_save_to_file(svg_code, "newcrane.svg");

        }

        if(choice = 3){

            double new_base;

            cout << "New base:";

            cin >> new_base;

            ale_set_base(device, new_base);

            string svg_code = ale_to_svg(device);

            ale_save_to_file(svg_code, "newcrane.svg");

        }

        if(choice = 4){

            double new_height;

            cout << "New height:";

            cin >> new_height;

            ale_set_height(device, new_height);

            string svg_code = ale_to_svg(device);

            ale_save_to_file(svg_code, "newcrane.svg");

        }

        if(choice = 5){

            double new_sliding;

            cout << "New sliding:";

            cin >> new_sliding;

            ale_set_sliding(device, new_sliding);

            string svg_code = ale_to_svg(device);

            ale_save_to_file(svg_code, "newcrane.svg");

        }

        if(choice = 6){

            double new_arm;

            cout << "New arm:";

            cin >> new_arm;

            ale_set_arm(device, new_arm);

            string svg_code = ale_to_svg(device);

            ale_save_to_file(svg_code, "newcrane.svg");

        }

        if(choice = 7){

            double new_angle;

            cout << "New angle:";

            cin >> new_angle;

            ale_set_angle(device, new_angle);

            string svg_code = ale_to_svg(device);

            ale_save_to_file(svg_code, "newcrane.svg");

        }
    }











   
    
}
