/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:48:01 by nweber            #+#    #+#             */
/*   Updated: 2025/07/25 10:21:01 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "MLX42.h"
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

int			mandelbrot(double cr, double ci);
void		render(t_data *data);
void		ft_hook(void *param);
void		mouse_hook(double xdelta, double ydelta, void *param);
void		handle_movement_verical(t_data *data, mlx_t *mlx);
void		handle_movement_horizontal(t_data *data, mlx_t *mlx);
void		handle_zoom(t_data *data, mlx_t *mlx, double zoom_factor);
void		zoom_in_keyboard(t_data *data, double zoom_factor);
void		zoom_out_keyboard(t_data *data, double zoom_factor);
void		zoom_in_mouse(t_data *data, double mouse_cr, double mouse_ci, double zoom_factor);
void		zoom_out_mouse(t_data *data, double mouse_cr, double mouse_ci, double zoom_factor);
void		render_pixel(t_data *data, int x, int y);
int			check_render_safety(t_data *data);
void		reset_view(t_data *data);
int			init_fractal(t_data *data);
void		put_pixel_fast(mlx_image_t *image, int x, int y, uint32_t color);
uint32_t	get_color(int iter);
int			main(void);

#endif
