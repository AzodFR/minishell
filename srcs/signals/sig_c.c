/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedelfos <jedelfos@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:27:31 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 16:17:00 by jedelfos         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void	sig_c(int sig)
{
	get_all_st(NULL)->state = 130;
	ft_printf("\n\033[32mMiShell %s", get_tild());
	(void)sig;
}

void	sig_quit(int sig)
{
	get_all_st(NULL)->state = 131;
	ft_printf("Quit: %d\n\033[32mMiShell %s", sig, get_tild());
	(void)sig;
}
