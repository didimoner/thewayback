#pragma once
#include "GameObjectCreator.h"

class GameObject;
class Log;

class GameObjectFactory {

private:
	GameObjectFactory() {}

	static GameObjectFactory s_instance;
	static Log Logger;

    std::map<std::string, std::unique_ptr<GameObjectCreator>> m_creators;
	
public:
	~GameObjectFactory();
	GameObjectFactory(const GameObjectFactory&) = delete;
	GameObjectFactory& operator=(const GameObjectFactory&) = delete;

	static GameObjectFactory& instance() {
		return s_instance;
	}

	// ----------------------------------

    void registerType(std::string type, std::unique_ptr<GameObjectCreator>&& pCreator);
    GameObject* create(std::string type);

};

