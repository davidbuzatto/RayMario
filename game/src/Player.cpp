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

Player::Player( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float speedX, float maxSpeedX, float jumpSpeed ) :
    Sprite( pos, dim, vel, color ),
    speedX( speedX ),
    maxSpeedX( maxSpeedX ),
    jumpSpeed( jumpSpeed ),
    facingDirection( Direction::RIGHT ),
    crouched( false ),
    frameTimeWalking( 0.1 ),
    frameTimeRunning( 0.05 ),
    frameAcum( 0 ),
    currentFrame( 0 ),
    maxFrames( 2 ),
    activationWidth( 0 ) {

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
    bool running = IsKeyDown( KEY_LEFT_CONTROL ) || IsGamepadButtonDown( 0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT );
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

        /*if ( IsKeyDown( KEY_DOWN ) ||
             IsGamepadButtonDown( 0, GAMEPAD_BUTTON_LEFT_FACE_DOWN ) ||
             GetGamepadAxisMovement( 0, GAMEPAD_AXIS_LEFT_Y ) > 0 ) {
            crouched = true;
        } else {
            crouched = false;
        }*/

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
        if ( currentFrame == 0 ) {
            DrawTexture( textures["mario1Dy"], pos.x, pos.y, WHITE );
        } else if ( currentFrame == 1 ) {
            DrawTexture( textures["mario2Dy"], pos.x, pos.y, WHITE );
        }
    } else {

        if ( facingDirection == Direction::RIGHT ) {
            if ( state == SpriteState::ON_GROUND ) {
                if ( crouched ) {
                    DrawTexture( textures["marioDR"], pos.x, pos.y, WHITE );
                } else {
                    if ( currentFrame == 0 ) {
                        DrawTexture( textures["mario1R"], pos.x, pos.y, WHITE );
                    } else if ( currentFrame == 1 ) {
                        DrawTexture( textures["mario2R"], pos.x, pos.y, WHITE );
                    }
                }
            } else if ( state == SpriteState::JUMPING ) {
                if ( vel.y < 0 ) {
                    DrawTexture( textures["mario1JR"], pos.x, pos.y, WHITE );
                } else {
                    DrawTexture( textures["mario2JR"], pos.x, pos.y, WHITE );
                }
            }
        } else {
            if ( state == SpriteState::ON_GROUND ) {
                if ( crouched ) {
                    DrawTexture( textures["marioDL"], pos.x, pos.y, WHITE );
                } else {
                    if ( currentFrame == 0 ) {
                        DrawTexture( textures["mario1L"], pos.x, pos.y, WHITE );
                    } else if ( currentFrame == 1 ) {
                        DrawTexture( textures["mario2L"], pos.x, pos.y, WHITE );
                    }
                }
            } else if ( state == SpriteState::JUMPING ) {
                if ( vel.y < 0 ) {
                    DrawTexture( textures["mario1JL"], pos.x, pos.y, WHITE );
                } else {
                    DrawTexture( textures["mario2JL"], pos.x, pos.y, WHITE );
                }
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
        Rectangle tileRect( tile.getX(), tile.getY(), tile.getWidth(), tile.getHeight() );

        if ( CheckCollisionRecs( cpN.getRect(), tileRect) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpN.getColor() );
            }
            return CollisionType::NORTH;
        } else if ( CheckCollisionRecs( cpS.getRect(), tileRect) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpS.getColor() );
            }
            return CollisionType::SOUTH;
        } else if ( CheckCollisionRecs( cpE.getRect(), tileRect) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpE.getColor() );
            }
            return CollisionType::EAST;
        } else if ( CheckCollisionRecs( cpW.getRect(), tileRect) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpW.getColor() );
            }
            return CollisionType::WEST;
        }

    } catch ( std::bad_cast const& ) {
    }

    return CollisionType::NONE;

}

CollisionType Player::checkCollisionGoomba( Sprite &sprite ) {

    try {
        
        Goomba &goomba = dynamic_cast<Goomba&>(sprite);
        Rectangle goombaRect = goomba.getRect();
        
        if ( state == SpriteState::JUMPING || vel.y > 0 ) {
            if ( CheckCollisionRecs( cpN.getRect(), goombaRect ) ) {
                return CollisionType::NORTH;
            } else if ( CheckCollisionRecs( cpS.getRect(), goombaRect ) ) {
                return CollisionType::SOUTH;
            } else if ( CheckCollisionRecs( cpE.getRect(), goombaRect ) ) {
                return CollisionType::EAST;
            } else if ( CheckCollisionRecs( cpW.getRect(), goombaRect ) ) {
                return CollisionType::WEST;
            }
        }

    } catch ( std::bad_cast const& ) {
    }

    return CollisionType::NONE;

}

void Player::updateCollisionProbes() {

    cpN.setX( pos.x + dim.x / 2 - cpN.getWidth() / 2 );
    cpN.setY( pos.y );

    cpS.setX( pos.x + dim.x / 2 - cpS.getWidth() / 2 );
    cpS.setY( pos.y + dim.y - cpS.getHeight() );

    cpE.setX( pos.x + dim.x - cpE.getWidth() );
    cpE.setY( pos.y + dim.y / 2 - cpE.getHeight() / 2 );

    cpW.setX( pos.x );
    cpW.setY( pos.y + dim.y / 2 - cpW.getHeight() / 2 );

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

void Player::setActivationWidth( float activationWidth ) {
    this->activationWidth = activationWidth;
}