#pragma once
#include "GameObjectCreator.h"
#include "GameObject.h"
#include "Log.h"

class GameObjectFactory {

private:
	GameObjectFactory() {}
	~GameObjectFactory() {}
	static GameObjectFactory* s_pInstance;
	static Log* Logger;

    std::map<std::string, GameObjectCreator*> m_creators;
	
public:
	GameObjectFactory(const GameObjectFactory&) = delete;
	GameObjectFactory& operator=(const GameObjectFactory&) = delete;

	static GameObjectFactory* instance() {
		if (s_pInstance == nullptr) {
			s_pInstance = new GameObjectFactory();
		}
		return s_pInstance;
	}

	// ----------------------------------

    void registerType(std::string type, GameObjectCreator* pCreator);
    GameObject* create(std::string type);

};

