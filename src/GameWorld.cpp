/**
 * @file GameWorld.cpp
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Baddie.h"
#include "Block.h"
#include "GameState.h"
#include "GameWorld.h"
#include "Item.h"
#include "Mario.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "SpriteState.h"
#include "Tile.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <vector>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION

//#define RELEASE

#ifdef RELEASE
#define ACTIVATE_DEBUG false
#define ALLOW_ENABLE_CONTROLS false
#define INITIAL_MAP_ID 1
#define LOAD_TEST_MAP false
#define LOAD_RESOURCES_FROM_RRES true
#define PARSE_BLOCKS true
#define PARSE_ITEMS true
#define PARSE_BADDIES true
GameState GameWorld::state = GAME_STATE_TITLE_SCREEN;
#else
#define ACTIVATE_DEBUG true
#define ALLOW_ENABLE_CONTROLS true
#define INITIAL_MAP_ID 1
#define LOAD_TEST_MAP true
#define LOAD_RESOURCES_FROM_RRES false
#define PARSE_BLOCKS true
#define PARSE_ITEMS true
#define PARSE_BADDIES true
GameState GameWorld::state = GAME_STATE_PLAYING;
#endif

bool GameWorld::debug = ACTIVATE_DEBUG;
bool GameWorld::showFPS = ACTIVATE_DEBUG;
bool GameWorld::immortalMario = ACTIVATE_DEBUG;
bool ResourceManager::loadFromRRES = LOAD_RESOURCES_FROM_RRES;
float GameWorld::gravity = 20;

/**
 * @brief Construct a new GameWorld object
 */
GameWorld::GameWorld() :
    mario( 
        Vector2( 0, 0 ), 
        Vector2( 32, 40 ), 
        Vector2( 0, 0 ), 
        Color( 0, 0, 0, 255 ),
        260,
        360,
        -600,
        ACTIVATE_DEBUG
    ),
    map( mario, INITIAL_MAP_ID, LOAD_TEST_MAP, PARSE_BLOCKS, PARSE_ITEMS, PARSE_BADDIES, this ),
    camera( nullptr ),
    showControls( ACTIVATE_DEBUG ),
    stateBeforePause( GAME_STATE_TITLE_SCREEN ),
    remainingTimePointCount( 0 ),
    pauseMusic( false ),
    pauseMarioUpdate( false ),
    showOverlayOnPause( true ),
    irisOutFinished( false ),
    irisOutTime( 1 ),
    irisOutAcum( 0 ) {

    mario.setGameWorld( this );
    mario.setMap( &map );
    //mario.changeToSuper();
    //mario.changeToFlower();

}

/**
 * @brief Destroy the GameWorld object
 */
GameWorld::~GameWorld() = default;

/**
 * @brief Reads user input and updates the state of the game.
 */
