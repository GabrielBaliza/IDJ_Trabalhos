#include "Bullet.h"


Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, bool targetsPlayer, int frameCount, float frameTime, Vec2 bulletScale, Vec2 colliderScale, Vec2 colliderOffset) : Component::Component(associated){    
    Sprite* go_sprite = new Sprite(associated, sprite, frameCount, frameTime);
    go_sprite->SetScale(bulletScale.x, bulletScale.y);
    Collider *go_collider = new Collider(associated, colliderScale, colliderOffset);
    associated.AddComponent(go_sprite);
    associated.AddComponent(go_collider);

    distanceLeft = maxDistance;
    this->damage = damage;
    this->speed = {speed*cos(angle) , speed*sin(angle)};
    this->targetsPlayer = targetsPlayer;
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

void Bullet::NotifyCollision(GameObject& other){
    if(other.GetComponent("PenguinBody") && this->targetsPlayer){
        this->associated.RequestDelete();
    }
    if(other.GetComponent("PenguinCannon") && this->targetsPlayer){
        this->associated.RequestDelete();
    }
    if((other.GetComponent("Minion") || other.GetComponent("Alien")) && !this->targetsPlayer){
        this->associated.RequestDelete();
    }
}