#include "Bullet.h"


Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite) : Component::Component(associated){
    Sprite* go_sprite = new Sprite(associated, sprite);
    associated.AddComponent(go_sprite);

    distanceLeft = maxDistance;
    this->damage = damage;
    this->speed = {speed*cos(angle) , speed*sin(angle)};
    associated.angleDeg = (180/PI)*angle;
    
}

void Bullet::Update(float dt){
    if(distanceLeft <= 0){
        associated.RequestDelete();
    }
    else{
        associated.box.x += speed.x * dt;
        associated.box.y += speed.y * dt;
        float distPassed = sqrt(pow(speed.x * dt, 2.0) + pow(speed.y * dt, 2.0));
        distanceLeft -= distPassed;
    }

}

void Bullet::Render(){}

bool Bullet::Is(std::string type){
    return (type == "Bullet");
}

int Bullet::GetDamage(Vec2 target){
    return damage;
}