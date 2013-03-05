CC = gcc
SRC = simple-gpio.c
EXE = simple-gpio


all: $(EXE)

$(EXE):
	$(CC) -o $(EXE) $(SRC)
	chown root:root $(EXE)
	chmod +x,u+s $(EXE)

.PHONY: clean
clean: 
	rm -f $(EXE)