#include <bsd/stdlib.h>

/*!
 * Return a random value between lower_bound and upper_bound.
 * Bounds are inclusive.
 *
 * @param [in] lower_bound The lower bound
 * @param [in] upper_bound The upper bound
 *
 */

int randrange(int lower_bound, int upper_bound)
{
    return arc4random_uniform(upper_bound - lower_bound + 1) + lower_bound;
}
