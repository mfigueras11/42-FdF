/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 11:04:49 by mfiguera          #+#    #+#             */
/*   Updated: 2018/03/05 19:11:12 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define SCL 5
# define ABS(x) (x > 0 ? x : -1 * (x))
# define SCLY 10
# define WINH 1440
# define WINW 2650

# include "mlx.h"
# include <math.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "fcntl.h"

typedef struct		s_point
{
	double	x;
	double	y;
	double	z;
	double	z0;
}					t_point;

typedef struct		s_ptrs
{
	void	*img;
	void	*win;
	void	*mlx;
}					t_ptrs;

typedef struct		s_fdf
{
	t_ptrs	ptr;
	double	a1;
	double	a2;
	double	a3;
	double	scl;
	double	depth;
	int		offx;
	int		offy;
	int		h;
	int		w;
	t_point	**t;
	int		fd;
	int		color;
}					t_fdf;

int					keyispressed(int key, t_fdf *m);
int					keyispressed2(int key, t_fdf *m);
void				draw_it(t_fdf m);
void				rotate_point(t_point *p, t_fdf m);
t_point				in_there(double x, double y, double z);
void				swap_points(t_point *a, t_point *b);

#endif
