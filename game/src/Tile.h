/**
 * @file Tile.h
 * @author Prof. Dr. David Buzatto
 * @brief Tile class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Sprite.h"
#include <string>

class Tile : public virtual Sprite {

protected:
    std::string key;
    bool visible;
    bool onlyBaddies;
    bool showCollisionOnDebug;

public:

    Tile( Vector2 pos, Vector2 dim, Color color, std::string key, bool visible );
    Tile( Vector2 pos, Vector2 dim, Color color, std::string key, bool visible, bool onlyBaddies );
    ~Tile() override;

    void update() override;
    void draw() override;

    bool isOnlyBaddies() const;

};