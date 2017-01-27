/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suvitiel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 18:00:57 by suvitiel          #+#    #+#             */
/*   Updated: 2017/01/27 17:01:08 by suvitiel         ###   ########.fr       */
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

/* remove old piece */

char **removepiece(char **soluce, t_tetriminos *tetri)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (soluce[i])
	{
		j = 0;
		while (soluce[i][j])
		{
			if (soluce[i][j] >= tetri->id)
				soluce[i][j] = '0';
			j++;
		}
		i++;
	}
	return soluce;
}


/* Algo */

/* check si je peux poser la piece tetri sur soluce a l'endroit pos */
char		**pose_piece(t_tetriminos *tetri, char **soluce1, t_coord pos, int size)
{
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
	pos = posTetri;
//	ft_print_result(soluce);
//	printf("\nLa piece %c, est teste dans soluce a la position x:%d et y:%d.\n", tetri->id, pos.x, pos.y);
	soluce = removepiece(soluce, tetri);
	while (pos.x < posBase.x + 4 && pos.x < size)
	{
		while (pos.y < posBase.y + 4 && pos.y < size)
		{
			countPiece = 0;
			while (countPiece < 4)
			{
//				printf("\nLa piece %c, partie %d de coordonnes x:%d et y:%d est teste dans soluce a la position x:%d et y:%d.\n", tetri->id, countPiece+1, tetri->bc[countPiece].x, tetri->bc[countPiece].y, pos.x, pos.y);
//				if (tetri->id == 'B')
//				{
//					printf("\nLa piece %c, partie %d de coordonnes x:%d et y:%d est teste dans soluce a la position x:%d et y:%d.\n", tetri->id, countPiece, tetri->bc[countPiece].x, tetri->bc[countPiece].y, pos.x, pos.y);
//					sleep(1);
//				}
				if (soluce[pos.x][pos.y] && soluce[pos.x][pos.y] == '0' && tetri->bc[countPiece].x == posTetri.x - posBase.x && tetri->bc[countPiece].y == posTetri.y - posBase.y)
				{
					//					if (tetri->id == 'B')
//					printf("La piece %c, parti %d, est pose car (tetri->bc[countPiece].x) = %d donc egale a posTetri.x - posBase.x= %d - %d. (POur info pos.x = %d)\n", tetri->id, countPiece+1, tetri->bc[countPiece].x, posTetri.x, posBase.x, pos.x);
//					printf("La piece %c, parti %d, est pose car (tetri->bc[countPiece].y) = %d donc egale a posTetri.y - posBase.y= %d - %d. (POur info pos.y = %d)\n", tetri->id, countPiece+1, tetri->bc[countPiece].y, posTetri.y, posBase.y, pos.y);
//					printf("piece pose++");
					soluce[pos.x][pos.y] = tetri->id;
					piecepose++;
				}
//				else
//				{
//					printf("La piece %c, parti %d, nes pas pose car tetri->bc[countPiece].x= %d donc pas egale a posTetri.x - posBase.x = %d - %d. (POur info pos.x = %d)\n", tetri->id, countPiece+1, tetri->bc[countPiece].x, posBase.x, posTetri.x, pos.x);
//					printf("La piece %c, parti %d, nes pas pose car tetri->bc[countPiece].y= %d donc pas egale a posTetri.y - posBase.y = %d - %d. (POur info pos.y = %d)\n", tetri->id, countPiece+1, tetri->bc[countPiece].y, posBase.y, posTetri.y, pos.y);
//				}
				countPiece++;
			}
			pos.y++;
			posTetri.y++;
		}
		pos.y = 0;
		posTetri.y = 0;
		pos.x++;
		posTetri.x++;
	}
//	ft_print_result(soluce);
//	printf("piece -> %d\n", piecepose);
//	sleep(1);
	if (piecepose != 4)
	{
//		ft_print_result(soluce);
//		printf("piece -> %d\n", piecepose);
//		sleep(2);
		return (NULL);
	}
	else
//		ft_print_result(soluce);
//	sleep(1);
	return soluce;
}


