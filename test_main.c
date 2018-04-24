//
// Created by Dan Bergeland on 4/9/18.
//

#include <stdio.h>
#include "hydro.h"
#include "HAL_mock.h"

typedef struct test_counter{
    int total_tests;
    int failed_tests;
} test_counter;

test_counter assert_true(test_counter tc, int expression, char* description){
    tc.total_tests+=1;
    if(!expression){
        tc.failed_tests+=1;
        printf(" -- FAIL -- %s\n",description);
    }
    return tc;
}

test_counter test_init_hydro_is_correct(test_counter tc){
    hydro_state hs = init_hydro();
    printf("test_init_hydro\n");
    tc = assert_true(tc, hs.status==hydro_DEFAULT, "Wrong init status\n");
    return tc;
}

test_counter test_pump_when_high_water_detected(test_counter tc){
    hydro_state hs = init_hydro();
    printf("test_pump_when_high_water\n");
    hs.high_water_sense = ON;
    hs.low_water_sense = ON;
    hs = next_hydro_state(hs);
    tc = assert_true(tc, hs.pump==ON,"Pump not on.");
    tc = assert_true(tc, hs.status==hydro_PUMPING,"Status not pumping.");
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

    tc = assert_true(tc, hs.pump==OFF,"Pump should be off when low water");
    tc = assert_true(tc, hs.status==hydro_DEFAULT,"State should be default, not pumping");
    return tc;
}

test_counter test_lights_on_between_0and10_hours(test_counter tc){
    hydro_state hs = init_hydro();
    printf("test_lights_on_between_0and10_hours\n");

    hs = next_hydro_state(hs);

    tc = assert_true(tc, hs.light==ON, "Light should be on when time is 0.");
    tc = assert_true(tc, hs.status == hydro_DEFAULT, "State should be default.");

    //Set to 10 hours, in seconds
    hs.timer_seconds = 10*60*60;
    hs = next_hydro_state(hs);

    tc = assert_true(tc, hs.light==ON, "Light should be on when time is 10 hours.");

    hs.timer_seconds = 10*60*60+1;
    hs = next_hydro_state(hs);

    tc = assert_true(tc, hs.light==OFF, "Light should be off, 1 second after 10 hours.");

    return tc;
}

test_counter test_counter_rolls_to_0_after_12hours(test_counter tc){
    hydro_state hs = init_hydro();
    printf("test_counter_rolls_to_0_after_12hours\n");

    hs.timer_seconds = 12*60*60;
    hs = next_hydro_state(hs);
    tc = assert_true(tc, hs.timer_seconds==12*60*60, "Timer should go up to 12 hours\n");

    hs.timer_seconds = 12*60*60+1;
    hs = next_hydro_state(hs);
    tc = assert_true(tc, hs.timer_seconds==0, "Timer should roll over to 0 over 12 hours\n");
    return tc;
}

test_counter test_fan_runs_opposite_of_pump(test_counter tc){
    hydro_state hs = init_hydro();
    printf("test_fan_runs_opposite_of_pump\n");


    hs.low_water_sense=OFF;
    hs = next_hydro_state(hs);
    tc = assert_true(tc, hs.fan==ON, "Fan should be on when pump is off\n");
    tc = assert_true(tc, hs.pump==OFF, "Pump should be off\n");

    hs.high_water_sense=ON;
    hs.low_water_sense=ON;
    hs = next_hydro_state(hs);
    tc = assert_true(tc, hs.fan==OFF, "Fan should be off when pump is on\n");
    tc = assert_true(tc, hs.pump==ON, "Pump should be on.\n");
    return tc;
}


int main(void){
    init_HAL_mock();
    test_counter tc;
    tc.failed_tests=0;
    tc.total_tests=0;
    printf("Running Tests!\n");
    tc = test_init_hydro_is_correct(tc);
    tc = test_pump_when_high_water_detected(tc);
    tc = test_stop_pump_when_low_water(tc);
    tc = test_lights_on_between_0and10_hours(tc);
    tc = test_counter_rolls_to_0_after_12hours(tc);
    tc = test_fan_runs_opposite_of_pump(tc);

    printf("Ran %d tests.  %d failed.\n",tc.total_tests,tc.failed_tests);
   return 0;
}
