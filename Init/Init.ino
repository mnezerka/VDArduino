//New board initializer
//Use this sketch to fill the EEPROM memory with appropriate values
//Vitezslav Dostal | started 03.03.2017

#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <TickerScheduler.h>

const char* sensor       = "<5-uppercase-chars>";  //Sensor indentification                               //memory 361-380
const char* key          = "<enter-server-key>";   //API write key                                        //memory 381-400
const char* adminLogin   = "admin";                //Update firmware login                                //memory 401-420
const char* adminPasswd  = "admin";                //Update firmware password                             //memory 421-440
const char* wifiLogin    = "<enter-wifi-login>";   //Wifi login (projects without WiFi manager only)      //memory 441-460
const char* wifiPasswd   = "<enter-wifi-passwd>";  //Wifi password (projects without WiFi manager only)   //memory 461-480
const char  serialUsed   = true;                   //Console connected                                    //memory 481
const char  displayUsed  = true;                   //Display connected                                    //memory 482
const char  dallasUsed   = true;                   //Dallas sensor connected                              //memory 483
const char  dhtUsed      = true;                   //DHT sensor connected                                 //memory 484
const char  dhtType      = 11;                     //Type of DHT sensor                                   //memory 485
const char  bmeUsed      = false;                  //BME280 sensor connected                              //memory 486
const char  outsideUsed  = false;                  //Get readings from external site                      //memory 487
const char* outsidePath  = "/fetch/outside.php";   //Outside temperature path                             //memory 488-507
const char  bmePins      = 0;                      //BME580 sensor on alternative pins                    //memory 508
const char  reporting    = true;                   //Report readings to server                            //memory 509
const char  interval     = 1;                      //Next measure (in minutes)                            //memory 510
const char  sleepMode    = false;                  //Deep sleep between measures                          //memory 511

      char* host   = "initial";
const int   offset = 360;

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

TickerScheduler ts(5);
int address = 0;
byte value, value1, value2, value3, value4, value5, value6, value7, value8, value9, value10;

template <class T> int EEPROM_writeAnything(int ee, const T& value)
{
  const byte* p = (const byte*)(const void*)&value;
  unsigned int i;
  for (i = 0; i < sizeof(value); i++)
    EEPROM.write(ee++, *p++);
  return i;
}

template <class T> int EEPROM_readAnything(int ee, T& value)
{
  byte* p = (byte*)(void*)&value;
  unsigned int i;
  for (i = 0; i < sizeof(value); i++)
    *p++ = EEPROM.read(ee++);
  return i;
}

struct config_t
{
  char  sensor[20];
  char  key[20];           
  char  adminLogin[20];
  char  adminPasswd[20];
  char  wifiLogin[20];
  char  wifiPasswd[20];
  char  serialUsed;
  char  displayUsed;
  char  dallasUsed;
  char  dhtUsed;
  char  dhtType;
  char  bmeUsed;
  char  outsideUsed;
  char  outsidePath[20];
  char  bmePins;
  char  reporting;
  char  interval;
  char  sleepMode;
} memory, data;

void setup()
{
  Serial.begin(115200);
  EEPROM.begin(512);
  
  read();
  write();

  setupWifi();
  setupWebServer(host);

  ts.add(1, 500, showMemory, 0, false);
}

void write()
{
  strcpy(memory.sensor,      sensor);
  strcpy(memory.key,         key);
  strcpy(memory.adminLogin,  adminLogin);
  strcpy(memory.adminPasswd, adminPasswd);
  strcpy(memory.wifiLogin,   wifiLogin);
  strcpy(memory.wifiPasswd,  wifiPasswd);
  memory.serialUsed        = serialUsed;
  memory.displayUsed       = displayUsed;
  memory.dallasUsed        = dallasUsed;
  memory.dhtUsed           = dhtUsed;
  memory.dhtType           = dhtType;
  memory.bmeUsed           = bmeUsed;
  memory.outsideUsed       = outsideUsed;
  strcpy(memory.outsidePath, outsidePath);
  memory.bmePins           = bmePins;
  memory.reporting         = reporting;
  memory.interval          = interval;
  memory.sleepMode         = sleepMode;

  EEPROM_writeAnything(offset, memory);
  EEPROM.commit();
}

void read()
{
  EEPROM_readAnything(offset, data);
  Serial.println("=====================");
  Serial.println("1   5    10   15   20");
  Serial.println("=====================");
  Serial.println(data.sensor);
  Serial.println(data.key);
  Serial.println(data.adminLogin);
  Serial.println(data.adminPasswd);
  Serial.println(data.wifiLogin);
  Serial.println(data.wifiPasswd);
  Serial.println(data.outsidePath);
  Serial.println("=====================");
}

void setupWifi()
{
  WiFiManager wifiManager;
  wifiManager.setTimeout(300);
  wifiManager.autoConnect("ESP8266 Initialization");
}

void setupWebServer(char host[])
{
  MDNS.begin(host);
  httpUpdater.setup(&httpServer, "/");
  httpServer.begin();
  MDNS.addService("http", "tcp", 80);
  Serial.printf("For firmware update use http://%s.local in your browser\n", host);
}

void loop()
{
  ts.update();
  httpServer.handleClient();  
}

void showMemory(void* context)
{ 
  value1  = EEPROM.read(address+0);
  value2  = EEPROM.read(address+1);
  value3  = EEPROM.read(address+2);
  value4  = EEPROM.read(address+3);
  value5  = EEPROM.read(address+4);
  value6  = EEPROM.read(address+5);
  value7  = EEPROM.read(address+6);
  value8  = EEPROM.read(address+7);
  value9  = EEPROM.read(address+8);
  value10 = EEPROM.read(address+9);

  Serial.print(address);
  Serial.print("\t");
  Serial.print("|");
  Serial.print("\t");
  Serial.print(value1, DEC);
  Serial.print("\t");
  Serial.print(value2, DEC);
  Serial.print("\t");
  Serial.print(value3, DEC);
  Serial.print("\t");
  Serial.print(value4, DEC);
  Serial.print("\t");
  Serial.print(value5, DEC);
  Serial.print("\t");
  Serial.print(value6, DEC);
  Serial.print("\t");
  Serial.print(value7, DEC);
  Serial.print("\t");
  Serial.print(value8, DEC);
  Serial.print("\t");
  Serial.print(value9, DEC);
  Serial.print("\t");
  Serial.print(value10, DEC);
  Serial.println();

  address = address + 10;
  
  if (address >= 512)
  {
    address = 0;
    read();
  }
}
