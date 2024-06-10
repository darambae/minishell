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
	char	*start_line;
	char	*end_line;
	char	*start_t;
	char	*end_t;
	char	*cmd_line;
	t_cmd	*first_cmd;
	int		save_out;
	int		save_in;
}				t_minishell;

//init
void		trim_line(char *line, t_minishell *g_param);
t_minishell	*init_param(char **envp);
char		**make_copy(char **env);

int			ft_error(char *msg);
int			is_executable(t_cmd *cmd, t_minishell *g_param);

//constructor

t_cmd		*execcmd(void);
t_cmd		*redircmd(t_cmd *sub_cmd, int mode, t_minishell *g_param);
t_cmd		*pipecmd(t_cmd *left, t_cmd *right);
t_cmd		*nul_terminator(t_cmd *cmd);

// parsing
/*peek : skip whitespace and tabs, return true if first carac == c
or False if not or if there is no carac*/
int			peek(char *c, t_minishell *g_param);
int			get_token(int save, t_minishell *g_param);
t_cmd		*parse(t_minishell *g_param);
int			quote_parsing(char *cur, int save, char quote, t_minishell *param);
void		skip_whitespace(char **cur, t_minishell *g_param);
int			dollars_parsing(char *cur, int save, char q, t_minishell *param);
char		*get_path(char *s_redircmd, t_minishell *g_param);
//void		give_token(char **cur, int *res);

//execution
int			fork1(void);
void		run_cmd(t_cmd *cmd, t_minishell *g_param);
void		execute_cmd(char **cmds, t_minishell *g_param);

//redirection util function
t_redircmd	*exchange_cmd_order(t_redircmd *rcmd);
void		ft_dup2(t_redircmd *rcmd, int std);
void		here_doc(t_redircmd *rcmd);

//builtins
bool		is_builtin(char *cmd);
bool		is_cd_export_unset(t_cmd *cmd);
void		run_cd_export_unset(t_cmd *cmd, t_minishell *g_param);
void		run_builtin(char **argv, t_minishell *g_param);
void		ft_exit(char **cmds);
int			ft_echo(char **argv);
int			ft_env(char **argv, t_minishell *g_param);
int			ft_pwd(void);
void		ft_cd(t_execcmd *cmd, t_minishell *g_param);
void		ft_export(t_execcmd *cmd, t_minishell *g_param);
void		ft_unset(t_execcmd *cmd, t_minishell *g_param);

//signal
void		handle_exit_status(int status);
void		handle_signal_before(int sig);
void		handle_signal_during_execution(int sig);
void		handle_signal_heredoc(int sig);
void		setup_parent_signals(void);

//clean
void		free_cmd(t_cmd *cmd);
void		ft_clean_all(char *line, t_minishell *g_param);
void		handle_exit(char *line, t_minishell *g_param);

//utils
char		**create_double_arr(int size);
int			len_arr(char **arr);

#endif