#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <chrono>
#include <sys/wait.h>


void do_command(char** argv)
{
    // Start the clock
    auto start_time = std::chrono::high_resolution_clock::now(); 

    // Clone process
    pid_t child = fork();

    // Check for errors
    if(child < 0){
        std::cerr << strerror(errno);
        exit(errno);
    }
    
    if(child == 0){
        // Parent process

        // Execute given command
        auto exec_error = execvp(argv[0], argv);
        
        // check for errors
        if(exec_error < 0)
        {
            std::cerr << strerror(errno);
            exit(errno);
        }
        
    }
    else
    {
        // Parent process

        // Wait for the child process to finish
        wait(nullptr);

        // Stop the clock
        auto end_time = std::chrono::high_resolution_clock::now();

        // Calculate the duration
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

        // Output the duration
        std::cout << "Command completed with " << errno << " exit code and took " << duration.count() << " microseconds.";
    }
    


}

int main(int argc, char** argv)
{
    // argc - 1 arguments given + NULL
    char* argument[argc];
    for(int i = 0; i < argc - 1; i++)
    {
        argument[i] = argv[i + 1];
    }
    argument[argc - 1] = NULL;

    // Pointer to char* array
    char** argp = argument;

    // Call do_command
    do_command(argp);



    return 0;
}