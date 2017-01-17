/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suvitiel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 18:00:57 by suvitiel          #+#    #+#             */
/*   Updated: 2017/01/17 04:23:53 by suvitiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/* malloc and free tab */

void	free_soluce(char **soluce, int size)
{
/*	int i;

	i = 0;
	while (i < size)
	{
		free(soluce[i]);
		i++;
	}
	free(soluce);*/
}

char	**malloc_soluce(int size)
{
	char **soluce;
	int i;
	int j;

	j = -1;
	i = 0;
	soluce = (char**)malloc(sizeof(char*) * (size + 1));
	if (soluce == NULL)
		return (NULL);
	while (i < size)
	{
		soluce[i] = (char*)malloc(sizeof(char) * size + 1);
		if (soluce[i] == NULL)
			return (NULL);
		//	while (++j < size)
		//		soluce[i][j] = '0';
		soluce[i][size] = 0;
		i++;
	}
	soluce[size] = 0;
	return (soluce);
}


/* Algo */

int		pose_piece(t_tetriminos *tetri, char **soluce, t_coord pos)
{
	return 1;
}

char	**find_soluce(int size, t_tetriminos *tetri, char **soluce, t_coord pos)
{
	soluce = malloc_soluce(size);
	while (tetri)
	{
		if (pose_piece(tetri, soluce, pos) == 1)
		{
			tetri++;
			pos.x = 0;
			pos.y = 0;
		}
		else
		{
			if (pos.x + 1 == size)
			{
				pos.x = 0;
				pos.y++;
			}
			else
				pos.x++;
			if (pos.y + 1 == size && pos.x + 1 == size)
			{
				free_soluce(soluce, size);
				return (NULL);
			}
		}
	}
	return (soluce);
}

char	**ft_resolve(t_tetriminos *tetri)
{
	char	**soluce;
	int sizemap;
	t_coord pos;

	pos.x = 0;
	pos.y = 0;
	sizemap = 3;
	if (!tetri)
		return (NULL);
	while (find_soluce(sizemap, tetri, soluce, pos) == NULL)
		sizemap++;
	return (find_soluce(sizemap, tetri, soluce, pos));
}

/* print function */

void	ft_print_result(char **soluce)
{
	int i;
	int j;

	if (!soluce)
		return ;
	i = 0;
	while (soluce[i])
	{
		write(1, soluce[i], ft_strlen(soluce[i]));
		write(1, "\n", 1);
		i++;
		}
}

/* todo : link and remove */

int main()
{
	t_tetriminos	*tetri1;
	t_tetriminos	*tetri2;

	tetri1 = (t_tetriminos*)malloc(sizeof(tetri1));
	tetri2 = (t_tetriminos*)malloc(sizeof(tetri2));
	tetri1->bc[0].x = 0;
	tetri1->bc[1].x = 0;
	tetri1->bc[2].x = 0;
	tetri1->bc[3].x = 0;
	tetri1->bc[0].y = 0;
	tetri1->bc[1].y = 1;
	tetri1->bc[2].y = 2;
	tetri1->bc[3].y = 3;

	tetri2->bc[0].x = 0;
	tetri2->bc[1].x = 0;
	tetri2->bc[2].x = 1;
	tetri2->bc[3].x = 1;
	tetri2->bc[0].y = 0;
	tetri2->bc[1].y = 0;
	tetri2->bc[2].y = 1;
	tetri2->bc[3].y = 1;

	tetri1->id = 'A';
	tetri2->id = 'B';

	tetri1->next = tetri2;
	tetri2->next = NULL;
	ft_print_result(ft_resolve(tetri1));
	return (0);
}
