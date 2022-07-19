
#include "minishell.h"

int	ft_check_cmd(char * cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		write(2, "minishell: command not found\n", 29);
		return (-1);
	}
	if (access(cmd, X_OK) == -1)
	{
		ft_eprintf("minishell: permission denied: %s\n", cmd);
		return (-1);
	}	
	return (0);
}