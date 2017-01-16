/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suvitiel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 18:00:57 by suvitiel          #+#    #+#             */
/*   Updated: 2017/01/11 18:18:51 by suvitiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	free_soluce(char ***soluce)
{
// TODO : Free le tableau de solution
}

char	**ft_resolve(t_tetriminos tetri)
{
	int				sizemap;
	char			**soluce;

	sizemap = 4;
	if (!tetri)
		return (NULL);
	soluce = (char**)malloc(sizeof(char*) * (sizemap + 1));
	if (soluce == NULL)
		return (NULL);
	while (find_soluce(sizemap, tetri, &soluce) == 0)
	{
		sizemap++;
		free_soluce(&soluce);
		soluce = (char**)malloc(sizeof(char*) * (sizemap + 1));
		if (soluce == NULL)
			return (NULL);
	}
	return (soluce);
}

void	ft_print_result(char **soluce)
{
	if (!soluce)
		return ;
// TODO: afficher tableau Zer
}

int main()
{
	t_tetriminos	tetri;

	ft_print_result(ft_resolve(tetri));
	return (0);
}
