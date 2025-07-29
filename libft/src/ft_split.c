/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:50:37 by vloureir          #+#    #+#             */
/*   Updated: 2025/04/19 13:10:47 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_clean_alloc(char **av, int ac)
{
	int	i;

	i = -1;
	while (++i < ac)
		free(av[i]);
	free(av);
}

static size_t	ft_len(char const *str, char c, int *i)
{
	int		j;
	size_t	len;

	j = *i;
	len = 0;
	while (str[j] && str[j] == c)
		j++;
	while (str[j] && str[j] != c)
	{
		j++;
		len++;
	}
	*i = j;
	return (len);
}

static size_t	ft_word_count(char const *s, char c)
{
	int	i;
	int	count;
	int	state;

	i = 0;
	count = 0;
	while (s[i])
	{
		state = 1;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			if (state)
			{
				state = 0;
				count++;
			}
			i++;
		}
	}
	return (count);
}

static char	**ft_populate_array(char const *s, char c, char **av)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	j = 0;
	while (s[i])
	{
		len = ft_len(s, c, &i);
		if (len)
		{
			av[j] = malloc(sizeof(char) * (len + 1));
			if (!av[j])
			{
				ft_clean_alloc(av, j);
				return (NULL);
			}
			ft_strlcpy(av[j], &s[i - len], len + 1);
			j++;
		}
	}
	return (av);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**argv;

	if (!s)
		return (NULL);
	count = ft_word_count(s, c);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	argv[count] = 0;
	argv = ft_populate_array(s, c, argv);
	return (argv);
}
