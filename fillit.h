/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suvitiel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 18:01:15 by suvitiel          #+#    #+#             */
/*   Updated: 2017/01/17 01:00:45 by suvitiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct			s_coord
{
	int					x;
	int					y;
}						t_coord;

typedef struct			s_tetriminos
{
	char				id;
	t_coord				bc[4];
	struct s_tetriminos *next;
}						t_tetriminos;

int ft_strlen(char *str);

#endif
