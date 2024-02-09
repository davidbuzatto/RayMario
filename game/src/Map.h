/**
 * @file Map.h
 * @author Prof. Dr. David Buzatto
 * @brief Map class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Baddie.h"
#include "Coin.h"
#include "Drawable.h"
#include "Player.h"
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

    std::vector<Coin> coins;
    std::vector<Baddie*> baddies;

    Player &player;

    Color backgroundColor;
    int backgroundId;
    int maxBackgroundId;
    int musicId;
    int maxMusicId;

public:

    Map( Player &player );
    ~Map();
    virtual void draw();
    std::vector<Tile> &getTiles();
    std::vector<Coin> &getCoins();
    std::vector<Baddie*> &getBaddies();
    void parseMap( int mapNumber, bool loadTestMap );
    float getMaxWidth();
    float getMaxHeight();
    void setPlayerOffset( float playerOffset );
    void playMusic();

    static int tileWidth;

};