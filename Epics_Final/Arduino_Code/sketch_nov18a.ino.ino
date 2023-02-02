#include<Wire.h>
#include<MPU6050_tockn.h>
#if defined(ESP32)
#include<WiFi.h>
#elif defined(ESP8266)
#include<ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include<Wire.h>
#include<Adafruit_Sensor.h>
#include <NTPClient.h>
#include <WiFiUdp.h>


#define FIREBASE_HOST "epics-1d096-default-rtdb.firebaseio.com"      
#define FIREBASE_AUTH "ply4wQFlRPbHEYEPuORZOqcsDpILxXzXQaPgE5u7"

//Provide the token generation process info

#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define WIFI_SSID "OPPO A31"
#define WIFI_PASSWORD "123456789"

#define API_KEY "AIzaSyBv531nf_0cZbhrKhkLcV3xDTuqqb_Yc_I"

#define USER_EMAIL "mgowrisankar5877@gmail.com"
#define USER_PASSWORD "123456"

#define DATABASE_URL "https://epics-1d096-default-rtdb.firebaseio.com"

//Firebase Objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

//USER ID VARIABLE

String uid;

//Database Main Path

String databasePath;

String Xpath = "/X";
String Ypath ="/Y";
String Zpath ="/Z";
String timePath="timestamp";

String parentPath;

FirebaseJson json;



WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");


int timestamp;

MPU6050 mpu6050(Wire);
unsigned long timer = 0;

 
 
double x;
double y;
double z;

unsigned long sendDataPrevMillis =0;
unsigned long timerDelay =18000;
 
unsigned long epochTime; 

// Function that gets current epoch time
unsigned long getTime() {
  timeClient.update();
  unsigned long now = timeClient.getEpochTime();
  return now;
}


void setup(){
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print("Not connected-");
  }

 
  Serial.println("WiFi Connected");
  Serial.begin(115200);
  //initWiFi();
  timeClient.begin();


  config.api_key = API_KEY;

  auth.user.email= USER_EMAIL;
  auth.user.password=USER_PASSWORD;

  config.database_url=DATABASE_URL;

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  config.token_status_callback = tokenStatusCallback;

  config.max_token_generation_retry = 5;

  Firebase.begin(&config, &auth);


  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
  // Print user UID
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.println(uid);

  // Update database path
  databasePath = "/UsersData/" + uid + "/readings";
  
}
void loop(){


    mpu6050.update();
 if (Firebase.ready() && (millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();

      //Get current timestamp
      timestamp = getTime();
      Serial.print ("time: ");
      Serial.println (timestamp);
      parentPath= databasePath + "/" + String(timestamp);
      Serial.println("AngleX= ");
      Serial.println(mpu6050.getAngleX());
      Serial.println("AngleY= ");
      Serial.println(mpu6050.getAngleY());
      Serial.println("AngleZ= ");
      Serial.println(mpu6050.getAngleZ());
      Serial.println("-----------------------------------------");

      json.set(Xpath.c_str(), String(mpu6050.getAngleX()));
      json.set(Ypath.c_str(),String(mpu6050.getAngleY()));
      json.set(Zpath.c_str(),String(mpu6050.getAngleZ()));  
      json.set(timePath.c_str(),String(timestamp));   

      Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
      timer = millis();
  }

}
