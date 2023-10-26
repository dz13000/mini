/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:44:36 by mabed             #+#    #+#             */
/*   Updated: 2023/10/26 15:01:25 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef enum e_tokens
{
	SPACES,
	REDIRECTION_IN,
	REDIRECTION_OUT,
	PIPE,
	ALPHANUMERIC,
	DOLLAR,
	INTERRO,
	SIMPLE_QUOTE,
	DOUBLE_QUOTE,
	CMD,           //comande
	FILE_IN,       //word == '<'
	HERE_DOC,      // word == '<<'
	FILE_OUT,      //word == '>'
	FILE_OUT_SUR,  //word == '>>'
	OPEN_FILE,     // word following '<'
	LIMITOR,       // word following '<<'
	EXIT_FILE,     // word followinf '>'
	EXIT_FILE_RET, // word following '>>'
}						t_tokens;

typedef struct s_env
{
	char				*content;
	struct s_env		*next;
}						t_env;

typedef struct s_list
{
	char				*content;
	struct s_list		*next;
	struct s_list		*prev;
	t_data				*data;
	t_tokens			token;
	int					indice;
}						t_list;

typedef struct s_data
{
	t_list				*first;
	t_list				*last;
	int					exit_code;
	struct s_env		*env_list;
	char				**envi;
	char				***tb_cmd;
	char				**msg_err;
}						t_data;

void					ft_negative(char *line);
int						verif_quote(char *line);
t_list					*ft_lstnew(t_data *data, char content, int i);
t_list					*ft_lstadd_back(t_list **lst, t_list *new);
void					creat_list(char *str, t_data *dbl_list);
char					*c_to_str(char c);
// void		tokens_distrib(t_list *list);
void					join_link(t_data *data);
t_tokens				get_token(char *str);
int						syntax_error(t_data *data);
int						verif_spaces_chevron(t_list *tmp);
int						verif_pipe(t_list *tmp);
t_env					*ft_envnew(char *content);
t_env					*ft_envadd_back(t_env **lst, t_env *new);
t_env					*creat_env_lst(char **content);
char					*get_path_var(t_env *env, char *str, int i);
void					replace_quote(t_data *data);
void					replace_dollar_quote(t_list *lst);
void					ft_positive(t_data *data);
int						var_env_len(char *str);
int						var_dollar_len(char *str);
char					*replace_alpha_null(t_list *lst, int i);
char					*replace_alpha_env(t_list *lst, char *str, int i);
void					del_link(t_list *lst);
// void		del_next_link(t_list *lst);
char					*replace_dollar_alpha(t_list *lst);
char					*replace_dollar_digit(t_list *lst);
char					*replace_dollar_return_code(t_list *lst);
void					replace_dollar(t_data *data);
char					*replace_dollar_alpha2(t_list *lst);
char					*replace_dollar_digit2(t_list *lst);
char					*replace_dollar_return_code2(t_list *lst);
char					*replace_alpha_env2(t_list *lst, char *str);
char					*replace_alpha_null2(t_list *lst);
void					free_list(t_list *lst);
void					free_data(t_data *data);
void					free_env(t_env *env);
char					**env2(t_env *env);
void					del_empty_join_quote(t_data *data);
int						verif_chev_next_chev(t_list *tmp);
t_list					*ft_lstnew2(t_data *data, char content, int i);
void					creat_list2(char *str, t_data *dbl_list, t_list **first,
							t_list **last);
t_tokens				get_token2(char *str);
void					join_link2(t_list **first, t_list **last);
void					integration(t_list **lst);
char					***tab_cmd(t_data *dbl_list);
int						nb_cmd(t_list *lst);
void					get_token3(t_list **list);
void					get_token4(t_list **list);
void					get_token5(t_list **list);
// void		ft_positive(char *line);
// t_list		*ft_lstnew(char content, t_data *dbl_list);
// t_list		*ft_lstadd_back(t_list **lst, t_list *new);
// void		creat_list(char *str, t_data *dbl_list);
// char		*c_to_str(char c);
// void		tokens_distrib(t_list *list);
// void		join_link(t_list *list, t_data *data);
// t_tokens	get_token(char *str);
// int			ft_comp_env(t_list *list, char *str);
// void		ft_replace_dollar(t_list *list, char *str, int i);
// void		str_shift(t_list *list);
// void		ft_dollar(t_list *list);
// void		ft_double_quote(t_list *list);
// void		ft_simple_quote(t_list *list);
// int			check_quote(t_list *list);

#endif
