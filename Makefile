autofan: autofan.c
	gcc -o autofan autofan.c
install: autofan
	sudo cp autofan /usr/local/bin/autofan
uninstall:
	sudo rm -f /usr/local/bin/autofan
