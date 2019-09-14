# ReklamaEngine
## Potrebni paketi:
- glew
- glfw
- glm
- assimp

U common se nalaze sve koristene funkcije i knjiznice.

U objects se nalaze modeli svih objekata.

U shaders se nalaze svi parovi vertex i fragment shadera.

U teksturi se nalaze Skybox teksture i obicne teksture za objekte.

## Program se kompajlira preko:
g++ -std=c++17 main.cpp common/*.cpp -lglfw -lassimp -lGLU -lGL -lGLEW
## Kontrole:
- ESC - izlazi iz programa
