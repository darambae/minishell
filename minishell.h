/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:30:43 by dabae             #+#    #+#             */
/*   Updated: 2024/06/28 11:58:02 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <stdbool.h>
# include "libft/libft.h"

enum e_token
{
	EXEC,
	PIPE,
	REDIR,
};

extern int	g_exit_status;

typedef struct s_cmd
{
	enum e_token	type;

}			t_cmd;

typedef struct s_execcmd
{
	enum e_token	type;
	char			*argv[100];
	char			*end_argv[100];
}				t_execcmd;

typedef struct s_pipecmd
{
	enum e_token	type;
	t_cmd			*left;
	t_cmd			*right;
}				t_pipecmd;

typedef struct s_redircmd
{
	enum e_token	type;
	t_cmd			*cmd;
	char			*start_file;
	char			*end_file;
	int				token;
	int				mode;
	int				fd;
}				t_redircmd;

typedef struct s_minishell
{
	char	**env_variables;
	int		exit_status;
	int		res;
	char	*start_line;
	char	*end_line;
	char	*start_t;
	char	*end_t;
	char	*cmd_line;
	t_cmd	*first_cmd;
	int		save_out;
	int		save_in;
	char	**arg_to_clean;
}				t_minishell;

//init
void		init_parse_line(char *line, t_minishell *param);
void		init_param(char **envp, t_minishell *param);

int			ft_error(char *msg, int exit_code);
int			is_executable(t_cmd *cmd, t_minishell *param);

//constructor

t_cmd		*execcmd(void);
t_cmd		*redircmd(t_cmd *sub_cmd, int mode, t_minishell *param);
t_cmd		*pipecmd(t_cmd *left, t_cmd *right);
t_cmd		*nul_terminator(t_cmd *cmd);

// parsing
/*peek : skip whitespace and tabs, return true if first charac == c
or False if not or if there is no carac*/
int			peek(char *c, t_minishell *param);
int			get_token(int save, t_minishell *param);
void		handle_token(char **cur, int save, t_minishell *param);
t_cmd		*parse(t_minishell *param);
char		*dollars_exit(char **cur);
char		*dollars_env(char **cur, char quote, t_minishell *param);
int			quote_parsing(char **cur, int i, t_minishell *param, char *quote);
void		skip_whitespace(char **cur, t_minishell *param);
void		dollars_parsing(char **cur, char quote, int *i, t_minishell *param);
char		*get_env_value(char *s_redircmd, t_minishell *param);
void		save_arg_to_clean(char *s, t_minishell *param);

//execution
int			fork1(void);
void		run_cmd(t_cmd *cmd, t_minishell *param);
void		execute_cmd(char **cmds, t_minishell *param);
int			heredoc_in_branch(t_cmd *branch);

//redirection util function
t_redircmd	*exchange_cmd_order(t_redircmd *rcmd);
void		ft_dup2(t_redircmd *rcmd, int std);
void		here_doc(t_redircmd *rcmd, t_minishell *param);

//builtins
bool		is_builtin(char *cmd);
bool		is_cd_export_unset(t_cmd *cmd);
void		run_cd_export_unset(t_cmd *cmd, t_minishell *param);
void		run_builtin(char **argv, t_minishell *param);
void		ft_exit(char **cmds);
int			ft_echo(char **argv);
int			ft_env(char **argv, t_minishell *param);
int			ft_pwd(void);
int			ft_cd(t_execcmd *cmd, t_minishell *param);
void		ft_export(t_execcmd *cmd, t_minishell *param);
void		ft_unset(t_execcmd *cmd, t_minishell *param);

//signal
void		handle_exit_status(int status);
void		handle_signal_before(int sig);
void		handle_signal_during_execution(int sig);
void		handle_signal_heredoc(int sig);
void		setup_parent_signals(void);

//clean
void		free_cmd(t_cmd *cmd);
void		clean_for_next(char *line, t_minishell *param);
void		clean_all(char *line, t_minishell *param);

//utils
char		**create_double_arr(int size);
int			len_arr(char **arr);

#endif
