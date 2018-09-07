#ifndef TEXTURE_LOADER_HPP
#define TEXTURE_LOADER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>
#include <vector>

// Ova klasa ujedinjuje nekoliko metoda. Sve metode uzimaju path do tekstura te ih loadaju.




class TextureLoader{

    public:
        // Load a .BMP file using our custom loader
        // Ovu funkciju nisam radio ja. Loada teksture za objekte, kako je opisano u ResourceManager.h
        static GLuint loadBMP_2D(const char * imagepath);

        // Ovu funkciju jesam radio ja, a loada teksture za SkyBox.
        static GLuint loadCubemap( std::vector<std::string> faces );
};

#endif
