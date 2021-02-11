/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_advanced_sort_tab.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedelfos <jedelfos@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 11:52:39 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 12:24:57 by jedelfos         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap_tab(char **one, char **two)
{
	char *swap;

	swap = *one;
	*one = *two;
	*two = swap;
}

void	ft_advanced_sort_string_tab(char **teub, int (*cmp)(char *, char *))
{
	int		i;
	int		j;

	i = -1;
	while (teub[++i])
	{
		j = 0;
		while (teub[j])
		{
			if ((*cmp)(teub[i], teub[j]) < 0)
				ft_swap_tab(&teub[i], &teub[j]);
			j++;
		}
	}
}
