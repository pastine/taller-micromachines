#include "common/Socket.h"
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include <cstring>

#define MAX_CLIENT_QUEUE 10

Socket::Socket() {
    this->skt_fd = -1;
}

Socket::Socket(Socket &&other) {
    this->skt_fd = other.skt_fd;
    other.skt_fd = -1;
}

addrinfo* Socket::_get_address_list(const char *host, const char* service) {
    struct addrinfo hints;
    struct addrinfo *addr_list;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;

    // we get a list of posible addresses to connect to.
    int err = getaddrinfo(host, service, &hints, &addr_list);
    if (err != 0) {
        std::cout << gai_strerror(err) << "\n";
        return NULL;
    }
    return addr_list;
}

int Socket::_try_addrinfo_connections(struct addrinfo* addr_list) {
    // we are trying to connect to each address,
    // stoping (and using) the first one we can connect to.
    int skt_temp = -1;
    int err;
    for (struct addrinfo *ptr = addr_list; ptr != nullptr; ptr = ptr->ai_next) {
        skt_temp = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (skt_temp == -1) {
            // the socket creation faild given that the
            // address is not available we should try the next one
            // so we continue the loop
            continue;
        }
        err = connect(skt_temp, ptr->ai_addr, ptr->ai_addrlen);
        if (err == -1) return -1;
        // if we had no issues connecting to the address, we exit the loop
        break;
    }
    // if we didn't connect to any addresses, the function will return -1.
    return skt_temp;
}

void Socket::connect_to(std::string& host, std::string& service) {
    const char* _host = host.data();
    const char* _service = service.data();
    struct addrinfo *addr_list = this->_get_address_list(_host, _service);
    if (!addr_list) throw std::runtime_error("No address list available");

    int skt_temp = _try_addrinfo_connections(addr_list);
    if (skt_temp < 0) throw std::runtime_error("Failed to connect socket");
    freeaddrinfo(addr_list);

    this->skt_fd = skt_temp;
}

void Socket::bind_and_listen(std::string &service) {
    const char* _service = service.data();
    struct addrinfo *addr_list = _get_address_list(NULL, _service);
    if (! addr_list) throw std::runtime_error("No address list available");

    int skt_fd_tmp = -1;
    struct addrinfo *ptr;
    for (ptr = addr_list; ptr != nullptr; ptr = ptr->ai_next) {
        skt_fd_tmp = socket(ptr->ai_family,
                             ptr->ai_socktype,
                             ptr->ai_protocol);
        if (skt_fd_tmp < 0) break;
        if (bind(skt_fd_tmp, addr_list->ai_addr, addr_list->ai_addrlen) == 0) {
            break;
        }
        close(skt_fd_tmp);
    }
    freeaddrinfo(addr_list);

    if (skt_fd_tmp < 0)
        throw std::runtime_error("Failed to create the socket");

    int status = listen(skt_fd_tmp, MAX_CLIENT_QUEUE);
    if (status != 0) throw std::runtime_error("Failed to start listening");
    this->skt_fd = skt_fd_tmp;
}

Socket Socket::accept_connection() {
    Socket other;
    other.skt_fd = accept(this->skt_fd, NULL, NULL);
    if (other.skt_fd < 0){
        std::string err = "Socket can't accept client: ";
        err += strerror(errno);
        throw std::runtime_error(err);
    }
    // this socket will be moved because there is no copy constructor
    return other;
}

int Socket::send(const char *message, size_t len) {
    int bytes_sent = 0, sent_this_time = 0;
    while (bytes_sent < (int) len) {
        sent_this_time = ::send(this->skt_fd,
                                &message[bytes_sent],
                                len - bytes_sent,
                                MSG_NOSIGNAL);
        bytes_sent += sent_this_time;
        if (sent_this_time <= 0) {
            std::string err = "Socket Connection lost: ";
            err += strerror(errno);
            throw std::runtime_error(err);
        }
    }
    return bytes_sent;
}

void Socket::receive(char *buffer, size_t bytes_to_read) {
    int bytes_received = 0, recv_this_time = 0;
    while (bytes_received < (int) bytes_to_read) {
        recv_this_time = ::recv(this->skt_fd,
                                &buffer[bytes_received],
                                bytes_to_read - bytes_received,
                                0);
        if (recv_this_time <= 0) {
            std::string err = "Socket Connection lost: ";
            err += strerror(errno);
            throw std::runtime_error(err);
        }
        bytes_received += recv_this_time;
    }
}

Socket::~Socket() {
    if (this->skt_fd > 0) {
        close(skt_fd);
    }
}

Socket& Socket::operator=(Socket &&other) {
    if (this == &other) return *this;
    this->skt_fd = other.skt_fd;
    other.skt_fd = -1;
    return *this;
}

void Socket::shutdown() {
    if (this->skt_fd < 0) return;
    ::shutdown(this->skt_fd, SHUT_RDWR);
    close(this->skt_fd);
}
