#include "catch2/catch2.hpp"
#include "crane.h"

//testing ale_check_constraints function

TEST_CASE("ale_check_constraints should return true if all the constraints are respected and there are no negative length","[crane]"){

    REQUIRE( ale_check_constraints(200,60,50,500,90,400,45) == true);
}

TEST_CASE("ale_check_constraints should return false if at least one of the length is negative","[crane]"){
    
    REQUIRE( ale_check_constraints(-200,60,50,500,90,400,45) == false);

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

TEST_CASE("ale_init should return a NULL pinter if constraints are not respected","[crane]"){

    REQUIRE( ale_init(200,-60,50,500,90,400,45) == NULL);
}

TEST_CASE("ale_init should succeed and return a pointer to a structure , which contains the legths given , if constraints are respected","[crane]"){

    Crane* device = ale_init(200,-60,50,500,90,400,45);

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

// testing ale_set functions




