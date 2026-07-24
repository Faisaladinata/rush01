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

void	initialize_clues(t_clues *clues, int n)
{
	clues->top.target = create_arr(n, 0);
	clues->top.max_height = create_arr(n, 0);
	clues->top.min_height = create_arr(n, 0);
	clues->top.max_idx = stack_create(n);
	clues->bot.target = create_arr(n, 0);
	clues->bot.max_height = create_arr(n, 0);
	clues->bot.min_height = create_arr(n, 0);
	clues->bot.max_idx = stack_create(n);
	clues->left.target = create_arr(n, 0);
	clues->left.max_height = create_arr(n, 0);
	clues->left.min_height = create_arr(n, 0);
	clues->left.max_idx = stack_create(n);
	clues->right.target = create_arr(n, 0);
	clues->right.max_height = create_arr(n, 0);
	clues->right.min_height = create_arr(n, 0);
	clues->right.max_idx = stack_create(n);
}

void	free_clues(t_clues *clues, int n)
{
	free(clues->top.target);
	free(clues->top.max_height);
	free(clues->top.min_height);
	stack_free(clues->top.max_idx, n);
	free(clues->bot.target);
	free(clues->bot.max_height);
	free(clues->bot.min_height);
	stack_free(clues->bot.max_idx, n);
	free(clues->left.target);
	free(clues->left.max_height);
	free(clues->left.min_height);
	stack_free(clues->left.max_idx, n);
	free(clues->right.target);
	free(clues->right.max_height);
	free(clues->right.min_height);
	stack_free(clues->right.max_idx, n);
}

/*
// DELETE ME
void	temp_clues_target(t_clues *clues, int n)
{
	int *top = (int[]){1, 2, 4, 3, 4, 3, 3, 3, 4};
	int *bot = (int[]){3, 4, 1, 3, 3, 3, 2, 4, 2};
	int *left = (int[]){1, 2, 4, 4, 2, 3, 3, 5, 2};
	int *right = (int[]){4, 6, 3, 3, 2, 3, 2, 1, 3};

	for (int i = 0; i < n; i++)
		clues->top.target[i] = top[i];
	for (int i = 0; i < n; i++)
		clues->bot.target[i] = bot[i];
	for (int i = 0; i < n; i++)
		clues->left.target[i] = left[i];
	for (int i = 0; i < n; i++)
		clues->right.target[i] = right[i];
}
#include <stdio.h>
int main()
{
	t_game_state state;
	state.n = 4;
	state.board = (int*[]){
		(int[]){0, 0, 0, 0},
		(int[]){0, 0, 0, 0},
		(int[]){0, 0, 0, 0},
		(int[]){0, 0, 0, 0}
	};
	initialize_clues(&state.clues, 4);
	temp_clues_target(&state.clues, 4);

	printf("out 1: %d\n", is_valid_placement(0, 3, &state));
	printf("out 2: %d\n", is_valid_placement(0, 1, &state)); //
	printf("out 3: %d\n", is_valid_placement(1, 2, &state));
	printf("out 4: %d\n", is_valid_placement(2, 3, &state)); //
	printf("out 5: %d\n", is_valid_placement(2, 1, &state));
	printf("out 6: %d\n", is_valid_placement(3, 2, &state)); //
	printf("out 7: %d\n", is_valid_placement(3, 0, &state));
	printf("out 8: %d\n", is_valid_placement(0, 2, &state));
	printf("out 9: %d\n", is_valid_placement(0, 1, &state));
}
*/