/* backtracking */
int	test_piece(t_coord pos, t_tetriminos *tetri, char ***soluce, int size)
{
	t_coord newpos;
	if (pose_piece(tetri, *soluce, pos, size) != NULL)
	{
		*soluce = pose_piece(tetri, *soluce, pos, size);
		if (tetri->next)
		{
//			printf("la prochaine piece a test est %c\n", tetri->next->id);
			newpos.x = 0;
			newpos.y = 0;
			test_piece(newpos, tetri->next, soluce, size);
		}
		else
		{
			ft_print_result(*soluce);
			//	free soluce
			exit(1);
		}
	}
//	printf("\nJe retest la piece %c avec cette position %d, %d\n", tetri->id, pos.x, pos.y);
	if (pos.y + 1 == size)
	{
		pos.y = 0;
		pos.x++;
	}
	else
		pos.y++;
	if (pos.y + 1 == size && pos.x + 1 == size)
		return (0);
	else
	{
//		printf("recursive\n");
//		printf("\nJe retest la piece b avec une auter position %d, %d\n", pos.x, pos.y);
		test_piece(pos, tetri, soluce, size);
	}
	return (0);
}

/* malloc, algo puis free */
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

/* test pour chaque taille de map en commencant par 2 */
char	**ft_resolve(t_tetriminos *tetri)
{
	int sizemap;
	t_coord pos;

	pos.x = 0;
	pos.y = 0;
	sizemap = 2;
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
	t_tetriminos	*tetri3;
	t_tetriminos	*tetri4;

	tetri1 = (t_tetriminos*)malloc(sizeof(t_tetriminos));
	tetri2 = (t_tetriminos*)malloc(sizeof(t_tetriminos));
	tetri3 = (t_tetriminos*)malloc(sizeof(t_tetriminos));
	tetri4 = (t_tetriminos*)malloc(sizeof(t_tetriminos));
/* test 1
	tetri1->bc[0].x = 0;
	tetri1->bc[1].x = 1;
	tetri1->bc[2].x = 2;
	tetri1->bc[3].x = 3;
	tetri1->bc[0].y = 0;
	tetri1->bc[1].y = 0;
	tetri1->bc[2].y = 0;
	tetri1->bc[3].y = 0;

	tetri2->bc[0].x = 0;
	tetri2->bc[1].x = 1;
	tetri2->bc[2].x = 0;
	tetri2->bc[3].x = 1;
	tetri2->bc[0].y = 0;
	tetri2->bc[1].y = 0;
	tetri2->bc[2].y = 1;
	tetri2->bc[3].y = 1;
*/

/* test2 */
	tetri1->bc[0].x = 0;
	tetri1->bc[1].x = 0;
	tetri1->bc[2].x = 1;
	tetri1->bc[3].x = 2;
	tetri1->bc[0].y = 0;
	tetri1->bc[1].y = 1;
	tetri1->bc[2].y = 1;
	tetri1->bc[3].y = 1;

	tetri2->bc[0].x = 0;
	tetri2->bc[1].x = 0;
	tetri2->bc[2].x = 0;
	tetri2->bc[3].x = 0;
	tetri2->bc[0].y = 0;
	tetri2->bc[1].y = 1;
	tetri2->bc[2].y = 2;
	tetri2->bc[3].y = 3;

	tetri3->bc[0].x = 0;
	tetri3->bc[1].x = 1;
	tetri3->bc[2].x = 1;
	tetri3->bc[3].x = 1;
	tetri3->bc[0].y = 0;
	tetri3->bc[1].y = 0;
	tetri3->bc[2].y = 1;
	tetri3->bc[3].y = 2;

	tetri4->bc[0].x = 0;
	tetri4->bc[1].x = 0;
	tetri4->bc[2].x = 1;
	tetri4->bc[3].x = 1;
	tetri4->bc[0].y = 0;
	tetri4->bc[1].y = 1;
	tetri4->bc[2].y = 1;
	tetri4->bc[3].y = 2;



	tetri1->id = 'A';
	tetri2->id = 'B';
	tetri3->id = 'C';
	tetri4->id = 'D';

	tetri1->next = tetri2;
	tetri2->next = tetri3;
	tetri3->next = tetri4;
	tetri4->next = NULL;

	ft_resolve(tetri1);
	return (0);
}
