/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:27:04 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/08 16:27:56 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

int				ft_strlengnl(char *s);
char			*ft_strchrgnl(char *s, char c);
char			*ft_strcpygnl(char *dest, char *src);
char			*ft_strdupgnl(char *s);
char			*ft_substring(char *str, unsigned int start, unsigned int len);
char			*joinnwrfree(char *str1, char *str2);
int				get_next_line(int fd, char **line);
#endif
