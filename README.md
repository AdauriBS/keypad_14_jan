# Projeto de Controle de LEDs e Buzzer com Teclado Matricial 4x4

## Descrição
Este projeto utiliza um **Raspberry Pi Pico** para controlar três LEDs (azul, verde e vermelho) e um buzzer, com base na entrada de um teclado matricial 4x4. O sistema, desenvolvido em **C**, lê as teclas pressionadas no teclado e aciona os LEDs e o buzzer conforme definido.

## Componentes Utilizados
- **Raspberry Pi Pico**
- **Teclado Matricial 4x4**
- **LEDs** (azul, verde e vermelho)
- **Resistores de 220 ohms**
- **Buzzer**
- **Protoboard e cabos de conexão**

## Diagrama de Conexões
O diagrama de conexões está detalhado no arquivo `diagram.json`. As conexões principais são:

### Teclado Matricial
- **Colunas** conectadas aos pinos **GP1 a GP4** do Raspberry Pi Pico
- **Linhas** conectadas aos pinos **GP5 a GP8** do Raspberry Pi Pico

### LEDs
- **LED azul** conectado ao pino **GP28** do Raspberry Pi Pico através de um resistor de 220 ohms
- **LED verde** conectado ao pino **GP27** do Raspberry Pi Pico através de um resistor de 220 ohms
- **LED vermelho** conectado ao pino **GP26** do Raspberry Pi Pico através de um resistor de 220 ohms

### Buzzer
- **Buzzer** conectado ao pino **GP21** do Raspberry Pi Pico

## Funcionalidades
- **Tecla A**: Acende o **LED azul**
- **Tecla B**: Acende o **LED verde**
- **Tecla C**: Acende o **LED vermelho**
- **Tecla D**: Acende todos os três LEDs
- **Tecla #**: Aciona o **buzzer**, que emite um som curto e contínuo a cada 250 ms

## Código Fonte
O código fonte do projeto está disponível no arquivo [`keypad_14_jan.c`](./keypad_14_jan.c). Ele configura os pinos do Raspberry Pi Pico, lê as teclas pressionadas e controla os LEDs e o buzzer conforme as entradas do teclado matricial.
Vídeo - Apresentação [https://drive.google.com/file/d/12PscNWF8t_HIvUkmxGzE14TbbHgnS_Y0/view?usp=sharing]

## Como Executar
1. Conecte todos os componentes seguindo o diagrama de conexões.
2. Compile o arquivo `keypad_14_jan.c` e faça o upload para o Raspberry Pi Pico.
3. Alimente o Raspberry Pi Pico e teste as funcionalidades pressionando as teclas do teclado matricial.

## Vídeo
https://drive.google.com/file/d/16YoFY1BWDy9PEkTdgIPBYjgSiTu8xjoI/view?usp=sharing

## Licença
Este projeto está licenciado sob a [MIT License](./LICENSE).

