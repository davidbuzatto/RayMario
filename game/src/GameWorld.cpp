/**
 * @file GameWorld.cpp
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "GameWorld.h"
#include "GameState.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <cassert>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
//#include "raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION

#include "Mario.h"
#include "Item.h"
#include "Baddie.h"
#include "SpriteState.h"
#include "Tile.h"
#include "Box.h"
#include "utils.h"

#define ACTIVATE_DEBUG true

#define INITIAL_MAP_ID 1
#define LOAD_TEST_MAP false

#define PARSE_BOXES true
#define PARSE_ITEMS false
#define PARSE_BADDIES false


bool GameWorld::debug = ACTIVATE_DEBUG;
bool GameWorld::showFPS = ACTIVATE_DEBUG;
bool GameWorld::immortalMario = ACTIVATE_DEBUG;
//GameState GameWorld::state = GameState::TITLE_SCREEN;
GameState GameWorld::state = GameState::PLAYING;
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
    map( mario, INITIAL_MAP_ID, LOAD_TEST_MAP, PARSE_BOXES, PARSE_ITEMS, PARSE_BADDIES ),
    camera( nullptr ),
    showControls( ACTIVATE_DEBUG ),
    stateBeforePause( GameState::TITLE_SCREEN ) {
    mario.changeToFlower();
    std::cout << "creating game world..." << std::endl;
}

/**
 * @brief Destroy the GameWorld object
 */
GameWorld::~GameWorld() {
    std::cout << "destroying game world..." << std::endl;
}

/**
 * @brief Reads user input and updates the state of the game.
 */
