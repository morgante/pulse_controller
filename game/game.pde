import codebase;

final int screenWidth = 300;
final int screenHeight = 300;

void initialize() {
  addScreen("mylevel", new MyLevel(screenWidth, screenHeight));
}

class MyLevel extends Level {
  MyLevel(float levelWidth, float levelHeight) {
    super(levelWidth, levelHeight);
    addScreenLayer("my level layer", new MyLevelLayer(this));
  }
}

class MyLevelLayer extends LevelLayer {
  MyLevelLayer(Level owner) {
    super(owner);
    color blueColor = color(0,130,255);
    setBackgroundColor(blueColor);
    MyCharacter mc = new MyCharacter();
    mc.setPosition(width/2, height/2);
    addPlayer(mc);
    MyEnemy me = new Myenemy();
    addInteractor(me);
    addBoundary(new Boundary(0,height, width,height));
    addBoundary(new Boundary(width,height, width,0));
    addBoundary(new Boundary(width,0,0,0));
    addBoundary(new Boundary(0,0,0,height));
  }
}

class MyCharacter extends Player {
  MyCharacter() {
    super("character");
    setStates();
    handleKey('W');
    handleKey('A');
    handleKey('S');
    handleKey('D');
    setImpulseCoefficients(0.75,0.75);
  }

  void handleInput() {
    if(isKeyDown('W')) { addImpulse(0,-1); }
    if(isKeyDown('A')) { addImpulse(-1,0); }
    if(isKeyDown('D')) { addImpulse(1,0); }
    if(isKeyDown('S')) { addImpulse(0,1); }
  }

  void hit() {
    fill(255,0,0,200);
    rect(x-10,y-10,19,19);
  }

  void setStates() {
    addState(new State("idle", "idle.gif"));
  }
}

class MyEnemy extends Interactor implements Tracker {
  MyEnemy() {
    super("enemy");
    setStates();
  }

  void overlapOccurredWith(Actor other, float[] direction) {
    other.hit();
  }

  void setStates() {
    addState(new State("idle", "idle_enemy.gif"));
  }

  void track(Actor actor, float x, float y, float w, float h) {
    GenericTracker.track(this, actor, 0.05);
  }
}