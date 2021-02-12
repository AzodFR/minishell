/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:26:24 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/12 13:36:08 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void	insert_tree(t_tree **root, t_type *cmd)
{
	t_tree	*node;

	node = NULL;
	if (!(*root))
		init_node(root, cmd);
	else if (cmd->type > 1 && cmd->type < 6)
	{
		init_node(&node, cmd);
		node->left = *root;
		*root = node;
	}
	else if (cmd->type == 8)
		return ;
	else
		insert_tree(&(*root)->right, cmd);
}

void	create_tree(t_type *cmd, t_tree **tree)
{
	t_type *redir;
	t_type *back;

	redir = NULL;
	back = NULL;
	while (cmd && cmd->type != 1)
	{
		if (cmd->type > 1 && cmd->type < 6)
		{
			insert_tree(tree, cmd);
			cmd = cmd->next;
		}
		else if (cmd->type == 8)
			cmd = cmd->next;
		else
		{
			insert_tree(tree, cmd);
			cmd = find_next_type(cmd);
		}
	}
}

int		check_left(t_tree **left)
{
	char **cmd;

	if ((*left)->cmd->type < 3 || (*left)->cmd->type > 5)
	{
		if ((*left)->right && (*left)->right->cmd->type == 0 &&
		!check_cmd(get_env_st(NULL), prep_cmd((*left)->right->cmd, 0), 0))
		{
			cmd = prep_cmd((*left)->right->cmd, 0);
			end_ling(get_all_st(NULL)->state, cmd[0]);
			return (0);
		}
	}
	(*left) = (*left)->left;
	return (1);
}

int		check_all(t_tree *root)
{
	t_tree	*right;
	t_tree	*left;
	t_tree	*node;

	node = root;
	left = node->left;
	right = node->right;
	while (node)
	{
		left = node->left;
		if (node->cmd->type > 2 && node->cmd->type < 6)
			right = NULL;
		else
			right = node->right;
		while (left)
			check_left(&left);
		if (right && right->cmd->type == 0 && !check_cmd(get_env_st(NULL),
		prep_cmd(right->cmd, 0), 0))
			return (not_good_right(right));
		node = right;
	}
	return (1);
}

void	build_tree(t_type *begin)
{
	t_tree	*root;

	root = NULL;
	prep(begin);
	get_all_st(NULL)->prog = 1;
	while (begin)
	{
		translate_only(begin);
		create_tree(begin, &root);
		if (check_all(root))
			exec_cmd(root);
		wrfree(root);
		root = NULL;
		get_fd_back(get_all_st(NULL)->fd);
		check_exit();
		if (get_all_st(NULL)->exit == -1)
		{
			get_all_st(NULL)->exit = 0;
			return ;
		}
		while (begin && begin->type != 1)
			if (!go_next_begin(&begin))
				break ;
	}
}
