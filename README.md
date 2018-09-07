# ReklamaEngine
U common se nalaze sve koristene funkcije i knjiznice.
U objects se nalaze modeli svih objekata.
U shaders se nalaze svi parovi vertex i fragment shadera.
U teksturi se nalaze Skybox teksture i obicne teksture za objekte.

main.cpp je glavni dio programa. Iz programa se izlazi pritiskom na ESC tipku.

Program se kompajlira preko:

g++ -std=c++17 main.cpp common/*.cpp -lglfw -lassimp -lGLU -lGL -lGLEW

Iz naredbe je vidljivo da je za uspjesno kompajliranje potrebno imati glfw, assimp, glew knjiznice.
