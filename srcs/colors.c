/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:00:00 by nweber            #+#    #+#             */
/*   Updated: 2025/07/26 10:32:55 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static uint32_t	smooth(int iter, double shift)
{
	double	t;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	if (iter == MAX_ITER)
		return (0xFF000000);
	t = fmod(((double)iter / MAX_ITER) + shift, 1.0);
	if (t < 0)
		t += 1.0;
	r = (uint8_t)(9 * (1 - t) * t * t * t * 255);
	g = (uint8_t)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (uint8_t)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return (0xFF000000 | (r << 16) | (g << 8) | b);
}

static uint32_t	psychedelic(int iter, double shift)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	double	phase;

	if (iter == MAX_ITER)
		return (0xFF000000);
	phase = (iter * 0.3) + shift * 6.28;
	r = (uint8_t)(sin(phase) * 127 + 128);
	g = (uint8_t)(sin(phase + 2.094) * 127 + 128);
	b = (uint8_t)(sin(phase + 4.188) * 127 + 128);
	return (0xFF000000 | (r << 16) | (g << 8) | b);
}

static uint32_t	fire(int iter, double shift)
{
	double	t;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	if (iter == MAX_ITER)
		return (0xFF000000);
	t = fmod(((double)iter / MAX_ITER * 3.0) + shift, 1.0);
	if (t < 0)
		t += 1.0;
	r = 255;
	g = 255;
	b = (uint8_t)(255 * ((t - 0.66) * 3));
	if (t < 0.33)
	{
		r = (uint8_t)(255 * (t * 3));
		g = 0;
		b = 0;
	}
	else if (t < 0.66)
		g = (uint8_t)(255 * ((t - 0.33) * 3));
	if (t < 0.66)
		b = 0;
	return (0xFF000000 | (r << 16) | (g << 8) | b);
}

static uint32_t	ocean(int iter, double shift)
{
	double	t;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	if (iter == MAX_ITER)
		return (0xFF000000);
	t = fmod(((double)iter / MAX_ITER * 2.0) + shift, 1.0);
	if (t < 0)
		t += 1.0;
	if (t < 0.5)
	{
		r = 0;
		g = (uint8_t)(128 * (t * 2));
		b = (uint8_t)(255 * (t * 2));
	}
	else
	{
		r = (uint8_t)(128 * ((t - 0.5) * 2));
		g = (uint8_t)(128 + 127 * ((t - 0.5) * 2));
		b = 255;
	}
	return (0xFF000000 | (r << 16) | (g << 8) | b);
}

uint32_t	get_color(int iter, int color_mode, double shift)
{
	if (color_mode == 1)
		return (psychedelic(iter, shift));
	else if (color_mode == 2)
		return (fire(iter, shift));
	else if (color_mode == 3)
		return (ocean(iter, shift));
	else
		return (smooth(iter, shift));
}
