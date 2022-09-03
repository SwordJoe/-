#include"Reactor.hpp"

void test(int port,char *IP){
    //ReactorServer server(8888,"172.24.40.165",4,1000);
    ReactorServer server(port,IP,4,1000);
    
    server.start();
}

int main(int argc,char *argv[])
{
    test(atoi(argv[2]),argv[1]);
    return 0;
}