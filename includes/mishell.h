/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mishell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:12:37 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/08 09:34:44 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#ifndef MISHELL_H
# define MISHELL_H
# define EXIT_SUCCESS 0
# define EXIT_FAILED 1
# define SUCCESS 0
# define FAILED 1
# define MALLOC 2
# define QUIT 3
# define BAD_ENV 4
# define QUOTE 5
# include "ft_printf.h"
# include "donut.h"
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <curses.h>
# include <term.h>
# include <unistd.h>
# include <fcntl.h>

int g_ret;
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

/*
**	TYPE 7 = "blabla"
**	TYPE 6 = 'blabla'
**	TYPE 5 = >>
**	TYPE 4 = <
**	TYPE 3 = >
**	TYPE 2 = |
**	TYPE 1 = ;
**	TYPE 0 = blabla
*/
typedef struct			s_type
{
	char			type;
	char			*content;
	struct s_type	*next;
	struct s_type	*prev;
}						t_type;
typedef struct s_tree
{
	t_type	*cmd;
	struct s_tree *right;
	struct s_tree *left;
}				t_tree;

typedef struct			s_all
{
	int		state;
	int		flag_quote;
	int		flag_cmd;
	int		flag_esc;
	int		fd[3];
	t_tree	*last_node;
}						t_all;
void			welcome(char **env);
void			loop(int fd);
/*
**	BUILTINS
*/
void				get_pwd(void);
void				get_env(t_env *envp);
void			change_dir(t_env *env, char **args);
void				export_env(t_env *env, char **args);
void				unset(t_env *env, char **args);
void				do_echo(char **args);
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
int				handler(char **cmd, t_env *env);
char			**trim_args(char *line, char c);
void			ft_exit(int code);
char			*ft_translate( char *s, t_env *env, t_all *all, int i);
int				splitter_counter_cmd(char *s, t_all *a, int i);
int				splitter_counter_args(char *s, t_all *a, int *j);
t_type *prepare_array(char *line);
char			*backavoid(char *s);
char			*recreate(char *s, int *i, char *r, int j);
t_all			*get_all_st(t_all *all);

char		*stran(char *s, int *i, t_all *all, char *string);
char		*add_one(char *s, char c);

int			main_donut(void);
t_env		*get_env_st(t_env *env);
char	*check_translation(char *s);
t_type		*find_next_type(t_type *begin);
void    build_tree(t_type *begin);
void				exec_cmd(t_tree *root);
void    exec_pipe(t_tree *root, int backfd, int count);
char		**prep_cmd(t_type *begin, int i);
void	sig_c(int sig);
char	*get_tild(void);
int		create_file(int type, char **file_name);
void				redirections(t_tree *root);
void	translate_only(t_type *begin);
#endif