/**
 * @file Player.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Player class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Player.h"
#include "Direction.h"
#include "GameWorld.h"
#include "Goomba.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "Tile.h"
#include <iostream>
#include <typeinfo>
#include <utils.h>

Player::Player( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float speedX, float maxSpeedX, float jumpSpeed, bool immortal ) :
    Sprite( pos, dim, vel, color, 0, 2 ),
    speedX( speedX ),
    maxSpeedX( maxSpeedX ),
    jumpSpeed( jumpSpeed ),
    immortal( immortal ),
    ducking( false ),
    lookigUp( false ),
    running( false ),
    frameTimeWalking( 0.1 ),
    frameTimeRunning( 0.05 ),
    activationWidth( 0 ),
    coins( 0 ),
    lives( 5 ),
    points( 0 ),
    time( 400 ) {

    setState( SpriteState::ON_GROUND );

    cpN.setColor( PINK );
    cpS.setColor( VIOLET );
    cpE.setColor( YELLOW );
    cpW.setColor( LIME );

    updateCollisionProbes();
    
}

Player::~Player() {
}

void Player::update() {
    
    std::map<std::string, Sound>& sounds = ResourceManager::getSounds();
    float delta = GetFrameTime();
    running = IsKeyDown( KEY_LEFT_CONTROL ) || IsGamepadButtonDown( 0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT );
    float currentSpeedX = running ? maxSpeedX : speedX;
    float currentFrameTime = running && state != SpriteState::DYING ? frameTimeRunning : frameTimeWalking;

    if ( vel.x != 0 || state == SpriteState::DYING ) {
        frameAcum += delta;
        if ( frameAcum >= currentFrameTime ) {
            frameAcum = 0;
            currentFrame++;
            currentFrame %= maxFrames;
        }
    } else {
        currentFrame = 0;
    }

    if ( state != SpriteState::DYING ) {

        if ( IsKeyDown( KEY_RIGHT ) ||
             IsGamepadButtonDown( 0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT ) ||
             GetGamepadAxisMovement( 0, GAMEPAD_AXIS_LEFT_X ) > 0 ) {
            facingDirection = Direction::RIGHT;
            vel.x = currentSpeedX;
        } else if ( IsKeyDown( KEY_LEFT ) ||
                    IsGamepadButtonDown( 0, GAMEPAD_BUTTON_LEFT_FACE_LEFT ) ||
                    GetGamepadAxisMovement( 0, GAMEPAD_AXIS_LEFT_X ) < 0 ) {
            facingDirection = Direction::LEFT;
            vel.x = -currentSpeedX;
        } else {
            vel.x = 0;
        }

        if ( IsKeyDown( KEY_UP ) ||
             IsGamepadButtonDown( 0, GAMEPAD_BUTTON_LEFT_FACE_UP ) ||
             GetGamepadAxisMovement( 0, GAMEPAD_AXIS_LEFT_Y ) < 0 ) {
            lookigUp = true;
        } else {
            lookigUp = false;
            if ( IsKeyDown( KEY_DOWN ) ||
                 IsGamepadButtonDown( 0, GAMEPAD_BUTTON_LEFT_FACE_DOWN ) ||
                 GetGamepadAxisMovement( 0, GAMEPAD_AXIS_LEFT_Y ) > 0 ) {
                ducking = true;
            } else {
                ducking = false;
            }
        }

        if ( ( IsKeyPressed( KEY_SPACE ) ||
               IsGamepadButtonDown( 0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN ) ) && state != SpriteState::JUMPING ) {
            vel.y = jumpSpeed;
            state = SpriteState::JUMPING;
            PlaySound( sounds["jump"] );
        }

        pos.x = pos.x + vel.x * delta;
        pos.y = pos.y + vel.y * delta;

        vel.y += GameWorld::gravity;

    }

}

void Player::draw() {

    std::map<std::string, Texture2D> &textures = ResourceManager::getTextures();
    
    if ( state == SpriteState::DYING ) {
        DrawTexture( textures[std::string( TextFormat( "mario%dDy", currentFrame ) )], pos.x, pos.y, WHITE );
    } else {

        char dir = facingDirection == Direction::RIGHT ? 'R' : 'L';

        if ( state == SpriteState::ON_GROUND ) {

            if ( lookigUp ) {
                DrawTexture( textures[std::string( TextFormat( "mario0Lu%c", dir ) )], pos.x, pos.y, WHITE );
            } else if ( ducking ) {
                DrawTexture( textures[std::string( TextFormat( "mario0Du%c", dir ) )], pos.x, pos.y, WHITE );
            } else if ( running ) {
                DrawTexture( textures[std::string( TextFormat( "mario%dRu%c", currentFrame, dir ) )], pos.x, pos.y, WHITE );
            } else { // iddle
                DrawTexture( textures[std::string( TextFormat( "mario%d%c", currentFrame, dir ) )], pos.x, pos.y, WHITE );
            }

        } else if ( state == SpriteState::JUMPING ) {
            
            if ( vel.y < 0 ) {
                if ( running ) {
                    DrawTexture( textures[std::string( TextFormat( "mario0JuRu%c", dir ) )], pos.x, pos.y, WHITE );
                } else {
                    DrawTexture( textures[std::string( TextFormat( "mario0Ju%c", dir ) )], pos.x, pos.y, WHITE );
                }
            } else {
                DrawTexture( textures[std::string( TextFormat( "mario0Fa%c", dir ) )], pos.x, pos.y, WHITE );
            }
        }

    }

    if ( GameWorld::debug ) {
        cpN.draw();
        cpS.draw();
        cpE.draw();
        cpW.draw();
        DrawRectangleLines( 
            pos.x + dim.x / 2 - activationWidth / 2, 
            pos.y + dim.y / 2 - activationWidth / 2, 
            activationWidth, activationWidth, BLACK );
    }

}

CollisionType Player::checkCollision( Sprite &sprite ) {
    return CollisionType::NONE;
}

CollisionType Player::checkCollisionTile( Sprite& sprite ) {
    
    try {

        Tile& tile = dynamic_cast<Tile&>( sprite );
        Rectangle tileRect = tile.getRect();

        if ( cpN.checkCollision( tileRect ) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpN.getColor() );
            }
            return CollisionType::NORTH;
        } else if ( cpS.checkCollision( tileRect ) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpS.getColor() );
            }
            return CollisionType::SOUTH;
        } else if ( cpE.checkCollision( tileRect ) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpE.getColor() );
            }
            return CollisionType::EAST;
        } else if ( cpW.checkCollision( tileRect ) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpW.getColor() );
            }
            return CollisionType::WEST;
        }

    } catch ( std::bad_cast const& ) {
    }

    return CollisionType::NONE;

}

CollisionType Player::checkCollisionBaddie( Sprite &sprite ) {

    try {
        
        Baddie &baddie = dynamic_cast<Baddie&>(sprite);
        Rectangle baddieRect = baddie.getRect();
        
        if ( state == SpriteState::JUMPING || vel.y > 0 ) {
            if ( cpN.checkCollision( baddieRect ) ) {
                return CollisionType::NORTH;
            } else if ( cpS.checkCollision( baddieRect ) ) {
                return CollisionType::SOUTH;
            } else if ( cpE.checkCollision( baddieRect ) ) {
                return CollisionType::EAST;
            } else if ( cpW.checkCollision( baddieRect ) ) {
                return CollisionType::WEST;
            }
        }

    } catch ( std::bad_cast const& ) {
    }

    return CollisionType::NONE;

}

void Player::drawHud() {

    std::map<std::string, Texture2D>& textures = ResourceManager::getTextures();

    DrawTexture( textures["guiMario" ], 34, 32, WHITE );
    DrawTexture( textures["guiX" ], 54, 49, WHITE );
    drawSmallNumber( lives, 68, 49, textures, "guiNumbersWhite" );
    
    DrawTexture( textures["guiCoin"], GetScreenWidth() - 115, 32, WHITE );
    DrawTexture( textures["guiX"], GetScreenWidth() - 97, 34, WHITE );
    drawSmallNumber( coins, GetScreenWidth() - 34 - std::to_string( coins ).length() * 16, 34, textures, "guiNumbersWhite" );
    drawSmallNumber( points, GetScreenWidth() - 34 - std::to_string( points ).length() * 16, 50, textures, "guiNumbersWhite");

    int t = time - ( (int) GetTime() );
    DrawTexture( textures["guiTime"], GetScreenWidth() - 34 - 176, 32, WHITE );
    drawSmallNumber( t, GetScreenWidth() - 34 - 128 - std::to_string( t ).length() * 16, 50, textures, "guiNumbersYellow");

    DrawTexture( textures["guiNextItem"], GetScreenWidth() / 2 - textures["guiNextItem"].width / 2, 20, WHITE );

}

float Player::getSpeedX() {
    return speedX;
}

float Player::getMaxSpeedX() {
    return maxSpeedX;
}

float Player::getJumpSpeed() {
    return jumpSpeed;
}

float Player::getActivationWidth() {
    return activationWidth;
}

void Player::setImmortal( bool immortal ) {
    this->immortal = immortal;
}

bool Player::isImmortal() {
    return immortal;
}

void Player::setActivationWidth( float activationWidth ) {
    this->activationWidth = activationWidth;
}

void Player::setLives( int lives ) {
    this->lives = lives;
}

void Player::setCoins( int coins ) {
    this->coins = coins;
}

void Player::setPoints( int points ) {
    this->points = points;
}

int Player::getLives() {
    return lives;
}

int Player::getCoins() {
    return coins;
}

int Player::getPoints() {
    return points;
}

void Player::addLives( int lives ) {
    this->lives += lives;
}

void Player::removeLives( int lives ) {
    this->lives -= lives;
}

void Player::addCoins( int coins ) {
    this->coins += coins;
}

void Player::removeCoins( int coins ) {
    this->coins -= coins;
}

void Player::addPoints( int points ) {
    this->points += points;
}

void Player::removePoints( int points ) {
    this->points -= points;
}