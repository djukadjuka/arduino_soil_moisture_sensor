#ifndef __LED_MODULE_H
#define __LED_MODULE_H

#include "Arduino.h"

#define LED_PROG_PIN (5)

class LEDModule{

    unsigned long last_inner_update_time;
    unsigned long on_time;
    unsigned long off_time;

public:

    void init_pins(){
        // LED configuration
        pinMode(LED_PROG_PIN, OUTPUT);
    }

    void set_last_inner_update_time(unsigned long time){
        // Last updated time only for leds - used for toggling led diodes
        this->last_inner_update_time = time;
    }

    void set_on_time(unsigned long on_time){
        // Sets for how long the led light should be turned on in toggle
        this->on_time = on_time;
    }

    void set_off_time(unsigned long off_time){
        // Sets for how long the led light should be turned off in toggle
        this->off_time = off_time;
    }

    void set_on_off_time(unsigned long on_time, unsigned long off_time){
        // Combination of how long the led light should be on / off
        this->set_on_time(on_time);
        this->set_off_time(off_time);
    }

    void reset(){
        // Resets led diodes last inner update time 
        this->set_last_inner_update_time(0);
    }

    LEDModule(){
        this->set_last_inner_update_time(millis());
    }

    void led_on(int led_id){
        // Turns on led diode by ID
        digitalWrite(led_id, HIGH);
    }
    
    void led_off(int led_id){
        // Turns on led diode by ID
        digitalWrite(led_id, LOW);
    }
    
    void on_prog(){
        // Example turning on led diode by defined ID
        this->led_on(LED_PROG_PIN);
    } 
    
    void off_prog(){
        // Example turning off led diode by defined ID
        this->led_off(LED_PROG_PIN);
    }
    
    short is_led_on(int led_id){
        // Checks if some led is on
        if(digitalRead(led_id)){
            return TRUE;
        }
        return FALSE;
    }

    void toggle_led(int led_id){
        // Toggles led irregardles of time
        if(is_led_on(led_id) == TRUE){
            led_off(led_id);
        }else{
            led_on(led_id);
        }
    }

    void off_all(){
        // Turns off all leds
        this->off_prog();
    }

    void on_all(){
        // Turns on all leds
        this->on_prog();
    }

    unsigned short toggle_diff(unsigned long current_millis, unsigned long on_time, unsigned long off_time, int led_id){
        // Returns TRUE if led is toggled,
        // Toggles leds based on time irreeguardless of states
        short led_state = is_led_on(led_id);

        unsigned long update_time;
        if(led_state == FALSE){
            update_time = off_time;
        }else{
            update_time = on_time;
        }
        
        if(current_millis - this->last_inner_update_time >= update_time){
            this->toggle_led(led_id);
            this->last_inner_update_time = current_millis;
            return TRUE;
        }else{
            return FALSE;
        }
    }

};  

#endif // __LED_MODULE_H