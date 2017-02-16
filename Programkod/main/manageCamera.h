/*
  ConnectToWiFi.h - Library for connecting to WiFi-network.
  Created by SAFE24, Januari 20, 2017.
  Released into the public domain.
*/



//------------------------------
//-----  FUNCTIONS -----
//------------------------------


//Sending commands to the camera
int sendToCamera ( String, String,const char*,const char*);

// Activates a virtual port on Camera
String activateVirtualPort (String);

// Deactivates a virtual port on Camera
String deactivateVirtualPort (String);



