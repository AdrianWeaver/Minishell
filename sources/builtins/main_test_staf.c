/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_staf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@42.fr>                     +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:50:56 by aweaver           #+#    #+#             */
/*   Updated: 2022/06/27 16:46:16 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	t_env	**env_list;
	char	**unset_tester;
	char	**export_tester;
	int		ret;
	int		export_ret;

	(void)argc;
	(void)argv;
	env_list = malloc(sizeof(*env_list) * 1);
	//unset_tester = ft_split("_toto", ' ');
	unset_tester = ft_split("MAIL USER GIT_PROMPT_EXECUTABLE SHLVL WT_PROFILE_ID LD_LIBRARY_PATH HOME OLDPWD MAKEFLAGS WSL_DISTRO_NAME MAKE_TERMERR WAYLAND_DISPLAY LOGNAME _ WSL_INTEROP PULSE_SERVER NAME TERM HISTCONTROL PATH XDG_RUNTIME_DIR WT_SESSION MAKELEVEL GLIBCPP_FORCE_NEW DISPLAY LANG __GIT_PROMPT_DIR SHELL MAKE_TERMOUT PWD XDG_DATA_DIRS MFLAGS HOSTTYPE WSLENV GLIBCXX_FORCE_NEW LD_PRELOAD", ' ');
	//export_tester = ft_split("fix=fuxk fix=bisou", ' ');
	export_tester = ft_split("h=notvisible h=Im:a:path h2 h3=sta h3_+=rt", ' ');
	*env_list = ft_env_to_list(env);
	ft_print_env(*env_list);
	printf("Printing whole env just above ^^^^^^^^^^^\n");
	ret = ft_unset(env_list, unset_tester);
	ft_print_env(*env_list);
	printf("Printing unset env just above ^^^^^^^^^^^\n");
	ft_print_env(*env_list);
	export_ret = ft_export(env_list, export_tester);
	ft_print_env(*env_list);
	printf("Printing env after export just above ^^^^^^^^^^^\n");
	//ft_print_pwd();
	//ft_free_env(env_list);
	ft_free_double_array(unset_tester);
	ft_free_double_array(export_tester);
	printf("\33[0;32mUnset returned : %d\n\33[0m", ret);
	//printf("\33[0;32mexport returned : %d\n\33[0m", export_ret);
	free(env_list);
	ft_magic_malloc(FLUSH, 0, NULL);
	return (0);
}
