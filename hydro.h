#ifndef EMBEDDED_DEMO_LIBRARY_H
#define EMBEDDED_DEMO_LIBRARY_H

#define ON 1
#define OFF 0

#define LIGHT_OFF_TIME 36000 //10 hours in seconds

enum hydro_status_code{
    hydro_DEFAULT,
    hydro_PUMPING,
    hydro_ALL_OFF
};

typedef struct hydro_state{
    enum hydro_status_code status;
    int low_water_sense;
    int high_water_sense;
    int pump;
    int fan;
    int light;
    int timer_seconds;
} hydro_state;

hydro_state init_hydro(void);

hydro_state next_hydro_state(hydro_state);

#endif