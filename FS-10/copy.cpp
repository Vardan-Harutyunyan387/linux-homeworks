#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 100

int main(int argc, char** argv)
{
    
    //check if arguments were provided
    if(argc < 3)
    {
        std::cerr << "Please provide file path"<<std::endl;
        exit(1);
    }

    char* file = argv[1];

    //open source file
    int fd = open(file, O_RDONLY);
    if(fd < 0)
    {
        std::cerr << strerror(errno)<<std::endl; 
        exit(errno);  
    }

    char* file_2 = argv[2];

    //open destination file
    int fd_2 = open(file_2, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(fd_2 < 0)
    {
        std::cerr << strerror(errno)<<std::endl; 
        exit(errno);  
    }

    char buf[BUFFER_SIZE + 1];
    int hole_length = 0;
    int data_length = 0;
    int current_pos = 0;

    //Get file info
    struct stat file_stat;
    if(stat(file, &file_stat) < 0)
    {
        std::cerr << strerror(errno)<<std::endl; 
        exit(errno);   
    }
    int size_of_file = file_stat.st_size;
    //std::cout << "size of file " << size_of_file << std::endl;
    

    while(current_pos < size_of_file)
    {
        //find distance to closest data
        ssize_t data_dist = lseek(fd, 0, SEEK_DATA);
        if (data_dist < 0) {
            std::cerr << strerror(errno)<< std::endl;
            close(errno);
        }
        hole_length += data_dist;
        //std::cout << "data dist " << data_dist << std::endl;


        if(0 < data_dist)
        {
            //std::cout << "in if" << std::endl;

            //create hole in destination
            int created_hole_length = lseek(fd_2, data_dist, SEEK_END);
            if (created_hole_length < 0) {
                std::cerr << strerror(errno)<< std::endl;
                close(errno);
            }
            current_pos += created_hole_length;

        }


        int read_length;
        while(true)
        {
            //read data from source
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

            //delete \0 from the end
            for(int i = read_bytes - 1; i >= 0; --i)
            {
                if(buf[i] == '\0')
                {
                    read_bytes--;
                }
            }

            //add 1 \0 to the end
            buf[read_bytes] = '\0';
            
            current_pos += read_bytes;
            data_length += read_bytes - 1;
            
            //write to destination
            ssize_t written_bytes = write(fd_2, buf, read_bytes);
            if(written_bytes < 0)
            {
                std::cerr << strerror(errno)<<std::endl; 
                exit(errno);       
            }  

            //check if there is still data
            ssize_t hole_dist = lseek(fd, 0, SEEK_HOLE);
            if (data_dist < 0) {
                std::cerr << strerror(errno)<< std::endl;
                close(errno);
            }
            if(hole_dist == 0)
            {
                break;
            }
            //std::cout << "hole dist " << hole_dist << std::endl; 
        }
    }

    //Close file descriptor   
    int close_result = close(fd);
    if (close_result < 0)
    {
        std::cerr << strerror(errno)<<std::endl;
    }

    //Close file descriptor
    close_result = close(fd_2);
    if (close_result < 0)
    {
        std::cerr << strerror(errno)<<std::endl;
    }
    

    std::cout << "data length = " << data_length << " hole length = "<< hole_length << std::endl;

    

    return 0;
}