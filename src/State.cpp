#include "State.h"

State::State(){
    started = false;
    popRequested = false;
    quitRequested = false;
}

State::~State(){
    objectArray.clear();
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

bool State::PopRequested(){
    return popRequested;
}

bool State::QuitRequested(){
    return quitRequested;
}

void State::StartArray(){
	for(int it = 0; it <= (int)objectArray.size() - 1; it++){
		objectArray[it]->Start();
    }
	started = true;
}

void State::UpdateArray(float dt){
    for(int it = 0; it < (int)objectArray.size(); it++){
		objectArray[it]->Update(dt);
	}
}

void State::RenderArray(){
    for(int it = 0; it < (int)objectArray.size(); it++){
		objectArray[it]->Render();
    }
}