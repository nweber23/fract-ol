/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:48:32 by nweber            #+#    #+#             */
/*   Updated: 2025/07/26 09:18:28 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	handle_color_keys(data, data->mlx);
	if (data->auto_shift)
	{
		data->color_shift += 0.01;
		if (data->color_shift > 1.0)
			data->color_shift = 0.0;
		data->needs_redraw = true;
	}
	if (data->needs_redraw)
		render(data);
}

int	init_fractal(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "Fractol", false);
	if (!data->mlx)
		return (EXIT_FAILURE);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->image)
		return (mlx_terminate(data->mlx), EXIT_FAILURE);
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
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) < 0)
		return (mlx_terminate(data->mlx),
			mlx_delete_image(data->mlx, data->image), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data = (t_data){0};
	if (!parse_args(argc, argv, &data))
	{
		print_usage();
		return (EXIT_FAILURE);
	}
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
