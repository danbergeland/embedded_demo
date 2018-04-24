#ifndef EMBEDDED_DEMO_LIBRARY_H
#define EMBEDDED_DEMO_LIBRARY_H

#define ON 1
#define OFF 0

//#define TEST

enum hydro_status_code{
    hydro_DEFAULT,
    hydro_PUMPING,
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

hydro_state read_hydro_inputs(hydro_state);

void set_hydro_outputs(hydro_state);

#endif
