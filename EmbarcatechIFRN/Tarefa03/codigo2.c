// Bibliotecas padrão
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Configuração da frequência do buzzer (em Hz)
#define BUZZER_FREQUENCY 100

// define recursos do sistema
#define PEDESTRE_BUTTONS_PIN  3 // Botões em GPIO 3
#define PEDESTRE_LEDS_VERDE_PIN  2 // LED verde em GPIO 2
#define PEDESTRE_BUZZERS_PIN 10  // Configuração do pino do buzzer

#define SEMAFORO_VERMELHO_PIN  13 // LED Vermelho em GPIO 15
#define SEMAFORO_AMARELO_PIN  14 // LED Amarelo em GPIO 14
#define SEMAFORO_VERDE_PIN  15 // LED Verde em GPIO 13

int tempo_normal[3] = {8, 2, 10};
int tempo_pedestre[3] = {8, 5, 15};

// Definição de uma função para inicializar o PWM no pino do buzzer
void pwm_init_buzzer(uint pin) {
    // Configurar o pino como saída de PWM
    gpio_set_function(pin, GPIO_FUNC_PWM);

    // Obter o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configurar o PWM com frequência desejada
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (BUZZER_FREQUENCY * 4096)); // Divisor de clock
    
    pwm_init(slice_num, &config, true);

    // Iniciar o PWM no nível baixo
    pwm_set_gpio_level(pin, 0);
}

// Definição de uma função para emitir um beep com duração especificada
void beep(uint pin, uint duration_ms) {
    // Obter o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configurar o duty cycle para 50% (ativo)
    pwm_set_gpio_level(pin, 2048);

    // Temporização
    sleep_ms(duration_ms);

    // Desativar o sinal PWM (duty cycle 0)
    pwm_set_gpio_level(pin, 0);

    // Pausa entre os beeps
    // sleep_ms(100); // Pausa de 100ms
}

void semaforo() {
    // Verde
    gpio_put(SEMAFORO_VERMELHO_PIN, 0);
    gpio_put(SEMAFORO_VERDE_PIN, 1);
    for (int i = 0; i < tempo_normal[0]; i++) {
        sleep_ms(1000);
        if (gpio_get(PEDESTRE_BUTTONS_PIN) == 0) {
            return; // Sai do ciclo normal para atender o botão
        }
    }

    // Amarelo
    gpio_put(SEMAFORO_VERDE_PIN, 0);
    gpio_put(SEMAFORO_AMARELO_PIN, 1);
    for (int i = 0; i < tempo_normal[1]; i++) {
        sleep_ms(1000);
        if (gpio_get(PEDESTRE_BUTTONS_PIN) == 0) {
            return;
        }
    }

    // Vermelho
    gpio_put(SEMAFORO_AMARELO_PIN, 0);
    gpio_put(SEMAFORO_VERMELHO_PIN, 1);
    for (int i = 0; i < tempo_normal[2]; i++) {
        sleep_ms(1000);
        if (gpio_get(PEDESTRE_BUTTONS_PIN) == 0) {
            return;
        }
    }
}


void sinalizacao_pedestre() {
    // Primeiro bloco: semáforo verde para veículos
    gpio_put(SEMAFORO_VERDE_PIN, 1);     // Ativar verde para veículos
    gpio_put(SEMAFORO_VERMELHO_PIN, 0); // Garantir que vermelho esteja apagado
    gpio_put(SEMAFORO_AMARELO_PIN, 0);  // Garantir que amarelo esteja apagado
    gpio_put(PEDESTRE_LEDS_VERDE_PIN, 0); // Garantir que o LED dos pedestres esteja apagado
    sleep_ms(tempo_pedestre[0] * 1000); // Aguardar tempo do semáforo verde

    // Segundo bloco: semáforo amarelo para veículos
    gpio_put(SEMAFORO_VERDE_PIN, 0);    // Apagar verde para veículos
    gpio_put(SEMAFORO_AMARELO_PIN, 1); // Ativar amarelo
    sleep_ms(tempo_pedestre[1] * 1000); // Aguardar tempo do semáforo amarelo

    // Terceiro bloco: semáforo vermelho para veículos e verde para pedestres
    gpio_put(SEMAFORO_AMARELO_PIN, 0);   // Apagar amarelo
    gpio_put(SEMAFORO_VERMELHO_PIN, 1);  // Ativar vermelho para veículos
    gpio_put(PEDESTRE_LEDS_VERDE_PIN, 1); // Ativar verde para pedestres

    // Alerta sonoro para pedestres
    beep(PEDESTRE_BUZZERS_PIN, tempo_pedestre[2] * 1000);
    sleep_ms(tempo_pedestre[2] * 1000); // Aguardar tempo para pedestres atravessarem

    // Final do ciclo: apagar verde para pedestres
    gpio_put(PEDESTRE_LEDS_VERDE_PIN, 0); // Apagar verde para pedestres
}

int main() {


  // inicializa recursos
  //stdio_init_all();

  // Inicializa os pinos dos Leds
  gpio_init(SEMAFORO_VERMELHO_PIN);
  gpio_init(SEMAFORO_AMARELO_PIN);
  gpio_init(SEMAFORO_VERDE_PIN);
  gpio_init(PEDESTRE_LEDS_VERDE_PIN);

  // Define como saída
  gpio_set_dir(SEMAFORO_VERMELHO_PIN, GPIO_OUT);
  gpio_set_dir(SEMAFORO_AMARELO_PIN, GPIO_OUT);
  gpio_set_dir(SEMAFORO_VERDE_PIN, GPIO_OUT);
  gpio_set_dir(PEDESTRE_LEDS_VERDE_PIN, GPIO_OUT);

  // Inicializa o botão e define como entrada
  gpio_init(PEDESTRE_BUTTONS_PIN);
  gpio_set_dir(PEDESTRE_BUTTONS_PIN, GPIO_IN);
  gpio_pull_up(PEDESTRE_BUTTONS_PIN);

  // Inicializa o buzzer e define como saída
  gpio_init(PEDESTRE_BUZZERS_PIN);
  gpio_set_dir(PEDESTRE_BUZZERS_PIN, GPIO_OUT);
  
  // Inicializar o PWM no pino do buzzer
  pwm_init_buzzer(PEDESTRE_BUZZERS_PIN);
  
  // variaveis
  int proximo = 0;

  while (true) {
    // Verifica se o botão foi pressionado
    if (gpio_get(PEDESTRE_BUTTONS_PIN) == 0) {
        // Executa o ciclo de pedestre
        printf("Botão pressionado!\n");
        sinalizacao_pedestre();
    } else {
        // Executa o ciclo normal do semáforo
        semaforo();
    }
  }
}