/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:26:24 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/10 14:35:30 by thjacque         ###   ########lyon.fr   */
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
    //ft_printf("add right %s\n", (*cmd)->content);
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
   // ft_printf("add left %s in %s\n", (*cmd)->content, (*node)->cmd->content);
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
        //ft_printf("actual node: %s\n", node->cmd->content);
        if (begin->type > 1 && begin->type < 6)
            add_left_node(&node, &begin, begin->type);
        else
            add_right_node(&node, &begin);
    }
}

void    show(char **cmd)
{
    int i;
     i = -1;
     while (cmd[++i])
			ft_printf("for cmd: |%s| -> |%s|\n", cmd[0], cmd[i]);
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
        show(prep_cmd(node->cmd, 0));
       
        left = node->left;
        right = node->right;
        while (left)
        {
            show(prep_cmd(left->cmd, 0));
            if (left->right)
            show(prep_cmd(left->right->cmd, 0));
            ft_printf("\t\t\tnode: %s\n\tleft: %s\t\t\t\tright: %s\n\n", left->cmd->content, left->left ? left->left->cmd->content : NULL, left->right ? left->right->cmd->content : NULL);
            left = left->left;
        }
        ft_printf("go right on %s\n", node->cmd->content);
        if (right)
         ft_printf("\t\t\tnode: %s\n\tleft: %s\t\t\t\tright: %s\n\n", right->cmd->content, right->left ? right->left->cmd->content : NULL, right->right ? right->right->cmd->content : NULL);
        node = right;
    }
}

void        init_node(t_tree **node, t_type *cmd)
{
	t_tree	*newnode;

	if (!(newnode = wrmalloc(sizeof(t_tree))))
		ft_exit(MALLOC);
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->cmd = cmd;
    *node = newnode;
}

void        insert_tree(t_tree **root, t_type *cmd)
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

t_type *type_space(t_type *prec)
{
    t_type *new;
    
    if (!(new = wrmalloc(sizeof(t_type))))
        ft_exit(MALLOC);
    new->content = ft_strdup(" ");
    new->next = NULL;
    new->prev = prec;
    new->type = 8;
    return (new);
}

void    tmp_redir(t_type **red, t_type **cmd)
{
    t_type *fd;
    t_type *next;

    if (!(*red))
    {
        if (!(*red = wrmalloc(sizeof(t_type))))
        ft_exit(MALLOC);
        (*red)->next = NULL;
        (*red)->type = (*cmd)->type;
    }
    (*red)->content = ft_strdup((*cmd)->content);
    fd = (*cmd)->next;
    while (fd->type == 8)
        fd = fd->next;
    next = (*red);
    while (next->next)
        next = next->next;
    if (!(next->next = wrmalloc(sizeof(t_type))))
        ft_exit(MALLOC);
    next->next->content = ft_strdup(fd->content);
    next->next->next = type_space(next->next);
    next->next->type = 0;
    (*cmd) = fd;
}

t_type	*destroy_t_type(t_type *type)
{
	t_type *save_prev;
	t_type *save_next;

	save_prev = type->prev;
	save_next = type->next;
	wrfree(type->content);
	wrfree(type);
	if (save_next != NULL)
		save_next->prev = save_prev;
	if (save_prev != NULL)
	{
		save_prev->next = save_next;
		return (save_prev);
	}
	return (save_next);
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
        //    while (cmd && cmd->type == 8)
        //       cmd = cmd->next;
        //    if (cmd && (cmd->type == 0 ||cmd->type == 6 || cmd->type == 7))
        //       cmd = cmd->next;
        //     while (cmd && cmd->type == 8)
        //        cmd = cmd->next;
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

t_type      *moov_t_type(t_type *moov, t_type *dest)
{

   // printf("%s\n", moov->content);
    t_type  *dest_next;
    moov->prev->next = moov->next;
    moov->next->prev = moov->prev;
    dest_next = dest->next;
    dest->next = moov;
	if (dest_next)
	    dest_next->prev = moov;
    moov->next = dest_next;
    moov->prev = dest;
    return (moov);
}

int		add_space(t_type *begin, t_type *prev)
{
	t_type	*temp;

    temp = wrmalloc(sizeof(t_type));
	temp->content = wrmalloc(2);
	temp->content[0] = ' ';
	temp->content[1] = 0;
	temp->type = 8;
	temp->next = NULL;
    prev = NULL;
    if (prev)
    {
        begin = prev;
        if (prev->next)
        {
            prev = prev->next;
            prev->prev = temp;
            temp->next = prev;
        }
    }
    else
    {
    	while (begin && begin->next)
        	begin = begin->next;
    }
	begin->next = temp;
	temp->prev = begin;
	return (0);
}



t_type    *post_tree(t_type *begin)
{
	t_type *last;
	t_type *temp;
	t_type *temp2;
    temp = begin;
    int i;
	add_space(begin, NULL);

    while (begin && begin->next)
	{
		last = NULL;
		temp = begin;
		i = 0;
		while (temp->next)
		{
			if (temp->type == 5 || temp->type == 3)
				i++;
			temp = temp->next;
		}
        printf("i = %i\n", i);

		temp = begin;
		while(i > 0)
		{
			temp = begin;
			while(temp->next && temp->type != 3 && temp->type != 5)
				temp = temp->next;
			if (temp->type == 3 || temp->type == 5)
			{
                add_space(temp->next, temp);
				last = temp;
				while(last->next && last->next->type  != 1 && last->next->type != 2)
					last = last->next;
				temp2 = temp->next;
				last = moov_t_type(temp, last);
                if (temp2->type != 8)
				    last = moov_t_type(temp2, last);
            	else
				    last = moov_t_type(temp2->next, last);
                
			}
    		i--;
            temp2 = last;
            if (i == 0)
		    {
               while(temp2->prev && temp2->type != 5 && temp2->type != 3 && temp2 != begin)
                   temp2 = temp2->prev;
               if (temp2->type == 3 || temp2->type == 5)
                   temp = temp2;
                
                
               while(temp2 != begin)
               {
                   temp2 = temp2->prev;
                   if (temp2->type == 3 || temp2->type == 5)
                   {
                        wrfree(temp2->content);
                        temp2->content = ft_strdup(temp->content);
                        temp2->type = temp->type;
                        destroy_t_type(temp);
                        temp = temp2;
                        printf("je suis sur %s\n", temp->content);
                   }   
               }
            }
        }
		begin = last;
		while (begin != NULL && begin->next != NULL && begin->next->type != 5 && begin->next->type != 3)
			begin = begin->next;

        

//emp2 = temp2- > prev ;


	}
	return (NULL);
}

void    build_tree(t_type *begin)
{
    t_tree *root;
    root = NULL;

   // t_type *temp;


   // temp = begin;
//printf("\n\n\n\n");
prep(begin);
 /*   temp = begin;
   while(temp)
    {
        printf("%i     %s\n", temp->type, temp->content);
        temp = temp->next;
    }
printf("\n\n\n\n");*/

//printf("\n\n\n\n");
   
//printf("\n\n\n\n");



  //  temp = begin;




  /*  temp = begin;
    while(temp)
    {
        printf("%i     %s\n", temp->type, temp->content);
            if (temp->type == 5)
                add_space(temp, temp->prev);
        temp = temp->next;
    }
printf("\n\n\n\n");*/



    while (begin)
    {
        translate_only(begin);
        create_tree(begin, &root);
       //print_tree(root);
       if (check_all(root))
          exec_cmd(root);
        wrfree(root);
        root = NULL;
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