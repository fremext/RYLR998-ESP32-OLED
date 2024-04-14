
#include <Adafruit_SSD1306.h> // Biblioteca para el controlador de pantalla OLED SSD1306
#include <Adafruit_GFX.h> // Biblioteca para gráficos vectoriales

// Configuración de la pantalla OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // Instancia de la clase Adafruit_SSD1306 para controlar la pantalla OLED

String lora_band = "915000000"; // Banda de frecuencia (Hz) dependiendo del país/región
String lora_networkid = "18";   // Identificación de la red LoRa
String lora_address = "2";      // Dirección del módulo LoRa
int led = 23;                   // LED conectado al pin D23 del ESP32

String textoEntrada; // Almacena los datos recibidos del emisor


void setup() {
  // Inicialización de la pantalla OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Inicializa la pantalla OLED con la dirección I2C 0x3C y la alimentación interna del regulador de tensión
  display.clearDisplay(); // Borra el contenido del búfer de visualización de la pantalla
  display.display(); // Muestra el contenido del búfer en la pantalla

  pinMode(led, OUTPUT); // Modo de salida para el LED

  Serial2.begin(115200, SERIAL_8N1, 16, 17); // Inicialización del puerto serie 2 (pin 16 RXD, 17 TXD UART del ESP32)
  Serial.begin(115200);                      // Inicialización del puerto serie principal a 115200 baudios

  delay(1500);
  Serial2.println("AT+BAND=" + lora_band);      // Configuración del módulo/puerto serie (UART 2)
  delay(500);
  Serial2.println("AT+NETWORKID=" + lora_networkid); // Establece la identificación de la red LoRa
  delay(500);
  Serial2.println("AT+ADDRESS=" + lora_address); // Establece la dirección del módulo LoRa
  delay(1000);
}

void loop() {
  if (Serial2.available()) { // Si hay datos disponibles en el puerto serie 2
    textoEntrada = Serial2.readString(); // Almacena los datos recibidos del emisor
    textoEntrada.trim();                 // Elimina espacios en blanco al principio y al final del mensaje
    Serial.println(textoEntrada);        // Muestra por consola los datos recibidos del emisor

    if (textoEntrada.indexOf("ON") >= 0) { // Busca la palabra "ON" en el mensaje recibido
      digitalWrite(led, HIGH); // Enciende el LED si se encuentra la palabra "ON"
      // Configuración y visualización de mensajes en la pantalla OLED
      display.clearDisplay(); // Borra el contenido actual de la pantalla OLED
      display.setTextSize(1); // Establece el tamaño del texto en 1
      display.setTextColor(SSD1306_WHITE); // Establece el color del texto en blanco
      display.setCursor(0, 0); // Establece la posición del cursor en la pantalla
      display.println("Receptor:0 a 8.Km"); // Imprime el mensaje en la pantalla
      display.setCursor(0, 10); // Establece una nueva posición del cursor
      display.println("Estado del LED"); // Imprime el mensaje en la pantalla
      display.setTextSize(2); // Establece el tamaño del texto en 2
      display.setCursor(12, 35); // Establece una nueva posición del cursor
      display.println("ENCENDIDO"); // Imprime el mensaje en la pantalla
      display.drawRect(6, 27, 118, 30, SSD1306_WHITE); // Dibuja un rectángulo alrededor del mensaje
      display.display(); // Muestra el contenido en la pantalla OLED
      delay(1500); // Espera 1.5 segundos
      display.fillRect(6, 27, 118, 30, SSD1306_BLACK); // Borra el mensaje "ENCENDIDO" de la pantalla
    } else {
      digitalWrite(led, LOW); // Apaga el LED si no se encuentra la palabra "ON"
      // Configuración y visualización de mensajes en la pantalla OLED
      display.clearDisplay(); // Borra el contenido actual de la pantalla OLED
      display.setTextSize(1); // Establece el tamaño del texto en 1
      display.setTextColor(SSD1306_WHITE); // Establece el color del texto en blanco
      display.setCursor(0, 0); // Establece la posición del cursor en la pantalla
      display.println("Receptor:FREMEXT"); // Imprime el mensaje en la pantalla
      display.setCursor(0, 10); // Establece una nueva posición del cursor
      display.println("Estado del LED"); // Imprime el mensaje en la pantalla
      display.setTextSize(2); // Establece el tamaño del texto en 2
      display.setCursor(23, 35); // Establece una nueva posición del cursor
      display.println("APAGADO"); // Imprime el mensaje en la pantalla
      display.drawRect(17, 27, 95, 30, SSD1306_WHITE); // Dibuja un rectángulo alrededor del mensaje
      display.display(); // Muestra el contenido en la pantalla OLED
    }
  }
}