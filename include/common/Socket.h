#ifndef SRC_COMMON_SOCKET_H
#define SRC_COMMON_SOCKET_H


#include <string>
#include <netdb.h>
#include <vector>

class SocketException : public std::exception {
private:
	std::string description;
public:
	SocketException(const char* description, const char* error);

	const char* what() const noexcept;
};

class Socket {
private:
    int skt_fd;

    int _try_addrinfo_connections(struct addrinfo *address_list);

    addrinfo *_get_address_list(const char *host, const char *service);

public:
    Socket();

    ~Socket();

    // move operators
    Socket(Socket &&other);

    Socket &operator=(Socket &&other);

    // cant copy the socket
    Socket(const Socket &other) = delete;

    Socket &operator=(const Socket &other) = delete;

    void connect_to(std::string &host, std::string &service);

    void bind_and_listen(std::string &service);

    Socket accept_connection();

    int send(const char *message, size_t len);

    void receive(char *buffer, size_t bytes_to_read);

    void shutdown();
};


#endif //SRC_COMMON_SOCKET_H
