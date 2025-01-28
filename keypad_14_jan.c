#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/pwm.h"

#define ROWS 4 //linhas
#define COLS 4 //colunas

uint rowPins[ROWS] = {8, 7, 6, 5}; // Pinos conectados às linhas do teclado
uint colPins[COLS] = {4, 3, 2, 1}; // Pinos conectados às colunas do teclado

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

uint ledBLUEPin = 28; // Pino conectado ao LED BLUE
uint ledGREENPin = 27; // Pino conectado ao LED GREEN
uint ledREDPin = 26; // Pino conectado ao LED RED
uint buzzerPin = 21; // Pino conectado ao Buzzer

// Função de configuração inicial
void setup() {
  stdio_init_all();

  // Configurar os pinos dos LEDs como saída
  gpio_init(ledBLUEPin);
  gpio_set_dir(ledBLUEPin, GPIO_OUT);
  gpio_init(ledREDPin);
  gpio_set_dir(ledREDPin, GPIO_OUT);
  gpio_init(ledGREENPin);
  gpio_set_dir(ledGREENPin, GPIO_OUT);

  // Configurar o pino do Buzzer como saída
  gpio_init(buzzerPin);
  gpio_set_dir(buzzerPin, GPIO_OUT);

  // Configurar os pinos das colunas como saída e setar HIGH
  for (int i = 0; i < COLS; i++) {
    gpio_init(colPins[i]);
    gpio_set_dir(colPins[i], GPIO_OUT);
    gpio_put(colPins[i], 1); // Coluna iniciada com HIGH
  }

  // Configurar os pinos das linhas como entrada com pull-up
  for (int i = 0; i < ROWS; i++) {
    gpio_init(rowPins[i]);
    gpio_set_dir(rowPins[i], GPIO_IN);
    gpio_pull_up(rowPins[i]); // Configura pull-up nas linhas
  }
}

// Função para ler a tecla pressionada
char getKey() {
  for (int col = 0; col < COLS; col++) {
    // Setar a coluna atual como LOW
    gpio_put(colPins[col], 0);

    for (int row = 0; row < ROWS; row++) {
      // Verificar se a linha está em LOW (botão pressionado)
      if (gpio_get(rowPins[row]) == 0) {
        return keys[row][col]; // Retorna a tecla pressionada
      }
    }

    // Setar a coluna atual como HIGH
    gpio_put(colPins[col], 1);
  }

  return '\0'; // Nenhuma tecla pressionada
}

//Funcao para ativar o Buzzer por 2 segundos
void tocar_buzzer(){
  gpio_set_function(buzzerPin, GPIO_FUNC_PWM);      // Configura pino como saída PWM
    uint slice_num = pwm_gpio_to_slice_num(buzzerPin); // Obter o slice do PWM

    pwm_set_clkdiv(slice_num, 125.0);                  
    pwm_set_wrap(slice_num, 255);                      
    pwm_set_gpio_level(buzzerPin, 50);              
    pwm_set_enabled(slice_num, true);                  // Ativar o PWM

    sleep_ms(100);                                    // Manter o som por 2 segundos

    pwm_set_enabled(slice_num, false);                 // Desativar o PWM  
}

// Função para controlar os LEDs e o buzzer
void controlOutputs(char key) {
  // Lógica para acender/apagar os LEDs com base na tecla pressionada
  if (key == 'A') {
    gpio_put(ledBLUEPin, 1); // Acender o LED BLUE enquanto 'A' estiver pressionada
  } else {
    gpio_put(ledBLUEPin, 0); // Apagar o LED
  }

  if (key == 'B') {
    gpio_put(ledGREENPin, 1); // Acender o LED GREEN enquanto 'B' estiver pressionada
  } else {
    gpio_put(ledGREENPin, 0); // Apagar o LED
  }

  if (key == 'C') {
    gpio_put(ledREDPin, 1); // Acender o LED RED enquanto 'C' estiver pressionada
  } else {
    gpio_put(ledREDPin, 0); // Apagar o LED
  }

  if (key == 'D') {
    // Acender os 3 LEDs enquanto 'D' estiver pressionada
    gpio_put(ledBLUEPin, 1);
    gpio_put(ledGREENPin, 1);
    gpio_put(ledREDPin, 1);

  } else {
    // Apagar os 3 LEDs e o buzzer
    if (key != 'A') gpio_put(ledBLUEPin, 0);
    if (key != 'B') gpio_put(ledGREENPin, 0);
    if (key != 'C') gpio_put(ledREDPin, 0);
  }

  // Emitir som curto e contínuo com o buzzer enquanto '#' estiver pressionado
  if (key == '#') {
    tocar_buzzer();
  }
}

int main() {
  setup();
  char lastKey = '\0';

  while (1) {
    char key = '\0';

    for (int col = 0; col < COLS; col++) {
      gpio_put(colPins[col], 0);

      for (int row = 0; row < ROWS; row++) {
        if (gpio_get(rowPins[row]) == 0) {
          key = keys[row][col];
        }
      }

      gpio_put(colPins[col], 1);
    }

    if (key != lastKey) {
      if (key != '\0') {
        printf("Tecla pressionada: %c\n", key);
      } else {
        printf("Nenhuma tecla pressionada\n");
      }
      lastKey = key;
    }

    // Chama a função para controlar os LEDs e o buzzer
    controlOutputs(key);

    busy_wait_us(100000); // Esperar 100 ms (100.000 microsegundos)
  }

  return 0;
}
