/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_board2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madinata <madinata@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 14:25:40 by madinata          #+#    #+#             */
/*   Updated: 2026/07/24 19:42:28 by madinata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush_one.h"

void	swap_int(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

// Sets running clues from one side.
void	clue_set_one(int coord, int n,
					t_clue_state *clue_state, t_direction direction)
{
	int	diff;
	int	index;
	int	row;
	int	col;

	row = coord / n;
	col = coord % n;
	if (direction == RIGHT || direction == LEFT)
		swap_int(&row, &col);
	if (direction == TOP || direction == LEFT)
		index = row;
	else if (direction == BOTTOM || direction == RIGHT)
		index = n - row - 1;
	if (stack_view(&clue_state->max_idx[col]) == -1)
	{
		stack_push(&clue_state->max_idx[col], index);
		clue_state->max_height[col] = index + 1;
		clue_state->min_height[col]++;
	}
	else if (index < stack_view(&clue_state->max_idx[col]))
	{
		diff = stack_push(&clue_state->max_idx[col], index);
		clue_state->max_height[col] -= diff - 1;
		clue_state->min_height[col]++;
	}
}

// Unsets running clues from one side.
void	clue_unset_one(int col, int row, t_clue_state *clue_state,
					t_direction direction)
{
	int	diff;
	int	axis;

	if (direction == TOP || direction == BOTTOM)
		axis = col;
	else
		axis = row;
	diff = stack_pop(&clue_state->max_idx[axis]);
	clue_state->max_height[axis] += diff - 1;
	clue_state->min_height[axis]--;
}

// Checks clues from one side.
int	clue_validate_one(int col, int row, t_clue_state *clue_state,
					t_direction direction)
{
	int	failed;
	int	axis;

	if (direction == TOP || direction == BOTTOM)
		axis = col;
	else
		axis = row;
	failed = 0;
	if (clue_state->max_height[axis] < clue_state->target[axis])
		failed = 1;
	if (clue_state->min_height[axis] > clue_state->target[axis])
		failed = 1;
	if (clue_state->min_height[axis] == clue_state->target[axis]
		&& stack_view(&clue_state->max_idx[axis]) != 0)
		failed = 1;
	return (failed);
}
