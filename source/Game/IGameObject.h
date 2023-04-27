#ifndef I_GAME_OBJECT
#define I_GAME_OBJECT

#include <vector>
class SDL_Renderer;
class IGameObject {
public: 
	virtual ~IGameObject() {};
	virtual void update(float deltaTime) = 0;
	virtual void processInput() = 0;
	virtual void render(SDL_Renderer* renderer) = 0;
	virtual void setIsAlive(bool isAlive) = 0;
	virtual bool getIsAlive() const = 0;
	virtual std::vector<IGameObject*> getChildren() = 0;
	virtual IGameObject* getParent() = 0;


protected: //Functions
	IGameObject() {};
};

#endif