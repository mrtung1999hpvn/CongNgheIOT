/* Controlling LED using Firebase console by CircuitDigest(www.circuitdigest.com) */
#include <ESP8266WiFi.h>                                                
#include <FirebaseArduino.h>  
#include <Wire.h>                

#define FIREBASE_HOST "bt-battatled.firebaseio.com"                         //host tren firebase 
#define FIREBASE_AUTH "goUvbdVQ7T9pwMluRuoV0K1CnBP5L4ZLoUkWIYD1"      //Auth tren firebase google               
#define WIFI_SSID "NguyenThanh"                                   // Ten Wifi       
#define WIFI_PASSWORD "12356789"                                    //Pass wifi

String ThaoTac = "";    // Biến nhận dữ liệu
String LED_D4 = "";   // Biến nhận dữ liệu
int chanD2 = D2;  // Sử dụng chân D2 đấu vào dương của đèn và âm đèn vào chân GND -> 2
int chanD3 = D3;  // Sử dụng chân D3 đấu vào dương của đèn và âm đèn vào chân GND -> 3
int chanD4 = D4;  // Sử dụng chân D4 đấu vào dương của đèn và âm đèn vào chân GND -> 8

void setup() {
  Serial.begin(9600);
  Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */
  delay(1000);
  pinMode(chanD2, OUTPUT);      
  pinMode(chanD3, OUTPUT);
  pinMode(chanD4, OUTPUT);              
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                      //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                                      //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase
  
}

void loop() {
  
  ThaoTac = Firebase.getString("DieuKhienXe/ThaoTac"); //  Lấy dữ liệu của đèn LED_D3 BatTatLed/LED_D3
  Serial.print(ThaoTac);
  Wire.beginTransmission(8); /* begin with device address 8 */
  if(ThaoTac=="up")
  {
    Wire.write("up");
  }
  if(ThaoTac=="down"){
    Wire.write("down");
  }
  if(ThaoTac=="left")
  {
    Wire.write("left");
  }
  if(ThaoTac=="right")
  {
    Wire.write("right");
  }
  if(ThaoTac=="stop")
  { 
    Wire.write("stop");
  }
  if (ThaoTac=="auto")
  {
    Wire.write("auto"); 
  } 
  if(ThaoTac=="servoleft")
  {
    Wire.write("servoleft"); 
  }
  if(ThaoTac=="servoright")
  {
    Wire.write("servoright");
  }
  Wire.endTransmission();    /* stop transmitting */
   Wire.requestFrom(8, 13); /* request & read data of size 13 from slave */
 while(Wire.available()){
    char c = Wire.read();
  Serial.print(c);
 }
 Serial.println();
  
}
