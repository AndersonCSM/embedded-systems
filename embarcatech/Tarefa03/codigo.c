// Bibliotecas padrão
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

// Configuração da frequência do buzzer (em Hz)
#define BUZZER_FREQUENCY 100;

void semaforo(){
    gpion_put(SEMAFORO_VERMELHO_PIN, 0);
    gpion_put(SEMAFORO_VERDE_PIN, 1);
    sleep_ms(tempo_normal[0]*1000);

    gpion_put(SEMAFORO_VERDE_PIN, 0);
    gpion_put(SEMAFORO_AMARELO_PIN, 1);
    sleep_ms(tempo_normal[1]*1000);

    gpion_put(SEMAFORO_AMARELO_PIN, 0);
    gpion_put(SEMAFORO_VERMELHO_PIN, 1);
    sleep_ms(tempo_normal[2]*1000);
}

void sinalizacao_pedestre(){
    gpion_put(SEMAFORO_VERMELHO_PIN, 0);
    gpion_put(SEMAFORO_VERDE_PIN, 1);
    sleep_ms(tempo_pedestre[0]*1000);

    gpion_put(SEMAFORO_VERDE_PIN, 0);
    gpion_put(SEMAFORO_AMARELO_PIN, 1);
    sleep_ms(tempo_pedestre[1]*1000);

    gpion_put(SEMAFORO_AMARELO_PIN, 0);
    gpion_put(SEMAFORO_VERMELHO_PIN, 1);
    gpion_put();
    sleep_ms(tempo_pedestre[2]*1000);
}

int main() {
  // define recursos do sistema
  const PEDESTRE_BUTTONS_PIN = 3; // Botões em GPIO 3
  const PEDESTRE_LEDS_VERDE_PIN = 2; // LED verde em GPIO 2
  const PEDESTRE_BUZZERS_PIN = 10; // Avisos sonoros em GPIO 10

  const SEMAFORO_VERMELHO_PIN = 15; // LED Vermelho em GPIO 15
  const SEMAFORO_AMARELO_PIN = 14; // LED Amarelo em GPIO 14
  const SEMAFORO_VERDE_PIN = 13; // LED Verde em GPIO 13

  // inicializa recursos
  //stdio_init_all();

  // Inicializa os pinos dos Leds
  gpio_init(SEMAFORO_VERMELHO_PIN);
  gpio_init(SEMAFORO_AMARELO_PIN);
  gpio_init(SEMAFORO_VERDE_PIN);
  gpio_init(PEDESTRE_LEDS_VERDE_PIN);

  // Define como saída
  gpio_put(SEMAFORO_VERMELHO_PIN, GPIO_OUT);
  gpio_put(SEMAFORO_AMARELO_PIN, GPIO_OUT);
  gpio_put(SEMAFORO_VERDE_PIN, GPIO_OUT);
  gpio_put(PEDESTRE_LEDS_VERDE_PIN, GPIO_OUT);

  // Inicializa o botão e define como entrada
  gpio_init(PEDESTRE_BUTTONS_PIN);
  gpio_set_dir(PEDESTRE_BUTTONS_PIN, GPIO_IN);
  gpio_pull_up(PEDESTRE_BUTTONS_PIN);

  // Inicializa o buzzer e define como saída
  gpio_init(BUZZER_PIN);
  gpio_set_dir(BUZZER_PIN, GPIO_OUT);


  //Variáveis
  int pedestre = 0;
  int tempo_normal[3] = [8, 2, 10];
  int tempo_pedestre[3] = [8, 5, 15];

  while (true) {
    pedestre = gpio_get(PEDESTRE_BUTTONS_PIN);
    if(!pedestre){
      semaforo();
    } else if (){
      sinalizacao_pedestre();
    }

  }
}