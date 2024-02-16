/**
 * @file Mario.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Mario class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Mario.h"
#include "Direction.h"
#include "GameWorld.h"
#include "GameState.h"
#include "MarioType.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "Tile.h"
#include <iostream>
#include <typeinfo>
#include <utils.h>

Mario::Mario( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float speedX, float maxSpeedX, float jumpSpeed, bool immortal ) :
    Sprite( pos, dim, vel, color, 0, 2 ),
    speedX( speedX ),
    maxSpeedX( maxSpeedX ),
    jumpSpeed( jumpSpeed ),
    immortal( immortal ),
    invulnerable( false ),
    invulnerableTime( 2 ),
    invulnerableTimeAcum( 0 ),
    invulnerableBlink( false ),
    ducking( false ),
    lookigUp( false ),
    running( false ),
    frameTimeWalking( 0.1 ),
    frameTimeRunning( 0.05 ),
    activationWidth( 0 ),
    powerUpActivationRadius( 100 ),
    coins( 0 ),
    lives( 5 ),
    points( 0 ),
    maxTime( 0 ),
    ellapsedTime( 0.0f ),
    type( MarioType::SMALL ),
    reservedPowerUp( MarioType::SMALL ),
    runningAcum( 0 ),
    runningTime( 0.5 ),
    drawRunningFrames( false ),
    lastPos( pos ) {

    setState( SpriteState::ON_GROUND );

    cpN.setColor( PINK );
    cpS.setColor( VIOLET );
    cpE.setColor( YELLOW );
    cpE1.setColor( YELLOW );
    cpW.setColor( LIME );
    cpW1.setColor( LIME );

    updateCollisionProbes();
    
}

Mario::~Mario() {
}

void Mario::update() {
    
    running = ( IsKeyDown( KEY_LEFT_CONTROL ) || 
                IsGamepadButtonDown( 0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT ) ) &&
                vel.x != 0;

    if ( running ) {
        runningAcum += GetFrameTime();
        if ( runningAcum >= runningTime ) {
            drawRunningFrames = true;
        }
    } else {
        runningAcum = 0;
        drawRunningFrames = false;
    }

    if ( state != SpriteState::DYING && state != SpriteState::VICTORY ) {
        ellapsedTime += GetFrameTime();
    }

    float delta = GetFrameTime();
    float currentSpeedX = running ? ( drawRunningFrames ? maxSpeedX * 1.3 : maxSpeedX ) : speedX;
    float currentFrameTime = running && state != SpriteState::DYING ? frameTimeRunning : frameTimeWalking;
    std::map<std::string, Sound>& sounds = ResourceManager::getSounds();

    if ( ellapsedTime >= maxTime && state != SpriteState::DYING && state != SpriteState::VICTORY ) {
        state = SpriteState::DYING;
        PlaySound( sounds["playerDown"] );
        removeLives( 1 );
        GameWorld::state = GameState::TIME_UP;
    }

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

    if ( invulnerable ) {
        invulnerableTimeAcum += delta;
        invulnerableBlink = !invulnerableBlink;
        if ( invulnerableTimeAcum >= invulnerableTime ) {
            invulnerableTimeAcum = 0;
            invulnerable = false;
            invulnerableBlink = false;
        }
    }

    if ( state != SpriteState::DYING && state != SpriteState::VICTORY ) {

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
            if ( vel.x >= -10 && vel.x <= 10 ) {
                vel.x = 0;
            } else {
                vel.x = vel.x * 0.9;
            }
        }

        if ( state == SpriteState::ON_GROUND ) {
            if ( IsKeyDown( KEY_DOWN ) ||
                 IsGamepadButtonDown( 0, GAMEPAD_BUTTON_LEFT_FACE_DOWN ) ||
                 GetGamepadAxisMovement( 0, GAMEPAD_AXIS_LEFT_Y ) > 0 ) {
                ducking = true;
                vel.x = 0;
            } else {
                ducking = false;
            }
        }

        if ( ( IsKeyPressed( KEY_SPACE ) ||
               IsGamepadButtonPressed( 0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN ) ) && 
               state != SpriteState::JUMPING ) {
            if ( state == SpriteState::ON_GROUND ) {
                vel.y = jumpSpeed;
                state = SpriteState::JUMPING;
                PlaySound( sounds["jump"] );
            }
        }

        if ( ( IsKeyPressed( KEY_LEFT_CONTROL ) ||
               IsGamepadButtonPressed( 0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT ) ) &&
             type == MarioType::FLOWER ) {

            if ( facingDirection == Direction::RIGHT ) {
                fireballs.push_back( Fireball( Vector2( pos.x + dim.x / 2, pos.y + dim.y / 2 - 3 ), Vector2( 16, 16 ), Vector2( 400, 100 ), RED, Direction::RIGHT, 2 ) );
            } else {
                fireballs.push_back( Fireball( Vector2( pos.x, pos.y + dim.y / 2 - 3 ), Vector2( 16, 16 ), Vector2( -400, 100 ), RED, Direction::LEFT, 2 ) );
            }
            PlaySound( sounds["fireball"] );

        }

        std::vector<int> collectedIndexes;
        for ( size_t i = 0; i < fireballs.size(); i++ ) {
            fireballs[i].update();
            if ( fireballs[i].getState() == SpriteState::TO_BE_REMOVED ) {
                collectedIndexes.push_back(i);
            }
        }
        for ( int i = collectedIndexes.size() - 1; i >= 0; i-- ) {
            fireballs.erase( fireballs.begin() + collectedIndexes[i] );
        }

        pos.x = pos.x + vel.x * delta;
        pos.y = pos.y + vel.y * delta;

        vel.y += GameWorld::gravity;

        if ( (int) lastPos.y < (int) pos.y ) {
            state = SpriteState::FALLING;
        }
        lastPos = pos;

    }

}

void Mario::draw() {

    std::map<std::string, Texture2D> &textures = ResourceManager::getTextures();
    std::string prefix;

    switch ( type ) {
        default:
        case MarioType::SMALL:
            prefix = "small";
            break;
        case MarioType::SUPER:
            prefix = "super";
            break;
        case MarioType::FLOWER:
            prefix = "flower";
            break;
    }

    if ( state == SpriteState::DYING ) {
        DrawTexture( textures[std::string( TextFormat( "smallMario%dDy", currentFrame))], pos.x, pos.y, WHITE);
    } else {

        char dir = facingDirection == Direction::RIGHT ? 'R' : 'L';

        if ( !invulnerableBlink ) {

            if ( state == SpriteState::ON_GROUND ) {

                if ( lookigUp ) {
                    DrawTexture( textures[std::string( TextFormat( "%sMario0Lu%c", prefix.c_str(), dir ) )], pos.x, pos.y, WHITE );
                } else if ( ducking ) {
                    DrawTexture( textures[std::string( TextFormat( "%sMario0Du%c", prefix.c_str(), dir ) )], pos.x, pos.y, WHITE );
                } else if ( drawRunningFrames ) {
                    DrawTexture( textures[std::string( TextFormat( "%sMario%dRu%c", prefix.c_str(), currentFrame, dir ) )], pos.x, pos.y, WHITE );
                } else { // iddle
                    if ( ( IsKeyPressed( KEY_LEFT_CONTROL ) ||
                           IsGamepadButtonPressed( 0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT ) ) && 
                           type == MarioType::FLOWER ) {
                        DrawTexture( textures[std::string( TextFormat( "%sMario%dTf%c", prefix.c_str(), currentFrame, dir ) )], pos.x, pos.y, WHITE );
                    } else {
                        DrawTexture( textures[std::string( TextFormat( "%sMario%d%c", prefix.c_str(), currentFrame, dir ) )], pos.x, pos.y, WHITE );
                    }
                }

            } else if ( state == SpriteState::JUMPING ) {
                if ( drawRunningFrames ) {
                    DrawTexture( textures[std::string( TextFormat( "%sMario0JuRu%c", prefix.c_str(), dir ) )], pos.x, pos.y, WHITE );
                } else {
                    DrawTexture( textures[std::string( TextFormat( "%sMario0Ju%c", prefix.c_str(), dir ) )], pos.x, pos.y, WHITE );
                }
            } else if ( state == SpriteState::FALLING ) {
                DrawTexture( textures[std::string( TextFormat( "%sMario0Fa%c", prefix.c_str(), dir ) )], pos.x, pos.y, WHITE );
            } else if ( state == SpriteState::VICTORY ) {
                DrawTexture( textures[std::string( TextFormat( "%sMario0Vic", prefix.c_str() ) )], pos.x, pos.y, WHITE );
            }

        }

        for ( size_t i = 0; i < fireballs.size(); i++ ) {
            fireballs[i].draw();
        }

    }

    if ( GameWorld::debug ) {
        cpN.draw();
        cpS.draw();
        cpE.draw();
        cpE1.draw();
        cpW.draw();
        cpW1.draw();
        DrawRectangleLines( 
            pos.x + dim.x / 2 - activationWidth / 2, 
            pos.y + dim.y / 2 - activationWidth / 2, 
            activationWidth, activationWidth, BLACK );
        DrawCircleLines( 
            pos.x + dim.x / 2,
            pos.y + dim.y / 2,
            powerUpActivationRadius, BLACK );
    }

}

CollisionType Mario::checkCollision( Sprite &sprite ) {
    return CollisionType::NONE;
}

CollisionType Mario::checkCollisionTile( Sprite& sprite ) {
    
    try {

        Tile& tile = dynamic_cast<Tile&>( sprite );
        Rectangle tileRect = tile.getRect();

        for ( size_t i = 0; i < fireballs.size(); i++ ) {
            Fireball *f = &fireballs[i];
            switch ( f->checkCollisionTile( tile ) ) {
                case CollisionType::NORTH:
                    if ( GameWorld::debug ) {
                        tile.setColor( cpN.getColor() );
                    }
                    f->setVelY( -f->getVelY() );
                    break;
                case CollisionType::SOUTH:
                    if ( GameWorld::debug ) {
                        tile.setColor( cpS.getColor() );
                    }
                    f->setVelY( -300 );
                    break;
                case CollisionType::EAST:
                    if ( GameWorld::debug ) {
                        tile.setColor( cpE.getColor() );
                    }
                    f->setState( SpriteState::TO_BE_REMOVED );
                    break;
                case CollisionType::WEST:
                    if ( GameWorld::debug ) {
                        tile.setColor( cpW.getColor() );
                    }
                    f->setState( SpriteState::TO_BE_REMOVED );
                    break;
            }
        }

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
        } else if ( cpE.checkCollision( tileRect ) || cpE1.checkCollision( tileRect ) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpE.getColor() );
            }
            return CollisionType::EAST;
        } else if ( cpW.checkCollision( tileRect ) || cpW1.checkCollision( tileRect ) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpW.getColor() );
            }
            return CollisionType::WEST;
        }

    } catch ( std::bad_cast const& ) {
    } 

    return CollisionType::NONE;

}

CollisionType Mario::checkCollisionBaddie( Sprite &sprite ) {

    try {
        
        Baddie &baddie = dynamic_cast<Baddie&>(sprite);
        Rectangle baddieRect = baddie.getRect();
        
        for ( size_t i = 0; i < fireballs.size(); i++ ) {
            Fireball* f = &fireballs[i];
            switch ( f->checkCollisionBaddie( baddie ) ) {
                case CollisionType::NORTH:
                case CollisionType::SOUTH:
                case CollisionType::EAST:
                case CollisionType::WEST:
                    f->setState( SpriteState::TO_BE_REMOVED );
                    baddie.setState( SpriteState::DYING );
                    PlaySound( ResourceManager::getSounds()["stomp"] );
                    break;
            }
        }

        if ( state == SpriteState::JUMPING || vel.y > 0 ) {
            if ( cpN.checkCollision( baddieRect ) ) {
                return CollisionType::NORTH;
            } else if ( cpS.checkCollision( baddieRect ) ) {
                return CollisionType::SOUTH;
            } else if ( cpE.checkCollision( baddieRect ) || cpE1.checkCollision( baddieRect ) ) {
                return CollisionType::EAST;
            } else if ( cpW.checkCollision( baddieRect ) || cpW1.checkCollision( baddieRect ) ) {
                return CollisionType::WEST;
            }
        }

    } catch ( std::bad_cast const& ) {
    }

    return CollisionType::NONE;

}

CollisionType Mario::checkCollisionBox( Sprite& sprite ) {

    try {

        Box& box = dynamic_cast<Box&>( sprite );
        Rectangle boxRect = box.getRect();

        for ( size_t i = 0; i < fireballs.size(); i++ ) {
            Fireball* f = &fireballs[i];
            switch ( f->checkCollisionTile( box ) ) {
                case CollisionType::NORTH:
                    if ( GameWorld::debug ) {
                        box.setColor( cpN.getColor() );
                    }
                    f->setVelY( -f->getVelY() );
                    break;
                case CollisionType::SOUTH:
                    if ( GameWorld::debug ) {
                        box.setColor( cpS.getColor() );
                    }
                    f->setVelY( -300 );
                    break;
                case CollisionType::EAST:
                    if ( GameWorld::debug ) {
                        box.setColor( cpE.getColor() );
                    }
                    f->setState( SpriteState::TO_BE_REMOVED );
                    break;
                case CollisionType::WEST:
                    if ( GameWorld::debug ) {
                        box.setColor( cpW.getColor() );
                    }
                    f->setState( SpriteState::TO_BE_REMOVED );
                    break;
            }
        }

        if ( cpN.checkCollision( boxRect ) ) {
            if ( GameWorld::debug ) {
                box.setColor( cpN.getColor() );
            }
            return CollisionType::NORTH;
        } else if ( cpS.checkCollision( boxRect ) ) {
            if ( GameWorld::debug ) {
                box.setColor( cpS.getColor() );
            }
            return CollisionType::SOUTH;
        } else if ( cpE.checkCollision( boxRect ) || cpE1.checkCollision( boxRect ) ) {
            if ( GameWorld::debug ) {
                box.setColor( cpE.getColor() );
            }
            return CollisionType::EAST;
        } else if ( cpW.checkCollision( boxRect ) || cpW1.checkCollision( boxRect ) ) {
            if ( GameWorld::debug ) {
                box.setColor( cpW.getColor() );
            }
            return CollisionType::WEST;
        }

    } catch ( std::bad_cast const& ) {
    }

    return CollisionType::NONE;

}

void Mario::drawHud() {

    std::map<std::string, Texture2D>& textures = ResourceManager::getTextures();

    DrawTexture( textures["guiMario" ], 34, 32, WHITE );
    DrawTexture( textures["guiX" ], 54, 49, WHITE );
    drawWhiteSmallNumber( lives < 0 ? 0 : lives, 68, 49, textures );
    
    DrawTexture( textures["guiCoin"], GetScreenWidth() - 115, 32, WHITE );
    DrawTexture( textures["guiX"], GetScreenWidth() - 97, 34, WHITE );
    drawWhiteSmallNumber( coins, GetScreenWidth() - 34 - getSmallNumberWidth( coins ), 34, textures);
    drawWhiteSmallNumber( points, GetScreenWidth() - 34 - getSmallNumberWidth( points ), 50, textures );

    int t = (int) (maxTime - ellapsedTime);
    t = t < 0 ? 0 : t;

    DrawTexture( textures["guiTime"], GetScreenWidth() - 34 - 176, 32, WHITE );
    drawYellowSmallNumber( t, GetScreenWidth() - 34 - 128 - getSmallNumberWidth( t ), 50, textures );

    if ( reservedPowerUp == MarioType::SUPER ) {
        DrawTexture( textures["mushroom"], GetScreenWidth() / 2 - textures["mushroom"].width / 2, 32, WHITE );
    } else if ( reservedPowerUp == MarioType::FLOWER ) {
        DrawTexture( textures["fireFlower0"], GetScreenWidth() / 2 - textures["fireFlower0"].width / 2, 32, WHITE );
    }
    DrawTexture( textures["guiNextItem"], GetScreenWidth() / 2 - textures["guiNextItem"].width / 2, 20, WHITE );

}

float Mario::getSpeedX() {
    return speedX;
}

float Mario::getMaxSpeedX() {
    return maxSpeedX;
}

float Mario::getJumpSpeed() {
    return jumpSpeed;
}

float Mario::getActivationWidth() {
    return activationWidth;
}

float Mario::getPowerUpActivationRadius() {
    return powerUpActivationRadius;
}

void Mario::setImmortal( bool immortal ) {
    this->immortal = immortal;
}

bool Mario::isImmortal() {
    return immortal;
}

void Mario::setActivationWidth( float activationWidth ) {
    this->activationWidth = activationWidth;
}

void Mario::setLives( int lives ) {
    this->lives = lives;
}

void Mario::setCoins( int coins ) {
    this->coins = coins;
}

void Mario::setPoints( int points ) {
    this->points = points;
}

void Mario::setMaxTime( float maxTime ) {
    this->maxTime = maxTime;
}

int Mario::getLives() {
    return lives;
}

int Mario::getCoins() {
    return coins;
}

int Mario::getPoints() {
    return points;
}

void Mario::addLives( int lives ) {
    this->lives += lives;
}

void Mario::removeLives( int lives ) {
    this->lives -= lives;
}

void Mario::addCoins( int coins ) {
    this->coins += coins;
}

void Mario::removeCoins( int coins ) {
    this->coins -= coins;
}

void Mario::addPoints( int points ) {
    this->points += points;
}

void Mario::removePoints( int points ) {
    this->points -= points;
}

void Mario::changeToSmall() {
    type = MarioType::SMALL;
    pos.y = pos.y + 12;
    dim.y = 40;
    maxFrames = 2;
}

void Mario::changeToSuper() {
    type = MarioType::SUPER;
    dim.y = 56;
    maxFrames = 3;
}

void Mario::changeToFlower() {
    type = MarioType::FLOWER;
    dim.y = 56;
    maxFrames = 3;
}

void Mario::setReservedPowerUp( MarioType reservedPowerUp ) {
    this->reservedPowerUp = reservedPowerUp;
}

MarioType Mario::getReservedPowerUp() {
    return reservedPowerUp;
}

void Mario::consumeReservedPowerUp() {
    if ( reservedPowerUp == MarioType::SUPER ) {
        changeToSuper();
    } else if ( reservedPowerUp == MarioType::FLOWER ) {
        changeToFlower();
    }
    reservedPowerUp = MarioType::SMALL;
}

MarioType Mario::getType() {
    return type;
}

void Mario::setInvulnerable( bool invulnerable ) {
    this->invulnerable = invulnerable;
}

bool Mario::isInvulnerable() {
    return invulnerable;
}

void Mario::updateCollisionProbes() {

    cpN.setX( pos.x + dim.x / 2 - cpN.getWidth() / 2 );
    if ( ducking ) {
        cpN.setY( pos.y + dim.y - 32 );
    } else {
        cpN.setY( pos.y );
    }

    cpS.setX( pos.x + dim.x / 2 - cpS.getWidth() / 2 );
    cpS.setY( pos.y + dim.y - cpS.getHeight() );

    cpE.setX( pos.x + dim.x - cpE.getWidth() );
    cpE1.setX( pos.x + dim.x - cpE1.getWidth() );
    cpW.setX( pos.x );
    cpW1.setX( pos.x );

    if ( type == MarioType::SMALL ) {

        if ( ducking ) {
            cpE.setY( pos.y + 21 - cpE.getHeight() / 2 );
            cpE1.setY( pos.y + 30 - cpE1.getHeight() / 2 );
            cpW.setY( pos.y + 21 - cpW.getHeight() / 2 );
            cpW1.setY( pos.y + 30 - cpW1.getHeight() / 2 );
        } else {
            cpE.setY( pos.y + dim.y * 0.33 - cpE.getHeight() / 2 );
            cpE1.setY( pos.y + dim.y * 0.66 - cpE1.getHeight() / 2 );
            cpW.setY( pos.y + dim.y * 0.33 - cpW.getHeight() / 2 );
            cpW1.setY( pos.y + dim.y * 0.66 - cpW1.getHeight() / 2 );
        }

    } else {

        if ( ducking ) {
            cpE.setY( pos.y + 36 - cpE.getHeight() / 2 );
            cpE1.setY( pos.y + 46 - cpE1.getHeight() / 2 );
            cpW.setY( pos.y + 36 - cpW.getHeight() / 2 );
            cpW1.setY( pos.y + 46 - cpW1.getHeight() / 2 );
        } else {
            cpE.setY( pos.y + dim.y * 0.33 - cpE.getHeight() / 2 );
            cpE1.setY( pos.y + dim.y * 0.66 - cpE1.getHeight() / 2 );
            cpW.setY( pos.y + dim.y * 0.33 - cpW.getHeight() / 2 );
            cpW1.setY( pos.y + dim.y * 0.66 - cpW1.getHeight() / 2 );
        }

    }

}

void Mario::reset( bool removePowerUps ) {

    if ( removePowerUps ) {
        changeToSmall();
        reservedPowerUp = MarioType::SMALL;
    }
    vel.x = 0;
    vel.y = 0;
    state = SpriteState::ON_GROUND;
    facingDirection = Direction::RIGHT;
    ducking = false;
    lookigUp = false;
    running = false;
    ellapsedTime = 0;
    invulnerable = false;
    invulnerableTimeAcum = 0;
    invulnerableBlink = false;

}

void Mario::resetAll() {
    lives = 5;
    coins = 0;
    points = 0;
    reset( true );
}