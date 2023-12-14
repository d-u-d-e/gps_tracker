#define TINY_GSM_MODEM_A6
#include <TinyGSM.h>

#define GSM_PWR_PIN 9
#define GSM_RST_PIN 6
#define GSM_LOW_PWR_PIN 5

void setup() {
    // put your setup code here, to run once:

    pinMode(GSM_PWR_PIN, OUTPUT);
    pinMode(GSM_RST_PIN, OUTPUT);
    pinMode(GSM_LOW_PWR_PIN, OUTPUT);
    digitalWrite(GSM_RST_PIN, LOW);
    digitalWrite(GSM_LOW_PWR_PIN, HIGH);
    digitalWrite(GSM_PWR_PIN, HIGH);

    SerialUSB.begin(9600);
    while(!SerialUSB){;}
    Serial1.begin(115200);

    //send a pulse to wake up the module
    digitalWrite(GSM_PWR_PIN, LOW);
    delay(3000);
    digitalWrite(GSM_PWR_PIN, HIGH);

    SerialUSB.println("Now turning on A9G!");
}

void loop() {
    TinyGsm modem(Serial1);
    TinyGsmClient gsm_client(modem);

    while (true){


        ;
    }


    while (Serial1.available() > 0) {
        SerialUSB.write(Serial1.read());
    }
    while (SerialUSB.available() > 0) {
        Serial1.write(SerialUSB.read());
        Serial1.flush();
    }
}