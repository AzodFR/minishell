/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:03:32 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/14 15:28:55 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mishell.h"

int		sep_count(char *s, int *i, char c)
{
	int		j;
	
	j = 0;
	while (s[j])
	{
		if (s[j] == c)
			if (s[j - 1] == '\\')
				j++;
			else
			{
				*i = *i + j + 1;
				return (1);
			}
		else
			j++;
	}
	return (-1);
}

void	init_value(int *cmds, t_all *a)
{
	a->flag_quote = 0;
	a->flag_esc = 0;
	a->flag_cmd = 0;
	*cmds = 1;
}

int		print_error_quote(void)
{
	ft_printf("\033[32mMiShell \033[31m✘ \033[0m");
	ft_printf("You need to close your quotes\n");
	return (-1);
}

int	splitter_counter_cmd(char *s, t_all *a, int i)
{
	char		c;
	int			cmds;

	init_value(&cmds, a);
	while (s[++i])
	{
		if (!a->flag_cmd && (a->flag_cmd = 1))
			while (s[i] == ' ')
				i++;
		if ( i > 0 && s[i - 1] == '\\')
			a->flag_esc = 1;
		if (s[i] == '\\')
			continue ;
		if (!a->flag_esc && (s[i] == '\'' | s[i] == '\"') && (c = s[i]))
		{
			if (sep_count(&s[i + 1], &i, c) < 0)
				if ((a->flag_quote = 1))
					break ;
		}
		else if (!a->flag_esc && (s[i] == ';' && s[i+1]) && (++cmds))
			a->flag_cmd = 0;
		else
			a->flag_esc = 0;
	}	
	if (a->flag_quote)
		return (print_error_quote());
	return (cmds);
}

int	splitter_counter_args(char *s, t_all *a, int *j)
{
	char		c;
	int			i;
	int			count;

	init_value(&count, a);
	i = *j;
	while (s[++i])
	{
		if (!a->flag_cmd && (a->flag_cmd = 1))
			while (s[i] == ' ')
				i++;
		if (i > 0 && s[i - 1] == '\\')
			a->flag_esc = 1;
		if (s[i] == '\\')
			continue ;
		if (!a->flag_esc && (s[i] == '\'' | s[i] == '\"') && (c = s[i]))
		{
			if (sep_count(&s[i + 1], &i, c) < 0)
				if ((a->flag_quote = 1))
					break ;
			++count;	
		}
		if (s[i] == ' ' && count++)
		{
			while (s[++i] == ' ' && s[i])
				;
			--i;
		}
		else if (!a->flag_esc && s[i] == ';' && (*j = i))
			return (count);
		else
			a->flag_esc = 0;
	}	
	if (a->flag_quote)
		return (print_error_quote());
	(*j = i);
	return (count);
}