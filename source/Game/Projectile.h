#ifndef C_PROJECTILE
#define C_PROJECTILE
#include "Ball.h"

class Paddle;
class Projectile : public Ball {
public:
    //Default constructor
    Projectile(
        Vector2D boundaryMinimum,
        Vector2D boundaryMaximum,
        Vector2D shape,
        Vector2D position,
        Vector2D velocity,
        SDL_Color* color,
        float maxSpeed,
        Paddle* parent
    );
    virtual void update(float deltaTime) override;

public: //ICollideable overrides
    virtual void resolveCollision(ICollideable* other) override;
    void launch(Vector2D startingPosition);

    virtual IGameObject* getParent() override;

private: //Functions
    Projectile();

protected://data
    Paddle* parent;
    

};

#endif