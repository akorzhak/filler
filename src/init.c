/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 05:59:29 by akorzhak          #+#    #+#             */
/*   Updated: 2018/06/25 05:59:31 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		define_fractal(char *name, t_ptr *p)
{
	if (ft_strcmp(name, "mandelbrot") == 0)
		p->fract_name = MANDELBROT;
	else if (ft_strcmp(name, "julia") == 0)
		p->fract_name = JULIA;
	else if (ft_strcmp(name, "burningship") == 0)
		p->fract_name = BURNINGSHIP;
	else if (ft_strcmp(name, "buffalo") == 0)
		p->fract_name = BUFFALO;
	else if (ft_strcmp(name, "drop") == 0)
		p->fract_name = DROP;
	else if (ft_strcmp(name, "tricorn") == 0)
		p->fract_name = TRICORN;
	else
		return (0);
	return (1);
}

void	init_color(t_ptr *p)
{
	p->col.r_freq = 0.002;
	p->col.g_freq = 0.00006;
	p->col.b_freq = 0.00006;
	p->col.r_phase = 0.0008;
	p->col.g_phase = 0.00009;
	p->col.b_phase = 0.00004;
	p->col.center = 530;
	p->col.delta = 4;
	p->col.variant = 0;
}

void	init_ptr(t_ptr *p)
{
	p->mlx = mlx_init();
	p->iter_max = 100;
	p->zoom = 1;
	p->mx = 0.0;
	p->my = 0.0;
	p->infinit_border = 4.0;
	init_color(p);
}

void	init_fractal(t_ptr *p)
{
	if (p->fract_name == MANDELBROT || p->fract_name == BUFFALO)
	{
		p->max_real = 1.1;
		p->min_imag = -1.2;
	}
	else if (p->fract_name == BURNINGSHIP)
	{
		p->max_real = 1.0;
		p->min_imag = -1.6;
	}
	else if (p->fract_name == JULIA)
	{
		p->max_real = 2.2;
		p->min_imag = -1.6;
	}
	else
	{
		p->max_real = 1.8;
		p->min_imag = -1.6;
	}
	p->min_real = -2.1;
	p->max_imag = p->min_imag + (p->max_real - p->min_real) * SIZE_Y / SIZE_X;
	p->j_real = -0.4;
	p->j_imag = 0.6;
}

void	init_factors(int x, int y, t_ptr *p)
{
	p->iter = 0;
	p->c_imag = p->max_imag - y
				* (p->max_imag - p->min_imag) / (SIZE_Y - 1) + p->my;
	p->c_real = p->min_real + x
				* (p->max_real - p->min_real) / (SIZE_X - 1) + p->mx;
	p->z_real = p->c_real;
	p->z_imag = p->c_imag;
}
