#ifndef SENSOR_SIM
#define SENSOR_SIM

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FirebaseArduino.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

#define FIREBASE_HOST "iot-bootcamp-c2308.firebaseio.com"
#define FIREBASE_AUTH "qktFfhEr4lBtySOeggEBWzbipKiZOOlFSVBOlPum"


enum Types {ANALOG, UART, SPI, I2C};

class SensorClass {
	protected:
		typedef struct UARTData {
			int baud;
			int count;
			SoftwareSerial *uart;
		} UARTData;

		union values {
			values() {}
			int level;
			UARTData data;
			~values() {}
		};
	public:
		void begin (void);
		bool checkConnection (void);
		bool connect (String uid);
		void refresh(void);
		void stop(void);
		values val;
	private:
		bool start(void);
		Types type;
		String uid;
};

extern SensorClass SensorSim;

#endif