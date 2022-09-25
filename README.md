# Sistemas distribuidos & Programação paralela:

> ## Semana 1:

- ### Os motivos de se fazer?
    - Menos tempo;
    - Mais complexidade;
    - Aproveitamento total de recursos computacionais;
    - Ultrapassar limites de um único hardware;

<br>

- ### Desafios:
    - Sincronia no uso e comunicação dos dados;
    - Divisão adequada entre os recursos computacionais disponivéis de:
        - processos; 
        - códigos; 
        - dados; 
    - Complexidade de implementação;
    - Conhecimento do hardware;
    - Impedimentos de paralelização;
    - Depuração complexa;


<br>

- ### SpeedUp:
    - Porcentagem de melhora em comparação do sequencial para o paralelo
    - Modos de se calcular:
        - Comum:<br> $SpeedUp = \frac{\Delta T _{Sequencial}}{\Delta T _{Paralelo}}$ <br>

        - Pela lei de Amdahl: <br> $SpeedUp = \frac{ 1 }{\frac{ \Delta T _{Paralelo}}{nroProcesos} + \Delta T _{Sequencial}}$ <br>

<br>


> ## Semana 2:

 - ### Modelos de computação paralela:
    - **Modelos de máquina**: Descreve as caracteristicas das máquinas
    - **Modelos de programação**: Permite compreender aspectos ligados a implementação e desempenho do codigo
    - **Modelos de aplicação**: representa o paralelismo de um algoritmo

<br>

 - ### Modelos de máquinas da taxonomia de Flynn: 
 <center>

| **_Instruction \ Data_** 	| \| 	| _SD <br> (Single Data)_  	| \| 	| _MD <br> (Multiple Data)_ 	|
|:---:	|:---:	|:---:	|:---:	|:---:	|
| **_SI <br> (Single Instruction)_** 	| \| 	| SISD <br> Máquina von Neumann 	| \| 	| SIMD <br> Máquinas Array 	|
| **_MI <br> (Multiple Instruction)_** 	| \| 	| MISD <br> Sem representante 	| \| 	| MIMD <br> Multiprocessadores <br> e Multicomputadores 	|

 </center>

<br>

- ### Vantagens da modelagem paralela:
    - Permite compreender os diferentes impactos da aplicação na implementação de um codigo paralelo
        - Qtd de calculos envolvidos
        - Volume de dados manipulados
        - Depedência de informações entre as atividades em execução

<br>

- ###  Distribuição do trabalho (Granulosidade)
    - Relação entre o tamanho de cada tarefa e o tamanho total do programa (razão entre computação e comunicação):
        - Alta(Grossa)
        - Média
        - Baixa(Fina)
    - Indica o tipo de arquitetura mais adequada:
        - Clusters(grossa)
        - SMP(média)
        - Procs vetoriais(fina)

<br>

- ### Paralelismo de dados VS Paralelismo de tarefas
    - Paralelismo de dados:
        - Execução de uma mesma tarefa sobre diferentes partes de um conjunto de dados.
        - Os dados determinam a concorrência da aplicação e a forma como o cálculo deve ser distribuído na arquitetura
    - Paralelismo de tarefa:
        - Execução paralela de diferentes atividades sobre conjuntos distintos de dados
        - Identificação das atividades concorrentes da aplicação e como essas atividades são distribuídas pelos recursos disponíveis

<br>


- ### Mémoria compartilhada VS Troca de mensagens
    - Identifica como ocorre o compartilhamento de infoemações durante a execução;
    - Mémoria compartilhada
        - As tarefas em execução compartilham um mesmo espaço de memória
        - Comunicação através do acesso a uma área compartilhada
    - Troca de mensagens
        - Não existe um espaço de endereçamento comum
        - Comunicação através de troca de mensagens usando a rede de interconexão.

<br>


- ## Modelos de Aplicação
    - WorkPool
        - Tarefas disponibilizadas em uma estrutura de dados global (memória compartilhada)
        - Desafios: Sincronização
        - Vantagem: Balanceamento de carga
    - Mestre / Escravo (Task farming)
        - Mestre dividi tarefas entre processos escravos 
        - Desafio: Escalonamento centralizado (gargalo)
        - Vantagem: Maior tolerância a falhas
    - Pipeline
        - Fluxo contínuo de dados
        - Sobreposição de comunicação e computação
    - Divisão e conquista
        - Processo Pai e Filhos
        - Pai dividi o trabalho e repassa uma parte para os Filhos
  - Desafio: dificuldade de balanceamento de carga das tarefas

<br>


- ## Fases paralelas
  - Etapas de computação e Sincronização
  - Desafios: 
    - Problema de balanceamento de carga
      - Processos que acabam antes
    - Overhead de comunicação
      - comunicação é realizada ao mesmo tempo

<br>


> ## Semana 04:

- ## Troca de mensagens
    - comunicação síncrona (bloqueante)
        - send bloqueia emissor até receptor executar receive
        - receive bloqueia receptor até emissor enviar mensagem
    - comunicação assíncrona (não bloqueante)
        - send não bloqueia emissor
        - receive pode ser realizado durante execução

- ## Comunicação em grupo
    - Broadcast: envio de msg a todos os processos do grupo
    - Gather/Scatter:
        - Gather:  recebimento de partes de mensagens de diversos processos de um grupo por um processo
        (coletar)
        - Scatter: envio de partes de uma mensagem de um processo para diferentes processos de um grupo
        (distribuir)
