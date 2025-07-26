/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:25:43 by nweber            #+#    #+#             */
/*   Updated: 2025/07/26 08:27:50 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_pixel_fast(mlx_image_t *image, int x, int y, uint32_t color)
{
	uint8_t	*pixel;

	pixel = &image->pixels[(y * image->width + x) * sizeof(uint32_t)];
	*(uint32_t *)pixel = color;
}

int	check_render_safety(t_data *data)
{
	double	x_range;
	double	y_range;

	x_range = data->x_max - data->x_min;
	y_range = data->y_max - data->y_min;
	if (!isfinite(x_range) || !isfinite(y_range))
		return (0);
	if (x_range <= 0 || y_range <= 0)
		return (0);
	if (!isfinite(data->x_min) || !isfinite(data->x_max))
		return (0);
	if (!isfinite(data->y_min) || !isfinite(data->y_max))
		return (0);
	return (1);
}

static int	calculate_fractal(t_data *data, double cr, double ci)
{
	if (data->fractal_type == MANDELBROT)
		return (mandelbrot(cr, ci));
	else if (data->fractal_type == JULIA)
		return (julia(cr, ci, data->julia_cr, data->julia_ci));
	else if (data->fractal_type == PHOENIX)
		return (phoenix(cr, ci));
	return (0);
}

void	render_pixel(t_data *data, int x, int y)
{
	double	x_range;
	double	y_range;
	double	cr;
	double	ci;
	int		iter;

	x_range = data->x_max - data->x_min;
	y_range = data->y_max - data->y_min;
	cr = data->x_min + x * (x_range / WIDTH);
	ci = data->y_min + y * (y_range / HEIGHT);
	if (isfinite(cr) && isfinite(ci))
	{
		iter = calculate_fractal(data, cr, ci);
		put_pixel_fast(data->image, x, y,
			get_color(iter, data->color_mode, data->color_shift));
	}
	else
		put_pixel_fast(data->image, x, y, 0xFF000000);
}

void	render(t_data *data)
{
	int	x;
	int	y;

	if (!data->needs_redraw)
		return ;
	data->needs_redraw = false;
	if (!check_render_safety(data))
	{
		reset_view(data);
		return ;
	}
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			render_pixel(data, x, y);
			x++;
		}
		y++;
	}
}
