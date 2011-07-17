// LCD DISPLAY KODE
// cip ved stik HD74HC245
// hukommelse tb62706an /http://pdf1.alldatasheet.com/datasheet-pdf/view/31602/TOSHIBA/TB62706.html

// HUSK AT DIR SKAL S�TTES TIL H�J (STIK 14)  (s� f�r du str�m direkte fra kasserne)
// stik 5 er ground

# define serial_red_1 7 // stik 1
# define serial_red_2 8 // stik 2
# define clock 2 // stik 6
# define latch 3 // stik 7
# define enable 4 // stik 8
# define serial_green_1 6 // stik 10
# define serial_green_2 5 //stik 9

# define num_panels 2 // number of screens
# define red 1
# define green 2
# define yellow 3
# define black 0
# define selectorPot 0 // the program selection potmeter
# define speedPot 2 // speed potmeter
# define jack 2 // line in signal



long lasttime = 0; // global timer variable
int xstep=0; // global variable for lines routine
byte redscreen[num_panels * 16][8]; // seperate layer for red pixels
byte greenscreen[num_panels * 16][8]; // seperate layer for green pixels

void lines() // abstract scrolling lines, play around with division factors in setPixel lines and xstep for new patterns
{
  setPixel(0,(xstep/2)%8,1); //draw red point
  setPixel(0,(((xstep/1)-1)%8),0); //erase previous point
  setPixel(0,(xstep/3)%8,2); //draw green point
  setPixel(0,(((xstep/7)-1)%8),0); //erase previous point
  if (xstep>1000) xstep=0;  // 1000 could be changes with pot meter read?

}

void vu(int color) // classic vu meter
{
  int potVal = analogRead(jack); // read line in signal
  for(int udslag = 0 ; udslag < ((potVal+1) / 64 ) * num_panels ; udslag ++)
  {
    for(int xdummy = 0; xdummy < 8; xdummy++)
    {
       setPixel(udslag,xdummy,color);  
    }
  }
  
  for(int rest = ((potVal+1) / 64 ) * num_panels ; rest < num_panels * 16; rest ++)
  {
    for(int xdummy = 0; xdummy < 8; xdummy++)
    {
       setPixel(rest, xdummy, 0);
    }
  }
}

void paintsomething() // trash routine to get some grfx
{
  for(int dummy=0;dummy<8;dummy++)
  {
    setPixel(dummy*5,dummy,1);
    setPixel(dummy*5+1,dummy,2);
  }
}


void drawblock(int x,int y,int size,int color) // ultra lo-res block drawing routine
{
  for(int xloop=x;xloop<(x+size);xloop++)
  {
    for(int yloop=y;yloop<(y+size);yloop++)
    {
    setPixel (xloop,yloop,color);
    }
  }
}

void tonebar(int pos) // central, mirrored tonebar drawn at pos, combine with scroller for oscilloscope efx
{
  int value = analogRead(jack); // read line in
  for (int x=0; x<4; x++)
  {
    setPixel(pos,x,((value+1)/256)<x); // if statement TRUE then paint red (1)
  }
  for (int x=0; x<4; x++)
  {
    setPixel(pos,7-x,((value+1)/256)<x); // FALSE = black / 0
  }
}

void scrollxred() // scroll only red colors one pixel
{
  for (int xpush=1 ; xpush < num_panels*16;xpush++)
  {
    for (int ydummy=0; ydummy < 8; ydummy++)
    {
      redscreen [xpush-1][ydummy] = redscreen [xpush][ydummy];
    }
  }
}


void scrollxgreen() // scroll only green colors one pixel
{
  for (int xpush=1 ; xpush < num_panels*16;xpush++)
  {
    for (int ydummy=0; ydummy < 8; ydummy++)
    {
      greenscreen [xpush-1][ydummy] = greenscreen [xpush][ydummy];
    }
  }
}

void setup()
{
  //Serial.begin(9600);
  pinMode(clock, OUTPUT); 
  pinMode(enable, OUTPUT); 
  pinMode(latch, OUTPUT); 
  pinMode(serial_red_1, OUTPUT); 
  pinMode(serial_green_1, OUTPUT);
  pinMode(serial_green_2, OUTPUT);
  pinMode(serial_red_2, OUTPUT);
  pinMode(13, OUTPUT); //led out
  digitalWrite(13, HIGH);
  boolean ishigh = true; 
}



