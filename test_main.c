//
// Created by Dan Bergeland on 4/9/18.
//

#include <stdio.h>
#include "hydro.h"

typedef struct test_counter{
    int total_tests;
    int failed_tests;
} test_counter;

test_counter test_init_hydro_is_correct(test_counter tc){
    hydro_state hs = init_hydro();
    printf("test_init_hydro\n");
    tc.total_tests+=1;
    if(hs.status!=hydro_DEFAULT){
        printf("FAIL - wrong status!\n");
        tc.failed_tests+=1;
    }

    return tc;
}

test_counter test_pump_when_high_water_detected(test_counter tc){
    hydro_state hs = init_hydro();
    printf("test_pump_when_high_water\n");
    hs.high_water_sense = ON;
    hs.low_water_sense = ON;
    hs = next_hydro_state(hs);
    tc.total_tests+=1;
    if(hs.pump == OFF) {
        tc.failed_tests+=1;
        printf("FAIL - Pump not on\n");
    }
    tc.total_tests+=1;
    if(hs.status != hydro_PUMPING){
        tc.failed_tests+=1;
        printf("FAIL - Status not pumping\n");
    }
    return tc;
}

test_counter test_stop_pump_when_low_water(test_counter tc){
    hydro_state hs = init_hydro();
    printf("test_stop_pump_when_low_water\n");
    hs.status=hydro_PUMPING;
    hs.pump = ON;
    hs.high_water_sense = OFF;
    hs.low_water_sense = OFF;
    hs = next_hydro_state(hs);
    tc.total_tests+=1;
    if(hs.pump == ON){
        tc.failed_tests+=1;
        printf("FAIL - Pump on\n");
    }

    tc.total_tests+=1;
    if(hs.status != hydro_DEFAULT){
        tc.failed_tests+=1;
        printf("FAIL - State should be default\n");
    }
    return tc;
}


int main(void){
    test_counter tc;
    tc.failed_tests=0;
    tc.total_tests=0;
    printf("Running Tests!\n");
    tc = test_init_hydro_is_correct(tc);
    tc = test_pump_when_high_water_detected(tc);
    tc = test_stop_pump_when_low_water(tc);

    printf("Ran %d tests.  %d failed.\n",tc.total_tests,tc.failed_tests);
   return 0;
}
