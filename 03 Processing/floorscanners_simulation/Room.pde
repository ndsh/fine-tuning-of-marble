class Room { 
  float xsize, ysize, zsize;
  PVector pos;
  float[] pattern;
  Room (float xs, float ys, float zs, float xp, float yp, float zp) {  
    xsize = xs;
    ysize = ys;
    zsize = zs;
    pos = new PVector(xp, yp, zp);
    pattern = new float[floor(xsize*zsize)];
    initPattern();
  } 
  void update() {
  }
  void draw() {
    noFill();
    stroke(b/4);
    strokeWeight(1);
    pushMatrix();
    translate(pos.x, pos.y, pos.z);
    box(xsize, ysize, zsize);
    translate(xsize*-0.5, ysize*-0.5, zsize*0.5);
    if (viewBg)
    {
      rotateX(-PI/2);
      translate(0, 0, ysize);
      drawPattern();
    }
    popMatrix();
  }
  void initPattern()
  {
    float xoff = 0.0;
    float increment = 0.02;
    int ip = 0;
    for (int x = 0; x < xsize; x++) {
      xoff += increment;
      float zoff = 0.0;
      for (int z = 0; z < zsize; z++) {
        zoff += increment;
        pattern[ip] = (noise(xoff, zoff) * 255);
        ip++;
      }
    }
  }
  void drawPattern()
  {
    int ip = 0;
    for (int x = 0; x < xsize; x++) {
      for (int z = 0; z < zsize; z++) {
        fill(color(pattern[ip]));
        noStroke();
        rect(x, z, 1, 1);
        ip++;
      }
    }
  }
}