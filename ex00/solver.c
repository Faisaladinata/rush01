#include "rush_one.h"

#include <stdio.h>

void print_board(t_game_state *state)
{
    for (int i = 0; i < state->n; i++){
		for (int j = 0; j < state->n; j++){
			printf("%d ", state->board[i][j]);
		}
		printf("\n");
	}
}

int is_unique_row(int row, int num, t_game_state *state){
    int count = 0;
    int i = 0;

    while (i < state->n){
        if (state->board[row][i] == num)
            count++;
        i++;
    }
    return (count == 0);
}

int solve(int col, int num, t_game_state *state){
    if (num == 0)
    {
        print_board(state);
        return (1);
    }
    else if (col == state->n)
        return (solve(0, num - 1, state));

    for (int row = 0; row < state->n; row++)
    {
        if (state->board[row][col] == 0 && is_unique_row(row, num, state) && is_valid_placement(col, row, state))
        {
            state->board[row][col] = num;
            if (solve(col + 1, num, state))
                return (1);
            state->board[row][col] = 0;
            clue_unset(col, row, state);
        }
    }

    return (0);
}
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

int main(){
    t_game_state state;
    state.n = 9;
    state.board = create_arr2d(state.n, state.n);
    initialize_clues(&state.clues, state.n);
    
    temp_clues_target(&state.clues, state.n);
    solve(0, state.n, &state);
}
