#include <WiFi.h>

void loop_hx711() {
                           
      
      Serial.print("starttime:"); 
      Serial.println(starttime);  
      Serial.println(scale.get_units(10), 0); //天秤取10次平均

      scale.power_down();             // 天平進入睡眠模式
      delay(1000);
      scale.power_up();               // 天平結束睡眠模式

      h=scale.get_units(5);      //放天秤值進變數h
      
      Serial.print("now : ");
      Serial.println(h);
      
      if((h-h2)==h){  //如果重量值等於上一個重量值=初值 沒變化值 h3(變化值)=0
        h3=0;
        h2=h; 
        Serial.print("h3:");
        Serial.println(h3);
        Serial.print("h2:");
        Serial.println(h2);
       
            if (client.connect(server,80)){                           // "184.106.153.149" or api.thingspeak.com //傳初值
                            
                             client.print(String("GET ") + resource + apiKey_711 + "&field1=" + h + "&field2=" +  h3 + //傳現值於頻道1 差值頻道2
                             " HTTP/1.1\r\n" +
                             "Host: " + server + "\r\n" + 
                             "Connection: close\r\n\r\n");
  
                             Serial.print("now : ");
                             Serial.print(h);
                             Serial.print(" g, discrepancy: ");
                             Serial.print(h3);
                             Serial.println("g. Send to Thingspeak.");
                             client.stop();
                             Serial.println("Waiting...");
                                          }                       
                      }
      
      
      else if(millis()-starttime>delaytime){      //如果有變化值每過30s 記錄一次並歸零
         
        float avg1;  //1~7天 sum平均
        float absavg1; //avg1取絕對值
        float avg2;  //8~14天 sum平均
        float absavg2; //avg2取絕對值
        float absavg; //avg取絕對值
        save[i]=sum; //存檔
        sum=0;  //歸零
        Serial.print ("sum_avg:") ;
        Serial.println(sum) ;
        Serial.print ("count:") ;
        Serial.print (i) ;
        Serial.print ("=") ;
        Serial.println (save[i]) ;
  
        i++;  //累計資料數
        if(i>13){  //只存0~13(14筆)
          i=0;
                }

        for(int x = 0; x<7; x++ ){

           total1 = total1+save[x];
           avg1=total1/7;
           absavg1=abs(avg1);
           
           Serial.print ("total1:") ;
           Serial.println (total1) ;
           Serial.print ("avg1:") ;
           Serial.print (avg1) ;
                                  }
                                  
        for(int x = 7; x<14; x++ ){

          total2 = total2+save[x];
          avg2=total2/7;
          absavg2=abs(avg2);
          
          Serial.print ("total2:") ;
          Serial.println (total2) ;
          Serial.print ("avg2:") ;
          Serial.println (avg2); 
          

                                 }

       
        avg=avg1-avg2;
        absavg=abs(avg);
        Serial.print ("avg:") ;
        Serial.println (avg) ;  
        

          if (client.connect(server,80)){                    //   "184.106.153.149" or api.thingspeak.com    //連線到THINGSPEAK
                                 
                             client.print(String("GET ") + resource + apiKey_7112 +  "&field1=" + absavg1 + "&field2=" +  absavg2 + "&field4=" +  absavg + //傳前七天於頻道1 後七天頻道2 平均差值頻道4
                              " HTTP/1.1\r\n" +
                              "Host: " + server + "\r\n" + 
                              "Connection: close\r\n\r\n");
                              
                             Serial.print("avg_thingspeak : ");
                             Serial.println(avg);
                           
                                        }
        starttime=millis();


                            }
 
      else {      //如果有變化值未到時間繼續讀值傳值
      h3=h-h2;
      h2=h;                               //放值進去h2(舊值)
      Serial.print("h2:"); 
      Serial.println(h2);                 //傳變化值 

      
        if(-h3>2){                     // 減少超過2g傳值到THINGSPEAK  (變化超過2)
          Serial.print("h3:"); 
          Serial.println(h3);  
          sum=h3+sum;               //累計重量變化值
            
          if (client.connect(server,80)){   //   "184.106.153.149" or api.thingspeak.com    //連線到THINGSPEAK
                            
                            
                             client.print(String("GET ") + resource + apiKey_711 + "&field1=" + h + "&field2=" +  h3 + "&field3=" + sum  + //傳現值於頻道1 差值頻道2 總計傳頻道3
                              " HTTP/1.1\r\n" +
                              "Host: " + server + "\r\n" + 
                              "Connection: close\r\n\r\n");
  
                             Serial.print("now : ");
                             Serial.print(h);
                             Serial.print(" g, discrepancy: ");
                             Serial.print(h3);
                             Serial.println("g. Send to Thingspeak.");
                             Serial.print("sum:"); 
                             Serial.println(sum);
                             float displaysum =abs(sum);  //負值轉正值
                             

                             
                             client.stop();
                             Serial.println("Waiting...");
                             

                             // OLED Display 
                              display.clearDisplay();   
                              display.setTextSize(1);
                              display.setTextColor(WHITE);
                              display.setCursor(0,8); display.println("TODAY EAT");
                              display.setCursor(0,24); display.println(displaysum);
                              display.setCursor(28,24); display.println("g");
                              display.display();
                              delay(1000); 
                                          }
             
                 }
      
      
    
                 // thingspeak needs minimum 15 sec delay between updates
                   delay(15000); 
        
 
        }

                  }
