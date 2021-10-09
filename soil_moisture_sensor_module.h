
#ifndef __SOIL_MOISTURE_SENSOR_MODULE_H
#define __SOIL_MOISTURE_SENSOR_MODULE_H
#define SENSOR_PIN A0 

class SoilMoistureSensorModule{

public:
    SoilMoistureSensorModule(){

    }

    void reset(){

    }
    
    int get_sensor_reading(){
        int output_value= analogRead(SENSOR_PIN);
        return output_value;
    }

    int get_mapped_sensor_reading(){
        return map(get_sensor_reading(), 550, 0, 0, 100);
    }

    String get_sensor_reading_string(){
        char buff[5];
        sprintf(buff, "%d", this->get_sensor_reading());
        return "Sensor reading: " + String(buff);
    }

    String get_mapped_sensor_reading_string(){
        char buff[5];
        sprintf(buff, "%d", this->get_mapped_sensor_reading());
        return "Sensor reading: " + String(buff) + String("%");
    }

};

#endif // __SOIL_MOISTURE_SENSOR_MODULE_H