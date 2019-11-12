//
// Created by casimiro on 29/10/19.
//

#include "common/Communication.h"


Communication::Communication(std::string &host, std::string &service) {
    this->socket.connect_to(host, service);
}



Communication::Communication(Socket socket) {
    this->socket = std::move(socket);
}


void Communication::shutdown() {
    this->socket.shutdown();
}


void Communication::send_msg(std::string& msg) {
    uint16_t msg_len = msg.length();
    try {
        this->socket.send((char*) &msg_len, sizeof(uint16_t));
        this->socket.send((char*) msg.data(), msg_len);
    } catch (std::runtime_error& e) {
        std::string err = "Error in Communication::send_msg -> ";
        err += e.what();
        throw std::runtime_error(err);
    }
}


void Communication::receive_msg(std::string& msg) {
    try {
        uint16_t bytes_to_read = 0;
        this->socket.receive((char*) &bytes_to_read, sizeof(uint16_t));
        msg.resize(bytes_to_read);
        this->socket.receive((char*) msg.data(), bytes_to_read);
        std::cout << msg.data() << "\n";
    } catch (std::runtime_error& e) {
        std::string err = "Error in Communication::receive_msg -> ";
        err += e.what();
        throw std::runtime_error(err);
    }
}

Communication::Communication(Communication &&other) {
    this->socket = std::move(other.socket);
}

Communication &Communication::operator=(Communication &&other) {
    if (this == &other) return *this;
    this->socket = std::move(other.socket);
    return *this;
}

Communication::Communication() {;}

