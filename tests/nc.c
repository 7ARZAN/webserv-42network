#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>

#define BUFFER_SIZE 1024
struct pollfd fds[20];
int fdd = 0;

int main(int argc, char **argv) {
	int server_fd, new_socket;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	char buffer[BUFFER_SIZE] = {0};

			// we wanna use ipv4 and tcp
	server_fd = socket(AF_INET, SOCK_STREAM  , 0);
	fcntl(server_fd, F_SETFL, fcntl(server_fd, F_GETFL, 0) | O_NONBLOCK);

	// Setting up the address struct
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(atoi(argv[1]));

	// Binding the socket to the port 8800
	bind(server_fd, (struct sockaddr *)&address, sizeof(address));


	// Listening for incoming connections
	if (listen(server_fd, 20) < 0) {
		perror("listen");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	printf("Server is listening on port %d\n", atoi(argv[1]));
	while (true){
		int new_socket = accept(server_fd, NULL, NULL);
		if (new_socket != -1){
			fds[fdd].fd = new_socket;
			fds[fdd].events = POLLIN;
			printf("new fucking connection %d\n", fds[fdd].fd);
			fdd++;
		}
		if (fdd > 20)
			break;
		int i = -1;
		while (++i < fdd){
			poll(fds, fdd, 1);
			if (fds[i].revents != 0) {
			printf("  fd=%d; events: %s%s%s\n", fds[i].fd,
				(fds[i].revents & POLLIN)  ? "POLLIN "  : "",
				(fds[i].revents & POLLHUP) ? "POLLHUP " : "",
				(fds[i].revents & POLLERR) ? "POLLERR " : "");
			}
			bzero(buffer, 1024);
			if (fds[i].revents & POLLIN){
				read(fds[i].fd, buffer, 1024);
				if (strlen(buffer) > 0)
					printf("connection {%d} %s\n", fds[i].fd, buffer);
			}
		}
	}

	return 0;
}

