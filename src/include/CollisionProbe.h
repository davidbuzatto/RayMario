/**
 * @file CollisionProbe.h
 * @author Prof. Dr. David Buzatto
 * @brief CollisionProbe class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "CollisionType.h"
#include "Drawable.h"
#include "raylib.h"

class CollisionProbe : public virtual Drawable {

    Vector2 pos;
    Vector2 dim;
    Color color;

public:

    CollisionProbe();
    CollisionProbe( Vector2 pos, Vector2 dim, Color color );
    ~CollisionProbe() override;

    void draw() override;
    CollisionType checkCollision( Rectangle &rect ) const;

    void setPos( Vector2 pos );
    void setPos( float x, float y );
    void setX( float x );
    void setY( float y );

    void setDim( Vector2 dim );
    void setDim( float width, float height );
    void setWidth( float width );
    void setHeight( float height );

    void setColor( Color color );

    Vector2& getPos();
    float getX() const;
    float getY() const;

    Vector2& getDim();
    float getWidth() const;
    float getHeight() const;

    Color& getColor();
    Rectangle getRect() const;

};