#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <LittleFS.h>
#include <SD.h>
#include <WiFi.h>
#include <Update.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


#define DHTPIN 10       // Pin GPIO conectado al DATA del DHT11
#define DHTTYPE DHT11   // Especificar el tipo de sensor (DHT11)

// Crear una instancia del sensor DHT
DHT dht(DHTPIN, DHTTYPE);

// Definir pines para la pantalla ST7735S
#define TFT_CS     5
#define TFT_RST    4
#define TFT_DC     2

// Crear objeto para la pantalla ST7735S
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  // Inicializar comunicación SPI
  SPI.begin();

  // Inicializar el puerto serie
  Serial.begin(9600);
  dht.begin();
  Serial.println("DHT11 Sensor iniciado");

  // Inicializar la pantalla ST7735S
  tft.initR(INITR_BLACKTAB);  // Configuración específica para ST7735S
  tft.fillScreen(ST7735_BLACK);  // Limpiar pantalla con fondo negro

  // Escribir texto inicial en pantalla
  tft.setTextColor(ST7735_WHITE); 
  tft.setTextSize(1);
  tft.setCursor(10, 10);
  tft.println("Inicializando...");
}

void loop() {
  // Leer temperatura y humedad del DHT11
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // Verificar errores de lectura
  if (isnan(temp) || isnan(hum)) {
    Serial.println("Error leyendo el sensor DHT11");
    tft.fillScreen(ST7735_BLACK);  // Limpiar la pantalla
    tft.setCursor(10, 10);
    tft.setTextColor(ST7735_RED);
    tft.println("Error en sensor!");
    delay(2000);
    return;
  }

  // Mostrar valores en el Monitor Serial
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.println(" °C");

  Serial.print("Humedad: ");
  Serial.print(hum);
  Serial.println(" %");

  // Mostrar valores en la pantalla ST7735
  tft.fillScreen(ST7735_BLACK);  // Limpiar pantalla antes de actualizar
  tft.setCursor(10, 10);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.println("Temperatura:");
  tft.setCursor(10, 30);
  tft.print(temp);
  tft.println(" °C");

  tft.setCursor(10, 50);
  tft.println("Humedad:");
  tft.setCursor(10, 70);
  tft.print(hum);
  tft.println(" %");

  // Esperar antes de la siguiente actualización
  delay(2000);
}