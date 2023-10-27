/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_quote2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:06:44 by mabed             #+#    #+#             */
/*   Updated: 2023/10/27 13:42:35 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// i et l indice du caractere apres le dollar
char	*get_path_var(t_env *env, char *tmp, int i)
{
	t_env	*tmp_env;

	tmp_env = env;
	if (!env)
		exit(1);
	while (tmp_env != NULL)
	{
		if (var_env_len(tmp_env->content) == var_dollar_len(tmp + i))
		{
			if (ft_strncmp(tmp_env->content, tmp + i,
					var_env_len(tmp_env->content)) == 0)
				return (tmp_env->content);
		}
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

char	*replace_alpha_null(t_list *lst, int i)
{
	int		j;
	int		k;
	char	*str;

	j = 0;
	k = 0;
	str = malloc(sizeof(char) * (ft_strlen(lst->content)
				- var_dollar_len(lst->content + i)));
	while (lst->content[j])
	{
		if (j == (i - 1))
			j = j + var_dollar_len(lst->content + i) + 1;
		if (lst->content[j])
			str[k++] = lst->content[j++];
	}
	str[k] = '\0';
	free (lst->content);
	return (str);
}

typedef struct s_var
{
	int		j;
	int		k;
	int		l;
	char	*tmp;
}t_var;

void	alloc_var(t_var *var, char *str, int i, t_list *lst)
{
	var->j = 0;
	var->j = 0;
	var->l = var_env_len(str) + 1;
	var->tmp = malloc(sizeof(char) * (ft_strlen(lst->content)
				- var_dollar_len(lst->content + i) + ft_strlen(str + var->l)));
}

char	*replace_alpha_env(t_list *lst, char *str, int i)
{
	// int		j;
	// int		k;
	// int		l;
	// char	*tmp;
	t_var var;

	// j = 0;
	// k = 0;
	// val = var_env_len(str) + 1;
	alloc_var(&var, str, i, &*lst);
	// var.tmp = malloc(sizeof(char) * (ft_strlen(lst->content)
	// 			- var_dollar_len(lst->content + i) + ft_strlen(str + var.l)));
	while (lst->content[var.j])
	{
		if (var.j == (i - 1))
		{
			var.j = var.j + var_dollar_len(lst->content + i) + 1;
			while (str[var.l])
			{
				var.tmp[var.k] = str[var.l];
				var.k++;
				var.l++;
			}
		}
		if (lst->content[var.j])
		{
			var.tmp[var.k] = lst->content[var.j];
			var.j++;
			var.k++;
		}
	}
	var.tmp[var.k] = '\0';
	free (lst->content);
	return (var.tmp);
}
