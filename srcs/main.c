/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:48:32 by nweber            #+#    #+#             */
/*   Updated: 2025/07/24 10:56:46 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
Mathe Explained Mandelbrot
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

/*
Mathe Explained Julia
	iter = 0 -> MAX ist z.B. 1000
	min_x = -2.0, max_x = 2.0
	min_y = -2.0, max_y = 2.0
	Komplexe Zahlen bestehen aus 2 doubles
	zr = Realteil von z (startet als Pixelkoordinate)
	zi = Imaginärteil von z (startet als Pixelkoordinate)
	cr = Konstanter Realteil von c (z.B. -0.7)
	ci = Konstanter Imaginärteil von c (z.B. 0.27015)
	Julia nutzt dieselbe Iteration wie Mandelbrot:
		zr_neu = zr * zr - zi * zi + cr
		zi_neu = 2 * zr * zi + ci
	Der Unterschied: c (cr, ci) ist konstant, und z (zr, zi) ändert sich je Pixel
	Julia erzeugt interessante Muster abhängig vom gewählten c
*/

/*
Mathe Explained Phoenix
	iter = 0 -> MAX z.B. 1000
	Erweiterung der Mandelbrot-Menge mit Rückkopplung
	Verwendet aktuellen z-Wert und vorherigen z-Wert
	Formel:
		z_next = z*z + p * z_prev + c
	zr = Realteil von z
	zi = Imaginärteil von z
	z_prev_r = Realteil von z_{n-1}
	z_prev_i = Imaginärteil von z_{n-1}
	pr = Realteil von p (Parameter, z.B. -0.5)
	pi = Imaginärteil von p (z.B. 0.5)
	cr = Realteil von c aka x-Koordinate
	cr = x_min + (x / (double)WIDTH) * (x_max - x_min)
	ci = Imaginärteil von c aka y-Koordinate
	ci = y_min + (y / (double)HEIGHT) * (y_max - y_min)
	c = cr + ci * i
	Jeder neue Wert hängt vom vorherigen ab, was komplexe Strukturen erzeugt
	Mehr Kontrolle durch p – kleine Änderungen = große visuelle Unterschiede
*/

int	mandelbrot(double cr, double ci)
{
	double zr = 0.0;
	double zi = 0.0;
	double zr2 = 0.0;
	double zi2 = 0.0;
	int iter = 0;

	while (zr2 + zi2 <= 4.0 && iter < MAX_ITER)
	{
		zi = 2 * zr * zi + ci;
		zr = zr2 - zi2 + cr;
		zr2 = zr * zr;
		zi2 = zi * zi;
		iter++;

		if (iter > 16 && zr2 + zi2 < 0.001)
			return MAX_ITER;
	}
	return iter;
}

void	put_pixel_fast(mlx_image_t *image, int x, int y, uint32_t color)
{
	uint8_t *pixel = &image->pixels[(y * image->width + x) * sizeof(uint32_t)];
	*(uint32_t *)pixel = color;
}

uint32_t	get_color(int iter)
{
	double t = (double)iter / MAX_ITER;
	uint8_t r = (uint8_t)(9 * (1 - t) * t * t * t * 255);
	uint8_t g = (uint8_t)(15 * (1 - t) * (1 - t) * t * t * 255);
	uint8_t b = (uint8_t)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return 0xFF000000 | (r << 16) | (g << 8) | b;
}

void	render(t_data *data)
{
	if (!data->needs_redraw)
		return;
	data->needs_redraw = false;
	double x_scale = (data->x_max - data->x_min) / WIDTH;
	double y_scale = (data->y_max - data->y_min) / HEIGHT;
	for (int y = 0; y < HEIGHT; y++)
	{
		double ci = data->y_min + y * y_scale;
		for (int x = 0; x < WIDTH; x++)
		{
			double cr = data->x_min + x * x_scale;
			int iter = mandelbrot(cr, ci);
			put_pixel_fast(data->image, x, y, get_color(iter));
		}
	}
}

void	handle_movement(t_data *data, mlx_t *mlx)
{
	double move_step = 0.1 * (data->x_max - data->x_min);

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

void	handle_zoom(t_data *data, mlx_t *mlx, double zoom_factor)
{
	double x_center = (data->x_min + data->x_max) / 2;
	double y_center = (data->y_min + data->y_max) / 2;

	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		data->x_min = x_center + (data->x_min - x_center) * zoom_factor;
		data->x_max = x_center + (data->x_max - x_center) * zoom_factor;
		data->y_min = y_center + (data->y_min - y_center) * zoom_factor;
		data->y_max = y_center + (data->y_max - y_center) * zoom_factor;
		data->needs_redraw = true;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		data->x_min = x_center + (data->x_min - x_center) / zoom_factor;
		data->x_max = x_center + (data->x_max - x_center) / zoom_factor;
		data->y_min = y_center + (data->y_min - y_center) / zoom_factor;
		data->y_max = y_center + (data->y_max - y_center) / zoom_factor;
		data->needs_redraw = true;
	}
}

void	ft_hook(void *param)
{
	t_data *data = param;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);

	handle_movement(data, data->mlx);
	handle_zoom(data, data->mlx, 0.9);

	if (data->needs_redraw)
		render(data);
}

int	main(void)
{
	t_data data = {0};

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
	data.needs_redraw = true;
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
