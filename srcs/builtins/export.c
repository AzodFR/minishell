/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:55:34 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/06 18:25:48 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void	stop_at_equal(char **teub, int i)
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

char	*escape(char *s)
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

int		print_export(t_env *env)
{
	int		i;
	char	c;
	char	q;
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
		c = act->state ? '=' : 0;
		q = act->state ? '"' : 0;
		ft_printf("declare -x %s%c%c%s%c\n", act->name, c, q,
		escape(act->value), q);
		act = act->next;
	}
	return (0);
}

int		treat_export(char *arg, t_env *env)
{
	if (!ft_strchr(arg, '=') && !env_find(env, arg))
	{
		ft_envadd_back(&env, ft_envnew(arg, ""));
		env_edit_state(env_find(env, arg), 0);
		return (0);
	}
	else if (!ft_strchr(arg, '"') || !ft_strchr(arg, '\''))
	{
		if (!env_find(env, get_name(arg)))
			ft_envadd_back(&env, ft_envnew(get_name(arg), get_value(arg)));
		else
			env_edit_value(env_find(env, get_name(arg)), get_value(arg));
		env_edit_state(env_find(env, get_name(arg)), 2);
		return (0);
	}
	return (1);
}

void		export_env(t_env *env, char **args)
{
	int		i;
	int		ret;

	if (!args[1] && !print_export(env) && get_all_st(NULL)->state == 0)
		return ;
	i = 0;
	ret = 1;
	while (args[++i])
	{
		if (args[i][0] == '=' && !(ret = 0))
		{
			ft_dprintf(2, "\033[32mMiShell \033[31m✘ \033[0m");
			ft_dprintf(2, "export: `%s`: not a valid identifier\n", args[i]);
		}
		else
			ret = treat_export(args[i], env);
	}
	get_all_st(NULL)->state = ret;
}
