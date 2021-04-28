#include "catch2/catch2.hpp"
#include "crane.h"

//testing ale_check_constraints function

TEST_CASE("ale_check_constraints should return true if all the constraints are respected and there are no negative length","[crane]"){

    REQUIRE( ale_check_constraints(200,60,50,500,90,400,45) == true);
}

TEST_CASE("ale_check_constraints should return false if the drawing is out of the space allowed","[crane]"){

    REQUIRE( ale_check_constraints(200,60,50,700,90,500,45) == false);
    REQUIRE( ale_check_constraints(200,110,50,500,90,400,45) == false);
    REQUIRE( ale_check_constraints(700,60,50,500,90,400,45) == false);
}

TEST_CASE("ale_check_constraints should return false if at least one of the length is negative","[crane]"){
    
    REQUIRE( ale_check_constraints(-200,60,50,500,90,400,45) == false);

}

TEST_CASE("ale_check_constraints should return false if angle is grater than 90 or lower than -90","[crane]"){
    
    REQUIRE( ale_check_constraints(200,60,50,500,90,400,-180) == false);

}

TEST_CASE("ale_check_constraints should return false if base_height > base_width","[crane]"){
    
    REQUIRE( ale_check_constraints(200,210,50,500,90,400,45) == false);
    
}

TEST_CASE("ale_check_constraints should return false if base > base_width","[crane]"){
    
    REQUIRE( ale_check_constraints(200,60,210,500,90,400,45) == false);
    
}

TEST_CASE("ale_check_constraints should return false if height <= base_width ","[crane]"){
    
    REQUIRE( ale_check_constraints(200,60,50,190,90,400,45) == false);
    
}

TEST_CASE("ale_check_constraints should return false if sliding > (base_width - base) > base","[crane]"){
    
    REQUIRE( ale_check_constraints(200,210,50,500,155,400,45) == false);
    
}

TEST_CASE("ale_check_constraints should return false if height <= base","[crane]"){
    
    REQUIRE( ale_check_constraints(200,210,50,45,90,400,45) == false);
    
}

TEST_CASE("ale_check_constraints should return false if arm > height","[crane]"){
    
    REQUIRE( ale_check_constraints(200,210,50,500,90,600,45) == false);
    
}

// testing ale_init function

TEST_CASE("ale_init should return a NULL pointer if constraints are not respected","[crane]"){

    REQUIRE( ale_init(200,-60,50,500,90,400,45) == NULL);
}

TEST_CASE("ale_init should succeed and return a pointer to a structure , which contains the legths given , if constraints are respected","[crane]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,45);

    REQUIRE(device != NULL);
    REQUIRE(device->base_width == 200);
    REQUIRE(device->base_height == 60);
    REQUIRE(device->base == 50);
    REQUIRE(device->height == 500);
    REQUIRE(device->sliding == 90);
    REQUIRE(device->arm == 400);
    REQUIRE(device->angle == 45);

    delete device;

}

// testing ale_set_base_width function

TEST_CASE("If the new length does no respect constraints the function ale_set_base_width should return 1","[craine]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,45);

    REQUIRE(ale_set_base_width(device,-190) == 1);
    
}

TEST_CASE("If the new length respects constraints the function ale_set_base_width should return 0","[craine]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,45);

    REQUIRE(ale_set_base_width(device,195) == 0);
    
}

TEST_CASE("Function ale_set_base_width should replace the old length with the new one","[craine]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,45);

    ale_set_base_width(device,195);

    REQUIRE(device->base_width == 195);
    
}

// testing ale_set_base_height function

TEST_CASE("If the new length does no respect constraints the function ale_set_base_height should return 1","[craine]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,45);

    REQUIRE(ale_set_base_height(device,-60) == 1);
    
}

TEST_CASE("If the new length respects constraints the function ale_set_base_height should return 0","[craine]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,45);

    REQUIRE(ale_set_base_height(device,65) == 0);
    
}

TEST_CASE("Function ale_set_base_height should replace the old length with the new one","[craine]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,45);

    ale_set_base_height(device,65);

    REQUIRE(device->base_height == 65);
    
}

// testing ale_set_base function


TEST_CASE("If the new length does not respect constraints the function ale_set_base should return 1","[craine]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,45);

    REQUIRE(ale_set_base(device,-50) == 1);
    
}

TEST_CASE("If the new length respects constraints the function ale_set_base should return 0","[craine]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,45);

    REQUIRE(ale_set_base(device, 55) == 0);
    
}

