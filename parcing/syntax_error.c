/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:28:13 by mabed             #+#    #+#             */
/*   Updated: 2023/10/26 14:54:17 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	alloc_msg(t_data *data)
{
	data->msg_err = malloc(sizeof(char **) * 8);
	data->msg_err[0] = ft_strdup("minishell: syntax error near unexpected token `<'\n");
	data->msg_err[1] = ft_strdup("minishell: syntax error near unexpected token `<<'\n");
	data->msg_err[2] = ft_strdup("minishell: syntax error near unexpected token `>'\n");
	data->msg_err[3] = ft_strdup("minishell: syntax error near unexpected token `>>'\n");
	data->msg_err[4] = ft_strdup("minishell: syntax error near unexpected token `newline'\n");
	data->msg_err[5] = ft_strdup("minishell: syntax error near unexpected token `<<<'\n");
	data->msg_err[6] = ft_strdup("minishell: syntax error near unexpected token `>>>'\n");
	data->msg_err[7] = ft_strdup("minishell: syntax error near unexpected token `|'\n");
}

int	syntax_error(t_data *data)
{
	t_list	*tmp;

	tmp = data->first;
	alloc_msg(&*data);
	while (tmp != NULL)
	{
		if (verif_pipe(tmp, &*data) == 1)
			return (1);
		if (verif_spaces_chevron(tmp, &*data) == 1)
			return (1);
		if (tmp->token == REDIRECTION_IN && ft_strlen(tmp->content) == 3)
			return (printf("%s", data->msg_err[0]), 1);
		else if (tmp->token == REDIRECTION_IN && ft_strlen(tmp->content) > 3)
			return (printf("%s", data->msg_err[1]), 1);
		else if (tmp->token == REDIRECTION_IN && ft_strlen(tmp->content) < 3 && (tmp->next == NULL || (tmp->next->token == SPACES && tmp->next->next == NULL)))
			return (printf("%s", data->msg_err[4]), 1);
		if (tmp->token == REDIRECTION_OUT && ft_strlen(tmp->content) == 3)
			return (printf("%s", data->msg_err[2]), 1);
		else if (tmp->token == REDIRECTION_OUT && ft_strlen(tmp->content) > 3)
			return (printf("%s", data->msg_err[3]), 1);
		else if (tmp->token == REDIRECTION_OUT && ft_strlen(tmp->content) < 3 && (tmp->next == NULL || (tmp->next->token == SPACES && tmp->next->next == NULL)))
			return (printf("%s", data->msg_err[4]), 1);
		if (verif_chev_next_chev(tmp, &*data) == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	verif_spaces_chevron(t_list *tmp, t_data *data)
{
	if ((tmp->token == REDIRECTION_IN || tmp->token == REDIRECTION_OUT) && tmp->next != NULL && tmp->next->next != NULL && tmp->next->token == SPACES && tmp->next->next->token == REDIRECTION_IN)
	{
		if (ft_strlen(tmp->content) <= 4)
			return (printf("%s", data->msg_err[0]), 1);
		else if (ft_strlen(tmp->content) == 5)
			return (printf("%s", data->msg_err[1]), 1);
		else if (ft_strlen(tmp->content) > 5)
			return (printf("%s", data->msg_err[5]), 1);
	}
	if ((tmp->token == REDIRECTION_IN || tmp->token == REDIRECTION_OUT) && tmp->next != NULL && tmp->next->next != NULL && tmp->next->token == SPACES && tmp->next->next->token == REDIRECTION_OUT)
	{
		if (ft_strlen(tmp->content) <= 4)
			return (printf("%s", data->msg_err[2]), 1);
		else if (ft_strlen(tmp->content) == 5)
			return (printf("%s", data->msg_err[3]), 1);
		else if (ft_strlen(tmp->content) > 5)
			return (printf("%s", data->msg_err[6]), 1);
	}
	return (0);
}

int	verif_chev_next_chev(t_list *tmp, t_data *data)
{
	if (tmp->token == REDIRECTION_IN)
	{
		if (tmp->next->token == REDIRECTION_OUT && ft_strlen(tmp->next->content) == 1)
			return (printf("%s", data->msg_err[2]), 1);
		else if (tmp->next->token == REDIRECTION_OUT && ft_strlen(tmp->next->content) > 1)
			return (printf("%s", data->msg_err[3]), 1);
	}
	else if (tmp->token == REDIRECTION_OUT)
	{
		if (tmp->next->token == REDIRECTION_IN && ft_strlen(tmp->next->content) == 1)
			return (printf("%s", data->msg_err[0]), 1);
		else if (tmp->next->token == REDIRECTION_IN && ft_strlen(tmp->next->content) > 1)
			return (printf("%s", data->msg_err[1]), 1);
	}
	return (0);
}

int	verif_pipe(t_list *tmp, t_data *data)
{
	if(tmp->token == PIPE && (tmp->prev == NULL || (tmp->prev->token == SPACES && tmp->prev->prev == NULL)))
		return (printf("%s", data->msg_err[7]), 1);
	else if((tmp->token ==  PIPE) && ((tmp->prev->token == REDIRECTION_IN || tmp->prev->token == REDIRECTION_OUT) || ((tmp->prev->token == SPACES) && (tmp->prev->prev->token == REDIRECTION_IN || tmp->prev->prev->token == REDIRECTION_OUT))))
		return (printf("%s", data->msg_err[7]), 1);
	else if (tmp->token == PIPE && ft_strlen(tmp->content) > 1)
		return (printf("%s", data->msg_err[7]), 1);
	else if(tmp->token == PIPE && (tmp->next == NULL || (tmp->next->token == SPACES && tmp->next->next == NULL)))
		return (printf("%s", data->msg_err[7]), 1);
	else if(tmp->token == PIPE && tmp->next != NULL && tmp->next->token == SPACES && tmp->next->next->token == PIPE)
		return (printf("%s", data->msg_err[7]), 1);
	else
		return (0);
}

