
#ifndef __TRACY__
#define __TRACY__

#include <stdint.h>

#define DEFAULT_PARAM_DAMPING_COEFF (0.7f)
#define DEFAULT_PARAM_G (60.0f)

/**
 * output of the linear controller
 *
 */
typedef struct {
    float rule1;
    float rule2;
} feedback_rule_t;

/**
 * represents a tracking error: reference_pos - current_pos
 *
 */
typedef struct {
    float x_error;
    float y_error;
    float theta_error;
} tracking_error_t;

/**
 * velocity of reference in polar robot coordinates
 *
 */
typedef struct {
    float tangential_velocity;
    float angular_velocity;
} reference_velocity_t;

/**
 * compute the linear controller output
 *
 * @param current_error error between where you want to be and where you are 
 *                      at this timestep
 * @param reference_velocity velocity you want to be at currently
 * @param output pointer to memory to store result
 *
 */
void tracy_linear_controller(const tracking_error_t * current_error,
                                const reference_velocity_t * reference_velocity,
                                feedback_rule_t * output);

/**
 * manually set parameters used by linear controller
 *
 * @param param_fancy_greek_c no restrictions
 * @param param_g has to be > 0
 *
 * @return 0 on success, or something else on failure
 */
uint8_t tracy_set_controller_params(float param_damping_coeff, float param_g);

#endif