TEST_CASE("Function ale_set_base should replace the old length with the new one","[craine]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,45);

    ale_set_base(device, 55);

    REQUIRE(device->base == 55);
    
}

// testing ale_set_height function

TEST_CASE("If the new length does not respect constraints the function ale_set_height should return 1","[craine]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,45);

    REQUIRE(ale_set_height(device,-500) == 1);
    
}

TEST_CASE("If the new length respects constraints the function ale_set_height should return 0","[craine]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,45);

    REQUIRE(ale_set_height(device, 510) == 0);
    
}

TEST_CASE("Function ale_set_height should replace the old length with the new one","[craine]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,45);

    ale_set_height(device, 510);

    REQUIRE(device->height == 510);
    
}

// testing ale_set_sliding function

TEST_CASE("If the new length does not respect constraints the function ale_set_sliding should return 1","[craine]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,45);

    REQUIRE(ale_set_sliding(device,-90) == 1);
    
}

TEST_CASE("If the new length respects constraints the function ale_set_sliding should return 0","[craine]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,45);

    REQUIRE(ale_set_sliding(device, 95) == 0);
    
}

TEST_CASE("Function ale_set_slidingshould replace the old length with the new one","[craine]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,45);

    ale_set_sliding(device, 95);

    REQUIRE(device->sliding == 95);
    
}

// testing ale_set_arm function

TEST_CASE("If the new length does not respect constraints the function ale_set_arm should return 1","[craine]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,45);

    REQUIRE(ale_set_arm(device,-400) == 1);
    
}

TEST_CASE("If the new length respects constraints the function ale_set_arm should return 0","[craine]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,45);

    REQUIRE(ale_set_arm(device, 410) == 0);
    
}

TEST_CASE("Function ale_set_arm should replace the old length with the new one","[craine]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,45);

    ale_set_arm(device, 95);

    REQUIRE(device->arm == 95);
    
}

// testing ale_set_angle function

TEST_CASE("If the new length respects constraints the function ale_set_angle should return 0","[craine]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,45);

    REQUIRE(ale_set_angle(device, 50) == 0);
    
}

TEST_CASE("Function ale_set_angle should replace the old length with the new one","[craine]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,45);

    ale_set_angle(device, 50);

    REQUIRE(device->angle == 50);
    
}

// testing ale_to_svg

TEST_CASE("ale_to_svg should create a string with the right svg code", "[crane]"){

    string s = ale_load_from_file("/home/alessandro/first-homework/crane3.svg");

    AleCrane* device = ale_init(200,60,50,500,90,400,0);

    bool with_measures = 0;

    string r = ale_to_svg(device, 0);

    REQUIRE(r == s);

}

TEST_CASE("ale_to_svg should write ERROR if the device pointer is NULL", "[crane]"){

    AleCrane* device = ale_init(200,60,50,500,90,400,180);

    bool with_measures = 0;

    string r = ale_to_svg(device, 0);

    REQUIRE(r == "ERROR");

}



//testing ale_save_to_file


TEST_CASE("ale_save_to_file should save in the right filea a given string", "[crane]"){

    string s = "Hakunamatata";

    ale_save_to_file(s, "/home/alessandro/first-homework/PROVA.md");

    string r = ale_load_from_file("/home/alessandro/first-homework/PROVA.md");

    REQUIRE(r == s);

}



//testing load_from_file

TEST_CASE("ale_load_form file should return a string with the cintents of yhe file","[crane]"){

    string s = ale_load_from_file("PROVA2.md");

    REQUIRE(s == "Ciao, come stai?");
}


//testing ale_parse

TEST_CASE("ale_parse should return a NULL pointer if the crane drawing in the svg file does not respect the constarints" ,"[crane]"){

    string s = ale_load_from_file("/home/alessandro/first-homework/crane2.svg");

    REQUIRE(ale_parse(s) == NULL);
}

TEST_CASE("ale_parse should return a non NULL pointer if the crane drawing in the svg file respects constarints", "[crane]"){
    
    string s = ale_load_from_file("/home/alessandro/first-homework/crane.svg");

    REQUIRE(ale_parse(s) != NULL);

}

TEST_CASE("ale_parse should return a Crane structure with the read length","[crane]"){


    string s = ale_load_from_file("/home/alessandro/first-homework/crane.svg");

    AleCrane* device = ale_parse(s);

    REQUIRE(device->base_width == 200);
    REQUIRE(device->base_height == 60);
    REQUIRE(device->base == 50);
    REQUIRE(device->height == 500);
    REQUIRE(device->sliding == 90);
    REQUIRE(device->arm == 400);
    REQUIRE(device->angle == 0);

}










