#ifndef SCENE_EDITOR_H
#define SCENE_EDITOR_H

// Include Dear ImGui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
// Include glm::type_ptr
#include <glm/gtc/type_ptr.hpp>

// Ovdje deklariram neke podatke koji se koriste za testiranje

    // za Camera
    float   camera_Position[3] = { 30.0f, 5.0f, -30.0f };
    float   camera_RotationSpeed = 4.0f;
    bool    camera_Rotate = false;
    // za Skybox
    static int skybox_SelectedTexture = 0;
    const char* skybox_LoadButton = "Load Texture";
    char skybox_LoadPath[64];
    // za Models
    static int objects_SelectedModel = 0;
    float   objects_Position[3] = { 3.0f, 0.0f, -3.0f };
    float   objects_Scale[3] = { 1.0f, 1.0f, 1.0f };
    float   objects_RotationSpeed = 0.0f;
    float   objects_Destination[3] = { -3.0f, 5.0f, 3.0f };

void imguiSetup(){
    // Stvara imgui kontekst kako bi se imgui knjiznice mogle koristiti
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& mIO = ImGui::GetIO();(void)mIO;
    ImGui_ImplGlfw_InitForOpenGL( window, true );
    ImGui_ImplOpenGL3_Init( "#version 130" );
    // Setup Dark style
    ImGui::StyleColorsDark();
}

void imguiCreateFrame(){
    // Stvaranje novog frame-a
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
}

void imguiCreateCameraSection( Camera* &recordingCamera, GameObject* &skyboxObject, std::vector< Model* > &sceneObjects  ){
    // Ovdje se stvara panel 'Properties' koji se vidi na videu, a u njega se stavljaju sve relevantne opcije
    
    imguiCreateFrame();
    ImGui::Begin("Properties");
        if ( ImGui::TreeNode("Camera:") )
        {
            ImGui::Text("Set various Camera properties.");
            ImGui::SliderFloat3( "Position", glm::value_ptr( recordingCamera->getPositionRef() ), -40.0f, 40.0f );
            ImGui::SliderFloat( "RotationSpeed", &recordingCamera->getRotationSpeedRef(), 0.0f, 1.0f );
            ImGui::TreePop();
        }
        if ( ImGui::TreeNode("Skybox:") )
        {
                // OVO JE SPREMNO ZA UPORABU!
            std::vector <const char*> skybox_TextureList = ResourceManager::listLoadedSkyboxTextures();
            ImGui::ListBox("", &skybox_SelectedTexture , &skybox_TextureList[0], skybox_TextureList.size(), 4 );
            ImGui::SameLine();
                if ( ImGui::Button( "Load Texture" ) )
                {
                    skyboxObject->setTexture( ResourceManager::getSkyboxTexture( skybox_TextureList[ skybox_SelectedTexture ] ) );
                }
            ImGui::TreePop();
        }
        if ( ImGui::TreeNode("Objects:") )
        {
            ImGui::Text("Set various Object properties.");
            for ( int i = 0; i < sceneObjects.size(); i++ )
            {
                std::string foo = "Object" + std::to_string( i );
                if ( ImGui::TreeNode( foo.c_str() ) )
                {
                    // Ovdje treba napisati kod koji ce manipulirati pozicijom, rotacijom, skaliranjem te smjerom
                    // kretanja. Za NADOGRADITI!
//                     if ( ImGui::TreeNode( "Load Another Model:" ) )
//                     {
                        ImGui::SliderFloat3( "Position", glm::value_ptr( sceneObjects[i]->getTranslateVectorRef() ), -5.0f, 5.0f );
                        ImGui::SliderFloat( "Scale", &sceneObjects[i]->getScaleFactorRef(), -5.0f, 5.0f );
                        ImGui::SliderFloat3( "Rotation", glm::value_ptr( sceneObjects[i]->getRotateVectorRef() ), -5.0f, 5.0f );
                        std::vector <const char*> objects_ModelList = ResourceManager::listLoadedPathsToModels();
                        ImGui::ListBox("", &objects_SelectedModel, &objects_ModelList[0], objects_ModelList.size(), 4 );
                        ImGui::SameLine();
                            if ( ImGui::Button( "Load Model" ) )
                            {
                                sceneObjects[ i ]->loadModel( ResourceManager::getPathToModel( objects_ModelList[ objects_SelectedModel ] ) );
                            }
//                         ImGui::TreePop();
//                     }
                    if ( ImGui::SmallButton( "Delete Object" ) )
                        sceneObjects.erase( sceneObjects.begin() + i );
                    ImGui::TreePop();
                }
            }
            if ( ImGui::SmallButton("Add Object") )
                sceneObjects.push_back( new Model( ResourceManager::getPathToModel( ResourceManager::listLoadedPathsToModels()[0] ) ) );
            ImGui::TreePop();
        }

    ImGui::End();
}

void imguiRenderFrame(){
    // Crta Frame na ekran
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());    
}

void imguiCleanup(){
        // Dear ImGui Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

#endif
