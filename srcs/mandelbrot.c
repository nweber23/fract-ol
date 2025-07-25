/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:25:09 by nweber            #+#    #+#             */
/*   Updated: 2025/07/25 15:47:04 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	mandelbrot_check_escape(double zr, double zi, int iter)
{
	double	magnitude;

	magnitude = zr * zr + zi * zi;
	if (magnitude > 4.0)
		return (1);
	if (iter > 16 && magnitude < 0.001)
		return (2);
	return (0);
}

static void	mandelbrot_update_z(double *zr, double *zi, double *zr2, double *zi2, double cr, double ci)
{
	*zi = 2 * (*zr) * (*zi) + ci;
	*zr = (*zr2) - (*zi2) + cr;
	*zr2 = (*zr) * (*zr);
	*zi2 = (*zi) * (*zi);
}

int	mandelbrot(double cr, double ci)
{
	double	zr;
	double	zi;
	double	zr2;
	double	zi2;
	int		iter;
	int		escape_check;

	zr = 0.0;
	zi = 0.0;
	zr2 = 0.0;
	zi2 = 0.0;
	iter = 0;
	while (iter < MAX_ITER)
	{
		escape_check = mandelbrot_check_escape(zr, zi, iter);
		if (escape_check == 1)
			break ;
		if (escape_check == 2)
			return (MAX_ITER);
		mandelbrot_update_z(&zr, &zi, &zr2, &zi2, cr, ci);
		iter++;
	}
	return (iter);
}
