/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:26:24 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 16:57:47 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"


void	insert_tree(t_tree **root, t_type *cmd)
{
	t_tree  *node;

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

void create_tree(t_type *cmd, t_tree **tree)
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


int check_all(t_tree *root)
{
	t_tree *right;
	t_tree *left;
	t_tree *node;
	char **cmd;
	
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
		{
			if (left->cmd->type < 3 || left->cmd->type > 5)
			{
				if (left->right && left->right->cmd->type == 0 && !check_cmd(get_env_st(NULL), prep_cmd(left->right->cmd, 0), 0))
				{
					cmd = prep_cmd(left->right->cmd, 0);
					end_ling(get_all_st(NULL)->state, cmd[0]);
					return (0);
				}
			}
			left = left->left;
		}
		if (right && right->cmd->type == 0 && !check_cmd(get_env_st(NULL), prep_cmd(right->cmd, 0), 0))
		{
			cmd = prep_cmd(right->cmd, 0);
			end_ling(get_all_st(NULL)->state, cmd[0]);
			return (0);
		}
		node = right;
	}
	return (1);
}

void get_fd_back(int fd[3])
{
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	dup2(fd[2], 2);
}

void    build_tree(t_type *begin)
{
	t_tree *root;
	root = NULL;
	int state;

	prep(begin);
	while (begin)
	{
		translate_only(begin);
		create_tree(begin, &root);
		if (check_all(root))
			exec_cmd(root);
		wrfree(root);
		root = NULL;
		get_fd_back(get_all_st(NULL)->fd);
		if (get_all_st(NULL)->exit == 1)
		{
			state = get_all_st(NULL)->state;
			wrdestroy();
			exit(state);
		}
		else if (get_all_st(NULL)->exit == -1)
		{
			get_all_st(NULL)->exit = 0;
			return ;
		}
		while (begin && begin->type != 1)
		{
			begin = find_next_type(begin);
			if (begin && begin->type == 1)
			{
				begin = begin->next;
				break ;
			}
			else if (begin)
				begin = begin->next;
		}
	}
}
