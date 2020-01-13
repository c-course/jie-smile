#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>

#define MAX 1024

void myserver(const char *root, const char *ip, __uint16_t port)
{
    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr(ip);

    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(serv_sock, 20);

    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    int sock =
            accept(serv_sock, (struct sockaddr *)&client_addr, &client_addr_size);

    char temp[MAX];
    bzero(temp, MAX);
    strcat(temp, root);

    char buf[MAX];
    bzero(buf, MAX);
    recv(sock, buf, MAX, 0);
    char *path = strcat(temp, buf);
    std::ifstream istrm(path, std::ios::binary);
    bzero(buf, MAX);
    istrm.read(buf, MAX);
    int n = istrm.gcount();
    send(sock, buf, n, 0);

    istrm.close();
    close(sock);
    close(serv_sock);
}

int main(int args, char **argv)
{
    const char *root = argv[1];
    const char *ip = "127.0.0.1";
    __uint16_t port = 1234;
    myserver(root, ip, port);

    return 0;
}
