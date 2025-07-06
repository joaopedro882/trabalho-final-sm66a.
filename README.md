# trabalho-final-sm66a.

## 📝 Descrição Técnica

Este repositório contém o desenvolvimento de um sistema embarcado para contar eventos detectados por um sensor de luz (LDR) e exibir o valor em forma binária utilizando LEDs.
O projeto foi concebido como parte dos requisitos avaliativos da disciplina SM66A - Sistemas Microcontrolados.

O sistema é implementado em um microcontrolador TM4C123, que recebe um sinal digital proveniente de um comparador analógico conectado a um LDR. Cada vez que ocorre uma variação de luz suficiente para gerar uma borda de subida no comparador, o microcontrolador incrementa um contador. Este valor é então exibido em 4 LEDs conectados às saídas digitais PF1 a PF4, representando o número de ativações do sensor em formato binário.

## ✨ Funcionalidades Implementadas (mínimo de 1)

- Contador de eventos via sensor LDR: O sistema monitora a saída de um comparador conectado a um LDR. Cada vez que a luz diminui (ou a resistência do LDR aumenta) gerando uma borda de subida no comparador, o microcontrolador incrementa um contador interno.
- Exibição binária do contador em LEDs: O valor do contador é mostrado em tempo real através de 4 LEDs conectados aos pinos PF1 a PF4 do TM4C123, formando um display binário visual.
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

1.  **Diagrama Elétrico:** O esquema de interconexão dos componentes está disponível em `/imagem_2025-07-05_004309366.pdf`.

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

6.  **Código:**

    #include "tm4c123gh6pm.h"

// Variáveis globais
volatile unsigned long contador = 0;
const unsigned long LEDS[] = {

                                                            0x00, // 0000 (0)
                                                            0x02, // 0010 (1) - PF1
                                                            0x00,
                                                            0x04, // 0100 (2) - PF2
                                                            0x00,
                                                            0x06, // 0110 (3) - PF1+PF2
                                                            0x00,
                                                            0x08, // 1000 (4) - PF3
                                                            0x00,
                                                            0x0A, // 1010 (5) - PF1+PF3
                                                            0x00,
                                                            0x0C, // 1100 (6) - PF2+PF3
                                                            0x00,
                                                            0x0E, // 1110 (7) - PF1+PF2+PF3
                                                            0x00,
                                                            0x10, // 0001 (8) - PF4
                                                            0x00,
                                                            0x12, // 0011 (9) - PF1+PF4
                                                            0x00,
                                                            0x14, // 0101 (10) - PF2+PF4
                                                            0x00,
                                                            0x16, // 0111 (11) - PF1+PF2+PF4
                                                            0x00,
                                                            0x18, // 1001 (12) - PF3+PF4
                                                            0x00,
                                                            0x1A, // 1011 (13) - PF1+PF3+PF4
                                                            0x00,
                                                            0x1C, // 1101 (14) - PF2+PF3+PF4
                                                            0x00,
                                                            0x1E  // 1111 (15) - PF1+PF2+PF3+PF4
};

void PortF_Init(void);
void EnableInterrupts(void);
void Delay_ms(unsigned long ms);

int main(void){
    PortF_Init();
    EnableInterrupts();

    while(1){
        GPIO_PORTF_DATA_R = LEDS[contador % 32-1];
    }
}

void PortF_Init(void){
    SYSCTL_RCGC2_R |= 0x20;
    while((SYSCTL_PRGPIO_R & 0x20) == 0);

    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R = 0x1F;
    GPIO_PORTF_DIR_R = 0x1E;    // PF1-PF4 output, PF0 input
    GPIO_PORTF_DEN_R = 0x1F;
    GPIO_PORTF_PUR_R = 0x01;    // Pull-up em PF0

    // Configura interrupção borda de descida
    GPIO_PORTF_IS_R &= ~0x01;
    GPIO_PORTF_IBE_R &= ~0x01;
    GPIO_PORTF_IEV_R &= ~0x01;
    GPIO_PORTF_ICR_R = 0x01;
    GPIO_PORTF_IM_R |= 0x01;
    NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF00FFFF) | 0x00A00000;
    NVIC_EN0_R = 0x40000000;
}

void GPIOPortF_Handler(void){
    GPIO_PORTF_ICR_R = 0x01;
    GPIO_PORTF_IM_R &= ~0x01;    // Desabilita interrupção

    // Debounce robusto
    Delay_ms(200);

    if((GPIO_PORTF_DATA_R & 0x01) == 0){ // Confirma borda de descida
        contador++;
    }

    GPIO_PORTF_IM_R |= 0x01;     // Reabilita interrupção
}

void Delay_ms(unsigned long ms){
    volatile unsigned long i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 1600; j++); // Aprox 1ms @16MHz
}
   
## 🚀 Cronograma e Evolução (Roadmap)

- [x] Definição da arquitetura de software.
- [x] Implementação do módulo de leitura de sensores.
- [x] Implementação da lógica de controle.
- [x] Validação e testes funcionais.
