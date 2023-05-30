// Include the header file for this class
#include "MyGPS2.h"

// Constructor: accepts serial port, baud rate and pins used for transmitting/receiving data
GPS::GPS(HardwareSerial &serial, uint32_t baud_rate, uint8_t rx_pin, uint8_t tx_pin, uint8_t mode_of_transmission) : _serial(serial), _tx_pin(tx_pin), _rx_pin(rx_pin), _mode_of_transmission(mode_of_transmission)
{
    // Initialize the serial port with given baud rate and mode of transmission
    _serial.begin(baud_rate, mode_of_transmission);
}

// Initialize the serial port
void GPS::begin()
{
    TRACE();
    _serial.begin(9600, SERIAL_8N1, _rx_pin, _tx_pin);
}

// Update the data from the GPS module
void GPS::update()
{
    TRACE();
    // While there is data available on the serial port
    while (_serial.available() > 0)
    {
        // Read the data and parse it using TinyGPS++
        _gps.encode(_serial.read());
    }
    // If location information has been updated
    if (_gps.location.isUpdated())
    {
        _latitude = _gps.location.lat();
        _longitude = _gps.location.lng();
        _latitude_timer = millis();
        _longitude_timer = _latitude_timer;
        _altitude = _gps.altitude.meters();
        _altitude_timer = millis();
    }

    // If date information has been updated
    if (_gps.date.isUpdated())
    {
        // Store the date
        _date = String(_gps.date.day()) + "/" + String(_gps.date.month()) + "/" + String(_gps.date.year());
        _date_timer = millis();
    }

    // If time information has been updated
    if (_gps.time.isUpdated())
    {
        // Store the time
        _time = String(_gps.time.hour()) + ":" + String(_gps.time.minute()) + ":" + String(_gps.time.second());
        _time_timer = millis();
    }

    
}

// Check whether the GPS data is valid
bool GPS::isValid()
{
    TRACE();
    // Check to see if data stale
    if (millis() - _latitude_timer > kStaleDataTimeout || millis() - _longitude_timer > kStaleDataTimeout || millis() - _altitude_timer > kStaleDataTimeout || millis() - _date_timer > kStaleDataTimeout || millis() - _time_timer > kStaleDataTimeout)
    {
        _valid = false;
    }
    else
    {
        _valid = true;
    }

    return _valid;
}

// Get the latitude in degrees
double GPS::getLatitude()
{
    TRACE();
    if (millis() - _latitude_timer > kStaleDataTimeout) // Check to see if data stale
    {
        _latitude = 0.0;
    }
    return _latitude;
}

// Get the longitude in degrees
double GPS::getLongitude()
{
    TRACE();
    if (millis() - _longitude_timer > kStaleDataTimeout) // Check to see if data stale
    {
        _longitude = 0.0;
    }
    return _longitude;
}

// Get the altitude in meters
double GPS::getAltitude()
{
    TRACE();
    if (millis() - _altitude_timer > kStaleDataTimeout) // Check to see if data stale
    {
        _altitude = 0.0;
    }
    return _altitude;
}

// Get the date in DD/MM/YYYY format
String GPS::getDate()
{
    TRACE();
    if (millis() - _date_timer > kStaleDataTimeout) // Check to see if data stale
    {
        _date = "";
    }
    return _date;
}

// Get the time in HH:MM:SS format
String GPS::getTime()
{
    TRACE();
    if (millis() - _time_timer > kStaleDataTimeout) // Check to see if data stale
    {
        _time = "";
    }
    return _time;
}

void GPS::test()
{
    TRACE();
    // Print the latitude, longitude, altitude, date and time
    Serial.println("Latitude: " + String(getLatitude(), 6));
    Serial.println("Longitude: " + String(getLongitude(), 6));
    Serial.println("Altitude: " + String(getAltitude(), 2));
    Serial.println("Date: " + getDate());
    Serial.println("Time: " + getTime());
}
