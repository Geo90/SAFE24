//-----------------------------------------------
//This sketch is combined from Adafruit DHT sensor and tdicola for dht.h library
// https://learn.adafruit.com/dht/overview
// https://gist.github.com/teos0009/acad7d1e54b97f4b2a88
//other Authors Arduino and associated Google Script:
//Aditya Riska Putra
//Ahmed Reza Rafsanzani
//Ryan Eko Saputro
//See Also:
//http://jarkomdityaz.appspot.com/
//
//ELINS UGM
//
//Modified for Hackster.io project for the MKR1000 
//by Stephen Borsay(Portland, OR, USA)
//Since Arduino can't https, we need to use Pushingbox API (uses http)to run 
//the Google Script (uses https). Alternatly use Ivan's SecureWifi encryption
//- See more at: http://www.esp8266.com/viewtopic.php?f=29&t=3587#sthash.lWbpb243.dpuf
//#include "DHT.h"

//Download ESP8266.h package -->
//http://arduino.esp8266.com/stable/package_esp8266com_index.json

/**************************
 *    ARDUINO LIBRARY     *
 **************************/
#include "ESP8266WiFi.h"


/**************************
 *    CUSTOM LIBRARY     *
 **************************/
#include "ConnectToWiFi.h"


// WiFi parameters to be user-configured
const char* ssid = "iPhone";
const char* password = "12345678";
const char WEBSITE[] = "api.pushingbox.com"; //pushingbox API server
const String devid = "vBDE0176C74D864E"; //device ID on Pushingbox for our Scenario



void setup(void)
{
  Serial.begin(115200);
  // Connect to WiFi
  connectToWifi(ssid, password);  
  
}

void loop() {
   //Wait between measurements longer then normal to slow donwn
  //google sheet populate, as We dont want to exceed free service quota
  delay(10000); //10 seconds, (sampling rate vs. service call quota)

  float humidityData = 0;//dht.readHumidity();
  // Read temperature as Celsius (the default)
  float celData = 1;//dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float fehrData = 2;//dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  /*if (isnan(humidityData) || isnan(celData) || isnan(fehrData))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }*/

  // Compute heat index in Celsius (isFahreheit = false)
  float hicData = 666;//dht.computeHeatIndex(celData, humidityData, false);
  // Compute heat index in Fahrenheit (the default)
  float hifData = 999;//dht.computeHeatIndex(fehrData, humidityData);

  //Print to Serial monitor or Terminal of your chocice at 115200 Baud (Humidity, Temp C, Temp F, Heat Index C, Heat index F)
  Serial.print("Humidity: ");  Serial.print(humidityData);  Serial.print(" %\t");
  Serial.print("Temperature in Cel: ");  Serial.print(celData);  Serial.print(" *C ");
  Serial.print("Temperature in Fehr: ");  Serial.print(fehrData);  Serial.print(" *F\t");
  Serial.print("Heat index in Cel: ");  Serial.print(hicData);  Serial.print(" *C ");
  Serial.print("Heat index in Fehr: ");  Serial.print(hifData);  Serial.print(" *F\n");
    
  WiFiClient client;  //Instantiate WiFi object

    //Start or API service using our WiFi Client through PushingBox
    //PushingBox writes data to google-scrit which writes the data
    //into the google-speadsheet
   /* if (client.connect(WEBSITE, 80))
      { 
         client.print("GET /pushingbox?devid=" + devid
       + "&humidityData=" + (String) humidityData
       + "&celData="      + (String) celData
       + "&fehrData="     + (String) fehrData
       + "&hicData="      + (String) hicData
       + "&hifData="      + (String) hifData
         );

      client.println(" HTTP/1.1"); 
      client.print("Host: ");
      client.println(WEBSITE);
      client.println("User-Agent: ESP8266/1.0");
      client.println("Connection: close");
      client.println();
      }
      */
}
