#ifndef __SEGMENTED_DIGIT_DISPLAY_H
#define __SEGMENTED_DIGIT_DISPLAY_H

#define PIN_A (2)
#define PIN_B (3)
#define PIN_C (4)
#define PIN_D (5)
#define PIN_E (6)
#define PIN_F (7)
#define PIN_G (8)
#define PIN_D1 (9)
#define PIN_D2 (10)
#define PIN_D3 (11)
#define PIN_D4 (12)

#define SEGMENT_ON (LOW)
#define SEGMENT_OFF (HIGH)
#define DIGIT_SELECTED (HIGH)
#define DIGIT_NOT_SELECTED (LOW)

class SegmentedDigitDisplay{
    void create_digit(int digit){
        switch(digit){
            case 1:{
                digitalWrite(PIN_A, SEGMENT_OFF);   
                digitalWrite(PIN_B, SEGMENT_ON);   
                digitalWrite(PIN_C, SEGMENT_ON);   
                digitalWrite(PIN_D, SEGMENT_OFF);   
                digitalWrite(PIN_E, SEGMENT_OFF);   
                digitalWrite(PIN_F, SEGMENT_OFF);   
                digitalWrite(PIN_G, SEGMENT_OFF);    
                break;
            }
            case 2:{
                digitalWrite(PIN_A, SEGMENT_ON);   
                digitalWrite(PIN_B, SEGMENT_ON);   
                digitalWrite(PIN_C, SEGMENT_OFF);   
                digitalWrite(PIN_D, SEGMENT_ON);   
                digitalWrite(PIN_E, SEGMENT_ON);   
                digitalWrite(PIN_F, SEGMENT_OFF);   
                digitalWrite(PIN_G, SEGMENT_ON);    
                break;
            }
            case 3:{
                digitalWrite(PIN_A, SEGMENT_ON);   
                digitalWrite(PIN_B, SEGMENT_ON);   
                digitalWrite(PIN_C, SEGMENT_ON);   
                digitalWrite(PIN_D, SEGMENT_ON);   
                digitalWrite(PIN_E, SEGMENT_OFF);   
                digitalWrite(PIN_F, SEGMENT_OFF);   
                digitalWrite(PIN_G, SEGMENT_ON);    
                break;
            }
            case 4:{
                digitalWrite(PIN_A, SEGMENT_OFF);   
                digitalWrite(PIN_B, SEGMENT_ON);   
                digitalWrite(PIN_C, SEGMENT_ON);   
                digitalWrite(PIN_D, SEGMENT_OFF);   
                digitalWrite(PIN_E, SEGMENT_OFF);   
                digitalWrite(PIN_F, SEGMENT_ON);   
                digitalWrite(PIN_G, SEGMENT_ON);    
                break;
            }
            case 5:{
                digitalWrite(PIN_A, SEGMENT_ON);   
                digitalWrite(PIN_B, SEGMENT_OFF);   
                digitalWrite(PIN_C, SEGMENT_ON);   
                digitalWrite(PIN_D, SEGMENT_ON);   
                digitalWrite(PIN_E, SEGMENT_OFF);   
                digitalWrite(PIN_F, SEGMENT_ON);   
                digitalWrite(PIN_G, SEGMENT_ON);    
                break;
            }
            case 6:{
                digitalWrite(PIN_A, SEGMENT_ON);   
                digitalWrite(PIN_B, SEGMENT_OFF);   
                digitalWrite(PIN_C, SEGMENT_ON);   
                digitalWrite(PIN_D, SEGMENT_ON);   
                digitalWrite(PIN_E, SEGMENT_ON);   
                digitalWrite(PIN_F, SEGMENT_ON);   
                digitalWrite(PIN_G, SEGMENT_ON);    
                break;
            }
            case 7:{
                digitalWrite(PIN_A, SEGMENT_ON);   
                digitalWrite(PIN_B, SEGMENT_ON);   
                digitalWrite(PIN_C, SEGMENT_ON);   
                digitalWrite(PIN_D, SEGMENT_OFF);   
                digitalWrite(PIN_E, SEGMENT_OFF);   
                digitalWrite(PIN_F, SEGMENT_OFF);   
                digitalWrite(PIN_G, SEGMENT_OFF);    
                break;
            }
            case 8:{
                digitalWrite(PIN_A, SEGMENT_ON);   
                digitalWrite(PIN_B, SEGMENT_ON);   
                digitalWrite(PIN_C, SEGMENT_ON);   
                digitalWrite(PIN_D, SEGMENT_ON);   
                digitalWrite(PIN_E, SEGMENT_ON);   
                digitalWrite(PIN_F, SEGMENT_ON);   
                digitalWrite(PIN_G, SEGMENT_ON);    
                break;
            }
            case 9:{
                digitalWrite(PIN_A, SEGMENT_ON);   
                digitalWrite(PIN_B, SEGMENT_ON);   
                digitalWrite(PIN_C, SEGMENT_ON);   
                digitalWrite(PIN_D, SEGMENT_ON);   
                digitalWrite(PIN_E, SEGMENT_OFF);   
                digitalWrite(PIN_F, SEGMENT_ON);   
                digitalWrite(PIN_G, SEGMENT_ON);    
                break;
            }
            case 0:{
            }
            default:{
                digitalWrite(PIN_A, SEGMENT_ON);   
                digitalWrite(PIN_B, SEGMENT_ON);   
                digitalWrite(PIN_C, SEGMENT_ON);   
                digitalWrite(PIN_D, SEGMENT_ON);   
                digitalWrite(PIN_E, SEGMENT_ON);   
                digitalWrite(PIN_F, SEGMENT_ON);   
                digitalWrite(PIN_G, SEGMENT_OFF);    
                break;
            }
        }
    }

public:
    SegmentedDigitDisplay(){
    
    }

