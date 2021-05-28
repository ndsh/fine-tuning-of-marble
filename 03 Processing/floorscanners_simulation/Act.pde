class FTAct { 
  boolean mHasStarted;
  boolean mHasEnded;
  boolean mWaitForTimeout;
  boolean[] mPodDone;
  int[] mMovementsCounter;
  int[] mMovementsLimit;
  int[] mMotorActions;
  int[] mSensorActions;
  int[] mSynthActions;
  int mTimeOut;
  int mID;

  FTAct(int actID, int timeOut, boolean waitForTimeout, int movementsLimit[], int motorActions[], int synthActions[], int sensorActions[])
  {
    mWaitForTimeout = waitForTimeout;
    mHasStarted = false;
    mHasEnded= false;
    mTimeOut = timeOut;
    mID = actID;
    mMotorActions = motorActions;
    mSensorActions = sensorActions;
    mSynthActions = synthActions;
    mMovementsLimit = movementsLimit;
    mMovementsCounter = new int []{0, 0, 0, 0, 0, 0, 0};
    mPodDone = new boolean[]{false, false, false, false, false, false, false};
  }

  void updateCounter(int podID)
  {
    mMovementsCounter[podID] += 1;
  }

  Boolean waitForTimeout()
  {
    return mWaitForTimeout;
  }

  Boolean arePodsDone()
  {
    int c = 0;
    for (int i = 0; i < 7; i++)
    {
      if (isPodDone(i)) c++;
    }
    if (c==7)
    {
      return true;
    } else
    {
      return false;
    }
  }

  Boolean isPodDone(int podID)
  {
    return mPodDone[podID];
  }

  void setPodDone(int podID)
  {
    mPodDone[podID] = true;
  }

  Boolean hasReachedLimit(int podID)
  {
    if (mMovementsCounter[podID] == mMovementsLimit[podID])
    {
      return true;
    } else
    {
      return false;
    }
  }
  int getID()
  {
    return mID;
  }


  int getTimeout()
  {
    return mTimeOut;
  }

  int getSensorAction(int podID)
  {
    return mSensorActions[podID];
  }

  int getSynthAction(int podID)
  {
    return mSynthActions[podID];
  }

  int getMotorAction(int podID)
  {
    return mMotorActions[podID];
  }
}