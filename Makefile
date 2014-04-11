CC=gcc
CFLAGSs=-g #-Wall
LIBS= -lpthread -lm
SOURCES=main.c datos.h Puente.h Puente.c carro.h carro.c cola.c params.h params.c lista.h lista.c semaforos.h oficial.h
OBJECTS=$(SOURCES:.cpp=.o)
EXE=puente

all: $(SOURCES) $(EXE)

$(EXE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $@
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -rf *o puente

#gcc main.c  -lpthread datos.h Puente.h Puente.c carro.h carro.c cola.c params.h params.c lista.h lista.c semaforos.h oficial.h -o puenteclear

