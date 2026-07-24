/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_board.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madinata <madinata@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 13:16:50 by madinata          #+#    #+#             */
/*   Updated: 2026/07/24 16:30:29 by madinata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush_one.h"
#include <stdlib.h>

void	clue_unset_one(int col, int row, t_clue_state *clue_state);
int		clue_validate_one(int col, int row, t_clue_state *clue_state);
void	clue_set_one(int coord, int n, t_clue_state *clue_state,
			t_direction direction);

// Sets a number into clues. Needs to be unset manually if succeeds.
void	clue_set(int col, int row, t_game_state *state)
{
	int	coord;

	coord = row * state->n + col;
	clue_set_one(coord, state->n, &state->clues.top, TOP);
	clue_set_one(coord, state->n, &state->clues.bot, BOTTOM);
	clue_set_one(coord, state->n, &state->clues.left, LEFT);
	clue_set_one(coord, state->n, &state->clues.right, RIGHT);
}

// Reverses a clue in coordinate, restoring old one.
void	clue_unset(int col, int row, t_game_state *state)
{
	if (row == stack_view(&state->clues.top.max_idx[col]))
		clue_unset_one(col, -1, &state->clues.top);
	if (state->n - row - 1 == stack_view(&state->clues.bot.max_idx[col]))
		clue_unset_one(col, -1, &state->clues.bot);
	if (col == stack_view(&state->clues.left.max_idx[row]))
		clue_unset_one(-1, row, &state->clues.left);
	if (state->n - col - 1 == stack_view(&state->clues.right.max_idx[row]))
		clue_unset_one(-1, row, &state->clues.right);
}

// Checks if a given poistion is valid or not compared to the clues.
// Returns 1 on succes, 0 otherwise.
int	is_valid_placement(int col, int row, t_game_state *state)
{
	int				failed;

	failed = 0;
	clue_set(col, row, state);
	failed += clue_validate_one(col, -1, &state->clues.top);
	failed += clue_validate_one(col, -1, &state->clues.bot);
	failed += clue_validate_one(-1, row, &state->clues.left);
	failed += clue_validate_one(-1, row, &state->clues.right);
	if (!failed)
		return (1);
	clue_unset(col, row, state);
	return (0);
}

int	initialize_clues(t_clues *clues, int n)
{
	t_clue_state	*positions[4];
	int				i;

	positions[0] = &clues->top;
	positions[1] = &clues->bot;
	positions[2] = &clues->left;
	positions[3] = &clues->right;
	i = 0;
	while (i < 4)
	{
		positions[i]->target = create_arr(n, 0);
		positions[i]->max_height = create_arr(n, 0);
		positions[i]->min_height = create_arr(n, 0);
		positions[i]->max_idx = stack_create(n);
		if (!positions[i]->target || !positions[i]->max_height
			|| !positions[i]->min_height || !positions[i]->max_idx)
			return (free_clues(clues, n), 0);
		i++;
	}
	return (1);
}

void	free_clues(t_clues *clues, int n)
{
	t_clue_state	*positions[4];
	int				i;

	positions[0] = &clues->top;
	positions[1] = &clues->bot;
	positions[2] = &clues->left;
	positions[3] = &clues->right;
	i = 0;
	while (i < 4)
	{
		free(positions[i]->target);
		free(positions[i]->max_height);
		free(positions[i]->min_height);
		stack_free(positions[i]->max_idx, n);
		i++;
	}
}
