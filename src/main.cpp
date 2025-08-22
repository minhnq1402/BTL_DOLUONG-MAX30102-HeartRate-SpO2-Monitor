#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "MAX30105.h" 
#include "spo2_algorithm.h" 


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

MAX30105 particleSensor;
const byte RATE_SIZE = 4; 
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0; 
float beatsPerMinute;
int beatAvg;
const int bufferLength = 50; 
uint32_t irBuffer[bufferLength];
uint32_t redBuffer[bufferLength];
int bufferIndex = 0;
int32_t spo2;
int8_t validSPO2;
int32_t heartRate;
int8_t validHeartRate;
const int GRAPH_DATA_SIZE = 100; 
int graphData[GRAPH_DATA_SIZE];
int graphIndex = 0;
bool fingerDetected = false;



void drawGraph() {
    display.drawRect(26, 43, 102, 21, SSD1306_WHITE);

    for (int i = 0; i < GRAPH_DATA_SIZE - 1; i++) {
        int y1 = map(graphData[i], 70000, 100000, 63, 44);
        int y2 = map(graphData[i + 1], 70000, 100000, 63, 44);
        
        y1 = constrain(y1, 44, 63);
        y2 = constrain(y2, 44, 63);

        display.drawLine(i + 27, y1, i + 28, y2, SSD1306_WHITE);
    }
}

void setup() {
    Serial.begin(115200); 
    Wire.begin(21, 22); 
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("OLED init failed")); 
        while (1); 
    }


    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(15, 25);
    display.println("Welcome");
    display.display();
    delay(1000);

    display.clearDisplay();
    display.setCursor(0, 25);
    display.println("Heart Monitor"); 
    display.display();
    delay(2000);


    if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) { 
        Serial.println(F("Không tìm thấy MAX30102. Kiểm tra dây nối!")); 
        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(0, 0);
        display.println("SENSOR FAILED"); 
        display.display();
        while (1);
    }
    Serial.println("MAX30102 SUCCESS");

    particleSensor.setup(); 
    particleSensor.setPulseAmplitudeRed(0x0A); 
    particleSensor.setPulseAmplitudeGreen(0); 

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(25, 25);
    display.println("SETUP"); 
    display.display();
    delay(1000);


    for (int i = 0; i < GRAPH_DATA_SIZE; i++) {
        graphData[i] = 0;
    }
}


void loop() {
    uint32_t irValue = particleSensor.getIR(); 
    uint32_t redValue = particleSensor.getRed(); 


    if (irValue < 50000) { 
        if (fingerDetected) {
            bufferIndex = 0;
            for(int i = 0; i < bufferLength; i++) {
                irBuffer[i] = 0;
                redBuffer[i] = 0;
            }
        }
        fingerDetected = false;
        display.clearDisplay();
        display.setTextSize(2);
        display.setCursor(0, 25);
        display.println("PLACE FINGER");
        display.display();
        delay(200); 
        return;
    } else {
        if (!fingerDetected) {
            fingerDetected = true; 
            display.clearDisplay();
            display.setTextSize(2);
            display.setCursor(10, 25);
            display.println("Reading..."); 
            display.display();
        }
    }

    for (int i = 0; i < GRAPH_DATA_SIZE - 1; i++) {
        graphData[i] = graphData[i + 1];
    }
    graphData[GRAPH_DATA_SIZE - 1] = irValue;


    if (fingerDetected) {
        irBuffer[bufferIndex] = irValue;
        redBuffer[bufferIndex] = redValue;
        bufferIndex++;

        if (bufferIndex == bufferLength) { 
            maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate); 
            bufferIndex = 0; 
        }
    }
    

    display.clearDisplay(); 
    display.setTextSize(2);
    display.drawChar(0, 0, (char)3, SSD1306_WHITE, SSD1306_BLACK, 2); 
    display.setCursor(25, 5);

    if (validHeartRate && heartRate >= 40 && heartRate <= 160) { 
        display.print(heartRate);
    } else {
        display.print("--");
    }
    display.setTextSize(1);
    display.print(" bpm");

    display.setTextSize(2);
    display.setCursor(25, 25);
    if (validSPO2 && spo2 >= 80 && spo2 <= 100) { 
        display.print(spo2);
    } else {
        display.print("--"); 
    }
    display.setTextSize(1);
    display.print(" %");

    drawGraph();
    display.display(); 

    particleSensor.nextSample();

    delay(20); 
}