void GameWorld::inputAndUpdate() {

    map.parseMap();

    const std::vector<Tile*> &tiles = map.getTiles();
    const std::vector<Block*> &blocks = map.getBlocks();
    std::vector<Item*> &items = map.getItems();
    std::vector<Item*> &staticItems = map.getStaticItems();
    std::vector<Baddie*> &baddies = map.getBaddies();

    std::map<std::string, Sound> &sounds = ResourceManager::getSounds();
    std::map<std::string, Music> &musics = ResourceManager::getMusics();

    if ( IsKeyPressed( KEY_LEFT_ALT ) && ALLOW_ENABLE_CONTROLS ) {
        showControls = !showControls;
    }

    if ( mario.getState() != SPRITE_STATE_DYING && 
         mario.getState() != SPRITE_STATE_VICTORY &&
         mario.getState() != SPRITE_STATE_WAITING_TO_NEXT_MAP &&
         state != GAME_STATE_TITLE_SCREEN &&
         state != GAME_STATE_FINISHED && 
         !pauseMusic ) {
        map.playMusic();
    }

    if ( state != GAME_STATE_TITLE_SCREEN &&
         state != GAME_STATE_FINISHED &&
         state != GAME_STATE_PAUSED ) {
        mario.setActivationWidth( GetScreenWidth() * 2 );
        mario.update();
    } else if ( !pauseMarioUpdate && state != GAME_STATE_TITLE_SCREEN ) {
        mario.update();
    }

    if ( mario.getState() != SPRITE_STATE_DYING && 
         mario.getState() != SPRITE_STATE_VICTORY &&
         mario.getState() != SPRITE_STATE_WAITING_TO_NEXT_MAP &&
         state != GAME_STATE_TITLE_SCREEN &&
         state != GAME_STATE_FINISHED &&
         state != GAME_STATE_PAUSED ) {

        std::vector<int> collectedIndexes;

        if ( IsKeyPressed( KEY_ENTER ) || IsGamepadButtonPressed( 0, GAMEPAD_BUTTON_MIDDLE_RIGHT ) ) {
            pauseGame( true, true, true, true );
        }

        for ( const auto block : blocks ) {
            block->update();
        }

        for ( const auto& item : items ) {
            item->update();
        }
        
        for ( const auto& staticItem : staticItems ) {
            staticItem->update();
        }

        for ( const auto& baddie : baddies ) {
            baddie->update();
            baddie->followTheLeader( &mario );
        }

        // tiles collision resolution
        mario.updateCollisionProbes();
        for ( const auto tile : tiles ) {

            // mario x tiles
            CollisionType col = mario.checkCollision( tile );

            if ( tile->getType() == TILE_TYPE_SOLID ) {
                switch ( col ) {
                    case COLLISION_TYPE_NORTH:
                        mario.setY( tile->getY() + tile->getHeight() );
                        mario.setVelY( 0 );
                        mario.updateCollisionProbes();
                        break;
                    case COLLISION_TYPE_SOUTH:
                        mario.setY( tile->getY() - mario.getHeight() );
                        mario.setVelY( 0 );
                        mario.setState( SPRITE_STATE_ON_GROUND );
                        mario.updateCollisionProbes();
                        break;
                    case COLLISION_TYPE_EAST:
                        mario.setX( tile->getX() - mario.getWidth() );
                        mario.setVelX( 0 );
                        mario.updateCollisionProbes();
                        break;
                    case COLLISION_TYPE_WEST:
                        mario.setX( tile->getX() + tile->getWidth() );
                        mario.setVelX( 0 );
                        mario.updateCollisionProbes();
                        break;
                    default:
                        break;
                }
            } else if ( tile->getType() == TILE_TYPE_SOLID_FROM_ABOVE ) {
                if ( col == COLLISION_TYPE_SOUTH && mario.getState() == SPRITE_STATE_FALLING ) {
                    mario.setY( tile->getY() - mario.getHeight() );
                    mario.setVelY( 0 );
                    mario.setState( SPRITE_STATE_ON_GROUND );
                    mario.updateCollisionProbes();
                }
            }/* else if ( tile->getType() == TILE_TYPE_SLOPE_UP || tile->getType() == TILE_TYPE_SLOPE_DOWN ) {

                if ( mario.getState() == SPRITE_STATE_FALLING ) {

                    const float width = tile->getWidth();
                    const float height = tile->getHeight();
                    const float xStart = tile->getX();
                    const float xEnd = xStart + width;
                    const float yStart = tile->getY();
                    const float yEnd = yStart + height;

                    Vector2 pos = mario.getSouthCollisionProbePos();

                    if ( pos.x >= xStart &&
                         pos.x <= xEnd &&
                         pos.y >= yStart &&
                         pos.y <= yEnd ) {

                        const float adjPosX = pos.x - xStart;
                        const float adjPosY = pos.y - yStart;
                        const float ratio = height / width;
                        float projectionY = 0;

                        if ( tile->getType() == TILE_TYPE_SLOPE_UP ) {
                            projectionY = height - adjPosX * ratio;
                        } else if ( tile->getType() == TILE_TYPE_SLOPE_DOWN ) {
                            projectionY = adjPosX * ratio;
                        }

                        if ( adjPosY <= projectionY - 10 ) {
                            
                        } else {
                            mario.setY( static_cast<int>(projectionY + tile->getY() - mario.getHeight() - 5 ) );
                            mario.setVelY( 0 );
                            mario.setState( SPRITE_STATE_ON_GROUND );
                            mario.updateCollisionProbes();
                        }

                    }

                }
            }*/

            // baddies x tiles
            for ( const auto baddie : baddies ) {
                
                baddie->updateCollisionProbes();

                if ( baddie->getState() != SPRITE_STATE_DYING && 
                     baddie->getState() != SPRITE_STATE_TO_BE_REMOVED &&
                     ( tile->getType() == TILE_TYPE_SOLID || 
                       tile->getType() == TILE_TYPE_SOLID_ONLY_FOR_BADDIES ||
                       tile->getType() == TILE_TYPE_SOLID_FROM_ABOVE ) ) {
                    switch ( baddie->checkCollision( tile ) ) {
                        case COLLISION_TYPE_NORTH:
                            baddie->setY( tile->getY() + tile->getHeight() );
                            baddie->setVelY( 0 );
                            baddie->updateCollisionProbes();
                            break;
                        case COLLISION_TYPE_SOUTH:
                            baddie->setY( tile->getY() - baddie->getHeight() );
                            baddie->setVelY( 0 );
                            baddie->onSouthCollision();
                            baddie->updateCollisionProbes();
                            break;
                        case COLLISION_TYPE_EAST:
                            baddie->setX( tile->getX() - baddie->getWidth() );
                            baddie->setVelX( -baddie->getVelX() );
                            baddie->updateCollisionProbes();
                            break;
                        case COLLISION_TYPE_WEST:
                            baddie->setX( tile->getX() + tile->getWidth() );
                            baddie->setVelX( -baddie->getVelX() );
                            baddie->updateCollisionProbes();
                            break;
                        default:
                            break;
                    }
                }

            }

            // items x tiles
            for ( const auto item : items ) {

                if ( tile->getType() == TILE_TYPE_SOLID || tile->getType() == TILE_TYPE_SOLID_FROM_ABOVE ) {

                    item->updateCollisionProbes();

                    switch ( item->checkCollision( tile ) ) {
                        case COLLISION_TYPE_NORTH:
                            item->setY( tile->getY() + tile->getHeight() );
                            item->setVelY( 0 );
                            item->updateCollisionProbes();
                            break;
                        case COLLISION_TYPE_SOUTH:
                            item->setY( tile->getY() - item->getHeight() );
                            item->setVelY( 0 );
                            item->onSouthCollision( mario );
                            item->updateCollisionProbes();
                            break;
                        case COLLISION_TYPE_EAST:
                            item->setX( tile->getX() - item->getWidth() );
                            item->setVelX( -item->getVelX() );
                            item->updateCollisionProbes();
                            break;
                        case COLLISION_TYPE_WEST:
                            item->setX( tile->getX() + tile->getWidth() );
                            item->setVelX( -item->getVelX() );
                            item->updateCollisionProbes();
                            break;
                        default:
                            break;
                    }

                }

            }

        }

        // blocks collision resolution
        mario.updateCollisionProbes();

        for ( const auto block : blocks ) {

            // mario x blocks
            switch ( mario.checkCollision( block ) ) {
                case COLLISION_TYPE_NORTH:
                    mario.setY( block->getY() + block->getHeight() );
                    mario.setVelY( 0 );
                    mario.updateCollisionProbes();
                    block->doHit( mario, &map );
                    break;
                case COLLISION_TYPE_SOUTH:
                    mario.setY( block->getY() - mario.getHeight() );
                    mario.setVelY( 0 );
                    mario.setState( SPRITE_STATE_ON_GROUND );
                    mario.updateCollisionProbes();
                    break;
                case COLLISION_TYPE_EAST:
                    mario.setX( block->getX() - mario.getWidth() );
                    mario.setVelX( 0 );
                    mario.updateCollisionProbes();
                    break;
                case COLLISION_TYPE_WEST:
                    mario.setX( block->getX() + block->getWidth() );
                    mario.setVelX( 0 );
                    mario.updateCollisionProbes();
                    break;
                default:
                    break;
            }

            // baddies x blocks
            for ( const auto baddie : baddies ) {

                baddie->updateCollisionProbes();

                if ( baddie->getState() != SPRITE_STATE_DYING && 
                     baddie->getState() != SPRITE_STATE_TO_BE_REMOVED ) {
                    switch ( baddie->checkCollision( block ) ) {
                        case COLLISION_TYPE_NORTH:
                            baddie->setY( block->getY() + block->getHeight() );
                            baddie->setVelY( 0 );
                            baddie->updateCollisionProbes();
                            break;
                        case COLLISION_TYPE_SOUTH:
                            baddie->setY( block->getY() - baddie->getHeight() );
                            baddie->setVelY( 0 );
                            baddie->onSouthCollision();
                            baddie->updateCollisionProbes();
                            break;
                        case COLLISION_TYPE_EAST:
                            baddie->setX( block->getX() - baddie->getWidth() );
                            baddie->setVelX( -baddie->getVelX() );
                            baddie->updateCollisionProbes();
                            break;
                        case COLLISION_TYPE_WEST:
                            baddie->setX( block->getX() + block->getWidth() );
                            baddie->setVelX( -baddie->getVelX() );
                            baddie->updateCollisionProbes();
                            break;
                        default:
                            break;
                    }
                }

            }

            // items x blocks
            for ( const auto item : items ) {

                item->updateCollisionProbes();

                switch ( item->checkCollision( block ) ) {
                    case COLLISION_TYPE_NORTH:
                        item->setY( block->getY() + block->getHeight() );
                        item->setVelY( 0 );
                        item->updateCollisionProbes();
                        break;
                    case COLLISION_TYPE_SOUTH:
                        item->setY( block->getY() - item->getHeight() );
                        item->setVelY( 0 );
                        item->onSouthCollision( mario );
                        item->updateCollisionProbes();
                        break;
                    case COLLISION_TYPE_EAST:
                        item->setX( block->getX() - item->getWidth() );
                        item->setVelX( -item->getVelX() );
                        item->updateCollisionProbes();
                        break;
                    case COLLISION_TYPE_WEST:
                        item->setX( block->getX() + block->getWidth() );
                        item->setVelX( -item->getVelX() );
                        item->updateCollisionProbes();
                        break;
                    default:
                        break;
                }

            }

        }

        // mario x items collision resolution and offscreen items removal
        for ( size_t i = 0; i < items.size(); i++ ) {

            Item* item = items[i];

            if ( item->getState() != SPRITE_STATE_HIT &&
                 item->getState() != SPRITE_STATE_TO_BE_REMOVED ) {
                if ( item->checkCollision( &mario ) != COLLISION_TYPE_NONE ) {
                    if ( !mario.isTransitioning() ) {
                        item->setState( SPRITE_STATE_HIT );
                        item->playCollisionSound();
                        if ( item->isPauseGameOnHit() ) {
                            pauseGame( false, false, false, false );
                        }
                        item->updateMario( mario );
                    }
                } else if ( item->getY() > map.getMaxHeight() ) {
                    item->setState( SPRITE_STATE_TO_BE_REMOVED );
                }
            }

            if ( item->getState() == SPRITE_STATE_TO_BE_REMOVED ) {
                collectedIndexes.push_back( static_cast<int>( i ) );
            }

        }

        for ( int i = collectedIndexes.size() - 1; i >= 0; i-- ) {
            delete items[collectedIndexes[i]];
            items.erase( items.begin() + collectedIndexes[i] );
        }
        
        // mario x static items collision resolution
        collectedIndexes.clear();
        for ( size_t i = 0; i < staticItems.size(); i++ ) {

            Item* item = staticItems[i];

            if ( item->getState() != SPRITE_STATE_HIT &&
                 item->getState() != SPRITE_STATE_TO_BE_REMOVED ) {
                if ( item->checkCollision( &mario ) != COLLISION_TYPE_NONE ) {
                    item->setState( SPRITE_STATE_HIT );
                    item->playCollisionSound();
                    item->updateMario( mario );
                } else if ( item->getY() > map.getMaxHeight() ) {
                    item->setState( SPRITE_STATE_TO_BE_REMOVED );
                }
            }

            if ( item->getState() == SPRITE_STATE_TO_BE_REMOVED ) {
                collectedIndexes.push_back( static_cast<int>( i ) );
            }

        }

        for ( int i = collectedIndexes.size() - 1; i >= 0; i-- ) {
            delete staticItems[collectedIndexes[i]];
            staticItems.erase( staticItems.begin() + collectedIndexes[i] );
        }

        // baddies activation and mario and fireballs x baddies collision resolution and offscreen baddies removal
        collectedIndexes.clear();
        if ( mario.getState() != SPRITE_STATE_DYING && 
             mario.getState() != SPRITE_STATE_VICTORY &&
             mario.getState() != SPRITE_STATE_WAITING_TO_NEXT_MAP ) {

            mario.updateCollisionProbes();

            for ( size_t i = 0; i < baddies.size(); i++ ) {

                Baddie* baddie = baddies[i];

                // baddies activation
                if ( baddie->getState() == SPRITE_STATE_IDLE ) {
                    baddie->activateWithMarioProximity( mario );
                }

                if ( baddie->getState() != SPRITE_STATE_DYING && 
                     baddie->getState() != SPRITE_STATE_TO_BE_REMOVED ) {

                    const CollisionType col = mario.checkCollisionBaddie( baddie );

                    if ( mario.isInvincible() && col ) {
                        baddie->onHit();
                        PlaySound( sounds["stomp"] );
                        mario.addPoints( baddie->getEarnedPoints() );
                    } else {

                        if ( baddie->getAuxiliaryState() != SPRITE_STATE_INVULNERABLE ) {

                            // mario and fireballs x baddies collision resolution and offscreen baddies removal
                            switch ( col ) {
                                case COLLISION_TYPE_NORTH:
                                case COLLISION_TYPE_EAST:
                                case COLLISION_TYPE_WEST:
                                    if ( !mario.isImmortal() && !mario.isInvulnerable() ) {
                                        switch ( mario.getType() ) {
                                            case MARIO_TYPE_SMALL:
                                                mario.setState( SPRITE_STATE_DYING );
                                                mario.playPlayerDownMusicStream();
                                                mario.removeLives( 1 );
                                                break;
                                            case MARIO_TYPE_SUPER:
                                                PlaySound( sounds["pipe"] );
                                                mario.setLastStateBeforeTransition( mario.getState() );
                                                mario.setState( SPRITE_STATE_TRANSITIONING_SUPER_TO_SMALL );
                                                mario.setInvulnerable( true );
                                                break;
                                            case MARIO_TYPE_FLOWER:
                                                PlaySound( sounds["pipe"] );
                                                mario.setLastStateBeforeTransition( mario.getState() );
                                                mario.setState( SPRITE_STATE_TRANSITIONING_FLOWER_TO_SMALL );
                                                mario.setInvulnerable( true );
                                                break;
                                        }
                                    }
                                    break;
                                case COLLISION_TYPE_SOUTH:
                                    if ( mario.getState() == SPRITE_STATE_FALLING && 
                                         baddie->getState() != SPRITE_STATE_DYING && 
                                         baddie->getState() != SPRITE_STATE_TO_BE_REMOVED ) {
                                        mario.setY( baddie->getY() - mario.getHeight() );
                                        if ( ( IsKeyDown( KEY_LEFT_CONTROL ) ||
                                               IsGamepadButtonDown( 0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT ) ) ) {
                                            mario.setVelY( -400 );
                                        } else {
                                            mario.setVelY( -200 );
                                        }
                                        mario.setState( SPRITE_STATE_JUMPING );
                                        baddie->onHit();
                                        PlaySound( sounds["stomp"] );
                                        mario.addPoints( baddie->getEarnedPoints() );
                                    } else {
                                        if ( !mario.isImmortal() && !mario.isInvulnerable() ) {
                                            switch ( mario.getType() ) {
                                                case MARIO_TYPE_SMALL:
                                                    mario.setState( SPRITE_STATE_DYING );
                                                    mario.playPlayerDownMusicStream();
                                                    mario.removeLives( 1 );
                                                    break;
                                                case MARIO_TYPE_SUPER:
                                                    PlaySound( sounds["pipe"] );
                                                    mario.setLastStateBeforeTransition( mario.getState() );
                                                    mario.setState( SPRITE_STATE_TRANSITIONING_SUPER_TO_SMALL );
                                                    mario.setInvulnerable( true );
                                                    break;
                                                case MARIO_TYPE_FLOWER:
                                                    PlaySound( sounds["pipe"] );
                                                    mario.setLastStateBeforeTransition( mario.getState() );
                                                    mario.setState( SPRITE_STATE_TRANSITIONING_FLOWER_TO_SMALL );
                                                    mario.setInvulnerable( true );
                                                    break;
                                            }
                                        }
                                    }
                                    break;
                                case COLLISION_TYPE_FIREBALL:
                                    baddie->onHit();
                                    PlaySound( sounds["stomp"] );
                                    mario.addPoints( baddie->getEarnedPoints() );
                                    break;
                                default:
                                    break;

                            }

                        } else {

                            if ( col ) {
                                if ( col == COLLISION_TYPE_FIREBALL ) {
                                    baddie->onHit();
                                    PlaySound( sounds["stomp"] );
                                    mario.addPoints( baddie->getEarnedPoints() );
                                } else {
                                    if ( !mario.isImmortal() && !mario.isInvulnerable() ) {
                                        switch ( mario.getType() ) {
                                            case MARIO_TYPE_SMALL:
                                                mario.setState( SPRITE_STATE_DYING );
                                                mario.playPlayerDownMusicStream();
                                                mario.removeLives( 1 );
                                                break;
                                            case MARIO_TYPE_SUPER:
                                                PlaySound( sounds["pipe"] );
                                                mario.setLastStateBeforeTransition( mario.getState() );
                                                mario.setState( SPRITE_STATE_TRANSITIONING_SUPER_TO_SMALL );
                                                mario.setInvulnerable( true );
                                                break;
                                            case MARIO_TYPE_FLOWER:
                                                PlaySound( sounds["pipe"] );
                                                mario.setLastStateBeforeTransition( mario.getState() );
                                                mario.setState( SPRITE_STATE_TRANSITIONING_FLOWER_TO_SMALL );
                                                mario.setInvulnerable( true );
                                                break;
                                        }
                                    }
                                }
                            }

                        }

                    }

                    if ( baddie->getX() + baddie->getWidth() < 0 ||
                         baddie->getX() > map.getMaxWidth() ||
                         baddie->getY() > map.getMaxHeight() ) {
                        baddie->setState( SPRITE_STATE_TO_BE_REMOVED );
                    }

                } else {
                    if ( baddie->getX() + baddie->getWidth() < 0 ||
                         baddie->getX() > map.getMaxWidth() ||
                         baddie->getY() > map.getMaxHeight() ) {
                        baddie->setState( SPRITE_STATE_TO_BE_REMOVED );
                    }
                }

                if ( baddie->getState() == SPRITE_STATE_TO_BE_REMOVED ) {
                    collectedIndexes.push_back( static_cast<int>( i ) );
                }

                mario.updateCollisionProbes();

            }

        }

        for ( int i = collectedIndexes.size() - 1; i >= 0; i-- ) {

            Baddie *baddie = baddies[collectedIndexes[i]];
            delete baddie;
            baddies.erase( baddies.begin() + collectedIndexes[i] );

            // the map draws baddies in two layers
            // the baddies are stored in three vectors:
            //     one for baddies management (all baddies)
            //     one for drawing in front of the scenario
            //     one for drawing in back of the scenario
            map.eraseBaddieFromDrawingVectors( baddie );

        }

    } else if ( mario.getState() == SPRITE_STATE_DYING ) {

        if ( !mario.isPlayerDownMusicStreamPlaying() && !mario.isGameOverMusicStreamPlaying() ) {
            
            if ( mario.getLives() > 0 ) {
                resetMap();
            } else if ( mario.getLives() < 0 ) {
                resetGame();
            } else {
                mario.playGameOverMusicStream();
                state = GAME_STATE_GAME_OVER;
                mario.setLives( -1 );
            }

        }

    } else if ( state == GAME_STATE_COUNTING_POINTS ) {

        if ( !IsMusicStreamPlaying( musics["courseClear"] ) ) {
            PlayMusicStream( ResourceManager::getMusics()["courseClear"] );
        } else {
            UpdateMusicStream( musics["courseClear"] );
        }

        remainingTimePointCount--;
        mario.addPoints( 50 );

        if ( remainingTimePointCount % 3 == 0 ) {
            PlaySound( sounds["coin"] );
        }

        if ( remainingTimePointCount == 0 ) {
            state = GAME_STATE_IRIS_OUT;
        }

    } else if ( state == GAME_STATE_IRIS_OUT ) {

        if ( !IsMusicStreamPlaying( musics["courseClear"] ) ) {
            StopMusicStream( musics["courseClear"] );
            PlaySound( sounds["goalIrisOut"] );
            state = GAME_STATE_GO_TO_NEXT_MAP;
            irisOutAcum = 0;
        } else {
            UpdateMusicStream( musics["courseClear"] );
            if ( static_cast<int>(GetMusicTimeLength( musics["courseClear"] )) == static_cast<int>(GetMusicTimePlayed( musics["courseClear"] )) ) {
                StopMusicStream( musics["courseClear"] );
            }
        }

    } else if ( state == GAME_STATE_GO_TO_NEXT_MAP ) {

        irisOutAcum += GetFrameTime();
        if ( irisOutAcum >= irisOutTime ) {
            irisOutFinished = true;
        }

        if ( irisOutFinished ) {
            irisOutAcum = 0;
            irisOutFinished = false;
            nextMap();
        }

    } else if ( mario.getState() == SPRITE_STATE_VICTORY ) {

        remainingTimePointCount = mario.getRemainingTime();
        state = GAME_STATE_COUNTING_POINTS;
        map.setDrawBlackScreen( true );
        mario.setState( SPRITE_STATE_WAITING_TO_NEXT_MAP );

    } else if ( state == GAME_STATE_PAUSED ) {
        if ( IsKeyPressed( KEY_ENTER ) || IsGamepadButtonPressed( 0, GAMEPAD_BUTTON_MIDDLE_RIGHT ) ) {
            unpauseGame();
        }
    }

    if ( mario.getState() != SPRITE_STATE_DYING && mario.getY() > map.getMaxHeight() ) {
        mario.setState( SPRITE_STATE_DYING );
        mario.playPlayerDownMusicStream();
        mario.removeLives( 1 );
    }

    if ( IsGamepadButtonPressed( 0, GAMEPAD_BUTTON_RIGHT_TRIGGER_1 ) ) {
        if ( showControls ) {
            debug = !debug;
        }
    }

    const float xc = GetScreenWidth() / 2.0;
    const float yc = GetScreenHeight() / 2.0;
    const float pxc = mario.getX() + mario.getWidth() / 2.0;
    const float pyc = mario.getY() + mario.getHeight() / 2.0;
    
    camera->offset.x = xc;

    if ( pxc < xc ) {
        camera->target.x = xc + Map::TILE_WIDTH;
        map.setMarioOffset( 0 );         // x parallax
    } else if ( pxc >= map.getMaxWidth() - xc - Map::TILE_WIDTH ) {
        camera->target.x = map.getMaxWidth() - GetScreenWidth();
        camera->offset.x = 0;
    } else {
        camera->target.x = pxc + Map::TILE_WIDTH;
        map.setMarioOffset( pxc - xc );  // x parallax
    }

    camera->offset.y = yc;

    if ( pyc < yc ) {
        camera->target.y = yc + Map::TILE_WIDTH;
    } else if ( pyc >= map.getMaxHeight() - yc - Map::TILE_WIDTH ) {
        camera->target.y = map.getMaxHeight() - GetScreenHeight();
        camera->offset.y = 0;
    } else {
        camera->target.y = pyc + Map::TILE_WIDTH;
    }

    if ( state == GAME_STATE_TITLE_SCREEN ) {

        if ( !IsMusicStreamPlaying( musics["title"] ) ) {
            PlayMusicStream( musics["title"] );
        } else {
            UpdateMusicStream( musics["title"] );
        }

        if ( GetKeyPressed() && !IsKeyPressed( KEY_LEFT_ALT ) ) {
            StopMusicStream( musics["title"] );
            state = GAME_STATE_PLAYING;
        }

    }

    if ( state == GAME_STATE_GAME_OVER ) {
        mario.playGameOverMusicStream();
    }

}

