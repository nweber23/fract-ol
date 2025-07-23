/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:48:32 by nweber            #+#    #+#             */
/*   Updated: 2025/07/23 21:43:12 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
Mathe Explained
	iter = 0 -> MAX ist 1000
	min_x = -2.5, max_x = 1.0
	min_y = -1.0, max_y = -1.0
	Komplexe Zahl kann mit 2 double werten dargestellt werden|
	zr = Realteil
	zr_neu = zr * zr - zi * zi + cr
	zi = Imaginärteil
	zi_neu = 2 * zr * zi + ci;
	cr = Realteil von c aka x-Koordinate
	cr = x_min + (x / (double)WIDTH) * (x_max - x_min)
	ci = Imaginärteil von c aka y-Koordinate
	ci = y_min + (y / (double)HEIGHT) * (y_max - y_min)
	c = Komplexe Zahl
	c = cr + ci * i(i wird repraesentiert durch ci)
*/

int	mandelbrot(double cr, double ci)
{
	double	zr;
	double	zi;
	double	temp;
	int		iter;

	zr = 0.0;
	zi = 0.0;
	iter = 0;
	while (zr * zr + zi * zi <= 4.0 && iter < MAX_ITER)
	{
		temp = zr * zr - zi * zi + cr;
		zi = 2 * zr * zi + ci;
		zr = temp;
		iter++;
	}
	return (iter);
}

void	put_pixel_color(t_data *data, int x, int y, int iter)
{
	double	t;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint32_t	color;

	t = (double)iter / MAX_ITER;
	r = (uint8_t)(9 * (1 - t) * t * t * t * 255);
	g = (uint8_t)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (uint8_t)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	color = 0xFF000000 | (r << 16) | (g << 8) | b;
	mlx_put_pixel(data->image, x, y, color);
}

void	render(t_data *data)
{
	int		x;
	int		y;
	double	cr;
	double	ci;
	int		iter;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			cr = data->x_min + (x * (data->x_max - data->x_min) / WIDTH);
			ci = data->y_min + (y * (data->y_max - data->y_min) / HEIGHT);
			iter = mandelbrot(cr, ci);
			put_pixel_color(data, x, y, iter);
			x++;
		}
		y++;
	}
}

void	handle_movement(t_data *data, mlx_t *mlx)
{
	double	move_step;

	move_step = 0.1 * (data->x_max - data->x_min);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		data->y_min -= move_step;
		data->y_max -= move_step;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		data->y_min += move_step;
		data->y_max += move_step;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		data->x_min -= move_step;
		data->x_max -= move_step;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		data->x_min += move_step;
		data->x_max += move_step;
	}
}

void	handle_zoom(t_data *data, mlx_t *mlx, double zoom_factor)
{
	double	x_center;
	double	y_center;

	x_center = (data->x_min + data->x_max) / 2;
	y_center = (data->y_min + data->y_max) / 2;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		data->x_min = x_center + (data->x_min - x_center) * zoom_factor;
		data->x_max = x_center + (data->x_max - x_center) * zoom_factor;
		data->y_min = y_center + (data->y_min - y_center) * zoom_factor;
		data->y_max = y_center + (data->y_max - y_center) * zoom_factor;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		data->x_min = x_center + (data->x_min - x_center) / zoom_factor;
		data->x_max = x_center + (data->x_max - x_center) / zoom_factor;
		data->y_min = y_center + (data->y_min - y_center) / zoom_factor;
		data->y_max = y_center + (data->y_max - y_center) / zoom_factor;
	}
}

void	ft_hook(void *param)
{
	t_data	*data;
	mlx_t	*mlx;

	data = (t_data *)param;
	mlx = data->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	handle_movement(data, mlx);
	handle_zoom(data, mlx, 0.9);
	render(data);
}

int	main(void)
{
	t_data	data;

	data.mlx = mlx_init(WIDTH, HEIGHT, "Mandelbrot", true);
	if (!data.mlx)
		return (EXIT_FAILURE);
	data.image = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	if (!data.image)
		return (mlx_terminate(data.mlx), EXIT_FAILURE);
	data.x_min = -2.5;
	data.x_max = 1.0;
	data.y_min = -1.0;
	data.y_max = 1.0;
	data.zoom = 1.0;
	if (mlx_image_to_window(data.mlx, data.image, 0, 0) < 0)
	{
		mlx_delete_image(data.mlx, data.image);
		mlx_terminate(data.mlx);
		return (EXIT_FAILURE);
	}
	render(&data);
	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_loop(data.mlx);
	mlx_delete_image(data.mlx, data.image);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
