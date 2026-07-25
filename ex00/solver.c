/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 07:02:40 by lming-ha          #+#    #+#             */
/*   Updated: 2026/07/25 07:02:40 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush_one.h"
#include <unistd.h>

void	print_board(t_game_state *state)
{
	int		i;
	int		j;
	char	digit;

	i = 0;
	while (i < state->n)
	{
		j = 0;
		while (j < state->n)
		{
			digit = (char)(state->board[i][j] + '0');
			write(1, &digit, 1);
			if (++j < state->n)
				write(1, " ", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}

int	is_unique_row(int row, int num, t_game_state *state)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < state->n)
	{
		if (state->board[row][i] == num)
			count++;
		i++;
	}
	return (count == 0);
}

int	solve(int col, int num, t_game_state *state)
{
	int	row;

	if (num == 0)
		return (print_board(state), 1);
	else if (col == state->n)
		return (solve(0, num - 1, state));
	row = 0;
	while (row < state->n)
	{
		if (state->board[row][col] == 0
			&& is_unique_row(row, num, state)
			&& is_valid_placement(col, row, state))
		{
			state->board[row][col] = num;
			if (solve(col + 1, num, state))
				return (1);
			state->board[row][col] = 0;
			clue_unset(col, row, state);
		}
		row++;
	}
	return (0);
}
