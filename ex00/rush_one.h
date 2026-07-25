/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush_one.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madinata <madinata@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 13:17:01 by madinata          #+#    #+#             */
/*   Updated: 2026/07/24 15:56:30 by madinata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH_ONE_H
# define RUSH_ONE_H

int				*create_arr(int size, int init_num);
int				**create_arr2d(int size_y, int size_x);

// index stack
typedef struct s_index_stack
{
	int	*stack;
	int	top;
}	t_index_stack;
void			stack_free(t_index_stack *stack, int n);
int				stack_push(t_index_stack *stack, int num);
int				stack_pop(t_index_stack *stack);
int				stack_view(t_index_stack *stack);
t_index_stack	*stack_create(int n);

// current clue state
typedef struct s_clue_state
{
	int				*target;
	t_index_stack	*max_idx;
	int				*max_height;
	int				*min_height;
}	t_clue_state;

// all clues
typedef struct s_clues
{
	t_clue_state	top;
	t_clue_state	bot;
	t_clue_state	left;
	t_clue_state	right;
}	t_clues;

// all game states
typedef struct s_game_state
{
	int		n;
	int		**board;
	t_clues	clues;
}	t_game_state;

// validator
int				initialize_clues(t_clues *clues, int n);
void			free_clues(t_clues *clues, int n);
int				is_valid_placement(int col, int row, t_game_state *state);
void			clue_unset(int col, int row, t_game_state *state);
typedef enum e_direction
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
}	t_direction;

int				solve(int col, int num, t_game_state *state);

#endif