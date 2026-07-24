/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madinata <madinata@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 13:15:44 by madinata          #+#    #+#             */
/*   Updated: 2026/07/24 13:16:01 by madinata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Create a 1d or 2d int arrays and initalize with zeros
#include <stdlib.h>

int	*create_arr(int size, int init_num)
{
	int	i;
	int	*ptr;

	ptr = malloc(size * sizeof(int));
	i = 0;
	while (i < size)
		ptr[i++] = init_num;
	return (ptr);
}

int	**create_arr2d(int size_y, int size_x)
{
	int	i;
	int	*flat;
	int	**ptr;

	i = 0;
	flat = malloc(size_x * size_y * sizeof(int));
	ptr = malloc(size_y * sizeof(int *));
	while (i < size_x * size_y)
		flat[i++] = 0;
	i = 0;
	while (i < size_y)
	{
		ptr[i] = flat + (i * size_x);
		i++;
	}
	return (ptr);
}
