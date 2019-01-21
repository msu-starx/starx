////////////////////////////////////////
// MSU STARX ExoSuit                  //
// Firmware v3 (January-2019)         //
// Arduino Micro (ATmega32U4)         //
// All rights reserved                //
////////////////////////////////////////

// Arduino Micro Pinouts
/////////////////////////////////////////////////////////////////////////
// ADC: A0-A5, A6-A11 (4, 6, 8, 9, 10, 12) [10-bit resolution, 0~1023] //
// PWM: 3, 5, 6, 9, 10, 11, 13                                         //
/////////////////////////////////////////////////////////////////////////

// Arduino Parameters
// ----- Serial Communication (USB) -----
const int BAU_RAT = 1000000; // Serial baud rate (bps)
// ----- Pulse Width Modulation (PWM) -----
const int PWM_PIN[] = {5, 9, 10, 11}; // PWM pins
const int PWM_CPS = 8; // Clock prescaler (1, 8, 64, 256, 1024)
const double PWM_FRQ = 50; // Wave frequency (Hz)
// ----- Pulse Width Modulation (PWM) -----
const int ADC_NUM = 12; // Number of ADC pins available
const int PIN_NUM = 10; // Number of GPIO pins available
// ----- Packet Settings -----
const int PAC_PAR = 5; // Maximum number of parameters in a packet
const char PAC_DEL = ','; // Packet delimiter
const char PAC_TER = '\r'; // Packet terminator

// Arduino Commands
const String SendADCValuesString = "ADC";
const String SetGPIODirectionString = "PIN";
const String SetGPIODirectionInString = "IN";
const String SetGPIODirectionOutString = "OUT";
const String SetPWMDutyCycleString = "PWM";
const String SetFullStopString = "STP";
const String ErrorMessageString = "ERROR";
const String StartMessageString = "START";

// Arduino Messages
String packet = "";
String parameter[PAC_PAR] = {};

///////////////
// Functions
///////////////

// Sends the ADC values as 12 separate 10-bit words
void sendADC() {
    int pin_adc[ADC_NUM];
    String message = "";
    for (int i = 0; i < ADC_NUM; i++) {
        pin_adc[i] = analogRead(i);
        message += String(pin_adc[i]);
        if (i < ADC_NUM - 1) {
            message += PAC_DEL;
        }
        else {
            message += PAC_TER;
        }
    }
    Serial.print(message);
}

// Sets the PWM duty cycles in percentage values
void setPWM(String parameter[]) {
    int duty_cycle[4];
    String message = "";
    for (int i = 0; i < sizeof(duty_cycle) / sizeof(int); i++) {
        duty_cycle[i] = parameter[i + 1].toInt();
        message += String(duty_cycle[i]);
        if (i < sizeof(duty_cycle) / sizeof(int) - 1) {
            message += PAC_DEL;
        }
        else {
            message += PAC_TER;
        }
    }
    // Sets PWM duty cycle
    OCR3A = ICR3 * (duty_cycle[0] / 100.0); // Pin 5
    OCR1A = ICR1 * (duty_cycle[1] / 100.0); // Pin 9
    OCR1B = ICR1 * (duty_cycle[2] / 100.0); // Pin 10
    OCR1C = ICR1 * (duty_cycle[3] / 100.0); // Pin 11
    Serial.print(message);
}

// Sets specific GPIO pins direction and state
void setGPIO(String parameter[]) {
    // TODO
}

// Sets a full stop
void setStop() {
    // TODO
}

