/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush_one.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madinata <madinata@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 13:17:01 by madinata          #+#    #+#             */
/*   Updated: 2026/07/23 22:19:52 by madinata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH_ONE_H
# define RUSH_ONE_H

int	*create_arr(int size, int init_num);
int	**create_arr2d(int size_y, int size_x);

typedef struct s_index_stack
{
	int	*stack;
	int top;
}	t_index_stack;
t_index_stack *stack_create(int n);
void	stack_free(t_index_stack *stack, int n);
int		stack_push(t_index_stack *stack, int num);
int		stack_pop(t_index_stack *stack);
int		stack_view(t_index_stack *stack);

typedef struct s_clue_state
{
	int *target;
	t_index_stack *max_idx;
	int *max_height;
	int	*min_height;
}	t_clue_state;

typedef struct s_clues
{
	t_clue_state 	top;
	t_clue_state 	bot;
	t_clue_state	left;
	t_clue_state	right;
}	t_clues;

typedef struct s_game_state
{
	int		n;
	int		**board;
	t_clues	clues;
}	t_game_state;

#endif