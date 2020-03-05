# GUIA 1

## 2 - apropos time

mostra a lista de funções que inclui o nome "time"

## 3 - mn 2 gettimeofday

Synopsys
```c
#include <sys/time.h>
int gettimeofday(struc timeval * tv, struct timezone * tz);

int settimeofday(const struct timeval *tv, const struct timezone * tz);
```

struct timeval
```c
struct timeval
{
    time_t tv_sec; // seconds
    suseconds_t tv_usec; // microseconds
};
```
```c
struct timezone
{
    int tz_minueswest; // minutes west of greenwich
    int tz_dsttime; // type of DST correction
}
```

### return values

gettimeofday() and settimeofday() will return 0 if success or  -1 if failure in which case errno is set appropriately

## 4 - copiar  e executar

```
$ cp /home/mmadeira/Aulas/SPD-P1/teste_tempo.c .

$ gcc -Wall -std=gnu99 teste_tempo.c
```
Output: 
```
$ ./a.out
Elapsed time: Loop time = 0.000002
```
```
$ time ./a.out
Elapsed time: LOop time = 0.000002
real 0m0.002s
user 0m0.000s
sys  0m0.004s
```
* Real is the actual wallclock time it took to run
* Sys is the amount of time the system spent while executing your program (i.e. time spent by the kernel)
* User is the amount of time that was spend in user-mode executing it (i.e. time spent executing where you werent in the kernel)

found the answer [here](https://stackoverflow.com/questions/8299948/how-to-compute-run-time-for-a-c-program-in-ubuntu)


## 5.


