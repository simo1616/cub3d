#include "cub3d.h"

void error_and_exit(char *msg)
{
    ft_putstr_fd("Error\n", 2);
    ft_putstr_fd(msg, 2);
    exit(EXIT_FAILURE);
}

void	error_and_exit_free(char **tokens, char *msg)
{
	free_split(tokens);
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

// void	error_and_exit_free(void *arg, char *msg)
// {
// 	free(str);
// 	ft_putstr_fd(msg, 2);
	
// 	exit(EXIT_FAILURE);
// }

void	check_color_value(int value)
{
	if (value < 0 || value > 255)
	{
		ft_putstr_fd("Error:\nCouleur invalide: ", 2);
		ft_putnbr_fd(value, 2);
		ft_putchar_fd('\n', 2);
		exit(EXIT_FAILURE);
	}
}
