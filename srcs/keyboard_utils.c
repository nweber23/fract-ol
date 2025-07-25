/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:23:17 by nweber            #+#    #+#             */
/*   Updated: 2025/07/25 13:23:51 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	handle_movement_vertical(t_data *data, mlx_t *mlx)
{
	double	move_step;

	move_step = 0.05 * (data->x_max - data->x_min);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		data->y_min -= move_step;
		data->y_max -= move_step;
		data->needs_redraw = true;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		data->y_min += move_step;
		data->y_max += move_step;
		data->needs_redraw = true;
	}
}

void	handle_movement_horizontal(t_data *data, mlx_t *mlx)
{
	double	move_step;

	move_step = 0.05 * (data->x_max - data->x_min);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		data->x_min -= move_step;
		data->x_max -= move_step;
		data->needs_redraw = true;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		data->x_min += move_step;
		data->x_max += move_step;
		data->needs_redraw = true;
	}
}

void	zoom_in_keyboard(t_data *data, double zoom_factor)
{
	double	x_center;
	double	y_center;
	double	new_x_range;
	double	new_y_range;

	x_center = (data->x_min + data->x_max) / 2;
	y_center = (data->y_min + data->y_max) / 2;
	new_x_range = (data->x_max - data->x_min) * zoom_factor;
	new_y_range = (data->y_max - data->y_min) * zoom_factor;
	if (new_x_range > 1e-15 && new_y_range > 1e-15)
	{
		if (isfinite(new_x_range) && isfinite(new_y_range))
		{
			data->x_min = x_center - new_x_range / 2;
			data->x_max = x_center + new_x_range / 2;
			data->y_min = y_center - new_y_range / 2;
			data->y_max = y_center + new_y_range / 2;
			data->needs_redraw = true;
		}
	}
}

void	zoom_out_keyboard(t_data *data, double zoom_factor)
{
	double	x_center;
	double	y_center;
	double	new_x_range;
	double	new_y_range;

	x_center = (data->x_min + data->x_max) / 2;
	y_center = (data->y_min + data->y_max) / 2;
	new_x_range = (data->x_max - data->x_min) / zoom_factor;
	new_y_range = (data->y_max - data->y_min) / zoom_factor;
	if (new_x_range < 10.0 && new_y_range < 10.0)
	{
		data->x_min = x_center - new_x_range / 2;
		data->x_max = x_center + new_x_range / 2;
		data->y_min = y_center - new_y_range / 2;
		data->y_max = y_center + new_y_range / 2;
		data->needs_redraw = true;
	}
}

void	reset_view(t_data *data)
{
	data->x_min = -2.5;
	data->x_max = 1.0;
	data->y_min = -1.0;
	data->y_max = 1.0;
	data->needs_redraw = true;
}
