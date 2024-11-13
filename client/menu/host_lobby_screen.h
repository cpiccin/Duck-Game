#ifndef HOST_LOBBY_SCREEN_H
#define HOST_LOBBY_SCREEN_H

#include <QPainter>
#include <QResizeEvent>
#include <qboxlayout.h>
#include <QLabel>
#include <QLineEdit>
#include <qfontdatabase.h>
#include <QPushButton>
#include <QDebug> 
#include <iostream>
#include <QSound>
#include <QScrollArea>
#include <string>
#include <QTimer>
#include <iostream>
#include <map>
#include "rounded_rectangle.h"
#include "../../common/queue.h"
#include "../../common/messages/generic_msg.h"

class HostLobbyScreen : public QWidget {
    Q_OBJECT

public: 
    HostLobbyScreen(Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue);


private slots: 
    void onAddLocalPlayerButtonClicked();
    void updatePlayersInLobby();
    void onLeftArrowClicked();
    void onRightArrowClicked();
    void onReadyButtonClicked();
signals: 
    void playersUpdated();

private:
    Queue<GenericMsg*>* send_queue;
    Queue<GenericMsg*>* recv_queue; 
    QFont customFont;
    QSound *keyPressSound;
    QPushButton *localPlayerButton;
    QScrollArea* scrollArea;
    QWidget* scrollWidget;
    QVBoxLayout* scrollLayout;
    QPixmap *leftIcon;
    QPixmap *rightIcon;
    uint8_t lobby_id;
    bool isLocalPlayerAdded = false;
    std::list<DescipcionPlayer> players;
    std::vector<QWidget*> lobbyWidgets;
    // color de pato y su imagen
    std::list<std::pair<uint8_t, QPixmap*>> ducks_images;
    void processIncomingMessages();
};  

#endif // LOBBY_SCREEN_H
