#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    printf("Sequential region 1\n");
    
    // Task 2: Create n threads
    // Each thread outputs information about itself
    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        int num_procs = omp_get_num_procs();
        
        printf("I am %d thread from %d threads! Available processors: %d\n", 
               thread_num, total_threads, num_procs);
    }
    
    printf("\nSequential region 2\n");
    
    // Task 3: Setting the number of threads
    printf("\nSetting the number of threads (4):\n");
    omp_set_num_threads(4);
    
    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        
        printf("I am %d thread from %d threads!\n", thread_num, total_threads);
    }
    
    // Examples of private, shared modifiers
    printf("\nExample of using private and shared modifiers:\n");
    
    int shared_var = 10;
    
    #pragma omp parallel private(shared_var)
    {
        // shared_var is a private variable with undefined initial value
        shared_var = omp_get_thread_num();
        printf("Thread %d: private shared_var = %d\n", omp_get_thread_num(), shared_var);
    }
    
    printf("After parallel region: shared_var = %d\n", shared_var);
    
    int firstprivate_var = 20;
    
    #pragma omp parallel firstprivate(firstprivate_var)
    {
        // firstprivate_var is initialized with value from main thread
        firstprivate_var += omp_get_thread_num();
        printf("Thread %d: firstprivate_var = %d\n", omp_get_thread_num(), firstprivate_var);
    }
    
    printf("After parallel region: firstprivate_var = %d\n", firstprivate_var);
    
    int shared_explicit_var = 30;
    
    #pragma omp parallel shared(shared_explicit_var)
    {
        // shared_explicit_var is a shared variable
        #pragma omp critical
        {
            shared_explicit_var += omp_get_thread_num();
            printf("Thread %d: shared shared_explicit_var = %d\n", omp_get_thread_num(), shared_explicit_var);
        }
    }
    
    printf("After parallel region: shared_explicit_var = %d\n", shared_explicit_var);
    
    // Task 4: Creating several independent code sections
    printf("\nCreating several independent code sections:\n");
    
    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        
        #pragma omp sections
        {
            #pragma omp section
            {
                printf("First section, thread %d\n", thread_num);
            }
            
            #pragma omp section
            {
                printf("Second section, thread %d\n", thread_num);
            }
            
            #pragma omp section
            {
                printf("Third section, thread %d\n", thread_num);
            }
        }
        
        printf("After sections execution, thread %d\n", thread_num);
    }
    
    // Example of using the single directive
    printf("\nExample of using the single directive:\n");
    
    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        printf("Parallel region, thread %d\n", thread_num);
        
        #pragma omp single
        {
            printf("This code is executed by only one thread (%d)\n", thread_num);
        }
        
        printf("After single directive, thread %d\n", thread_num);
    }
    
    // Example of using the master directive
    printf("\nExample of using the master directive:\n");
    
    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        printf("Parallel region, thread %d\n", thread_num);
        
        #pragma omp master
        {
            printf("This code is executed only by the master thread (0)\n");
        }
        
        printf("After master directive, thread %d\n", thread_num);
    }
    
    return 0;
}