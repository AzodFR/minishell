/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 00:05:23 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/06 19:34:54 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void				exec_cmd(t_tree *root)
{
	int	type;

	if (!root)
		return ;
	type = root->cmd->type;
	if (type == 2)
		exec_pipe(root, 1, 0);
	else if (type > 2 && type < 6)
		redirections(root);
	else
		handler(prep_cmd(root->cmd, 0), get_env_st(NULL));
}