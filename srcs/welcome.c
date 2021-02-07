/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:10:18 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/06 19:17:09 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void	welcome2(void)
{
	ft_printf("\033[36m     ,8'8.`8888,8^8.`8888.       8 8888\033[33m   `8.`");
	ft_printf("8888.    8 8888        8 8 888888888888 8 8888         8 8888 ");
	ft_printf("        \n");
	ft_printf("\033[36m    ,8' `8.`8888' `8.`8888.      8 8888\033[33m    `8.");
	ft_printf("`8888.   8 8888        8 8 8888         8 8888         8 8888 ");
	ft_printf("        \n");
	ft_printf("\033[36m   ,8'   `8.`88'   `8.`8888.     8 8888\033[33m     `8");
	ft_printf(".`8888.  8 8888888888888 8 8888         8 8888         8 8888 ");
	ft_printf("        \n");
	ft_printf("\033[36m  ,8'     `8.`'     `8.`8888.    8 8888\033[33m 8b   `");
	ft_printf("8.`8888. 8 8888        8 8 8888         8 8888         8 8888 ");
	ft_printf("        \n");
	ft_printf("\033[36m ,8'       `8        `8.`8888.   8 8888\033[33m `8b.  ");
	ft_printf(";8.`8888 8 8888        8 8 8888         8 8888         8 8888 ");
	ft_printf("        \n");
	ft_printf("\033[36m,8'         `         `8.`8888.  8 8888\033[33m  `Y888");
	ft_printf("8P ,88P' 8 8888        8 8 888888888888 8 888888888888 8 88888");
	ft_printf("8888888 \033[0m\n\n\n\n\n\n\n\n\n\n");
}

void	welc_msg(void)
{
	ft_printf("\033[36m          .         .                  \033[33m\n");
	ft_printf("\033[36m         ,8.       ,8.           8 8888\033[33m    d88");
	ft_printf("8888o.   8 8888        8 8 8888888888   8 8888         8 8888 ");
	ft_printf("        \n");
	ft_printf("\033[36m        ,888.     ,888.          8 8888\033[33m  .`888");
	ft_printf("8:' `88. 8 8888        8 8 8888         8 8888         8 8888 ");
	ft_printf("        \n");
	ft_printf("\033[36m       .`8888.   .`8888.         8 8888\033[33m  8.`88");
	ft_printf("88.   Y8 8 8888        8 8 8888         8 8888         8 8888 ");
	ft_printf("        \n");
	ft_printf("\033[36m      ,8.`8888. ,8.`8888.        8 8888\033[33m  `8.`8");
	ft_printf("888.     8 8888        8 8 8888         8 8888         8 8888 ");
	ft_printf("        \n");
	welcome2();
}

void	welcome(char **env)
{
	pid_t		prog;
	char		*teub[2];
	char		**tuub;
	
	teub[0] = NULL;
	if (!(prog = fork()))
		execve("/usr/bin/clear", teub, env);
	wait(&prog);
	tuub = ft_split("stty -echoctl", ' ');
	if (!(prog = fork()))
		execve("/bin/stty", tuub, env);
	wait(&prog);
	welc_msg();
}
