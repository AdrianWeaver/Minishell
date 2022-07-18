#!/bin/bash
check_results(){
	test_diff1=1
	if diff .test_bash .test_minishell >/dev/null
	then
		test_diff1=0
	fi
	test_diff2=1
	if diff .test_err_bash .test_err_minishell >/dev/null
	then
		test_diff2=0
	fi

	if [[ "$test_diff1" -eq "1" || "$test_diff2" -eq "1" ]]
	then
		echo -en "\033[31mTEST FAILED: \033[m"
		echo "'$@'"
		if [[ -s ".test_bash" || -s ".test_minishell" ]]
		then
			echo "Expected output:"
			cat .test_bash | cat -e;
			echo -en "\nObtained output:\n"
			cat .test_minishell | cat -e;
			echo ""
		fi
		if [[ -s ".test_err_bash" || -s ".test_err_minishell" ]]
		then
			echo -en "\nExpected Error output:\n";
			cat .test_err_bash | cat -e;
			echo -en "\nObtained Error output:\n"
			cat .test_err_minishell | cat -e
			echo ""
		fi
	else
		echo -en "\033[32mTEST PASSED: \033[m"
		echo "$@"
	fi
}

check_err_bash_output(){
	test_err_bash_output_var=$(cat .test_err_bash | wc -l)
	sed -i 's/bash: line .*:/minishell:/g' .test_err_bash
	if [[ $test_err_bash_output_var -gt "1" ]]
	then
		sed -i '$ d' .test_err_bash
	fi
}

launch_test(){
	echo -n "$@" | bash >.test_bash 2>.test_err_bash
	check_err_bash_output $@
	echo -n "$@" | ./minishell 2>.test_err_tmp | sed -n '1!p' | sed 's/M-pM-^_M-&M-^FRubberduckersM-pM-^_M-&M-^F:/bash:/g' | sed -n '$!p' >.test_minishell
	cat .test_err_tmp | sed 's/M-pM-^_M-&M-^FRubberduckersM-pM-^_M-&M-^F:/bash:/g'  >.test_err_minishell
	rm .test_err_tmp
	check_results $@;
}

launch_env(){
	echo "launch_env started"
}

launch_pwd(){
	echo "launch_pwd started"
	launch_test "pwd"
}

launch_parsing(){
	launch_test ":"
	launch_test "!"
	launch_test ">"
	launch_test "<"
	launch_test ">>"
	launch_test "<<"
	launch_test "<>"
	launch_test ">>>>>"
	launch_test ">>>>>>>>>>>>>>>>>>"
	launch_test "<<<<<"
	launch_test "<<<<<<<<<<<<<<<<<<"
	launch_test "> > > >"
	launch_test ">> >> >> >>"
	launch_test ">>>> >> >> >>"
	launch_test "/"
	launch_test "//"
	launch_test "/."
	launch_test "/./../../../../.."
	launch_test "////////"
	launch_test "\\"
	launch_test "\\\\"
	launch_test "\\\\\\\\"
	launch_test "-"
	launch_test "|"
	launch_test "| yo"
	launch_test "| | |"
	launch_test "||"
	launch_test "||||"
	launch_test "|||||||||||||||"
	launch_test ">>|<<"
	launch_test "&&"
	launch_test "&&&&&"
	launch_test "&&&&&&&&&&&&"
	launch_test ""
	launch_test "yo"
	launch_test "'yo'"
	launch_test '"yo"'
	launch_test "yo je fais nimp"
	launch_test "Makefile"
}

launch_cd(){
	echo "launch_cd started"
}

launch_unset(){
	echo "launch_unset started"
}

launch_export(){
	echo "launch_export started"
}

launch_echo(){
	echo "launch_echo"
	launch_test "echo"
	launch_test "echo -n"
	launch_test "echo yo"
	launch_test "echoyo"
	launch_test "echo-nyo"
	launch_test "echo -n yo"
	launch_test 'echo "-n" yo'
	launch_test "echo -nyo"
	launch_test "echo yo -n" 
	launch_test "echo yo mon bichon"
	launch_test "echo                  yo"
	launch_test "echo    yo     mon    bichon"
	launch_test "\"             \" | cat -e"
	launch_test "ls | wc"
}

chose_tests(){
	if [[ "$#" -eq "0" ]]
	then
		echo "No ARGS IN INPUT"
		launch_pwd;
		launch_parsing;
		launch_cd;
		launch_unset;
		launch_export;
		launch_echo;
	fi
	if [[ "$@" == *"parsing"* ]]
	then
		launch_parsing;
	fi
	if [[ "$@" == *"cd"* ]]
	then
		launch_cd;
	fi
	if [[ "$@" == *"pwd"* ]]
	then
		launch_pwd;
	fi
	if [[ "$@" == *"env"* ]]
	then
		launch_env;
	fi
	if [[ "$@" == *"unset"* ]]
	then
		launch_unset;
	fi
	if [[ "$@" == *"export"* ]]
	then
		launch_export;
	fi
	if [[ "$@" == *"echo"* ]]
	then
		launch_echo;
	fi
}

make
chose_tests $@
