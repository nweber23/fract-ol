/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:25:09 by nweber            #+#    #+#             */
/*   Updated: 2025/07/28 17:33:18 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	check_cardioid(double cr, double ci)
{
	double	q;
	double	temp;

	q = cr - 0.25;
	q = q * q + ci * ci;
	temp = q + (cr - 0.25);
	if (q * temp < 0.25 * ci * ci)
		return (1);
	return (0);
}

static int	check_bulb(double cr, double ci)
{
	double	temp_cr;
	double	temp_ci;

	temp_cr = cr + 1.0;
	temp_ci = ci;
	if (temp_cr * temp_cr + temp_ci * temp_ci < 0.0625)
		return (1);
	return (0);
}

static int	mandelbrot_loop(double cr, double ci, int max_iter)
{
	double	zr;
	double	zi;
	double	zr2;
	double	zi2;
	int		iter;

	zr = 0.0;
	zi = 0.0;
	zr2 = 0.0;
	zi2 = 0.0;
	iter = 0;
	while (iter < max_iter && zr2 + zi2 <= 4.0)
	{
		zi = 2.0 * zr * zi + ci;
		zr = zr2 - zi2 + cr;
		zr2 = zr * zr;
		zi2 = zi * zi;
		iter++;
	}
	return (iter);
}

int	mandelbrot(double cr, double ci)
{
	if (check_cardioid(cr, ci))
		return (MAX_ITER);
	if (check_bulb(cr, ci))
		return (MAX_ITER);
	return (mandelbrot_loop(cr, ci, MAX_ITER));
}
