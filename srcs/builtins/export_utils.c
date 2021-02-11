/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedelfos <jedelfos@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:55:34 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 15:38:52 by jedelfos         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

static void	stop_at_equal(char **teub, int i)
{
	int		j;

	while (teub[++i])
	{
		j = 0;
		while (teub[i][j] != '=' && teub[i][j])
			j++;
		teub[i][j] = 0;
	}
}

static char	*escape(char *s)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (s[++i])
		if (s[i] == '"' || s[i] == '$')
			j++;
	if (!(tmp = wrmalloc((ft_strlen(s) + j + 1) * sizeof(char))))
		ft_exit(MALLOC);
	j = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '"' || s[i] == '$')
			tmp[i + j++] = '\\';
		tmp[i + j] = s[i];
	}
	tmp[i + j] = 0;
	return (tmp);
}

int			print_export(t_env *env)
{
	int		i;
	char	**envlist;
	t_env	*act;

	act = env;
	envlist = env_to_tab(env);
	ft_advanced_sort_string_tab(envlist, &ft_strcmp);
	stop_at_equal(envlist, -1);
	i = -1;
	while (envlist[++i])
	{
		if (envlist[i][0] == '_' && !envlist[i][1])
			continue;
		act = env_find(env, envlist[i]);
		if (act->state == 1)
			ft_printf("declare -x %s=""\n", act->name);
		if (act->state == 2)
			ft_printf("declare -x %s=\"%s\"\n", act->name, escape(act->value));
		else
			ft_printf("declare -x %s\n", act->name);
		act = act->next;
	}
	return (0);
}
