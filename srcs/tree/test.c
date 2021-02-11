/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:16:35 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 16:40:21 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

char	*ft_strfdup(char *s, char *bef)
{
	wrfree(bef);
	return (ft_strdup(s));
}

t_type	*prep_redir(void)
{
	t_type	*redir;

	if (!(redir = wrmalloc(sizeof(t_type))))
		ft_exit(MALLOC);
	redir->prev = NULL;
	redir->next = NULL;
	return (redir);
}

t_type	*prep2(t_type *begin, int found)
{
	t_type	*redir;
	t_type	*tmp;
	t_type	*tmp2;
	t_type	*prev;

	tmp = begin;
	redir = prep_redir();
	while (tmp && tmp->type != 1 && tmp->type != 2)
	{
		if (is_right_redir(tmp) && (found = 1))
		{
			redir->type = tmp->type;
			redir->content = ft_strdup(tmp->content);
			tmp2 = tmp->next;
			while (tmp2->type == 8)
				tmp2 = tmp2->next;
			if (tmp2)
			{
				add_back(&redir, tmp2);
				tmp2->prev->next = tmp2->next;
			}
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp == begin && (tmp->type = 8))
				begin->content = ft_strfdup(" ", begin->content);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	if (found)
	{
		prev->next = redir;
		lastredir(redir)->next = tmp;
	}
	return (tmp ? tmp->next : tmp);
}

void	prep(t_type *begin)
{
	t_type *tmp;

	tmp = begin;
	while (tmp)
		tmp = prep2(tmp, 0);
}
