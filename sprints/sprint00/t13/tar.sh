if [[ $1 == "-c" ]]; then
	tar -cjvf $2 $@
elif [[ $1 == "-e" ]]; then
	tar -xf $2
fi
