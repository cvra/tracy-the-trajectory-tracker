
#ifndef __TRACY__
#define __TRACY__

#include <stdint.h>

#define DEFAULT_PARAM_FANCY_GREEK_C (0.7f)
#define DEFAULT_PARAM_G (60.0f)

typedef struct {
    float rule1;
    float rule2;
} feedback_rule_t;

typedef struct {
    float x_error;
    float y_error;
    float theta_error;
} tracking_error_t;

typedef struct {
    float radial_velocity;
    float angular_velocity;
} reference_velocity_t;

uint8_t tracy_linear_controller(const tracking_error_t * current_error,
                                const reference_velocity_t * reference_velocity,
                                feedback_rule_t * output);

uint8_t tracy_set_controller_params(float param_fancy_greek_c, float param_g);

#endif
