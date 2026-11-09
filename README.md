# PSI – Microcontroladores 2: Threads e Recursos Compartilhados

Aluno: Artur Serejo Dantas – Nº USP 15441730 – Turma B2-09
Placa: FRDM-KL25Z – Zephyr RTOS

| Pasta | Atividade |
|---|---|
| `padaria/` | Produtor e consumidor **sem** sincronização (padeiro x cliente, `saldo_vitrine`) |
| `filosofos/` | Jantar dos filósofos com um `k_mutex` por garfo e ordem fixa de aquisição |

O relatório está em `Atividades_Threads_Artur_Serejo_Dantas.pdf`.

## Como compilar e gravar

```
west build -p always -b frdm_kl25z padaria
west flash
```

Troque `padaria` por `filosofos` para o outro projeto.
A saída aparece no terminal serial (115200 baud).

Para as Partes 2 e 3 da padaria, altere os `#define` de tempo e prioridade no topo de `padaria/src/main.c`.
