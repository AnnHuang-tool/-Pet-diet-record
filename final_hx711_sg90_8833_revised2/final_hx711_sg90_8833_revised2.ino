//引入涵式庫
#include <ThingSpeak.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESP32Servo.h>
#include <HX711.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


//連WIFI網路
const char* ssid     = "28N4F";
const char* pass = "22730119";

//[PINand顯示設置]
// Ain1 and Ain2 DRV8833 pins.
#define  AIN3 = 2;
#define  AIN1 = 14;


//OLED設定
#define OLED_RESET     21
Adafruit_SSD1306 display(128, 32, &Wire, -1);

//HX711設定
const int DT_PIN = 25;
const int SCK_PIN = 26;
const int scale_factor = -207; //比例參數，從校正程式中取得
HX711 scale;


//HX711_宣告
float h;  // h=天秤讀到的值
float h2=0; //宣告暫存的變數h2存舊值 新值=h
float h3; //宣告暫存的變數h3 存變化值(h-h2)
float sum=0; //宣告一個變數存總計

//HX711_計時器
unsigned long starttime=millis(); // 計時器值放入的變數
int i=0;       //計數(0~13) 存到相應的位置
float save[13];  //陣列 存值0~13
float total1=0;   //每筆存值相加
float total2=0;
float avg=0;   //每七天平均相減
unsigned long delaytime=86400000; //one day


//DRV8833_Thingspeak
char* server = "api.thingspeak.com";
unsigned long channelID_8833 = 1472641;
char* readAPIKey_8833 = "AN6606R6C6BP2ZAA";
unsigned int dataFieldOne_8833 = 3; 
String apiKey_8833 = "Z16K62EFTWVIX3BC";     //  Enter your Write API key from ThingSpeak
char* resource = "/update?api_key=";


//HX711_Thingspeak
String apiKey_711 = "7Z46IGZR87OY7FE9";     //  Enter your Write API key from ThingSpeak
String apiKey_7112 = "JGPCK8ZD7I1WKHYH"; 


//SG90_Thingspeak
unsigned long channelID_sg90 = 1485980;
char* readAPIKey_sg90 = "NVDDOQG9QXK4PNHU";
unsigned int dataFieldOne_sg90 = 3; 
String apiKey_sg90 = "JGPCK8ZD7I1WKHYH";     //  Enter your Write API key from ThingSpeak


//sg90_初始變數
float aConst_sg90 = 2.25E-02 ;


//drv8833_初始變數
float aConst_8833 = 2.25E-02 ;


// 建立SERVO物件
Servo myservo;  


// 建立WiFi_client_連THINGSPEAK收值
WiFiClient client;


//setup_各程式
void setup() {
 Serial.begin(115200); //開監控視窗
 pinMode(2, OUTPUT); // 設定飼料馬達電控開關接到哪一個PIN腳
 pinMode(14, OUTPUT); // 設定要將沉水馬達電控開關接到哪一個PIN腳

 Serial.println("Connecting to ");
 Serial.println(ssid);
 WiFi.begin(ssid, pass);//連網路
   //connectWiFi();
  while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
      ThingSpeak.begin( client );


    //啟動oled
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    
    
    //印天秤資訊+啟動
    Serial.println("Initializing the scale");
    scale.begin(DT_PIN, SCK_PIN);
    Serial.println("Before setting up the scale:"); 
    Serial.println(scale.get_units(5), 0);  //未設定比例參數前的數值
    scale.set_scale(scale_factor);       // 設定比例參數
    scale.tare();               // 歸零

    Serial.println("After setting up the scale:"); 

    Serial.println(scale.get_units(5), 0);  //設定比例參數後的數值

    Serial.println("Readings:");  //在這個訊息之前都不要放東西在電子稱上
    
    Serial.println("測試ing"); 
    myservo.attach(13);  // 設定要將MG90接到哪一個PIN腳
}


//loop_執行各程式
void loop() {
 loop_sg90();
 loop_drv8833(); 
 loop_hx711();

}
