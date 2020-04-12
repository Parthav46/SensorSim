#include "SensorSim.h"

extern void check (Stream &port, char *ssid, char *pswd) {
    Stream *serial = &port;
    HTTPClient http;
    serial->println("Starting ESP8266...");
    WiFi.begin(ssid, pswd);
    while (WiFi.status() != WL_CONNECTED)
    {
        serial->print(".");
        delay(500);
    }
    serial->println();
    serial->print("connected: ");
    serial->println(WiFi.localIP());
    http.begin("http://www.google.com");
    int httpCode = http.GET();
    if(httpCode == HTTP_CODE_OK) {
        serial->println("Connected to the Internet");
    } else {
        serial->println("Failed to connect to the Internet");
	}
}