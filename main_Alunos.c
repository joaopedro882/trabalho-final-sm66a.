#include "tm4c123gh6pm.h"

// Variáveis globais
volatile unsigned long contador = 0;
const unsigned long LEDS[] = {
                                                            0x00, // 0000 (0)
                                                            0x02, // 0010 (1) - PF1
                                                            0x04, // 0100 (2) - PF2
                                                            0x06, // 0110 (3) - PF1+PF2
                                                            0x08, // 1000 (4) - PF3
                                                            0x0A, // 1010 (5) - PF1+PF3
                                                            0x0C, // 1100 (6) - PF2+PF3
                                                            0x0E, // 1110 (7) - PF1+PF2+PF3
                                                            0x10, // 0001 (8) - PF4
                                                            0x12, // 0011 (9) - PF1+PF4
                                                            0x14, // 0101 (10) - PF2+PF4
                                                            0x16, // 0111 (11) - PF1+PF2+PF4
                                                            0x18, // 1001 (12) - PF3+PF4
                                                            0x1A, // 1011 (13) - PF1+PF3+PF4
                                                            0x1C, // 1101 (14) - PF2+PF3+PF4
                                                            0x1E  // 1111 (15) - PF1+PF2+PF3+PF4
};

void PortF_Init(void);
void EnableInterrupts(void);
void Delay_ms(unsigned long ms);

int main(void){
    PortF_Init();
    EnableInterrupts();

    while(1){
        GPIO_PORTF_DATA_R = LEDS[(contador % 16)];
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

    GPIO_PORTF_IS_R &= ~ 0x01; // GPIO Interrupt Sense 0 The edge on the corresponding pin is detected (edge-sensitive).
                                                    //1 The level on the corresponding pin is detected (level-sensitive).

    GPIO_PORTF_IBE_R &= ~0x01;// Interrupt Both Edges. 0  Interrupt generation is controlled by the GPIO Interrupt Event (GPIOIEV) register
                                                    // 1 Both edges on the corresponding pin trigger an interrupt.

    GPIO_PORTF_IEV_R &= ~ 0x01; // GPIO Interrupt Event . 0 A falling edge or a Low level on the corresponding pin triggers an interrupt.
                                                         // 1 A rising edge or a High level on the corresponding pin triggers an interrupt.
    GPIO_PORTF_ICR_R = 0x01;// Interrupt Clear .  1 The corresponding interrupt is cleared
    GPIO_PORTF_IM_R |= 0x01; //  GPIO Interrupt Mask. 0 The interrupt from the corresponding pin is masked.
                             //                       1 The interrupt from the corresponding pin is sent to the interrupt controller.

    NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF00FFFF) | 0x00A00000;
    NVIC_EN0_R = 0x40000000;
}

void GPIOPortF_Handler(void){
    //GPIO_PORTF_IM_R &= ~0x01;  // Desabilita interrupção temporariamente
    GPIO_PORTF_ICR_R = 0x01;   // Limpa o flag

    if (GPIO_PORTF_DATA_R & 0x01){
    contador++;
    }
    // Processamento
    Delay_ms(600);


    //GPIO_PORTF_IM_R |= 0x01;   // Reabilita interrupção
}

void Delay_ms(unsigned long ms){
    volatile unsigned long i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 1600; j++); // Aprox 1ms @16MHz
}
