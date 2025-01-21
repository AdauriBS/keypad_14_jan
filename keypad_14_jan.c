#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/pwm.h"

#define ROWS 4 
#define COLS 4 

uint slice_num;

//Pinos das linhas e colunas 
uint rowPins[ROWS] = {8, 7, 6, 5}; 
uint colPins[COLS] = {4, 3, 2, 1}; 

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

uint ledBLUEPin = 28; 
uint ledGREENPin = 27; 
uint ledREDPin = 26; 
uint buzzerPin = 21; 

void setup() {
  stdio_init_all();

//Configura os Leds
  gpio_init(ledBLUEPin);
  gpio_set_dir(ledBLUEPin, GPIO_OUT);
  gpio_init(ledREDPin);
  gpio_set_dir(ledREDPin, GPIO_OUT);
  gpio_init(ledGREENPin);
  gpio_set_dir(ledGREENPin, GPIO_OUT);

//Configura o Buzzer
  gpio_init(buzzerPin);
  gpio_set_dir(buzzerPin, GPIO_OUT);
  gpio_set_function(buzzerPin, GPIO_FUNC_PWM);      
  slice_num = pwm_gpio_to_slice_num(buzzerPin); // Obter o slice do PWM
  pwm_set_clkdiv(slice_num, 125.0);                  
  pwm_set_wrap(slice_num, 255); 

  // Configurar os pinos das colunas como saída e setar HIGH
  for (int i = 0; i < COLS; i++) {
    gpio_init(colPins[i]);
    gpio_set_dir(colPins[i], GPIO_OUT);
    gpio_put(colPins[i], 1); 
  }

  // Configurar os pinos das linhas como entrada com pull-up
  for (int i = 0; i < ROWS; i++) {
    gpio_init(rowPins[i]);
    gpio_set_dir(rowPins[i], GPIO_IN);
    gpio_pull_up(rowPins[i]); 
  }
}

// Função para ler a tecla pressionada
char getKey() {
  for (int col = 0; col < COLS; col++) {
    gpio_put(colPins[col], 0);

    for (int row = 0; row < ROWS; row++) {
      if (gpio_get(rowPins[row]) == 0) {
        return keys[row][col]; 
      }
    }
    gpio_put(colPins[col], 1);
  }

  return '\0';
}

void tocar_buzzer(){

    pwm_set_gpio_level(buzzerPin, 50);              
    pwm_set_enabled(slice_num, true);                  
    sleep_ms(100);                                    
    pwm_set_enabled(slice_num, false);                 
}

void controlLeds(char key) {
  if (key == 'A') {
    gpio_put(ledBLUEPin, 1); 
  } else {
    gpio_put(ledBLUEPin, 0); 
  }

  if (key == 'B') {
    gpio_put(ledGREENPin, 1); 
  } else {
    gpio_put(ledGREENPin, 0); 
  }

  if (key == 'C') {
    gpio_put(ledREDPin, 1); 
  } else {
    gpio_put(ledREDPin, 0); 
  }

  if (key == 'D') {
    gpio_put(ledBLUEPin, 1);
    gpio_put(ledGREENPin, 1);
    gpio_put(ledREDPin, 1);

  } else {
    if (key != 'A') gpio_put(ledBLUEPin, 0);
    if (key != 'B') gpio_put(ledGREENPin, 0);
    if (key != 'C') gpio_put(ledREDPin, 0);
  }
}

void controlBuzzer(char key) {

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

    controlLeds(key);
    controlBuzzer(key);

    busy_wait_us(100000); 
  }
  return 0;
}
