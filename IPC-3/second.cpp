#include <semaphore.h>
#include "shared_array.h"

const char *semaphore = "/aaaaa";

int main()
{
    int size = 12;
    Shared_array arr_1("text.txt", size);

    sem_t *sem = sem_open(semaphore, O_RDWR);
    if (sem == SEM_FAILED) {
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
    }


    int i = 0;
    while(true)
    {
        if(i == size - 1)
        {
            i = 0;
        }
        sem_wait(sem);
        std::cout << arr_1[i++] << " ";
        sem_post(sem);

    }


    sem_close(sem);
    sem_unlink(semaphore);
        

    return 0;
}