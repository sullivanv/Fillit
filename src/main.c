/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 18:47:49 by hanguelk          #+#    #+#             */
/*   Updated: 2017/01/30 17:55:02 by hanguelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fillit.h>

void			clean_tlist(t_tetriminos **tlist)
{
	t_tetriminos *tl;

	tl = *tlist;
	while (tl)
	{
		free(tl);
		tl = (*tlist)->next;
		*tlist = tl;
	}
}

t_tetriminos	*read_tetriminos(char *file, int i, int r, t_tetriminos *bk)
{
	char			*tmp;
	int				fd;
	t_tetriminos	*tlist;
	t_tetriminos	*tetri;

	tlist = NULL;
	if (!(tmp = (char *)malloc(sizeof(char) * 22)))
		print_error();
	if (!(fd = open(file, O_RDONLY)))
		print_error();
	while ((read(fd, tmp, 21)) > 0)
	{
		tetri = parse_tetriminos(tmp, 'A' + i++);
		if (tlist)
			tlist->next = tetri;
		else
			bk = tetri;
		tlist = move_leftup(tetri);
		r = (tmp[20] == '\n') ? 1 : 0;
		ft_bzero(tmp, 21);
	}
	close(fd);
	free(tmp);
	return ((!(tlist) || r == 1) ? NULL : bk);
}

int				main(int argc, char **argv)
{
	t_tetriminos	*tlist;

	tlist = NULL;
	if (argc == 2)
	{
		if ((tlist = read_tetriminos(argv[1], 0, 0, tlist)))
		{
			ft_resolve(tlist);
			clean_tlist(&tlist);
		}
		else
			print_error();
	}
	else
		print_usage();
	return (0);
}
