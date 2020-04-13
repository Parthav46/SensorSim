#include <ESP8266WiFi.h>
#include <SensorSim.h>

#define SSID "NETGEAR300"
#define PSWD "nooooo!!"

bool connected;

void setup() {
	Serial.begin(9600);
	WiFi.begin(SSID, PSWD);
	while(WiFi.status() != WL_CONNECTED) {
		Serial.print(".");
		delay(100);
	}
	Serial.println();
	Serial.print("Connected: ");
	Serial.println(WiFi.localIP());
	if (SensorSim.checkConnection()) Serial.println("Connected to the internet");
	else Serial.println("Failed to connect to the internet");
	SensorSim.begin();
	connected = SensorSim.connect("testing");
	if(connected) Serial.println("Synced with project");
}

void loop () {
	if(connected) SensorSim.refresh();
}