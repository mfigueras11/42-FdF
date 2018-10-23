/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 15:44:34 by mfiguera          #+#    #+#             */
/*   Updated: 2018/03/05 19:24:38 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_point(t_point *p, t_fdf m)
{
	double temp;

	p->x = p->x;
	p->z = p->z0 * cos(m.a1) * m.depth - p->y * sin(m.a1);
	p->y = p->y * cos(m.a1) + p->z0 * sin(m.a1) * m.depth;
	temp = p->z;
	p->z = p->x * sin(m.a2) + p->z * cos(m.a2);
	p->x = p->x * cos(m.a2) - temp * sin(m.a2);
	temp = p->x;
	p->x = (p->x * cos(m.a3) + p->y * sin(m.a3));
	p->y = (p->y * cos(m.a3) - temp * sin(m.a3));
	p->x = p->x * m.scl + m.offx;
	p->y = p->y * m.scl + m.offy;
}

t_point	in_there(double x, double y, double z)
{
	t_point p;

	p.x = x;
	p.y = y;
	p.z0 = z;
	return (p);
}

int		keyispressed2(int key, t_fdf *m)
{
	if (key == 124)
		m->offx += 10;
	if (key == 15)
		m->color += 0x080000;
	if (key == 5)
		m->color += 0x000800;
	if (key == 11)
		m->color += 0x000008;
	draw_it(*m);
	return (0);
}

void	swap_points(t_point *a, t_point *b)
{
	t_point temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
