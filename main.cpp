#include <iostream>
#include <unistd.h>
#include "timeout.h"
 extern "C" {
int main()
{
    std::cout << "Start Testing" << std::endl;

    int i=hm_init(&hashmap);

    std::cout << "HashMap initialization State:"<<i<<std::endl;
    std::cout << "Add device duration 1, address 1:"<<hm_add(1,1)<<std::endl;
    std::cout <<"wait for 2 s"<<std::endl;
    usleep(2000000);
    std::cout<<"END"<<std::endl;
    check_timeout();
    hm_disconnect(1);
    std::cout<<"Disconnected successfully"<<std::endl;
    //std::cout<<"Clear HashMap:"<<hm_destroy(hashmap)<<std::endl;*/ Error
    return 0;
}
 }
