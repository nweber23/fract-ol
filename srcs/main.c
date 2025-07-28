/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:48:32 by nweber            #+#    #+#             */
/*   Updated: 2025/07/28 20:20:51 by nweber           ###   ########.fr       */
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
	if (data->needs_resize)
		resize_image(data);
	if (data->needs_redraw)
		render(data);
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_data	*data;

	data = param;
	if (width > 0 && height > 0)
	{
		data->width = width;
		data->height = height;
		data->needs_resize = true;
	}
}

int	init_fractal(t_data *data)
{
	data->width = INITIAL_WIDTH;
	data->height = INITIAL_HEIGHT;
	data->mlx = mlx_init(data->width, data->height, "Fractol", true);
	if (!data->mlx)
		return (EXIT_FAILURE);
	data->image = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->image)
		return (mlx_terminate(data->mlx), EXIT_FAILURE);
	julia_check(data);
	data->needs_redraw = true;
	data->needs_resize = false;
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) < 0)
		return (mlx_terminate(data->mlx),
			mlx_delete_image(data->mlx, data->image), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	resize_image(t_data *data)
{
	mlx_image_t	*new_image;

	data->needs_resize = false;
	if (data->width <= 0 || data->height <= 0)
		return ;
	new_image = mlx_new_image(data->mlx, data->width, data->height);
	if (!new_image)
		return ;
	mlx_delete_image(data->mlx, data->image);
	data->image = new_image;
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) < 0)
	{
		mlx_delete_image(data->mlx, data->image);
		return ;
	}
	data->needs_redraw = true;
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
	mlx_resize_hook(data.mlx, resize_hook, &data);
	mlx_loop(data.mlx);
	mlx_delete_image(data.mlx, data.image);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
