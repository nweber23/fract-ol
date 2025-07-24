/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:48:01 by nweber            #+#    #+#             */
/*   Updated: 2025/07/24 10:52:42 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>

# define WIDTH 200
# define HEIGHT 200
# define MAX_ITER 1000

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	double		x_min;
	double		x_max;
	double		y_min;
	double		y_max;
	double		zoom;
	bool		needs_redraw;
}	t_data;

int		mandelbrot(double cr, double ci);
void	render(t_data *data);
void	ft_hook(void *param);
void	handle_movement(t_data *data, mlx_t *mlx);
void	handle_zoom(t_data *data, mlx_t *mlx, double zoom_factor);
int		main(void);

#endif
