//Sends temperature and humidity over WiFi to specified server via GET/POST request
//Chip ESP8266 + sensor DHT11
//Vitezslav Dostal | started 27.01.2017

#include <TimeLib.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>
#include <DHT.h>
#include <WiFiManager.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include "SSD1306Brzo.h"
#include "OLEDDisplayUi.h"
#include "images.h"
#include "Timer.h"

      String sensor          = "<from-eeprom>";           //Sensor indentification
const String host_prefix     = "ESP8266";                 //Hostname prefix
const char*  server          = "arduino.vitadostal.cz";   //Processing server
      String key             = "<from-eeprom>";                        //API write key
const String firmware        = "v1.04 / 4 Mar 2017" ;     //Firmware version

const int    interval        = 60;                        //Next measure on success (in seconds)
const int    pause           = 0.1;                       //Next measure on error (in seconds)
const int    attempts        = 5;                         //Number of tries

const char*  update_path     = "/firmware";               //Firmware update path
      String update_username = "<from-eeprom>";           //Firmware update login
      String update_password = "<from-eeprom>";           //Firmware update password

int          screenW         = 128;
int          screenH         = 64;
int          clockCenterX    = screenW / 2;
int          clockCenterY    = ((screenH - 16) / 2) + 16; // top yellow part is 16 px height
int          clockRadius     = 23;

const int    offset          = 360;

#define ONE_WIRE_BUS_PIN     0                            //Dallas DS18B20 DATA
#define DISPLAY_SDA          1                            //SSD1306 SCL
#define DHT_PIN              2                            //DHT11 DATA
#define DISPLAY_SCL          3                            //SSD1306 SDA
#define DHT_TYPE DHT11
#define DISPLAY_ADDRESS 0x3c

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;
DHT dht(DHT_PIN, DHT_TYPE);
SSD1306Brzo display(DISPLAY_ADDRESS, DISPLAY_SDA, DISPLAY_SCL);
OLEDDisplayUi ui (&display);
OneWire oneWire(ONE_WIRE_BUS_PIN);
DallasTemperature dallas(&oneWire);
Timer t;
String host;

template <class T> int EEPROM_readAnything(int ee, T& value)
{
  byte* p = (byte*)(void*)&value;
  unsigned int i; 
  for (i = 0; i < sizeof(value); i++)
    *p++ = EEPROM.read(ee++);
  return i;
}

void setup() {    
  //Initialization
  Serial.begin(115200);
  delay(10);
  dht.begin();
  delay(10);
  dallas.begin();
  delay(10);
  Serial.println();
  Serial.println();

  //Read memory
  Serial.println("Reading EEPROM memory...");
  readMemory();

  //Info memory
  infoMemory();
  
  //Hostname
  host = host_prefix + sensor;
  host.toLowerCase();
  Serial.println("My hostname is " + host);
    
  //WiFi manager
  Serial.println("Starting WiFi manager...");
  setupWifi();

  //Server
  Serial.println("Starting WebServer...");
  setupWebServer();

  //Display
  Serial.println("Starting display...");
  //setupDisplay();

  t.every(interval * 1000, takeReading, 0);
  //t.every(    0.01 * 1000, handleServer, 0);
  //t.every(    0.01 * 1000, handleDisplay, 0);
}

void infoMemory()
{  
  //Total memory
  Serial.print("Total memory ");
  uint32 size = spi_flash_get_id();
  size = size / 1024;
  size = round(size);
  Serial.print(size);
  Serial.println(" kB");
    
  //Fre space
  Serial.print("Free space available ");
  uint32_t space = ESP.getFreeSketchSpace();
  space = space / 1024;
  space = round(space);
  Serial.print(space);
  Serial.println(" kB");
  Serial.println();
}

