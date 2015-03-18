
#include <stdlib.h>
#include <math.h>

#include "trajectory_tracking.h"


/* public module prototypes */
void tracy_linear_controller(const tracking_error_t * current_error,
                             const reference_velocity_t * reference_velocity,
                             velocity_command_t * output);

uint8_t tracy_set_controller_params(float damping_coeff, float g);

/* module variables */

static float param_damping_coeff = DEFAULT_PARAM_DAMPING_COEFF;
static float param_g = DEFAULT_PARAM_G;

/* public function implementations */

uint8_t tracy_set_controller_params(float damping_coeff, float g)
{
    
    if(g <= 0) {
        return -1;
    }

    param_damping_coeff = damping_coeff;
    param_g = g;

    return 0;
}

void tracy_linear_controller(const tracking_error_t * current_error,
                             const reference_velocity_t * reference_velocity,
                             velocity_command_t * output)
{

    /* feedback control */
    float gain1 = 2 * param_damping_coeff;
    float tmp = reference_velocity->angular_velocity *
                reference_velocity->angular_velocity;
    tmp += param_g * reference_velocity->tangential_velocity *
           reference_velocity->tangential_velocity;
    gain1 *= sqrtf(tmp);

    float gain2 = param_g * fabs(reference_velocity->tangential_velocity);

    float sign_v = reference_velocity->tangential_velocity < 0.0f ? -1.0f : 1.0f; 

    output->tangential_velocity = gain1 * current_error->x_error;
    output->angular_velocity = sign_v * gain2 * current_error->y_error;
    output->angular_velocity += gain1 * current_error->theta_error;

    /* feedforward control */
    output->tangential_velocity += reference_velocity->tangential_velocity *
                                   cosf(current_error->theta_error);
    output->angular_velocity += reference_velocity->angular_velocity;
}
