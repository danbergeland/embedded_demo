//
// Created by Dan Bergeland on 4/24/18.
//
#include "HAL_mock.h"

mock_state local_state;

void init_HAL_mock(void){
    mock_state init_state = {
            .fan_state=0,
            .light_state=0,
            .pump_state=0,
            .low_water_sense=0,
            .high_water_sense=0};
    local_state = init_state;
}

int get_high_water_sense(void){
    return local_state.high_water_sense;
}

int get_low_water_sense(void){
    return local_state.low_water_sense;
}

void set_fan(int new_state){
    local_state.fan_state = new_state;
}
void set_pump(int new_state){
    local_state.pump_state = new_state;
}
void set_light(int new_state){
    local_state.light_state = new_state;
}