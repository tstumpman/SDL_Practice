#include "Grid.h"


//Constructor
Grid::Grid(
	unsigned short width,
	unsigned short height,
	float cellSize,
	Vector2D position,
	std::vector<IGameObject*> items
) {
	this->parent = nullptr;
	this->height = height;
	this->width = width;
	this->position = position;
	this->isAlive = true;
	this->items = items;
}

Grid::~Grid() {

}

void Grid::render(SDL_Renderer* renderer) {
	if (isAlive) {
		for (unsigned int i = 0; i < items.size(); i++) {
			items[i]->render(renderer);
		}
	}
}

void Grid::update(float deltaTime) {
	if (isAlive) {
		for (unsigned int i = 0; i < items.size(); i++) {
			items[i]->update(deltaTime);
		}
	}
}

void Grid::processInput() {
	if (isAlive) {
		for (unsigned int i = 0; i < items.size(); i++) {
			items[i]->processInput();
		}
	}
}

void Grid::setIsAlive(bool isAlive) {
	this->isAlive = isAlive;
}

void Grid::setPosition(Vector2D newPosition) {
	this->position = newPosition;
}

void Grid::resize(unsigned short newWidth, unsigned short newHeight) {
	setWidth(newWidth);
	setHeight(newHeight);
}

void Grid::setWidth(unsigned short newWidth) {
	this->width = newWidth;
}

void Grid::setHeight(unsigned short newHeight) {
	this->height = newHeight;
}

bool Grid::getIsAlive() const {
	return this->isAlive;
}

std::vector<IGameObject*> Grid::getChildren() {
	return this->items;
}

IGameObject* Grid::getChild(unsigned short col, unsigned short row) {
	unsigned short index = this->width * row + col;
	return getChild(index);
}

IGameObject* Grid::getChild(unsigned short index) {
	if (items.size() > index) {
		return items[index];
	}
	return nullptr;
}

