
/** ********************************************************************************
 * Nerd-Monitor
 * ==================================================================================
 * Shows the total miners and total hashrate of whole NerdMiner of your local
 * network
 *
 * @EnteroPositivo
 * *********************************************************************************
 */

#include "main.hpp"

#include <AsyncUDP.h>
#include <M5Display.h>
#include <WiFi.h>

#include "ArrayList.h"
#include "nerdMonitor.h"

const char *ssid = "YOUR-WIFI";
const char *pass = "YOUR-WIFI-PASSWORD";

AsyncUDP udp;

void setup(void) {
    M5_BEGIN();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        M5.Lcd.fillScreen(TFT_RED);
        M5.Lcd.drawString("WIFI Failed", 2, 2);
        while (1) {
            delay(1000);
        }
    }

    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setTextFont(2);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.drawString("miners", 90, 35);
    M5.Lcd.drawString("KH/s", 98, 100);

    M5.Lcd.setTextFont(7);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);

    if (udp.listen(9876)) {
        udp.onPacket([](AsyncUDPPacket packet) {
            char *tmpStr = (char *)malloc(packet.length() + 1);
            memcpy(tmpStr, packet.data(), packet.length());
            tmpStr[packet.length()] = '\0';  // ensure null termination
            String received = String(tmpStr);
            free(tmpStr);  // Strign(char*) creates a copy so we can delete our

            if (received.startsWith("HR=")) {
                String hrate = received.substring(3);

                addOrUpdateNerd(packet.remoteIP().toString(), hrate.toFloat());
                nerdsStats();

                // printNerds();

                /*
                Serial.print("Stats:  TOT=");
                Serial.print(nerdsCount);
                Serial.print(" HR=");
                Serial.println(nerdsHashRate);
                */

                M5.Lcd.drawNumber(nerdsCount, 2, 2);
                M5.Lcd.drawNumber(nerdsHashRate, 2, 70);
            }
        });
    }
}

void loop(void) {
    M5.update();

    delay(1000);
}