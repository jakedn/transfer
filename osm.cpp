#include "osm.h"
#include <sys/time.h>

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define DEFAULT_NUMBER_OF_ITERATIONS 12345678
#define FROM_SECOND_TO_NANO 1000000000
#define FROM_MILI_TO_NANO 1000
#define UNROLLING_FACTOR 3

double get_time(const timeval tv_start,const timeval tv_end, unsigned int iterations)
{
    double answer = (tv_end.tv_sec - tv_start.tv_sec) * FROM_SECOND_TO_NANO;
    answer += (tv_end.tv_usec - tv_start.tv_usec)*FROM_MILI_TO_NANO;
    return answer/iterations;
}

void empty_func1()
{
}
void empty_func2()
{
}
void empty_func3()
{
}



int main()
{
/*
    timeval tv_start;
    timeval tv_end;
    gettimeofday (&tv_start, NULL);
cout<<tv_start.tv_sec<<" "<<tv_start.tv_usec<<endl;   
    int x = 1;
    for(int i = 0; i < NUMBER_OF_ITERATIONS; i++)
    {
        x++;
    }
    gettimeofday (&tv_end, NULL);
cout<<tv_end.tv_sec<<" "<<tv_end.tv_usec<<endl; 
    
    long long diff = get_diff(tv_start, tv_end);
cout<<diff<<endl;
*/

osm_init();
cout<<osm_operation_time(0)<<endl;
osm_init();
cout<<osm_function_time(0)<<endl;
osm_init();
cout<<osm_syscall_time(0)<<endl;
    return 0;
}


int osm_init()
{
/*
    int* x = (int* )malloc(sizeof(int));
    free(x);
*/
    return 0;
}
int osm_finalizer()
{
    return 0;
}
double osm_operation_time(unsigned int iterations)
{   
    iterations = (iterations == 0 ? DEFAULT_NUMBER_OF_ITERATIONS : iterations);
    int x;
    int y;
    int z;
    timeval tv_start;
    timeval tv_end;
    gettimeofday (&tv_start, NULL);
    for(unsigned int i = 0; i < iterations; i++)
    {
        ++x;
        ++y;
        ++z;
    }
    gettimeofday (&tv_end, NULL);
    return get_time(tv_start, tv_end, iterations * UNROLLING_FACTOR);
}


double osm_function_time(unsigned int iterations)
{   
    iterations = (iterations == 0 ? DEFAULT_NUMBER_OF_ITERATIONS : iterations);
    timeval tv_start;
    timeval tv_end;
    gettimeofday (&tv_start, NULL);
    for(unsigned int i = 0; i < iterations; i++)
    {
        empty_func1();
        empty_func2();
        empty_func3();
    }
    gettimeofday (&tv_end, NULL);
    return get_time(tv_start, tv_end, iterations * UNROLLING_FACTOR);
}

double osm_syscall_time(unsigned int iterations)
{
    iterations = (iterations == 0 ? DEFAULT_NUMBER_OF_ITERATIONS : iterations);
    timeval tv_start;
    timeval tv_end;
    gettimeofday (&tv_start, NULL);
    for(unsigned int i = 0; i < iterations; i++)
    {
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
    }
    gettimeofday (&tv_end, NULL);
    return get_time(tv_start, tv_end, iterations * UNROLLING_FACTOR);
}



