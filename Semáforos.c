
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
sem_t *semaforo;
void *contar(void *arg)
{
    int hilo = *(int *)arg;
    for (int i = 1; i <= 10000; i++)
    {
        if (i == 4000)
        {
            sem_wait(semaforo);
        }
        printf("Hilo %d: %d\n", hilo, i);
        if (i == 6000)
        {
            sem_post(semaforo);
        }
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t hilo1, hilo2;
    int num1 = 1;
    int num2 = 2;
    semaforo = sem_open("/mi_semaforo", O_CREAT, 0644, 1);
    if (semaforo == SEM_FAILED)
    {
        perror("Error al crear semaforo");
        return 1;
    }
    pthread_create(&hilo1, NULL, contar, &num1);
    pthread_create(&hilo2, NULL, contar, &num2);
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    sem_close(semaforo);
    sem_unlink("/mi_semaforo");
    return 0;
}
