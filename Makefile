CC = gcc
LD = gcc
CFLAG = -O3 -Wall
LDFLAGS = -fopenmp
RM = /bin/rm -f
OBJS1 = gmlife_serial_modulo_O3.o 
OBJS2 =gmlife_parallel_modulo.o
OBJS3 =gmlife_serial_+rc_O3.o
OBJS4 = gmlife_parallel_+rc_bestVersion.o
EXECUTABLE1 =  gmlife_serial_modulo_O3
EXECUTABLE2 = gmlife_parallel_modulo
EXECUTABLE3 = gmlife_serial_+rc_O3
EXECUTABLE4 =gmlife_parallel_+rc_bestVersion
all: $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3) $(EXECUTABLE4) 

$(EXECUTABLE1): $(OBJS1)
	$(LD) $(OBJS1) -o $(EXECUTABLE1)

$(EXECUTABLE2): $(OBJS2)
	$(LD) $(LDFLAGS) $(OBJS2) -o $(EXECUTABLE2)

$(EXECUTABLE3): $(OBJS3)
	$(LD) $(OBJS3) -o $(EXECUTABLE3)

$(EXECUTABLE4): $(OBJS4)
	$(LD) $(LDFLAGS) $(OBJS4) -o $(EXECUTABLE4)
	
gmlife_serial_modulo_O3.o: gmlife_serial_modulo_O3.c
	$(CC) $(CFLAG) -c gmlife_serial_modulo_O3.c	
	
gmlife_parallel_modulo.o: gmlife_parallel_modulo.c
	$(CC) $(CFLAG) $(LDFLAGS) -c gmlife_parallel_modulo.c
	
gmlife_serial_+rc_O3.o: gmlife_serial_+rc_O3.c
	$(CC) $(CFLAG) -c gmlife_serial_+rc_O3.c
	
gmlife_parallel_+rc_bestVersion.o: gmlife_parallel_+rc_bestVersion.c
	$(CC) $(CFLAG) $(LDFLAGS) -c gmlife_parallel_+rc_bestVersion.c

clean:
	$(RM) $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3) $(EXECUTABLE4) $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4)
	
