#ifndef SHARED_ARRAY_H
#define SHARED_ARRAY_H

#include <iostream>
#include <string>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <chrono>
#include <thread>


#define KB_4  4096

class Shared_array
{
public:
    Shared_array(std::string name, int size);
    char& operator[](int index);
    ~Shared_array();

private:
    const char* name_ptr;
    int fd;
    void* mmap_ptr;
    std::string name;
    int size;
    char* mmap_ptr_char;
};

#endif // SHARED_ARRAY_H
