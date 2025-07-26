/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 23:02:37 by nweber            #+#    #+#             */
/*   Updated: 2025/07/26 08:28:22 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_usage(void)
{
	ft_printf("Usage: ./fractol [fractal_type] [options]\n\n");
	ft_printf("Fractal types:\n");
	ft_printf("  mandelbrot    - Classic Mandelbrot set\n");
	ft_printf("  julia [cr ci] - Julia set with parameters cr and ci\n");
	ft_printf("  phoenix       - Phoenix fractal\n\n");
	ft_printf("Options:\n");
	ft_printf("  -c [mode]     - Color mode (0=smooth, 1=psychedelic)\n\n");
	ft_printf("Controls:\n");
	ft_printf("  Arrow keys    - Move around\n");
	ft_printf("  W/S keys      - Zoom in/out\n");
	ft_printf("  Mouse scroll  - Zoom at cursor\n");
	ft_printf("  1/2/3/4 keys  - Switch color modes\n");
	ft_printf("  SPACE         - Toggle auto color shift\n");
	ft_printf("  R             - Reset view\n");
	ft_printf("  ESC           - Exit\n\n");
	ft_printf("Examples:\n");
	ft_printf("  ./fractol mandelbrot\n");
	ft_printf("  ./fractol julia -0.7 0.27015\n");
	ft_printf("  ./fractol phoenix -c 1\n");
}

static int	parse_julia_args(int argc, char **argv, t_data *data)
{
	if (argc < 4)
		return (0);
	data->julia_cr = ft_atof(argv[2]);
	data->julia_ci = ft_atof(argv[3]);
	return (1);
}

static int	parse_color_option(int argc, char **argv, t_data *data)
{
	int	i;

	i = 2;
	while (i < argc - 1)
	{
		if (ft_strcmp(argv[i], "-c") == 0)
		{
			data->color_mode = ft_atoi(argv[i + 1]);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	set_default_values(t_data *data)
{
	data->julia_cr = -0.7;
	data->julia_ci = 0.27015;
	data->color_mode = 0;
	data->color_shift = 0.0;
	data->auto_shift = false;
}

int	parse_args(int argc, char **argv, t_data *data)
{
	if (argc < 2)
		return (0);
	set_default_values(data);
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
		data->fractal_type = MANDELBROT;
	else if (ft_strcmp(argv[1], "julia") == 0)
	{
		data->fractal_type = JULIA;
		if (!parse_julia_args(argc, argv, data))
			return (0);
	}
	else if (ft_strcmp(argv[1], "phoenix") == 0)
		data->fractal_type = PHOENIX;
	else
		return (0);
	parse_color_option(argc, argv, data);
	return (1);
}
