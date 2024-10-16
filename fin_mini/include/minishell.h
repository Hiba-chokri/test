

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <fcntl.h>
#define PATH_MAX 1024

// Global var for exit status.
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// Global var for exit status.
extern int g_last_exit_status;

typedef enum {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_REDIRECT_APPEND,
    TOKEN_HEREDOC,
} token_type;

typedef struct s_token {
    token_type      type;
    char            *value;
    struct s_token  *next;
} t_token;

typedef struct {
    t_token *head;
    t_token *tail;
    int count;
} token_lst;

typedef struct s_command {
    char **args;
    int arg_count;
    int arg_capacity;
    char **input_files;
    int input_file_count;
    char **output_files;
    int output_file_count;
    char **heredoc_delimiters;
    int heredoc_count;
    struct s_command *next;
} t_command;


typedef struct s_cmd_lst
{
    t_command *head;
    t_command *tail;
    int count;
} cmd_lst;

typedef struct s_env_store
{
    char *key;
    char *value;
    struct s_env_store *next;
    struct s_env_store *prev;
} t_env_store;

// Function prototypes
char *read_input();
char	*find_path(t_env_store *head);
char **from_lst_to_array(t_env_store *head);
int is_builtin(cmd_lst *command);
token_lst *tokenize(char *input);
void    execute_builtins(cmd_lst *command);
void execute_command(cmd_lst *command, t_env_store *head);
char *expand_variables(char *str);
cmd_lst *parse(token_lst *tokens);
void free_tokens(token_lst *tokens);
void free_commands(cmd_lst *commands);

// New function prototypes
void open_files(t_command *command);
void handle_syntax_error(const char *message);
void check_commands(cmd_lst *command, t_env_store *head);
void    execute_builtins(cmd_lst *command);
int is_builtin(cmd_lst *command);
void	*free_str(char **tab, int c);
int is_valid_variable_char(char c);
void init_tokenize(token_lst **tokens, char **current_token);
void handle_non_quote(token_lst *tokens, char **current_token, int *current_token_len, char **token_end);
void handle_quote(char **current_token, int *current_token_len, char **token_end, int *in_quotes, char *quote_char);
void add_token(token_lst *tokens, char *current_token, int *current_token_len, token_type type, const char *value);
void handle_special_char(token_lst *tokens, char **token_end, char *current_token, int *current_token_len);
void handle_character(int *in_quotes, char *quote_char, char **token_end, char *current_token, int *current_token_len);
token_lst *finalize_tokenization(token_lst *tokens, char *current_token, int current_token_len, int in_quotes);
void init_command(t_command *command);
int handle_token(cmd_lst *commands, t_command **current_command, t_token *token);
int handle_word_token(t_command *command, t_token *token);
int handle_pipe_token(cmd_lst *commands, t_command **current_command);
int handle_redirection_token(t_command *command, t_token *token);
cmd_lst *finalize_parsing(cmd_lst *commands, t_command *current_command);
char *handle_command_substitution(char **write_ptr, char *read_ptr, size_t max_len);
char *handle_braced_variable(char **write_ptr, char *read_ptr, size_t max_len);
char *handle_variable_expansion(char **write_ptr, char *read_ptr, size_t max_len);
char *trim_white_space(char *str);
int ft_strcmp(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
char	**cmd_path(char **path, char *cmd);
char *handle_env_var(char *cmd, char **write_ptr, size_t max_len, char *read_ptr);

// Global variable for last exit status
extern int g_last_exit_status;
// execution

int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr(char *s, int fd);
void ft_free(char **str);
void				ft_putstr(char *s, int fd);
int					ft_isdigit(int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strdup(const char *s);
int					ft_strlen(char *str);
long                ft_atoi(char *nptr);
char *ft_strndup(char *s, size_t n);
char	**ft_split(char *str, char *charset);
char				*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcat(char *dest, char *src, size_t size);
char                *ft_substr(char *s, unsigned int start, size_t len);
size_t				ft_strlcpy(char *dst, char *src, size_t size);



/* FUNCTIONS */
void display_env_values(char **env, t_env_store *head);
int calculate_size(t_env_store *head);
int count_args(t_command *cmd);
void add_back_to_env_list(t_env_store **head, t_env_store *node_to_add);
t_env_store	*env_node(char *key, char *value);
int sort_export_vars(char **env, char *argv[], t_env_store *head);
void add_values_exp(char **env, char **argv, t_env_store **head);
void print_exp_vars(char **env, char *argv[]);
t_env_store 	*env_var_add_export(char **env, char *argv[]);
t_env_store *env_var_add(char **envp);
void	free_node(t_env_store *node);
char	*find_path(t_env_store *head);
#endif 