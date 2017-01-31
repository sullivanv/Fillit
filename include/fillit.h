/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanguelk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 20:52:57 by hanguelk          #+#    #+#             */
/*   Updated: 2017/01/31 17:21:28 by suvitiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <libft.h>

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

t_tetriminos			*parse_tetriminos(char *buf, char magic);
int						check_valid(t_tetriminos *tetri);
void					clean_tlist(t_tetriminos **tlist);
t_tetriminos			*move_leftup(t_tetriminos *tetri);
t_coord					*find_min(t_tetriminos *tetri);
char					**free_soluce(char ***soluce, int size);
char					**malloc_soluce(int size);
char					**ft_copy_tab(char **solucebase, int size);
char					**removepiece(char **soluce, t_tetriminos *tetri);
char					**pose_piece(t_tetriminos *tetri, char **soluce1,
									t_coord pos, int size);
int						test_piece(t_coord pos, t_tetriminos *tetri,
									char ***soluce, int size);
char					**find_soluce(int size, t_tetriminos *tetri,
									t_coord pos);
void					ft_resolve(t_tetriminos *tetri);
void					print_usage(void);
void					print_error(void);
void					ft_print_result(char **soluce);
void					display_tetri(t_tetriminos *tetri);
void					init_pos(int *x, int *y);

#endif
