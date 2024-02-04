#ifndef C_COLLISION_COMPONENT
#define C_COLLISION_COMPONENT
#include "Component.h"
#include "Rect.h"
#include "SDL/SDL_rect.h"

class CollisionComponent : public Component {
public:
	enum CollisionLayer {
		BACKGROUND,
		FOREGROUND,
		COLLISION_OFF,
	};
	CollisionComponent(Actor* owner,  CollisionLayer layer = COLLISION_OFF);

	~CollisionComponent() {};
	void update(float deltaTime) override;
	virtual void handleCollision(CollisionComponent* other);
	bool collidesWith(CollisionComponent* other);

	void setCollisionLayer(CollisionLayer layer);
	void setSize(Vector2D rect);

	const Rect getRect() const;

protected:
	CollisionLayer collisionLayer;
	Vector2D size;

private:
};

#endif