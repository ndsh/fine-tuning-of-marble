class FTScore {
  ArrayList<FTAct> mActs = new ArrayList<FTAct>();

  FTScore()
  {
    //SCORE #000
    //id,timeout,               waitTimeout   movementsLimit[7],               motorActions[7],                 synthActions[7]                  sensorActions[7]
    mActs.add(new FTAct(0, 500, true, new int []{1, 1, 1, 1, 1, 1, 1}, new int []{1, 1, 1, 1, 1, 1, 1}, new int []{0, 0, 0, 0, 0, 0, 0}, new int []{0, 0, 0, 0, 0, 0, 0}));
    mActs.add(new FTAct(1, 500, false, new int []{0, 0, 0, 0, 0, 0, 0}, new int []{0, 0, 0, 0, 0, 0, 0}, new int []{0, 0, 0, 0, 0, 0, 0}, new int []{0, 0, 0, 0, 0, 0, 0}));
    mActs.add(new FTAct(2, 500, false, new int []{0, 0, 0, 0, 0, 0, 0}, new int []{0, 0, 0, 0, 0, 0, 0}, new int []{0, 0, 0, 0, 0, 0, 0}, new int []{0, 0, 0, 0, 0, 0, 0}));
    mActs.add(new FTAct(3, 500, false, new int []{0, 0, 0, 0, 0, 0, 0}, new int []{0, 0, 0, 0, 0, 0, 0}, new int []{0, 0, 0, 0, 0, 0, 0}, new int []{0, 0, 0, 0, 0, 0, 0}));
  }

  boolean hasActStarted(int actID)
  {
    return mActs.get(actID).mHasStarted;
  }

  boolean hasActEnded(int actID)
  {
    return mActs.get(actID).mHasEnded;
  }

  int getMotorAction(int actID, int podID)
  {
    return mActs.get(actID).getMotorAction(podID);
  }

  int getSensorAction(int actID, int podID)
  {
    return mActs.get(actID).getSensorAction(podID);
  }

  int getSynthAction(int actID, int podID)
  {
    return mActs.get(actID).getSynthAction(podID);
  }

  int getTimeOut(int actID)
  {
    return mActs.get(actID).getTimeout();
  }

  int getTotalActs()
  {
    return  mActs.size();
  }

  void startAct(int actID)
  {
    mActs.get(actID).mHasStarted = true;
  }

  void endAct(int actID)
  {
    mActs.get(actID).mHasEnded = true;
  }
}