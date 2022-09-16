#include "State.h"

#define PINGINFACE "./assets/img/penguinface.png"
#define BOOM "./assets/audio/boom.wav"
#define BACKGROUND_AUDIO "./assets/audio/stageState.ogg"
#define BACKGROUND_FRAME "./assets/img/ocean.jpg"
#define TILEMAP "./assets/map/tileMap.txt"
#define TILESET "./assets/img/tileset.png"
#define MUSIC_TIMESTOPLAY -1 //-1 to continuous

#define TILESET_WIDTH 64
#define TILESET_HEIGHT 64
#define clipOriginX 0
#define clipOriginY 0


State::State(){
	quitRequested = false;
	started = false;
	GameObject* gameObject = new GameObject();
	Sprite* go_sprite = new Sprite(*gameObject, BACKGROUND_FRAME);
	CameraFollower* go_cameraFollower = new CameraFollower(*gameObject);
	gameObject->AddComponent(go_sprite);
	gameObject->AddComponent(go_cameraFollower);
	objectArray.emplace_back(gameObject);

	GameObject* gameObjectMap = new GameObject();
	TileSet* tileSet = new TileSet(TILESET_WIDTH, TILESET_HEIGHT, TILESET);
	TileMap* go_tileMap = new TileMap(*gameObjectMap, TILEMAP, tileSet);	
	gameObjectMap->AddComponent(go_tileMap);
	objectArray.emplace_back(gameObjectMap);

	GameObject* gameObjectAlien = new GameObject();
	Alien *go_alien = new Alien(*gameObjectAlien, 5);
	gameObjectAlien->box.Centralize(512, 300);
	gameObjectAlien->AddComponent(go_alien);
	objectArray.emplace_back(gameObjectAlien);

	GameObject* gameObjectPenguinBody = new GameObject();
	PenguinBody *penguinBody = new PenguinBody(*gameObjectPenguinBody);
	gameObjectPenguinBody->box.Centralize(704, 640);
	gameObjectPenguinBody->AddComponent(penguinBody);
	objectArray.emplace_back(gameObjectPenguinBody);

	LoadAssets();
	Camera::Follow(gameObjectPenguinBody);
    music.Play(MUSIC_TIMESTOPLAY);
}

State::~State(){
    objectArray.clear();
}

bool State::QuitRequested(){
    return quitRequested;
}

void State::LoadAssets(){
    music.Open(BACKGROUND_AUDIO);
}

void State::Update(float dt){
	//std::cout << dt << std::endl;
	Camera::Update(dt);
	if(InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		music.Stop();
		quitRequested = true;
	}

	// if(InputManager::GetInstance().KeyPress(SPACE_BAR)){
	// 	Vec2 objPos = Vec2(150.0, 0.0).GetRotated( -PI + PI*(std::rand() % 1001)/500.0 ) + Vec2(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
	// 	AddObject((int)objPos.x, (int)objPos.y);
	// }

    for(int it = 0; it <= (int)objectArray.size() - 1; it++){
		objectArray[it]->Update(dt);
    
	}
	for(int i = 0; i <= (int)objectArray.size() - 1; i++){
		for(int j = i+1; j <= (int)objectArray.size() - 1; j++){
			Collider *colliderA = (Collider*) objectArray[i]->GetComponent("Collider");
            Collider *colliderB = (Collider*) objectArray[j]->GetComponent("Collider");
			if(colliderA && colliderB){
				if(Collision::IsColliding(colliderA->box, colliderB->box, (float)objectArray[i]->angleDeg, (float)objectArray[j]->angleDeg)){
					objectArray[i]->NotifyCollision(*objectArray[j]);
					objectArray[j]->NotifyCollision(*objectArray[i]);
				}

			}

    	}
    }
	for(int it = 0; it <= (int)objectArray.size() - 1; it++){
		if(objectArray[it]->IsDead()){
			objectArray.erase(objectArray.begin()+it);
		}
    }
	SDL_Delay(dt);

}

void State::Render(){
	for(int it = 0; it <= (int)objectArray.size() - 1; it++){
		objectArray[it]->Render();
    }
}

void State::AddObject(int mouseX, int mouseY){
	GameObject* enemy = new GameObject();
	
	objectArray.emplace_back(enemy);
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go){
	std::shared_ptr<GameObject> ptrShare(go);
	objectArray.push_back(ptrShare);
	if(started == true){
		go->Start();
	}
	std::weak_ptr<GameObject> wPtr = ptrShare;
	return wPtr;
}


void State::Start(){
	LoadAssets();
	for(int it = 0; it <= (int)objectArray.size() - 1; it++){
		objectArray[it]->Start();
    }
	started = true;

}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go){
	for(int it = 0; it <= (int)objectArray.size() - 1; it++){
		if(objectArray[it].get() == go){
			std::weak_ptr<GameObject> wPtr = objectArray[it];
			return wPtr;
		}
    }
	std::weak_ptr<GameObject> wPtr_null;
	wPtr_null.reset();
	return wPtr_null;
}