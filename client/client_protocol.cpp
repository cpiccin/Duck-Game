#include "client_protocol.h"

#include <string>
#include <utility>
#include <vector>


ClientProtocol::ClientProtocol(Socket& skt): ProtocoloCommon(skt) {}

void ClientProtocol::handle_recv(EverythingOkMsg& msg) { (void)msg; }

void ClientProtocol::handle_recv(ErrorMsg& msg) {
    std::string error_msg = recv_string();
    msg.set_error_msg(error_msg);
}

void ClientProtocol::handle_send(const ViewLobbiesMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
}

void ClientProtocol::handle_send(const ChooseLobbyMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
    uint8_t lobby_id = msg.get_lobby_id();
    send_u_int8_t(lobby_id);
    std::string player_name = msg.get_player_name();
    send_string(player_name);
}

void ClientProtocol::handle_send(const CreateLobbyMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
    std::string player_name = msg.get_player_name();
    send_string(player_name);
}

void ClientProtocol::handle_send(const GoBackMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
}

void ClientProtocol::handle_send(const ExitFromLobbyMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
    std::string player_name = msg.get_player_name();
    send_string(player_name);
}

void ClientProtocol::handle_send(const StartGameMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
}

void ClientProtocol::handle_recv(InfoLobbyMsg& msg) {
    uint8_t players_size = recv_u_int8_t();
    std::list<DescipcionPlayer> players;

    for (int i = 0; i < players_size; i++) {
        DescipcionPlayer player;
        std::string nombre = recv_string();
        player.nombre = nombre;

        uint8_t color = recv_u_int8_t();
        player.color = color;

        players.push_back(player);
    }
    msg.set_players(players);
}

void ClientProtocol::handle_recv(SendLobbiesListMsg& msg) {
    uint8_t lobbies_size = recv_u_int8_t();
    std::vector<DescripcionLobby> lobbies;

    for (int i = 0; i < lobbies_size; i++) {
        DescripcionLobby lobby;
        uint8_t lobby_id = recv_u_int8_t();
        lobby.idLobby = lobby_id;

        std::string nombre_lobby = recv_string();
        lobby.nombreLobby = nombre_lobby;

        uint8_t cantidad_de_jugadores = recv_u_int8_t();
        lobby.cantidadJugadores = cantidad_de_jugadores;

        lobbies.push_back(lobby);
    }
    msg.set_lobbies(lobbies);
}

void ClientProtocol::handle_send(const CustomizedPlayerInfoMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
    uint8_t color = msg.get_color();
    std::string player_name = msg.get_player_name();
    send_u_int8_t(color);
    send_string(player_name);
}


void ClientProtocol::handle_recv(PickupDropMsg& msg) {
    std::string player_name = recv_string();
    msg.set_player_name(player_name);
    uint8_t item_id = recv_u_int8_t();
    msg.set_item_id(item_id);
}
// void ClientProtocol::handle_send(const PickupDropMsg& msg) {
//     uint8_t header = msg.get_header();
//     send_u_int8_t(header);
//     uint8_t item_id = msg.get_item_id();
//     std::string player_name = msg.get_player_name();
//     send_u_int8_t(item_id);
//     send_string(player_name);
// }

void ClientProtocol::handle_send(const StartActionMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
    uint8_t action_id = msg.get_action_id();
    std::string player_name = msg.get_player_name();
    send_u_int8_t(action_id);
    send_string(player_name);
}

void ClientProtocol::handle_send(const StopActionMsg& msg) {
    uint8_t header = msg.get_header();
    send_u_int8_t(header);
    uint8_t action_id = msg.get_action_id();
    std::string player_name = msg.get_player_name();
    send_u_int8_t(action_id);
    send_string(player_name);
}

void ClientProtocol::handle_recv(GameEndedMsg& msg) { (void)msg; }

void ClientProtocol::handle_recv(WinnerMsg& msg) {
    std::string winner_name = recv_string();
    msg.set_winner_name(winner_name);
}

void ClientProtocol::handle_recv(SendMapMsg& msg) {
    uint16_t filas = recv_u_int16_t();
    msg.set_filas(filas);
    uint16_t columnas = recv_u_int16_t();
    msg.set_columnas(columnas);
    std::vector<uint16_t> map;
    for (int i = 0; i < filas * columnas; i++) {
        uint16_t tile = recv_u_int16_t();
        map.push_back(tile);
    }
    msg.set_map(map);
}

void ClientProtocol::handle_recv(ProjectileInfoMsg& msg) {
    // recibo la posicion del proyectil
    std::vector<std::pair<uint8_t, uint8_t>> trail;
    for (int i = 0; i < recv_u_int8_t(); i++) {
        uint8_t pos_x = recv_u_int8_t();
        uint8_t pos_y = recv_u_int8_t();
        trail.push_back(std::pair<uint8_t, uint8_t>(pos_x, pos_y));
    }
    msg.set_trail(trail);
    uint8_t pos_x = recv_u_int8_t();
    uint8_t pos_y = recv_u_int8_t();
    msg.set_pos_x(pos_x);
    msg.set_pos_y(pos_y);
    // recibo el item del proyectil
    uint8_t item = recv_u_int8_t();
    msg.set_item(item);
}

void ClientProtocol::handle_recv(UpdatedPlayerInfoMsg& msg) {
    std::string player_name = recv_string();
    uint16_t x = recv_u_int16_t();
    uint16_t y = recv_u_int16_t();
    uint8_t state = recv_u_int8_t();
    uint8_t facing_direction = recv_u_int8_t();
    msg.set_player_name(player_name);
    msg.set_position(x, y);
    msg.set_state(state);
    msg.set_facing_direction(facing_direction);
}
