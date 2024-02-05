/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld class declaration. This class should contain all
 * game components and its state.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Player.h"
#include "Map.h"
#include "Drawable.h"

class GameWorld : public virtual Drawable {

    Player player;
    Map map;
    Camera2D *camera;
    
public:

    static bool debug;
    static float gravity;
    
    /**
     * @brief Construct a new GameWorld object.
     */
    GameWorld();

    /**
     * @brief Destroy the GameWorld object.
     */
    ~GameWorld();

    /**
     * @brief Reads user input and updates the state of the game.
     */
    void inputAndUpdate();

    /**
     * @brief Draws the state of the game.
     */
    virtual void draw();

    /**
     * @brief Load game resources like images, textures, sounds, fonts, shaders,
     * etc.
     * Should be called inside the constructor.
     */
    static void loadResources();

    /**
     * @brief Unload the once loaded game resources.
     * Should be called inside the destructor.
     */
    static void unloadResources();

    void setCamera( Camera2D *camera );
    
};