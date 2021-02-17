/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:30:50 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/17 15:21:35 by thjacque         ###   ########lyon.fr   */
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
	fd = -1;
	if (root->right)
		fd = create_file(root->cmd->type, prep_cmd(root->right->cmd, 0));
	if (fd == -1)
		return ;
	redirections(root, fd, redirection);
	close(fd);
}
