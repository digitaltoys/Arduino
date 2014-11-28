#include <Arduino.h>
#include <SPI.h>
#include <IPAddress.h>
#include <WizFi250.h>
#include "WizFi250_tcp_client.h"

#define SSID			"Tomato24"
#define KEY			""
#define AUTH			"OPEN"
#define LOCAL_PORT		8080
#define REMOTE_PORT             80
IPAddress destIP	        (213,186,33,19);

boolean 	Wifi_setup = false;
boolean 	currentLineIsBlank = false;
boolean		IsSendHtmlResponse = false;
uint8_t		currentLineIsBlankCnt = 0;
String          HTTP_req;
int             Wifi_status = -1;
int             D8val = LOW;

int             lastConnected = false;
int             pinSW = 9;
int             valSW = LOW;
int             valSWLast = LOW;

char server[] = "api.pushingbox.com";
WizFi250 	        wizfi250;
WizFi250_TCP_Client	myClient(server, REMOTE_PORT);

void sendData(int val);

//The setup function is called once at startup of the sketch
void setup()
{
  // Add your initialization code here
  Serial.begin(9600);
  Serial.println("\r\nSerial Init");

  pinMode(pinSW, INPUT);
  digitalWrite(pinSW, HIGH);
  
  WizFi250_init();
}

// The loop function is called in an endless loop
void loop()
{
  //Add your repeated code here
  wizfi250.RcvPacket();

  if( myClient.available() )
  {
    char c = myClient.recv();
    if( c != NULL)
      Serial.print(c);
  }
  else
  {
    if( !myClient.getIsConnected() && lastConnected )
    {
      Serial.println();
      Serial.println("disconnecting.");
      myClient.stop();
    }

    valSW = digitalRead(pinSW);
    if(!myClient.getIsConnected() && valSWLast != valSW)
    {
      delay(200);
      valSW = digitalRead(pinSW);
      if (valSW != valSWLast)
      {
	myClient = WizFi250_TCP_Client(destIP, REMOTE_PORT);
	myClient.connect();
        sendData(valSW);
        valSWLast = valSW;
      }
    }

    lastConnected = myClient.getIsConnected();
  }
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

void sendData(int val)
{
  Serial.println(val);
  String TxData;

  if (val == HIGH)
    TxData = "GET /pushingbox?devid=[문열림ID] HTTP/1.1\r\nHost: api.pushingbox.com\r\nUser-Agent: Arduino\r\n\r\n\r\n";
  else
    TxData = "GET /pushingbox?devid=[문닫힘ID] HTTP/1.1\r\nHost: api.pushingbox.com\r\nUser-Agent: Arduino\r\n\r\n\r\n";
  
  Serial.print(TxData);
  myClient.send(TxData);
}

