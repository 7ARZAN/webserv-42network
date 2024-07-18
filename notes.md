# questions

how the fuck is networks implimented in the kernel space? vlan? 

# it all starts with a socket
sockets are used to either communicate withing the same machine or to conmmunicate 
with other machines.
a socket in unix is basically a file descriptor.

## communication domains
socket syscall needs some informations about the socket to tune it out
    - the format of the socket
    - range of communication, either between processes or diffrent hosts
        connected to a single network
### domains?
supported domains are
    . `AF_UNIX` allows communication between applications on the same host within the kernel
    . `AF_INET` allows communication between applications running via IPV4 networks
    . `AF_INET6` allows communication between applications running via IPV6 networks
PF stands for protocol family
AF stands for address family


## socket types
there are basically two types of sockets datagram[udp] stream[tcp]
. stream
    + bidirectional
    + more reliable delivery
    - a bit slow
. datagram
    + connectionless
    + fast
    - less reliable delivery

## sockets API review
`socket()` : creates a new socket
`bind()`   : binds a socket to a certain address
`listen()` : allows a stream socket to accept incomming connections
`accept()` : accepts a connection from a peer 
`connect()`: establishes a connection with another socket

sockets can be used using read() and write() but its better to use `send()`, `recv()`, `sendto()`,
`recvfrom()`

# creating a socket
```c
#include <sys/socket.h>
int socket(int domain, int type, int protocol);
```
Domain is the communication domain for the socket [AF_UNIX...]
Type basically the communication domain for this socket either SOCK_STREAM for tcp or SOCK_DGRAM for udp
Protocol is set to 0 in sockets we use, if raw sockets are used we SOCK_RAW, or maybe to set the socket
to be non blocking we use SOCK_NONBLOCK

# binding the socket
```c
#include <sys/socket.h>
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

bind needs as an argument a sockaddr struct 
```c
struct sockaddr {
    sa_family_t sa_family; /* Address family (AF_* constant) */
    char sa_data[14]; /* Socket address (size varies according to socket domain) */
};
```
looking at each type of sockets, unix sockets uses **pathnames** while internet sockets uses a combination of
ip addr plus port number

we are sure that we are using Internet sockets so why bother and fill sockaddr, we can just use sockaddr_in and
cast it to sockaddr
```c
struct sockaddr_in {
    short int          sin_family;  // Address family, AF_INET
    unsigned short int sin_port;    // Port number
    struct in_addr     sin_addr;    // Internet address
    unsigned char      sin_zero[8]; // Same size as struct sockaddr
};
struct in_addr {
    uint32_t s_addr; // that's a 32-bit int (4 bytes)
};
```

## listening for incomming connections
```c
#include <sys/socket.h>
int listen(int sockfd, int backlog);
```

the listen syscall marks the stream socket as a socket ready to be connected to, the backlog limits the connections 
that our sockets could listen to

## quick history of a connection
2 computers fell in love
each one of them **opened a socket** for the other
computer a listened through his socket
computer b connected to that socket
computer a accepted
then they talked forever using `read()` and `write()`

computer a opened a passive socket
computer b opened a active connection

## accepting
```c
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

