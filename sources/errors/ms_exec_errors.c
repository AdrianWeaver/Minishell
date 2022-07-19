
#include "minishell.h"

int	ft_error(char *file)
{
	dup2(2, STDOUT_FILENO);
	ft_printf("%s: %s\n", strerror(errno), file);
	return (-1);
}