#include "CameraFollower.h"

CameraFollower::CameraFollower(GameObject& go) : Component::Component(go){}

void CameraFollower::Render(){


}

void CameraFollower::Update(float dt){
    associated.box.x = -1 * Camera::pos.x;
    associated.box.y = -1 * Camera::pos.y;
}

bool CameraFollower::Is(std::string type){
    return (type=="CameraFollower");
}