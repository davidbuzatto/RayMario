/**
 * @file Map.h
 * @author Prof. Dr. David Buzatto
 * @brief Map class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Baddie.h"
#include "Drawable.h"
#include "Mario.h"
#include "raylib.h"
#include "Sprite.h"
#include "Item.h"
#include "Tile.h"
#include <map>
#include <vector>

class Map : public virtual Drawable {

    std::vector<Tile> tiles;
    float maxWidth;
    float maxHeight;
    float marioOffset;

    Texture2D backgroundTexture;
    bool parsed;

    std::vector<Item*> items;
    std::vector<Baddie*> baddies;

    Mario &mario;

    Color backgroundColor;
    int backgroundId;
    int maxBackgroundId;
    int musicId;
    int maxMusicId;

    int id;
    int maxId;
    bool loadTestMap;

public:

    static int tileWidth;

    Map( Mario &mario, int mapNumber, bool loadTestMap );
    ~Map();
    virtual void draw();
    std::vector<Tile> &getTiles();
    std::vector<Item*> &getItems();
    std::vector<Baddie*> &getBaddies();
    void parseMap();
    float getMaxWidth();
    float getMaxHeight();
    void setMarioOffset( float marioOffset );
    void playMusic();
    void reset();
    bool next();
    void first();

};