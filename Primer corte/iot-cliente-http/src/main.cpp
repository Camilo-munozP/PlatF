#include <Arduino.h>
#include "libwifi.h"
#include <WiFi.h>

#define LED 2

const char *ssid = "Familia Mupe";
const char *password = "Dylans2015";
const char *host = "codelab.denkitronik.com";
const int port = 8080;
const String thingName = "ESPTH";  // Nombre del dispositivo

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Iniciando...");
  conectarWifi(ssid, password);
}

void loop() {
  WiFiClient cliente;
  if (!cliente.connect(host, port)) {
    Serial.println("Error al conectar con el servidor");
    delay(2000);
    return;
  }

  float temperatura = random(200, 350) / 10.0;  // Entre 20.0 y 35.0 °C
  float humedad = random(300, 900) / 10.0;      // Entre 30.0 y 90.0 %

  // Construir la URL con los datos en formato GET
  String url = "/thingname/" + thingName + "?temperatura=" + String(temperatura) + "&humedad=" + String(humedad);

  Serial.print("Enviando datos -> ");
  Serial.println(url);

  // Enviar solicitud GET
  cliente.print("GET " + url + " HTTP/1.1\r\n" +
                "Host: " + String(host) + "\r\n" +
                "Connection: close\r\n\r\n");

  // Esperar respuesta del servidor
  unsigned long tiempo = millis();
  while (cliente.available() == 0) {
    if (millis() - tiempo > 5000) {
      Serial.println("Tiempo de espera agotado");
      cliente.stop();
      return;
    }
  }

  while (cliente.available()) {
    String linea = cliente.readStringUntil('\r');
    Serial.print(linea);
  }

  Serial.println("\nFin de la conexión");
  cliente.stop();
  delay(4000);
}
