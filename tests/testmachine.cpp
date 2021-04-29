#include "../include/catch2/catch2.hpp"
#include "../include/crane.h"
#include "../include/EB_Device.h"
#include "../include/alemachine.h"

//ale_check_machine_constraints tests

TEST_CASE("ale_check_machine__constraints should return true if all the constraints are respected", "[machine]"){

    AleCrane* device1 = ale_init(200,60,50,600,90,500,0);
    EbDevice* device2 = eb_init(300,100,200,-20,50);

    REQUIRE(ale_check_machine_constraints(device1, device2, 50) == true);

    delete device2;
    delete device1;
}

TEST_CASE("ale_check_machine__constraints should return false if the angle of the crane is not zero", "[machine]"){

    AleCrane* device1 = ale_init(200,60,50,600,90,500,45);
    EbDevice* device2 = eb_init(300,100,200,-20,50);

    REQUIRE(ale_check_machine_constraints(device1, device2, 100) == false);

    delete device2;
    delete device1;
}

TEST_CASE("ale_check_machine__constraints should return false if the rotation of carrello-gru is lower than -80 o bigger than 0", "[machine]"){

    AleCrane* device1 = ale_init(200,60,50,600,90,500,0);
    EbDevice* device2 = eb_init(300,100,200,20,50);

    REQUIRE(ale_check_machine_constraints(device1, device2, 100) == false);

    delete device2;
    delete device1;
}

TEST_CASE("ale_check_machine__constraints should return false if the carrello-gru go out of the crane's arm", "[machine]"){

    AleCrane* device1 = ale_init(200,60,50,600,90,500,0);
    EbDevice* device2 = eb_init(300,100,200,-20,1000);

    REQUIRE(ale_check_machine_constraints(device1, device2, 100) == false);

    delete device2;
    delete device1;
}

TEST_CASE("ale_check_machine__constraints should return false if the drawing constraints are not respected", "[machine]"){

    AleCrane* device1 = ale_init(200,60,50,600,90,500,0);
    EbDevice* device2 = eb_init(300,100,200,-20,1000);

    REQUIRE(ale_check_machine_constraints(device1, device2, 100) == false);

    delete device2;
    delete device1;
}



TEST_CASE("ale_check_machine__constraints should return false if sliding + towtruck width are mora than 3/4 of the crane arm", "[machine]"){

    AleCrane* device1 = ale_init(200,60,50,600,90,500,0);
    EbDevice* device2 = eb_init(300,1000,200,-20,50);

    REQUIRE(ale_check_machine_constraints(device1, device2, 100) == false);

    delete device2;
    delete device1;
}

//ale_machine_init tests


TEST_CASE("ale_machine_init should return a NULL pointer if constraints are not respected", "[machine]"){

    AleCrane* device1 = ale_init(200,60,50,600,90,500,20);
    EbDevice* device2 = eb_init(300,1000,200,-20,50);

    AleMachine* machine = ale_machine_init(device1, device2, 100, 2);

    REQUIRE(machine == NULL);

    
    delete device1;
    delete device2;
    
}
    



TEST_CASE("ale_machine_init should return a  non NULL pointer if constraints are  respected", "[machine]"){

    AleCrane* device1 = ale_init(200,60,50,600,90,500,0);
    EbDevice* device2 = eb_init(300,100,200,-20,50);

    AleMachine* machine = ale_machine_init(device1, device2, 50, 2);

    REQUIRE(machine != NULL);

    ale_destroy(machine);
    delete device1;
    delete device2;
}


//ale_set_platform_sliding tests



TEST_CASE("If the new length does not respect constraints the function ale_set_platform_sliding should return 1","[craine]"){

    AleCrane* device1 = ale_init(200,60,50,600,90,500,20);
    EbDevice* device2 = eb_init(300,1000,200,-20,50);

    AleMachine* machine = ale_machine_init(device1, device2, 100, 2);

    REQUIRE(ale_set_platform_sliding(machine, 600) == 1);

    delete device2;
    delete device1;
    ale_destroy(machine);

        
}



TEST_CASE("If the new length  respect constraints the function ale_set_platform_sliding should return 0","[craine]"){

    AleCrane* device1 = ale_init(200,60,50,600,90,500,0);
    EbDevice* device2 = eb_init(300,100,200,-20,50);

    AleMachine* machine = ale_machine_init(device1, device2, 100, 2);

    REQUIRE(ale_set_platform_sliding(machine, 0) == 0);

    delete device2;
    delete device1;

    ale_destroy(machine);
    
}



//ale_machine_to_svg tests

