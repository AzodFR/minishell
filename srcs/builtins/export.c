/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedelfos <jedelfos@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:55:34 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/11 13:38:26 by jedelfos         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

void		stop_at_equal(char **teub, int i)
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

char		*escape(char *s)
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

static int	check_export_utils(char *s, int i, int *j)
{
	if (!j[0] && (s[i] == '.' || s[i] == '\\' || s[i] == '|' || s[i] == '*' ||
	s[i] == '/' || s[i] == '@' || s[i] == '&' || s[i] == '}' || s[i] == '{' ||
	s[i] == ']' || s[i] == '[' || s[i] == '!' || s[i] == '^' || s[i] == '~' ||
	s[i] == '#' || s[i] == '-' || s[i] == '$'))
	{
		ft_dprintf(2,
"\033[32mMiShell \033[31m✘ \033[0m export: `%s': not a valid identifier\n", s);
		return (0);
	}
	else if ((i == 0 && ft_isdigit(s[i])) ||
	(s[i] == '+' && (!s[i + 1] || (s[i + 1] && s[i + 1] != '='))))
	{
		ft_dprintf(2,
"\033[32mMiShell \033[31m✘ \033[0m export: `%s': not a valid identifier\n", s);
		return (0);
	}
	if (s[i] == '=')
		j[0] = 1;
	return (1);
}

int			check_export(char *s)
{
	int	i;
	int j;

	i = -1;
	j = 0;
	if (!ft_strlen(s) || !ft_strlen(get_name(s)) || isalldigit(get_name(s)))
	{
		ft_dprintf(2,
"\033[32mMiShell \033[31m✘ \033[0m export: `%s': not a valid identifier\n", s);
		return (0);
	}
	while (s[++i])
	{
		if (check_export_utils(s, i, &j) != 1)
			return (0);
	}
	return (1);
}

int			is_cat(char *s)
{
	int i;

	i = -1;
	while (s[++i] && s[i] != '=')
		;
	if (s[i] == '=' && s[i - 1] == '+')
		return (1);
	return (0);
}

int			treat_export(char *arg, t_env *env)
{
	if (!check_export(arg))
		return (1);
	if (!ft_strchr(arg, '=') && !env_find(env, arg))
	{
		ft_envadd_back(&env, ft_envnew(arg, ""));
		env_edit_state(env_find(env, arg), 0);
		return (0);
	}
	else
	{
		if (!env_find(env, get_name(arg)))
			ft_envadd_back(&env, ft_envnew(get_name(arg), get_value(arg)));
		else
			env_edit_value(env_find(env, get_name(arg)), is_cat(arg) ?
				ft_strjoin(env_find(env, get_name(arg))->value,
				get_value(arg)) : get_value(arg));
		if (!ft_strlen(get_value(arg)))
			env_edit_state(env_find(env, get_name(arg)), 1);
		else
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
		if (!ft_strncmp(args[1], "-", 1))
		{
			ft_dprintf(2,
"\033[32mMiShell \033[31m✘ \033[0m export: -%c: invalid option\n", args[1][1]);
			ret = 2;
		}
		else
			ret = treat_export(args[i], env);
	}
	get_all_st(NULL)->state = ret;
}