/**
 * @brief Draws the state of the game.
 */
void GameWorld::draw() {

    BeginDrawing();
    ClearBackground( WHITE );
    std::map<std::string, Texture2D>& textures = ResourceManager::getTextures();

    if ( state != GAME_STATE_GAME_OVER && state != GAME_STATE_TITLE_SCREEN ) {

        BeginMode2D( *camera );
        map.draw();
        EndMode2D();

        mario.drawHud();

        if ( state == GAME_STATE_TIME_UP ) {

            DrawRectangle( 0, 0, GetScreenWidth(), GetScreenHeight(), BLACK );
            Texture2D* t = &textures["guiTimeUp"];
            DrawTexture( *t, GetScreenWidth() / 2 - t->width / 2, GetScreenHeight() / 2 - t->height / 2, WHITE );

        } else if ( state == GAME_STATE_COUNTING_POINTS || state == GAME_STATE_IRIS_OUT || state == GAME_STATE_GO_TO_NEXT_MAP ) {

            Vector2 sc( GetScreenWidth() / 2, GetScreenHeight() / 2 );
            DrawTexture( textures["guiMario"], sc.x - textures["guiMario"].width / 2, sc.y - 120, WHITE);

            std::string message1 = "course clear!";
            drawString( message1, sc.x - getDrawStringWidth( message1 ) / 2, sc.y - 80 );

            int clockWidth = textures["guiClock"].width;
            int remainingTimeWidth = getSmallNumberWidth( mario.getRemainingTime() );
            int pointsPerSecondWidth = getSmallNumberWidth( 50 );
            int timesWidth = textures["guiX"].width;
            int equalSignWidth = getDrawStringWidth( "=" );
            int totalTimePoints = mario.getRemainingTime() * 50;
            int totalTimePointsWidth = getSmallNumberWidth( totalTimePoints );
            int completeMessageWidth = clockWidth + remainingTimeWidth + pointsPerSecondWidth + timesWidth + equalSignWidth + totalTimePointsWidth;
            int completeMessageStart = sc.x - (completeMessageWidth/2);
            int completeMessageY = sc.y - 40;

            DrawTexture( textures["guiClock"], completeMessageStart, completeMessageY, WHITE );
            drawWhiteSmallNumber( mario.getRemainingTime(), completeMessageStart + clockWidth, completeMessageY );
            DrawTexture( textures["guiX"], completeMessageStart + clockWidth + remainingTimeWidth, completeMessageY, WHITE );
            drawWhiteSmallNumber( 50, completeMessageStart + clockWidth + remainingTimeWidth + timesWidth, completeMessageY );
            drawString( "=", completeMessageStart + clockWidth + remainingTimeWidth + timesWidth + pointsPerSecondWidth, completeMessageY - 4 );
            drawWhiteSmallNumber( totalTimePoints, completeMessageStart + clockWidth + remainingTimeWidth + timesWidth + pointsPerSecondWidth + equalSignWidth, completeMessageY );

            Vector2 centerFunnel = GetWorldToScreen2D( mario.getCenter(), *camera );
            DrawRing( centerFunnel, 
                      sqrt( GetScreenWidth() * GetScreenWidth() + GetScreenHeight() * GetScreenHeight() ) * ( 1 - irisOutAcum / irisOutTime ),
                      GetScreenWidth() * 2, 
                      0, 360, 100, BLACK );

        } else if ( state == GAME_STATE_FINISHED ) {

            if ( !IsMusicStreamPlaying( ResourceManager::getMusics()["ending"] ) ) {
                PlayMusicStream( ResourceManager::getMusics()["ending"] );
            } else {
                UpdateMusicStream( ResourceManager::getMusics()["ending"] );
            }

            if ( GetKeyPressed() ) {
                StopMusicStream( ResourceManager::getMusics()["ending"] );
                resetGame();
            }

            DrawRectangle( 0, 0, GetScreenWidth(), GetScreenHeight(), Fade( RAYWHITE, 0.9 ) );
            Texture2D* t = &textures["guiCredits"];
            DrawTexture( *t, GetScreenWidth() / 2 - t->width / 2, 20, WHITE );

            std::string message1 = "Thank you for playing!!!";
            std::string message2 = "Press any key to restart!";

            drawString( message1, GetScreenWidth() / 2 - getDrawStringWidth( message1 ) / 2, t->height + 40 );
            drawString( message2, GetScreenWidth() / 2 - getDrawStringWidth( message2 ) / 2, t->height + 65 );

        } else if ( state == GAME_STATE_PAUSED ) {
            if ( showOverlayOnPause ) {
                DrawRectangle( 0, 0, GetScreenWidth(), GetScreenHeight(), Fade( BLACK, 0.3 ) );
            }
        }

    } else if ( state == GAME_STATE_TITLE_SCREEN ) {

        DrawRectangle( 0, 0, GetScreenWidth(), GetScreenHeight(), RAYWHITE );
        Texture2D* t = &textures["guiRayMarioLogo"];
        DrawTexture( *t, GetScreenWidth() / 2 - t->width / 2, GetScreenHeight() / 2 - t->height, WHITE );

        std::string message1 = "Press any key to start!";
        std::string message2 = "Developed by:";
        std::string message3 = "Prof. Dr. David Buzatto - IFSP";
        std::string message4 = "2024";
        drawString( message1, GetScreenWidth() / 2 - getDrawStringWidth( message1 ) / 2, GetScreenHeight() / 2 + getDrawStringHeight() + 30 );
        drawString( message2, GetScreenWidth() / 2 - getDrawStringWidth( message2 ) / 2, GetScreenHeight() / 2 + getDrawStringHeight() * 5 + 30 );
        drawString( message3, GetScreenWidth() / 2 - getDrawStringWidth( message3 ) / 2, GetScreenHeight() / 2 + getDrawStringHeight() * 6 + 35 );
        drawWhiteSmallNumber( 2024, GetScreenWidth() / 2 - getSmallNumberWidth( 2024 ) / 2, GetScreenHeight() / 2 + getDrawStringHeight() * 7 + 40 );
        
        Rectangle r( 40, 40, 70, 70 );
        DrawRectangle( r.x, r.y, r.width, r.height, Fade( RAYWHITE, 0.5 ) );
        DrawRectangleLinesEx( r, 5, BLACK );
        DrawText( "ray", r.x + r.width - 50, r.y + r.height - 35, 20, BLACK );

    } else if ( state == GAME_STATE_GAME_OVER ) {

        DrawRectangle( 0, 0, GetScreenWidth(), GetScreenHeight(), BLACK );
        Texture2D* t = &textures["guiGameOver"];
        DrawTexture( *t, GetScreenWidth() / 2 - t->width / 2, GetScreenHeight() / 2 - t->height / 2, WHITE );

    }

    if ( showControls ) {

        int compMargin = 10;
        Rectangle guiPanelRect( GetScreenWidth() - 120, GetScreenHeight() - 140, 100, 120 );
        GuiPanel( guiPanelRect, "Controls" );
        GuiCheckBox( Rectangle( guiPanelRect.x + compMargin, guiPanelRect.y + 30, 20, 20 ), "debug", &debug );
        GuiCheckBox( Rectangle( guiPanelRect.x + compMargin, guiPanelRect.y + 60, 20, 20 ), "fps", &showFPS );
        GuiCheckBox( Rectangle( guiPanelRect.x + compMargin, guiPanelRect.y + 90, 20, 20 ), "immortal", &immortalMario );
        mario.setImmortal( immortalMario );

        if ( showFPS ) {
            DrawRectangle( guiPanelRect.x, guiPanelRect.y - 30, guiPanelRect.width, 25, Fade( WHITE, 0.9 ) );
            DrawRectangleLines( guiPanelRect.x, guiPanelRect.y - 30, guiPanelRect.width, 25, GRAY );
            DrawFPS( guiPanelRect.x + compMargin, guiPanelRect.y - 27 );
        }

    }

    EndDrawing();

}

