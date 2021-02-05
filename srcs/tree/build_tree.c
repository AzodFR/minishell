/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:26:24 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/05 23:30:57 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void add_right_node(t_tree **node, t_type **cmd)
{
    t_tree *new;
    
    if (!(new = wrmalloc(sizeof(t_tree))))
        ft_exit(MALLOC);
    while ((*cmd)->type == 1 || (*cmd)->type == 8)
        *cmd = (*cmd)->next;
    new->cmd = *cmd;
    new->right = NULL;
    new->left = NULL;
    ft_printf("add right %s\n", (*cmd)->content);
    (*node)->right = new;
    (*node) = new;
    *cmd = find_next_type(*cmd);
}

void add_left_node(t_tree **node, t_type **cmd, int type)
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
    ft_printf("add left %s in %s\n", (*cmd)->content, (*node)->cmd->content);
    *cmd = (type > 1 && type < 6) ? (*cmd)->next : find_next_type(*cmd);
    if (*cmd)
     add_left_node(&((*node)->left), cmd, (*cmd)->type);
}

void    create_nodes(t_type *begin, t_tree *root)
{
    t_tree *node;
    
    node = root;
    while (begin)
    {
        ft_printf("actual node: %s\n", node->cmd->content);
        if (begin->type > 1 && begin->type < 6)
            add_left_node(&node, &begin, begin->type);
        else
            add_right_node(&node, &begin);
    }
}

void    print_tree(t_tree *root)
{
    t_tree *right;
    t_tree *left;
    t_tree *node;
    
    node = root;
    left = node->left;
    right = node->right;
     ft_printf("\t\t\tnode: %s\n\tleft: %s\t\t\t\tright: %s\n\n", node->cmd->content, !left ? NULL : left->cmd->content, !right ? NULL : right->cmd->content);
   
    while (node)
    {
        
        left = node->left;
        right = node->right;
        while (left)
        {
            ft_printf("\t\t\tnode: %s\n\tleft: %s\t\t\t\tright: %s\n\n", left->cmd->content, left->left ? left->left->cmd->content : NULL, left->right ? left->right->cmd->content : NULL);
            left = left->left;
        }
        ft_printf("go right on %s\n", node->cmd->content);
        if (right)
         ft_printf("\t\t\tnode: %s\n\tleft: %s\t\t\t\tright: %s\n\n", right->cmd->content, right->left ? right->left->cmd->content : NULL, right->right ? right->right->cmd->content : NULL);
        node = right;
    }
}

void    build_tree(t_type *begin, t_tree *root)
{
    ft_printf("start build tree\n");
    root->cmd = begin;
    root->left = NULL;
    root->right = NULL;
    begin = find_next_type(begin);
    create_nodes(begin, root);
    ft_printf("tree builded \n\n\n");
    print_tree(root);
}