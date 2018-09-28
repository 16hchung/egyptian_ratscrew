/**
 * ers_game.h
 * ----------
 * controller class which handles all game play
 */

#ifndef ERS_GAME_H
#define ERS_GAME_H
#include "deck.h"
#include "center_pile.h"

// forward declarations
class MainCenterPileView;
class BurnCenterPileView;
class PlayerView;
class InstructionsView;

class EgyptianRatscrewGame {
public:
    EgyptianRatscrewGame();
    ~EgyptianRatscrewGame();

    /** plays game, destructor handles everything with closing views, etc. */
    void play();

private:
    // CONSTRUCTOR HELPERS

    /** enforce a minimum window size, application exits with prompt if too small */
    void checkWindowSize();

    /** prints tutorial */
    void printIntro();

    /** prompts for player names and initializes player objects */
    void initPlayers();

    /** initializes all views */
    void initViews();

    // GAME PLAY HELPERS

    /**
     * called when player has slapped center
     * @param  playerIdx index of player who slapped
     * @return           true if slap is valid
     */
    bool playerSlappedCenter(int playerIdx);

    /** handles taking card from player (with next turn) and placing on central pile */
    void cardDown();

    /** check if player has lost */
    bool isGameDone();

    /** sets turn to next player */
    void nextPlayerTurn();

    /** get pointer to player who went befor this one */
    Player *getLastPlayer(int playerIdx = -1);

    /** gets pointer to current player (who just placed down card) */
    Player *getCurrentPlayer();

    // MODEL
    std::string winnerName = "";
    /** set in worst case scenario, if true, game will exit */
    bool shouldKillGame = false;

    Deck deck;
    CenterCardPile centerPile;
    std::vector<Player *> players;

    int currentPlayerIdx = 0;
    
    // VIEWS
    MainCenterPileView *centerPileView   = nullptr;
    BurnCenterPileView *burnPileView     = nullptr;
    PlayerView         *player1View      = nullptr;
    PlayerView         *player2View      = nullptr;
    InstructionsView   *instructionsView = nullptr;
};

#endif