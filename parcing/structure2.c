/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 23:15:21 by mabed             #+#    #+#             */
/*   Updated: 2023/10/26 13:19:38 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew2(t_data *data, char content, int i)
{
	t_list	*element;

	element = malloc(sizeof(t_list));
	if (!element)
		return (NULL);
	element->content = c_to_str(content);
	element->next = NULL;
	element->prev = NULL;
	element->token = get_token2(element->content);
	element->data = data;
	element->indice = i;
	return (element);
}

void	creat_list2(char *str, t_data *dbl_list, t_list **first, t_list **last)
{
	int		i;
	int		j;
	t_list	*list;

	j = 0;
	i = 0;
	if (!str)
		return ;
	*first = ft_lstnew2(dbl_list, str[i], j);
	list = *first;
	while (str[++i] != '\0')
		*last = ft_lstadd_back(&list, ft_lstnew2(dbl_list, str[i], ++j));
}

void	join_link2(t_list **first, t_list **last)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *first;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
		{
			if (tmp->token == tmp->next->token && tmp->token != SIMPLE_QUOTE
				&& tmp->token != DOUBLE_QUOTE)
			{
				tmp->content = ft_strjoin(tmp->content, tmp->next->content);
				tmp2 = tmp->next;
				tmp->next = tmp->next->next;
				if (tmp2->next != NULL)
					tmp2->next->prev = tmp;
				else
					*last = tmp;
				free(tmp2);
			}
			else
				tmp = tmp->next;
		}
	}
}

// void 	tab_cmd2(t_list *tmp,  char	***tab)
// {
// 	while (tmp != NULL)
// 	{
// 		int i;
// 		int	j;
// 		int k;

// 		i = 0;
// 		j = 0;
// 		k = nb_cmd(tmp);
// 		tab[i] = malloc(sizeof(char *) * (k + 1));
// 		while (tmp != NULL && tmp->token != PIPE)
// 		{
// 			if (tmp->token == CMD)
// 			{
// 				tab[i][j] = ft_strdup(tmp->content);
// 				j++;
// 			}
// 			tmp = tmp->next;
// 		}
// 		tab[i][j] = NULL;
// 		if (tmp != NULL)
// 			tmp = tmp->next;
// 		i++;
// 	}
// }

char	***tab_cmd(t_data *dbl_list)
{
	int		i;
	int		j;
	int		k;
	char	***tab;
	t_list	*tmp;

	i = 1;
	tmp = dbl_list->first;
	while (tmp != NULL)
	{
		if (tmp->token == PIPE)
			i++;
		tmp = tmp->next;
	}
	tab = malloc(sizeof(char **) * (i + 1));
	tmp = dbl_list->first;
	i = 0;
	// tab_cmd2(&*tmp, &*tab);
	while (tmp != NULL)
	{
		j = 0;
		k = nb_cmd(tmp);
		tab[i] = malloc(sizeof(char *) * (k + 1));
		while (tmp != NULL && tmp->token != PIPE)
		{
			if (tmp->token == CMD)
			{
				tab[i][j] = ft_strdup(tmp->content);
				j++;
			}
			tmp = tmp->next;
		}
		tab[i][j] = NULL;
		if (tmp != NULL)
			tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int	nb_cmd(t_list *lst)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp && (tmp->token != PIPE))
	{
		if (tmp->token == CMD)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
