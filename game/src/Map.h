/**
 * @file Map.h
 * @author Prof. Dr. David Buzatto
 * @brief Map class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Coin.h"
#include "Drawable.h"
#include "Goomba.h"
#include "raylib.h"
#include "Sprite.h"
#include "Tile.h"
#include <map>
#include <vector>

class Map : public virtual Drawable {

    std::vector<Tile> tiles;
    float maxWidth;
    float maxHeight;
    float playerOffset;

    Texture2D backgroundTexture;
    bool parsed;
    int mapNumber;

    std::vector<Coin> coins;
    std::vector<Goomba> goombas;

public:

    Map();
    ~Map();
    virtual void draw();
    std::vector<Tile> &getTiles();
    std::vector<Coin> &getCoins();
    std::vector<Goomba> &getGoombas();
    void parseMap( int mapNumber, bool loadTestMap );
    float getMaxWidth();
    float getMaxHeight();
    void setPlayerOffset( float playerOffset );
    void playMusic();

    static int tileWidth;

};