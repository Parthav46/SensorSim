#ifndef SENSOR_SIM
#define SENSOR_SIM

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "iot-bootcamp-c2308.firebaseio.com"
#define FIREBASE_AUTH "qktFfhEr4lBtySOeggEBWzbipKiZOOlFSVBOlPum"


// enum Types {ANALOG, SPI, UART, I2C};

class SensorClass {
	public:
		void begin (void);
		bool checkConnection (void);
		bool connect (char *uid);
		void refresh(void);
		void stop(void);
	private:
		bool start(void);
		int type;
		char *uid;
};

extern SensorClass SensorSim;

#endif