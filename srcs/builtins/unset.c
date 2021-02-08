/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:47:47 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/08 16:14:59 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

int			check_identifier(char *s, char *type)
{
	int i;

	i = -1;
	while (s[++i])
		if (s[i] == '.' || s[i] == '\\' || s[i] == '|' || s[i] == '*' ||
		s[i] == '/' || s[i] == '=' || s[i] == '@' || s[i] == '+' || s[i] == '&'
		|| s[i] == '}' || s[i] == '{' || s[i] == ']' || s[i] == '[' || s[i] == '!'
		|| s[i] == '^' || s[i] == '~' || s[i] == '#' || s[i] == '-')
		{
			ft_dprintf(2, "\033[32mMiShell \033[31m✘ \033[0m %s: `%s': not a valid identifier\n", type, s);
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
	{
		if (!ft_strncmp(args[1], "-", 1))
		{
			ft_dprintf(2, "\033[32mMiShell \033[31m✘ \033[0m unset: -%c: invalid option\n", args[1][1]);
			get_all_st(NULL)->state = 2;
		}
		else
			while (args[++i])
				if (check_identifier(args[i], "unset") && !(get_all_st(NULL)->state = 0))
					ft_env_remove_if(&env, args[i], ft_strcmp);
	}
}
