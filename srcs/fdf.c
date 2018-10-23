/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 11:02:23 by mfiguera          #+#    #+#             */
/*   Updated: 2018/03/05 19:22:45 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	**fill_grid(int h, int w)
{
	t_point	**grid;
	int		i;

	i = 0;
	if (!(grid = (t_point**)malloc(sizeof(*grid) * h)))
		exit(0);
	while (i < h)
	{
		if (!(grid[i++] = (t_point*)malloc(sizeof(t_point) * w)))
			exit(0);
	}
	return (grid);
}

void	get_measures(char *name, t_fdf *c)
{
	char	*line;
	int		l1;
	int		i;

	if ((c->fd = open(name, O_RDONLY)) == -1)
		exit(0);
	c->h = 0;
	c->w = 0;
	while (get_next_line(c->fd, &line) > 0)
	{
		(c->h)++;
		l1 = 0;
		i = -1;
		while (line[++i])
		{
			if (!ft_isspce(line[i]) && (ft_isspce(line[i + 1]) || !line[i + 1]))
				l1++;
		}
		if (l1 > c->w)
			c->w = l1;
		free(line);
	}
	free(line);
	close(c->fd);
	c->fd = open(name, O_RDONLY);
}

t_fdf	ft_get_map(char *name)
{
	t_fdf	c;
	char	*row;
	int		i;
	int		w;
	int		h;

	get_measures(name, &c);
	c.t = fill_grid(c.h, c.w);
	h = 0;
	while (get_next_line(c.fd, &row) > 0)
	{
		i = 0;
		w = -1;
		while (row[i + 0 * w++])
		{
			while (ft_isspce(row[i]) && row[i])
				i++;
			c.t[h][w] = in_there(w, h, ft_atoi(&row[i]));
			while (!ft_isspce(row[i]) && row[i])
				i++;
		}
		free(row + 0 * h++);
	}
	free(row + 0 * close(c.fd));
	return (c);
}

int		main(int ac, char **av)
{
	t_fdf map;

	if (ac != 2)
	{
		write(1, "Usage: ./fdf <path_to_file>\n", 29);
		return (1);
	}
	map = ft_get_map(av[1]);
	map.a1 = 0;
	map.a2 = 0;
	map.a3 = 0;
	map.scl = 10;
	map.depth = 1;
	map.offx = WINW / 4;
	map.offy = WINH * 3 / 4;
	map.ptr.mlx = mlx_init();
	map.ptr.win = mlx_new_window(map.ptr.mlx, WINW, WINH, "FdF");
	mlx_hook(map.ptr.win, 2, (map.color = 0xFFFFFF), keyispressed, &map);
	draw_it(map);
	mlx_loop(map.ptr.mlx);
	return (0);
}
