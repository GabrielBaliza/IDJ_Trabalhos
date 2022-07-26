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
	GameObject* gameObject = new GameObject();
	Sprite* go_sprite = new Sprite(*gameObject, BACKGROUND_FRAME);
	TileSet* tileSet = new TileSet(TILESET_WIDTH, TILESET_HEIGHT, TILESET);
	TileMap* go_tileMap = new TileMap(*gameObject, TILEMAP, tileSet);
	
	gameObject->AddComponent(go_sprite);
	gameObject->AddComponent(go_tileMap);
	objectArray.emplace_back(gameObject);

	LoadAssets();
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
	if(InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		quitRequested = true;
	}
	if(InputManager::GetInstance().KeyPress(SPACE_BAR)){
		Vec2 objPos = Vec2(200.0, 0.0).GetRotated( -PI + PI*(std::rand() % 1001)/500.0 ) + Vec2(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseX());
		AddObject((int)objPos.x, (int)objPos.y);
	}
    for(int it = 0; it <= (int)objectArray.size() - 1; it++){
		objectArray[it]->Update(dt);
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
	Sprite* enemy_sprite = new Sprite(*enemy, PINGINFACE);
	Sound* enemy_boom = new Sound(*enemy, BOOM);
	Face* enemy_face = new Face(*enemy);

	enemy->box.x = mouseX - (enemy_sprite->GetWidth()) / 2;
	enemy->box.y = mouseY - (enemy_sprite->GetHeight()) / 2;
	
	enemy->AddComponent(enemy_sprite);
	enemy->AddComponent(enemy_boom);
	enemy->AddComponent(enemy_face);

	objectArray.emplace_back(enemy);
}

void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		
		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(go->box.Contains((float)mouseX, (float)mouseY) ) {
					Face* face = (Face*)go->GetComponent( "Face" );
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2(200.0, 0.0).GetRotated( -PI + PI*(std::rand() % 1001)/500.0 ) + Vec2( mouseX, mouseY );
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}