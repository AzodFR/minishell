/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thjacque <thjacque@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:27:07 by thjacque          #+#    #+#             */
/*   Updated: 2021/01/08 16:24:58 by thjacque         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strchrgnl(char *s, char c)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return ((char *)&s[i]);
	return (NULL);
}

int		ft_strlengnl(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strcpygnl(char *dest, char *src)
{
	int		i;

	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = 0;
	return (dest);
}

char	*ft_strdupgnl(char *s)
{
	char	*ptr;
	int		i;

	i = -1;
	if (!(ptr = (char*)wrmalloc((ft_strlengnl(s) + 1) * sizeof(char))))
		return (NULL);
	while (s[++i])
		ptr[i] = s[i];
	ptr[i] = 0;
	return (ptr);
}

char	*ft_substring(char *str, unsigned int start, unsigned int len)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	count;
	char			*newstr;

	i = 0;
	j = ft_strlengnl(str);
	if (start >= j || j == 0)
		return (ft_strdupgnl(""));
	count = start - j;
	if (count > len)
		count = len;
	if (!(newstr = wrmalloc((count + 1) * sizeof(char))))
		return (NULL);
	while (len--)
		newstr[i++] = str[start++];
	newstr[i] = 0;
	return (newstr);
}
