#include <WiFi.h>



void loop_sg90() {

  delay(10000);
  Serial.println("sg90_start!");
  //reading data from thing speak
  aConst_sg90 = readTSData_sg90( channelID_sg90, dataFieldOne_sg90 );
  Serial.println(aConst_sg90);
  
  if(aConst_sg90==888)
  {    
  
  
  //貼馬達CODE

  //myservo.attach(13);  // 設定要將伺服馬達接到哪一個PIN腳
  
//1
  myservo.write(90);  //旋轉到0度，就是一般所說的歸零
  delay(1000); 
  Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
 
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
//2
  Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
 
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
//3
  Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
 
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
//4
  Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
 
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
//5
  Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
 
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
//6
 Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
 
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
//7
  Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
 
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");
//8
  Serial.print("去"); // 順時針轉 4S
  myservo.write(10); // 旋轉到180度//110度 8圈 180度14圈  一圈一顆
  delay(4000);              
 
  myservo.write(180); //後退 逆時針轉 2S
  delay(2000);
  Serial.print("回");


//變回555
    int s = 555;
    myservo.write(90);
    
    if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                          {  
                            
                             client.print(String("GET ") + resource + apiKey_sg90 + "&field3=" + s +    
                              " HTTP/1.1\r\n" +
                              "Host: " + server + "\r\n" + 
                              "Connection: close\r\n\r\n");
  
                          }
      
    
   }
          
 
 


}


float readTSData_sg90( long TSChannel, unsigned int TSField ) {

  float data_sg90 =  ThingSpeak.readFloatField( TSChannel, TSField, readAPIKey_sg90 );
  Serial.println( " 跑函式Data read from ThingSpeak: " + String( data_sg90 ) );
  return data_sg90;

 
  


}
