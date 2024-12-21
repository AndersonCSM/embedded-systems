# 🚦 **Sistema de Sinalização Sonora para Travessia de Pedestres**

## 📚 **Contextualização**
Este projeto foi desenvolvido por um aluno do curso de **Tecnologia em Análise e Desenvolvimento de Sistemas (TADS)** do **IFRN - Campus Central**. O objetivo é criar um sistema de baixo custo que auxilie pessoas com deficiência visual na travessia segura de cruzamentos com sinalização sonora e luminosa.

## 🎯 **Objetivos do Projeto**
- Desenvolver um sistema de controle de sinais de trânsito para cruzamentos.  
- Emitir sinais sonoros e visuais para garantir a travessia segura.  
- Implementar um botão para acionamento manual do sistema.

## 🛠️ **Tecnologias e Ferramentas**
- **Hardware:** Raspberry Pi Pico W, LEDs, Buzzer, Push Button, Resistores, Protoboard e Fiação.  
- **Simulador:** Wokwi (para testes e validação do circuito).  
- **Linguagem de Programação:** C  

## ⚙️ **Funcionamento do Sistema**
1. **Estado Inicial:** Os LEDs alternam entre verde, amarelo e vermelho automaticamente.  
2. **Ao pressionar o botão:**  
   - O sinal amarelo fica ativo por 5 segundos.  
   - O sinal vermelho fica ativo por 15 segundos, permitindo a travessia.  
   - O LED verde para pedestres acende e o buzzer emite som intermitente.  
3. **Pós-travessia:** O sistema retorna ao funcionamento normal.

## 📝 **Como Executar o Projeto**
1. Clone este repositório:  
   ```bash
   git clone https://github.com/AndersonCSM/EmbeddedSystems.git
