#include <WiFi.h>


//loop
void loop_drv8833() {

  delay(10000);
  Serial.println("drv8833_start!");
  //reading data from thing speak
  aConst_8833 = readTSData_8833( channelID_8833, dataFieldOne_8833 ); //跑128行涵式_並把channelID_8833, dataFieldOne_8833 值丟進去
  Serial.println(aConst_8833);

  //


  if(aConst_8833==333)
  {    


   // put your main code here, to run repeatedly:
  //myservo.attach(13);  // 設定要將伺服馬達接到哪一個PIN腳
  digitalWrite(2, HIGH);//5V 電源開啟
  digitalWrite(14, HIGH);//5V 電源開啟
  delay(50);

  //1
  myservo.write(90);  //旋轉到0度，就是一般所說的歸零
  delay(1000); 
  Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
  digitalWrite(14, LOW); //電源關閉
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
//2
  Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
  digitalWrite(14, HIGH);//電源開啟
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
//3
  Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
  digitalWrite(14, LOW);//電源關閉
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
//4
  Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
  digitalWrite(14, HIGH);//電源開啟
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
//5
  Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
  digitalWrite(14, LOW);//電源關閉
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
//6
 Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
  digitalWrite(14, HIGH);//電源開啟
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
//7
  Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
  digitalWrite(14, LOW);//電源關閉
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
//8
  Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
  digitalWrite(14, HIGH);//電源開啟
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
  Serial.println("STOP");
  // Put the motor in forward:
  digitalWrite(2, LOW);//電源關閉
  digitalWrite(14, LOW);//電源關閉
  // Wait to see the effect:
  delay(5000);
  Serial.println("start");
  // Put the motor in forward:


//變回666
    int h = 666;
    myservo.write(90);

    if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                          {  

                             client.print(String("GET ") + resource + apiKey_8833 + "&field3=" + h +    
                              " HTTP/1.1\r\n" +
                              "Host: " + server + "\r\n" + 
                              "Connection: close\r\n\r\n");

                          }


   }





}


float readTSData_8833( long TSChannel, unsigned int TSField ) {

  float data_8833 =  ThingSpeak.readFloatField( TSChannel, TSField, readAPIKey_8833 );
  Serial.println( " 跑函式Data read from ThingSpeak: " + String( data_8833 ) );
  return data_8833;





}
