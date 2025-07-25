/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:25:09 by nweber            #+#    #+#             */
/*   Updated: 2025/07/25 16:42:11 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot(double cr, double ci)
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
	while (zr2 + zi2 <= 4.0 && iter < MAX_ITER)
	{
		zi = 2 * zr * zi + ci;
		zr = zr2 - zi2 + cr;
		zr2 = zr * zr;
		zi2 = zi * zi;
		iter++;
		if (iter > 16 && zr2 + zi2 < 0.001)
			return (MAX_ITER);
	}
	return (iter);
}
