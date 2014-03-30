CC=gcc
CFLAGSs=-g #-Wall
LIBS=-lpthread
SOURCES=main.c datos.h Puente.h Puente.c carro.h carro.c cola.c params.h params.c lista.h lista.c
OBJECTS=$(SOURCES:.cpp=.o)
EXE=puente

all: $(SOURCES) $(EXE)

$(EXE): $(OBJECTS)
	$(CC) $(LIBS) $(OBJECTS) -o $@
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -rf *o puente
