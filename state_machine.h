#ifndef __STATE_MACHINE_H
#define __STATE_MACHINE_H

#include "lcd_module.h"
#include "led_module.h"
#include "soil_moisture_sensor_module.h"
#include "segmented_digit_display.h"
// #include "segmented_digit_display2.h"

#define BACKGROUND_CONTROLLER_PIN (13)
#define RESET_BUTTON_RESET_STATE (HIGH)

//////////////////////////////////////////////////////////////////////////////////////////////////
// STATES
//////////////////////////////////////////////////////////////////////////////////////////////////
// SS -> State Start
// MK -> Master Key

#define SS_RESET_ALL_MODULES            (0)
#define S_RESET_ALL_MODULES_DELAY       (1)
#define S_RESET_ALL_MODULES_REAL        (2)
#define SS_PRINT_MODULES_RESETTING      (3)
#define S_PRINT_MODULES_RESETTING_DELAY (4)

#define SS_IDLE_STATE (100)

#define SS_SENSOR_READING (200)
#define S_SENSOR_READING_DELAY (201)

//////////////////////////////////////////////////////////////////////////////////////////////////
// LCD STRINGS
//////////////////////////////////////////////////////////////////////////////////////////////////
#define LCD_STR_RESETTING_MODULES (String("Resetting all modules ..."))

//////////////////////////////////////////////////////////////////////////////////////////////////
// MILLIS
//////////////////////////////////////////////////////////////////////////////////////////////////
#define MS_RESET_ALL_STATES_DELAY                   (2000)
#define MS_RESET_ALL_STATES_LCD_PRINT_DELAY         (3500)
#define MS_SENSOR_READING_DELAY                     (1000)

class StateMachine{

    LCDModule lcd_module;
    LEDModule led_module;
    SoilMoistureSensorModule soil_moisture_sensor_module;
    SegmentedDigitDisplay segmented_digit_display;


    unsigned int state;
    unsigned int state_reset;
    unsigned int previous_state;

    unsigned long last_update_millis;
    unsigned long last_update_reset_millis;

    void change_state(unsigned int next_state){
        this->previous_state = this->state;
        this->state = next_state;
        this->last_update_millis = millis();
    }

    void change_reset_state(unsigned int next_reset_state){
        this->state_reset = next_reset_state;
        this->last_update_reset_millis = millis();
    }

public:
    
    void init_pins(){
        this->segmented_digit_display.init_pins();
        this->lcd_module.init_pins();
        this->led_module.init_pins();
        
    }

    void reset_all_modules(){
        // Sets all modules to initial state/ all modules need to have reset function
        this->lcd_module.reset();
        this->led_module.reset();
        this->segmented_digit_display.reset();
        this->soil_moisture_sensor_module.reset();

        this->state_reset = SS_RESET_ALL_MODULES;
        this->state = SS_IDLE_STATE;
        this->last_update_millis = millis();
    }

    StateMachine(){
        // Iniitalizes state machine
        this->state = SS_IDLE_STATE;
        this->previous_state = SS_IDLE_STATE;
        this->state_reset = SS_RESET_ALL_MODULES;
    }

    void UpdateResetModules(){
        // Updates state machine reset - if a reset button is pressed or smh        
        unsigned long current_millis = millis();
        
        int button_state = digitalRead(BACKGROUND_CONTROLLER_PIN);

        // Checks button state and switches on that
        if(SS_RESET_ALL_MODULES == this->state_reset){
            if(button_state == RESET_BUTTON_RESET_STATE){
                this->change_reset_state(S_RESET_ALL_MODULES_DELAY);
            }
        }
        // Checks if button released or enough time passed to reset
        else if(S_RESET_ALL_MODULES_DELAY == this->state_reset){
            if(button_state == !RESET_BUTTON_RESET_STATE){
                this->change_reset_state(SS_RESET_ALL_MODULES);
            }
            else if(current_millis - this->last_update_reset_millis >= MS_RESET_ALL_STATES_DELAY){
                this->change_reset_state(S_RESET_ALL_MODULES_REAL);
            }
        }
        // Resets everything to beginning state (Even EEPROM)
        else if(S_RESET_ALL_MODULES_REAL == this->state_reset){
            this->reset_all_modules();
            this->change_reset_state(SS_PRINT_MODULES_RESETTING);
        }
        else if(SS_PRINT_MODULES_RESETTING == this->state_reset){
            this->lcd_module.print_string(LCD_STR_RESETTING_MODULES);
            this->change_reset_state(S_PRINT_MODULES_RESETTING_DELAY);
        }
        else if(S_PRINT_MODULES_RESETTING_DELAY == this->state_reset){
            Serial.println("Waiting ...");
            if(current_millis - this->last_update_reset_millis >= MS_RESET_ALL_STATES_LCD_PRINT_DELAY){
                this->change_reset_state(SS_RESET_ALL_MODULES);
                this->lcd_module.reset();
            }
        }
    }

    void Update(){
        if(S_RESET_ALL_MODULES_REAL == this->state_reset || SS_PRINT_MODULES_RESETTING == this->state_reset || S_PRINT_MODULES_RESETTING_DELAY == this->state_reset){
            return;
        }

        unsigned long current_millis = millis();

        // Initial state that sets master key flag when turning on the device
        if(SS_IDLE_STATE == this->state){
            this->change_state(SS_SENSOR_READING);
        }
        else if(SS_SENSOR_READING == this->state){
            this->lcd_module.print_string(this->soil_moisture_sensor_module.get_mapped_sensor_reading_string());
            // this->segmented_digit_display.print_digit(" 23 ");
            this->change_state(S_SENSOR_READING_DELAY);
        }
        else if(S_SENSOR_READING_DELAY == this->state){
            if(current_millis - this->last_update_millis >= MS_SENSOR_READING_DELAY){
                this->change_state(SS_SENSOR_READING);
            }
        }
    }
};

#endif // __STATE_MACHINE_H
