/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:16:35 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/17 16:08:14 by thjacque         ###   ########lyon.fr   */
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
	redir->type = 0;
	return (redir);
}

int		prep3(t_type **redir, t_type **tmp, t_type **prev, t_type *begin)
{
	t_type	*tmp2;
	int		found;

	found = 0;
	if (is_right_redir(*tmp) && (found = 1))
	{
		if (!(*redir)->type)
			(*redir)->type = (*tmp)->type;
		(*redir)->content = ft_strdup((*tmp)->content);
		tmp2 = (*tmp)->next;
		(*tmp)->type = 8;
		while (tmp2->type == 8)
			tmp2 = tmp2->next;
		if (tmp2 && add_back(redir, tmp2))
			tmp2->prev->next = tmp2->next;
		if ((*tmp)->prev)
			(*tmp)->prev->next = (*tmp)->next;
		if ((*tmp) == begin && ((*tmp)->type = 8))
			begin->content = ft_strfdup(" ", begin->content);
	}
	check_left_redir(tmp);
	(*prev) = (*tmp);
	(*tmp) = (*tmp)->next;
	return (found);
}

t_type	*prep2(t_type *begin, int found)
{
	t_type	*redir;
	t_type	*tmp;
	t_type	*prev;

	tmp = begin;
	redir = prep_redir();
	while (tmp && tmp->type != 1 && tmp->type != 2)
		if (prep3(&redir, &tmp, &prev, begin))
			found = 1;
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
	while (tmp && !(get_all_st(NULL)->flag_quote = 0))
		tmp = prep2(tmp, 0);
}
