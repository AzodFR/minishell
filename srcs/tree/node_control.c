/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 11:04:31 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 11:08:15 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

static void		add_right_node(t_tree **node, t_type **cmd)
{
	t_tree *new;

	if (!(new = wrmalloc(sizeof(t_tree))))
		ft_exit(MALLOC);
	while ((*cmd)->type == 1 || (*cmd)->type == 8)
		*cmd = (*cmd)->next;
	new->cmd = *cmd;
	new->right = NULL;
	new->left = NULL;
	(*node)->right = new;
	(*node) = new;
	*cmd = find_next_type(*cmd);
}

static void		add_left_node(t_tree **node, t_type **cmd, int type)
{
	t_tree *new;

	if (!(*cmd) || !cmd || type == 1)
		return ;
	if (!(new = wrmalloc(sizeof(t_tree))))
		ft_exit(MALLOC);
	while (type == 8)
	{
		*cmd = (*cmd)->next;
		type = (*cmd)->type;
	}
	new->cmd = *cmd;
	new->right = NULL;
	new->left = NULL;
	(*node)->left = new;
	*cmd = (type > 1 && type < 6) ? (*cmd)->next : find_next_type(*cmd);
	if (*cmd)
		add_left_node(&((*node)->left), cmd, (*cmd)->type);
}

void			create_nodes(t_type *begin, t_tree *root)
{
	t_tree *node;

	node = root;
	while (begin)
	{
		if (begin->type > 1 && begin->type < 6)
			add_left_node(&node, &begin, begin->type);
		else
			add_right_node(&node, &begin);
	}
}

void			init_node(t_tree **node, t_type *cmd)
{
	t_tree	*newnode;

	if (!(newnode = wrmalloc(sizeof(t_tree))))
		ft_exit(MALLOC);
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->cmd = cmd;
	*node = newnode;
}
