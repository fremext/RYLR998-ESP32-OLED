
String lora_band = "915000000"; // Banda de frecuencia (Hz) dependerá del país/región donde se encuentre
String lora_networkid = "18";   // Identificación de la red LoRa
String lora_address = "1";      // Dirección del módulo LoRa
String lora_RX_address = "2";   // Dirección del módulo receptor LoRa

int led = 21;       // LED conectado al pin D21 del ESP32
int pulsador1 = 23; // Pulsador conectado al pin D22 del ESP32
int pulsador2 = 22; // Pulsador conectado al pin D23 del ESP32

void setup() {
  Serial2.begin(115200, SERIAL_8N1, 16, 17); // Puerto serie 2 (pin 16 RXD, 17 TXD UART del ESP32) y velocidad de 115200
  pinMode(pulsador1, INPUT_PULLUP); // Modo de entrada para el pin D23 del pulsador
  pinMode(pulsador2, INPUT_PULLUP); // Modo de entrada para el pin D22 del pulsador
  pinMode(led, OUTPUT); // Modo de salida para el pin D21 del LED

  delay(1500);
  Serial2.println("AT+BAND=" + lora_band); // Configuración del módulo/puerto serie (UART 2)
  delay(500);
  Serial2.println("AT+ADDRESS=" + lora_address); // Establecer la dirección del módulo LoRa
  delay(500);
  Serial2.println("AT+NETWORKID=" + lora_networkid); // Establecer la identificación de la red LoRa
  delay(1500);
}

void loop() {
  delay(100);

  if (digitalRead(pulsador1) == LOW) { // Si el pulsador 1 está presionado
    digitalWrite(led, HIGH); // Encender el LED
    Serial2.println("AT+SEND=" + lora_RX_address + ",2,ON"); // Enviar datos al módulo receptor "ON" (2 bytes)
  } else {
    digitalWrite(led, LOW); // Apagar el LED
  

  if (digitalRead(pulsador2) == LOW) { // Si el pulsador 2 está presionado
    digitalWrite(led, HIGH); // Encender el LED
    Serial2.println("AT+SEND=" + lora_RX_address + ",2,OF"); // Enviar datos al módulo receptor "OF" (2 bytes)
  } else {
    digitalWrite(led, LOW); // Apagar el LED
  }
}
}