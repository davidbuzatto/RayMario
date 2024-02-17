/**
 * @file Map.h
 * @author Prof. Dr. David Buzatto
 * @brief Map class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

class Block;

#include "Baddie.h"
#include "Block.h"
#include "Drawable.h"
#include "Mario.h"
#include "raylib.h"
#include "Sprite.h"
#include "Item.h"
#include "Tile.h"
#include <map>
#include <vector>

class Map : public virtual Drawable {

    std::vector<Tile*> tiles;
    std::vector<Block*> blocks;
    std::vector<Item*> items;
    std::vector<Item*> staticItems;
    std::vector<Baddie*> baddies;

    int id;
    int maxId;

    float maxWidth;
    float maxHeight;

    Mario& mario;
    float marioOffset;
    
    int backgroundId;
    int maxBackgroundId;
    Color backgroundColor;
    Texture2D backgroundTexture;
    
    int musicId;
    int maxMusicId;

    bool parseBlocks;
    bool parseItems;
    bool parseBaddies;

    bool loadTestMap;
    bool parsed;

public:

    static int tileWidth;

    Map( Mario &mario, int mapNumber, bool loadTestMap, bool parseBlocks, bool parseItems, bool parseBaddies );
    ~Map();
    virtual void draw();
    std::vector<Tile*> &getTiles();
    std::vector<Block*>& getBlocks();
    std::vector<Item*> &getItems();
    std::vector<Item*> &getStaticItems();
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