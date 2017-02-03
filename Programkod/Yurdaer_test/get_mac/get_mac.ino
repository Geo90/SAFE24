/**
 * Gets the MAC-adress and prints it out of some unknown
 * device?
 */

#include <ESP8266WiFi.h>

//Contains the MAC-adress as an int and a char arrays
uint8_t MAC_array[6];
char MAC_char[18];

void setup() {
    Serial.begin(115200);
    Serial.println();

    //
    WiFi.macAddress(MAC_array); 
    
    //
    for (int i = 0; i < sizeof(MAC_array); ++i) {
        sprintf(MAC_char, "%s%02x:", MAC_char, MAC_array[i]);
    }

    //Prints the MAC-adress
    Serial.println(MAC_char);
}

void loop() {
    //Prints tha MAC-adress char-array
    Serial.println(MAC_char);
    Serial.println();
    delay(5000);
}