// Start function
void setup() {
    // SETUP 1 - Serial Communication
    Serial.begin(BAU_RAT);
    Serial.print(StartMessageString + PAC_TER);

    // SETUP 2 - Pulse Width Modulation (PWM)
    // ----- Set PWM Pins -----
    pinMode(5, OUTPUT); // Set PWM Output Pin
    pinMode(9, OUTPUT); // Set PWM Output Pin
    pinMode(10, OUTPUT); // Set PWM Output Pin
    pinMode(11, OUTPUT); // Set PWM Output Pin

    // ----- Reset TCCR Values -----
    TCCR1A = 0; // Reset Timer/Counter Control Register 1 - Channel A
    TCCR1B = 0; // Reset Timer/Counter Control Register 1 - Channel B
    TCCR3A = 0; // Reset Timer/Counter Control Register 3 - Channel A
    TCCR3B = 0; // Reset Timer/Counter Control Register 3 - Channel B

    // ----- Set Clock Prescaler Value [TCCR1] -----
    //TCCR1B |= (1 << CS10); // Set Clock Prescaler = 1
    TCCR1B |= (1 << CS11); // Set Clock Prescaler = 8
    //TCCR1B |= (1 << CS11) | (1 << CS10); // Set Clock Prescaler = 64
    //TCCR1B |= (1 << CS12); // Set Clock Prescaler = 256
    //TCCR1B |= (1 << CS12) | (1 << CS10); // Set Clock Prescaler = 1024

    // ----- Set Clock Prescaler Value [TCCR3] -----
    //TCCR3B |= (1 << CS30); // Set Clock Prescaler = 1
    TCCR3B |= (1 << CS31); // Set Clock Prescaler = 8
    //TCCR3B |= (1 << CS31) | (1 << CS30); // Set Clock Prescaler = 64
    //TCCR3B |= (1 << CS32); // Set Clock Prescaler = 256
    //TCCR3B |= (1 << CS32) | (1 << CS30); // Set Clock Prescaler = 1024

    // ----- Set Non-Inverting OR Inverting Mode [TCCR1] -----
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << COM1C1); // Set Non-inverting PWM Mode
    //TCCR1A |= (1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0) | (1 << COM1C1) | (1 << COM1C0); // Set Inverting PWM Mode

    // ----- Set Non-Inverting OR Inverting Mode [TCCR3] -----
    TCCR3A |= (1 << COM3C1); // Set Non-inverting PWM Mode
    //TCCR3A |= (1 << COM3C1) | (1 << COM3C0); // Set Inverting PWM Mode

    // ----- Set Fast PWM Mode ------
    TCCR1A |= (1 << WGM11); // Fast-PWM (Mode 14, TOP = ICRn) - Part I
    TCCR1B |= (1 << WGM13) | (1 << WGM12); // Fast-PWM (Mode 14, TOP = ICRn) - Part II
    ICR1 = F_CPU / (PWM_CPS * PWM_FRQ) - 1; // Fast-PWM (Set Input Capture Register)
    TCCR3A |= (1 << WGM31); // Fast-PWM (Mode 14, TOP = ICRn) - Part I
    TCCR3B |= (1 << WGM33) | (1 << WGM32); // Fast-PWM (Mode 14, TOP = ICRn) - Part II
    ICR3 = F_CPU / (PWM_CPS * PWM_FRQ) - 1; // Fast-PWM (Set Input Capture Register)

    // ----- Set Phase and Frequency Correct PWM Mode ------
    //TCCR1B |= (1 << WGM13); // PFC-PWM (Mode 8, TOP = ICRn)
    //ICR1 = F_CPU / (2 * PWM_CPS * PWM_FRQ); // PFC-PWM (Set Input Capture Register)
    //TCCR3B |= (1 << WGM33); // PFC-PWM (Mode 8, TOP = ICRn)
    //ICR3 = F_CPU / (2 * PWM_CPS * PWM_FRQ); // PFC-PWM (Set Input Capture Register)
}

// Main loop
void loop() {
    if (Serial.available() > 0) {
        // Store incoming packet
        packet = Serial.readStringUntil(PAC_TER);

        // Split packet into substrings
        if (packet.indexOf(PAC_DEL) != -1) {
            int location;
            for (int i = 0; i < PAC_PAR; i++) {
                location = packet.indexOf(PAC_DEL);
                if (location != -1) {
                    parameter[i] = packet.substring(0, location);
                    packet = packet.substring(location + 1, packet.length());
                }
                else {
                    if (packet.length() > 0)
                        parameter[i] = packet;
                }
            }
        }
        else {
            parameter[0] = packet;
        }

        ///////////////
        // Commands
        ///////////////

        if (parameter[0] == SendADCValuesString) {
            sendADC();
        }
        else if (parameter[0] == SetGPIODirectionString) {
            setGPIO(parameter);
        }
        else if (parameter[0] == SetPWMDutyCycleString) {
            setPWM(parameter);
        }
        else if (parameter[0] == SetFullStopString) {
            setStop();
        }
        else {
            Serial.print(ErrorMessageString + PAC_TER);
        }
    }
}