void readMemory()
{
  struct config
  {
    char sensor[20];
    char key[20];           
    char login[20];
    char passwd[20];
  } memory; 
  
  EEPROM.begin(512);
  EEPROM_readAnything(offset, memory);
  if (sensor          == "<from-eeprom>") sensor          = memory.sensor;
  if (key             == "<from-eeprom>") key             = memory.key;
  if (update_username == "<from-eeprom>") update_username = memory.login;
  if (update_password == "<from-eeprom>") update_password = memory.passwd;
}

void setupWifi()
{
  WiFiManager wifiManager;
  wifiManager.setTimeout(300);
  wifiManager.autoConnect("ESP8266 Settings");
}

void setupWebServer()
{
  char login[20], passwd[20];
  
  MDNS.begin(host.c_str());
  httpUpdater.setup(&httpServer, update_path, update_username.c_str(), update_password.c_str());
  httpServer.on("/", HTTP_GET, []() {
    httpServer.sendHeader("Connection", "close");
    httpServer.sendHeader("Access-Control-Allow-Origin", "*");
    httpServer.send(200, "text/html", deviceStatus());
  });
  httpServer.begin();
  MDNS.addService("http", "tcp", 80);
}

void setupDisplay()
{
  //Display WiFi icon
  ui.setTargetFPS(60);
  ui.setActiveSymbol(activeSymbol);
  ui.setInactiveSymbol(inactiveSymbol);
  ui.setIndicatorPosition(TOP);
  ui.setIndicatorDirection(LEFT_RIGHT);
  ui.setFrameAnimation(SLIDE_LEFT);
  FrameCallback frames[] = {digitalClockFrame, temperatureFrame};
  ui.setFrames(frames, 2);
  ui.init();
  display.flipScreenVertically();
}

void loop()
{
  t.update();
  httpServer.handleClient();
}

void handleServer(void* context)
{
  httpServer.handleClient();
}

void handleDisplay(void* context)
{
  int remainingTimeBudget = ui.update();
  if (remainingTimeBudget > 0) delay(remainingTimeBudget);
}

void digitalClockFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y)
{
  String timenow = String(hour()) + ":" + twoDigits(minute()) + ":" + twoDigits(second());
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_24);
  display->drawString(clockCenterX + x , clockCenterY + y, timenow );
}

void temperatureFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y)
{
  display->drawString(64 + x, 32 + y, "20.8 °C");
}

void takeReading(void* context)
{
  Serial.println();

  float t_dal, h_dal, t_dht, h_dht;
  readSensorDallas (t_dal, h_dal);
  readSensorDHT (t_dht, h_dht);

  if (isnan(t_dal)) {
    t_dal = t_dht;
    t_dht = NAN;
  }

  //Push data to server
  Serial.println("Connecting to server " + String(server) + "...");
  WiFiClient client;
  if (client.connect(server, 80))
  {
    Serial.println("Server connected");

    String params;
    params += "key=" + key;
    params += "&sensor=" + sensor;
    if (!isnan(t_dal)) params += "&value1=" + String(t_dal); //Dallas
    if (!isnan(h_dht)) params += "&value2=" + String(h_dht); //DHT
    if (!isnan(t_dht)) params += "&value3=" + String(t_dht); //DHT

    //GET request
    /*client.println("GET /add.php?" + params + " HTTP/1.1");
      client.println("Host: " + String(server));
      client.println("User-Agent: ArduinoWiFi/1.1");
      client.println("Connection: close");
      client.println();*/

    //POST request
    String request;
    request += "POST /add.php HTTP/1.1\n";
    request += "Host: " + String(server) + "\n";
    request += "User-Agent: ArduinoWiFi/1.1\n";
    request += "Connection: close\n";
    request += "Content-Type: application/x-www-form-urlencoded\n";
    request += "Content-Length: ";
    request += (params.length() + 2);
    request += "\n\n";
    request += params;
    request += "\r\n\r\n";
    client.println(request);

    //See response
    /*delay(100);
      while(client.available())
      {
      String line = client.readStringUntil('\r');
      Serial.print(line);
      }*/

    Serial.println("Data sent");
  }
  client.stop();

  Serial.println("Waiting for " + String(interval) + " seconds...");
  //delay(interval*1000);
}

