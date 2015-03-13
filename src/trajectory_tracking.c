
#include <math.h>

#include "trajectory_tracking.h"


/* public module prototypes */
uint8_t tracy_linear_controller(const tracking_error_t * current_error,
                                const reference_velocity_t * reference_velocity,
                                feedback_rule_t * output);

uint8_t tracy_set_controller_params(float fancy_greek_c, float g);

/* module variables */

static float param_fancy_greek_c = DEFAULT_PARAM_FANCY_GREEK_C;
static float param_g = DEFAULT_PARAM_G;

/* public function implementations */

uint8_t tracy_set_controller_params(float fancy_greek_c, float g)
{
    param_fancy_greek_c = fancy_greek_c;
    param_g = g;

    return 0;
}

uint8_t tracy_linear_controller(const tracking_error_t * current_error,
                                const reference_velocity_t * reference_velocity,
                                feedback_rule_t * output)
{
    float gain1 = 2 * param_fancy_greek_c;
    float tmp = reference_velocity->angular_velocity *
                reference_velocity->angular_velocity;
    tmp += param_g * reference_velocity->radial_velocity *
           reference_velocity->radial_velocity;
    gain1 *= sqrt(tmp);

    float gain2 = param_g * fabs(reference_velocity->radial_velocity);

    float sign_v = reference_velocity->radial_velocity < 0.0f ? -1.0f : 1.0f; 

    output->rule1 = gain1 * current_error->x_error;
    output->rule2 = sign_v * gain2 * current_error->y_error;
    output->rule2 += gain1 * current_error->theta_error;

    return 0;
}
