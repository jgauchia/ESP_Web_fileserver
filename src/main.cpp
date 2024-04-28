/**
 * @file main.cpp
 * @author Jordi Gauchía
 * @brief Web file server example
 * @version 0.1
 * @date 2024-04
 */

/**
 * @brief App name version and revision showed in webserver
 * 
 */
#define APP "YOUR APP NAME"
#define VERSION 0.1
#define REVISION 0

#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <SPI.h>
#include <FS.h>
#include <SD.h>

#include "hal.h"
#include "sdcard.h"
#include <webpage.h>
#include <webserver.h>

static const char *ssidName = "your SSID";
static const char *ssidPW = "your password";

unsigned long networkTimeout = 10 * 1000;

void setup()
{
  initSD();
  initSPIFFS();

  unsigned long startingTime = millis();
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  vTaskDelay(100);

  log_i("%s", ssidName);
  WiFi.begin(ssidName, ssidPW);

  while (WiFi.status() != WL_CONNECTED && (millis() - startingTime) < networkTimeout)
  {
    vTaskDelay(250);
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    log_i("%s", WiFi.localIP().toString());
    configureWebServer();
    server.begin();
  }
}

void loop()
{
}
