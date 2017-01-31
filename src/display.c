/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 18:47:41 by hanguelk          #+#    #+#             */
/*   Updated: 2017/01/31 17:22:39 by suvitiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fillit.h>

void	print_usage(void)
{
	write(1, "[+] Usage: ./fillit tetriminosfile.fillit\n", 42);
	exit(-1);
}

void	print_error(void)
{
	write(1, "error\n", 6);
	exit(-1);
}

void	display_tetri(t_tetriminos *tetri)
{
	int i;
	int j;
	int n;

	i = 0;
	j = 0;
	n = 0;
	while (i < 4)
	{
		while (j < 4)
		{
			if (tetri->bc[n].x == i && tetri->bc[n].y == j)
			{
				write(1, &tetri->id, 1);
				n++;
			}
			else
				ft_putchar('.');
			if (j == 3)
				ft_putchar(0x0a);
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_putstr_zer(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '0')
			ft_putchar('.');
		else
			ft_putchar(str[i]);
		i++;
	}
}

void	ft_print_result(char **soluce)
{
	int i;

	if (!soluce)
		return ;
	i = 0;
	while (soluce[i])
	{
		ft_putstr_zer(soluce[i]);
		write(1, "\n", 1);
		i++;
	}
}
