#see README for a manual compilation process
CC = gcc
CFLAGS = -g
OBJ = displayStat.o scheduler.o

scheduler: $(OBJ) input.c
	@echo "Creating the scheduler ..."
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c %.h
	@echo "Creating object files ..."
	$(CC) -c $< -o $@

clean:
	@echo "Deleting object and binary files ..."
	rm -rvf *.o scheduler
