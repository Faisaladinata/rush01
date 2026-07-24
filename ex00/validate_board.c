#include "rush_one.h"
#include <stdlib.h>

// Sets a number into clues. Needs to be unset manually. Returns 1 on succes or 0 on failure.
int clue_set(int col, int row, t_game_state *state)
{
	int	diff;
	// This is for top
	if (stack_view(&state->clues.top.max_idx[col]) == -1)
	{
		// this is first one so it needs to calculate current height.
		stack_push(&state->clues.top.max_idx[col], row);
		// calculate current height based on position
		state->clues.top.max_height[col] = row + 1;
		state->clues.top.min_height[col]++;
	}
	else if (row < stack_view(&state->clues.top.max_idx[col]))
	{
		diff = stack_push(&state->clues.top.max_idx[col], row);
		// if it jumps too much, decrease the max_height
		state->clues.top.max_height[col] -= diff - 1;
		state->clues.top.min_height[col]++;
	}
	// now for bottom
	if (stack_view(&state->clues.bot.max_idx[col]) == -1)
	{
		stack_push(&state->clues.bot.max_idx[col], state->n - row - 1);
		state->clues.bot.max_height[col] = state->n - row;
		state->clues.bot.min_height[col]++;
	}
	else if (state->n - row - 1 < stack_view(&state->clues.bot.max_idx[col]))
	{
		diff = stack_push(&state->clues.bot.max_idx[col], state->n - row - 1);
		state->clues.bot.max_height[col] -= diff - 1;
		state->clues.bot.min_height[col]++;
	}
	// left
	if (stack_view(&state->clues.left.max_idx[row]) == -1)
	{
		stack_push(&state->clues.left.max_idx[row], col);
		state->clues.left.max_height[row] = col + 1;
		state->clues.left.min_height[row]++;
	}
	else if (col < stack_view(&state->clues.left.max_idx[row]))
	{
		diff = stack_push(&state->clues.left.max_idx[row], col);
		state->clues.left.max_height[row] -= diff - 1;
		state->clues.left.min_height[row]++;
	}
	// right
	if (stack_view(&state->clues.right.max_idx[row]) == -1)
	{
		stack_push(&state->clues.right.max_idx[row], state->n - col - 1);
		state->clues.right.max_height[row] = state->n - col;
		state->clues.right.min_height[row]++;
	}
	else if (state->n - col - 1 < stack_view(&state->clues.right.max_idx[row]))
	{
		diff = stack_push(&state->clues.right.max_idx[row], state->n - col - 1);
		state->clues.right.max_height[row] -= diff - 1;
		state->clues.right.min_height[row]++;
	}
	return (1);
}

// Reverses clue in coordinate, restoring old one. Returns 1 on succes or 0 on failure.
int clue_unset(int col, int row, t_game_state *state)
{
	int	diff;
	// Top
	if (row == stack_view(&state->clues.top.max_idx[col]))
	{
		diff = stack_pop(&state->clues.top.max_idx[col]);
		state->clues.top.max_height[col] += diff - 1;
		state->clues.top.min_height[col]--;
	}
	// Bot
	if (state->n - row - 1 == stack_view(&state->clues.bot.max_idx[col]))
	{
		diff = stack_pop(&state->clues.bot.max_idx[col]);
		state->clues.bot.max_height[col] += diff - 1;
		state->clues.bot.min_height[col]--;
	}
	// Left
	if (col == stack_view(&state->clues.left.max_idx[row]))
	{
		diff = stack_pop(&state->clues.left.max_idx[row]);
		state->clues.left.max_height[row] += diff - 1;
		state->clues.left.min_height[row]--;
	}
	// Right
	if (state->n - col - 1 == stack_view(&state->clues.right.max_idx[row]))
	{
		diff = stack_pop(&state->clues.right.max_idx[row]);
		state->clues.right.max_height[row] += diff - 1;
		state->clues.right.min_height[row]--;
	}
	return (1);
}

int	is_valid_placement(int col, int row, t_game_state *state)
{
	int	result;

	result = 0;
	clue_set(col, row, state);
	if (state->clues.top.max_height[col] >= state->clues.top.target[col]
		&& state->clues.top.min_height[col] <= state->clues.top.target[col]
		&& !(state->clues.top.min_height[col] == state->clues.top.target[col]
			&& stack_view(&state->clues.top.max_idx[col]) != 0))
		result++;
	if (state->clues.bot.max_height[col] >= state->clues.bot.target[col]
		&& state->clues.bot.min_height[col] <= state->clues.bot.target[col]
		&& !(state->clues.bot.min_height[col] == state->clues.bot.target[col]
			&& stack_view(&state->clues.bot.max_idx[col]) != 0))
		result++;
	if (state->clues.left.max_height[row] >= state->clues.left.target[row]
		&& state->clues.left.min_height[row] <= state->clues.left.target[row]
		&& !(state->clues.left.min_height[row] == state->clues.left.target[row]
			&& stack_view(&state->clues.left.max_idx[row]) != 0))
		result++;
	
	if (state->clues.right.max_height[row] >= state->clues.right.target[row]
		&& state->clues.right.min_height[row] <= state->clues.right.target[row]
		&& !(state->clues.right.min_height[row] == state->clues.right.target[row]
			&& stack_view(&state->clues.right.max_idx[row]) != 0))
		result++;
	
	if (result == 4)
		return (1);
	clue_unset(col, row, state);
	return (0);
}

// initalizes all clues
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