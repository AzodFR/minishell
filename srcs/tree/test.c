/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:16:35 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/10 14:23:17 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

int is_right_redir(t_type *tmp)
{
    return (tmp->type == 3 || tmp->type == 5);
}

t_type *add_space_t(t_type *prev)
{
    t_type *space;
    
    if (!(space = wrmalloc(sizeof(t_type))))
        ft_exit(MALLOC);
    space->prev = prev;
    space->next = NULL;
    space->type = 8;
    space->content = ft_strdup(" ");
    return (space);
}

t_type *add_file(t_type *prev, t_type *toadd)
{
    t_type *file;
    
    if (!(file = wrmalloc(sizeof(t_type))))
        ft_exit(MALLOC);
    file->prev = prev;
    file->next = NULL;
    file->type = toadd->type;
    file->content = ft_strdup(toadd->content);
    return (file);
}


void add_back(t_type **redir, t_type *toadd)
{
    t_type *begin;
    int    i;
    
    begin = *redir;
    i = 1;
    while (begin->next)
        begin = begin->next;
    begin->next = add_space_t(begin);
    begin = begin->next;
    begin->next = add_file(begin, toadd);
}

t_type *lastredir(t_type *redir)
{
    t_type *tmp;

    tmp = redir;
    while (tmp->next)
        tmp = tmp->next;
    return (tmp);
}

char    *ft_strfdup(char *s, char *bef)
{
    wrfree(bef);
    return (ft_strdup(s));
}

t_type *prep2(t_type *begin)
{
    t_type *redir;
    t_type *tmp;
    t_type *tmp2;
    t_type *prev;
    int     found;

    tmp = begin;
    if (!(redir = wrmalloc(sizeof(t_type))))
        ft_exit(MALLOC);
    redir->prev = NULL;
    redir->next = NULL;
    found = 0;
    while (tmp && tmp->type != 1 && tmp->type != 2)
    {
        if (is_right_redir(tmp))
        {
            found = 1;
            redir->type = tmp->type;
            redir->content = ft_strdup(tmp->content);
            tmp2 = tmp->next;
            while (tmp2->type == 8)
                tmp2 = tmp2->next;
            if (tmp2)
            {
                add_back(&redir, tmp2);
                tmp2->prev->next = tmp2->next;
            }
            if (tmp->prev)
                tmp->prev->next = tmp->next;
            if (tmp == begin && (tmp->type = 8))
                begin->content = ft_strfdup(" ", begin->content);
        }
        prev = tmp;
        tmp = tmp->next;  
    }
    if (found)
    {
        prev->next = redir;
        lastredir(redir)->next = tmp;
    }
    return (tmp ? tmp->next : tmp);
}

void prep(t_type *begin)
{
    t_type *tmp;

    tmp = begin;
    while (tmp)
        tmp = prep2(tmp);
}