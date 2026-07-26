/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 17:25:47 by lming-ha          #+#    #+#             */
/*   Updated: 2026/07/24 17:25:47 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush_one.h"
#include <unistd.h>

void	set_clues(int *values, t_clues *clues, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		clues->top.target[i] = values[i];
		clues->bot.target[i] = values[i + n];
		clues->left.target[i] = values[i + 2 * n];
		clues->right.target[i] = values[i + 3 * n];
		i++;
	}
}

int	parse_input(char *input, int *values, int *n)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (count >= 36 || input[i] < '1' || input[i] > '9')
			return (0);
		values[count++] = input[i++] - '0';
		if (!input[i])
			break ;
		if (input[i++] != ' ' || !input[i])
			return (0);
	}
	*n = count / 4;
	if (count % 4 != 0 || *n < 1 || *n > 9)
		return (0);
	i = 0;
	while (i < count)
	{
		if (values[i++] > *n)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_game_state	state;
	int				values[36];
	int				valid;

	state = (t_game_state){0};
	valid = (argc == 2 && argv[1][0] && parse_input(argv[1], values, &state.n));
	if (valid)
	{
		state.board = create_arr2d(state.n, state.n);
		valid = (state.board && initialize_clues(&state.clues, state.n));
	}
	if (valid)
	{
		set_clues(values, &state.clues, state.n);
		valid = solve(0, state.n, &state);
	}
	if (!valid)
		write(2, "Error\n", 6);
	free_clues(&state.clues, state.n);
	free_board(state.board);
	return (!valid);
}
