/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:31:25 by dabae             #+#    #+#             */
/*   Updated: 2024/06/28 11:28:01 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*create nodes for EXEC, REDIC, PIPE*/
t_cmd	*execcmd(void)
{
	t_execcmd	*execcmd;

	execcmd = (t_execcmd *)malloc(sizeof(*execcmd));
	if (!execcmd)
		return (NULL);
	ft_memset(execcmd, 0, sizeof(*execcmd));
	execcmd->type = EXEC;
	return ((t_cmd *)execcmd);
}

int	redir_file(t_redircmd *redircmd, int token)
{
	if (token == '[')
		redircmd->mode = O_RDONLY;
	else if (token == ']')
		redircmd->mode = O_RDWR | O_CREAT | O_TRUNC;
	else if (token == '{')
		redircmd->mode = O_RDWR | O_CREAT | O_APPEND;
	else if (token == '}')
		redircmd->mode = O_RDWR | O_CREAT | O_APPEND;
	else
		return (ft_error("syntax error near unexpected token", 1));
	return (0);
}

/*?*/
t_cmd	*multiple_redire(t_cmd *sub_cmd, t_redircmd *last_rcmd)
{
	t_redircmd	*first_rcmd;

	first_rcmd = (t_redircmd *)sub_cmd;
	while (first_rcmd->cmd->type == REDIR)
		first_rcmd = (t_redircmd *)first_rcmd->cmd;
	if (first_rcmd->cmd->type == EXEC)
	{
		last_rcmd->cmd = first_rcmd->cmd;
		first_rcmd->cmd = (t_cmd *)last_rcmd;
	}
	return (sub_cmd);
}

t_cmd	*redircmd(t_cmd *sub_cmd, int token, t_minishell *param)
{
	t_redircmd	*redircmd;

	redircmd = (t_redircmd *)malloc(sizeof(*redircmd));
	if (!redircmd)
	{
		ft_error("malloc", 1);
		exit(g_exit_status);
	}
	ft_memset(redircmd, 0, sizeof(*redircmd));
	redircmd->type = REDIR;
	redircmd->start_file = param->start_t;
	redircmd->end_file = param->end_t;
	redircmd->token = token;
	redir_file(redircmd, token);
	if (sub_cmd->type == EXEC)
		redircmd->cmd = sub_cmd;
	if (sub_cmd->type == REDIR)
		return (multiple_redire(sub_cmd, redircmd));
	return ((t_cmd *) redircmd);
}

t_cmd	*pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*pipecmd;

	pipecmd = (t_pipecmd *)malloc(sizeof(*pipecmd));
	ft_memset(pipecmd, 0, sizeof(*pipecmd));
	pipecmd->type = PIPE;
	pipecmd->left = left;
	pipecmd->right = right;
	return ((t_cmd *)pipecmd);
}
