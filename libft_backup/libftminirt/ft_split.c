/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:26:47 by jzackiew          #+#    #+#             */
/*   Updated: 2024/12/07 13:31:58 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_words_num(char const *str, char c)
{
	int	word_count;
	int	i;

	word_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			if (str[i + 1] == c || str[i + 1] == 0)
				word_count++;
		}
		i++;
	}
	return (word_count);
}

static char	*get_word(char const *str, int i, int word_len)
{
	int		k;
	char	*word;

	k = 0;
	word = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!word)
		return (NULL);
	while (k < word_len)
	{
		word[k] = str[(i + 1) - word_len + k];
		k++;
	}
	word[k] = 0;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	int		j;
	int		word_len;

	i = -1;
	j = 0;
	word_len = 0;
	arr = (char **)ft_calloc((get_words_num(s, c) + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	while (s[++i] != 0)
	{
		if (s[i] != c)
		{
			word_len++;
			if (s[i + 1] == c || s[i + 1] == 0)
			{
				arr[j++] = get_word(s, i, word_len);
				word_len = 0;
			}
		}
	}
	return (arr);
}

/* int main()
{
	char **x = ft_split("     Finding words to be split", ' ');
	int i = 0;

	while(x[i])
	{
		printf("%s\n", x[i]);
		i++;
	}
} */