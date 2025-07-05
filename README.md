# trabalho-final-sm66a.

## 📝 Descrição Técnica

Este repositório contém o desenvolvimento de um sistema embarcado para [objetivo do projeto]. O projeto foi concebido como parte dos requisitos avaliativos da disciplina SM66A - Sistemas Microcontrolados.

## ✨ Funcionalidades Implementadas (mínimo de 1)

- Contador de eventos via sensor LDR: O sistema monitora a saída de um comparador conectado a um LDR. Cada vez que a luz diminui (ou a resistência do LDR aumenta) gerando uma borda de subida no comparador, o microcontrolador incrementa um contador interno.
- Exibição binária do contador em LEDs: O valor do contador é mostrado em tempo real através de 4 LEDs conectados aos pinos PF1..PF4 do TM4C123, formando um display binário visual.
- Interrupção externa por GPIO: O microcontrolador usa uma interrupção por borda de subida no pino PF0 para detectar rapidamente a mudança do sinal do comparador, garantindo resposta imediata e baixo uso de CPU.

## ✨ Periféricos Utilizados (mínimo de 4)

- GPIO (PORTF)
- NVIC
- Delay


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
2.  **Configuração do Ambiente:** Detalhamento das bibliotecas e configurações da IDE necessárias.
3.  **Compilação e Upload:** Instruções para compilar o firmware e transferi-lo para o microcontrolador.

## 🚀 Cronograma e Evolução (Roadmap)

- [ ] Definição da arquitetura de software.
- [ ] Implementação do módulo de leitura de sensores.
- [ ] Implementação da lógica de controle.
- [ ] Validação e testes funcionais.