TEST_CASE("ale_machine_to_svg shoul return the right string if th machine is ok","[machine]"){

    AleCrane* device1 = ale_init(200,60,50,600,90,500,0);
    EbDevice* device2 = eb_init(300,100,200,-0,50);

    AleMachine* machine =ale_machine_init(device1,device2,0,3);

    string s = ale_machine_to_svg(machine);

    string r = eb_read_from_file("/home/alessandro/first-homework/provamachine3.svg");

    REQUIRE(s == r);

    
    delete device1;
    delete device2;

}


TEST_CASE("ale_machine_to_svg should return an error string if th machine pointer is NULLk","[machine]"){

    

    AleMachine* machine = NULL;

    string s = ale_machine_to_svg(machine);


    REQUIRE(s == "ERRORE");

    

}


//ale_machine_parse tests

TEST_CASE("ale_parse should return a NULL pointer if the machine drawing in the svg file does not respect the constarints" ,"[crane]"){

    //string s = ale_load_from_file("wrongmachine2.svg");
    string s = eb_read_from_file("/home/alessandro/first-homework/wrongmachine.svg");


    REQUIRE(ale_machine_parse(s) == NULL);
}


TEST_CASE("ale_machine_parse should return a non NULL pointer but a pointer to a AleMachine structure with the read length","[crane]"){


    
    string s = eb_read_from_file("provamachine0.svg");
    AleMachine* machine = ale_machine_parse(s);

    REQUIRE(machine != NULL);
    
    REQUIRE(machine->arr1[0]->base_width == 200);
    REQUIRE(machine->arr1[0]->base_height == 60);
    REQUIRE(machine->arr1[0]->base == 50);
    REQUIRE(machine->arr1[0]->height == 600);
    REQUIRE(machine->arr1[0]->arm == 500);
    REQUIRE(machine->arr1[0]->angle == 0);
    REQUIRE(machine->arr2[0]->length_shaft == 300);
    REQUIRE(machine->arr2[0]->width_towtruck == 100);
    REQUIRE(machine->arr2[0]->width_platform == 200);
    REQUIRE(machine->arr2[0]->rotation == -20);
    REQUIRE(machine->arr2[0]->sliding == 50);
    

    ale_destroy(machine);
   


}

//ale_are_equal tests

TEST_CASE("ale_are_equal function shoud return true if 2 machine are equal","[machine]"){

    AleCrane* device1 = ale_init(200,60,50,600,90,500,0);
    EbDevice* device2 = eb_init(300,100,200,-20,50);

    AleCrane* device3 = ale_init(200,60,50,600,90,500,0);
    EbDevice* device4 = eb_init(300,100,200,-20,50);

    AleMachine* machine1 = ale_machine_init(device1,device2,100,2);
    AleMachine* machine2 = ale_machine_init(device1,device2,100,2);

    REQUIRE(ale_are_equal(machine1,machine2) == true);

    ale_destroy(machine1);
    ale_destroy(machine2);

    delete device1;

    delete device2;

    delete device3;

    delete device4;


}
 
TEST_CASE("ale_are_equal function shoud return flase if 2 machine are not equal","[machine]"){

    AleCrane* device1 = ale_init(201,60,50,600,90,500,0);
    EbDevice* device2 = eb_init(300,100,200,-20,50);

    AleCrane* device3 = ale_init(200,60,50,600,90,500,0);
    EbDevice* device4 = eb_init(300,100,200,-20,50);

    AleMachine* machine1 = ale_machine_init(device1,device2,100,2);
    AleMachine* machine2 = ale_machine_init(device3,device4,100,2);

    REQUIRE(ale_are_equal(machine1,machine2) == false);

    ale_destroy(machine1);
    ale_destroy(machine2);

    delete device1;

    delete device2;

    delete device3;

    delete device4;


}

//ale_destroy tests
TEST_CASE("ale_destroy should return 1 if machine pointer is NULL","[machine]"){
    AleMachine* machine = NULL;

    REQUIRE(ale_destroy(machine) == 1);
}

TEST_CASE("ale_destroy should return 0 if machine pointer is NULL","[machine]"){

    AleCrane* device1 = ale_init(201,60,50,600,90,500,0);
    EbDevice* device2 = eb_init(300,100,200,-20,50);
    AleMachine* machine = ale_machine_init(device1,device2,100,2);

    REQUIRE(ale_destroy(machine) == 0);
}

TEST_CASE("find_string should find a string into a bigger one"){

    string s = "Ciao, come stai?";

    REQUIRE(find_string(s, "Ci", "?") == "Ciao, come stai");

}
