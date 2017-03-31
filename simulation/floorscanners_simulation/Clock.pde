class Clock
{
  int mPulseInterval = PULSEINTERVAL;
  int mPulseCount = 0;
  int mLast = 0;
  int mNext = 0;
  boolean mPulse = false;

  Clock () {
  }

  void update() {
    if (millis() >= mNext)
    {
      mPulse = true;
      calcIntervals();
      mPulseCount++;
    } else
    {
      mPulse = false;
    }
  }

  void resetClock() {
    mPulseCount = 0;
    calcIntervals();
  }

  int readClock() {
    return mPulseCount;
  }

  boolean readPulse()
  {
    return mPulse;
  }

  void updatePulse() {
    mPulseCount++;
  }

  void calcIntervals()
  {
    mLast = millis();
    mNext = mLast + mPulseInterval;
  }
}