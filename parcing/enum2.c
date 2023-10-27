/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:34:53 by cabouzir          #+#    #+#             */
/*   Updated: 2023/10/27 14:36:02 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_token4(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp && tmp->next != NULL)
	{
		if (tmp->next)
		{
			if (tmp->token == FILE_IN && tmp->next->token == ALPHANUMERIC)
				tmp->next->token = OPEN_FILE;
			else if (tmp->token == FILE_OUT && tmp->next->token == ALPHANUMERIC)
				tmp->next->token = EXIT_FILE;
			else if (tmp->token == FILE_OUT_SUR
				&& tmp->next->token == ALPHANUMERIC)
				tmp->next->token = EXIT_FILE_RET;
			else if (tmp->token == HERE_DOC && tmp->next->token == ALPHANUMERIC)
				tmp->next->token = LIMITOR;
		}
		tmp = tmp->next;
	}
}

void	get_token5_2(t_list *tmp)
{
	if (tmp->token == FILE_IN && tmp->next->next->token == ALPHANUMERIC)
		tmp->next->next->token = OPEN_FILE;
	else if (tmp->token == FILE_OUT
		&& tmp->next->next->token == ALPHANUMERIC)
		tmp->next->next->token = EXIT_FILE;
	else if (tmp->token == FILE_OUT_SUR
		&& tmp->next->next->token == ALPHANUMERIC)
		tmp->next->next->token = EXIT_FILE_RET;
	else if (tmp->token == HERE_DOC
		&& tmp->next->next->token == ALPHANUMERIC)
		tmp->next->next->token = LIMITOR;
}

void	get_token5(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp && tmp->next != NULL)
	{
		if (tmp->next->next && tmp->next->token == SPACES)
		{
			// if (tmp->token == FILE_IN && tmp->next->next->token == ALPHANUMERIC)
			// 	tmp->next->next->token = OPEN_FILE;
			// else if (tmp->token == FILE_OUT
			// 	&& tmp->next->next->token == ALPHANUMERIC)
			// 	tmp->next->next->token = EXIT_FILE;
			// else if (tmp->token == FILE_OUT_SUR
			// 	&& tmp->next->next->token == ALPHANUMERIC)
			// 	tmp->next->next->token = EXIT_FILE_RET;
			// else if (tmp->token == HERE_DOC
			// 	&& tmp->next->next->token == ALPHANUMERIC)
			// 	tmp->next->next->token = LIMITOR;
			get_token5_2(&*tmp);
		}
		tmp = tmp->next;
	}
	tmp = *list;
	while (tmp != NULL)
	{
		if (tmp->token == ALPHANUMERIC)
			tmp->token = CMD;
		tmp = tmp->next;
	}
}
