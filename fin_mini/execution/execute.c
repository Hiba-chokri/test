/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichokri <hichokri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:23:18 by hichokri          #+#    #+#             */
/*   Updated: 2024/10/16 12:34:41 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/minishell.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
#include "../include/minishell.h"
// execute a single command with its args with no pipes
// execute multiple commands with pipes
// execute a single builtin
// execute multiple builtins with a pipe
// handle signals
// handle heredoc
// finish builtins

char	*find_path(t_env_store *head)
{
	int		i;
	char	*path;

	i = 0;
	path = "PATH";
	while (head)
	{
		if (ft_strcmp(head->key, path) == 0)
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

char	**cmd_path(char **path, char *cmd)
{
	char	*path_cmd;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (access(cmd, F_OK | X_OK) == 0)
	{
		path[0] = cmd;
		return (path);
	}
	path_cmd = ft_strjoin("/", cmd);
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(tmp, path_cmd);
		free(tmp);
		i++;
	}
	free(path_cmd);
	return (path);
}

// executing one single command before piping
void execute_command(cmd_lst *command, t_env_store *head)
{
	int i;
	t_command *cmd;
	char **env_arr;
	int pid;
	char *path;
	char **cmd_p;
	char  **c_path;
	char **arg;
	int k = 0;

	 i = 0;
	 env_arr = from_lst_to_array(head);
	cmd = command->head;
	path = find_path(head); //extracting the path
	c_path = ft_split(path, ":"); // split the path by :
	pid = fork();
	
		//arg = ft_split(cmd->args, " \r\f\v\t\n");// split the command and it's args
		// while(cmd->args[k])
		// {
		// 	printf("--> %s \n",cmd->args[k]);
		// 	k++;
		// }
			if(cmd->args != NULL)
			{		
				cmd_p = cmd_path(c_path, cmd->args[0]);
				pid = fork();
				if (pid == -1)
				perror("fork error");
				if (pid == 0)
				{	
				while(cmd_p[i])
				{
					
					if (access(cmd_p[i], F_OK | X_OK) == 0)
					{
						execve(cmd_p[i], cmd->args, env_arr);
						perror("execve error");
					}
			
				i++;
				}
				}
				cmd = cmd->next;
			}
		else if(cmd->output_file_count >= 10)
		{
			open_outfiles ();
			cmd = cmd->next;
		}	
	}
	waitpid(pid,NULL,0);
}

void check_commands(cmd_lst *command, t_env_store *head)
{
    int i;
    t_command *cmd;
    int count;

    i = 0;
    cmd = command->head;
    count = count_args(cmd);
    // loop on the commands to check if they are builtins or simple command
    while (cmd)
    {
        if (count == 1)
        {
            if (is_builtin(command))
            {
                execute_builtins(command);
            }
            else
			{
                execute_command(command, head);
            }
        }
        else if (count > 1)
        {
                // is builtin
                
                // check for multiple commands
        }
        else
        {
                perror("command not found");
        }
        cmd = cmd->next;
    }
    
}
// void	child_process1(t_cmd *exec_cmd, char *cmd1, char *env[])
// {
// 	int		i;
// 	char	**cmd;

// 	i = 0;
// 	exec_cmd->infile = open(exec_cmd->argv[1], O_RDONLY);
// 	if (exec_cmd->infile == -1)
// 	{
// 		perror("opening file error");
// 		close(exec_cmd->fd[0]);
// 		close(exec_cmd->fd[1]);
// 		exit(exec_cmd->status);
// 	}
// 	exec_cmd->cmd_args = ft_split(cmd1, " \r\f\v\t\n");
// 	cmd = cmd_path(exec_cmd->cmd_path, exec_cmd->cmd_args[0]);
// 	while (cmd[i])
// 	{
// 		if (access(cmd[i], F_OK | X_OK) == 0)
// 		{
// 			dup2(exec_cmd->infile, 0);
// 			dup2(exec_cmd->fd[1], 1);
// 			close(exec_cmd->fd[0]);
// 			close(exec_cmd->fd[1]);
// 			close(exec_cmd->infile);
// 			execve(cmd[i], exec_cmd->cmd_args, env);
// 		}
// 		i++;
// 	}
// 	perror("command not found");
// 	exit(exec_cmd->status);
// }

// void	child_process2(t_cmd *exec_cmd, char *cmd2, char *env[])
// {
// 	int		i;
// 	char	**cmd;

// 	i = 0;
// 	exec_cmd->outfile = open(exec_cmd->argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (exec_cmd->outfile == -1)
// 	{
// 		perror("opening file error");
// 		exit(1);
// 	}
// 	exec_cmd->cmd_args = ft_split(cmd2, " \r\f\v\t\n");
// 	cmd = cmd_path(exec_cmd->cmd_path, exec_cmd->cmd_args[0]);
// 	while (cmd[i])////
// 	{
// 		if (access(cmd[i], F_OK | X_OK) == 0)
// 		{
// 			dup2(exec_cmd->fd[0], 0);
// 			dup2(exec_cmd->outfile, 1);
// 			close(exec_cmd->fd[0]);
// 			close(exec_cmd->fd[1]);
// 			close(exec_cmd->outfile);
// 			execve(cmd[i], exec_cmd->cmd_args, env);
// 		}
// 		i++;
// 	}
// 	perror("command not found");
// 	exit(127);
// }

// void	execute_single_command(t_cmd *exec_cmd, int argc, char *argv[], char *envp[])
// {
// 	if (argc != 1)
// 	{
// 		exec_cmd->argv = argv;
// 		if (pipe(exec_cmd->fd) < 0)
// 			perror("pipe error");
// 		exec_cmd->path = find_path(envp);
// 		exec_cmd->cmd_path = ft_split(exec_cmd->path, ":");
// 		exec_cmd->pid1 = fork();
// 		if (exec_cmd->pid1 == -1)
// 			perror("fork error");
// 		else if (exec_cmd->pid1 == 0)
// 			child_process1(exec_cmd, argv[2], envp);
// 		exec_cmd->pid2 = fork();
// 		if (exec_cmd->pid2 == -1)
// 			perror("fork error");
// 		else if (exec_cmd->pid2 == 0)
// 			child_process2(exec_cmd, argv[3], envp);
// 	}
// 	else
// 		perror("number of args incorrect");
// }