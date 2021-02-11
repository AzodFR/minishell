/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:28:50 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 15:34:03 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

int		no_prev(t_type *begin)
{
	t_type *cmd;

	cmd = begin->prev;
	while (cmd)
	{
		if (cmd->type == 0 || cmd->type == 6 || cmd->type == 7)
			return (0);
		else if (cmd->type == 8)
			cmd = cmd->prev;
		else
			return (1);
	}
	return (1);
}

int		no_next(t_type *begin)
{
	t_type *cmd;

	cmd = begin->next;
	while (cmd)
	{
		if (cmd->type == 0 || cmd->type == 6 || cmd->type == 7)
			return (0);
		else if (cmd->type == 8)
			cmd = cmd->next;
		else
			return (1);
	}
	return (1);
}

int		no_cmd(t_type *begin)
{
	return (no_prev(begin) || no_next(begin));
}

t_type	*errornear(char *s)
{
	ft_dprintf(2, "\033[32mMiShell \033[31m✘ \033[0msyntax error near unexpec");
	ft_dprintf(2, "ted token `%s'\n", s);
	return (NULL);
}
