#include "SensorSim.h"

SensorClass SensorSim;

bool SensorClass::checkConnection () {
	HTTPClient http;
	if (WiFi.status() != WL_CONNECTED) return false;
	http.begin("http://www.google.com");
	int httpCode = http.GET();
	if(httpCode == HTTP_CODE_OK) return true;
	return false;
}

void SensorClass::begin() {
	Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

bool SensorClass::connect (String uid) {
	SensorClass::uid = uid;
	SensorClass::type = (Types) Firebase.get(uid).getInt("type");
	return start();
}

/*
* Start firebase database location stream to check
* for changes.
*/
bool SensorClass::start() {
	Firebase.stream(uid);
	bool status = true;
	status &= Firebase.success();
	if(status){
		switch(type) {
			case ANALOG:
			{
				pinMode(D1, OUTPUT);
				val.level = 0;
				break;
			}
			case UART:
			{
			
				val.data = {0, 0, nullptr};
				val.data.uart = new SoftwareSerial(D6,D7);
				break;
			}
		}
	}
	if(!status) stop();
	return status;
}

void SensorClass::stop() {

}

void SensorClass::refresh() {
	if(Firebase.available()) {
		Firebase.readEvent();
		FirebaseObject data = Firebase.get(uid);
		switch (type) {
			case ANALOG:
			{
				val.level = data.getInt("value/val");
				analogWrite(D1, val.level);
				break;
			}
			case UART:
			{
				int baud = data.getInt("value/baud");
				if(val.data.baud != baud){
					if ((val.data.uart)->isListening())
						(val.data.uart)->end();
					val.data.baud = baud;
					val.data.count = data.getInt("value/count");
					(val.data.uart)->begin(val.data.baud);
				} else if (val.data.count != data.getInt("value/count")) {
					val.data.count = data.getInt("value/count");
					String str = data.getString("value/strtx");
					if(val.data.uart == nullptr) Serial.println("uart not initialized");
					else (val.data.uart)->print(str);
				}
				break;
			}
		}
	}
	if(type == UART) {
		if(val.data.uart->available() ) {
			String str = "";
			while((val.data.uart)->available()){
				str += (char)((val.data.uart)->read());
			}
			Firebase.setString(uid + "/value/strrx", str);	
		}
	}
}