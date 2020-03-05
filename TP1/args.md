###  args de execução
* **h** &rarr; comando de ajuda
* **q** &rarr; sort do array com [quick sort](https://en.wikipedia.org/wiki/Quicksort)
* **i** &rarr; sort do _array_ com [insertion sort](https://pt.wikipedia.org/wiki/Insertion_sort)
* **m** &rarr; sort do _array_com [merge sort](https://pt.wikipedia.org/wiki/Merge_sort)
* **p** &rarr; da _print_ dos factoriais do número inserido
* **u** &rarr; compila os testes unitários
* **t** &rarr; da print do tempo de execução da função
* **s**: &rarr; compila a versão sequencial com argumentos
    * **1:** compila a versão sequencial normal
    * **2:** compila a versão sequencial mas evita repetição de funções ex.: se divibilidade por 3 falhar então não vale apena fazer divisibilidade por 9
* **d:** &rarr; compila a versão com threads com argumentos
    * **1:** compila a versão com 2 threads em que 1 thread executa as funções pre-definidas (2, 3, 4, 5, 6, 9, 10) e a outra os genéricos
    * **2:** compila a versão com 3 threads em 1 thread executa as funções pre-definidas (2, 3, 4, 5, 6, 9, 10), 1 thread corre as divisões pares e outras as impares
    * **3:** compila a versão com N threads em que o input é dividido em N _threads_ e em que cada _thread_ vai procurar os factores de do seu número de thread multiplicado pelo número de _input_ divido pelo número total de _threads_
    * **4:** compila a versão semelhante à três só que os resultados são colocados linearmente no array devido aos mutexes
* **l:** &rarr; compila as funções 100 vezes
    * **1:** compila a função sequencial sem otimização
    * **2:** compila a função sequencial com otimização
    * **3:** compila a função com 2 threads
    * **4:** compila a função com 3 threads
    * **5:** compila a função com N threads (o pré-definido são 4)
    * **6:** compila a função com N threads e mutexes (o pré-definido são 4)
