/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mishell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:12:37 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/08 18:08:05 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISHELL_H
# define MISHELL_H
# define EXIT_SUCCESS 0
# define EXIT_FAILED 1
# define SUCCESS 1
# define FAILED 0
# define MALLOC 2
# define BAD_ENV 3
# include "ft_printf.h"

typedef struct			s_all
{
	int		state;
}						t_all;
typedef struct			s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}						t_env;
void			welcome(char **env);
/*
**	BUILTINS
*/
int				get_pwd(void);
int				get_env(t_env *envp);
int				change_dir(t_env *env, char **args);
/*
**	ENV LIST
*/
t_env			*init_env(char **env);
t_env			*ft_envnew(char *name, char *value);
void			ft_envadd_back(t_env **alst, t_env *new);
void			ft_envprint_one(t_env *env);
t_env			*env_find(t_env *env, char *name);
void			env_edit_value(t_env *env, char *value);
/*
**
*/
int				handler(char *cmd, t_all *all, t_env *env);
char			**trim_args(char *line, char c);
void			ft_exit(int code);
#endif