void loop()
{

 int program = analogRead(selectorPot); // read from the program selection potentiometer
  
  if (program<100)
  {
    lines();
    scrollxred();
    scrollxgreen();
  }

  if (program>=100 && program<200)
  {
    vu(red);
  }

  if (program>200 && program<400)
  {
    tonebar(0);
    scrollxred();
  }

  if (program>=300 && program<500)
  {
    for(int dummy=0;dummy<num_panels*16;dummy++)
    {
    tonebar(dummy);
    }
  }

  if (program>=500 && program<600)
  {
    drawblock (0,0,8,yellow);
    drawblock (0,8,8,black);
    drawblock (0,16,8,yellow);
    drawblock (0,24,8,black);
    print();
    delay(10);
 
    drawblock (0,0,8,black);
    drawblock (0,8,8,yellow);
    drawblock (0,16,8,black);
    drawblock (0,24,8,yellow);
    print();
    delay(10);
  }
  
  if (program>=600 && program<700)
  {
    scrollxred();
  }
  if (program>=700 && program<800)
  {
    scrollxgreen();
  }

  // hey: man kan blande programmer ved at lade deres gr�nsev�rdier g� ind over hinanden!!
  
  //tonebar(color);
  //scrollxred or scrollxgreen;
  //drawblock(x,y,size,color);
  //vu(color);
  //lines();

  if (millis() > lasttime + analogRead(speedPot))  // pause routine
  {
    xstep ++;
    lasttime = millis();
    print();
 }  

}

// ***********************************************
// drawing routine, updating entire LED display(s)
// ***********************************************

void print()
{

  digitalWrite(latch, LOW);
  digitalWrite(enable,LOW);
  digitalWrite(clock,LOW);
  delayMicroseconds(1);

  for(int panel= num_panels-1; panel >= 0; panel--)
  {
     for(int block = 4; block >=  1; block --)
     {
        for(int h = 3; h >= 0; h--)
        {
           for(int w = 3; w >= 0; w--)
           {
             int w_pos = panel* 4 *4 +  block* 4 - 4 + w;
           
             digitalWrite(serial_red_1,redscreen[w_pos][h] == 1);
             digitalWrite(serial_green_1,greenscreen[w_pos][h] == 1);
             digitalWrite(serial_red_2,redscreen[w_pos][h+ 4] == 1);
             digitalWrite(serial_green_2,greenscreen[w_pos][h + 4] == 1);
             
             digitalWrite(clock,HIGH);
             delayMicroseconds(1);
             digitalWrite(clock,LOW);
             delayMicroseconds(1);
           }
        }
     }
  }


    digitalWrite(latch, HIGH);
    delayMicroseconds(1);
    digitalWrite(latch, LOW);
    digitalWrite(enable, LOW);
 
}

// ***********************************************
// Sets the pixel at x,y to the given color
// ***********************************************
 
void setPixel( int x, int y , int color)
{
  // Bounds check
  if( x < 0 || x > num_panels*16-1 ) return;
  if( y < 0 || y > 8 ) return;
 
  if (color==1 || color==3)
  {
  // The x axis is flipped in the screen buffer:
  redscreen[ num_panels*16 - 1 - x ][y] = 1;
  //screen[ x ][y] = color;
  }
  if (color==2 || color==3)
  {
  // The x axis is flipped in the screen buffer:
  greenscreen[ num_panels*16 - 1 - x ][y] = 1;
  //screen[ x ][y] = color;
  }
  if (color==0)
  {
  // The x axis is flipped in the screen buffer:
  greenscreen[ num_panels*16 - 1 - x ][y] = 0;
  redscreen[ num_panels*16 - 1 - x ][y] = 0;
  //screen[ x ][y] = color;
  }
}

// ***********************************************
// Add the given color to the pixel at x,y (bitwise or)
// ***********************************************
 
void addPixel( int x, int y, byte color )
{
  // Bounds check
  if( x < 0 || x > num_panels*16-1 ) return;
  if( y < 0 || y > 8 ) return;
 
  // The X axis is flipped in the screen buffer:
  greenscreen[ num_panels*16 - 1 - x ][y] |= color;
  //screen[  x ][y] |= color;
}
