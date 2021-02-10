/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 11:36:44 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/10 16:12:51 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void	get_pwd(void)
{
	char	*path;

	//if (!ft_strncmp(env_find(get_env_st(NULL), "PWD")->value, "//", 2))
		path = ft_strdup(env_find(get_env_st(NULL), "PWD")->value);
	/*else
		path = getcwd(NULL, 0);*/
	ft_printf("%s\n", path);
	get_all_st(NULL)->state = 0;
}
