
#include "../include/minishell.h"
// step 1: check if it's a builtin
// int is_cmd(cmd_lst *command)
// {
//     t_command *cmd;
//     int i;

//     cmd = command->head;

//     if (access(cmd->args[0], F_OK | X_OK) == 0)
//         return 1;
//     else
//         return (0);
// }

int is_builtin(cmd_lst *command)
{
    t_command *cmd;

    cmd = command->head;
    if(ft_strcmp(cmd->args[0], "echo") == 0)
        return (1);
    if(ft_strcmp(cmd->args[0], "cd") == 0)
        return (1);
    if(ft_strcmp(cmd->args[0], "pwd") == 0)
        return (1);
    if(ft_strcmp(cmd->args[0], "exit") == 0)
        return (1);
    if(ft_strcmp(cmd->args[0], "unset") == 0)
        return (1);
    if(ft_strcmp(cmd->args[0], "env") == 0)
        return (1);
    else
        return (0);
}

void    execute_builtins(cmd_lst *command)
{
     t_command *cmd;

    cmd = command->head;
    if(ft_strcmp(cmd->args[0], "echo") == 0)
        echo_n(cmd->args[0]);
    if(ft_strcmp(cmd->args[0], "cd") == 0)
        change_dir(cmd->args[0]);
     if(ft_strcmp(cmd->args[0], "pwd") == 0)
        pwd(cmd->args[0]);
     if(ft_strcmp(cmd->args[0], "exit") == 0)
        exit(cmd->args[0]);
    if(ft_strcmp(cmd->args[0], "unset") == 0)
        unset(cmd->args[0]);
     if(ft_strcmp(cmd->args[0], "env") == 0)
        env(cmd->args[0]); 
}
// execute single simple command 
// void execute_simple_cmd(cmd_lst *command, t_env_store *path)
// {
//     int pid1;
//     char **cmd_path;
//     char *f_path;

//     pid1 = fork();
//     if (pid1 == 0)
//     {
//         f_path = find_pat(path);
//         // 
//     }
// }
// execute multiliple builtins 
