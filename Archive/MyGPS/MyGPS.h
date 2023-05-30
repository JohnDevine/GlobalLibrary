#ifndef MYGPS_H
#define MYGPS_H

#include "MyGlobal.h"
#include "HardwareSerial.h"
#include <TinyGPSPlus.h>
#include "MyTiming.h"

// Error codes
#define kGoodGPS 1        // GPS function good
#define kUARTFailed 10    // UART Failed to come up
#define kGoodGPSRead 15   // GPS read is good and llocation is valid
#define kReadFailed 20    // GPS read failed
#define kNoGPSFixYet 25   // GPS is reading OK but no fix yet
#define kBadSerialPort 30 // Bad serial port number
#define kGPSBadData 555   // Define bad data (HaHaHa)

/* Used in GPS functions*/
#define kGPSIntervalBetweenChecks 1000 // How long between checks to see if UART up
#define kMaxGPSWait 5000               // Maximum to wait for UART to get data in ms (must be > gps_interval_between_checks)

class MyGPS
{
public:
  int initGPS(int GPSHardwareSerialPort, long GPSSpeed, uint32_t GPSMode, int8_t ReadPin, int8_t WritePin);
  // Read the GPS
  int ReadGPS();

  // Keep reading the GPS until we get a lock and valid data
  int ReadTillValidGPS();

  // This provides a test function for the GPS and displays quite a lot of the data available
  void testGPS();

  // Get the latitude
  double GPS_Get_Lat();

  // Get the longitude
  double GPS_Get_Lng();

  // Get the altitude
  double GPS_Get_Alt();

  // Get the date_day
  int GPS_Get_date_day();

  // Get the date_month
  int GPS_Get_date_month();

  // Get the date_year
  int GPS_Get_date_year();

  // Get the time_hour
  int GPS_Get_time_hour();
  // Get the time_minute
  int GPS_Get_time_minute();
  // Get the time_second
  int GPS_Get_time_second();
  // Get the time_centisecond
  int GPS_Get_time_centisecond();

private:
  HardwareSerial &_SerialGPS = Serial2;
  int _GPSHardwareSerialPort;
  int _GPSSpeed;
  int _GPSMode;
  int _ReadPin;
  int _WritePin;
  int _wait_so_far;
  TinyGPSPlus _gps;
  MyTiming _MyTiming;
  int _GPSStatus;
};
#endif
