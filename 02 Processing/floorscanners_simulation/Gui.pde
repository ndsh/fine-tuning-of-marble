void guiInitSliders()
{
  cp5.addTextlabel("TITLE")
    .setText("/ FLOORSCANNER")
    .setPosition(8, 10)
    .setColorValue(color(b))
    ;

  cp5.addTextlabel("SUBTITLE")
    .setText("/ V0.2")
    .setPosition(8, 30)
    .setColorValue(color(b))
    ;

  cp5.addTextlabel("DASH")
    .setText("-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   ")
    .setPosition(8, 50)
    .setColorValue(color(b))
    ;

  actnb = cp5.addTextlabel("ACTNB")
    .setText("ACT #0")
    .setPosition(8, 70)
    .setColorValue(color(b))
    ;

  clnb = cp5.addTextlabel("CTNB")
    .setText("0")
    .setPosition(364, 70)
    .setColorValue(color(b))
    ;

  cp5.addSlider("ACTS")
    .setPosition(50, 70)
    .setWidth(308)
    .setRange(0, (tActs-1))
    .setValue(0)
    .setNumberOfTickMarks(tActs)
    .setSliderMode(Slider.FLEXIBLE)
    .setColorValue(color(b))
    .setColorActive(color(b))
    .setColorForeground(color(b))
    .setColorBackground(color(b/5))
    .setLabelVisible(false)
    ;

  cp5.addSlider("THRESHOLD")
    .setPosition(50, 100)
    .setWidth(308)
    .setRange(0, 255)
    .setValue(floor(255/2))
    .setColorValue(color(b))
    .setColorActive(color(b))
    .setColorForeground(color(b))
    .setColorBackground(color(b/5))
    .setLabelVisible(false)
    ;

  cp5.addTextlabel("THRNB")
    .setText("THOLD")
    .setPosition(8, 100)
    .setColorValue(color(b))
    ;

  cp5.addTextlabel("BGLB")
    .setText("MAP")
    .setPosition(98, 130)
    .setColorValue(color(b))
    ;

  cp5.addToggle("BGTG")
    .setPosition(140, 130)
    .setSize(30, 15)
    .setColorValue(color(b))
    .setColorActive(color(b))
    .setColorForeground(color(b))
    .setColorBackground(color(b/5))
    .setValue(viewBg)
    .setLabelVisible(false)
    ;

  cp5.addTextlabel("MODLB")
    .setText("MOD")
    .setPosition(8, 130)
    .setColorValue(color(b))
    ;

  cp5.addToggle("MOD")
    .setPosition(50, 130)
    .setSize(30, 15)
    .setColorValue(color(b))
    .setColorActive(color(b))
    .setColorForeground(color(b))
    .setColorBackground(color(b/5))
    .setValue(viewMod)
    .setLabelVisible(false)
    ;
}

public void MOD(boolean theFlag)
{
  if (theFlag==true) {
    viewMod = true;
  } else
  {
    viewMod = false;
  }
}

public void ACTS(int v)
{
  mAct = v;
  changeAct(mAct);
  updateGuiAct();
}

void updateGuiAct()
{
  actnb.setText("ACT #" + str(mAct));
  cp5.getController("ACTS").setValue(mAct);
}

void updateGuiThold()
{
  cp5.getController("THRESHOLD").setValue(thold);
}

public void THRESHOLD(float v)
{
  thold = floor(v);
}

public void BGTG(boolean theFlag) {
  if (theFlag==true) {
    viewBg = true;
  } else
  {
    viewBg = false;
  }
}

void guiShow()
{
  //update
  clnb.setText(str(clock.readClock()));

  //draw
  hint(DISABLE_DEPTH_TEST);
  cam.beginHUD();
  cp5.draw();
  cam.endHUD();
  hint(ENABLE_DEPTH_TEST);
}

void hitMouseTest()
{
  float x = 0;
  float y = 0;
  float w = 400;
  float h = 300;

  if (mouseX > x-5 && mouseX < (x+w+5))
  {
    if (mouseY > y-5 && mouseY < (y+h+5))
    {
      cam.setActive(false);
    } else
    {
      cam.setActive(true);
    }
  } else
  {
    cam.setActive(true);
  }
}

void keyPressed() {
  /*
  if (key == '1')
   {
   bvel = baseSpeed*1;
   BASE_NOTE = Scale.NOTE_A1;
   }
   if (key == '2')
   {
   bvel = baseSpeed*2;
   BASE_NOTE = Scale.NOTE_A2;
   }
   if (key == '3')
   {
   bvel = baseSpeed*4;
   BASE_NOTE = Scale.NOTE_A3;
   }
   if (key == '4')
   {
   bvel = baseSpeed*8;
   BASE_NOTE = Scale.NOTE_A4;
   }
   if (key == '5')
   {
   bvel = baseSpeed*12;
   BASE_NOTE = Scale.NOTE_A5;
   }
   */
}