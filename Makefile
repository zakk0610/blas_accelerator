SOURCES = sgemm.c dgemm.c
OBJECTS =$(SOURCES:.c=.o)

.PHONY: clean

%.o: %.c
	gcc -o $@ $^ -c -O0 -fPIC -g3

blas.ldflags = -L/home/zakk/anaconda2/lib -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5 -lpthread -lm -Wl,-rpath,/home/zakk/anaconda2/lib

all: $(OBJECTS)
	gcc $(OBJECTS) -shared -o libmrvlblas.so -fpic

test: test.c
	gcc $^ -o $@ ${blas.ldflags} -g3

clean:
	rm *.o libmrvlblas.so
