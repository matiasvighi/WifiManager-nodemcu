#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

void handleRoot() {
    Serial.println("Conectado al WiFi. IP: " + WiFi.localIP().toString());
    String html = "<html><body><h1>WiFi Conectado!</h1><p>IP: " + WiFi.localIP().toString() + "</p>";
    html += "<br><br><a href='/borrarWifi'>Borrar configuración WiFi</a></body></html>";
    server.send(200, "text/html", html);
}

void resetWifiData() {
  WiFiManager wifiManager;
  wifiManager.resetSettings();
  Serial.println("La configuración del WiFi ha sido borrada.");
  server.send(200, "text/html", "La configuración del WiFi ha sido borrada. Reiniciando...");
  delay(2000);
  ESP.restart();
}

void setup() {
  Serial.begin(115200);

  // Crea un objeto WiFiManager
  WiFiManager wifiManager;

  // Conectar la placa a una red WiFi
  wifiManager.autoConnect("MiNodemcuAP");

  // Si la conexión es exitosa, imprimir la dirección IP asignada
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Conectado a la red WiFi ");
    Serial.print(WiFi.SSID());
    Serial.print(" con la dirección IP ");
    Serial.println(WiFi.localIP());

    // Configurar el servidor web
    server.on("/", handleRoot);
    server.on("/borrarWifi", resetWifiData);
    server.begin();
  }
}

void loop() {
  server.handleClient();
}
