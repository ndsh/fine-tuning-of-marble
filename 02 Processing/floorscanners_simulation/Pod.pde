class Pod { 

  ///////////////////////////////////////////////////////////////////////////////////////////
  //Acting functions
  ///////////////////////////////////////////////////////////////////////////////////////////

  /* ----------------------------------------------------------------------------------------
   
   MOTOR ACTIONS
   
   setBaseSpeed(float nv)                                      Set the base speed (for all pods).
   setConstantSpeed(float speedFactor)                         Set the motor to a CONSTANT SPEED mode.
   setAccelSpeed(float in, float out, float maxSpeedLimiter)   Set the motor to an ACCELERATED SPEED mode.
   runTo(int position, int direction, int rotations)           Moves to a specific position.
   rotate(int times, int direction)                            Rotates N times in a specific direction
   
   */

  void moveMotor(int actionID)
  {

    if (!score.mActs.get(mAct).hasReachedLimit(id))
    {
      if (!_isMoving)
      {
        score.mActs.get(mAct).updateCounter(id);
        _isMoving = true;

        switch(actionID)
        {
        case 0: 

          //One full round constant speed
          setConstantSpeed(0.4);
          rotate(1, -1);

          break;

        case 1:

          //Go to random position with acceleration, +1 full rotation, direction 1
          setAccelSpeed(1, 1, 1);
          runTo(floor(random(FULLREV)), 1, 1);
          break;

        case 2:

          break;
        }
      }
    } else
    {
      score.mActs.get(mAct).setPodDone(id);
    }
  }

  ///////////////////////////////////////////////////////////////////////////////////////////

  /* ----------------------------------------------------------------------------------------
   
   SENSOR ACTIONS
   
   toggleRecording(Boolean b)      Record data ON/OFF
   toggleLED(Boolean b)            Set LED ON/OFF
   
   */

  void configureSensor(int actionID)
  {
    switch(actionID)
    {
    case 0: 
      //Recording data, LED ON
      toggleRecording(true);
      toggleLED(true);
      break;

    case 1:
      //Not recording data, LED OFF
      toggleRecording(false);
      toggleLED(false);
      break;

    case 2:

      break;
    }
  }

  ///////////////////////////////////////////////////////////////////////////////////////////

  /* ----------------------------------------------------------------------------------------
   
   SYNTH ACTIONS
   
   setThold(int nt)          Set the threshold for playing the note (0-255, data)
   setBaseNote(int n)        Set the base note for playing
   enableSynth(Boolean b)    Enable/disable sound
   
   */

  void tuneSynth(int actionID)
  {
    switch(actionID)
    {
    case 0: 
      //Play, set threshold, set base note to Scale.NOTE_A3
      enableSynth(true);
      setThold(150);
      setBaseNote(Scale.NOTE_A3);      
      break;

    case 1:
      //Play, set threshold, set base note to Scale.NOTE_A2
      enableSynth(true);
      setThold(150);
      setBaseNote(Scale.NOTE_A2);  

      break;

    case 2:

      break;
    }
  }

  ///////////////////////////////////////////////////////////////////////////////////////////

  PVector pos;
  int steps, stepsToGo, stepsLast, stepsTarget;
  int baseNote;
  float ang;
  float angInit;
  float rad;
  float vel, mBaseSpeed, mSpeed;
  float mRangeIn;
  float mRangeOut;
  float mMaxSpeedFactor;
  int dir;
  int note;
  int id;
  float[] storedData;
  Boolean _isMoving;
  Boolean _isPlaying;
  Boolean _isRecording;
  Boolean _mIsConstant;
  Boolean _ledOn;

  final Synthesizer synth = Synthesizer.getSynth();

  Pod (int podID, PVector position, float radious, float initAngle) {
    id = podID;
    rad = radious;
    pos = position;
    angInit = initAngle;
    ang = 0;
    vel = 0;
    dir = 1;
    mSpeed = 0.2;
    mBaseSpeed = baseSpeed;
    steps = 0;
    stepsLast = 0;
    stepsToGo = 0;
    storedData = new float[FULLREV];
    baseNote = Scale.NOTE_A3;
    mRangeIn = 0;
    mRangeOut = 0;
    mMaxSpeedFactor = 0;
    _isMoving = false;
    _isPlaying = false;
    _isRecording = false;
    _mIsConstant = true;
    _ledOn = false;
  }

  void draw()
  {
    pushMatrix();
    if (viewMod)
    {
      fill(b);
    } else
    {
      fill(b/4);
    }
    //stroke(d);
    noStroke();
    strokeWeight(0.5);
    translate(pos.x-(roomSize[0]*0.5), pos.y+(roomSize[1]*0.5)-10, pos.z-(roomSize[2]*0.5));
    rotateX(PI/2);
    drawCylinder(30, 14, 14, 20);
    rotateZ(ang);
    translate(rad*0.5, 0, 8);
    box(rad, 5, 2);
    translate(rad*0.5, 0, -4);
    box(2, 5, 8);
    if (_ledOn) {
      translate(0, 0, -4);
      noFill();
      stroke(255);
      float r = random(20, 24);
      ellipse(0, 0, r, r);
      //drawGradient(0, 0);
    }
    popMatrix();
  }

  ///////////////////////////////////////////////////////////////////////////////////////////
  //Data functions
  ///////////////////////////////////////////////////////////////////////////////////////////

  void setData(int p, float d)
  {
    storedData[p] = d;
  }

  float getData(int p)
  {
    return storedData[p];
  }

  void toggleLED(Boolean b)
  {
    _ledOn = b;
  }

  void toggleRecording(Boolean b)
  {
    _isRecording = b;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////
  //Motor functions
  ///////////////////////////////////////////////////////////////////////////////////////////

  void updateMotor()
  {
    //Update angle
    if (!_mIsConstant) updateSpeed();
    calculateAngSteps();
    if (ang > (PI*2))
    {
      ang = ang - (PI*2);
    }
  }

  void runTo(int position, int direction, int rotations)
  {
    stepsLast = steps;
    stepsTarget = getNewTargetRelativePosition(position, direction, rotations);
    stepsToGo = stepsTarget-steps;
    dir = direction;
  }

  void rotate(int times, int direction)
  {
    dir = direction;
    stepsLast = steps;
    stepsTarget = steps+(dir*times*FULLREV);
    stepsToGo = stepsTarget - steps;
  }

  void setBaseSpeed(float nv)
  {
    mBaseSpeed = nv;
  }

  void setConstantSpeed(float speedFactor)
  {
    //Linear constant speed of speedFactor (0 to 1) * MAXSPEED
    _mIsConstant = true;
    mSpeed = MAXSPEED * speedFactor;
    vel = mBaseSpeed+mSpeed;
  }

  void setAccelSpeed(float in, float out, float maxSpeedLimiter)
  {
    _mIsConstant = false;
    //in (0 to 1), define length of ease in curve
    //out (0 to 1), define length of ease out curve
    //speedFactor (0 to 1) limits the MAXSPEED (height) of the motion curve
    mRangeIn = in;
    mRangeOut = out;
    mMaxSpeedFactor = maxSpeedLimiter;
  }

  void calculateAngSteps()
  {
    if (stepsToGo != 0)
    {

      float st = map(vel, 0, PI*2, 0, dir*FULLREV);
      if (st > 0)
      {
        if (st > STEPSPERFRAME)
        {
          st = STEPSPERFRAME;
        }
        if (st > stepsToGo)
        {
          st = stepsToGo;
        }
      } else
      {
        if (st < STEPSPERFRAME*-1)
        {
          st = STEPSPERFRAME*-1;
        }
        if (st < stepsToGo)
        {
          st = stepsToGo;
        }
      }

      stepsToGo -= st;
      steps += st;
      ang = map(steps, 0, FULLREV, 0, PI*2);
      ang += angInit;
    } else
    {
      _isMoving = false;
    }
  }

  void updateSpeed()
  {
    //Calculate the current speed of the motor in acceleration using a linear ramp on the motor's speed.
    float newSpeed;
    float mMaxSpeed = (MAXSPEED * mMaxSpeedFactor);
    int currentPos = steps;
    int posIN = floor(stepsLast + (stepsToGo * mRangeIn * 0.5));
    int posOUT = floor((stepsToGo + stepsLast) - (stepsToGo* mRangeOut * 0.5));

    if (stepsLast > stepsTarget)
    {
      //Going backwards
      if (currentPos >= posIN)
      {
        //IN Ramp
        newSpeed = map(currentPos, stepsLast, posIN, MINSPEED, mMaxSpeed);
      } else
      {
        if (currentPos <= posOUT)
        {
          //OUT Ramp
          newSpeed = map(currentPos, posOUT, stepsTarget, mMaxSpeed, MINSPEED);
        } else
        {
          //Constant speed in between ramps
          newSpeed = mMaxSpeed;
        }
      }
    } else
    {
      //Going forwards
      if (currentPos <= posIN)
      {
        //IN Ramp
        newSpeed = map(currentPos, stepsLast, posIN, MINSPEED, mMaxSpeed);
      } else
      {
        if (currentPos >= posOUT)
        {
          //OUT Ramp
          newSpeed = map(currentPos, posOUT, stepsTarget, mMaxSpeed, MINSPEED);
        } else
        {
          //Constant speed in between ramps
          newSpeed = mMaxSpeed;
        }
      }
    }

    //Check if reached the destination to completely stop motor.
    if (steps == stepsTarget)
    {
      newSpeed = 0;
    }

    //Update speed
    if (newSpeed >= 0)
    {
      mSpeed = newSpeed;
      vel = mSpeed+mBaseSpeed;
    }
  }

  int getCurrentAbsolutePosition()
  {
    //Calculates an absolute position (0 to FULLREV) relative to the current relative one

    //Main calculation
    int currentRelativePos = steps;
    int currentRevolutions = 0;
    int absolutePos = 0;
    if (currentRelativePos < 0)
    {
      currentRevolutions = abs(floor(currentRelativePos / FULLREV));
      absolutePos = currentRelativePos + (FULLREV * currentRevolutions);
    } else
    {
      currentRevolutions = currentRelativePos / FULLREV;
      absolutePos = currentRelativePos - (FULLREV * currentRevolutions);
    }

    //Correction of range (from -FULLREV to FULLREV, to 0 to FULLREV)
    if (absolutePos < 0)
    {
      absolutePos += FULLREV;
    }
    return absolutePos;
  }

  int getNewTargetRelativePosition(int newAbsolutePos, int direction, int rotations)
  {
    //Calculates a relative position relative to an absolute one (0 to fullRev)
    //Does further recquired calculations regarding extra locked direction or rotation

    int newRelativePos = steps;
    int currentAbsolutePos = getCurrentAbsolutePosition();
    int distance = newAbsolutePos - currentAbsolutePos;
    switch(direction)
    {
    case -1:
      if (distance < 0)
      {
        //Already going to -1
        newRelativePos += distance - (FULLREV*rotations);
      } else
      {
        //Force to -1
        newRelativePos += distance - (FULLREV*(rotations+1));
      }
      break;

    case 0:
      if (distance < 0)
      {
        //Going -1
        newRelativePos += distance - (FULLREV*rotations);
      } else
      {
        //Going 1
        newRelativePos += distance + (FULLREV*rotations);
      }
      break;

    case 1:
      if (distance < 0)
      {
        //Force to 1
        newRelativePos += distance + (FULLREV*(rotations+1));
      } else
      {
        //Already going to 1
        newRelativePos += distance + (FULLREV*rotations);
      }
      break;
    }
    return newRelativePos;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////
  //Sound functions
  ///////////////////////////////////////////////////////////////////////////////////////////

  void setThold(int nt)
  {
    thold = nt;
    updateGuiThold();
  }

  void updateSynth()
  {
    float n = getData(getCurrentAbsolutePosition());
    if (n > thold)
    {
      note = Scale.note(Scale.MAJOR_CHORD_7, baseNote, floor(map(n, 0, 255, 0, 3)));
    } else
    {
      note = 0;
    }
  }

  void play()
  {
    synth.noteOn(note, 127);
  }

  void stop()
  {
    synth.noteOn(note, 0);
  }

  void setBaseNote(int n)
  {
    baseNote = n;
  }

  void enableSynth(Boolean b)
  {
    _isPlaying = b;
  }
}