void GameWorld::inputAndUpdate() {

    map.parseMap();

    std::vector<Tile*> &tiles = map.getTiles();
    std::vector<Box*> &boxes = map.getBoxes();
    std::vector<Item*> &items = map.getItems();
    std::vector<Baddie*> &baddies = map.getBaddies();

    std::vector<int> collectedIndexes;
    std::map<std::string, Sound> &sounds = ResourceManager::getSounds();
    std::map<std::string, Music> &musics = ResourceManager::getMusics();

    if ( IsKeyPressed( KEY_LEFT_ALT ) ) {
        showControls = !showControls;
    }

    if ( mario.getState() != SpriteState::DYING && 
         mario.getState() != SpriteState::VICTORY &&
         state != GameState::TITLE_SCREEN &&
         state != GameState::FINISHED && 
         state != GameState::PAUSED ) {
        map.playMusic();
    }

    if ( state != GameState::TITLE_SCREEN &&
         state != GameState::FINISHED &&
         state != GameState::PAUSED ) {
        mario.setActivationWidth( GetScreenWidth() * 2 );
        mario.update();
    }

    if ( mario.getState() != SpriteState::DYING && 
         mario.getState() != SpriteState::VICTORY &&
         state != GameState::TITLE_SCREEN &&
         state != GameState::FINISHED &&
         state != GameState::PAUSED ) {

        if ( IsKeyPressed( KEY_ENTER ) || IsGamepadButtonPressed( 0, GAMEPAD_BUTTON_MIDDLE_RIGHT ) ) {
            PlaySound( sounds["pause"] );
            stateBeforePause = state;
            state = GameState::PAUSED;
        }

        for ( size_t i = 0; i < boxes.size(); i++ ) {
            boxes[i]->update();
        }

        for ( size_t i = 0; i < items.size(); i++ ) {
            items[i]->update();
        }

        for ( size_t i = 0; i < baddies.size(); i++ ) {
            baddies[i]->update();
        }

        // tiles collision resolution
        mario.updateCollisionProbes();
        for ( size_t i = 0; i < tiles.size(); i++ ) {

            Tile *tile = tiles[i];

            // mario x tiles
            if ( !tile->isOnlyBaddies() ) {
                switch ( mario.checkCollision( tile ) ) {
                    case CollisionType::NORTH:
                        mario.setY( tile->getY() + tile->getHeight() );
                        mario.setVelY( 0 );
                        mario.updateCollisionProbes();
                        break;
                    case CollisionType::SOUTH:
                        mario.setY( tile->getY() - mario.getHeight() );
                        mario.setVelY( 0 );
                        mario.setState( SpriteState::ON_GROUND );
                        mario.updateCollisionProbes();
                        break;
                    case CollisionType::EAST:
                        mario.setX( tile->getX() - mario.getWidth() );
                        mario.setVelX( 0 );
                        mario.updateCollisionProbes();
                        break;
                    case CollisionType::WEST:
                        mario.setX( tile->getX() + tile->getWidth() );
                        mario.setVelX( 0 );
                        mario.updateCollisionProbes();
                        break;
                    case CollisionType::NONE:
                        break;
                }
            }

            // baddies x tiles
            for ( size_t j = 0; j < baddies.size(); j++ ) {
                Baddie* baddie = baddies[j];
                baddie->updateCollisionProbes();
                if ( baddie->getState() != SpriteState::DYING ) {
                    switch ( baddie->checkCollision( tile ) ) {
                        case CollisionType::NORTH:
                            baddie->setY( tile->getY() + tile->getHeight() );
                            baddie->setVelY( 0 );
                            baddie->updateCollisionProbes();
                            break;
                        case CollisionType::SOUTH:
                            baddie->setY( tile->getY() - baddie->getHeight() );
                            baddie->setVelY( 0 );
                            baddie->onSouthCollision();
                            baddie->updateCollisionProbes();
                            break;
                        case CollisionType::EAST:
                            baddie->setX( tile->getX() - baddie->getWidth() );
                            baddie->setVelX( -baddie->getVelX() );
                            baddie->updateCollisionProbes();
                            break;
                        case CollisionType::WEST:
                            baddie->setX( tile->getX() + tile->getWidth() );
                            baddie->setVelX( -baddie->getVelX() );
                            baddie->updateCollisionProbes();
                            break;
                    }
                }
            }

            // items x tiles
            for ( size_t j = 0; j < items.size(); j++ ) {
                Item* item = items[j];
                item->updateCollisionProbes();
                switch ( item->checkCollision( tile ) ) {
                    case CollisionType::NORTH:
                        item->setY( tile->getY() + tile->getHeight() );
                        item->setVelY( 0 );
                        item->updateCollisionProbes();
                        break;
                    case CollisionType::SOUTH:
                        item->setY( tile->getY() - item->getHeight() );
                        item->setVelY( 0 );
                        item->onSouthCollision();
                        item->updateCollisionProbes();
                        break;
                    case CollisionType::EAST:
                        item->setX( tile->getX() - item->getWidth() );
                        item->setVelX( -item->getVelX() );
                        item->updateCollisionProbes();
                        break;
                    case CollisionType::WEST:
                        item->setX( tile->getX() + tile->getWidth() );
                        item->setVelX( -item->getVelX() );
                        item->updateCollisionProbes();
                        break;
                }
            }

        }

        // boxes collision resolution
        mario.updateCollisionProbes();
        for ( size_t i = 0; i < boxes.size(); i++ ) {

            Box *box = boxes[i];

            // mario x boxes
            switch ( mario.checkCollision( box ) ) {
                case CollisionType::NORTH:
                    mario.setY( box->getY() + box->getHeight() );
                    mario.setVelY( 0 );
                    mario.updateCollisionProbes();
                    box->doHit( mario, &map );
                    break;
                case CollisionType::SOUTH:
                    mario.setY( box->getY() - mario.getHeight() );
                    mario.setVelY( 0 );
                    mario.setState( SpriteState::ON_GROUND );
                    mario.updateCollisionProbes();
                    break;
                case CollisionType::EAST:
                    mario.setX( box->getX() - mario.getWidth() );
                    mario.setVelX( 0 );
                    mario.updateCollisionProbes();
                    break;
                case CollisionType::WEST:
                    mario.setX( box->getX() + box->getWidth() );
                    mario.setVelX( 0 );
                    mario.updateCollisionProbes();
                    break;
                case CollisionType::NONE:
                    break;
            }

            // baddies x boxes
            for ( size_t j = 0; j < baddies.size(); j++ ) {
                Baddie* baddie = baddies[j];
                baddie->updateCollisionProbes();
                if ( baddie->getState() != SpriteState::DYING ) {
                    switch ( baddie->checkCollision( box ) ) {
                        case CollisionType::NORTH:
                            baddie->setY( box->getY() + box->getHeight() );
                            baddie->setVelY( 0 );
                            baddie->updateCollisionProbes();
                            break;
                        case CollisionType::SOUTH:
                            baddie->setY( box->getY() - baddie->getHeight() );
                            baddie->setVelY( 0 );
                            baddie->onSouthCollision();
                            baddie->updateCollisionProbes();
                            break;
                        case CollisionType::EAST:
                            baddie->setX( box->getX() - baddie->getWidth() );
                            baddie->setVelX( -baddie->getVelX() );
                            baddie->updateCollisionProbes();
                            break;
                        case CollisionType::WEST:
                            baddie->setX( box->getX() + box->getWidth() );
                            baddie->setVelX( -baddie->getVelX() );
                            baddie->updateCollisionProbes();
                            break;
                    }
                }
            }

            // items x boxes
            for ( size_t j = 0; j < items.size(); j++ ) {
                Item* item = items[j];
                item->updateCollisionProbes();
                switch ( item->checkCollision( box ) ) {
                    case CollisionType::NORTH:
                        item->setY( box->getY() + box->getHeight() );
                        item->setVelY( 0 );
                        item->updateCollisionProbes();
                        break;
                    case CollisionType::SOUTH:
                        item->setY( box->getY() - item->getHeight() );
                        item->setVelY( 0 );
                        item->onSouthCollision();
                        item->updateCollisionProbes();
                        break;
                    case CollisionType::EAST:
                        item->setX( box->getX() - item->getWidth() );
                        item->setVelX( -item->getVelX() );
                        item->updateCollisionProbes();
                        break;
                    case CollisionType::WEST:
                        item->setX( box->getX() + box->getWidth() );
                        item->setVelX( -item->getVelX() );
                        item->updateCollisionProbes();
                        break;
                }
            }

        }

        // mario x items collision resolution and offscreen items removal
        for ( size_t i = 0; i < items.size(); i++ ) {

            Item* item = items[i];

            if ( item->checkCollision( &mario ) != CollisionType::NONE ) {
                collectedIndexes.push_back( i );
                item->playCollisionSound();
                item->updateMario( mario );
            } else if ( item->getY() > map.getMaxHeight() ) {
                collectedIndexes.push_back( i );
            }

        }

        for ( int i = collectedIndexes.size() - 1; i >= 0; i-- ) {
            delete items[collectedIndexes[i]];
            items.erase( items.begin() + collectedIndexes[i] );
        }

        // baddies activation and mario and fireballs x baddies collision resolution and offscreen baddies removal
        collectedIndexes.clear();
        if ( mario.getState() != SpriteState::DYING && mario.getState() != SpriteState::VICTORY ) {

            mario.updateCollisionProbes();

            for ( size_t i = 0; i < baddies.size(); i++ ) {

                Baddie* baddie = baddies[i];

                // baddies activation
                if ( baddie->getState() == SpriteState::IDLE ) {
                    baddie->activateWithMarioProximity( mario );
                }

                // mario and fireballs x baddies collision resolution and offscreen baddies removal
                switch ( mario.checkCollisionBaddie( baddie ) ) {
                    case CollisionType::NORTH:
                    case CollisionType::EAST:
                    case CollisionType::WEST:
                        if ( !mario.isImmortal() && !mario.isInvulnerable() ) {
                            switch ( mario.getType() ) {
                                case MarioType::SMALL:
                                    mario.setState( SpriteState::DYING );
                                    PlaySound( sounds["playerDown"] );
                                    mario.removeLives( 1 );
                                    break;
                                case MarioType::SUPER:
                                    PlaySound( sounds["pipe"] );
                                    mario.changeToSmall();
                                    mario.setInvulnerable( true );
                                    mario.consumeReservedPowerUp();
                                    break;
                                case MarioType::FLOWER:
                                    PlaySound( sounds["pipe"] );
                                    mario.changeToSmall();
                                    mario.setInvulnerable( true );
                                    mario.consumeReservedPowerUp();
                                    break;
                            }
                        }
                        break;
                    case CollisionType::SOUTH:
                        if ( mario.getState() == SpriteState::FALLING && baddie->getState() != SpriteState::DYING ) {
                            mario.setY( baddie->getY() - mario.getHeight() );
                            mario.setVelY( -200 );
                            mario.setState( SpriteState::JUMPING );
                            baddie->onHit();
                            PlaySound( sounds["stomp"] );
                            mario.addPoints( 200 );
                        } else {
                            if ( !mario.isImmortal() && !mario.isInvulnerable() ) {
                                switch ( mario.getType() ) {
                                    case MarioType::SMALL:
                                        mario.setState( SpriteState::DYING );
                                        PlaySound( sounds["playerDown"] );
                                        mario.removeLives( 1 );
                                        break;
                                    case MarioType::SUPER:
                                        PlaySound( sounds["pipe"] );
                                        mario.changeToSmall();
                                        mario.setInvulnerable( true );
                                        mario.consumeReservedPowerUp();
                                        break;
                                    case MarioType::FLOWER:
                                        PlaySound( sounds["pipe"] );
                                        mario.changeToSmall();
                                        mario.setInvulnerable( true );
                                        mario.consumeReservedPowerUp();
                                        break;
                                }
                            }
                        }
                        break;
                    default:
                        if ( baddie->getY() > map.getMaxHeight() ) {
                            baddie->setState( SpriteState::TO_BE_REMOVED );
                        }
                        break;
                }

                if ( baddie->getState() == SpriteState::TO_BE_REMOVED ) {
                    collectedIndexes.push_back( i );
                }

                mario.updateCollisionProbes();

            }

        }

        for ( int i = collectedIndexes.size() - 1; i >= 0; i-- ) {
            delete baddies[collectedIndexes[i]];
            baddies.erase( baddies.begin() + collectedIndexes[i] );
        }

    } else if ( mario.getState() == SpriteState::DYING ) {

        if ( !IsSoundPlaying( sounds["playerDown"] ) && !IsSoundPlaying( sounds["gameOver"] ) ) {
            
            if ( mario.getLives() > 0 ) {
                resetMap();
            } else if ( mario.getLives() < 0 ) {
                resetGame();
            } else {
                PlaySound( sounds["gameOver"] );
                state = GameState::GAME_OVER;
                mario.setLives( -1 );
            }

        }

    } else if ( mario.getState() == SpriteState::VICTORY ) {

        if ( !IsSoundPlaying( sounds["courseClear"] ) ) {
            nextMap();
        }

    } else if ( state == GameState::PAUSED ) {
        if ( IsKeyPressed( KEY_ENTER ) || IsGamepadButtonPressed( 0, GAMEPAD_BUTTON_MIDDLE_RIGHT ) ) {
            state = stateBeforePause;
        }
    }

    if ( mario.getState() != SpriteState::DYING && mario.getY() > map.getMaxHeight() ) {
        mario.setState( SpriteState::DYING );
        PlaySound( sounds["playerDown"] );
        mario.removeLives( 1 );
    }

    if ( IsGamepadButtonPressed( 0, GAMEPAD_BUTTON_RIGHT_TRIGGER_1 ) ) {
        if ( showControls ) {
            debug = !debug;
        }
    }

    float xc = GetScreenWidth() / 2.0;
    float yc = GetScreenHeight() / 2.0;
    float pxc = mario.getX() + mario.getWidth() / 2.0;
    float pyc = mario.getY() + mario.getHeight() / 2.0;
    
    camera->offset.x = xc;

    if ( pxc < xc ) {
        camera->target.x = xc + Map::tileWidth;
        map.setMarioOffset( 0 );         // x parallax
    } else if ( pxc >= map.getMaxWidth() - xc - Map::tileWidth ) {
        camera->target.x = map.getMaxWidth() - GetScreenWidth();
        camera->offset.x = 0;
    } else {
        camera->target.x = pxc + Map::tileWidth;
        map.setMarioOffset( pxc - xc );  // x parallax
    }

    camera->offset.y = yc;

    if ( pyc < yc ) {
        camera->target.y = yc + Map::tileWidth;
    } else if ( pyc >= map.getMaxHeight() - yc - Map::tileWidth ) {
        camera->target.y = map.getMaxHeight() - GetScreenHeight();
        camera->offset.y = 0;
    } else {
        camera->target.y = pyc + Map::tileWidth;
    }

    if ( state == GameState::TITLE_SCREEN ) {

        if ( !IsMusicStreamPlaying( musics["title"] ) ) {
            PlayMusicStream( musics["title"] );
        } else {
            UpdateMusicStream( musics["title"] );
        }

        if ( GetKeyPressed() && !IsKeyPressed( KEY_LEFT_ALT ) ) {
            StopMusicStream( musics["title"] );
            state = GameState::PLAYING;
        }

    }

}

