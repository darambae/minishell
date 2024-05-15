/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:53:34 by dabae             #+#    #+#             */
/*   Updated: 2024/05/15 15:16:59 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
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

# define PROMPT "minishell$ "

enum e_token
{
	EXEC,
	PIPE,
	REDIR,
	ENVIRONMENT,
};

typedef struct s_type
{
	enum e_token	type;
}			t_type;

typedef struct s_execcmd
{
	enum e_token	type;
	char			*argv[10];
	char			*end_argv[10];
}				t_execcmd;

typedef struct s_env
{
	char	*name;
	char	*value;
}			t_env;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	char	*input;
	char	*output;
}			t_cmd;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	char	*input;
	char	*output;
}			t_cmd;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	char	*input;
	char	*output;
}			t_cmd;

#endif