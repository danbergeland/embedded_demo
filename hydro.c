#include "hydro.h"

hydro_state init_hydro(void){
    hydro_state hs = {.status = hydro_DEFAULT, .fan=OFF,.light=OFF,.pump=OFF,
            .high_water_sense=OFF,.low_water_sense=OFF,.timer_seconds=0};
    return hs;
}

hydro_state next_hydro_state(hydro_state prev_state){
    hydro_state hs = prev_state;
    if(prev_state.high_water_sense==ON)
    {
        hs.pump=ON;
        hs.status=hydro_PUMPING;
    }
    if(prev_state.low_water_sense==OFF)
    {
        hs.pump=OFF;
        hs.status=hydro_DEFAULT;
    }
    if(prev_state.timer_seconds>=0){
        hs.light=ON;
    }
    if(prev_state.timer_seconds>LIGHT_OFF_TIME){
        hs.light=OFF;
    }
    return hs;
}
