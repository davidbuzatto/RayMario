/**
 * @file Sprite.h
 * @author Prof. Dr. David Buzatto
 * @brief Sprite class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Drawable.h"

class Sprite : public virtual Drawable {

protected:
    Vector2 pos;
    Vector2 dim;
    Vector2 vel;
    Color color;

public:
    Sprite( Vector2 pos, Vector2 dim, Color color );
    Sprite( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~Sprite();
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual bool checkCollision( Sprite &sprite ) = 0;

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

    void setColor( Color color );

    Vector2 &getPos();
    float getX();
    float getY();

    Vector2 &getDim();
    float getWidth();
    float getHeight();

    Vector2 &getVel();
    float getVelX();
    float getVelY();
    
    Color &getColor();

};