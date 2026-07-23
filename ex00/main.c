#include "rush_one.h"
#include <stdio.h>

int main()
{
	t_game_state state;
	int **board = (int*[]){
		(int[]){1, 3, 2, 4},
		(int[]){4, 2, 3, 1},
		(int[]){3, 4, 1, 2},
		(int[]){2, 1, 4, 3}
	};
	state.board = board;
	
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			printf("%d ", state.board[i][j]);
		}
		printf("\n");
	}
}