#ifndef C_SPRITE_COMPONENT
#define C_SPRITE_COMPONENT
#include "Component.h"
#include "Rect.h"
class SDL_Texture;
class SDL_Renderer;
class SDL_Rect;
class SpriteComponent : public Component {
public:
	SpriteComponent(Actor* owner, int drawOrder = 100);

	~SpriteComponent();
	virtual void update(float deltaTime) {}
	virtual void setTexture(SDL_Texture* texture);
	virtual void draw(SDL_Renderer* renderer);
	int getDrawOrder() const;
	Rect getTextureRect() const;
	int getTextureHeight() const;
	int getTextureWidth() const;
	void setSourceRect(Rect sourceRect);
	void setDrawSize(Vector2D drawSize);
	SDL_Texture* getTexture() const;
	Vector2D getDrawSize() const;
	Vector2D getTextureSize() const;

protected:
	SDL_Texture* texture;
	int drawOrder;
	Vector2D drawSize;
	Rect* sourceRect;//Which part of the texture to draw from; null if using the whole texture
	int textureWidth;
	int textureHeight;

private:
};

#endif