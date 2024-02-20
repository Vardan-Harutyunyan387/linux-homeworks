#include <semaphore.h>
#include "shared_array.h"

const char *semaphore = "/aaaaa";

int main()
{
    int size = 12;
    Shared_array arr_1("text.txt", size);
    arr_1[4] = 'z';
    std::cout << arr_1[4] << std::endl;

    sem_t *sem = sem_open(semaphore, O_CREAT | O_EXCL, 0644, 1);
    if (sem == SEM_FAILED) {
        if(errno == EEXIST)
        {
            int sem_un_res = sem_unlink(semaphore);
            if(sem_un_res < 0)
            {
                std::cerr << strerror(errno) << std::endl;
                exit(errno);
            }

            sem = sem_open(semaphore, O_CREAT | O_EXCL, 0644, 1);
        }
        else{
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }
    }


    int i = 0;
    int j = 41;
    while(true)
    {
        if(i == size - 1)
        {
            i = 0;
        }
        if(j == 91)
        {
            j = 41;
        }
        sem_wait(sem);
        std::cout << "writing ";
        arr_1[i++] = (char)j++;
        sem_post(sem);
        std::this_thread::sleep_for(std::chrono::microseconds(50000));
    }

    return 0;
}