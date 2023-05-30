#include "MyGPS.h"


int MyGPS::initGPS(int GPSHardwareSerialPort, long GPSSpeed, uint32_t GPSMode, int8_t ReadPin, int8_t WritePin)
{
  TRACE();
  _GPSHardwareSerialPort = GPSHardwareSerialPort;
  _GPSSpeed = GPSSpeed;
  _GPSMode = GPSMode;
  _ReadPin = ReadPin;
  _WritePin = WritePin;
  if (GPSHardwareSerialPort == UART1)
  {
    _SerialGPS = Serial1;
  }
  else if (GPSHardwareSerialPort == UART2)
  {
    _SerialGPS = Serial2;
  }
  else
  {
    // Print an error message or throw an exception to indicate an invalid value.
    Serial.println("Invalid value for GPSHardwareSerialPort");
    return kBadSerialPort;
    // You may also want to assign null or do something else to indicate that the assignment failed.
  }

  _SerialGPS.begin(_GPSSpeed, _GPSMode, _ReadPin, _WritePin);
  _wait_so_far = 0;
  
  while (!_SerialGPS.available())
  {
    TRACE();
    _MyTiming.MyTimingDelay(kGPSIntervalBetweenChecks);
    _wait_so_far = _wait_so_far + kGPSIntervalBetweenChecks;
  
    if (_wait_so_far > kMaxGPSWait)
    {
      return kUARTFailed;
    }
  }
  

  // Read the GPS data.

  if (ReadGPS() == kReadFailed)
  {
    return kReadFailed;
  }

  return kGoodGPS;
}
int MyGPS::ReadGPS()
{
  TRACE();
  // flush the UART buffer first as the system may have been just piling up data from gps unit
  // SerialGPS->flush();  // NOT SO SURE THIS IS NEEDED

  // Read in data character by character and keep encoding it until no data left
  while (_SerialGPS.available() > 0)
  {
    _gps.encode(_SerialGPS.read());
  }

  // check to see if we have valid location data
  if (_gps.location.isValid() && _gps.date.isValid())  // Note that the location data may be valid before the date comes through
  {
    return kGoodGPSRead;
  }
  // If GPS is good BUT we have not got a fix return "No Fix Yet" status
  if (_gps.charsProcessed() > 0)
  {
    return kNoGPSFixYet;
  }
  TRACE();
  DUMP(_gps.charsProcessed());
  DUMP(_gps.sentencesWithFix());
  DUMP(_gps.failedChecksum());
  DUMP(_gps.passedChecksum());

  return kReadFailed;
}

int MyGPS::ReadTillValidGPS()
{
  TRACE();
  
  while (_GPSStatus = ReadGPS() == kNoGPSFixYet)
  {
    TRACE();
    // blinkLED(ESP32_LED_BUILTIN, kWaitingOnGPSFix, false); // let user know what is going on
    _MyTiming.MyTimingDelay(kGPSIntervalBetweenChecks); // Wait a second to give GPS time to read
  }
  return _GPSStatus;
}
void MyGPS::testGPS()
{
  TRACE();
  
  // ReadGPS();
  ReadTillValidGPS();

  DUMP(_gps.location.lat());
  DUMP(_gps.location.lng());
  DUMP(_gps.location.isValid());

  DUMP(_gps.date.isValid());
  DUMP(_gps.date.value());
  DUMP(_gps.date.day());
  DUMP(_gps.date.month());
  DUMP(_gps.date.year());

  DUMP(_gps.time.isValid());
  DUMP(_gps.time.hour());
  DUMP(_gps.time.minute());
  DUMP(_gps.time.second());
  DUMP(_gps.time.centisecond());

  DUMP(_gps.satellites.value());
  DUMP(_gps.satellites.isValid());
  DUMP(_gps.hdop.value());
  DUMP(_gps.hdop.isValid());
  DUMP(_gps.altitude.meters());
  DUMP(_gps.altitude.isValid());
  DUMP(_gps.course.deg());
  DUMP(_gps.course.isValid());
  DUMP(_gps.speed.kmph());
  DUMP(_gps.speed.isValid());

  //***************** From Functions

  DUMP(GPS_Get_Lat());
  DUMP(GPS_Get_Lng());


  DUMP(GPS_Get_Alt());

  DUMP(GPS_Get_date_day());
  DUMP(GPS_Get_date_month());
  DUMP(GPS_Get_date_year());

  DUMP(GPS_Get_time_hour());
  DUMP(GPS_Get_time_minute());
  DUMP(GPS_Get_time_second());
  DUMP(GPS_Get_time_centisecond());

}
// Get the latitude
double MyGPS::GPS_Get_Lat()
{
  TRACE();
  ReadTillValidGPS();
  if (_gps.location.isValid())
  {
    return (_gps.location.lat());
  }
  return (kGPSBadData);
}

// Get the longitude
double MyGPS::GPS_Get_Lng()
{
  TRACE();
  ReadTillValidGPS();
  if (_gps.location.isValid())
  {
    return (_gps.location.lng());
  }
  return (kGPSBadData);
}
// Get the altitude
double MyGPS::GPS_Get_Alt()
{
  ReadTillValidGPS();
  if (_gps.altitude.isValid())
  {
    return (_gps.altitude.meters());
  }
  return (kGPSBadData);
}
// Get the date_day
int MyGPS::GPS_Get_date_day()
{
  ReadTillValidGPS();
  if (_gps.date.isValid())
  {
    return (_gps.date.day());
  }
  return (kGPSBadData);
}

// Get the date_month
int MyGPS::GPS_Get_date_month()
{
  ReadTillValidGPS();
  if (_gps.date.isValid())
  {
    return (_gps.date.month());
  }
  return (kGPSBadData);
}

// Get the date_year
int MyGPS::GPS_Get_date_year()
{
  ReadTillValidGPS();
  if (_gps.date.isValid())
  {
    return (_gps.date.year());
  }
  return (kGPSBadData);
}


// Get the time_hour
int MyGPS::GPS_Get_time_hour()
{
  ReadTillValidGPS();
  if (_gps.time.isValid())
  {
    return (_gps.time.hour());
  }
  return (kGPSBadData);
}
// Get the time_minute
int MyGPS::GPS_Get_time_minute()
{
  ReadTillValidGPS();
  if (_gps.time.isValid())
  {
    return (_gps.time.minute());
  }
  return (kGPSBadData);
}
// Get the time_second
int MyGPS::GPS_Get_time_second()
{
  ReadTillValidGPS();
  if (_gps.time.isValid())
  {
    return (_gps.time.second());
  }
  return (kGPSBadData);
}

// Get the time_centisecond
int MyGPS::GPS_Get_time_centisecond()
{
  ReadTillValidGPS();
  if (_gps.time.isValid())
  {
    return (_gps.time.centisecond());
  }
  return (kGPSBadData);
}