/**
 * @brief Draws the state of the game.
 */
void GameWorld::draw() {

    BeginDrawing();
    ClearBackground( WHITE );

    int columns = GetScreenWidth() / Map::tileWidth;
    int lines = GetScreenHeight() / Map::tileWidth;

    if ( state != GameState::GAME_OVER && state != GameState::TITLE_SCREEN ) {

        BeginMode2D( *camera );

        map.draw();
        mario.draw();

        if ( debug ) {
            for ( int i = -20; i <= lines + 20; i++ ) {
                DrawLine( -2000, i * Map::tileWidth, 10000, i * Map::tileWidth, GRAY );
            }
            for ( int i = -20; i <= columns + 250; i++ ) {
                DrawLine( i * Map::tileWidth, -2000, i * Map::tileWidth, 2000, GRAY );
            }
        }

        EndMode2D();

        mario.drawHud();

        if ( state == GameState::TIME_UP ) {
            Texture2D* t = &ResourceManager::getTextures()["guiTimeUp"];
            DrawTexture( *t, GetScreenWidth() / 2 - t->width / 2, GetScreenHeight() / 2 - t->height / 2, WHITE );
        } else if ( state == GameState::FINISHED ) {

            if ( !IsMusicStreamPlaying( ResourceManager::getMusics()["ending"] ) ) {
                PlayMusicStream( ResourceManager::getMusics()["ending"] );
            } else {
                UpdateMusicStream( ResourceManager::getMusics()["ending"] );
            }

            if ( GetKeyPressed() ) {
                PlayMusicStream( ResourceManager::getMusics()["ending"] );
                resetGame();
            }

            DrawRectangle( 0, 0, GetScreenWidth(), GetScreenHeight(), Fade( RAYWHITE, 0.9 ) );
            Texture2D* t = &ResourceManager::getTextures()["guiCredits"];
            DrawTexture( *t, GetScreenWidth() / 2 - t->width / 2, 20, WHITE );

            std::string message1 = "Thank you for playing!!!";
            std::string message2 = "Press any key to restart!";

            drawString( message1, GetScreenWidth() / 2 - getDrawStringWidth( message1 ) / 2, t->height + 40, ResourceManager::getTextures() );
            drawString( message2, GetScreenWidth() / 2 - getDrawStringWidth( message2 ) / 2, t->height + 65, ResourceManager::getTextures() );

        } else if ( state == GameState::PAUSED ) {
            DrawRectangle( 0, 0, GetScreenWidth(), GetScreenHeight(), Fade( BLACK, 0.3 ) );
        }

    } else if ( state == GameState::TITLE_SCREEN ) {

        DrawRectangle( 0, 0, GetScreenWidth(), GetScreenHeight(), RAYWHITE );
        Texture2D* t = &ResourceManager::getTextures()["guiRayMarioLogo"];
        DrawTexture( *t, GetScreenWidth() / 2 - t->width / 2, GetScreenHeight() / 2 - t->height, WHITE );

        std::string message1 = "Press any key to start!";
        std::string message2 = "Developed by:";
        std::string message3 = "Prof. Dr. David Buzatto - IFSP";
        std::string message4 = "2024";
        drawString( message1, GetScreenWidth() / 2 - getDrawStringWidth( message1 ) / 2, GetScreenHeight() / 2 + getDrawStringHeight() + 30, ResourceManager::getTextures());
        drawString( message2, GetScreenWidth() / 2 - getDrawStringWidth( message2 ) / 2, GetScreenHeight() / 2 + getDrawStringHeight() * 5 + 30, ResourceManager::getTextures());
        drawString( message3, GetScreenWidth() / 2 - getDrawStringWidth( message3 ) / 2, GetScreenHeight() / 2 + getDrawStringHeight() * 6 + 35, ResourceManager::getTextures());
        drawWhiteSmallNumber( 2024, GetScreenWidth() / 2 - getSmallNumberWidth( 2024 ) / 2, GetScreenHeight() / 2 + getDrawStringHeight() * 7 + 40, ResourceManager::getTextures() );
        
        Rectangle r( 40, 40, 70, 70 );
        DrawRectangle( r.x, r.y, r.width, r.height, Fade( RAYWHITE, 0.5 ) );
        DrawRectangleLinesEx( r, 5, BLACK );
        DrawText( "ray", r.x + r.width - 50, r.y + r.height - 35, 20, BLACK );

    } else if ( state == GameState::GAME_OVER ) {

        DrawRectangle( 0, 0, GetScreenWidth(), GetScreenHeight(), BLACK );
        Texture2D* t = &ResourceManager::getTextures()["guiGameOver"];
        DrawTexture( *t, GetScreenWidth() / 2 - t->width / 2, GetScreenHeight() / 2 - t->height / 2, WHITE );

    }

    if ( showControls ) {

        int compMargin = 10;
        Rectangle guiPanelRect( GetScreenWidth() - 120, GetScreenHeight() - 140, 100, 120 );
        GuiPanel( guiPanelRect, "Controles" );
        GuiCheckBox( Rectangle( guiPanelRect.x + compMargin, guiPanelRect.y + 30, 20, 20 ), "debug", &debug );
        GuiCheckBox( Rectangle( guiPanelRect.x + compMargin, guiPanelRect.y + 60, 20, 20 ), "fps", &showFPS );
        GuiCheckBox( Rectangle( guiPanelRect.x + compMargin, guiPanelRect.y + 90, 20, 20 ), "imortal", &immortalMario );
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
    std::cout << "loading resources..." << std::endl;
    ResourceManager::loadTextures();
    ResourceManager::loadSounds();
    ResourceManager::loadMusics();
}

/**
 * @brief Unload the once loaded game resources.
 * Should be called inside the destructor.
 */
void GameWorld::unloadResources() {
    std::cout << "unloading resources..." << std::endl;
    ResourceManager::unloadTextures();
    ResourceManager::unloadSounds();
    ResourceManager::unloadMusics();
}

void GameWorld::setCamera( Camera2D *camera ) {
    this->camera = camera;
}

void GameWorld::resetMap() {
    mario.reset( true );
    map.reset();
    state = GameState::PLAYING;
}

void GameWorld::resetGame() {
    mario.resetAll();
    map.first();
    map.reset();
    state = GameState::TITLE_SCREEN;
}

void GameWorld::nextMap() {
    if ( map.next() ) {
        mario.reset( false );
        state = GameState::PLAYING;
    } else {
        state = GameState::FINISHED;
    }
}