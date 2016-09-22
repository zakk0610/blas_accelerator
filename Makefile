SOURCES = sgemm.c dgemm.c
OBJECTS =$(SOURCES:.c=.o)

%.o: %.c
	gcc -o $@ $^ -c -O3 -fPIC

all: $(OBJECTS)
	gcc $(OBJECTS) -shared -o libmrvlblas.so -fpic

clean:
	rm *.o libmrvlblas.so
