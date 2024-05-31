#include "../minishell.h"

t_redircmd	*exchange_cmd_order(t_redircmd *rcmd)
{
	t_redircmd	*rcmd2;
	t_cmd		*cmd3;

	rcmd2 = (t_redircmd *) rcmd->cmd;
	cmd3 = rcmd2->cmd;
	if (rcmd2->token == '{')
	{
		rcmd->cmd = cmd3;
		rcmd2->cmd = (t_cmd *) rcmd;
		return (rcmd2);
	}
	return (rcmd);
}
