/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 16:15:05 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 11:55:39 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void cmd_exit(char **args)
{
    long long i;
    i = -1;
    while (args[++i])
        ;
    if (i > 2)
    {
        if (isalldigit(args[1]))
        {
            get_all_st(NULL)->exit = -1;
            get_all_st(NULL)->state = 1;
            ft_dprintf(2,"\033[32mMiShell \033[31m✘ \033[0m");
            ft_dprintf(2,"exit: too many arguments\n");
            return ;
        }
    }
    get_all_st(NULL)->exit = 1;
    if (i == 1)
        get_all_st(NULL)->state = 0;
    else
    {
        i = ft_atoll(args[1]);
        if (!isalldigit(args[1]))
            get_all_st(NULL)->state = 255;
        else if (i > 255)
            get_all_st(NULL)->state = i % 256;
        else if (i < -255 && i % 256 == 0)
         get_all_st(NULL)->state = 255;
        else
            get_all_st(NULL)->state = i;
    }
    return ;
}