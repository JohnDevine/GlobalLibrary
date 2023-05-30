#ifndef MYGPS2_H
#define MYGPS2_H


// Include required libraries
#include <JDGlobal.h> // Global definitions
#include <TinyGPS++.h> // TinyGPS++ library for parsing NMEA sentences
#include <HardwareSerial.h> // Arduino's hardware serial library

#define kStaleDataTimeout 50000 // Timeout for stale data in milliseconds

class GPS {
  public:
    // Constructor: accepts serial port, baud rate and pins used for transmitting/receiving data
    GPS(HardwareSerial& serial, uint32_t baud_rate, uint8_t rx_pin, uint8_t tx_pin, uint8_t mode_of_transmission);

    // Initialize the serial port
    void begin();

    // Update the data from the GPS module
    void update();

    // Check whether the GPS data is valid
    bool isValid();

    // Get the latitude in degrees
    double getLatitude();

    // Get the longitude in degrees
    double getLongitude();

    // Get the altitude in meters
    double getAltitude();

    // Get the date in DD/MM/YYYY format
    String getDate();

    // Get the time in HH:MM:SS format
    String getTime();

    // Test the GPS module
    void test();

  private:
    // Serial port used for communicating with GPS module
    HardwareSerial& _serial;

    // TinyGPS++ object for parsing NMEA sentences
    TinyGPSPlus _gps;

    // Pins used for transmitting/receiving data
    uint8_t _tx_pin;
    uint8_t _rx_pin;

    // Mode of transmission used by the GPS module
    uint8_t _mode_of_transmission;

    // Variables for storing latitude, longitude, altitude, date and time
    double _latitude = 0.0;
    unsigned long _latitude_timer = 0; // Timer for latitude
    double _longitude = 0.0;
    unsigned long _longitude_timer = 0; // Timer for longitude
    double _altitude = 0.0;
    unsigned long _altitude_timer = 0; // Timer for altitude
    String _date = "";
    unsigned long _date_timer = 0; // Timer for date
    String _time = "";
    unsigned long _time_timer = 0; // Timer for time

    // Flag for indicating whether GPS data is valid
    bool _valid = false;
};
#endif
