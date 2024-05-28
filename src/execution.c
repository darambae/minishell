#include "../minishell.h"

static void run_pipe(t_cmd *cmd) {
    t_pipecmd *pcmd = (t_pipecmd *)cmd;

    if (pipe(g_param->pipe_fds) < 0)
        err_msg("pipe failed");

    // Fork first child process
    g_param->child_pids[g_param->child_count] = fork1();
    if (g_param->child_pids[g_param->child_count] == 0) {
        close(g_param->pipe_fds[0]); // Close unused read end of the pipe
        dup2(g_param->pipe_fds[1], STDOUT_FILENO); // Redirect stdout to write end of the pipe
        close(g_param->pipe_fds[1]); // Close write end of the pipe
        run_cmd(pcmd->left); // Execute left command
        exit(EXIT_SUCCESS);
    }
    g_param->child_count++;

    // Fork second child process
    g_param->child_pids[g_param->child_count] = fork1();
    if (g_param->child_pids[g_param->child_count] == 0) {
        close(g_param->pipe_fds[1]); // Close unused write end of the pipe
        dup2(g_param->pipe_fds[0], STDIN_FILENO); // Redirect stdin to read end of the pipe
        close(g_param->pipe_fds[0]); // Close read end of the pipe
        run_cmd(pcmd->right); // Execute right command
        exit(EXIT_SUCCESS);
    }
    g_param->child_count++;

    // Close both ends of the pipe in the parent process
    close(g_param->pipe_fds[0]);
    close(g_param->pipe_fds[1]);

    // Wait for both child processes to finish
    waitpid(g_param->child_pids[g_param->child_count - 2], NULL, 0);
    waitpid(g_param->child_pids[g_param->child_count - 1], NULL, 0);
}


// static void	run_pipe(t_cmd *cmd, int *p, char **envp)
// {
//     t_pipecmd   *pcmd;
// 	pid_t		pid1;
// 	pid_t		pid2;
	
// 	pcmd = (t_pipecmd *) cmd;
// 	if (pipe(p) < 0)
// 		err_msg("pipe failed");
// 	g_param->child_pids[g_param->child_count] = fork1();
// 	if (g_param->child_pids[g_param->child_count] == 0)
// 	{
// 		close(1);
// 		dup(p[1]);
// 		close(p[0]);
// 		close(p[1]);
// 		run_cmd(pcmd->left, envp);
// 		exit(EXIT_SUCCESS);
// 	}
// 	g_param->child_count++;
// 	g_param->child_pids[g_param->child_count] = fork1();
// 	if (g_param->child_pids[g_param->child_count] == 0)
// 	{
// 		close(0);
// 		dup(p[0]);
// 		close(p[0]);
// 		close(p[1]);
// 		run_cmd(pcmd->right, envp);
// 		exit(EXIT_SUCCESS);
// 	}
// 	g_param->child_count++;
// 	close(p[0]);
// 	close(p[1]);
// 	waitpid(g_param->child_pids[g_param->child_count - 2], NULL, 0);
//     waitpid(g_param->child_pids[g_param->child_count - 1], NULL, 0);
// }

// static void	run_redire(t_cmd *cmd, char **envp)
// {
//     t_redircmd  *rcmd;
// 	char	*line;
// 	//int		j;

// 	rcmd = (t_redircmd *) cmd;
// 	if (rcmd->token == '{') //here_doc
// 	{
// 		line = readline("> ");
// 		//j = 0;
// 		while (ft_strcmp(line, rcmd->start_file))
// 		{
// 			//rcmd->here_doc[j++] = ft_strdup(line);
// 			line = readline("> ");
// 			add_history(line);
// 		}
// 	}
// 	else
// 	{
// 		close(rcmd->fd);
// 		if (open(rcmd->start_file, rcmd->mode) < 0)
// 		{
// 			printf("failed to open %s\n", rcmd->start_file);
// 			exit(1);
// 		}
// 	}
// 	run_cmd(rcmd->cmd, envp);
// }
static void run_redire(t_cmd *cmd) {
    t_redircmd *rcmd = (t_redircmd *)cmd;

    if (rcmd->token == '{') { // here_doc
        // Handle here_doc separately if necessary
    } else {
        if (rcmd->fd < 0) {
            perror("failed to open file for redirection");
            exit(EXIT_FAILURE);
        }
        if (rcmd->mode == O_RDONLY) {
            dup2(rcmd->fd, STDIN_FILENO);  // Redirect stdin to the file
        } else {
            dup2(rcmd->fd, STDOUT_FILENO); // Redirect stdout to the file
        }
        close(rcmd->fd); // Close the original file descriptor after dup2
    }

    run_cmd(rcmd->cmd); // Execute the command
}

void    run_cmd(t_cmd *cmd)
{	
    t_execcmd   *ecmd;

    if (!cmd)
        err_msg("cdm doesn't exist\n");
    if (cmd->type == EXEC)
    {
        ecmd = (t_execcmd *) cmd;
        if (ecmd->argv[0] == 0)
            exit(0);
        execute_cmd(ecmd->argv);
    }
    else if (cmd->type == PIPE)
		run_pipe(cmd);
    else if (cmd->type == REDIR)
		run_redire(cmd);
    exit(0);
}
