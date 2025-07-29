/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:22:12 by nweber            #+#    #+#             */
/*   Updated: 2025/07/29 20:43:45 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	handle_zoom(t_data *data, mlx_t *mlx, double zoom_factor)
{
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		zoom_in_keyboard(data, zoom_factor);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		zoom_out_keyboard(data, zoom_factor);
}

void	zoom_in_mouse(t_data *data, double mouse_cr,
						double mouse_ci, double zoom_factor)
{
	double	new_x_min;
	double	new_x_max;
	double	new_y_min;
	double	new_y_max;
	double	new_x_range;

	new_x_range = (data->x_max - data->x_min) * zoom_factor;
	new_x_min = mouse_cr - (mouse_cr - data->x_min) * zoom_factor;
	new_x_max = mouse_cr + (data->x_max - mouse_cr) * zoom_factor;
	new_y_min = mouse_ci - (mouse_ci - data->y_min) * zoom_factor;
	new_y_max = mouse_ci + (data->y_max - mouse_ci) * zoom_factor;
	if (isfinite(new_x_min) && isfinite(new_x_max))
	{
		if (isfinite(new_y_min) && isfinite(new_y_max) && new_x_range > 1e-14)
		{
			data->x_min = new_x_min;
			data->x_max = new_x_max;
			data->y_min = new_y_min;
			data->y_max = new_y_max;
			data->needs_redraw = true;
		}
	}
}

void	zoom_out_mouse(t_data *data, double mouse_cr,
						double mouse_ci, double zoom_factor)
{
	double	x_range;
	double	y_range;
	double	new_x_range;
	double	new_y_range;

	x_range = data->x_max - data->x_min;
	y_range = data->y_max - data->y_min;
	new_x_range = x_range / zoom_factor;
	new_y_range = y_range / zoom_factor;
	if (new_x_range < 10.0 && new_y_range < 10.0)
	{
		data->x_min = mouse_cr - (mouse_cr - data->x_min) / zoom_factor;
		data->x_max = mouse_cr + (data->x_max - mouse_cr) / zoom_factor;
		data->y_min = mouse_ci - (mouse_ci - data->y_min) / zoom_factor;
		data->y_max = mouse_ci + (data->y_max - mouse_ci) / zoom_factor;
		data->needs_redraw = true;
	}
}

void	mouse_hook(double xdelta, double ydelta, void *param)
{
	t_data	*data;
	int32_t	mouse_x;
	int32_t	mouse_y;
	double	mouse_cr;
	double	mouse_ci;

	(void)xdelta;
	data = param;
	mlx_get_mouse_pos(data->mlx, &mouse_x, &mouse_y);
	mouse_cr = data->x_min + (mouse_x / (double)data->width)
		* (data->x_max - data->x_min);
	mouse_ci = data->y_min + (mouse_y / (double)data->height)
		* (data->y_max - data->y_min);
	if (ydelta > 0)
	{
		if ((data->x_max - data->x_min) * 0.9 > 1e-15)
			zoom_in_mouse(data, mouse_cr, mouse_ci, 0.9);
	}
	else if (ydelta < 0)
		zoom_out_mouse(data, mouse_cr, mouse_ci, 0.9);
}

void	reset_view(t_data *data)
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
	data->needs_redraw = true;
}
