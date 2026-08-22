autofan: autofan.c
	gcc -o autofan autofan.c
fan: fan.c
	gcc -o fan fan.c
install: autofan fan
	sudo cp autofan /usr/local/bin/autofan
	sudo cp fan /usr/local/bin/fan
uninstall:
	sudo rm -f /usr/local/bin/autofan
	sudo rm -f /usr/local/bin/fan
