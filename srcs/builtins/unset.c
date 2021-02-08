/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:47:47 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/08 15:19:14 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

int			check_identifier(char *s)
{
	int i;

	i = -1;
	while (s[++i])
		if (s[i] == '.' || s[i] == '\\' || s[i] == '|' || s[i] == '*' || s[i] == '/' || s[i] == '=' || s[i] == '@' || s[i] == '+' || s[i] == '&' || s[i] == '}' || s[i] == '{' || s[i] == ']' || s[i] == '[' || s[i] == '!' || s[i] == '^' || s[i] == '~' || s[i] == '#' || s[i] == '-')
		{
			get_all_st(NULL)->state = 1;
			return (0);
		}
	return (1);
}

void		unset(t_env *env, char **args)
{
	int		i;

	i = 0;
	if (args[1])
		while (args[++i])
			if (check_identifier(args[i]) && !(get_all_st(NULL)->state = 0))
				ft_env_remove_if(&env, args[i], ft_strcmp);
}
