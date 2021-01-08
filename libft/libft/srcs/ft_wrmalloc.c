/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrmalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:21:21 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/08 16:23:06 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	**wrgetter(void)
{
	static t_list *wrm;

	return (&wrm);
}

void			*wrmalloc(unsigned long size)
{
	char	*buffer;
	t_list	*new_elem;

	if (!(buffer = malloc(size)))
	{
		wrdestroy();
		return (0);
	}
	if (!(new_elem = malloc(sizeof(t_list))))
	{
		free(buffer);
		wrdestroy();
		exit(1);
	}
	new_elem->content = buffer;
	new_elem->next = 0;
	ft_lstadd_back(wrgetter(), new_elem);
	return (buffer);
}

int				wrfree(void *ptr)
{
	t_list	*prev;
	t_list	*current;
	t_list	*next;
	t_list	**wrstart;

	prev = 0;
	wrstart = wrgetter();
	current = *wrstart;
	while (current)
	{
		next = current->next;
		if (current->content == ptr)
		{
			free(ptr);
			free(current);
			if (prev)
				prev->next = next;
			else
				*wrstart = next;
			return (EXIT_SUCCESS);
		}
		prev = current;
		current = current->next;
	}
	return (EXIT_FAILURE);
}

void			wrdestroy(void)
{
	t_list	*current;
	t_list	*next;
	t_list	**wrstart;

	wrstart = wrgetter();
	current = *wrstart;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*wrstart = 0;
}