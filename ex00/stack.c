/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madinata <madinata@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 13:16:17 by madinata          #+#    #+#             */
/*   Updated: 2026/07/24 13:16:33 by madinata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush_one.h"
#include <stdlib.h>

t_index_stack	*stack_create(int n)
{
	t_index_stack	*new_arr;
	int				i;

	new_arr = malloc(n * sizeof(t_index_stack));
	if (!new_arr)
		return (0);
	i = 0;
	while (i < n)
	{
		new_arr[i].top = 0;
		new_arr[i].stack = create_arr(n, -1);
		if (!new_arr[i].stack)
		{
			stack_free(new_arr, i);
			return (0);
		}
		i++;
	}
	return (new_arr);
}

void	stack_free(t_index_stack *stack, int n)
{
	int	i;

	i = 0;
	if (!stack)
		return ;
	while (i < n)
		free(stack[i++].stack);
	free(stack);
}

// returns the difference between the last number and current one
int	stack_push(t_index_stack *stack, int num)
{
	int	difference;

	difference = 1;
	if (stack->stack[stack->top] != -1)
	{
		difference = stack->stack[stack->top] - num;
		stack->top++;
	}
	stack->stack[stack->top] = num;
	return (difference);
}

// returns the difference between current number and previous one
int	stack_pop(t_index_stack *stack)
{
	int	last;
	int	difference;

	last = stack->stack[stack->top];
	stack->stack[stack->top] = -1;
	difference = 1;
	if (stack->top > 0)
	{
		stack->top--;
		difference = stack->stack[stack->top] - last;
	}
	return (difference);
}

int	stack_view(t_index_stack *stack)
{
	return (stack->stack[stack->top]);
}
