  #include <WiFi.h>
  #include <ESP32Servo.h>
  #include <HTTPClient.h>
 
  int led=2;
  int ir=5;
  Servo motor;
 
  const char* ssid="Mad";
  const char* password="12345";
 
  const char* apiRoute="https://ir-machine-learning.makeskilled.live/predict?ir=";
 
  void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid,password);
    while(WiFi.status()!=WL_CONNECTED){
      Serial.print(".");
      delay(500);
    }
    Serial.println("WIFI CONNECTED");
    pinMode(ir,INPUT);
    pinMode(led,OUTPUT);
    motor.attach(23);
  }
 
  void loop() {
    int m=digitalRead(ir);
 
    Serial.print("Sensor: ");
    Serial.println(m);
 
    delay(1000);
 
    int value=getDataFromAPI(m);
    if(value==1){
      motor.write(90);
      delay(5000);
      motor.write(0);
      digitalWrite(led,1);
    } else if (value==2){
      motor.write(0);
      digitalWrite(led,0);
    }
    delay(4000);
  }
 
  int getDataFromAPI(int m){
    if(WiFi.status()==WL_CONNECTED){
      HTTPClient http;
      http.begin(apiRoute+String(m));
      int responseCode=http.GET();
      if(responseCode>0){
        String response=http.getString();
        Serial.print("API Response: ");
        Serial.println(response);
        http.end();
        if(response=="Object"){
          return(1);
        } else if(response=="No Object"){
          return(2);
        } else {
          return(0);
        }
      }
    }
  }
