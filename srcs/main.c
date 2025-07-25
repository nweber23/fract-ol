/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:48:32 by nweber            #+#    #+#             */
/*   Updated: 2025/07/25 08:29:35 by nweber           ###   ########.fr       */
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

void	put_pixel_fast(mlx_image_t *image, int x, int y, uint32_t color)
{
	uint8_t	*pixel;

	pixel = &image->pixels[(y * image->width + x) * sizeof(uint32_t)];
	*(uint32_t *)pixel = color;
}

uint32_t	get_color(int iter)
{
	double	t;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	t = (double)iter / MAX_ITER;
	r = (uint8_t)(9 * (1 - t) * t * t * t * 255);
	g = (uint8_t)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (uint8_t)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return (0xFF000000 | (r << 16) | (g << 8) | b);
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
		iter = mandelbrot(cr, ci);
		put_pixel_fast(data->image, x, y, get_color(iter));
	}
	else
		put_pixel_fast(data->image, x, y, 0xFF000000);
}

void	render(t_data *data)
{
	int	x;
	int	y;

	if (!data->needs_redraw)
		return;
	data->needs_redraw = false;
	if (!check_render_safety(data))
	{
		reset_view(data);
		return;
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

void	handle_movement(t_data *data, mlx_t *mlx)
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

void	handle_zoom(t_data *data, mlx_t *mlx, double zoom_factor)
{
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		zoom_in_keyboard(data, zoom_factor);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		zoom_out_keyboard(data, zoom_factor);
}

void	zoom_in_mouse(t_data *data, double mouse_cr, double mouse_ci, double zoom_factor)
{
	double	new_x_min;
	double	new_x_max;
	double	new_y_min;
	double	new_y_max;

	new_x_min = mouse_cr - (mouse_cr - data->x_min) * zoom_factor;
	new_x_max = mouse_cr + (data->x_max - mouse_cr) * zoom_factor;
	new_y_min = mouse_ci - (mouse_ci - data->y_min) * zoom_factor;
	new_y_max = mouse_ci + (data->y_max - mouse_ci) * zoom_factor;
	if (isfinite(new_x_min) && isfinite(new_x_max))
	{
		if (isfinite(new_y_min) && isfinite(new_y_max))
		{
			data->x_min = new_x_min;
			data->x_max = new_x_max;
			data->y_min = new_y_min;
			data->y_max = new_y_max;
			data->needs_redraw = true;
		}
	}
}

void	zoom_out_mouse(t_data *data, double mouse_cr, double mouse_ci, double zoom_factor)
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
	mouse_cr = data->x_min + (mouse_x / (double)WIDTH) * (data->x_max - data->x_min);
	mouse_ci = data->y_min + (mouse_y / (double)HEIGHT) * (data->y_max - data->y_min);
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
	data->x_min = -2.5;
	data->x_max = 1.0;
	data->y_min = -1.0;
	data->y_max = 1.0;
	data->needs_redraw = true;
}

void	ft_hook(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_R))
		reset_view(data);
	handle_movement(data, data->mlx);
	handle_zoom(data, data->mlx, 0.9);
	if (data->needs_redraw)
		render(data);
}

int	init_fractal(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "Mandelbrot", false);
	if (!data->mlx)
		return (EXIT_FAILURE);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->image)
		return (mlx_terminate(data->mlx), EXIT_FAILURE);
	data->x_min = -2.5;
	data->x_max = 1.0;
	data->y_min = -1.0;
	data->y_max = 1.0;
	data->needs_redraw = true;
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) < 0)
	{
		mlx_delete_image(data->mlx, data->image);
		mlx_terminate(data->mlx);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(void)
{
	t_data	data;

	data = (t_data){0};
	if (init_fractal(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	render(&data);
	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_scroll_hook(data.mlx, mouse_hook, &data);
	mlx_loop(data.mlx);
	mlx_delete_image(data.mlx, data.image);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
