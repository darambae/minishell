/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:31:22 by dabae             #+#    #+#             */
/*   Updated: 2024/06/27 15:17:55 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_arg_to_clean(t_minishell *param)
{
	int	i;

	i = 0;
	while (param->arg_to_clean[i])
	{
		free(param->arg_to_clean[i]);
		param->arg_to_clean[i] = NULL;
		i++;
	}
	free(param->arg_to_clean);
	param->arg_to_clean = NULL;
	// param->arg_to_clean = malloc(sizeof(char *));
	// if (!param->arg_to_clean)
	// 	ft_error("malloc failed in ft_clean_all function", 1);
	// param->arg_to_clean[0] = NULL;
}

static void	free_rcmd(t_cmd *cmd)
{
	t_redircmd	*rcmd;

	if (!cmd)
		return ;
	rcmd = (t_redircmd *) cmd;
	if (rcmd->token == '{')
		unlink(rcmd->start_file);
	if (rcmd->cmd)
		free_cmd(rcmd->cmd);
	free(rcmd);
	rcmd = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	t_pipecmd	*pcmd;

	if (cmd->type == EXEC)
	{
		free(cmd);
		cmd = NULL;
	}
	else if (cmd->type == REDIR)
		free_rcmd(cmd);
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *) cmd;
		if (pcmd->left)
			free_cmd(pcmd->left);
		if (pcmd->right)
			free_cmd(pcmd->right);
		free(pcmd);
		pcmd = NULL;
	}
}

void	ft_clean_all(char *line, t_minishell *param)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
	if (param)
	{
		if (param->first_cmd)
		{
			free_cmd(param->first_cmd);
			param->first_cmd = NULL;
		}
		if (param->arg_to_clean)
			init_arg_to_clean(param);
		if (param->cmd_line)
		{
			free(param->cmd_line);
			param->cmd_line = NULL;
		}
	}
}

void	handle_exit(char *line, t_minishell *param)
{
	char	**arr;

	printf("exit\n");
	if (line && ft_strncmp(line, "exit", 4) == 0)
	{
		arr = ft_split(line, ' ');
		ft_exit(arr);
		ft_free_tab(arr);
	}
	if (param->env_variables)
		ft_free_tab(param->env_variables);
	if (param->save_out)
		close(param->save_out);
	if (param->save_in)
		close(param->save_in);
	ft_clean_all(line, param);
	free(param->arg_to_clean);
	param->arg_to_clean = NULL;
	free(param);
	param = NULL;
	exit(g_exit_status);
}
