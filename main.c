/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:48:32 by nweber            #+#    #+#             */
/*   Updated: 2025/07/22 13:23:18 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	handle_close(void *param)
{
	(void)param;
	exit (0);
}

int	handle_key(int keycode, void *param)
{
	t_vars *vars = (t_vars *)param;
	printf("Keycode: %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	handle_mouse(int button, int x, int y, t_vars *vars, void *param)
{
	vars = (t_vars *)param;
	printf("Mouse Button: %d at x=%d and y=%d\n", button, x, y);
	return (0);
}

void	draw_circle(t_vars *vars)
{
	int x;
	int y;
	int radius = 100;
	int center_x = WIDTH / 2;
	int center_y = HEIGHT / 2;
	int color = 0x00FF00;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if ((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y) <= radius * radius)
				mlx_pixel_put(vars->mlx, vars->win, x, y, color);
			x++;
		}
		y++;
	}
}

int	main(void)
{
	t_vars vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 800, 600, "fractol");
	draw_circle(&vars);
	mlx_hook(vars.win, 17, 0, handle_close, NULL);
	mlx_mouse_hook(vars.win, handle_mouse, &vars);
	mlx_key_hook(vars.win, handle_key, &vars);
	mlx_loop(vars.mlx);
	return 0;
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