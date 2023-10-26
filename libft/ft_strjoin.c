/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabed <mabed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:31:31 by mabed             #+#    #+#             */
/*   Updated: 2023/09/27 11:54:44 by mabed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen2(char const *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		j;
	int		i;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	str = malloc(sizeof(char) * (ft_strlen2(s1) + ft_strlen2(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[k] = s1[i];
		i++;
		k++;
	}
	while (s2[j])
	{
		str[k] = s2[j];
		j++;
		k++;
	}
	str[k] = '\0';
	return (free((char *)s1), free((char *)s2), str);
}
