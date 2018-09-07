#ifndef CAMERA_H
#define CAMERA_H

// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

class Camera{
    
private:
        // Podaci potrebni za izradu View matricu
        // Svi ovi podaci salju se u funkciju knjiznice glm, koja vraca 4x4 matricu u mViewMatrix
        // Smisao mViewMatrix matrice je transformiranje objekata u sceni
    
        glm::vec3 mCameraPosition;              // Pozicija kamere izrazena kao vektor tri float vrijednosti
        glm::vec3 mCameraLookingAtPoint;        // Pozicija  na koju kamere gleda, izrazena kao vektor tri float vrijednosti
        glm::vec3 mCameraUpVector;              // Jedinicni vektor koji kameri govori u kojem smjeru je "vrh" scene
        glm::mat4 mViewMatrix;                  // Matrica dimenzija 4x4 koja se koristi za transformiranje scene

        // Podaci potrebni za Projection matricu
        // Svi ovi podaci salju se u funkciju knjiznice glm, koja vraca 4x4 matricu u mProjectionMatrix
        // Smisao te matrice je transformiranje scene zajedno uz mViewMatrix te matricu pojedinacnog Objekta u sceni

        float mRadius;                  // Radijus - sirina scene koja ce se vidjeti na ekranu
        float mAspectRatio;             // AspectRatio - odreduje format prikaza, tj omjer width / height
        float mNearZPlane;              // 
        float mFarZPlane;               // nearZPlane zajedno s mFarZPlane odreduju "dubinu" scene koja se vidi na ekranu
        glm::mat4 mProjectionMatrix;    // ovdje se sprema 4x4 matrica koju vraca glm funkcija. Ta matrica se koristi
                                        // za transformiranje scene...

        float mRotationSpeed;           // Brzina rotacije (oko osi) kamere
        glm::mat4 mVP;                  // ovo je umnozak mProjectionMatrix i mViewMatrix, spremam ga zasebno zato sto
                                        // mi je lakse od mnozenja projM i viewM svaki put kada mi treba

public:
        Camera();   // konstruktor, ne radi nista.

        // View setters
        // Ove funkcije koristim zato sto su mi sve member varijable privatne, pa da mogu mijenjati njihove vrijednosti.
        
        void setPosition( glm::vec3 position );
        void setLookingAtPoint( glm::vec3 lookingAtPoint );
        void setUpVector( glm::vec3 upVector );
        void setViewMatrix();
        // Projection setters
        void setRadius( float radius );
        void setAspectRatio( float aspectRatio );
        void setNearZPlane( float nearZPlane );
        void setFarZPlane( float farZPlane );
        void setProjectionMatrix();
        
        void setVP();
        
        // View getters
        // Ove funkcije, koristim da vidim trenutnu vrijednost varijabli. Klasicne getter i setter funkcije.
        
        glm::vec3 getPosition();
        glm::vec3 getLookingAtPoint();
        glm::vec3 getUpVector();
        glm::mat4 getViewMatrix();
            // by reference
        // Ovdje krsim svoje pravilo da ne zelim direktan pristup varijablama, jer ovim funkcijama dajem tocno to...
        // Ovo sam napravio kao privremeno rjesenje.
        glm::vec3& getPositionRef();
        glm::vec3& getLookingAtPointRef();
        glm::vec3& getUpVectorRef();
        glm::mat4& getViewMatrixRef();

        // Projection getters
        float getRadius();
        float getAspectRatio();
        float getNearZPlane();
        float getFarZPlane();
        glm::mat4 getProjectionMatrix();

        float& getRotationSpeedRef();
        glm::mat4 getVP();
                
        // Posebne, tj, naprednije metode...
        // Ova metoda mi rotira kameru tako da azurira njezinu poziciju koristeci parametar radius te sinus/kosinus
        // funkiju. Pogledati camera.cpp
        void rotateCamera( float radius );
        
};

#endif
