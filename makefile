CC = g++
CXXFLAGS = -fPIC
PYTHON_INCLUDE = /usr/include/python3.8
PYTHON_LIB = /usr/lib/python3.8/config-3.8-x86_64-linux-gnu
TARGET = _libgrafo.so

all: $(TARGET)

$(TARGET): grafo_wrap.o grafo.o
	$(CC) -shared grafo_wrap.o grafo.o -o $(TARGET) -L$(PYTHON_LIB) -lpython3.8

grafo_wrap.o: grafo_wrap.cxx
	$(CC) $(CXXFLAGS) -c grafo_wrap.cxx -o grafo_wrap.o -I$(PYTHON_INCLUDE)

grafo_wrap.cxx: grafo.i grafo.h
	swig -python -c++ grafo.i

grafo.o: grafo.cpp grafo.h
	$(CC) $(CXXFLAGS) -c -o grafo.o grafo.cpp

clean:
	rm -f *.o $(TARGET) grafo_wrap.cxx libgrafo.py
	rm -rf __pycache__

.PHONY: all clean
