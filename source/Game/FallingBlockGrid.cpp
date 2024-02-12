#include "FallingBlockGrid.h"
#include "../MathUtils.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_render.h"
#include "SDL/SDL_Rect.h"
#include "MoveComponent.h"
#include "MonospaceCharacter.h"
#include "InputComponent.h"

//Constructor
FallingBlockGrid::FallingBlockGrid(
	Game* game,
	Vector2D gridSize,
	CartesianCoordinate gridDimensions
) :
	Actor(game)
{
	this->gridSize = gridSize;
	this->gridIndices = gridDimensions.abs();
	this->items.resize(gridIndices.x * gridIndices.y);
	for (unsigned int i = 0; i < items.size(); i++) {
		items[i] = nullptr;
	}
}

//Destructor
FallingBlockGrid::~FallingBlockGrid() {
}

void FallingBlockGrid::updateActor(float deltaTime) {
}

void FallingBlockGrid::setPosition(Vector2D newPosition) {
	Actor::setPosition(newPosition);

	for (unsigned int col = 0; col < gridIndices.x; col++) {
		for (unsigned int row = 0; row < gridIndices.y; row++) {
			CartesianCoordinate index2d = CartesianCoordinate(col, row);
			Actor* item = getItemAt(index2d);
			if (item != nullptr) {
				item->setPosition(getCellPosition(index2d));
			}
		}
	}
}

Vector2D FallingBlockGrid::getSize() const {
	return gridSize;
}

CartesianCoordinate FallingBlockGrid::getGridDimensions() const {
	return gridIndices;
}

void FallingBlockGrid::setItem(CartesianCoordinate coord, Actor* item){
	setItem(getIndex(coord), item);
}

void FallingBlockGrid::setItem(unsigned int index, Actor* item) {
	if (index < items.size()) {
		items[index] = item;
	}
}

Rect FallingBlockGrid::getBoundaryForItemSlot(CartesianCoordinate coord) {
	return Rect(
		getCellPosition(coord),
		getCellSize()
	);
}

Vector2D FallingBlockGrid::getCellSize() const {
	float cellWidth = gridSize.x / gridIndices.x;
	float cellHeight = gridSize.y / gridIndices.y;
	return Vector2D(cellWidth, cellHeight);
}

Vector2D FallingBlockGrid::getCellPosition(CartesianCoordinate coord) const {
	Vector2D cellSize = getCellSize();
	Vector2D position = this->getPosition();
	return Vector2D(
		coord.x * cellSize.x + position.x,
		coord.y * cellSize.y + position.y
	);
}

Actor* FallingBlockGrid::getItemAt(unsigned int index) {
	if (index < items.size()) {
		return items[index];
	}
	return nullptr;
}

Actor* FallingBlockGrid::getItemAt(CartesianCoordinate index){
	return getItemAt(getIndex(index));
}

std::vector<Rect> FallingBlockGrid::calculateLetterSlots(
	Rect boundary,
	unsigned int cols,
	unsigned int rows
) {
	float cellWidth = boundary.getSize().x / (float)cols;
	float cellHeight = boundary.getSize().y / (float)rows;
	std::vector<Rect> returnMe = std::vector<Rect>();
	returnMe.resize(rows * cols);

	unsigned int index = 0;
	for (unsigned int r = 0; r < rows; r++) {
		for (unsigned int c = 0; c < cols; c++) {
			returnMe[index] =
				Rect(
					int((c * cellWidth) + boundary.getOrigin().x),
					int((r * cellHeight) + boundary.getOrigin().y),
					int(cellWidth),
					int(cellHeight)
				);
			index++;
		}
	}
	return returnMe;
}

CartesianCoordinate FallingBlockGrid::getCoordinate(unsigned int index) {
	int row_index = index / gridIndices.x;
	int col_index = index % gridIndices.x;
	return CartesianCoordinate(col_index, row_index);
}

unsigned int FallingBlockGrid::getIndex(CartesianCoordinate coordinate) {
	return (coordinate.y * gridIndices.x) + coordinate.x;
}