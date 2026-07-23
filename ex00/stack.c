#include "rush_one.h"
#include <stdlib.h>

#include <stdio.h>
t_index_stack *stack_create(int n)
{
	t_index_stack	*new_arr;
	int				i;

	new_arr = malloc(n * sizeof(t_index_stack));
	i = 0;
	while (i < n)
	{
		new_arr[i].top = 0;
		new_arr[i].stack = create_arr(n, -1);
		i++;
	}
	return (new_arr);
}

void	stack_free(t_index_stack *stack, int n)
{
	int	i;

	i = 0;
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