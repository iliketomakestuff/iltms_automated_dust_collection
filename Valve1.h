#include <Adafruit_PWMServoDriver.h> //https://learn.adafruit.com/adafruit-16-channel-pwm-slash-servo-shield/library-reference

class Valve1
{
  public:
    Valve1(int channel);
    void open();
    void close();
    void begin();
    bool isOpen();
  private:
    Adafruit_PWMServoDriver _driver;
    int _channel;
    bool _isOpen;
};
