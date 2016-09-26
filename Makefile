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

blas.ldflags = -L/home/zakk/anaconda2/lib -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5 -lpthread -lm -Wl,-rpath,/home/zakk/anaconda2/lib

all: clean $(OBJECTS) test
	gcc $(OBJECTS) -shared -o libmrvlblas.so -fpic ${OPTION}

test: test.c
	gcc $^ -o $@ ${blas.ldflags} -g3 ${OPTION}

clean:
	rm *.o libmrvlblas.so test -f
