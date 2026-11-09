/*
 * Jantar dos Filosofos - Zephyr RTOS - FRDM-KL25Z
 * Solucao: cada filosofo pega SEMPRE primeiro o garfo de menor numero.
 * Isso quebra a espera circular e impede o deadlock.
 */
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define N_FILOSOFOS 5
#define STACK_SIZE  1024
#define PRIORIDADE  5          /* todos com a mesma prioridade */

static struct k_mutex garfos[N_FILOSOFOS];
static struct k_thread threads[N_FILOSOFOS];
K_THREAD_STACK_ARRAY_DEFINE(pilhas, N_FILOSOFOS, STACK_SIZE);

static void filosofo(void *p1, void *p2, void *p3)
{
	int id = (int)(intptr_t)p1;
	int esq = id;
	int dir = (id + 1) % N_FILOSOFOS;

	/* ordem fixa: menor numero primeiro */
	int primeiro = (esq < dir) ? esq : dir;
	int segundo  = (esq < dir) ? dir : esq;

	int refeicoes = 0;

	while (1) {
		printk("Filosofo %d pensando\n", id);
		k_msleep(300 + 170 * id);        /* tempo diferente para cada um */

		k_mutex_lock(&garfos[primeiro], K_FOREVER);
		k_mutex_lock(&garfos[segundo], K_FOREVER);

		refeicoes++;
		printk("Filosofo %d COMENDO (garfos %d e %d) - refeicao #%d\n",
		       id, primeiro, segundo, refeicoes);
		k_msleep(500);

		k_mutex_unlock(&garfos[segundo]);
		k_mutex_unlock(&garfos[primeiro]);
	}
}

int main(void)
{
	for (int i = 0; i < N_FILOSOFOS; i++) {
		k_mutex_init(&garfos[i]);
	}

	for (int i = 0; i < N_FILOSOFOS; i++) {
		k_thread_create(&threads[i], pilhas[i], STACK_SIZE,
				filosofo, (void *)(intptr_t)i, NULL, NULL,
				PRIORIDADE, 0, K_NO_WAIT);
	}
	return 0;
}
