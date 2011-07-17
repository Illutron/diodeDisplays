// LCD DISPLAY KODE
// cip ved stik HD74HC245 
// hukommelse tb62706an /http://pdf1.alldatasheet.com/datasheet-pdf/view/31602/TOSHIBA/TB62706.html

// HUSK AT DIR SKAL S\ufffdTTES TIL H\ufffdJ (STIK 14)  (s\ufffd f\ufffdr du str\ufffdm direkte fra kasserne)
// stik 5 er ground


# define serial_red_1 7 // stik 1
# define serial_red_2 8 // stik 2
# define clock 2 // stik 6
# define latch 3 // sanatik 7
# define enable 4 // stik 8
# define serial_green_1 6 // stik 10
# define serial_green_2 5//stik 9


# define num_panels 1
# define red 1
# define green 2
# define red_green 3
# define black 0
#include "WProgram.h"
void setup();
byte getcolor(boolean color);
void stargase();
void vol_meter();
void mikro_disko();
void draw_picture();
void picture_move();
void move_forward(boolean cycle);
void snake();
void snake2();
void move_back(boolean cycle);
void vol_visual();
void vol_wave();
void loop();
void clear_scr();
void print();
void matrix();
void volume();
int abs2(int value);
void beat();
int last_value = 0;
int current = 0;

int current_volume =0;
boolean current_beat = false;

