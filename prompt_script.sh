#!/bin/bash

print_file(){
		echo "FILE="
		cat -e $@
		echo -e "\nEND OF FILE.\n"
}

clean_output(){
	printf '%s\n' "$@"
	sed "s,/,\\\/,g" <<<"$@"
	var=$@
	if [[ -s ".testy" ]]
	then
		print_file .testy
		prompt=$(cat .testy | sed -n '1p' | sed "s/$var//g")
	#ABOVE GETS PROM
		prompt=$(echo "$prompt" | sed "s,/,\\\/,g")
		sed -i '1d' .testy
		sed -i "\$ s/$prompt//g" .testy
		#output=$(cat .testy | sed '1d' | sed "\$ s/$prompt//g")
		#echo "$output"
		print_file .testy
	fi
}

launch_test(){
echo "variable ="
printf '%s' "$1"
echo "end of var"
printf '%s' "$@" | ./minishell > .testy
clean_output $@
}


launch_test 'yo'
