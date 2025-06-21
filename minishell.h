/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelmahf <maelmahf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:03:24 by hmouis            #+#    #+#             */
/*   Updated: 2025/06/21 15:20:26 by maelmahf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int					g_exit_status;

/*env*/
typedef struct s_env
{
	char					*key;
	char					*data;
	char					*oldpwd;
	char					*pwd;
	struct s_env			*next;
}							t_env;

// variables for functions
typedef struct s_var_export
{
	int						i;
	char					*equal;
	char					*key;
	char					*s;
	char					*value;
}							t_var_export;

typedef struct s_var_env
{
	int						i;
	char					*key;
	char					*data;
}							t_var_env;

/*type of tokens*/
typedef enum e_types
{
	op_redirect_input,  // <
	op_redirect_output, // >
	op_herdoc,          // <<
	op_append,          // >>
	op_pipe,            // |
	word,
	var,
	string,
	single_quote,
	double_quote,
	TYPE_INVALID = -1
}							t_types;

typedef enum e_builtins_type
{
	e_echo,
	e_cd,
	e_pwd,
	e_export,
	e_unset,
	e_env,
	e_exit,
}							t_builtins_type;

typedef struct s_list
{
	void					*content;
	struct s_list			*next;
}							t_list;

typedef struct s_lst
{
	char					*content;
	enum e_types			type;
	struct s_lst			*next;
}							t_lst;

typedef struct s_var
{
	int						i;
	int						y;
	char					*token;
	int						length;
}							t_var;

typedef struct s_exp
{
	char					*content;
	t_types					type;
	struct s_exp			*next;
}							t_exp;

typedef struct s_exec
{
	char					**args;
	int						*exit_status;
}							t_exec;

typedef struct s_gnl
{
	char					*str;
	t_types					type;
	struct s_gnl			*next;
}							t_gnl;

typedef struct s_herdoc
{
	t_gnl					*list;
	struct s_herdoc			*next;
}							t_herdoc;

typedef struct s_final_struct
{
	t_gnl					*args;
	t_gnl					*redirect;
	t_herdoc				*herdoc;
	t_env					*lst_env;
	struct s_final_struct	*next;
}							t_final_struct;

typedef struct s_new_exp
{
	t_lst					*string;
	t_types					type;
	struct s_new_exp		*next;
}							t_new_exp;

typedef struct s_cmd
{
	t_lst					*arg;
	char					**args;
	t_lst					*redirect;
	struct s_cmd			*next;
}							t_cmd;

typedef struct s_va
{
	int						i;
	int						start;
	int						len;
}							t_va;

typedef struct s_helper_var
{
	char					*str;
	char					*field_str;
	int						flag;
}							t_helper_va;

/*her_doc*/
t_herdoc					*fill_herdoc(t_lst *redirect, t_env *env,
								t_herdoc **herdoc);
t_gnl						*her_doc(char *del, t_env *env, t_gnl *lst);
t_herdoc					*new_herdoc(void);
void						put_error_msg(char *str);
char						*expand_herdoc(char *str, t_env *env);
int							expand_in_herdoc(t_va *va, char *str,
								char **new_str, t_env *env);
int							add_inside_quote(char *str, char **new_str, int *i);

/*expansion*/
void						fnl_argm(t_env *list, t_lst *argm, t_new_exp **exp,
								t_final_struct **fnl);
void						fnl_red(t_env *list, t_lst *red, t_new_exp **exp,
								t_final_struct **fnl);
void						split_string(char *str, t_new_exp **exp);
void						check_double_quote(char **str, t_env *env,
								t_new_exp *exp);
void						split_str(char **str, char *field_str, t_gnl **gnl,
								t_new_exp *exp);
void						is_var(t_new_exp *exp, t_helper_va *va, t_env *env,
								t_gnl **gnl);
void						add_space(char **field_str, int *remainder,
								int *count);
int							skip_split_char(char *str, int *i, int *remainder,
								int *check);
void						skip_var_char(char *str, int *i, int *len);
int							dollar_sign_in_quote(char *str, t_va *va,
								t_new_exp **exp);
char						*fnl_str(t_env *env, t_new_exp *exp);
char						*expand_double_quote(char *str, t_env *env);
t_final_struct				*fnl_node(void);
int							redirect_type(char *str);
int							dollar_sign_string(char *str, t_va *va,
								t_new_exp **exp);
int							quote_string(char *str, t_va *va, t_new_exp **exp);
int							get_flag_v(char c);
int							get_flag_q(char quote);
void						del_last_str(char *str, t_va *va, t_new_exp **exp);
int							split_char(char c);
void						add_to_string_lst(t_lst **lst, char *content,
								int flag);