/**
 * @brief Load game resources like images, textures, sounds, fonts, shaders etc.
 * Should be called inside the constructor.
 */
void GameWorld::loadResources() {
    ResourceManager::loadResources();
}

/**
 * @brief Unload the once loaded game resources.
 * Should be called inside the destructor.
 */
void GameWorld::unloadResources() {
    ResourceManager::unloadResources();
}

void GameWorld::setCamera( Camera2D *camera ) {
    this->camera = camera;
    this->map.setCamera( camera );
}

Camera2D* GameWorld::getCamera() const {
    return camera;
}

void GameWorld::resetMap() {
    mario.reset( true );
    map.reset();
    state = GAME_STATE_PLAYING;
}

void GameWorld::resetGame() {
    mario.resetAll();
    map.first();
    map.reset();
    state = GAME_STATE_TITLE_SCREEN;
}

void GameWorld::nextMap() {
    if ( map.next() ) {
        mario.reset( false );
        state = GAME_STATE_PLAYING;
    } else {
        state = GAME_STATE_FINISHED;
    }
}

void GameWorld::pauseGame( bool playPauseSFX, bool pauseMusic, bool showOverlay, bool pauseMarioUpdate ) {
    if ( playPauseSFX ) {
        PlaySound( ResourceManager::getSounds()["pause"] );
    }
    this->pauseMusic = pauseMusic;
    showOverlayOnPause = showOverlay;
    this->pauseMarioUpdate = pauseMarioUpdate;
    stateBeforePause = state;
    state = GAME_STATE_PAUSED;
}

void GameWorld::unpauseGame() {
    state = stateBeforePause;
    map.setDrawMessage( false );
    pauseMusic = false;
    pauseMarioUpdate = false;
}

bool GameWorld::isPauseMusicOnPause() const {
    return pauseMusic;
}

bool GameWorld::isShowOverlayOnPause() const {
    return showOverlayOnPause;
}