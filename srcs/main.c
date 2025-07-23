/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:48:32 by nweber            #+#    #+#             */
/*   Updated: 2025/07/23 16:27:06 by nweber           ###   ########.fr       */
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
	double zr = 0.0, zi = 0.0, temp;
	int iter = 0;
	while (zr * zr + zi * zi <= 4.0 && iter < MAX_ITER)
	{
		temp = zr * zr - zi * zi + cr;
		zi = 2 * zr * zi + ci;
		zr = temp;
		iter++;
	}
	return (iter);
}

void	render(void *param)
{
	t_data *data = (t_data *)param;
	double x_min = -2.5, x_max = 1.0;
	double y_min = -1.0, y_max = 1.0;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			double cr = x_min + (x * (x_max - x_min) / WIDTH);
			double ci = y_min + (y * (y_max - y_min) / HEIGHT);
			int iter = mandelbrot(cr, ci);
			double t = (double)iter / MAX_ITER;
			uint8_t r = (uint8_t)(9 * (1 - t) * t * t * t * 255);
			uint8_t g = (uint8_t)(15 * (1 - t) * (1 - t) * t * t * 255);
			uint8_t b = (uint8_t)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
			uint32_t color = 0xFF000000 | (r << 16) | (g << 8) | b;
			mlx_put_pixel(data->image, x, y, color);
		}
	}
}

void	ft_hook(void* param)
{
	t_data *data = (t_data *)param;
	mlx_t* mlx = data->mlx;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP) || mlx_is_key_down(mlx, MLX_KEY_S))
		data->image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN) || mlx_is_key_down(mlx, MLX_KEY_W))
		data->image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) || mlx_is_key_down(mlx, MLX_KEY_A))
		data->image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT) || mlx_is_key_down(mlx, MLX_KEY_D))
		data->image->instances[0].x += 5;
}

int	main(void)
{
	t_data data;

	data.mlx = mlx_init(WIDTH, HEIGHT, "Mandelbrot", true);
	if (!data.mlx)
		return (EXIT_FAILURE);
	data.image = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	if (!data.image)
	{
		mlx_terminate(data.mlx);
		return (EXIT_FAILURE);
	}
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

/*
ARROW_KEYS 123-126
- LEFT	123
- RIGHT	124
- DOWN	125
- UP	126
MOUSE_WHEEl_UP 4
MOUSE_WHEEL_DOWN 5
SPACEBAR 49
C 8
*/