%module libgrafo

%{
#include "grafo.h"
%}

%include "std_vector.i"  
%template(IntVector) std::vector<int>;  
%include "grafo.h"
