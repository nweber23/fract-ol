/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:48:32 by nweber            #+#    #+#             */
/*   Updated: 2025/07/22 10:56:30 by nweber           ###   ########.fr       */
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
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int main(void)
{
	t_vars vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 800, 600, "Hello MLX");
	mlx_pixel_put(vars.mlx, vars.win, 400, 300, 0x00FF00);
	mlx_hook(vars.win, 17, 0, handle_close, NULL);
	mlx_key_hook(vars.win, handle_key, &vars);
	mlx_loop(vars.mlx);
	return 0;
}
