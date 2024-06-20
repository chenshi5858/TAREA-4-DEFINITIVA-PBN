%module _libgrafo

%{
#include "grafo.h"
%}

%include "std_vector.i"  // Incluir la interfaz estándar de SWIG para std::vector

%template(IntVector) std::vector<int>;  // Especialización para std::vector<int>

%include "grafo.h"  // Incluir tu archivo de cabecera personalizado

