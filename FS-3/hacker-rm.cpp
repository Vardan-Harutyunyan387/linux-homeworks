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
    

    if(argc < 2)
    {
        std::cerr << "Please provide file path"<<std::endl;
        exit(1);
    }
    char* file = argv[1];


    int fd = open(file, O_RDWR);//Open file
    if(fd < 0)
    {
        std::cerr << strerror(errno)<<std::endl; 
        exit(errno);  
    }
    
    char buf[BUFFER_SIZE];
    for(int i = 0; i < BUFFER_SIZE; i++)
        buf[i] = '\0';

    
    struct stat file_stat;
    if(stat(file, &file_stat) < 0)//Get file info
    {
        std::cerr << strerror(errno)<<std::endl; 
        exit(errno);   
    }
    int size = file_stat.st_size;


    ssize_t cursor = 0;
    ssize_t written_bytes;
    while(cursor < size)//No need to use lseek opened file without O_APPEND so we will start to write from the start
    {
        written_bytes = write(fd, buf, BUFFER_SIZE);
        if(written_bytes < 0)
        {
            std::cerr << strerror(errno)<<std::endl; 
            exit(errno);  
        }
        cursor += written_bytes;
    }

    int unlink_result = unlink(file);//Delete file
    if(unlink_result < 1)
    {
        std::cerr << strerror(errno)<<std::endl; 
        exit(errno);      
    }

    int close_result = close(fd);//Close file descriptor
    if (close_result < 0)
    {
        std::cerr << strerror(errno)<<std::endl;
    }
    


    return 0;
}