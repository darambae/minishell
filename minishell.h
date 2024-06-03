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
	ENVIRONMENT,
};



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
}				t_minishell;
extern t_minishell	*g_param;

void 	err_msg(char *msg);

//constructor
t_cmd	*execcmd(void);
t_cmd	*redircmd(t_cmd *sub_cmd, int mode);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);
t_cmd	*nul_terminator(t_cmd *cmd);
void	ft_clean_all(void);

// parsing
/*peek : skip whitespace and tabs, return true if first carac == c or False if not
or if there is no carac*/
int		peek(char *c);
int		get_token(int save);
t_cmd	*parse(char *line);
int		quote_parsing(char *cur, int save, char quote);
void	skip_whitespace(char **cur);
int		dollars_parsing(char *cur, int save, char quote);
char	*get_path(char *s_redircmd);

//quote handlers
bool	valid_quote(char *line);
char	*remove_quotes(char *word);


//execution
int				fork1(void);
t_minishell		*run_cmd(t_cmd *cmd);
void			execute_cmd(char **cmds);

//redirection util function
t_redircmd	*exchange_cmd_order(t_redircmd *rcmd);
void	ft_dup2(t_redircmd *rcmd, int std);
void	here_doc(t_redircmd *rcmd);

//builtins
bool		is_builtin(char *cmd);
bool	is_cd_export_unset(t_cmd *cmd);
void	run_cd_export_unset(t_cmd *cmd);

t_minishell	*run_builtin(char **argv);
void		ft_exit(char **cmds, int exit_code);
int			ft_echo(char **argv);
int			ft_env(char **argv);
int			ft_pwd(void);
t_minishell		*ft_cd(char **argv);
//signal
void	handle_exit_status(int status);
void	handle_signal_before(int sig);
void	handle_signal_after(int sig);

#endif
