/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedelfos <jedelfos@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:30:50 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 15:51:22 by jedelfos         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

static void			redirections(t_tree *root, int fd, int redirection)
{
	dup2(fd, redirection);
	close(fd);
	exec_cmd(root->left);
}

void				exec_redir(t_tree *root)
{
	int		fd;
	int		redirection;

	redirection = ft_atoi(root->cmd->content);
	if (!redirection)
		redirection = 1;
	if (root->cmd->type == 4)
		redirection = 0;
	fd = create_file(root->cmd->type, prep_cmd(root->right->cmd, 0));
	if (fd == -1)
		return ;
	redirections(root, fd, redirection);
}
