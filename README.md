# Socket-Networking

## API

1. Socket Address Structure

```c
struct in_addr{
in_addr_t s_addr; /*32 bit IPv4 network byte ordered address*/
};
struct sockaddr_in {
   uint8_t sin_len; /* length of structure (16)*/
   sa_family_t sin_family; /* AF_INET*/
   in_port_t sin_port; /* 16 bit TCP or UDP port number */
   struct in_addr sin_addr; /* 32 bit IPv4 address*/
   char sin_zero[8]; /* not used but always set to zero */
};
```

2. Generic  Address Structure

```c
struct sockaddr {
   uint8_t sa_len;
   sa_family_t sa_family; /* address family: AD_xxx value */
   char sa_data[14];
};
```

3. Byte ordering
```c
#include <netinet/in.h>
uint16_t htons(uint16_t host16bitvalue);
uint32_t htonl(uint32_t host32bitvalue);
uint16_t ntohs(uint16_t net16bitvalue);
uint32_t ntohl(uint32_t net32bitvalue);
```

4. Elementary Socket System Calls
```c
#include <sys/socket.h>
int socket (int family, int type, int protocol);
int connect (int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);
int bind(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);
/* The listen() function converts an unconnected socket into a passive socket, indicating that the kernel should accept incoming connection requests directed to this socket. */
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *cliaddr,socklen_t *addrlen);
ssize_t send(int sockfd, const void *buf, size_t nbytes, int flags);
ssize_t recv(int sockfd, void *buf, size_t nbytes, int flags);
int close(int sockfd);
ssize_t recvfrom(int sockfd, void* buff, size_t nbytes,int flags, struct sockaddr* from,
                           socklen_t *addrlen);
ssize_t sendto(int sockfd, const void *buff, size_t nbytes,int flags, const struct sockaddr *to, socklen_t addrlen);
```

## Run locally

1. Clone the repository
```bash
git clone https://github.com/waquas9248/Socket-Networking.git
cd Socket-Networking
```

2. Compile a program
```bash
gcc tcp_echo_server.c -o tcp_echo_server
```

3. Run the compiled program:
```bash
./tcp_echo_server
```
