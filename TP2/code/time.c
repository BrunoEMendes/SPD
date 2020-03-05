#include <time.h>
#include <sys/time.h>
#include "time.h"

// função de tempo implementada pela Professora Margarida Moura em SPD
// https://tutoria.ualg.pt/2019/pluginfile.php/132032/mod_resource/content/0/Guia1-Exerc%C3%ADcios%20Iniciais.pdf
double get_function_run_time()
{
    struct timeval time;
    gettimeofday(&time,NULL);
    return ( (double)(time.tv_sec*1000000+time.tv_usec)/1000000 );
}
