/*
Jumpers Settings

 -----------
| 1 | 2 | 3 |                         : (1,2) Disable Stay Away, 
 -----------                            (2,3) En Stay Away [Default]
| 4 | 5 | 6 |                         : (4,5) Disable Dimmable, 
 ----------------                       (5,6) Enable Dimmable [Default]
| 7 | 8 | 9 | 10 |                    : (7,8) Enable Left, 
 ----------------                       (8,9) Enable Both [Default], 
                                        (9,10) Enable Right

*/




#include <NewPing.h>

#define DEBUG_MODE          true

//Pins
#define LAMP_PIN            3
#define EN_RIGHT_SENSOR     4
#define EN_DIMMABLE_PIN     5
#define EN_MODE_PIN         6
#define EN_LEFT_SENSOR      7

//Constant
#define NONE               -1
#define BOTH               -1
#define LEFT                0
#define RIGHT               1
#define INCREASE            0
#define DECREASE            1

// Sonar
#define SONAR_NUM           2
#define MAX_DISTANCE        100 //Cm
#define DISTANCE_THRESHOLD  30  //Cm

#if DEBUG_MODE

String SensDirecton[SONAR_NUM];

#endif


//Jumper Config
int8_t   EnabledSide;
bool     EnableDimmable;
bool     EnableStayAway;

// Lamp
const int16_t   MinBrightness = 10;
bool            IncreaseBrightness;
int16_t         LampBrightness;
int8_t          LampState = NONE;
const uint8_t   LampStep = 5;
const uint16_t  LampOnDelay = 5000;
unsigned long   LampOnMillis;
unsigned long   Millis;

// Sonar
const uint8_t   ErrorTolerance = 2;
bool            IsCarDetect[SONAR_NUM];
float           Distances[SONAR_NUM];
float           PrevDistances[SONAR_NUM];
uint16_t        GetClose[SONAR_NUM];
uint16_t        StayAway[SONAR_NUM];
uint8_t         ErrorCount[SONAR_NUM];

NewPing Sonar[SONAR_NUM] = {
    NewPing(12, 11, MAX_DISTANCE),  //Trigger, echo, and max distance. 
    NewPing(10, 9, MAX_DISTANCE), 
};


void setup() {
    #if DEBUG_MODE
    
    SensDirecton[LEFT] = String("Left");
    SensDirecton[RIGHT] = String("Right");
    Serial.begin(115200);
    #endif
    
    pinMode(LAMP_PIN, OUTPUT);
    pinMode(EN_MODE_PIN, INPUT_PULLUP);
    pinMode(EN_DIMMABLE_PIN, INPUT_PULLUP);
    pinMode(EN_LEFT_SENSOR, INPUT_PULLUP);
    pinMode(EN_RIGHT_SENSOR, INPUT_PULLUP);

    read_jumpers();

    #if DEBUG_MODE
    print_jumper();
    #endif
}

void loop() {

    //Read Handle
    read_distances();

    // Modes
    if (EnableStayAway) non_timer_mode();
    else                timer_mode();

    // Lamp Brightness Handler
    brightness_handle();

    // Lamp Handler
    if (EnableDimmable) dimmable();
    else                non_dimmable();

    // Debug
    #if DEBUG_MODE
    print_status();
    #endif
    
}


