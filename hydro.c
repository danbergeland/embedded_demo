#include "hydro.h"

#ifdef TEST
    #include "HAL_mock.h"
#else
    #include "HAL.h"
#endif


#define LIGHT_OFF_TIME 36000 //36000 = 10 hours in seconds
#define TIMER_ROLLOVER 43200 //43200 = 12 hours in seconds

//private
hydro_state handle_high_water_sense(hydro_state state){
    state.pump=ON;
    state.status=hydro_PUMPING;
    state.fan=OFF;
    return state;
}

//private
hydro_state handle_low_water_sense(hydro_state state){
    state.pump=OFF;
    state.status=hydro_DEFAULT;
    state.fan=ON;
    return state;
}

hydro_state init_hydro(void){
    hydro_state hs = {
            .status = hydro_DEFAULT,
            .fan=OFF,
            .light=OFF,
            .pump=OFF,
            .high_water_sense=OFF,
            .low_water_sense=OFF,
            .timer_seconds=0};
    return hs;
}

hydro_state next_hydro_state(hydro_state prev_state){
    hydro_state next_state = prev_state;
    if(prev_state.high_water_sense==ON)
    {
        next_state = handle_high_water_sense(prev_state);
    }
    else if(prev_state.low_water_sense==OFF)
    {
        next_state = handle_low_water_sense(prev_state);
    }

    if(prev_state.timer_seconds>TIMER_ROLLOVER){
        prev_state.timer_seconds=0;
        next_state.timer_seconds = 0;
    }

    if(prev_state.timer_seconds>LIGHT_OFF_TIME){
        next_state.light=OFF;
    }
    else{
        next_state.light=ON;
    }

    return next_state;
}


hydro_state read_hydro_inputs(hydro_state last_state){
    hydro_state return_vals = last_state;
    return_vals.high_water_sense = get_high_water_sense();
    return_vals.low_water_sense = get_low_water_sense();

    return return_vals;
}

void set_hydro_outputs(hydro_state desired_state){
    set_fan(desired_state.fan);
    set_pump(desired_state.pump);
    set_light(desired_state.light);
}
