/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 13:42:35 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/08 16:27:56 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*prev;

	if (!del)
		return ;
	while (*lst)
	{
		del((*lst)->content);
		prev = *lst;
		*lst = (*lst)->next;
		wrfree(prev);
	}
	*lst = NULL;
}
