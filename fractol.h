/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:48:01 by nweber            #+#    #+#             */
/*   Updated: 2025/07/22 10:56:36 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "MLX/mlx.h"
# include <stdlib.h>
# include <math.h>

# define WIDTH 800
# define HEIGHT 800

typedef struct s_vars {
	void *mlx;
	void *win;
}	t_vars;

#endif
