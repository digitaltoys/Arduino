#include <Arduino.h>
#include <SPI.h>
#include <IPAddress.h>
#include <WizFi250.h>
#include <WizFi250_tcp_server.h>


#define SSID			"Tomato24"
#define KEY			""
#define AUTH			"OPEN"
#define LOCAL_PORT		8080

boolean 	Wifi_setup = false;
boolean 	currentLineIsBlank = false;
boolean		IsSendHtmlResponse = false;
WizFi250 	wizfi250;
uint8_t		currentLineIsBlankCnt = 0;
String          HTTP_req;
int             Wifi_status = -1;
int             D8val = LOW;

WizFi250_TCP_Server myServer(LOCAL_PORT);

void sendHeader();
void sendData();

//The setup function is called once at startup of the sketch
void setup()
{
  // Add your initialization code here
  Serial.begin(19200);
  Serial.println("\r\nSerial Init");
  
  for(int i=2; i<13; i++)
  {
    pinMode(i, OUTPUT);
  }

  WizFi250_init();
}

// The loop function is called in an endless loop
void loop()
{
  //Add your repeated code here
    /*String buf;
    for(int j=0;j<3000;j++)
    {
      buf += "*";
      Serial.println(buf);
      Serial.println(j);
    }
    */  
    wizfi250.RcvPacket();

    if( myServer.isListen() != true )
    {
      myServer.listen();
    }

    if( myServer.available())
    {
      if( IsSendHtmlResponse == true )
      {
        IsSendHtmlResponse=false;
        myServer.stop();
      }

      char c = myServer.recv();
      if( c != NULL )
      {
        Serial.print((char)c);
        HTTP_req += String(c);
        if(c == '\n' && currentLineIsBlank)
        {
          sendHeader();
          sendData();
          currentLineIsBlank = false;
          IsSendHtmlResponse = true;
          HTTP_req = "";
        }

        if(c == '\n')
        {
//          Serial.print("len:");
//          Serial.println(HTTP_req.length());
          String param = GetParam(HTTP_req);
          if (param == "d8=1")
          {
            D8val = HIGH;
            digitalWrite(8,D8val);
          }
          else if (param == "d8=0")
          {
            D8val = LOW;
            digitalWrite(8,D8val);
          }

          HTTP_req = "";
          currentLineIsBlank = true;
        }
        else if(c != '\r')
        {
          currentLineIsBlank = false;
        }
      }
    }
}

String GetParam(String buf)
{
  if (buf.startsWith("GET /?") != true) return String("");
  
  return buf.substring(6, buf.indexOf(" ",7));
}

void WizFi250_init()
{
  wizfi250.begin();
  wizfi250.setDebugPrint(4);
  wizfi250.hw_reset();

  wizfi250.sync();
  wizfi250.setDhcp();

  while(Wifi_status != 0)
  {
   Wifi_status = wizfi250.join(SSID,KEY,AUTH);
    delay(2000);
  }
}

void sendHeader()
{
  String TxData;

  TxData = "HTTP/1.1 200 OK\r\n";
  TxData += "Content-Type: text/html\r\n";
  TxData += "Connection: close\r\n";
  //TxData += "Refresh: 5\r\n";
  TxData += "\r\n";
  TxData += "<!DOCTYPE HTML>\r\n";
  TxData += "<html>\r\n";
  TxData += "<head>\r\n";
  myServer.send(TxData);
  TxData = "";

  //TxData = 
  char html[256] =
  "<link rel='stylesheet' href='http://code.jquery.com/ui/1.11.2/themes/smoothness/jquery-ui.css'>"\
  "<script src='http://code.jquery.com/jquery-1.10.2.js'></script>"\
  "<script src='http://code.jquery.com/ui/1.11.2/jquery-ui.js'></script>\r\n"\
//  "\r\n";
//  myServer.send(TxData);

//  TxData = 
  "<script>"\
      "$(function() {"\
         "$('a')"\
            ".button()"\
            ".click(function( event ) {"\
               "event.preventDefault();"\
            "});"\
      "});"\
   "</script>"\
            "</head>\r\n"\
            " ";
  myServer.send(html);
//  myServer.send(TxData);
}

void sendData()
{
  String TxData, buf;
  char temp_value[100] = {0};
  TxData += "<body>\r\n";
/*
  for(int analogChannel=0; analogChannel<0; analogChannel++)
  {
    int sensorReading = analogRead(analogChannel);
    sprintf( temp_value, "analog%d is %d <br />\r\n", analogChannel, sensorReading);
    TxData += temp_value;
  }
*/  
  for(int dPin=8; dPin<9; dPin++)
  {
    int val = digitalRead(dPin);
    sprintf( temp_value, 
      "<h1>D%d is %d <br/><a href='/?d%d=%d'>LED%d is %s</a><br /></h1>\r\n",
      dPin, D8val, dPin, 1-D8val, dPin, (D8val)? "On":"Off");
    //sprintf( temp_value, "digitalPin%d<br />\r\n",digitalPin);
    TxData += temp_value;
  }
  myServer.send(TxData);
  TxData = "";

  TxData += "</body>\r\n";
  TxData += "</html>\r\n";
  TxData += "\r\n";
  TxData += "\r\n";

  myServer.send(TxData);
}


