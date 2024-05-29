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

typedef struct s_minishell
{
	char	**env_variables;
}				t_minishell;

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
	char			**here_doc;
	int				mode;
	int				fd;
}				t_redircmd;

extern t_minishell	*g_param;

void 	err_msg(char *msg);

//constructor
t_cmd	*execcmd(void);
t_cmd	*redircmd(t_cmd *sub_cmd, char *s_file, char *e_file, int mode);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);
t_cmd	*nul_terminator(t_cmd *cmd);



// parsing
int		peek(char **start_str, char *end_str, char *c);
int		get_token(char **start_line, char *end_line, char **start_t, char **end_t);
t_cmd	*parse(char *line);
bool    check_closed_quotes(char *line, int num_double, int num_single);

//quote handlers
bool	valid_quote(char *line);
char	*remove_quotes(char *word);


//execution
int		fork1(void);
int    run_cmd(t_cmd *cmd);
int		execute_cmd(char **cmds);

//builtins
bool	check_builtin(char *cmd);

//signal
void    handle_signal();

#endif