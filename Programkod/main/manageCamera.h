/*
  ConnectToWiFi.h - Library for connecting to WiFi-network.
  Created by SAFE24, Januari 20, 2017.
  Released into the public domain.
*/



//------------------------------
//-----  FUNCTIONS -----
//------------------------------

//Move camera to the desired angle and specify which camera to move. 
String moveCameraHorizontal (int, int);
String moveCameraVertical (int, int);

String continuousPanTiltMove (int, int, int);

// Autofocus On/Off. 
String autoFocus ( String, String);

// Autoiris On/Off. 
String autoIris ( String, String);

//Sending commands to the camera
int sendToCamera ( String, String,const char*,const char*);

// Activates a virtual port on Camera
String activateVirtualPort (String);

// Deactivates a virtual port on Camera
String deactivateVirtualPort (String);