String deviceStatus() {
  String info;

  info  = "<!DOCTYPE HTML><html><head><title>ESP8266 device</title><meta charset='utf-8' />";
  info += "<style>html{font-family: sans-serif}</style></head>";
  info += "<body><h1>ESP8266 device</h1>";

  info += ("<b>Sensor</b>: ");
  info += (sensor + " [<a href='//" + server + "/?sensor=" + sensor + "'>graph</a>]");
  info += ("<br />");

  info += ("<b>Hostname:</b> ");
  info += (host + ".local [<a href='//" + host + ".local'>open</a>]");
  info += ("<br />");

  info += ("<b>IP address:</b> ");
  info += (WiFi.localIP().toString());
  info += ("<br />");

  byte mac[6];

  info += ("<b>MAC address:</b> ");
  info += mac2String(WiFi.macAddress(mac));
  info += ("<br />");

  info += ("<b>WiFi network (SSID):</b> ");
  info += (WiFi.SSID());
  info += ("<br />");

  info += ("<b>Signal strength (RSSI):</b> ");
  info += (WiFi.RSSI());
  info += (" dBm");
  info += ("<br />");

  float t1, h1, t2, h2;
  readSensorDallas(t2, h2);
  info += ("<b>DS18B20 Reading:</b> " + String(t2) + "&#8451; ");
  info += ("<br />");
  readSensorDHT(t1, h1);
  info += ("<b>DHT11 Reading:</b> " + String(t1) + "&#8451; " + String(h1) + "%");
  info += ("<br />");

  info += ("<b>Firmware:</b> ");
  info += (firmware);
  info += (" [<a href='/firmware'>update</a>]");
  info += ("<br />");

  info += ("<b>Author:</b> ");
  info += ("vita@vitadostal.cz");
  info += ("<br />");
  info += ("<br />");

  info += ("<b>Schema</b><ul style='padding-top: 0; margin-top: 0;'>");
  info += ("<li><b>GPIO0:</b> Dallas DS18B20 data &amp; pull-up resistor 4K7&#8486;</li>");
  info += ("<li><b>GPIO1:</b> SSD1306 display SDA (I2C serial data)</li>");
  info += ("<li><b>GPIO2:</b> DHT11 data &amp; pull-up resistor 10K&#8486;</li>");
  info += ("<li><b>GPIO3:</b> SSD1306 display SCL (I2C serial clock)</li>");
  info += ("</ul>");

  info += ("<img alt='Schema' src='//arduino.vitadostal.cz/img/ESP01.png' />");
  info += ("</body></html>");

  return info;
}

void readSensorDHT(float &t, float &h)
{
  int i = 1;

  h = dht.readHumidity();
  t = dht.readTemperature();

  while (isnan(h) || isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");

    if (i == attempts) return;

    delay(pause * 1000);
    h = dht.readHumidity();
    t = dht.readTemperature();
    i++;
  }

  Serial.println("DHT | Measured data: " + String(t) + "°C " + String(h) + "%");
}

void readSensorDallas(float &t, float &h)
{
  int i;

  dallas.requestTemperatures();
  t = dallas.getTempCByIndex(0);
  i = round (t * 10);
  t = i / 10.0;

  if (t == -127)
  {
    t = NAN;
    Serial.println("Failed to read from Dallas sensor!");
    return;
  }

  h = 0;

  Serial.println("Dallas | Measured data: " + String(t) + "°C ");
}

String mac2String(byte ar[]) {
  String s;
  for (byte i = 0; i < 6; ++i)
  {
    char buf[3];
    sprintf(buf, "%2X", ar[i]);
    s += buf;
    if (i < 5) s += ':';
  }
  return s;
}

String twoDigits(int digits) {
  if (digits < 10) {
    String i = '0' + String(digits);
    return i;
  }
  else {
    return String(digits);
  }
}
