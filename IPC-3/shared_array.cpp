#include "shared_array.h"
#include <cerrno>
#include <cstdlib>

Shared_array::Shared_array(std::string name, int size)
{
    this->name = name;
    this->size = size;
    std::string str_size = std::to_string(size);
    this->name = '/' + this->name + '_' + str_size;
    name_ptr = this->name.c_str();

    fd = shm_open(name_ptr, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if(fd < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    int ftrunc = ftruncate(fd, KB_4);

    int final_size = size / KB_4;
    if(size % KB_4 != 0)
    {
        final_size += 1;
    }
    final_size *= KB_4;

    mmap_ptr = mmap(NULL, final_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(MAP_FAILED == mmap_ptr)
    {
        std::cerr << strerror(errno) << std::endl;
        std::exit(errno);   
    }
    mmap_ptr_char = static_cast<char*>(mmap_ptr);
}

char& Shared_array::operator[](int index)
{
    return mmap_ptr_char[index];
}

Shared_array::~Shared_array()
{
    munmap(mmap_ptr, KB_4);
    close(fd);
    shm_unlink(name_ptr);
}