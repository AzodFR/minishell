/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 11:36:44 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/12 13:53:41 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void	get_pwd(void)
{
	char	*path;

	path = NULL;
	if (env_find(get_env_st(NULL), "PWD"))
	{
		path = ft_strdup(env_find(get_env_st(NULL), "PWD")->value);
		ft_printf("%s\n", path);
	}
	else
		ft_printf("%s\n", getcwd(NULL, 10000));
	get_all_st(NULL)->state = 0;
}
