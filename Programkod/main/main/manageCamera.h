/*
  ConnectToWiFi.h - Library for connecting between ESP8266 och IP-camera.
  Created by SAFE24, February 18, 2017.
  Released into the public domain.
*/



//------------------------------
//-----  FUNCTIONS -----
//------------------------------

/**
   This function will send a request to the server
*/
int sendToCamera ( String, String, const char*, const char*);


/*Continuous pan/tilt motion.
  Positive values mean right (pan) and up (tilt),
  negative values mean left (pan) and down (tilt). "0,0"
  means stop.
*/
String continuousPanTiltMove (int, int, int);
// Activates a virtual port on Camera
String activateVirtualPort (String);
// Deactivates a virtual port on Camera
String deactivateVirtualPort (String);





