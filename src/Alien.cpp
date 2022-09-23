#include "Alien.h"

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions) : Component::Component(associated){
    
    Sprite* go_sprite = new Sprite(associated, ALIEN);
    Collider *go_collider = new Collider(associated, {0.65, 0.6}, {-5, 0});
    associated.AddComponent(go_sprite);
    associated.AddComponent(go_collider);

    speed = {0, 0};
    destination = {associated.box.x, associated.box.y};
    hp = MAXHP;
    minionArray.resize(nMinions);
    state = AlienState::RESTING;

    alienCount++;
}

Alien::~Alien(){
    alienCount--;
    minionArray.clear();
}

void Alien::Start(){
    State& state = Game::GetInstance().GetState();
    for(int i = 0; i < (int) minionArray.size(); i++){
        float distribute = PI2*i/minionArray.size();
        GameObject* go = new GameObject();
        Minion* go_Minion = new Minion(*go, state.GetObjectPtr(&associated), distribute);
        go->AddComponent(go_Minion);
        minionArray[i] = state.AddObject(go);
    }
}

void Alien::Update(float dt){
    if(hp <= 0){
        State& state = Game::GetInstance().GetState();
        GameObject* explosion = new GameObject();
        Sprite* go_sprite = new Sprite(*explosion, ALIEN_DEATH, 4, 0.3, 1.2);
        Sound* boom = new Sound(*explosion, BOOM);
        explosion->box = associated.box;
        explosion->AddComponent(go_sprite);
        explosion->AddComponent(boom);
        boom->Play();
        state.AddObject(explosion);

        associated.RequestDelete();
    }
    if(PenguinBody::player){
        if(state == AlienState::RESTING){
            restTimer.Update(dt);
            if(restTimer.Get() >= RESTINGCOOLDOWN){
                destination = PenguinBody::player->PlayerPos();
                float dist;
                dist = sqrt(pow((destination.x - (associated.box.x + associated.box.w/2)), 2.0) + pow((destination.y - (associated.box.y + associated.box.h/2)), 2.0));
                speed.x = SPEED*(destination.x - (associated.box.x + associated.box.w/2))/dist;
                speed.y = SPEED*(destination.y - (associated.box.y + associated.box.h/2))/dist;

                state = AlienState::MOVING;
                
            }
        }
        else{ // (state == AlienState::MOVING)
            float dist;
            dist = sqrt(pow((destination.x - (associated.box.x + associated.box.w/2)), 2.0) + pow((destination.y - (associated.box.y + associated.box.h/2)), 2.0));
            associated.box.x += dt*speed.x;
            associated.box.y += dt*speed.y;
            if(dist <= dt * SPEED){
                associated.box.x = destination.x - associated.box.w/2;
                associated.box.y = destination.y - associated.box.h/2;
                if(minionArray.size() > 0){
                    Vec2 posPlayer = PenguinBody::player->PlayerPos();
                    float minDist = 100000000, dist;
                    int closest = 0;
                    for(int it = 0; it < (int)minionArray.size(); it++){
                        dist = sqrt(pow((posPlayer.x - (minionArray[it].lock().get()->box.x)), 2.0) + pow((posPlayer.y - (minionArray[it].lock().get()->box.y)), 2.0));
                        if(dist < minDist){
                            minDist = dist;
                            closest = it;
                        }
                    }
                    Minion* cMinion = (Minion*)minionArray[closest].lock().get()->GetComponent("Minion");
                    cMinion->Shoot(posPlayer);
                }
                restTimer.Restart();
                state = AlienState::RESTING;
            }
        }
    }
    associated.angleDeg -= dt * ALIEN_ANG_VEL;
}

void Alien::Render(){}

bool Alien::Is(std::string type){
    return (type == "Alien");
}

void Alien::MinionHit(GameObject& minion){
    auto tMinion = (Minion*)minion.GetComponent("Minion");
    int id;
    for(int it = 0; it < (int)minionArray.size(); it++){
        if(tMinion == (Minion*)minionArray[it].lock().get()->GetComponent("Minion")){
            std::cout << "Minion HIT" << std::endl;
            id = it;
            break;
        }
    }
    minionArray.erase(minionArray.begin()+id);

}

void Alien::NotifyCollision(GameObject& other){
    auto bullet = (Bullet*)other.GetComponent("Bullet");
    if(bullet && !bullet->targetsPlayer){
        hp -= bullet->GetDamage({0,0});
        std::cout << "Alien HP: " << hp << std::endl;
    }
}