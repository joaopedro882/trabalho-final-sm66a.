# trabalho-final-sm66a.

## 📝 Descrição Técnica

Este repositório contém o desenvolvimento de um sistema embarcado para contar eventos detectados por um sensor de luz (LDR) e exibir o valor em forma binária utilizando LEDs.
O projeto foi concebido como parte dos requisitos avaliativos da disciplina SM66A - Sistemas Microcontrolados.

O sistema é implementado em um microcontrolador TM4C123, que recebe um sinal digital proveniente de um comparador analógico conectado a um LDR. Cada vez que ocorre uma variação de luz suficiente para gerar uma borda de subida no comparador, o microcontrolador incrementa um contador. Este valor é então exibido em 4 LEDs conectados às saídas digitais PF1 a PF4, representando o número de ativações do sensor em formato binário.

## ✨ Funcionalidades Implementadas (mínimo de 1)

- Contador de eventos via sensor LDR: O sistema monitora a saída de um comparador conectado a um LDR. Cada vez que a luz diminui (ou a resistência do LDR aumenta) gerando uma borda de subida no comparador, o microcontrolador incrementa um contador interno.
- Exibição binária do contador em LEDs: O valor do contador é mostrado em tempo real através de 4 LEDs conectados aos pinos PF1..PF4 do TM4C123, formando um display binário visual.
- Interrupção externa por GPIO: O microcontrolador usa uma interrupção por borda de subida no pino PF0 para detectar rapidamente a mudança do sinal do comparador, garantindo resposta imediata e baixo uso de CPU.

## ✨ Periféricos Utilizados (mínimo de 4)

- GPIO (PORTF)
- Delay
- Clock
- Interrupção


## 🛠️ Hardware e Componentes (mínimo 1)

* Microcontrolador: TM4C123G
* Sensores: LDR.
* Atuadores: LEds(cores vermelha, azul, branco e verde).
* Comparador de tensão: LM 311
* Resistores
* Potenciômetro

## ⚙️ Procedimento de Montagem e Execução

*(Esta seção deve ser detalhada ao longo do desenvolvimento)*

1.  **Diagrama Elétrico:** O esquema de interconexão dos componentes está disponível em `docs/esquema.pdf`.

3.  **Configuração do Ambiente:**
   
    Utilizar o Code Composer Studio (CCS) configurado para o microcontrolador TM4C123GH6PM.
    
    Incluir a biblioteca tm4c123gh6pm.h no projeto
    
4.  **Compilação e Upload:**
  
    Abrir o projeto no CCS ou Keil.

    Compilar o firmware (Build).

    Conectar o kit Tiva C LaunchPad via cabo USB.

    Gravar o programa no microcontrolador (Debug)

    Executar (Run), observando o comportamento no terminal (LEDs) e no comparador.

5.  **Execução e Teste:**

    Alterar a luminosidade incidente no LDR para verificar se o comparador gera as bordas.

    Observar os LEDs indicando o valor do contador em binário, incrementando a cada detecção.
   
## 🚀 Cronograma e Evolução (Roadmap)

- [ ] Definição da arquitetura de software.
- [ ] Implementação do módulo de leitura de sensores.
- [ ] Implementação da lógica de controle.
- [ ] Validação e testes funcionais.
