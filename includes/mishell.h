/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mishell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:12:37 by thjacque          #+#    #+#             */
/*   Updated: 2021/02/15 10:08:38 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISHELL_H
# define MISHELL_H
# include "extern.h"

void			welcome(char **env);
/*
**	BUILTINS
*/
void			get_pwd(void);
void			get_env(t_env *envp);
void			change_dir(t_env *env, char **args);
void			export_env(t_env *env, char **args);
int				print_export(t_env *env);
void			unset(t_env *env, char **args);
void			do_echo(char **args);
void			cmd_exit(char **args);
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
t_env			*get_env_st(t_env *env);
/*
**	TREE BUILD
*/
void			build_tree(t_type *begin);
void			init_node(t_tree **node, t_type *cmd);
void			create_nodes(t_type *begin, t_tree *root);
/*
**	CMD EXECUTION
*/
void			treat(char *line);
t_type			*find_next_type(t_type *begin);
void			exec_cmd(t_tree *root);
void			exec_pipe(t_tree *root, int backfd, int count);
void			exec_redir(t_tree *root);
int				handler(char **cmd, t_env *env);
int				exec_cmd_parents(char *path, char **args, char**env);
int				create_file(int type, char **file_name);
void			check_exit(void);
/*
**	CHECKER
*/
char			*search_cmd_local(char **args);
char			*search_cmd_abs(char **args);
int				se_path(t_env *env, int i, char **args, int launch);
int				se_local(t_env *env, char **args, int launch);
int				se_abs(t_env *env, char **args, int launch);
void			search_cmd(t_env *env, char **args, int i);
int				is_directory(const char *path);
int				isalldigit(char *s);
int				check_cmd(t_env *env, char **args, int i);
/*
**	PREPARE CMD
*/
int				no_prev(t_type *begin);
int				no_next(t_type *begin);
int				no_cmd(t_type *begin);
t_type			*errornear(char *s);
char			*translate(char *s, int *i, t_all *all, char *string);
char			**prep_cmd(t_type *begin, int i);
char			**trim_args(char *line, char c);
void			ft_exit(int code);
int				splitter_counter_cmd(char *s, t_all *a, int i);
int				splitter_counter_args(char *s, t_all *a, int *j);
t_type			*prepare_array(char *line);
t_all			*get_all_st(t_all *all);
t_type			*create_struc(char *line, int i, char type, t_type *str_type);
char			check_type(char *str, int i, char c);
int				jump_cote(char **line, int i, t_type **str_type, int *u);
int				moov_type(int u, char *line);
t_type			*split_type(char **linep, int u);
char			*add_one(char *s, char c);
char			*check_translation(char *s);
t_type			*find_next_type(t_type *begin);
void			translate_only(t_type *begin);
void			prep(t_type *begin);
t_type			*add_space_t(t_type *prev);
t_type			*add_file(t_type *prev, t_type *toadd);
void			add_back(t_type **redir, t_type *toadd);
t_type			*lastredir(t_type *redir);
int				go_next_begin(t_type **begin);
int				not_good_right(t_tree *right);

int				main_donut(char **args);
/*
**	UTILS
*/
void			sig_c(int sig);
void			sig_quit(int sig);
char			*get_tild(void);
int				end_ling(int ret, char *s);
int				is_right_redir(t_type *tmp);
void			get_fd_back(int fd[3]);
void			exit_donut(int sig);
int				too_much(t_type *tmp);
int				get_mpid(void);
#endif
