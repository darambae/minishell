#include "../minishell.h"

t_redircmd	*exchange_cmd_order(t_redircmd *rcmd)
{
	t_redircmd	*rcmd2;
	t_cmd		*cmd3;

	rcmd2 = NULL;
	cmd3 = NULL;
	if (rcmd->cmd->type != REDIR)
		return (rcmd);
	rcmd2 = (t_redircmd *) rcmd->cmd;
	cmd3 = rcmd2->cmd;
	if (rcmd2->token == '{')//if second redire = here_doc
	{
		rcmd->cmd = cmd3;
		rcmd2->cmd = (t_cmd *) rcmd;
		return (rcmd2);//here_doc in first, redir outfile in second
	}
	return (rcmd);
}
