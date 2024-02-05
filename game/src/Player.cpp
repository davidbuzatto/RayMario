/**
 * @file Player.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Player class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Player.h"
#include "ResourceManager.h"
#include "PlayerState.h"
#include "Direction.h"
#include "GameWorld.h"
#include "Goomba.h"
#include "Tile.h"
#include <typeinfo>
#include <iostream>
#include "raylib.h"

Player::Player( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float speedX, float maxSpeedX, float jumpSpeed ) :
    Sprite( pos, dim, vel, color ),
    speedX( speedX ),
    maxSpeedX( maxSpeedX ),
    jumpSpeed( jumpSpeed ),
    state( PlayerState::ON_GROUND ),
    facingDirection( Direction::RIGHT ),
    crouched( false ),
    frameTimeWalking( 0.1 ),
    frameTimeRunning( 0.05 ),
    frameAcum( 0 ),
    currentFrame( 0 ),
    maxFrames( 2 ),
    activationWidth( 0 ) {

    cpN.setColor( PINK );
    cpS.setColor( VIOLET );
    cpE.setColor( YELLOW );
    cpW.setColor( LIME );

    updateCollisionProbes();
    
}

Player::~Player() {
}

void Player::update() {
    
    std::map<std::string, Sound> &sounds = ResourceManager::getSounds();
    float delta = GetFrameTime();
    bool running = IsKeyDown( KEY_LEFT_CONTROL ) || IsGamepadButtonDown( 0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT );
    float currentSpeedX = running ? maxSpeedX : speedX;
    float currentFrameTime = running ? frameTimeRunning : frameTimeWalking;

    if ( vel.x != 0 ) {
        frameAcum += delta;
        if ( frameAcum >= currentFrameTime ) {
            frameAcum = 0;
            currentFrame++;
            currentFrame %= maxFrames;
        }
    } else {
        currentFrame = 0;
    }

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
           IsGamepadButtonDown( 0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN ) ) && state != PlayerState::JUMPING ) {
        vel.y = jumpSpeed;
        state = PlayerState::JUMPING;
        PlaySound( sounds["jump"] );
    }

    pos.x = pos.x + vel.x * delta;
    pos.y = pos.y + vel.y * delta;

    vel.y += GameWorld::gravity;

}

void Player::draw() {

    std::map<std::string, Texture2D> &textures = ResourceManager::getTextures();
    
    if ( facingDirection == Direction::RIGHT ) {
        if ( state == PlayerState::ON_GROUND ) {
            if ( crouched ) {
                DrawTexture( textures["marioDR"], pos.x, pos.y, WHITE );
            } else {
                if ( currentFrame == 0 ) {
                    DrawTexture( textures["mario1R"], pos.x, pos.y, WHITE );
                } else if ( currentFrame == 1 ) {
                    DrawTexture( textures["mario2R"], pos.x, pos.y, WHITE );
                }
            }
        } else if ( state == PlayerState::JUMPING ) {
            if ( vel.y < 0 ) {
                DrawTexture( textures["mario1JR"], pos.x, pos.y, WHITE );
            } else {
                DrawTexture( textures["mario2JR"], pos.x, pos.y, WHITE );
            }
        }
    } else {
        if ( state == PlayerState::ON_GROUND ) {
            if ( crouched ) {
                DrawTexture( textures["marioDL"], pos.x, pos.y, WHITE );
            } else {
                if ( currentFrame == 0 ) {
                    DrawTexture( textures["mario1L"], pos.x, pos.y, WHITE );
                } else if ( currentFrame == 1 ) {
                    DrawTexture( textures["mario2L"], pos.x, pos.y, WHITE );
                }
            }
        } else if ( state == PlayerState::JUMPING ) {
            if ( vel.y < 0 ) {
                DrawTexture( textures["mario1JL"], pos.x, pos.y, WHITE );
            } else {
                DrawTexture( textures["mario2JL"], pos.x, pos.y, WHITE );
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

bool Player::checkCollision( Sprite &sprite ) {
    return false;
}

bool Player::checkCollisionTile( Sprite &sprite ) {

    try {

        updateCollisionProbes();
        Tile &tile = dynamic_cast<Tile&>(sprite);
        Rectangle tileRect( tile.getX(), tile.getY(), tile.getWidth(), tile.getHeight() );

        Rectangle cpNRect( cpN.getX(), cpN.getY(), cpN.getWidth(), cpN.getHeight() );
        Rectangle cpSRect( cpS.getX(), cpS.getY(), cpS.getWidth(), cpS.getHeight() );
        Rectangle cpERect( cpE.getX(), cpE.getY(), cpE.getWidth(), cpE.getHeight() );
        Rectangle cpWRect( cpW.getX(), cpW.getY(), cpW.getWidth(), cpW.getHeight() );

        if ( CheckCollisionRecs( cpNRect, tileRect ) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpN.getColor() );
            }
            pos.y = tile.getY() + tile.getHeight();
            vel.y = 0;
            updateCollisionProbes();
            return true;
        } else if ( CheckCollisionRecs( cpSRect, tileRect ) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpS.getColor() );
            }
            pos.y = tile.getY() - dim.y;
            vel.y = 0;
            updateCollisionProbes();
            state = PlayerState::ON_GROUND;
            return true;
        } else if ( CheckCollisionRecs( cpERect, tileRect ) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpE.getColor() );
            }
            pos.x = tile.getX() - dim.x;
            vel.x = 0;
            updateCollisionProbes();
            return true;
        } else if ( CheckCollisionRecs( cpWRect, tileRect ) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpW.getColor() );
            }
            pos.x = tile.getX() + tile.getWidth();
            vel.x = 0;
            updateCollisionProbes();
            return true;
        }

    } catch ( std::bad_cast const& ) {
    }

    return false;

}

bool Player::checkCollisionGoomba( Sprite &sprite ) {

    try {
        
        updateCollisionProbes();
        Goomba &goomba = dynamic_cast<Goomba&>(sprite);
        Rectangle goombaRect( goomba.getX(), goomba.getY(), goomba.getWidth(), goomba.getHeight() );

        Rectangle cpNRect( cpN.getX(), cpN.getY(), cpN.getWidth(), cpN.getHeight() );
        Rectangle cpSRect( cpS.getX(), cpS.getY(), cpS.getWidth(), cpS.getHeight() );
        Rectangle cpERect( cpE.getX(), cpE.getY(), cpE.getWidth(), cpE.getHeight() );
        Rectangle cpWRect( cpW.getX(), cpW.getY(), cpW.getWidth(), cpW.getHeight() );
        
        if ( state == PlayerState::JUMPING || vel.y > 0 ) {
            if ( CheckCollisionRecs( cpNRect, goombaRect ) ||
                 CheckCollisionRecs( cpERect, goombaRect ) ||
                 CheckCollisionRecs( cpWRect, goombaRect ) ) {
                // die
                updateCollisionProbes();
                return false;
            } else if ( CheckCollisionRecs( cpSRect, goombaRect ) ) {
                pos.y = goomba.getY() - dim.y;
                vel.y = jumpSpeed;
                updateCollisionProbes();
                state = PlayerState::JUMPING;
                return true;
            }
        } else if ( CheckCollisionRecs( cpNRect, goombaRect ) ||
                    CheckCollisionRecs( cpSRect, goombaRect ) ||
                    CheckCollisionRecs( cpERect, goombaRect ) ||
                    CheckCollisionRecs( cpWRect, goombaRect ) ) {
            // die
            updateCollisionProbes();
            return false;
        }

    } catch ( std::bad_cast const& ) {
    }

    return false;

}

void Player::setState( PlayerState state ) {
    this->state = state;
}

PlayerState Player::getState() const {
    return state;
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