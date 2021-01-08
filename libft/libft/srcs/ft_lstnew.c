/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 13:18:32 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/08 16:24:58 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void *content)
{
	t_list		*elem;

	if (!(elem = wrmalloc(sizeof(t_list))))
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}
