#include "camera.h"

Camera::Camera(){
    // Dodati neki koristan konstruktor...
}
/////////////
// setters
void Camera::setPosition( glm::vec3 position ){
    mCameraPosition = position;
    std::cout << "mCameraPosition.x= " << mCameraPosition.x << std::endl;
    std::cout << "mCameraPosition.y= " << mCameraPosition.y << std::endl;
    std::cout << "mCameraPosition.z= " << mCameraPosition.z << std::endl;
}
void Camera::setLookingAtPoint( glm::vec3 lookingAtPoint ){
    mCameraLookingAtPoint = lookingAtPoint;
    std::cout << "mCameraLookingAtPoint.x= " << mCameraLookingAtPoint.x << std::endl;
    std::cout << "mCameraLookingAtPoint.y= " << mCameraLookingAtPoint.y << std::endl;
    std::cout << "mCameraLookingAtPoint.z= " << mCameraLookingAtPoint.z << std::endl;
}
void Camera::setUpVector( glm::vec3 upVector ){
    mCameraUpVector = upVector;
    std::cout << "mCameraUpVector.x= " << mCameraUpVector.x << std::endl;
    std::cout << "mCameraUpVector.y= " << mCameraUpVector.y << std::endl;
    std::cout << "mCameraUpVector.z= " << mCameraUpVector.z << std::endl;
}
void Camera::setViewMatrix(){
    mViewMatrix = glm::lookAt( mCameraPosition, mCameraLookingAtPoint, mCameraUpVector );
//    std::cout << "mViewMatrix= " << mViewMatrix << std::endl;
}
void Camera::setRadius( float radius ){
    mRadius = glm::radians( radius );      // glm::radians( 45.0f )
    std::cout << "mRadius= " << mRadius << std::endl;
}
void Camera::setAspectRatio( float aspectRatio ){
    mAspectRatio = aspectRatio; // 4.0f/3.0f
    std::cout << "mAspectRatio= " << mAspectRatio << std::endl;
}
void Camera::setNearZPlane( float nearZPlane ){
    mNearZPlane = nearZPlane;  // 0.1f
    std::cout << "mNearZPlane= " << mNearZPlane << std::endl;
}
void Camera::setFarZPlane( float farZPlane ){
    mFarZPlane = farZPlane;   // 100.0f    
    std::cout << "mFarZPlane= " << mFarZPlane << std::endl;
}
void Camera::setProjectionMatrix(){
    mProjectionMatrix = glm::perspective( mRadius, mAspectRatio, mNearZPlane, mFarZPlane );
//    std::cout << "mProjectionMatrix= " << mProjectionMatrix << std::endl;
}

void Camera::setVP(){
    mVP = mProjectionMatrix * mViewMatrix;
//    std::cout << "mVP= " << mVP << std::endl;
}

/////////////
// getters
glm::vec3 Camera::getPosition( ){
    return mCameraPosition;
}
glm::vec3 Camera::getLookingAtPoint( ){
    return mCameraLookingAtPoint;
}
glm::vec3 Camera::getUpVector( ){
    return mCameraUpVector;
}
glm::mat4 Camera::getViewMatrix(){
    return mViewMatrix;
}
    // by reference
glm::vec3& Camera::getPositionRef(){
    return mCameraPosition;
}
glm::vec3& Camera::getLookingAtPointRef(){
    return mCameraLookingAtPoint;
}
glm::vec3& Camera::getUpVectorRef(){
    return mCameraUpVector;
}
glm::mat4& Camera::getViewMatrixRef(){
    return mViewMatrix;
}


float Camera::getRadius(){
    return mRadius;      // glm::radians( 45.0f )
}
float Camera::getAspectRatio(){
    return mAspectRatio; // 4.0f/3.0f
}
float Camera::getNearZPlane(){
    return mNearZPlane;  // 0.1f
}
float Camera::getFarZPlane(){
    return mFarZPlane;   // 100.0f    
}
glm::mat4 Camera::getProjectionMatrix(){
    return mProjectionMatrix;
}

float& Camera::getRotationSpeedRef(){
    return mRotationSpeed;
}
glm::mat4 Camera::getVP(){
    return mVP;
}

/////////////
// Naprednije metode!
void Camera::rotateCamera( float radius ){
    if ( mRotationSpeed == 0.0f ) return;
// veci mRotationSpeed znaci sporija rotacija! Mozda bi bilo dobro prilagoditi kod...
        mCameraPosition.x = sin( glfwGetTime()/ mRotationSpeed ) * radius;
        mCameraPosition.z = cos( glfwGetTime()/ mRotationSpeed ) * radius;
        setViewMatrix();
}
