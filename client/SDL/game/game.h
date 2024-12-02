#include <algorithm>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <SDL2/SDL_timer.h>

#include "../../../common/messages/generic_msg.h"
#include "../../../common/queue.h"
#include "../../../common/thread.h"

#include "eventhandler.h"
#include "screens/loadingscreen.h"
#include "screens/pointsscreen.h"
#include "map.h"
#include "music/musichandler.h"
#include "screens/window.h"
#include "screens/winnerscreen.h"
class Game {
private:
    Queue<std::shared_ptr<GenericMsg>>& queueRecive;
    std::atomic<bool> running;
    EventHandler event_handler;
    SDL_Rect displayBounds;
    std::unique_ptr<MusicHandler> musicHandler;
    std::unique_ptr<Window> win;
    std::unique_ptr<LoadingScreen> loadingScreen;
    std::unique_ptr<WinnerScreen> winnerScreen;
    std::unique_ptr<PointsScreen> pointsScreen;

public:
    Game(Queue<std::shared_ptr<GenericMsg>>& queueSend,
         Queue<std::shared_ptr<GenericMsg>>& queueRecive, std::string playerName1,
         std::string playerName2 = "");

    void play();

    ~Game();
};
