CC = g++
CXXFLAGS = -fPIC
rutapython = /usr/include/python3.8
libreria = _libgrafo.so

all: $(libreria)

$(libreria): grafo_wrap.o grafo.o
	$(CC) -shared grafo_wrap.o grafo.o -o $(libreria) -lpython3.8

grafo_wrap.cxx: grafo.i grafo.h
	swig -python -c++ grafo.i

grafo_wrap.o: grafo_wrap.cxx
	$(CC) $(CXXFLAGS) -c grafo_wrap.cxx -o grafo_wrap.o -I$(rutapython)

grafo.o: grafo.cpp grafo.h
	$(CC) $(CXXFLAGS) -c -o grafo.o grafo.cpp

clean:
	rm -f *.o $(libreria) grafo_wrap.cxx grafo.py
	rm -rf __pycache__

.PHONY: all clean
