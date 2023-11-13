#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <chrono>
#include <sys/wait.h>
#include <sstream>
#include <vector>
#include <sys/stat.h>
#include <fcntl.h>

#define PATH_MAX 150



int main()
{
    // PATH_MAX is a constant representing the maximum path length
    char PATH[PATH_MAX]; 



    while(true)
    {
        std::string userInput;

        std::cout << "Enter a command: ";

        // Input whole line
        std::getline(std::cin, userInput);

        // Use std::istringstream to tokenize the input
        std::istringstream iss(userInput);
        
        // Store tokens in a vector of char*
        std::vector<std::string> tokens;
        std::string token;
        
        // Concatinate by ' '
        while (std::getline(iss, token, ' ')) {
            tokens.push_back(token);
        }

        // Create char* array to pass to system calls
        char* char_tokens[tokens.size() + 1];

        // Copy elements to array
        for(int i = 0; i < tokens.size(); i++)
        {
            char_tokens[i] = const_cast<char*>(tokens[i].c_str());
        }

        // Add null termination
        char_tokens[tokens.size()] = NULL;

        // pointer to array
        char** input = char_tokens;


        // Get current directory
        char* get_result = getcwd(PATH, sizeof(PATH));
        if(get_result == NULL)
        {
            std::cerr << strerror(errno);
            exit(errno);       
        }



        if(tokens[0] == "exit")
        {
            break;
        }
        else{
            // Clone process
            pid_t child = fork();

            // Check for errors
            if(child < 0){
                std::cerr << strerror(errno);
                exit(errno);
            }
            
            if(child == 0){
                // Parent process
                int exec_error;

                if(tokens[0] == "silent")
                {
                    // Get log number add .log
                    std::string logFileName = std::to_string(getpid()) + ".log";

                    // Open the log file for writing
                    int open_result = open(logFileName.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    
                    if(open_result < 0)
                    {
                        std::cerr << strerror(errno);
                        exit(errno);
                    }     

                    // close cerr cout and redirect
                    int dup_result = dup2(open_result, STDOUT_FILENO);
                    if(dup_result < 0)
                    {
                        std::cerr << strerror(errno);
                        exit(errno);
                    }  

                    dup_result = (open_result, STDERR_FILENO);
                    if(dup_result < 0)
                    {
                        std::cerr << strerror(errno);
                        exit(errno);
                    }  

                    // Close the original fil
                    auto close_result = close(open_result);
                    if(close_result < 0)
                    {
                        std::cerr << strerror(errno);
                        exit(errno);
                    }   

                    //Change input to start not from silent
                    input = input + 1;
                    //std::cout << input[0] << std::endl;             
                }


                // Execute given command
                if(tokens[0][0] == '/')
                {
                    exec_error = execv(input[0], input);
                }
                else{
                    exec_error = execvp(input[0], input);
                }
                
                // check for errors
                if(exec_error < 0)
                {
                    std::cerr << strerror(errno);
                    exit(errno);
                }
        
            }

        }
    }



    return 0;
}