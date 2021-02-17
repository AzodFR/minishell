/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:27:31 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/17 12:55:42 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void	sig_c(int sig)
{
	ft_printf("\n");
	if (!get_all_st(NULL)->prog)
	{
		get_all_st(NULL)->state = 1;
		ft_printf("\033[32mMiShell %s", get_tild());
	}
	(void)sig;
}

void	sig_quit(int sig)
{
	if (!get_all_st(NULL)->prog)
		return ;
	ft_printf("Quit: %d\n", sig);
	(void)sig;
}

void	exit_donut(int sig)
{
	if (sig == 3)
		exit(131);
	exit(130);
}
