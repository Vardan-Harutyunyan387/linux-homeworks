#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char** argv)
{
    std::string first = "first line\n";
    std::string second = "second line\0";
    

    if(argc < 2)//check if path was given
    {
        std::cerr << "Please provide file path"<<std::endl;
        exit(1);
    }
    char* file = argv[1];


    int fd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);//Open file
    if(fd < 0)
    {
        std::cerr << strerror(errno)<<std::endl; 
        exit(errno);  
    }


    int copy_fd;
    int dup_result = dup2(fd, copy_fd);//Copy file descriptor
    if(dup_result < 0)
    { 
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int write_result;
    write_result = write(fd, first.c_str(), first.size());//write string using first file descriptor
    if(write_result < 0)
    {
        std::cerr << strerror(errno)<<std::endl; 
        exit(errno);  
    }

    write_result = write(copy_fd, second.c_str(), second.size());//write string using second file descriptor
    if(write_result < 0)
    {
        std::cerr << strerror(errno)<<std::endl; 
        exit(errno);  
    }
 

    int close_result = close(fd);//Close fd file descriptor
    if (close_result < 0)
    {
        std::cerr << strerror(errno)<<std::endl;
    }

    close_result = close(copy_fd);//Close copy_fd file descriptor
    if (close_result < 0)
    {
        std::cerr << strerror(errno)<<std::endl;
    }
    


    return 0;
}