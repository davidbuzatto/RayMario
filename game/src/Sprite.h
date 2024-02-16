/**
 * @file Sprite.h
 * @author Prof. Dr. David Buzatto
 * @brief Sprite class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "CollisionType.h"
#include "CollisionProbe.h"
#include "Direction.h"
#include "Drawable.h"
#include "raylib.h"
#include "SpriteState.h"

class Sprite : public virtual Drawable {

protected:
    Vector2 pos;
    Vector2 dim;
    Vector2 vel;
    float angle;
    Color color;
    SpriteState state;

    float frameTime;
    float frameAcum;
    int currentFrame;
    int maxFrames;
    Direction facingDirection;

    CollisionProbe cpN;
    CollisionProbe cpS;
    CollisionProbe cpE;
    CollisionProbe cpW;

public:

    Sprite();
    Sprite( Vector2 pos, Vector2 dim, Color color );
    Sprite( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    Sprite( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames, Direction facingDirection );
    Sprite( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    Sprite( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float frameTime, int maxFrames );
    Sprite( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float frameTime, int maxFrames, Direction facingDirection );
    virtual ~Sprite();   // virtual destructor enables polimorphism

    virtual void update() = 0;
    virtual void draw() = 0;
    virtual CollisionType checkCollision( Sprite &sprite ) = 0;
    virtual void updateCollisionProbes();

    void setPos( Vector2 pos );
    void setPos( float x, float y );
    void setX( float x );
    void setY( float y );

    void setDim( Vector2 dim );
    void setDim( float width, float height );
    void setWidth( float width );
    void setHeight( float height );

    void setVel( Vector2 vel );
    void setVel( float velX, float velY );
    void setVelX( float velX );
    void setVelY( float velY );

    void setAngle( float angle );

    void setColor( Color color );
    void setState( SpriteState state );
    void setFacingDirection( Direction facingDirection );

    Vector2 &getPos();
    float getX();
    float getY();
    Vector2 getCenter();

    Vector2 &getDim();
    float getWidth();
    float getHeight();

    Vector2 &getVel();
    float getVelX();
    float getVelY();
    
    float getAngle();

    Color &getColor();
    SpriteState getState();
    Direction getFacingDirection();

    Rectangle getRect();

};