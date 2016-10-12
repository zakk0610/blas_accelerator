SOURCES = sgemm.c dgemm.c accelerator.c
OBJECTS =$(SOURCES:.c=.o)

.PHONY: clean

MDEBUG?=0
ifeq (${MDEBUG}, 1)
OPTION =-O0 -g3 -DMDEBUG
else
OPTION =-O3
endif

%.o: %.c
	gcc -o $@ $^ -c -fPIC ${OPTION}

blas.ldflags = $(shell python -c 'import theano; print(theano.config.blas.ldflags)')

all: clean $(OBJECTS) test
	gcc $(OBJECTS) -shared -o libmrvlblas.so -fpic ${OPTION}

test: test.c
	gcc $^ -o $@ ${blas.ldflags} ${OPTION}

clean:
	rm *.o libmrvlblas.so test -f

check: test
	LD_PRELOAD=./libmrvlblas.so ./test  2 3 10
