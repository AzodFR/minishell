/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:27:31 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/06 18:39:25 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void	sig_c(int sig)
{
	get_all_st(NULL)->state = 130;
	ft_printf("\n\033[32mMiShell %s", get_tild());
	(void)sig;
}