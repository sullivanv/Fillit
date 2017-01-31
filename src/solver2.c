/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suvitiel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 16:42:08 by suvitiel          #+#    #+#             */
/*   Updated: 2017/01/31 17:09:16 by suvitiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fillit.h>

char	**removepiece(char **soluce, t_tetriminos *tetri)
{
	int i;
	int j;

	i = -1;
	while (soluce[++i])
	{
		j = -1;
		while (soluce[i][++j])
		{
			if (soluce[i][j] >= tetri->id)
				soluce[i][j] = '0';
		}
	}
	return (soluce);
}

void	init_pos(int *x, int *y)
{
	*x = 0;
	*y = 0;
}

void	init_var(t_coord *pos, t_coord *posbase)
{
	*posbase = *pos;
	init_pos(&pos->x, &pos->y);
}

void	init_tab(char ***s, char **so1, int size, t_tetriminos *tetri)
{
	*s = ft_copy_tab(so1, size);
	*s = removepiece(*s, tetri);
}

char	**pose_piece(t_tetriminos *tetri, char **so1, t_coord pos, int size)
{
	t_coord	posbase;
	int		i[2];
	char	**s;

	i[1] = 0;
	init_var(&pos, &posbase);
	init_tab(&s, so1, size, tetri);
	while (pos.x < posbase.x + 4 && pos.x < size)
	{
		while (pos.y < posbase.y + 4 && pos.y < size)
		{
			i[0] = -1;
			while (++i[0] < 4)
			{
				if (s[pos.x][pos.y] && s[pos.x][pos.y] == '0' &&
					tetri->bc[i[0]].x == pos.x - posbase.x &&
					tetri->bc[i[0]].y == pos.y - posbase.y && ++i[1])
					s[pos.x][pos.y] = tetri->id;
			}
			pos.y++;
		}
		pos.y = 0;
		pos.x++;
	}
	return (i[1] == 4 ? s : free_soluce(&s, size));
}
