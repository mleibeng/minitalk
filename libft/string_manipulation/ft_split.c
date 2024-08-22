/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:49:51 by mleibeng          #+#    #+#             */
/*   Updated: 2023/10/31 23:17:20 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_substr_len(char const *str, char c)
{
	size_t	count_len;

	count_len = 0;
	while (str && str[count_len] != c)
	{
		if (str[count_len] == '\0')
			break ;
		count_len++;
	}
	return (count_len);
}

size_t	split_arr_len(char const *s, char c)
{
	size_t	i;
	size_t	string_count;
	size_t	alarm;

	i = 0;
	string_count = 0;
	alarm = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (c != s[i] && alarm == 0)
		{
			alarm = 1;
			string_count++;
		}
		if (c == s[i] && alarm == 1)
			alarm = 0;
		i++;
	}
	return (string_count);
}

void	*ft_free(char **split_arr, size_t i)
{
	while (i--)
		free(split_arr[i]);
	free(split_arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**split_arr;
	size_t	string_count;
	size_t	i;
	size_t	j;
	size_t	s_len;

	i = 0;
	string_count = split_arr_len(s, c);
	split_arr = (char **)malloc((string_count + 1) * sizeof(char *));
	if (split_arr == NULL)
		return (NULL);
	while (i < string_count && *s)
	{
		while (*s == c)
			s++;
		split_arr[i] = malloc((s_len = ft_substr_len(s, (unsigned char)c)) + 1);
		if (!split_arr[i])
			return (ft_free(split_arr, i));
		j = 0;
		while (j < s_len)
			split_arr[i][j++] = *s++;
		split_arr[i++][s_len] = '\0';
	}
	split_arr[i] = NULL;
	return (split_arr);
}
