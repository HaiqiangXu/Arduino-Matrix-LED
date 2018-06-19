#include <MD_MAX72xx.h>
#include <TrueRandom.h>
#include <CCommon.h>
#include <CJoystick.h>

//TODO: made these constants parameters of the constructors and set in the main.cpp instead of here
const int IN_AXIS_X = 17;   //A3
const int IN_AXIS_Y = 18;   //A4
const int IN_BUTTON = 2;
const unsigned long TIME_TO_POWER_DOWN = 60000;     //1 minute

enum class EGame { Tetris, Snake };
enum class EGameTurn { Computer, User };

class CLedGame
{
public:
    // Constructors
    CLedGame(int csPin, int iNumDevices, int iPinAxisX, int iPinAxisY, int iPinButton)
    {
        // initialize variables
        m_leds = new MD_MAX72XX(csPin, iNumDevices);
        m_leds->begin();
        m_iNumDevices = iNumDevices;

        m_joystick = new CJoystick(IN_AXIS_X, IN_AXIS_Y, IN_BUTTON);
        m_currentGame = EGame::Tetris;
        m_currentTurn = EGameTurn::User;
        m_lastDirectionX = EDirection::None;
        m_lastDirectionY = EDirection::None;
        m_iCurrentLevel = 0;
        m_lLastTime = millis();
    };

    // Public methods
    void SetGame(EGame newGame)
    {
        m_currentGame = newGame;
    };
    void StartGame();

    // Data accessors
	int GetNumDevices()
	{
		return m_iNumDevices;
	};

    EGame GetCurrentGame()
	{
		return m_currentGame;
	};
private:
    // Fields
    MD_MAX72XX* m_leds;
    CJoystick* m_joystick;
    int m_iNumDevices;          //number of Matrix leds attached
    EGame m_currentGame;
    EGameTurn m_currentTurn;
    EDirection m_lastDirectionX, m_lastDirectionY;
    int m_iButtonZ;
    int m_iCurrentLevel;        //current led for user to guess
    unsigned long m_lLastTime;

    // Private methods
    void GameTetris();
    void GameSnake();
    void ReadUserControls();
};