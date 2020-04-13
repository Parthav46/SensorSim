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

bool SensorClass::connect (char *uid) {
	SensorClass::uid = uid;
	SensorClass::type = Firebase.get(uid).getInt("type");
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
		case 0:
			pinMode(D1, OUTPUT);
			break;
		}
	}
	if(!status) stop();
	return status;
}

void SensorClass::stop() {

}

void SensorClass::refresh() {
	if(Firebase.available()) {
		switch (type) {
			case 0:
				int level = Firebase.readEvent().getInt("data");
				analogWrite(D1, level);
				break;
		}
	}
}