void						*new_node_(char *content, int flag);
t_new_exp					*new_lst_node(int type);
int							str_len(char *str);
void						expand_quote(t_exp **lst, char *str);
char						*expand_var(t_exp *exp, t_env *lst);
void						type_of_var(t_exp *exp);
t_exp						*new_var_node(char *content);
t_exp						*last_node_var(t_exp *lst);
void						add_var_back(t_exp **lst, t_exp *node);
void						add_to_var_lst(t_exp **lst, char *content);
int							tokenize_dollar_sign(t_exp **exp, char *str);
int							check_char(char c);
void						add_to_gnl_lst(t_gnl **lst, char *content,
								int type);
void						add_gnl_back(t_gnl **lst, t_gnl *node);
t_gnl						*final_node(char *content, int type);
t_gnl						*last_node_gnl(t_gnl *lst);
t_final_struct				*creat_new_exp(t_env *list, t_new_exp **exp,
								t_cmd *cmd, t_final_struct **fnl);
char						*ft_strjoin(char *s1, char *s2);
void						expand(t_new_exp *exp, t_env *env, t_gnl **gnl);
int							is_digit(char c);
char						*char_join(char *str, int count, char c);
int							var_char(char c);

/*syntax errors*/
void						error_msg(char *str, int status);
char						*check_quote(char *str);
int							is_quote(char c);
char						*pipe_line(t_lst *lst, int *status);
char						*simple_command(t_lst **lst);
void						add_to_lst_c(t_lst **lst, t_lst *node);
t_lst						*new_node_c(t_lst *node);
char						*n_of_herdoc(t_lst *lst, int *status);
void						add_tolst(t_lst **lst, t_cmd **cmd);

/*helper functions*/
int							valid_operator(char c1, char c2);
int							white_space(char c);
int							is_operator(char *str);
int							charchr(char *str, int c);
char						*ft_strlcpy(char *token, char *input, int len,
								int j);
t_exec						*gnl_to_array(t_gnl *head);

/*tokenizing*/
int							token_dollar_sign(int *i, char *input, t_var *var);
int							split_input(char *input, t_lst **lst);
int							token_quote(int *i, char *input, t_var *var);
int							token_operator(t_var *var, char *input,
								t_lst **lst);
int							end_of_input(t_var *var, char *input, t_lst **lst);
int							creat_token(t_var *var, char *input, t_lst **lst);
int							token_blank(t_var *var, char *input, t_lst **lst);

/*type of token*/
void						tokens_type(t_lst *lst);
int							is_redirection(t_lst *lst);
int							is_pipe(t_lst *lst);

/*linked list*/
t_cmd						*creat_cmd_struct(t_cmd **cmd, t_lst *lst);
t_cmd						*node(void);
t_lst						*last_node(t_lst *lst);
void						add_back(t_lst **lst, t_lst *node);
void						*new_node(char *content);
void						add_to_lst(t_lst **lst, char *content);

/*get env*/
int							is_builtins(char *cmd);
int							builtin_cd(char **cwd, t_var *var);
int							is_in_set(char c, const char *set);
t_env						*env_new_node(char *key, char *data);
char						*get_env(char *str, t_env *env);
char						*get_env_key(char *s);
char						*get_env_data(char *s);
char						*get_data_env(char *env);
void						add_env_to_list(t_env **lst, char **env);
int							split_char(char c);
int							split_var_arg(char *str, char **field_str);

// libft
char						*ft_strdup(char *s);
char						*ft_strncpy(char *dest, const char *src, size_t n);
int							is_alpha(char c);
int							is_alnum(char c);
int							ft_is_digits(char c);
long						ft_atoi(char *str);
char						*ft_strchr(char *s, char c);
char						*ft_substr(char *s, int start, int len);
void						ft_putstr_fd(char *s, int fd);
char						*ft_strcat(char *s1, char *s2);
char						*ft_strtok(char *str, char *delim);
int							ft_strcmp(char *s1, char *s2);

// exec
int							exec_builtins(t_env **lst_env, t_exec **cmd,
								t_final_struct *struc);
int							exec_cmd(char **env, t_exec **cmd,
								t_final_struct *tmp);
void						execute(t_final_struct *list, t_env *env_list,
								char **env);

void						exec_env(t_env **lst);
void						exec_echo(t_exec **cmd);
void						exec_export(t_env **env, t_exec **cmd);
void						exec_unset(t_env **env, t_exec **key);
void						exec_exit(t_final_struct *fnl, t_exec **cmd);
void						exec_pwd(t_env **env);
void						exec_cd(t_env **env, t_exec **cmd);
char						*get_variable(t_env **env, char *key);
int							type_of_redirect(char *redirect);
int							apply_redirect(t_final_struct *struc);
void						update_env(t_env **env, char *oldpwd, char *pwd);

/*garbage collector*/
void						ft_lstdelone(t_list *lst, void (*del)(void *));
void						*ft_malloc(size_t size, int flag);
void						ft_lstclear(t_list **lst, void (*del)(void *));
void						ft_lstadd_front(t_list **lst, t_list *new_);

#endif
