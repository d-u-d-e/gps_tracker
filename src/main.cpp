#define TINY_GSM_MODEM_A6
#define TINY_GSM_DEBUG SerialUSB
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

    modem.init("1234");
    bool connected = modem.waitForNetwork(600000L);

    if (connected){
        SerialUSB.println("I am connected to GSM network!");
    }

    bool tcp_connected = gsm_client.connect("142.251.143.195", 80);

    if (tcp_connected){
        SerialUSB.println("I am connected to TCP server!");
            uint8_t buf[1048];

        gsm_client.write("GET / HTTP/1.1");
        int bytes_read = 0;
        while ((bytes_read = gsm_client.read(buf, 1024)) > 0){
            buf[bytes_read] = 0;
            SerialUSB.print((char *) buf);
        }
    }
    else{
        SerialUSB.println("Failed to connecto via TCP!");
    }
    
    while (true){
        while (Serial1.available() > 0) {
            SerialUSB.write(Serial1.read());
        }
        while (SerialUSB.available() > 0) {
            Serial1.write(SerialUSB.read());
            Serial1.flush();
        }
    }
}