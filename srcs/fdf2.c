/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 10:49:23 by mfiguera          #+#    #+#             */
/*   Updated: 2018/03/05 19:15:09 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		keyispressed(int key, t_fdf *m)
{
	if (key == 53)
		exit(0);
	if (key == 18)
		m->a1 += 0.314159265358979;
	if (key == 19)
		m->a2 += 0.314159265358979;
	if (key == 20)
		m->a3 += 0.314159265358979;
	if (key == 2 || key == 6)
		m->depth *= 1.2;
	if ((key == 8 || key == 7) && m->depth > 0.01)
		m->depth /= 1.2;
	if (key == 6)
		m->scl *= 1.2;
	if (key == 7 && m->scl > 1)
		m->scl /= 1.2;
	if (key == 126)
		m->offy -= 10;
	if (key == 125)
		m->offy += 10;
	if (key == 123)
		m->offx -= 10;
	return (keyispressed2(key, m));
}

void	draw_liney(t_point p0, t_point p1, int **z, int color)
{
	double	slope;
	double	err;

	err = 0.0;
	if (p0.y > p1.y)
		swap_points(&p0, &p1);
	slope = (p1.x - p0.x) / (p1.y - p0.y);
	while (p0.y <= p1.y && p0.y <= WINH)
	{
		if (p0.x < WINW && p0.y < WINH && p0.x >= 0 && p0.x >= 0 && (int)p0.y *
				WINW + (int)p0.x < WINW * WINH && (int)p0.y * WINW +
				(int)p0.x > 0)
			z[0][((int)p0.y * WINW + (int)p0.x)] = color;
		err += (slope > 0 ? slope : -slope);
		if (err >= 0.1)
		{
			p0.x += slope;
			while (err >= 0.1)
				err -= 0.01;
		}
		p0.y++;
	}
}

void	draw_linex(t_point p0, t_point p1, int **z, int color)
{
	double	slope;
	double	err;

	err = 0.0;
	if (p0.x > p1.x)
		swap_points(&p0, &p1);
	slope = (p1.y - p0.y) / (p1.x - p0.x);
	while (p0.x <= p1.x && p0.x <= WINW)
	{
		if (p0.x < WINW && p0.y < WINH && p0.x >= 0 && p0.x >= 0 && (int)p0.y *
				WINW + (int)p0.x < WINW * WINH && (int)p0.y * WINW +
				(int)p0.x > 0)
			z[0][((int)p0.y * WINW + (int)p0.x)] = color;
		err += (slope > 0 ? slope : -slope);
		if (err >= 0.1)
		{
			p0.y += slope;
			while (err >= 0.1)
				err -= 0.01;
		}
		p0.x++;
	}
}

void	draw_line(t_point p0, t_point p1, int **z, int color)
{
	if ((int)p1.x - (int)p0.x != 0 &&
			ABS(((int)p1.x - (int)p0.x)) >= ABS(((int)p1.y - (int)p0.y)))
		draw_linex(p0, p1, z, color);
	else if ((int)p1.y - (int)p0.y != 0 &&
			ABS((int)p1.x - (int)p0.x) <= ABS((int)p1.y - (int)p0.y))
		draw_liney(p0, p1, z, color);
	else if ((int)p0.y * WINW + (int)p0.x < WINW * WINH && (int)p0.y >= 0
			&& (int)p0.x >= 0)
		z[0][(int)p0.y * WINW + (int)p0.x] = color;
}

void	draw_it(t_fdf m)
{
	int		*z;
	t_point	p;
	int		i;
	int		j;

	m.ptr.img = mlx_new_image(m.ptr.mlx, WINW, WINH);
	z = (int*)mlx_get_data_addr(m.ptr.img, (int*)&p.x, (int*)&p.y, (int*)&p.z);
	i = m.h - 1;
	while (i >= 0)
	{
		j = m.w - 1;
		while (j >= 0)
		{
			m.t[i][j] = in_there(i, j, m.t[i][j].z0);
			rotate_point(&(m.t[i][j]), m);
			if (i + 1 < m.h)
				draw_line(m.t[i][j], m.t[i + 1][j], &z, m.color);
			if (j + 1 < m.w)
				draw_line(m.t[i][j], m.t[i][j + 1], &z, m.color);
			j--;
		}
		i--;
	}
	mlx_put_image_to_window(m.ptr.mlx, m.ptr.win, m.ptr.img, 0, 0);
}
