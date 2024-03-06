#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <cstring>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <cmath>

bool is_prime(int n) {
    if (n <= 1) {
        return false;
    }

    if (n == 2) {
        return true;
    }

    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

int find_mth_prime(int m) {
    if (m < 1) {
        return -1;
    }
    if(m == 1)
    {
        return 2;
    }

    int count = 1;
    int number = 3;

    while (count < m) {
        if (is_prime(number)) {
            ++count;
        }
        if (count < m) {
            number += 2;
        }
    }

    return number;
}


int main(){

    int send_child_fd[2];
    int pipe_result = pipe(send_child_fd);
    if(pipe_result < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int send_parent_fd[2];
    int pipe_result_2 = pipe(send_parent_fd);
    if(pipe_result_2 < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int pid = fork();
    
    if(pid < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    
    if(pid > 0){
        close(send_child_fd[0]); // Close unused read end
        close(send_parent_fd[1]); // Close unused write end

        int num;
        int m_th_prime;

        while(true){
            std::cout << "Enter the m ";
            std::cin >> num;

            int write_result = write(send_child_fd[1], &num, sizeof(num));
            if(write_result < 0){
                std::cerr << strerror(errno) << std::endl;
                exit(errno);
            }

            int read_result = read(send_parent_fd[0], &m_th_prime, sizeof(num));
            if(read_result < 0){
                std::cerr << strerror(errno) << std::endl;
                exit(errno);
            }

            std::cout << num << "-th prime number is "<< m_th_prime <<std::endl;

        }
    }

    if(pid == 0){
        close(send_parent_fd[0]); // Close unused read end
        close(send_child_fd[1]); // Close unused write end
    
        int num;

        while(true){
            int read_result = read(send_child_fd[0], &num, sizeof(num));
            if(read_result < 0){
                std::cerr << strerror(errno) << std::endl;
                exit(errno);
            }

            num = find_mth_prime(num);

            int write_result = write(send_parent_fd[1], &num, sizeof(num));
            if(write_result < 0){
                std::cerr << strerror(errno) << std::endl;
                exit(errno);
            }
        }
    }

    return 0;
}