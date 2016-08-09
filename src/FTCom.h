/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 FTCom.h
 Copyright (c) 2016 The Fine Tuning of Marble
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#ifndef FTCom_h
#define FTCom_h
#include <MacAddress.h>

//Definitions
#define DEBUG_COM true

class FTCom
{
  public:
    FTCom();
    void update();
    String getMacAddress();
    void retrieveMacAddress();
    String macAddress;
  private:

};

#endif
