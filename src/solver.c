/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suvitiel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 16:42:08 by suvitiel          #+#    #+#             */
/*   Updated: 2017/01/31 17:10:34 by suvitiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fillit.h>

int		test_piece(t_coord p, t_tetriminos *t, char ***s, int siz)
{
	t_coord newpos;

	if (pose_piece(t, *s, p, siz) != NULL)
	{
		*s = pose_piece(t, *s, p, siz);
		if (t->next)
		{
			init_pos(&newpos.x, &newpos.y);
			test_piece(newpos, t->next, s, siz);
		}
		else
		{
			ft_print_result(*s);
			free_soluce(s, siz);
			exit(0);
		}
	}
	if (p.y + 1 == siz)
	{
		p.y = 0;
		p.x++;
	}
	else
		p.y++;
	return ((p.y + 1 == siz && p.x + 1 == siz) ? 0 : test_piece(p, t, s, siz));
}

char	**find_soluce(int si, t_tetriminos *t, t_coord p)
{
	char	**s;

	s = malloc_soluce(si);
	return (test_piece(p, t, &s, si) == 1 ? s : free_soluce(&s, si));
}

int		ft_sqrt_rec(int nb, int i)
{
	if (i * i > nb)
		return (i);
	return (ft_sqrt_rec(nb, i + 1));
}

int		find_size(t_tetriminos *tetri)
{
	int i;

	i = 0;
	while (tetri->next)
	{
		tetri = tetri->next;
		i = i + 4;
	}
	return (i > 2 ? ft_sqrt_rec(i, 0) : 2);
}

void	ft_resolve(t_tetriminos *tetri)
{
	int		sizemap;
	t_coord pos;

	pos.x = 0;
	pos.y = 0;
	sizemap = find_size(tetri);
	if (!tetri)
		return ;
	while (find_soluce(sizemap, tetri, pos) == NULL)
		sizemap++;
}
