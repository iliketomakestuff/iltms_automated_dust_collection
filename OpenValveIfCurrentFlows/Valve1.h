#include <Adafruit_PWMServoDriver.h> //https://learn.adafruit.com/adafruit-16-channel-pwm-slash-servo-shield/library-reference

class Valve1
{
  public:
    Valve1(int channel, int openPosition, int ClosedPosition);
    void open();
    void close();
    void begin();
    bool isOpen();
    int getOpenPosition();
    int getClosedPosition();
  private:
    Adafruit_PWMServoDriver _driver;
    int _channel;
    bool _isOpen;
    int _openPosition;
    int _closedPosition;
};
