/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:05:30 by nweber            #+#    #+#             */
/*   Updated: 2025/07/28 20:19:51 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia(double zr, double zi, double cr, double ci)
{
	double	zr2;
	double	zi2;
	double	temp;
	int		iter;

	zr2 = zr * zr;
	zi2 = zi * zi;
	iter = 0;
	while (zr2 + zi2 <= 4.0 && iter < MAX_ITER)
	{
		temp = zr2 - zi2 + cr;
		zi = 2 * zr * zi + ci;
		zr = temp;
		zr2 = zr * zr;
		zi2 = zi * zi;
		iter++;
	}
	return (iter);
}

void	julia_check(t_data *data)
{
	if (data->fractal_type == JULIA)
	{
		data->x_min = -2.0;
		data->x_max = 2.0;
		data->y_min = -2.0;
		data->y_max = 2.0;
	}
	else
	{
		data->x_min = -2.5;
		data->x_max = 1.0;
		data->y_min = -1.0;
		data->y_max = 1.0;
	}
}