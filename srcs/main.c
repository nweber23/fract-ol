/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:48:32 by nweber            #+#    #+#             */
/*   Updated: 2025/07/22 15:09:55 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void ft_randomize(void* param)
{
	(void)param;
	uint32_t x, y;
	int cx = 400;
	int cy = 400;
	int radius = 100;
	int thickness = 1;

	for (y = 0; y < image->height; ++y)
	{
		for (x = 0; x < image->width; ++x)
		{
			mlx_put_pixel(image, x, y, 0xFFFFFFFF);
		}
	}
	for (y = 0; y < image->height; ++y)
	{
		for (x = 0; x < image->width; ++x)
		{
			int dx = (int)x - cx;
			int dy = (int)y - cy;
			int dist2 = dx * dx + dy * dy;
			int r2 = radius * radius;
			if (dist2 >= r2 - 2 * radius * thickness && dist2 <= r2 + 2 * radius * thickness)
				mlx_put_pixel(image, x, y, 0xFFFF0000);
		}
	}
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

int32_t main(void)
{
	mlx_t* mlx;
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 800, 800)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
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