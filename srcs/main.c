/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:48:32 by nweber            #+#    #+#             */
/*   Updated: 2025/07/25 13:27:11 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#include "fractol.h"

void	ft_hook(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_R))
		reset_view(data);
	handle_movement_vertical(data, data->mlx);
	handle_movement_horizontal(data, data->mlx);
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
