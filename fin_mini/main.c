/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichokri <hichokri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:40:52 by hichokri          #+#    #+#             */
/*   Updated: 2024/10/16 12:03:36 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
// To compile pars/tok part:
// gcc main.c include/minishell.h token_parsing/expantion.c token_parsing/parsing.c token_parsing/tokenization.c utils/utils.c


// Global variable for last exit status
int g_last_exit_status = 0;

// Main function
int main(int argc, char *argv[], char **env) {
    char *input;
    t_env_store *head;
    token_lst *tokens;
    cmd_lst *commands;

     while (1) {
     printf("minishell> ");
    // t_cmd exec_cmd;
	// int		status;
	
	// // execute_single_command(&exec_cmd, argc, argv, envp);
        input = read_input();
        if (input == NULL) {
            if (feof(stdin)) {
                printf("\nExiting...\n");
                break;
            } else {
                perror("read_input");
                continue;
            }
        }
        
        if (ft_strlen(input) == 0 || isspace(input[0])) {
            free(input);
            continue;
        }

        tokens = tokenize(input);
        if (tokens == NULL) {
            free(input);
            continue;
        }

        commands = parse(tokens);
        if (commands == NULL) {
            free(input);
            free_tokens(tokens);
            continue;
        }
        // 
        // command printing logic

       // Here, where i would pass the commands list to the execution function
       // For now, we'll just print the commands!!
        
        t_command *cmd = commands->head;
           head = env_var_add(env);
         if(head == NULL)
            printf("hello\n");
            int i = 0;
        while (cmd) {
            printf("Command %d:\n", i);
            for (int j = 0; j < cmd->arg_count; j++) 
                printf("  Arg %d: %s\n", j, cmd->args[j]);
            for (int j = 0; j < cmd->input_file_count; j++)
                printf("  Input file %d: %s\n", j, cmd->input_files[j]);
            for (int j = 0; j < cmd->output_file_count; j++)
                printf("  Output file %d: %s\n", j, cmd->output_files[j]);

            for (int j = 0; j < cmd->heredoc_count; j++)
                printf("  Heredoc delimiter %d: %s\n", j, cmd->heredoc_delimiters[j]);

            cmd = cmd->next;
            i++;
        }
        execute_command(commands, head);
        // close(exec_cmd.fd[0]);
	// close(exec_cmd.fd[1]);
	 //waitpid(exec_cmd.pid1, &status, 0);
	// waitpid(exec_cmd.pid2, &status, 0);
	// return (WEXITSTATUS(status));
     
        // open_files(cmd);
        // check if the count_args is working
    //     cmd = commands->head;
    // //    int count = count_args(cmd);
    //    printf("%d\n", count);
       /////////////////////////////
     // check if env is stored in the linked list
       // display_env_values(env, head);
       //////////////////////////////////////
            // char ** arr = from_lst_to_array(head);
            // int k = 0;
            // while (arr[k])
            // {
            //     printf("->>%s\n", arr[k]);
            //     k++;
            // }
        //  printf("%s\n",find_path(head));
        ////////////////////
        // print the node value
        
        // print the key in value in find path
        free(input);
        free_tokens(tokens);
        free_commands(commands);
    }
    return (0);
}

// Reads a line of input from the user and returns it as a string
char *read_input() {
    char *input = NULL;
    size_t bufsize = 0;
    ssize_t characters = getline(&input, &bufsize, stdin); // this should be changed readlin
    
    if (characters == -1) {
        if (feof(stdin)) {
            free(input);
            return (NULL);  // EOF (Ctrl+D)
        } else {
            perror("getline");
            free(input);
            return (NULL);
        }
    }

    if (input[characters - 1] == '\n') 
        input[characters - 1] = '\0';

    return (input);
}

// t_error *error;

// int main(int argc, char **argv, char **env) {

//     (void)argc;
//     (void)argv;
//     char *input;
//    // t_command *command;
  
//     //command = NULL;
//     error = NULL;
//     t_env_store *env_list = NULL;
//     while (1)
//     {
//         // if(!env)
//         //     // create my own env_list
//         // else    
        
//         input = readline("minishell>");
//         if (input)
//             add_history(input);
//         if (ft_strncmp(input, "exit", 4) == 0)
//         {
//             free(input);
//             break;
//         }
//         env_list = env_var_add(env);
//         // command = ft_parser(input);
//         // if (!ft_error())
//         //     continue;
//         // t_command *tmp = command;
//         // int i;
//         // while (tmp)
//         // {
//         //     printf("command=%s\n", tmp->command);
//         //     i = 0;
//         //     if (tmp->args)
//         //     while (tmp->args[i])
//         //     {
//         //         printf("args=%s\n", tmp->args[i]);
//         //         i++;
//         //     }
//         //     t_redirection *t = tmp->redirection;
//         //     while (t)
//         //     {
//         //         printf("file=%s id=%d\n", t->file,
//         //             t->identifer);
//         //             t= t->next;
//         //     }
//         //     tmp = tmp->next;
//         // } 
//         // ft_free_command(&command); 
//         // free(input);
//     }
//     //ft_free_command(&command); 
//     return 0;
// }