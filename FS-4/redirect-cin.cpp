#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void initialize(int argc, char** argv)
{
    if(argc < 2)//Check if the path was given
    {
        std::cerr << "Please provide file path"<<std::endl;
        exit(1);
    }
    char* file = argv[1];

    int close_result = close(0);//Close input file descriptor 
    if (close_result < 0)
    {
        std::cerr << strerror(errno)<<std::endl;
    }

    int fd = open(file, O_RDWR);//Open file instead of input file descriptor
    if(fd < 0)
    {
        std::cerr << strerror(errno)<<std::endl; 
        exit(errno);  
    }


}

int main(int argc, char** argv)
{
  // initialize the program based on the requirements
  initialize(argc, argv);

  // read the string 
  std::string input;
  std::cin >> input;
  
  // logic to get the reversed string
  std::string reversed;
  
  // put your reversing logic here
  int size = input.size();
  int half_size = input.size() / 2;

  for(int i = 0; i < half_size; ++i)
  {
    char temp = input[i];
    input[i] = input[size - i - 1];
    input[size - i - 1] = temp;
  }

  // print to the console
  std::cout << input << std::endl;

  return 0;
}