// Non Timer Mode
void non_timer_mode(){
    for (uint8_t i = 0; i < SONAR_NUM; i++){
        if (Distances[i] > 0 && Distances[i] < DISTANCE_THRESHOLD){
            if (PrevDistances[i] < 1){
                PrevDistances[i] = Distances[i];
            } else {
                if      (PrevDistances[i] >  Distances[i]) GetClose[i]++;
                else if (PrevDistances[i] <  Distances[i]) StayAway[i]++;
            }
        } else if (PrevDistances[i] > 0){                
            ErrorCount[i]++;
            if (ErrorCount[i] > ErrorTolerance){
                if      (GetClose[i] > StayAway[i]) LampState = INCREASE;
                else if (GetClose[i] < StayAway[i]) LampState = DECREASE;                    

                #if DEBUG_MODE
                if (LampState == INCREASE)      Serial.println("Car Get close from "+SensDirecton[i]);
                else if (LampState == DECREASE) Serial.println("Car Stay away from "+SensDirecton[i]);

                Serial.print("Away:" + String(StayAway[i]));
                Serial.print("\tClose:" + String(GetClose[i]));
                Serial.println();   
                #endif
                
                // reset distance status
                GetClose[i] = 0;
                StayAway[i] = 0;
                PrevDistances[i] = 0;
            }
        }
    }
}
// Timer mode
void timer_mode(){
    Millis = millis();

    if (Millis >= LampOnMillis + LampOnDelay){
        LampState = DECREASE;
        LampOnMillis = 0;
    }

    for (uint8_t i = 0; i < SONAR_NUM; i++){
        if (Distances[i] > 0 && Distances[i] < DISTANCE_THRESHOLD){
            LampState = INCREASE;
            LampOnMillis = Millis;

            #if DEBUG_MODE
            Serial.println("Trigger From "+SensDirecton[i]);            
            #endif
        }
    }
}

// Brightness Handle
void brightness_handle(){
    if (LampState != NONE){
        if (LampState == INCREASE) {
            LampBrightness += LampStep;
            LampBrightness = LampBrightness > 255 ? 255 : LampBrightness;
        } else if (LampState == DECREASE){
            LampBrightness -= LampStep;
            LampBrightness = LampBrightness < 0 ? 0 : LampBrightness;
        }
        if (LampBrightness <= 0 || LampBrightness >= 255){
            LampState = NONE;
        }
    }
}
// Dimmable Handle
void dimmable(){
    if (LampBrightness < MinBrightness) 
        analogWrite(LAMP_PIN, MinBrightness);
    else                           
        analogWrite(LAMP_PIN, LampBrightness);
}
void non_dimmable(){
    if (LampBrightness > 0)
        digitalWrite(LAMP_PIN, HIGH);
    else
        digitalWrite(LAMP_PIN, LOW);
}

// Read Distances
void read_distances(){
    if (EnabledSide == BOTH){
        for(uint8_t i = 0; i < SONAR_NUM; i++){
            unsigned long echoTime = Sonar[i].ping_median(3, MAX_DISTANCE);
            Distances[i] = NewPing::convert_cm(echoTime);
        }
    } else {
        unsigned long echoTime = Sonar[EnabledSide].ping_median(3, MAX_DISTANCE);
        Distances[EnabledSide] = NewPing::convert_cm(echoTime);
        Distances[EnabledSide == LEFT ? RIGHT : LEFT] = 0;
    }
}
// Read Jumpers
void read_jumpers(){
    EnabledSide   = !digitalRead(EN_LEFT_SENSOR) ? LEFT : 
                    !digitalRead(EN_RIGHT_SENSOR) ? RIGHT : BOTH;
    EnableDimmable = digitalRead(EN_DIMMABLE_PIN);
    EnableStayAway = digitalRead(EN_MODE_PIN);

    // Disable Stay Away if one of side was diabled
    if (EnabledSide != BOTH) EnableStayAway = false;
}


// Print Jumpers State
void print_jumper(){
    String enabledSide = EnabledSide == LEFT ? "LEFT" : 
                         EnabledSide == RIGHT ? "RIGHT" : "BOTH";
    Serial.print("Dimmable:"+String(EnableDimmable ? "Enabled" : "Disabled"));
    Serial.print("\tStayAway:"+String(EnableStayAway ? "Enabled" : "Disabled"));
    Serial.println("\tEn_Side:"+enabledSide);
}
// Print Current Status
void print_status(){
    Serial.print("State:"+String(LampState));
    Serial.print("\tBrightness:"+String(LampBrightness));
    Serial.print("\tleft:"+String(Distances[LEFT]));
    Serial.println("\tright:"+String(Distances[RIGHT]));
}
