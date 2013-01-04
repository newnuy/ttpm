CC    = gcc -g -O
RM    = rm -rf
MV    = mv
CP    = cp -rf
STRIP = strip


exefile  = ttpm
objects  = ttpm.o points.o commonFunctions.o ver.o
dev_dir  = files
user_dir = files_backup


$(exefile): $(objects)
	$(CC) -lm -o $(exefile) $(objects)

%.o: %.c
	$(CC) -c $< -o $@

release:
	$(STRIP) $(exefile)
	$(RM) $(dev_dir)
	$(CP) $(user_dir) $(dev_dir)

.PHONY: clean
clean:
	$(RM) $(exefile) $(objects)
	$(RM) $(dev_dir)
