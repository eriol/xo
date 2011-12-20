/*
 * Copyright 2011 Daniele Tricoli <eriol@mornie.org>
 *
 * This file is part of xo.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library. If not, see http://www.gnu.org/licenses/.
 */

#include <stdlib.h>
#include <time.h>

/*!
 * Return a random value between lower_bound and upper_bound.
 * Bounds are inclusive.
 *
 * Remenber to initialize seed.
 *
 * @param [in] lower_bound The lower bound
 * @param [in] upper_bound The upper bound
 *
 */

int randrange(int lower_bound, int upper_bound)
{
    return (random() % (upper_bound - lower_bound + 1)) + lower_bound;
}
