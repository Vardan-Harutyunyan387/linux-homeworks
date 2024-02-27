#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>

void get_signal(int signal, siginfo_t* info, void* context)
{
    // Received a SIGUSR1 signal from process [PID] executed by [UID] ([username]).
    // State of the context: EIP = [value of EIP], EAX = [value of EAX], EBX = [value of EBX]. 
    pid_t sender_pid = info->si_pid;
    uid_t sender_uid = info->si_uid;

    struct passwd *pw = getpwuid(sender_uid);
    const char *sender_username = (pw != NULL) ? pw->pw_name : "Unknown";

    ucontext_t* context_cast = (ucontext_t*)context;
    unsigned long eip = context_cast->uc_mcontext.gregs[REG_RIP];
    unsigned long eax = context_cast->uc_mcontext.gregs[REG_RAX];
    unsigned long ebx = context_cast->uc_mcontext.gregs[REG_RBX];
    std::cout << "Received a SIGUSR1 signal from process " <<  sender_pid << " executed by " << sender_uid << " (" << sender_username << ")." << std::endl;
    std::cout << "State of the context: EIP = " << eip << ", EAX = " << eax << ", EBX = " << ebx << "." << std::endl;
}



int main()
{
    struct sigaction sg_action;
    memset(&sg_action, 0, sizeof(sg_action));

    sg_action.sa_sigaction = get_signal;
    int sigact_res = sigaction(SIGUSR1, &sg_action, NULL);
    
    while(true)
    {
        std::cout <<" pid = " << getpid() <<  std::endl;
        sleep(10);
    }


    return 0;
}