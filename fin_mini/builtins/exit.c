// The exit function terminates the currently running program explicitly which called it.
// The exit() function flushes all the buffers used by the program, 
//closes all the programs associated with the program calling it, and deletes all the temporary files associate with the program

// int exit(char **args)

// if (len(args) == 1)
// if args digit exit\n status (digit) (exited)
// if args alpha exit\n bash: exit: sdfsdf: numeric argument required\n (status = 2) (exited)

//else
    // if args[0] == digit && args[1] == aplha exit\n bash: exit: too many arguments\n (status = 2) (not exited)
    // if args[0] == alpha && args[1] == digit exit\n bash: exit: asdasd: numeric argument required\n (status = 2) (exited)
    // if args[0] == alpha && args[1] == alpha exit\n bash: exit: asdasd: numeric argument required\n (status = 2) (exited)
    // if args[0] == digit  && args[1] == digit exit\n bash: exit: too many arguments\n (status = 1) (not exited)


//if (*args > LLONG_MAX) exit\n bash: exit: 111111111111111111111111111111111111111: numeric argument required\n (status = 2) (exited)
int exit(char **args)
{
    unsigned int nbr;
    unsigned int nbr1;

    nbr = ft_atoi(args[1]);
    nbr1 = ft_atoi(args[2]);
    if (args[1] == NULL)
    {
        write (1, "exit\n", 6);
        exit (0);
    }
    if (args[1] != NULL && args[2] == NULL)
    {
        if (ft_is_digit(nbr))
        {
            write(1, "exit\n", 6);
            exit(nbr);
        }
        if (is_alpha(args[1]))
        {
            write(2, "exit\n", 6);
            write(2, "bash: exit: sdfsdf: numeric argument required\n", 47);
            exit(2);
        }
        else
        {
            if (ft_is_digit(nbr) && ft_is_alpha(args[2]))
            {
                write(2, "exit\n", 6);
                write(2, "bash: exit: too many arguments\n", 32);
                return (2);
            }
            if (ft_is_alpha(args[1]) && ft_is_digit(nbr1))
            {
                write(2, "exit\n", 6);
                write(2, "bash: exit: asdasd: numeric argument required\n", 47);
                exit(2);
            }
            if (ft_is_alpha(args[1]) && ft_is_alpha(args[2]))
            { 
                write(2, "exit\n", 6);
                write(2, "bash: exit: : numeric argument required\n", 47);
                exit (2);
            }
            if (ft_is_digit(nbr) && ft_is_digit(ft_atoi(nbr1)))
            {
                write(2, "exit\n", 6);
                write(2, "bash: exit: too many arguments\n", 32);
                exit (2);
            }
        }
    }
}