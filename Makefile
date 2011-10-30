CC    = gcc -g
RM    = rm -rf
STRIP = strip


objects = ttpm.o points.o


ttpr: $(objects)
	$(CC) -o ttpm $(objects)

%.o: %.c
	$(CC) -c $< -o $@

release:
	$(STRIP) ttpm

.PHONY: clean
clean:
	$(RM) ttpm $(objects)
