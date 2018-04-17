#define ERR -1
#define UNROLLING_FACTOR 10
#define SEC_TO_NANO 1000000000
#define MICRO_TO_NANO 1000

int osm_init()
{
    namePtr = new char[256];

    if (!namePtr)
    {
        return ERR;
    }

    return 0;
}


int osm_finalizer()
{
    delete[] namePtr;
    return 0;
}

double osm_operation_time(unsigned int iterations)
{
    struct timeval start, end;
    unsigned int iter = (iterations <= 0) ? 1000 : iterations;
    unsigned int round_iter = (unsigned int)std::ceil(iter / UNROLLING_FACTOR);
    int a = 0, b = 1, c = 2, d = 3, e = 4;
    int start_time = gettimeofday(&start, NULL);
    for (unsigned int i = 0; i < round_iter; i++)
    {
        a = b + 1;
        b = c + 1;
        c = d + 1;
        d = e + 1;
        e = a + 1;
        a = b + 1;
        b = c + 1;
        c = d + 1;
        d = e + 1;
        e = a + 1;
    }

    int end_time = gettimeofday(&end, NULL);
    if (start_time == ERR || end_time == ERR)
    {
        return ERR;
    }

    double time = ((end.tv_sec - start.tv_sec) * SEC_TO_NANO) +
                  (end.tv_usec - start.tv_usec) * MICRO_TO_NANO;

    return time / (ceil(iter/ UNROLLING_FACTOR) * UNROLLING_FACTOR);
}

void emptyFunction()
{
}

double osm_function_time(unsigned int iterations)
{
    struct timeval start, end;
    unsigned int iter = (iterations <= 0) ? 1000 : iterations;
    unsigned int round_iter = (unsigned int)std::ceil(iter / UNROLLING_FACTOR);
    int start_time = gettimeofday(&start, NULL);
    for (unsigned int i = 0; i < round_iter; i++)
    {
        emptyFunction();
        emptyFunction();
        emptyFunction();
        emptyFunction();
        emptyFunction();
        emptyFunction();
        emptyFunction();
        emptyFunction();
        emptyFunction();
        emptyFunction();
    }

    int end_time = gettimeofday(&end, NULL);
    if (start_time == ERR || end_time == ERR)
    {
        return ERR;
    }

    double time = ((end.tv_sec - start.tv_sec) * SEC_TO_NANO) +
                  (end.tv_usec - start.tv_usec) * MICRO_TO_NANO;

    return time / (ceil(iter/ UNROLLING_FACTOR) * UNROLLING_FACTOR);
}

double osm_syscall_time(unsigned int iterations)
{
    struct timeval start, end;
    unsigned int iter = (iterations <= 0) ? 1000 : iterations;
    unsigned int round_iter = (unsigned int)std::ceil(iter / UNROLLING_FACTOR);
    int start_time = gettimeofday(&start, NULL);
    for (unsigned int i = 0; i < round_iter; i++)
    {
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
    }

    int end_time = gettimeofday(&end, NULL);
    if (start_time == ERR || end_time == ERR)
    {
        return ERR;
    }

    double time = ((end.tv_sec - start.tv_sec) * SEC_TO_NANO) +
                  (end.tv_usec - start.tv_usec) * MICRO_TO_NANO;

    return time / (ceil(iter/ UNROLLING_FACTOR) * UNROLLING_FACTOR);
}
