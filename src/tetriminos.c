/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetriminos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 18:47:33 by hanguelk          #+#    #+#             */
/*   Updated: 2017/01/30 17:06:13 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fillit.h>

t_tetriminos	*parse_tetriminos(char *b, char magic)
{
	int				v[3];
	t_tetriminos	*tetri;

	ft_memset(&v, 0, sizeof(int) * 3);
	if (!(tetri = (t_tetriminos *)malloc(sizeof(t_tetriminos))))
		print_error();
	tetri->id = magic;
	tetri->next = NULL;
	while (*b)
	{
		if (*b != '.' && *b != '#' && (*b == '\n' && (v[1] != 4 && v[1] != 0)))
			print_error();
		if (*b == '#')
		{
			tetri->bc[v[2]].x = v[0];
			tetri->bc[v[2]].y = v[1];
			v[2]++;
		}
		v[0] += (v[1] == 4 && *b == '\n') ? 1 : 0;
		v[1] = (v[1] == 4 && *b == '\n') ? 0 : v[1] + 1;
		b++;
	}
	if (v[2] > 4 || !(check_valid(tetri)))
		print_error();
	return (tetri);
}

int				check_pos_block(t_tetriminos *tetri, int i, int j)
{
	if (tetri->bc[j].x == tetri->bc[i].x &&
			tetri->bc[j].y - 1 == tetri->bc[i].y)
		return (1);
	else if (tetri->bc[j].y == tetri->bc[i].y &&
			tetri->bc[j].x + 1 == tetri->bc[i].x)
		return (1);
	else if (tetri->bc[j].y == tetri->bc[i].y &&
			tetri->bc[j].x - 1 == tetri->bc[i].x)
		return (1);
	else if (tetri->bc[j].x == tetri->bc[i].x &&
			tetri->bc[j].y + 1 == tetri->bc[i].y)
		return (1);
	return (0);
}

int				check_valid(t_tetriminos *tetri)
{
	int i;
	int j;
	int flag;

	i = 0;
	flag = 0;
	while (i < 4)
	{
		j = i;
		while (j < 4)
			if (check_pos_block(tetri, i, j++))
				flag++;
		i++;
	}
	return (flag >= 3) ? 1 : 0;
}

t_coord			*find_min(t_tetriminos *tetri)
{
	int		i;
	t_coord	*min;

	min = (t_coord *)malloc(sizeof(t_coord));
	min->x = 4;
	min->y = 4;
	i = 0;
	while (i < 4)
	{
		if (tetri->bc[i].x < min->x)
			min->x = tetri->bc[i].x;
		if (tetri->bc[i].y < min->y)
			min->y = tetri->bc[i].y;
		i++;
	}
	return (min);
}

t_tetriminos	*move_leftup(t_tetriminos *tetri)
{
	int		i;
	t_coord	*min;

	i = 0;
	min = find_min(tetri);
	while (i < 4)
	{
		tetri->bc[i].x -= min->x;
		tetri->bc[i].y -= min->y;
		i++;
	}
	free(min);
	return (tetri);
}
