/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phoenix.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:32:23 by nweber            #+#    #+#             */
/*   Updated: 2025/07/25 13:24:46 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	phoenix_calc_z_squared(double *zr_temp, double *zi_temp,
	double zr, double zi)
{
	*zr_temp = zr * zr - zi * zi;
	*zi_temp = 2 * zr * zi;
}

static void	phoenix_add_feedback(double *zr_temp, double *zi_temp,
	double zr_prev, double zi_prev)
{
	*zr_temp += (-0.5) * zr_prev;
	*zi_temp += (-0.5) * zi_prev;
}

static void	phoenix_update_z(double *zr, double *zi,
	double *zr_prev, double *zi_prev)
{
	double	zr_temp;
	double	zi_temp;

	phoenix_calc_z_squared(&zr_temp, &zi_temp, *zr, *zi);
	phoenix_add_feedback(&zr_temp, &zi_temp, *zr_prev, *zi_prev);
	*zr_prev = *zr;
	*zi_prev = *zi;
	*zr = zr_temp + 0.5667;
	*zi = zi_temp;
}

static int	phoenix_check_escape(double zr, double zi, int iter)
{
	double	magnitude;

	magnitude = zr * zr + zi * zi;
	if (magnitude > 4.0)
		return (1);
	if (iter > 16 && magnitude < 0.001)
		return (2);
	return (0);
}

int	phoenix(double cr, double ci)
{
	double	zr;
	double	zi;
	double	zr_prev;
	double	zi_prev;
	int		iter;

	zr = cr;
	zi = ci;
	zr_prev = 0.0;
	zi_prev = 0.0;
	iter = 0;
	while (iter < MAX_ITER)
	{
		if (phoenix_check_escape(zr, zi, iter) == 1)
			break ;
		if (phoenix_check_escape(zr, zi, iter) == 2)
			return (MAX_ITER);
		phoenix_update_z(&zr, &zi, &zr_prev, &zi_prev);
		iter++;
	}
	return (iter);
}
