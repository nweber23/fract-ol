/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:48:32 by nweber            #+#    #+#             */
/*   Updated: 2025/07/21 23:00:06 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int handle_key(int keycode, void *param)
{
	if (keycode == 65307) // auf mac 53
	{
		mlx_destroy_window(param, param);
		exit(0);
	}
	return (0);
}

int main(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "Hello MLX");
	mlx_pixel_put(mlx, win, 400, 300, 0x00FF00);
	mlx_key_hook(win, handle_key, mlx);
	mlx_loop(mlx);
	return 0;
}

