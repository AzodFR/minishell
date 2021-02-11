/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedelfos <jedelfos@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 11:36:44 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 13:38:42 by jedelfos         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void	get_pwd(void)
{
	char	*path;

	path = ft_strdup(env_find(get_env_st(NULL), "PWD")->value);
	ft_printf("%s\n", path);
	get_all_st(NULL)->state = 0;
}
