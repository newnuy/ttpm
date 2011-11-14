CC    = gcc -g -O
RM    = rm -rf
STRIP = strip


exefile = ttpm
objects = ttpm.o points.o ver.o


ttpr: $(objects)
	$(CC) -o $(exefile) $(objects)

%.o: %.c
	$(CC) -c $< -o $@

release:
	$(STRIP) $(exefile)

.PHONY: clean
clean:
	$(RM) $(exefile) $(objects)