byte mikrodisko_text[] ={0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,0,0,1,0,1,0,0,1,0,1,0,1,1,0,0,1,1,0,0,0,1,1,1,0,1,0,0,1,1,1,0,1,0,0,1,0,0,1,1,0,0,0,1,0,0,1,0,0,1,0,1,0,1,0,1,0,0,1,1,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0,1,0,0,0,0,1,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,1,0,1,1,0,0,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,1,0,0,1,1,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,1,0,1,0,1,0,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,1,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,1,0,1,0,0,1,0,1,0,0,0,0,0,1,1,0,0,0,1,1,1,0,1,0,1,1,1,0,0,1,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


byte picture[num_panels * 16][8];

void setup()
{
  pinMode(clock, OUTPUT);  
  pinMode(enable, OUTPUT);  
  pinMode(latch, OUTPUT);  
  pinMode(serial_red_1, OUTPUT);  
  pinMode(serial_green_1, OUTPUT);
  pinMode(serial_green_2, OUTPUT);
    pinMode(serial_red_2, OUTPUT);
   pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    boolean ishigh = true;

   Serial.begin(9600);	// opens serial port, sets data rate to 9600 bps
Serial.println("hello");
 
   
}

byte getcolor(boolean color)
{
  if (color)
  {
     return random(1,3); 
  }
  return 0;
}



long lasttime = 0;

void stargase()
{
 
  int amount = 100;
  if (current_beat)
  {
    amount = 40;
  }
   for (int i =0; i < amount;i++)
  {
  
  
    picture[random(num_panels * 16)][random(8)] = getcolor(current_beat);
   
  
 }
  
}


void vol_meter()
{
  
  int length = 16 * (float)num_panels * ((float)current_volume / (float)600);
  clear_scr();
  for (int x = 0; x < length; x ++)
   {
  for (int y = 0; y < 8;y++)
  {
  
      picture[x][y] = green;
  
   }
 } 
}
 int move_mikro = 0;
void mikro_disko()
{
  clear_scr();
 
  if (current_beat)
  {
    move_mikro++;
    if (random(100) > analogRead(3)/10)
    {
       stargase(); 
    }
  }
  for(int i=0;i < 48 * 8 ; i ++)
  {
    if (mikrodisko_text[i] == 1)
    {
     picture[ i % 48+ move_mikro % 2][7 - i / 48] = mikrodisko_text[i];
    }
}
  
 
}

void draw_picture()
{
  clear_scr();
 int colors[50] = {0,0,0,0,2,2,2,2,0,0,0,1,1,1,0,0,0,0,0};
 
 
 int count =0; 
 while (count < 30)
 {
     int color = random(3);
     int i = 0;
     for (i;i < random(5);i++)
     {
       colors[i+ count] = color;
     }
     count = count + i;
 }

 for (int x = 0; x < num_panels* 16; x ++)
   {
  for (int y = 0; y < 8;y++)
  {

    picture[x][y] = colors[(x  + y+ 0) % 14] ;
 
   }
 } 
}

int move = 0;
void picture_move()
{
 if (current != last_value)
 {
    draw_picture(); 
 }
  if(current_beat)
  {
   move_back(true);
 
  
  }
 
}



void move_forward(boolean cycle)
{
  int tmp[8];
  for (int i = 0; i < 8 ; i ++)
  {
    tmp[i] =   picture[0][i] ;
  }
  for (int x = 0; x < num_panels* 16-1; x ++)
  {
    for (int y = 0; y < 8;y++)
    {

      picture[x][y] = picture[x+1][y] ;

    }


  }
  if (cycle)
  {
    for (int i = 0; i < 8 ; i ++)
    {
      picture[num_panels*16-1][i]=tmp[i] ;
    }
  }
  else
  {
    for (int i = 0; i < 8 ; i ++)
    {
      picture[num_panels*16-1][i]=0 ;
    }
  }
}



int dir = 0;
int snake_pos_x = 0;
int snake_pos_y = 0;
int snake_timer = 100;
void snake()
{
   if (current_beat)
   {
      
      move_back(false);
      int amount = (float)current_volume/600 * 8;
      int length = (float)current_volume/600 * (float)num_panels* 16;
  
       for (int i = 0; i < length  ;i++)
       {
            picture[i][amount] =red;
       }
  
   }
  
}

void snake2()
{
    if (millis() > lasttime + analogRead(3))
   {
   lasttime = millis();
     
      move_back(false);
      int amount = (float)current_volume/512 * 8;
     
      int color =random(1,2);
      
       for (int i = 0; i < amount  ;i++)
       {
          picture[num_panels*16-1][i] =red;
  
       }
      
     
      
   }
  
}

void move_back(boolean cycle)
{
  int tmp[8];
  for (int i = 0; i < 8 ; i ++)
  {
     tmp[i] =   picture[0][i] ;
  }
    for (int x = 0; x < num_panels* 16; x ++)
   {
    for (int y = 0; y < 8;y++)
    {
      
      picture[x][y] = picture[x+1][y] ;
 
     }
   
   
 } 
 if (cycle)
 {
    for (int i = 0; i < 8 ; i ++)
  {
     picture[num_panels*16-1][i]=tmp[i] ;
  }
 }
}

int pos = 0;
void vol_visual()
{
 
    pos = pos +1;
    if (pos >= num_panels* 16)
    {
       pos = 0; 
    }
    
       int amount = (float)current_volume / 600 * 8;
  for (int y = 0; y < 8;y++)
  {
  
    if (amount > y)  
    {
      picture[pos][y] = red ;
    }
    else
    {
     picture[pos][y] = black; 
    }
   }

  
}

void vol_wave()
{
   if (current_beat)
   {
  for (int x = 0; x < num_panels* 16; x ++)
   {
       int vol = analogRead(5)- 512;
       int amount = (float)vol / 600 * 8;
    for (int y = 0; y < 8;y++)
    {
  
      if (amount > y)  
      {
        picture[x][y] = red ;
      }
      else
      {
       picture[x][y] = black; 
      }
   }
   }
   }
}


void loop()
{
 
 volume();
 beat();
 current = (float)analogRead(2)/ (1024/ 8)+1;
// current = 8;
 
 
 switch (current)
   {
      case 1:
       stargase();
       break;
      case 2:
      vol_meter();
      break;
      case 3:
       vol_visual();
       break;
      case 4:
      picture_move();
      break;
      case 5:
      vol_wave();
      break;
      case 6:
      snake();
      break;
      case 7:
      snake2();
      break;
      case 8:
      matrix();
       break;
   }
   
  last_value = current;
 
  print();
}
void clear_scr()
{
  for (int x = 0; x < num_panels * 16; x ++)
 {
  for (int y = 0; y < 8;y++)
  {
    picture[x][y] = 0;
  }
 } 
}


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
            
             digitalWrite(serial_red_1,picture[w_pos][h] == 1 || picture[w_pos][h] == 3);
             digitalWrite(serial_green_1,picture[w_pos][h] == 2 || picture[w_pos][h] == 3);
             digitalWrite(serial_red_2,picture[w_pos][h+ 4] == 1 || picture[w_pos][h + 4] == 3);
             digitalWrite(serial_green_2,picture[w_pos][h + 4] == 2 || picture[w_pos][h +4 ] == 3);
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

long matrix_last_time = 0;
void matrix()
{
  if (matrix_last_time + 15 < millis())
  {
     matrix_last_time = millis();
     move_forward(false); 
     if (current_beat)
     {
   
  for (int i = 0; i  < random(8);i++)
  {
   int value = random(7);
 picture[num_panels * 16 -1][value] = green;
 picture[num_panels * 16 -2][value] = green;
  }
     }
 
  
  }
}

float running_vol_avg;

void volume()
{
 
  float avg = 0;
  for (int i = 0; i < 20; i++)
  {
    avg = avg * 0.9 + float(abs2(analogRead(5)- 512)) * 0.1;
  }
 running_vol_avg = running_vol_avg * 0.9 + float(abs2(avg)) * 0.1;
 current_volume = int(avg); 
}

int abs2(int value)
{
   if (value > 0)
    return value;
   
   return value * -1; 
}
int beat_last = false;

void beat()
{
  

 if ( running_vol_avg * 1.2 < current_volume && current_volume > 100 )
 {
     if (beat_last)
     {
        current_beat = false;
        return;
     }
     else
     {
       beat_last = true;
      
     }
     current_beat =  true;
     return;
 }
 else
 {
   beat_last = false;
   
 }
 current_beat = false;
}




int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

