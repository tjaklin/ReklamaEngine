// Include standard headers
#include <iostream>
#include <string>
#include <vector>
// Include GLEW
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

GLFWwindow* window;

// Include my custom headers
#include "common/ResourceManager.h"
#include "common/camera.h"
#include "common/GameObject.h"
#include "common/Model.h"
#include "common/SceneEditor.h"

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
    uint width = 1024; uint height = 768;
	window = glfwCreateWindow( width, height, "Tutorial 05 - Textured Cube", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	Shader reflectionShaderID;
    
    // Dodaje se shader pomocu klase ResourceManager, a nakon toga se preko getShader izraduje reflectionShaderID
    // objekt koji ce se koristiti za crtanje scene.
	if( ResourceManager::addShader( "reflection", "shaders/reflection.vs", "shaders/reflection.fs" ) )
		reflectionShaderID = ResourceManager::getShader( "reflection" );
	else
		std::cout << "Stanje Shader reflection: -" << std::endl;

    Shader skyboxShaderID;
    // Na slican nacin se ovdje loada skybox shader
	if( ResourceManager::addShader( "skybox", "shaders/skybox.vs", "shaders/skybox.fs" ) )
		skyboxShaderID = ResourceManager::getShader( "skybox" );
	else
		std::cout << "Stanje Shader skybox: -" << std::endl;
    
    std::vector<std::string> defaultSkyboxTextures
    {
        "textures/skybox/default/right.jpg",
        "textures/skybox/default/left.jpg",
        "textures/skybox/default/top.jpg",
        "textures/skybox/default/bottom.jpg",
        "textures/skybox/default/front.jpg",
        "textures/skybox/default/back.jpg"
    };
    // specificiraju se lokacije skybox tekstura te se loadaju u ResourceManager mapu skybox tekstura.
    if( ResourceManager::addSkyboxTexture( "skyboxDefault", defaultSkyboxTextures ) )
        std::cout << "Stanje Texture skyboxDefault: +" << std::endl;

    std::vector<std::string> sincitySkyboxTextures
    {
        "textures/skybox/mp_sincity/sincity_rt.tga",
        "textures/skybox/mp_sincity/sincity_lf.tga",
        "textures/skybox/mp_sincity/sincity_up.tga",
        "textures/skybox/mp_sincity/sincity_dn.tga",
        "textures/skybox/mp_sincity/sincity_ft.tga",
        "textures/skybox/mp_sincity/sincity_bk.tga",
    };
        // Na ovakav nacin moguce je dodati i koristiti proizvoljan broj skybox tekstura.
        // jer se svi loadani skyboxevi automatski dodaju u Panel Properties na izbor korisniku
    if( ResourceManager::addSkyboxTexture( "skyboxSincity", sincitySkyboxTextures ) )
        std::cout << "Stanje Texture skyboxSincity: +" << std::endl;

    // Ovdje dodajem putanje za tri modela koji dolaze uz program
    
    if( ResourceManager::addPathToModel( "nanosuit", "objects/nanosuit/nanosuit.obj" ) )
        std::cout << "Stanje Modela nanosuit: +" << std::endl;
    if( ResourceManager::addPathToModel( "leather_shoes", "objects/leather_shoes/leather_shoes.fbx" ) )
        std::cout << "Stanje Modela leather_shoes: +" << std::endl;
    if( ResourceManager::addPathToModel( "camera", "objects/camera/camera.fbx" ) )
        std::cout << "Stanje Modela camera: +" << std::endl;

    // Dark blue background
	glClearColor(0.2f, 0.15f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

    GLuint VertexArrayBasicID;
	glGenVertexArrays(1, &VertexArrayBasicID);
	glBindVertexArray(VertexArrayBasicID);

    // Izrada kamere! Ovo je Testna Kamera iz opisa programa
    Camera* editorCamera = new Camera();
    editorCamera->setRadius( 45.0f );
    editorCamera->setAspectRatio( 4.0f / 3.0f );
    editorCamera->setNearZPlane( 0.1f );
    editorCamera->setFarZPlane( 100.0f );
        editorCamera->setProjectionMatrix();
    editorCamera->setPosition( glm::vec3( 30.0f, 5.0f, 30.0f ) );
    editorCamera->setLookingAtPoint( glm::vec3( 0.0f, 0.0f, 0.0f ) );
    editorCamera->setUpVector( glm::vec3( 0.0f, 1.0f, 0.0f ) );
        editorCamera->setViewMatrix();
    editorCamera->setVP();
    
    // Ovo je Glavna Kamera iz opisa programa
    Camera* recordingCamera = new Camera();
    recordingCamera->setRadius( 45.0f );
    recordingCamera->setAspectRatio( 4.0f / 3.0f );
    recordingCamera->setNearZPlane( 0.1f );
    recordingCamera->setFarZPlane( 100.0f );
        recordingCamera->setProjectionMatrix();
    recordingCamera->setPosition( glm::vec3( 30.0f, 5.0f, 30.0f ) );
    recordingCamera->setLookingAtPoint( glm::vec3( 0.0f, 0.0f, 0.0f ) );
    recordingCamera->setUpVector( glm::vec3( 0.0f, 1.0f, 0.0f ) );
        recordingCamera->setViewMatrix();
    recordingCamera->setVP();
        
    glm::mat4 editorCameraVP = recordingCamera->getVP();
    glm::mat4 recordingCameraVP = recordingCamera->getVP();

    // Izrada Skyboxa!
    GLuint VertexArraySkyboxID;
	glGenVertexArrays(1, &VertexArraySkyboxID);
	glBindVertexArray(VertexArraySkyboxID);

    GameObject* skybox_cube = new GameObject();

    skybox_cube->fillData( shapeCube_PosNorm, sizeof( shapeCube_PosNorm ) );
	skybox_cube->setTexture( ResourceManager::getSkyboxTexture( "skyboxDefault" ) );
    skybox_cube->setModel();

    // Izrada svih Modela!
    glBindVertexArray( VertexArrayBasicID );        

    std::vector< Model* > sceneObjects;
        // ovdje se u scenu dodaje default objekt koji se radi iz modela s indexom 2 u listiLoadedPathsToModels
        sceneObjects.push_back( new Model( ResourceManager::getPathToModel( 
                            ResourceManager::listLoadedPathsToModels()[2] ) ) );

        // Tu napravimo renderingCamera model za lakse predocivanje gibanja kamere u nasoj sceni.
        // Taj model je kamera
        Model* cameraPreviewObject = 
            new Model( ResourceManager::getPathToModel( ResourceManager::listLoadedPathsToModels()[2] ) );
        
    // Setup Dear ImGui binding
    // Ovime pokrecemo ImGui knjiznicu
imguiSetup();

// U funkcijama ispod se specificira kod za snimanje scene te outputanja snimke u clip.mp4
    // FFMPEG setup
// start ffmpeg telling it to expect raw rgba 720p-60hz frames
// -i - tells it to read frames from stdin
const char* cmd = "ffmpeg -r 60 -f rawvideo -pix_fmt rgba -s 1024x768 -i - "
                  "-threads 0 -preset fast -y -pix_fmt yuv420p -crf 21 -vf vflip clip.mp4";

// open pipe to ffmpeg's stdin in binary write mode
FILE* ffmpeg = popen(cmd, "w");

int* buffer = new int[width*height];

/////////////////////////// MAIN DO LOOP /////////////////////////////
	do{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
        recordingCamera->setViewMatrix();
        recordingCamera->setProjectionMatrix();
        recordingCamera->setVP();
        recordingCameraVP = recordingCamera->getVP();

        cameraPreviewObject->setTranslate( recordingCamera->getPosition() );
        cameraPreviewObject->setRotate( -recordingCamera->getPosition(), 10.0f );
        
        reflectionShaderID.activate();
        glBindVertexArray( VertexArrayBasicID );        

            // render the cameraPreviewModel object
            cameraPreviewObject->updateObjectData();
            reflectionShaderID.setMatrix4fv( "VP", editorCameraVP );
            reflectionShaderID.setMatrix4fv( "M", cameraPreviewObject->getModelMAT() );
            reflectionShaderID.set3f( "viewPos", recordingCamera->getPosition() );
            reflectionShaderID.set1i( "skybox", 0 );

            cameraPreviewObject->Draw( reflectionShaderID );            

        for ( int i = 0; i < sceneObjects.size(); i++ )
        {
            // render the loaded model
            sceneObjects[i]->updateObjectData();
            reflectionShaderID.setMatrix4fv( "VP", editorCameraVP );
            reflectionShaderID.setMatrix4fv( "M", sceneObjects[i]->getModelMAT() );
            reflectionShaderID.set3f( "viewPos", recordingCamera->getPosition() );
            reflectionShaderID.set1i( "skybox", 0 );

            sceneObjects[i]->Draw( reflectionShaderID );            
        }
        reflectionShaderID.deactivate();

    // SKYBOX IDE TU!
            glDepthFunc(GL_LEQUAL);
                // Use skybox shader
            skyboxShaderID.activate();
            glBindVertexArray( VertexArraySkyboxID );
		glActiveTexture(GL_TEXTURE0);
        glBindTexture( GL_TEXTURE_CUBE_MAP, skybox_cube->getTexture().getTexture() );
            skyboxShaderID.setMatrix4fv( "projection", editorCamera->getProjectionMatrix() );
        glm::mat4 skybox_view = glm::mat4( glm::mat3( editorCamera->getViewMatrix() ) );
            skyboxShaderID.setMatrix4fv( "view", skybox_view );
            skyboxShaderID.set1i( "skybox", 0 );

        skybox_cube->draw();
            skyboxShaderID.deactivate();
            glDepthFunc(GL_LESS);        

        // IMGUI rendering my frame;

       imguiCreateCameraSection( recordingCamera, skybox_cube, sceneObjects );
       imguiRenderFrame();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Swap buffers
		glfwSwapBuffers(window);
            // OVdje se uzima slika svake scene pa se iz niza slika radi video
            glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
            fwrite(buffer, sizeof(int)*width*height, 1, ffmpeg);        
        glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );


    // Kada prestane program gasimo FFMPEG - za snimanje scene
            // Close FFMPEG
            pclose(ffmpeg);    
            
    // Cleanup VBO and shader
	glDeleteVertexArrays(1, &VertexArrayBasicID);
    glDeleteVertexArrays(1, &VertexArraySkyboxID);
    
        // Dear ImGui Cleanup
        imguiCleanup();
	// Close OpenGL window and terminate GLFW
    glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
