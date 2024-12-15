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