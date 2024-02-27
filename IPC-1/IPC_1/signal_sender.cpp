#include <iostream>
#include <sys/types.h>
#include <signal.h>
#include <cstring>




int main(int argc,char **argv)
{
    if(argc < 2)
    {
        std::cerr << "not enogth arguments";
        std::exit(1);
    }
    
    char* pid_p = argv[1];
    
    int pid = atoi(pid_p);

    int kill_res = kill(pid, SIGUSR1);
    if(kill_res < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    
    return 0;
}