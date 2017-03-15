#define  MAX_DEVICES 4
#define CLK_PIN   13  // or SCK
#define DATA_PIN  11  // or MOSI
#define CS_PIN    10  // or SS
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <time.h>
#include <time.h>

#if INCLUDE_HARDWARE_SPI
// SPI hardware interface
MD_MAX72XX mx = MD_MAX72XX(CS_PIN, MAX_DEVICES);
#else
// Arbitrary pins
MD_MAX72XX mx = MD_MAX72XX(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
#endif

int i ;
int t ;

int c ;
int r ;
int d;
int botc;
int botr;

//____________Joystick_______________________________
// function to move the dot one space to the right

void moveRight()
{
  c = c - 1;
  if (c < 0)
  {
    c = 0;
  }
}

// function to move the dot one space to the left
void moveLeft()
{
  c = c + 1;
  if (c > 7)
  {
    c = 7;
  }
}

// function to move the dot one space down
void moveUp()
{
  r = r * 2;
  if (r > 128 )
  {
    r = 128;
  }
}

// function to move the dot one space down
void moveDown()
{
  r = r / 2;
  if (r < 1)
  {
    r = 1;
  }
}



//___________________Random Dot by robot___________________________

int o;     // bot row
int p;     // bot column
// function to move the dot one space to the right
void  botmoveRight()
{
  p = p - 1;
  if (p < 0)
  {
    p = 0;
  }
}

// function to move the  bot dot one space to the left
void botmoveLeft()
{
  p = p + 1;
  if (p > 7)
  {
    p = 7;
  }
}

// function to move the bot dot one space up
void botmoveUp()
{
  o = o * 2;
  if (o > 128 )
  {
    o = 128;
  }
}

// function to move the bot dot one space down
void botmoveDown()
{
  o = o / 2;
  if (o < 1)
  {
    o = 1;
  }
}

void humanPlayer()
{
  i = analogRead(A0);
  Serial.println(i, DEC);

  t = analogRead(A1);
  Serial.println(t, DEC);

  if (i <= 500 )
  {
    moveRight();
  }
  if (i >= 550 )
  {
    moveLeft();
  }
  if (t > 500 )
  {
    moveUp();
  }
  if (t < 450 )
  {
    moveDown();
  }
}
void roBot()
{
  botc = random(1000);
  botr = random(1000);

  if (botc <= 333 )
  {
    botmoveRight();
  }
  if (botc >= 666 )
  {
    botmoveLeft();
  }
  if (botr >= 666)
  {
    botmoveUp();
  }
  if (botr <= 333 )
  {
    botmoveDown();
  }
}
void endGame()
{
  if (c == p)
  {
    mx.setColumn(c, r + o); // Set joystick and bot dot on same column
  }
  else
  {
    mx.setColumn(c, r);   // set joystick dot
    mx.setColumn(p, o);   // set bot dot
  }

  delay(d);
  mx.clear();
}
//___________________Main Loop__________________
void setup()
{
  randomSeed(analogRead(152));
  mx.begin();
  Serial.begin(19200);
  c = 7;
  r = 128;
  p = 0;
  o = 1;
  int repeats;
  //for (repeats = 0; repeats < 9999; repeats++)
  d = 20;
  do
  {
    //----------- game 1  -----------------------------
    mx.setColumn(4,  1);
    mx.setColumn(5,   32 + 16 + 8 + 4 + 2 + 1);      //------#1
    mx.setColumn(6, 1 + 16);
    delay (1000);
    mx.clear();
    do
    {
      roBot();
      humanPlayer();

      endGame();
      d = d + 5;
      if (d == 350)
      {
        d = 20;
      }
    } while (r != o   || c != p );
    //-------------------------------------------------------------------game 2 --------------------------------------
    mx.setColumn(7, 8 + 1);
    mx.setColumn(6, 16 + 2 + 1);                  //-------------#2
    mx.setColumn(5, 16 + 4 + 1);
    mx.setColumn(4, 8 + 1);
    delay (1000);
    mx.clear();
    c = 7;
    r = 128;
    p = 0;
    o = 1;
    d = 10;
    do
    {
      roBot();

      humanPlayer();
      endGame();
    } while (r != o   || c != p );
    //------------------------------------------game 3 ---------------------------------------
    mx.setColumn(6, 1 + 4 + 16);
    mx.setColumn(5, 1 + 4 + 16);    //----------# 3------------
    mx.setColumn(4, 2 + 8);
    delay(1000);


    mx.clear();
    d = 1200;
    c = 7;
    r = 128;
    p = 0;
    o = 1;
    do
    {
      roBot();

      humanPlayer();

      endGame();
      d = d - 5;
      if (d == 5)
      {
        d = 800;
      }
    } while (r != o   || c != p );
    //-------------- Test if the dots are in the same column or not ------------
  } while (r != o   || c != p );


  //-----------  dots are in the same location -----
  //-------------------- GAME OVER -----------------
  mx.setColumn(1, 8);
  mx.setColumn(2, 4 + 32 + 64);
  mx.setColumn(3, 4);
  mx.setColumn(4, 4);                    //smiley face
  mx.setColumn(5, 4 + 32 + 64);
  mx.setColumn(6, 8);
  delay(1000);
  mx.setColumn(1, 8 + 32);
  mx.setColumn(2, 4 + 32);
  mx.setColumn(3, 4);
  mx.setColumn(4, 4);                    //smiley face wink
  mx.setColumn(5, 4 + 32 + 64);
  mx.setColumn(6, 8);
  delay(200);
  mx.setColumn(1, 8);
  mx.setColumn(2, 4 + 32 + 64);
  mx.setColumn(3, 4);
  mx.setColumn(4, 4);                    //smiley face
  mx.setColumn(5, 4 + 32 + 64);
  mx.setColumn(6, 8);
  delay(1000);
  mx.begin();


}

void loop()
{

}
