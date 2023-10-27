/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabed <mabed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:21:00 by mabed             #+#    #+#             */
/*   Updated: 2023/10/24 04:17:18 by mabed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_list *lst)
{
	t_list	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}

void	free_data(t_data *data)
{
	free_list(data->first);
	free_env(data->env_list);
	free(data);
}

int	main(int ac, char **av, char **env)
{
	char			*line;
	static t_data	data = {NULL, NULL, 0, NULL, NULL, NULL, NULL};
	t_list			*list;
	int				i;
	const char *tab[18] = {"SPACES", "REDIRECTION_IN", "REDIRECTION_OUT", "PIPE", "ALPHANUMERIC", "DOLLAR", "INTERRO", "SIMPLE_QUOTE", "DOUBLE_QUOTE", "CMD", "FILE_IN", "HERE_DOC", "FILE_OUT", "FILE_OUT_SUR", "OPEN_FILE", "LIMITOR", "EXIT_FILE", "EXIT_FILE_RET"};
	int				j;
	int				k;

	(void)ac;
	(void)av;
	// k = 0;

	data.env_list = creat_env_lst(env);
	data.envi = env2(data.env_list);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (line && *line)
			add_history(line);
		if (verif_quote(line) <= 0)
		{
			ft_negative(line);
			creat_list(line, &data);
			join_link(&data);
			if (syntax_error(&data) == 0)
			{
				ft_positive(&data);
				replace_quote(&data);
				replace_dollar(&data);
				join_link(&data);
				get_token3(&data.first);
				get_token4(&data.first);
				get_token5(&data.first);
				data.tb_cmd = tab_cmd(&data);
			}
		}
		list = data.first;
		while (list != NULL)
		{
			printf("%s\n--------\n", list->content);
			printf("token: %s\n", tab[list->token]);
			printf("-----------------------------------------\n");
			list = list->next;
		}
		j = 0;
		while (data.tb_cmd[j] != NULL)
		{
			k = 0;
			while (data.tb_cmd[j][k] != NULL)
			{
				printf("cmd[%d][%d] : %s\n",j, k, data.tb_cmd[j][k]);
				k++;
			printf("--------\n");
			}
			j++;
		}

		//free_list(data.first);
		// list = data.env_list;
		// while (list != NULL)
		// {
		// 	printf("%s\n", list->content);
		// 	printf("-----------------------------------------\n");
		// 	list = list->next;
		// }
	}
	i = data.exit_code;
	free_data(&data);
	return (i);
}