    void init_pins(){
        pinMode(PIN_A, OUTPUT);     
        pinMode(PIN_B, OUTPUT);     
        pinMode(PIN_C, OUTPUT);     
        pinMode(PIN_D, OUTPUT);     
        pinMode(PIN_E, OUTPUT);     
        pinMode(PIN_F, OUTPUT);     
        pinMode(PIN_G, OUTPUT);   
        pinMode(PIN_D1, OUTPUT);  
        pinMode(PIN_D2, OUTPUT);  
        pinMode(PIN_D3, OUTPUT);  
        pinMode(PIN_D4, OUTPUT);  
    }
    /*
        A
       ---
    F |   | B
      | G |
       ---
    E |   | C
      |   |
       ---
        D
    This example code is in the public domain.
    */
    void print_digit(const char arr[]){
        // For 4 digits, use a string such as: "1234"
        // For less digits, use a space in place of each digit
        // you dont want to be displayed
        digitalWrite(PIN_D1, DIGIT_NOT_SELECTED);
        digitalWrite(PIN_D2, DIGIT_NOT_SELECTED);
        digitalWrite(PIN_D3, DIGIT_NOT_SELECTED);
        digitalWrite(PIN_D4, DIGIT_NOT_SELECTED);
        for(int i=0;    i<4;    i++){
            switch(i){
                case 0:{
                    if(arr[i] != ' '){
                        digitalWrite(PIN_D1, DIGIT_SELECTED);
                        create_digit(arr[i] - '0');
                    }
                    break;
                }
                case 1:{
                    if(arr[i] != ' '){
                        digitalWrite(PIN_D2, DIGIT_SELECTED);
                        create_digit(arr[i] - '0');
                    }
                    break;
                }
                case 2:{
                    if(arr[i] != ' '){
                        digitalWrite(PIN_D3, DIGIT_SELECTED);
                        create_digit(arr[i] - '0');
                    }
                    break;
                }
                case 3:{
                    if(arr[i] != ' '){
                        digitalWrite(PIN_D4, DIGIT_SELECTED);
                        create_digit(arr[i] - '0');
                    }
                    break;
                }
            }
        }
    }

    void reset(){
        
    }

};

#endif // __SEGMENTED_DIGIT_DISPLAY_H