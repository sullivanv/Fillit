/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suvitiel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 18:00:57 by suvitiel          #+#    #+#             */
/*   Updated: 2017/01/26 02:45:13 by suvitiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"


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

/* malloc and free tab */
void	free_soluce(char ***soluce, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free((*soluce)[i]);
		i++;
	}
	free(*soluce);
}

char	**malloc_soluce(int size)
{
	char	**soluce;
	int i;
	int j;

	i = 0;
	soluce = (char**)malloc(sizeof(char*) * (size + 1));
	if (soluce == NULL)
		return (NULL);
	while (i < size)
	{
		soluce[i] = (char*)malloc(sizeof(char) * size + 1);
		if (soluce[i] == NULL)
			return (NULL);
		j = -1;
		while (++j < size)
				soluce[i][j] = '0';
		soluce[i][size] = 0;
		i++;
	}
	soluce[size] = 0;
	return (soluce);
}

/* copy tab */

char **ft_copy_tab(char **solucebase, int size)
{
	char **soluce = malloc_soluce(size);
	int i;
	int j;

	i = 0;
	while (solucebase[i])
	{
		j = 0;
		while (solucebase[i][j])
		{
			soluce[i][j] = solucebase[i][j];
			j++;
		}
		i++;
	}
	return soluce;
}


/* Algo */

int		pose_piece(t_tetriminos *tetri, char **soluce1, t_coord pos, int size)
{
	// TODO : check si je peux poser la piece tetri sur soluce a l'endroit pos
	int nbpos;
	t_coord posBase;
	t_coord posTetri;
	int countPiece;
	int piecepose;
	char **soluce = ft_copy_tab(soluce1, size);

	nbpos = 0;
	posBase = pos;
	posTetri.x = 0;
	posTetri.y = 0;
	piecepose = 0;
//	ft_print_result(soluce);
	printf("\nLa piece %c, est teste dans soluce a la position x:%d et y:%d.\n", tetri->id, pos.x, pos.y);
	while (pos.x < posBase.x + 4 && pos.x < size)
	{
		while (pos.y < posBase.y + 4 && pos.y < size)
		{
			countPiece = 0;
			while (countPiece < 4)
			{
				if (tetri->id == 'B')
				{
//					printf("\nLa piece %c, partie %d de coordonnes x:%d et y:%d est teste dans soluce a la position x:%d et y:%d.\n", tetri->id, countPiece, tetri->bc[countPiece].x, tetri->bc[countPiece].y, pos.x, pos.y);
//					sleep(1);
				}
				if (soluce[pos.y][pos.x] && soluce[pos.y][pos.x] == '0' && tetri->bc[countPiece].x == pos.x && tetri->bc[countPiece].y == pos.y)
					{
						//					if (tetri->id == 'B')
						//printf("piece pose++");
						soluce[pos.y][pos.x] = tetri->id;
						piecepose++;
					}
					countPiece++;
			}
			pos.y++;
		}
		pos.y = 0;
		pos.x++;
	}
//	sleep(3);
	if (piecepose != 4)
	{
		ft_print_result(soluce);
		printf("piece -> %d\n", piecepose);
		sleep(2);
		return (0);
	}
	else
		ft_print_result(soluce);
//	sleep(1);
	return 1;
}

int	test_piece(t_coord pos, t_tetriminos *tetri, char ***soluce, int size)
{
	if (pose_piece(tetri, *soluce, pos, size) == 1)
	{
		if (tetri->next)
			test_piece(pos, tetri->next, soluce, size);
		else
		{
			ft_print_result(*soluce);
			//	free soluce
			exit(1);
		}
	}
	printf("\nJe retest la piece %c avec cette position %d, %d\n", tetri->id, pos.x, pos.y);
	if (pos.y + 1 == size)
	{
		pos.y = 0;
		pos.x++;
	}
	else
		pos.y++;
	if (pos.x + 1 == size && pos.y + 1 == size)
		return (0);
	else
	{
		printf("recursive\n");
//		printf("\nJe retest la piece b avec une auter position %d, %d\n", pos.x, pos.y);
		test_piece(pos, tetri, soluce, size);
	}
	return (0);
}


char	**find_soluce(int size, t_tetriminos **begin, t_tetriminos *tetri, t_coord pos)
{
	char	**soluce;

	soluce = malloc_soluce(size);
	if (test_piece(pos, tetri, &soluce, size) == 1)
		return (soluce);
	else
	{
		free_soluce(&soluce, size);
		return (NULL);
	}
}

char	**ft_resolve(t_tetriminos *tetri)
{
	int sizemap;
	t_coord pos;

	pos.x = 0;
	pos.y = 0;
	sizemap = 3;
	if (!tetri)
		return (NULL);
	while (find_soluce(sizemap, &tetri, tetri, pos) == NULL)
		sizemap++;
	return (find_soluce(sizemap, &tetri, tetri, pos));
}

/* todo : link and remove */

int main()
{
	t_tetriminos	*tetri1;
	t_tetriminos	*tetri2;

	tetri1 = (t_tetriminos*)malloc(sizeof(t_tetriminos));
	tetri2 = (t_tetriminos*)malloc(sizeof(t_tetriminos));
	tetri1->bc[0].x = 0;
	tetri1->bc[1].x = 0;
	tetri1->bc[2].x = 0;
	tetri1->bc[3].x = 0;
	tetri1->bc[0].y = 0;
	tetri1->bc[1].y = 1;
	tetri1->bc[2].y = 2;
	tetri1->bc[3].y = 3;

	tetri2->bc[0].x = 0;
	tetri2->bc[1].x = 1;
	tetri2->bc[2].x = 0;
	tetri2->bc[3].x = 1;
	tetri2->bc[0].y = 0;
	tetri2->bc[1].y = 0;
	tetri2->bc[2].y = 1;
	tetri2->bc[3].y = 1;

	tetri1->id = 'A';
	tetri2->id = 'B';

	tetri1->next = tetri2;
	tetri2->next = NULL;

	ft_resolve(tetri1);
	return (0);
}




/*
char **find_soluce(int size, t_tetriminos **begin, t_tetriminos *tetri, t_coord pos[2])
{
	char	**soluce;

	soluce = malloc_soluce(size);
	pos[0] = pos[1];
	tetri = *begin;
	while (tetri)
	{
		if (pose_piece(tetri, soluce, pos[0]) == 1)
		{
			tetri = tetri->next;
			pos[0].x = 0;
			pos[0].y = 0;
////////////// ???????????????
			pos[1].x = 0;
			pos[1].y = 0;
////////////// ???????????????
		}
		// TODO : A TESTER
		else
		{
			if (pos[0].x + 1 == size)
			{
				pos[0].x = 0;
				pos[0].y++;
			}
			else
				pos[0].x++;
			if (pos[0].y + 1 == size && pos[0].x + 1 == size)
			{
				free_soluce(&soluce, size);
				if (pos[1].x + 1 == size)
				{
					pos[1].x = 0;
					pos[1].y++;
				}
				else
					pos[1].x++;
				if (pos[1].y + 1 == size && pos[1].x + 1 == size)
					return (NULL);
				find_soluce(size, begin, tetri, pos);
			}
		}
	}
	return (soluce);
}
*/
