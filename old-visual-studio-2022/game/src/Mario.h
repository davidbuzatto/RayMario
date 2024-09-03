/**
 * @file Mario.h
 * @author Prof. Dr. David Buzatto
 * @brief Mario class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

class GameWorld;
class Map;

#include "CollisionProbe.h"
#include "CollisionType.h"
#include "Fireball.h"
#include "MarioType.h"
#include "raylib.h"
#include "Sprite.h"
#include <vector>

class Mario : public Sprite {

    float speedX;
    float maxSpeedX;
    float jumpSpeed;
    float dyingVelY;
    bool immortal;
    bool invulnerable;
    float invulnerableTime;
    float invulnerableTimeAcum;
    bool invulnerableBlink;

    bool ducking;
    bool lookingUp;
    bool running;
    bool invincible;

    float frameTimeWalking;
    float frameTimeRunning;

    float activationWidth;

    int lives;
    int coins;
    int yoshiCoins;
    int points;
    float maxTime;
    float ellapsedTime;

    MarioType type;

    CollisionProbe cpE1;
    CollisionProbe cpW1;

    MarioType reservedPowerUp;

    std::vector<Fireball> fireballs;

    float runningAcum;
    float runningTime;
    bool drawRunningFrames;

    float movingAcum;

    float transitioningFrameTime;
    float transitioningFrameAcum;
    int transitionSteps;
    int superToFlowerTransitionSteps;
    int transitionCurrentFrame;
    int transitionCurrentFramePos;
    const int transitionFrameOrder[11] = { 0, 1, 0, 1, 0, 1, 2, 1, 2, 1, 2 };
    const int reverseTransitionFrameOrder[11] = { 2, 1, 2, 1, 2, 1, 0, 1, 0, 1, 0 };
    const int superToFlowerTransitionFrameOrder[11] = { 0, 1, 0, 1, 0, 1, 0, 1 };

    float invincibleTime;
    float invincibleAcum;

    bool playerDownMusicStreamPlaying;
    bool gameOverMusicStreamPlaying;

    Vector2 lastPos;
    SpriteState lastStateBeforeTransition;
    GameWorld *gw;
    Map *map;
    
public:

    Mario( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float speedX, float maxSpeedX, float jumpSpeed, bool immortal );
    ~Mario() override;

    void update() override;
    void draw() override;
    void updateCollisionProbes() override;
    void drawHud() const;

    CollisionType checkCollision( Sprite *sprite ) override;
    CollisionType checkCollisionBaddie( Sprite *sprite );

    void setImmortal( bool immortal );
    void setActivationWidth( float activationWidth );
    
    float getSpeedX() const;
    float getMaxSpeedX() const;
    float getJumpSpeed() const;
    bool isImmortal() const;
    float getActivationWidth() const;

    void setLives( int lives );
    void setCoins( int coins );
    void setYoshiCoins( int yoshiCoins );
    void setPoints( int points );
    void setMaxTime( float maxTime );
    void setLastStateBeforeTransition( SpriteState lastStateBeforeTransition );

    void setGameWorld( GameWorld *gw );
    void setMap( Map *map );

    GameWorld* getGameWorld() const;
    Map* getMap() const;

    int getLives() const;
    int getCoins() const;
    int getYoshiCoins() const;
    int getPoints() const;
    int getRemainingTime() const;

    void addLives( int lives );
    void removeLives( int lives );
    void addCoins( int coins );
    void addYoshiCoins( int yoshiCoins );
    void removeCoins( int coins );
    void addPoints( int points );
    void removePoints( int points );
    
    void changeToSmall();
    void changeToSuper();
    void changeToFlower();

    void setReservedPowerUp( MarioType reservedPowerUp );
    MarioType getReservedPowerUp() const;
    void releaseReservedPowerUp();

    MarioType getType() const;
    void setInvulnerable( bool invulnerable );
    bool isInvulnerable() const;

    void setInvincible( bool invincible );
    bool isInvincible() const;

    bool isTransitioning() const;

    void reset( bool removePowerUps );
    void resetAll();

    void playPlayerDownMusicStream();
    void playGameOverMusicStream();
    bool isPlayerDownMusicStreamPlaying() const;
    bool isGameOverMusicStreamPlaying() const;

    Vector2 getSouthCollisionProbePos() const;

};