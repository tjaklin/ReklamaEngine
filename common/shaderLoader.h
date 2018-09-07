#ifndef SHADER_LOADER_HPP
#define SHADER_LOADER_HPP

// Ova Funkcija uzima put do shadera te ih loada u memoriji, a vraca GLuint koji sadrzi adresu loadanih shadera
// Funkciju nisam napravio ja, skinuo sam je s neta.
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif
