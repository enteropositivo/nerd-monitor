#ifndef NERD_MONITOR_H
#define NERD_MONITOR_H

#include <Arduino.h>

//- Information of every NerdMiner
struct nerdInfo
{
    String IP = "";
    unsigned long TimeStampt = 0;
    float HashRate = 0;
};

extern int nerdsCount;
extern float nerdsHashRate;

void addOrUpdateNerd(String IP, float hr);
int existsNerd(String IP);
void printNerds();
void nerdsStats();

#endif  // NERD_MONITOR_H