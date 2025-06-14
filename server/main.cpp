#include "server/server.h"
#include "tests/client/mock_server.h"

int main(int argc, char* argv[]) {
    if (argc != 2)
        return 1;

    std::string servname = argv[1];

    /* MockServer server;
    server.start(servname); */

    Server server(servname);
    server.start();

    return 0;
}
