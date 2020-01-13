#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <libgen.h>
#include <fstream>

#define MAX 1024

void curl(const char *path, const char *ip, __uint16_t port)
{
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    send(sock, path, strlen(path),0);
    char *file_name = basename((char *)path);
    char buf[MAX];
    bzero(buf, MAX);
    int n = recv(sock, buf, MAX, 0);
    std::ofstream ostrm(file_name, std::ios::binary);
    ostrm.write(buf, n);

    ostrm.close();
    close(sock);
}

int main(int args, char **argv){
    const char *path = argv[1];
    const char *ip = "127.0.0.1";
    __uint16_t port = 1234;
    curl(path, ip, port);

    return 0;
}
