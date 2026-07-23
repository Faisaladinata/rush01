#include "rush_one.h"
#include <stdlib.h>

#include <stdio.h>

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

	return (1);
}

// Reverses clue in coordinate, restoring old one. Returns 1 on succes or 0 on failure.
int clue_unset(int col, int row, t_game_state *state)
{
	int	diff;
	// Top
	diff = stack_pop(&state->clues.top.max_idx[col]);
	printf("diff: %d\n", diff);
	state->clues.top.max_height[col] += diff - 1;
	state->clues.top.min_height[col]--;
	(void) row;
	return (1);
}

int	is_valid_placement(int col, int row, t_game_state *state)
{
	clue_set(col, row, state);
	if(state->clues.top.max_height[col] >= state->clues.top.target[col]
		&& state->clues.top.min_height[col] <= state->clues.top.target[col])
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

// DELETE ME
void	temp_clues_target(t_clues *clues, int n)
{
	int *top = (int[]){4, 3, 2, 1};
	int *bot = (int[]){1, 2, 2, 2};
	int *left = (int[]){4, 3, 2, 1};
	int *right = (int[]){1, 2, 2, 2};

	for (int i = 0; i < n; i++)
		clues->top.target[i] = top[i];
	for (int i = 0; i < n; i++)
		clues->bot.target[i] = bot[i];
	for (int i = 0; i < n; i++)
		clues->left.target[i] = left[i];
	for (int i = 0; i < n; i++)
		clues->right.target[i] = right[i];
}

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

	printf("out: %d\n", is_valid_placement(2, 3, &state));
	printf("cl %d %d\n", state.clues.top.min_height[2], state.clues.top.max_height[2]);
	printf("out: %d\n", is_valid_placement(2, 2, &state));
	printf("cl %d %d\n", state.clues.top.min_height[2], state.clues.top.max_height[2]);
	printf("out: %d\n", is_valid_placement(2, 1, &state));
	printf("cl %d %d\n", state.clues.top.min_height[2], state.clues.top.max_height[2]);
	//printf("%d\n", is_valid_placement(1, 2, &state));
	//printf("%d\n", is_valid_placement(1, 1, &state));
	//printf("%d\n", is_valid_placement(0, 1, &state));
	/*
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			printf("%d ", state.board[i][j]);
		}
		printf("\n");
	}
	*/
}