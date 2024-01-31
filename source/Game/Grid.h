#ifndef C_GRID
#define C_GRID
#include <vector>
#include "Vector2D.h"
#include "IGameObject.h"


class SDL_Renderer;
class SDL_Color;

/*
* A grid is a 2D collection of renderable objects.
* Each object in a grid has its origin offset by their position in the grid.
*/
class Grid : public IGameObject {
	//Default constructor
	Grid(
		unsigned short width,
		unsigned short height,
		float cellSize,
		Vector2D position,
		std::vector<IGameObject*> items
	);
	~Grid();

public: //IGameObject overrides
	void update(float deltaTime);
	void processInput();
	void render(SDL_Renderer* renderer);
	void setIsAlive(bool isAlive);
	bool getIsAlive() const;
	std::vector<IGameObject*> getChildren();

public:
	void resize(unsigned short newWidth, unsigned short newHeight);
	void setHeight( unsigned short newHeight);
	void setWidth(unsigned short newWidth);
	void setPosition(Vector2D newPosition);
	IGameObject* getChild(unsigned short col, unsigned short row);
	IGameObject* getChild(unsigned short index);


private:
	IGameObject * parent;
	unsigned short height;
	unsigned short width;
	Vector2D position;
	bool isAlive;
	std::vector<IGameObject*> items;

};
#endif