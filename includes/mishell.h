/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mishell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:12:37 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/12 18:48:39 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISHELL_H
# define MISHELL_H
# define EXIT_SUCCESS 0
# define EXIT_FAILED 1
# define SUCCESS 1
# define FAILED 0
# define MALLOC 2
# define QUIT 3
# define BAD_ENV 4
# include "ft_printf.h"
# include "donut.h"
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <curses.h>
# include <term.h>

typedef struct			s_all
{
	int		state;
}						t_all;

/*
**	STATE 2 ="blabla"
**	STATE 1 =""
**	STATE 0 =
*/
typedef struct			s_env
{
	char			*name;
	char			*value;
	int				state;
	struct s_env	*next;
}						t_env;
void			welcome(char **env);
void			loop(t_env *envp);
/*
**	BUILTINS
*/
int				get_pwd(void);
int				get_env(t_env *envp);
int				change_dir(t_env *env, char **args);
int				export_env(t_env *env, char **args);
int				unset(t_env *env, char **args);
/*
**	ENV LIST
*/
t_env			*init_env(char **env);
t_env			*ft_envnew(char *name, char *value);
void			ft_envadd_back(t_env **alst, t_env *new);
void			ft_envprint_one(t_env *env);
t_env			*env_find(t_env *env, char *name);
void			env_edit_value(t_env *env, char *value);
char			**env_to_tab(t_env *env);
void			env_edit_state(t_env *env, int value);
char			*get_name(char *s);
char			*get_value(char *s);
void			ft_env_remove_if(t_env **begin_list, void *name_ref,
				int (*cmp)());
void			ft_remove_elem(t_env **ptr_back, t_env **ptr);
/*
**
*/
int				handler(char *cmd, t_all *all, t_env *env);
char			**trim_args(char *line, char c);
void			ft_exit(int code);
char			*ft_translate( char *s, t_env *env, t_all *all);

int			main_donut(void);
t_env		*get_env_st(t_env *env);
#endif