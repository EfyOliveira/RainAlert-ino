# RainAlert-ino


---

Projeto: Sensor de Chuva com Arduino e Notificação SMS

Descrição

Este projeto utiliza um sensor de chuva acoplado a um Arduino para detectar chuva e enviar uma notificação SMS para um número previamente configurado, usando o módulo SIM800L.


---

Materiais Necessários

1. Placa Arduino (ex.: Uno, Nano ou similar)


2. Módulo Sensor de Chuva


3. Módulo GSM SIM800L


4. Protoboard e cabos jumpers


5. Fonte de alimentação para o módulo SIM800L (3,7V a 4,2V)


6. Antena e chip SIM com créditos para SMS




---

Esquema de Conexão

Sensor de Chuva:

AO/DO → Pino A0 ou D2 do Arduino

VCC → 5V no Arduino

GND → GND no Arduino


SIM800L:

VCC → Fonte 3,7V a 4,2V

GND → GND no Arduino e na fonte

TX → Pino RX (10) no Arduino

RX → Pino TX (11) no Arduino




---

Código Arduino

```bash
#include <SoftwareSerial.h>

// Configuração da comunicação serial com o SIM800L
SoftwareSerial SIM800L(10, 11); // RX no pino 10, TX no pino 11

// Configuração do sensor
const int sensorPin = A0;
int valorSensor = 0;

void setup() {
  // Inicializa as portas seriais
  Serial.begin(9600);       // Serial para monitor do PC
  SIM800L.begin(9600);      // Serial para o SIM800L

  // Configuração inicial do módulo SIM800L
  delay(1000);
  SIM800L.println("AT");    // Teste de conexão
  delay(1000);
  SIM800L.println("AT+CMGF=1"); // Define o modo SMS texto
  delay(1000);

  Serial.println("Configuração concluída!");
}

void loop() {
  valorSensor = analogRead(sensorPin);

  if (valorSensor < 500) { // Ajuste o valor conforme a sensibilidade desejada
    Serial.println("Chuva detectada!");
    enviarSMS("+XXXXXXXXXXXXX", "Alerta: Chuva detectada!");
    delay(30000); // Aguarda 30 segundos antes de enviar outra notificação
  }
  delay(1000); // Aguarda antes de realizar a próxima leitura
}

void enviarSMS(String numero, String mensagem) {
  SIM800L.print("AT+CMGS=\"");
  SIM800L.print(numero); // Número do destinatário
  SIM800L.println("\"");
  delay(1000);
  SIM800L.print(mensagem); // Mensagem a ser enviada
  delay(1000);
  SIM800L.write(26); // Envia CTRL+Z para finalizar o SMS
  delay(3000);
  Serial.println("Mensagem enviada!");
}
```

---

Instruções

1. Alimente o Módulo SIM800L: Certifique-se de que a tensão esteja entre 3,7V e 4,2V. Use um regulador de tensão, como o LM2596, para evitar danos.


2. Configure o Chip SIM: Insira um chip SIM com créditos para SMS e conecte a antena ao módulo.


3. Ajuste o Sensor de Chuva: Regule a sensibilidade no potenciômetro do módulo comparador.


4. Carregue o Código: Utilize o Arduino IDE para carregar o código na placa.




---

Funcionamento

O sensor detecta a presença de água e envia um sinal para o Arduino.

O Arduino processa o sinal e aciona o módulo SIM800L.

O SIM800L envia uma mensagem SMS para o número +55 12 99671-9209 com o alerta de chuva.



---

Observações

Ajuste o valor de detecção (if (valorSensor < 500)) conforme a sensibilidade do sensor.

Verifique se o chip SIM está ativo e com créditos.

Use uma fonte de alimentação estável para evitar reinicializações no módulo SIM800L.



---
