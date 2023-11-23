#include <iostream>
#include <chrono>
#include <random>
#include <cstdlib>
#include <pthread.h>
#include <string.h>


struct info
{
    long long sum;
    int* start;
    int* end;
};

void* thread_sum(void* scrt)
{
    // cast to info*
    info* args = (info*)scrt;

    //calculate partial sum
    long long partial_sum = 0;
    for(auto i = args->start; i < args->end; i++) 
    {
        partial_sum += *i;
    }

    args->sum = partial_sum;
    return nullptr;
}

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        std::cerr << "not enogth arguments" << std::endl;
        exit(0);
    }

    // turn string to int
    int n = std::atoi(argv[1]);
    int number_of_thread = std::atoi(argv[2]);

    long long sum = 0;
    int* arr = new int[n];

    // make array of random numbers
    for(int i = 0; i < n; i++)
    {
        arr[i] = rand();
        //arr[i] = 1;
    }

    // start the clock
    auto start_time = std::chrono::high_resolution_clock::now(); 

    for(int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    // Stop the clock
    auto end_time = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << "operation duration without multithreading: " << duration.count() <<  " sum = " << sum <<std::endl;






    sum = 0;

    // array of structs
    info* args = new info[number_of_thread];

    // array of threads
    pthread_t* threads = new pthread_t[number_of_thread];

    // start the clock
    auto start_timet = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < number_of_thread; i++)
    {
        int jump = n / number_of_thread;
        
        // find from where to where 1 thread must calculate
        args[i].start = arr + (i * jump);
        args[i].end = (i == number_of_thread - 1)? arr + n: arr + ((i + 1) * jump);

        // create thread and execute function
        int thread_create_result = pthread_create(&threads[i], nullptr, thread_sum, &args[i]);
        if(thread_create_result != 0)
        {
            std::cerr << strerror(thread_create_result) << std::endl;
            exit(thread_create_result);
        }
    }

    for (int i = 0; i < number_of_thread; ++i) {
        // wait until all threads finish work
        int join_result = pthread_join(threads[i], nullptr);
        if(join_result != 0)
        {
            std::cerr << strerror(join_result) << std::endl;
            exit(join_result);
        }
    }

    // sum of all partial sums
    for(int i = 0; i < number_of_thread; i++)
    {
        sum += args[i].sum;
    }



    // Stop the clock
    auto end_timet = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    auto durationt = std::chrono::duration_cast<std::chrono::microseconds>(end_timet - start_timet);

    std::cout << "operation duration with multithreading: " << durationt.count() <<  " sum = " << sum <<std::endl;
    
    //deallocate memory
    delete [] args;
    delete [] arr;
    delete [] threads;
    
    return 0;
}