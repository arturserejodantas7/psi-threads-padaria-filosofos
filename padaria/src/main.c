/*
 * Padaria - Produtor e Consumidor SEM sincronizacao (Atividade 1)
 * Zephyr RTOS - FRDM-KL25Z
 *
 * Para as Partes 2 e 3, altere apenas os #define abaixo.
 */
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define TEMPO_PADEIRO_MS   1000   /* Parte 2: 500 ou 2000 */
#define TEMPO_CLIENTE_MS   1500   /* Parte 2: 2000 ou 500 */

#define PRIO_PADEIRO       5      /* Parte 3: menor numero = maior prioridade */
#define PRIO_CLIENTE       5

#define STACK_SIZE         1024
#define CAPACIDADE_VITRINE 10     /* so informativo: o codigo NAO respeita o limite */

/* Variavel compartilhada, sem nenhuma protecao */
volatile int saldo_vitrine = 0;

static void padeiro(void *a, void *b, void *c)
{
	int pao = 0;

	while (1) {
		k_msleep(TEMPO_PADEIRO_MS);
		pao++;
		saldo_vitrine++;              /* le, soma 1 e grava: nao e atomico */
		printk("PADEIRO: Pao #%d pronto (Saldo vitrine = %d)%s\n",
		       pao, saldo_vitrine,
		       saldo_vitrine > CAPACIDADE_VITRINE ? "  <-- VITRINE ESTOURADA" : "");
	}
}

static void cliente(void *a, void *b, void *c)
{
	int pao = 0;

	while (1) {
		k_msleep(TEMPO_CLIENTE_MS);
		pao++;
		saldo_vitrine--;              /* nao verifica se ha pao */
		printk("CLIENTE: Peguei pao #%d (Saldo vitrine = %d)%s\n",
		       pao, saldo_vitrine,
		       saldo_vitrine < 0 ? "  <-- SALDO NEGATIVO" : "");
	}
}

K_THREAD_DEFINE(tid_padeiro, STACK_SIZE, padeiro, NULL, NULL, NULL,
		PRIO_PADEIRO, 0, 0);
K_THREAD_DEFINE(tid_cliente, STACK_SIZE, cliente, NULL, NULL, NULL,
		PRIO_CLIENTE, 0, 0);
