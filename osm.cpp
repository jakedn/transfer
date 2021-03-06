#include "osm.h"
#include <sys/time.h>

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define WARMUP 1000
#define DEFAULT_NUMBER_OF_ITERATIONS 1000
#define FROM_SECOND_TO_MICRO 1000000
#define FROM_MICRO_TO_NANO 1000
#define UNROLLING_FACTOR 5

double get_time(const timeval tv_start, const timeval tv_end, unsigned long long iterations)
{
    double answer = (tv_end.tv_sec - tv_start.tv_sec) * FROM_SECOND_TO_MICRO;
    answer += (tv_end.tv_usec - tv_start.tv_usec);
    return answer / iterations * FROM_MICRO_TO_NANO;
}

void empty_func1() {}
void empty_func2() {}
void empty_func3() {}



int main()
{
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

    int x = 0;
    int y = 0;
    for(unsigned int i = 0; i < WARMUP; i++)
    {
        ++x;
        ++y;
    }
    return 0;
}

int osm_finalizer()
{
    return 0;
}
double osm_operation_time(unsigned int iterations)
{   
    iterations = (iterations == 0 ? DEFAULT_NUMBER_OF_ITERATIONS : iterations);
    int x = 0;
    int y = 0;
    int z = 0;
    int w = 0;
    int r = 0;


    for(unsigned int i = 0; i < WARMUP; i++)
    {
        ++x;
        ++y;
    }
    timeval tv_start;
    timeval tv_end;
    gettimeofday (&tv_start, NULL);
    for(unsigned int i = 0; i < iterations; i++)
    {
        x = x + 1;
        y = y + 1;
        z = z + 1;
        w = w + 1;
        r = r + 1;
    }
    gettimeofday (&tv_end, NULL);
    return get_time(tv_start, tv_end, (unsigned long long)iterations * UNROLLING_FACTOR);
}


double osm_function_time(unsigned int iterations)
{   
    iterations = (iterations == 0 ? DEFAULT_NUMBER_OF_ITERATIONS : iterations);
    int x = 0;
    int y = 0;


    for(unsigned int i = 0; i < WARMUP; i++)
    {
        ++x;
        ++y;
    }

    timeval tv_start;
    timeval tv_end;
    gettimeofday (&tv_start, NULL);
    for(unsigned int i = 0; i < iterations; i++)
    {
        empty_func1();
        empty_func2();
        empty_func3();
        empty_func1();
        empty_func2();
    }
    gettimeofday (&tv_end, NULL);
    return get_time(tv_start, tv_end, (unsigned long long)iterations * UNROLLING_FACTOR);
}

double osm_syscall_time(unsigned int iterations)
{
    iterations = (iterations == 0 ? DEFAULT_NUMBER_OF_ITERATIONS : iterations);
    int x = 0;
    int y = 0;

    for(unsigned int i = 0; i < WARMUP; i++)
    {
        ++x;
        ++y;
    }
    timeval tv_start;
    timeval tv_end;
    gettimeofday (&tv_start, NULL);
    for(unsigned int i = 0; i < iterations; i++)
    {
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
    }
    gettimeofday (&tv_end, NULL);
    return get_time(tv_start, tv_end, (unsigned long long)iterations * UNROLLING_FACTOR);
}



