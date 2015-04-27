
#include <stdlib.h>
#include <math.h>

#include "trajectory_tracking.h"


/* public module prototypes */
void tracy_linear_controller(const struct tracking_error * current_error,
                             const struct robot_velocity * reference_velocity,
                             struct robot_velocity * output);

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

void tracy_linear_controller(const struct tracking_error * current_error,
                             const struct robot_velocity * reference_velocity,
                             struct robot_velocity * output)
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

void tracy_global_error_to_local(struct tracking_error *error, float heading)
{
    float c, s, x, y;
    c = cosf(heading);
    s = sinf(heading);

    x = error->x_error * c + error->y_error * s;
    y = error->x_error * -s + error->y_error * c;

    error->x_error = x;
    error->y_error = y;
}
