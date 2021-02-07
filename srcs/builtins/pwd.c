/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 11:36:44 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/06 18:42:06 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void	get_pwd(void)
{
	char	path[10000];

	getcwd(path, 10000);
	ft_printf("%s\n", path);
	get_all_st(NULL)->state = 0;
}
