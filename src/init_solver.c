/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_solver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suvitiel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 17:07:39 by suvitiel          #+#    #+#             */
/*   Updated: 2017/01/31 17:08:38 by suvitiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fillit.h>

char	**free_soluce(char ***soluce, int size)
{
	int i;

	i = -1;
	while (++i < size)
		free((*soluce)[i]);
	free(*soluce);
	return (NULL);
}

char	**malloc_soluce(int size)
{
	char	**soluce;
	int		i;
	int		j;

	i = -1;
	soluce = (char**)malloc(sizeof(char*) * (size + 1));
	if (soluce == NULL)
		return (NULL);
	while (++i < size)
	{
		soluce[i] = (char*)malloc(sizeof(char) * size + 1);
		if (soluce[i] == NULL)
			return (NULL);
		j = -1;
		while (++j < size)
			soluce[i][j] = '0';
		soluce[i][size] = 0;
	}
	soluce[size] = 0;
	return (soluce);
}

char	**ft_copy_tab(char **solucebase, int size)
{
	char	**soluce;
	int		i;
	int		j;

	i = -1;
	soluce = malloc_soluce(size);
	while (solucebase[++i])
	{
		j = -1;
		while (solucebase[i][++j])
			soluce[i][j] = solucebase[i][j];
	}
	return (soluce);
}
