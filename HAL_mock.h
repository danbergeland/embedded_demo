//
// Created by Dan Bergeland on 4/24/18.
// This is mocked for the library testing only.

#ifndef EMBEDDED_DEMO_HAL_H
#define EMBEDDED_DEMO_HAL_H

void init_HAL_mock(void);

int get_high_water_sense(void);
int get_low_water_sense(void);

void set_fan(int);
void set_pump(int);
void set_light(int);

typedef struct mock_state{
    int high_water_sense;
    int low_water_sense;
    int fan_state;
    int light_state;
    int pump_state;
} mock_state;

#endif //EMBEDDED_DEMO_HAL_H
