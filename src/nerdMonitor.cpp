#include <nerdMonitor.h>

#include "ArrayList.h"

ArrayList<nerdInfo> nerdMiners;

int nerdDisconnected = -1;
int nerdsCount = 0;
float nerdsHashRate = 0;

//- Exists= return array position  - No exists= return -1
int existsNerd(String IP) {
    for (int i = 0; i < nerdMiners.size(); i++) {
        const nerdInfo x = nerdMiners.get(i, {});
        if (x.IP == IP)
            return i;
    }

    return -1;
}

void addOrUpdateNerd(String IP, float hr) {
    int index = -1;

    nerdInfo ne;
    ne.IP = IP;
    ne.HashRate = hr;
    ne.TimeStampt = millis();

    index = existsNerd(IP);
    if (index >= 0) {  //- exists
        nerdMiners.set(index, ne);
    } else {  //- No exists
        nerdMiners.add(ne);
    }
}

//- Computes totals
void nerdsStats() {
    //- some nerd disconnected before => delete
    if (nerdDisconnected >= 0) {
        nerdMiners.removeAt(nerdDisconnected);
        nerdDisconnected = -1;
    }

    nerdsCount = nerdMiners.size();
    nerdsHashRate = 0;

    for (int i = 0; i < nerdMiners.size(); i++) {
        nerdInfo n = nerdMiners.get(i, {});
        nerdsHashRate += n.HashRate;
        if (((millis() - n.TimeStampt) / 1000) > 10) {
            // Serial.println("-Discon--");
            nerdDisconnected = i;
        }
    }
}

//- For debugging
void printNerds() {
    for (int i = 0; i < nerdMiners.size(); i++) {
        nerdInfo n = nerdMiners.get(i, {});
        Serial.print(n.IP + "HR[" + String(n.HashRate) + "]" +
                     " T=" + (String)((millis() - n.TimeStampt) / 1000));
        Serial.println(i);
    }
    Serial.println();
}
