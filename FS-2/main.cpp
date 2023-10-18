#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int main(int argc, char** argv)
{
    

    if(argc < 3)
    {
        std::cerr << "Please provide file path"<<std::endl;
        exit(1);
    }

    char* file = argv[1];


    int fd = open(file, O_RDONLY);
    if(fd < 0)
    {
        std::cerr << strerror(errno)<<std::endl; 
        exit(errno);  
    }
    char buf[BUFFER_SIZE + 1];

    char* file_2 = argv[2];


    int fd_2 = open(file_2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd_2 < 0)
    {
        std::cerr << strerror(errno)<<std::endl; 
        exit(errno);  
    }


    

    
    while(true)
    {
        ssize_t read_bytes = read(fd, buf, BUFFER_SIZE);

        if(read_bytes < 0)
        {
            std::cerr << strerror(errno)<<std::endl; 
            exit(errno);       
        }
        if(read_bytes == 0)
        {
            break;
        }

        buf[read_bytes] = '\0';
        
        ssize_t written_bytes = write(fd_2, buf, read_bytes);
        if(written_bytes < 0)
        {
            std::cerr << strerror(errno)<<std::endl; 
            exit(errno);       
        }

    }

    int close_result = close(fd);
    if (close_result < 0)
    {
        std::cerr << strerror(errno)<<std::endl;
    }
    


    return 0;
}