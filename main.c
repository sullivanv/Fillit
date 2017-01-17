/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suvitiel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 18:00:57 by suvitiel          #+#    #+#             */
/*   Updated: 2017/01/17 01:02:42 by suvitiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		find_soluce(int size, t_tetriminos *tetri, char ***soluce)
{
	
	return (1);
}

void	free_soluce(char **soluce, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(soluce[i]);
		i++;
	}
	free(soluce);
}

char	**malloc_soluce(int size)
{
	char **soluce;
	int i;

	i = 0;
	soluce = (char**)malloc(sizeof(char*) * (size + 1));
	if (soluce == NULL)
		return (NULL);
	while (i < size)
	{
		soluce[i] = (char*)malloc(sizeof(char) * size + 1);
		if (soluce[i] == NULL)
			return (NULL);
		soluce[i][size] = 0;
		i++;
	}
	soluce[size] = 0;
	return (soluce);
}

char	**ft_resolve(t_tetriminos *tetri)
{
	char	**soluce;
	int sizemap;

	sizemap = 3;
	if (!tetri)
		return (NULL);
	soluce = malloc_soluce(sizemap);
	while (find_soluce(sizemap, tetri, &soluce) == 0)
	{
		free_soluce(soluce, sizemap);
		sizemap++;
		soluce = malloc_soluce(sizemap);
		if (soluce == NULL)
			return (NULL);
	}
	return (soluce);
}

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



int main()
{
	t_tetriminos	*tetri;

	ft_print_result(ft_resolve(tetri));
	return (0);
}
