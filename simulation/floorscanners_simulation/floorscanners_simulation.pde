/*///////////////////////////////////////////////////////////////////////////////////////
 
 ~FLOOR SCANNERS~ SIMULATION
 Luiz Zanotello, Julian Hespenheide, Irena Kukric.
 2016/2017.
 V 1.0
 
 ----------------------------------------------------------------------------------------
 
 Edit PARAMS bellow.
 Edit/include MOTOR actions, SENSOR actions, SYNTH actions at the Pod constructor.
 Edit/include ACTS in the Score constructor.
 
 ----------------------------------------------------------------------------------------
 
 //////////////////////////////////////////////////////////////////////////////////////*/

//Params
Boolean blockRotation = true;
int[] roomSize = {700, 300, 1000};
int baseRad = 100;
float baseSpeed = 0.01;
int PULSEINTERVAL = 50;
int FULLREV = 64000;
int STEPSPERFRAME = 1000;
float MAXSPEED = 0.1;
float MINSPEED = 0.001;
int d = 20;
int b = 240;

//Imports
import de.dennisppaul.newmusicalinstruments.synthesizer.*;
import ddf.minim.*;
import peasy.*;
import controlP5.*;

//Instances
ArrayList<Pod> pods = new ArrayList<Pod>();
Room room;
Clock clock;
PeasyCam cam;
ControlP5 cp5;
FTScore score;
Textlabel actnb, clnb;
int thold, mAct, tActs, mTimeoutCounter;
Boolean viewBg, viewMod;

void setup()
{
  fullScreen(OPENGL);
  background(d);
  smooth(8);
  noStroke();
  frameRate(30);
  noiseDetail(10);

  //Init ROOM and SURFACE
  room = new Room(roomSize[0], roomSize[1], roomSize[2], 0, 0, 0);

  //Init SCORE
  score = new FTScore();
  tActs = score.getTotalActs();

  //Init Vars
  mAct = 0;
  mTimeoutCounter = 0;
  thold = floor(255/2);
  viewBg = false;
  viewMod = true;

  //Init CLOCK
  clock = new Clock();

  //Init PODs
  pods.add( new Pod(0, new PVector (300, 0, 400), baseRad, random(PI*2)));
  pods.add( new Pod(1, new PVector (120, 0, 620), baseRad, random(PI*2)));
  pods.add( new Pod(2, new PVector (400, 0, 150), baseRad, random(PI*2)));
  pods.add( new Pod(3, new PVector (215, 0, 840), baseRad, random(PI*2)));
  pods.add( new Pod(4, new PVector (550, 0, 840), baseRad, random(PI*2)));
  pods.add( new Pod(5, new PVector (125, 0, 150), baseRad, random(PI*2)));
  pods.add( new Pod(6, new PVector (420, 0, 670), baseRad, random(PI*2)));

  //Init CAM
  cam = new PeasyCam(this, 100);
  cam.setDistance(1000);
  cam.setMinimumDistance(100);
  cam.setMaximumDistance(2000);
  if (blockRotation) cam.setYawRotationMode();
  cam.setActive(false);

  //Init CONTROLS
  cp5 = new ControlP5(this);
  cp5.setAutoDraw(false);
  guiInitSliders();

  //Start first act
  changeAct(mAct);
}

void draw()
{
  background(d);
  clock.update();
  conduct();
  room.draw();
  hitMouseTest();
  guiShow();
  updatePods();
  drawPods();
  playPods();
}

void conduct()
{
  //Check if current act must be updated
  if (clock.readPulse())
  {
    mTimeoutCounter++;
    if (mTimeoutCounter > score.getTimeOut(mAct))
    {
      changeAct(mAct+1);
      updateGuiAct();
    } else
    {
      //Check if all pods are done
      if (score.mActs.get(mAct).arePodsDone())
      {
        if (!score.mActs.get(mAct).waitForTimeout())
        {
          changeAct(mAct+1);
          updateGuiAct();
        }
      }
      updatePodActions(mAct);
    }
  }
}

void changeAct(int a)
{
  mAct = a;
  if (a >= score.mActs.size())
  {
    a = 0;
    mAct = 0;
  }
  clock.resetClock();
  mTimeoutCounter = 0;
  score.startAct(a);
  updatePodActions(a);
}

void updatePodActions(int a)
{
  for (int i = 0; i < 7; i++)
  {
    pods.get(i).configureSensor(score.getSensorAction(a, i));
    pods.get(i).tuneSynth(score.getSynthAction(a, i));
    pods.get(i).moveMotor(score.getMotorAction(a, i));
  }
}

void updatePods()
{
  for (int i = 0; i < pods.size(); i++)
  {
    if (pods.get(i)._isMoving) pods.get(i).updateMotor();
    if (pods.get(i)._isRecording)
    {
      float tipX = pods.get(i).pos.x+(cos(pods.get(i).ang)*pods.get(i).rad);
      float tipZ = pods.get(i).pos.z+(sin(pods.get(i).ang)*pods.get(i).rad);
      pods.get(i).setData(pods.get(i).getCurrentAbsolutePosition(), room.pattern[floor(floor(tipX)*floor(tipZ))]);
    }
    if (pods.get(i)._isPlaying) pods.get(i).updateSynth();
  }
}

void drawPods()
{
  for (int i = 0; i < pods.size(); i++)
  {
    pods.get(i).draw();
  }
}

void playPods()
{
  for (int i = 0; i < pods.size(); i++)
  {
    pods.get(i).play();
  }
}