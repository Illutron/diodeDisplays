

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

// ##### INPUTS ####

# define sound_in 5
# define pot_one 2
# define pot_two 2
# define movement 9
// ### OUTPUT ##########

# define status_led 10


// ### VARIABLES ######
#include "WProgram.h"
void timechk();
void loop();
int do_automatic_mode();
void show_mode(int smode);
void virus();
void virus_do(int x, int y);
void train();
void matrix();
byte getcolor(boolean color);
void stargase();
void vol_meter();
void draw_picture();
void picture_move();
void move_forward(boolean cycle);
void move_back(boolean cycle);
void move_up(boolean cycle);
void vol_visual();
void vol_wave();
void setup();
void clear_scr();
void set_color(int color);
void print();
void volume();
int abs2(int value);
void beat();
boolean changed= false;
int system_mode = 0;
int num_modes = 18;

boolean printit = true;
int current_volume =0;
boolean current_beat = false;

byte picture[num_panels * 16][8];

long automatic_last_time =0;
long move_last = 0;
long text_last_time = 0;
long matrix_last_time;
float running_vol_avg;
int train_num = 0;
int amount;


// ######## LOGIC ##################

int x_mode = -1;

long last_time_chk =0;
void timechk()
{
  if (last_time_chk > millis() )
  {
     automatic_last_time =0;
    move_last = 0;
    text_last_time = 0 ;
    matrix_last_time =0;
  }
}

void loop()
{
timechk();
  picture[random(num_panels * 16)][random(8)] =random(3);
  move_up(true);
  print();

}


int automatic_current_mode = 0;

long automatic_pause = 0;
int do_automatic_mode()
{

  if (millis() >= automatic_pause + automatic_last_time)
  {
    automatic_current_mode = automatic_current_mode+ random(-8,8);
    if (automatic_current_mode < 0 || automatic_current_mode >= num_modes-1)
    {
      automatic_current_mode = 4; 
    }

  
    if (automatic_current_mode % 2 == 0)
    {
      automatic_pause = random(500,3000);
    }
    else
    {
      automatic_pause = random(2000,5000);
    }

    automatic_last_time = millis();
  }

  return automatic_current_mode;

}




void show_mode(int smode)
{
  //  stargase();
   train();
 /* int mode = smode;
  if (mode % 2 == 0)
  {
    if (move_last + 10 < millis())
    {
      move_last = millis();
      switch(random(3.5))
      {
        case 0:
          move_up(true);
          break;
        case 1:
           move_forward(true);
          break;
        case 2:
          move_back(true);
         break;
        case 3:
         move_up(true);
         break;
        
      }
     
    }  


  }
  else
  {
    switch (mode - mode / 2 )
    {
      case 0:
       set_color(red_green);
       break;
    case 1:
     virus();
     

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
      //snake();
      stargase();
     
      break;
    case 6:
      matrix();
      break;
    case 7: 
      vol_wave();
      
      break;
    case 8:
    //  mikro_disko(); 
      stargase();
      break;


    }
 
  // mikro_disko(); 
 
  }*/

}



// ### VISUALISERS ###########################

void virus()
{
   if (current_beat && random(100) > 50)
   {
      int x = random(1,num_panels * 16-2);
      int y =random(1,6);
      int color = random(0,3); 
       picture[x][y] = color;
       picture[x][y-1] = color;
       picture[x][y+1] = color;
       picture[x-1][y] = color;  
       picture[x+1][y] = color; 
   }
   
   int start_pos = random(10, num_panels * 16-10);
   
   if (random(100) > 50)
   {
   for (int x=start_pos; x < num_panels * 16-1; x ++)
   {
     for (int y=1; y < 7; y ++)
     {
      virus_do( x,  y);
    } 
   }
   }
   else
   {
    for (int x=start_pos; x >= 1; x--)
   {
     for (int y=1; y < 7; y ++)
     {
      virus_do( x,  y);
    } 
   } 
   }
  
}

void virus_do(int x, int y)
{
  if (x > 0 && x < num_panels * 16 -1 && y > 0 && y< 7)
  {
      if (picture[x][y] > 0 && random(100) > 50) // virus
      {
         picture[x+ random(-1,1)][y+ random(-1,1)] = picture[x][y];
          picture[x+ random(-1,1)][y+ random(-1,1)] = picture[x][y];
      }
      else if (picture[x][y] == 0 && random(100) > 70)
      {
          picture[x+ random(-1,1)][y+ random(-1,1)] = picture[x][y];
          picture[x+ random(-1,1)][y+ random(-1,1)] = picture[x][y];
      }
  }
   
}

int train_pos = 0;

void train()
{
  
  if (matrix_last_time + 100 < millis())
  {
    
    matrix_last_time = millis();
    move_forward(false); 
     // cars
     if(random(400) < 10)
     {
     amount = max(0,min(current_volume/20,10)-2);
     if (running_vol_avg < 100)
    for (int i = 0; i  < random(amount);i++)
    {
     int value = random(7);
     picture[num_panels * 16 -1][value] = green;
   //  picture[num_panels * 16 -2][value] = green;
    }
    if (current_volume > 10 && train_num == 0)
    {
      train_num = random(4,7);
      train_pos = random(0,7);
    }
    if (train_num > 0)
    {
      train_num--;
      picture[num_panels * 16 -1][train_pos] = red;
    }
     }
 
    
  }
}

void matrix()
{
  if (matrix_last_time + 15 < millis())
  {
  
    matrix_last_time = millis();
    move_forward(false); 
  for (int i = 0; i  < random(4);i++)
  {
   int value = random(8);
 picture[num_panels * 16 -0][value] = random(4);;
 picture[num_panels * 16 -1][value] = random(4);
  }
 
   
  }
}


byte getcolor(boolean color)
{
  if (color)
  {
    return random(1,3);
  }
  return 0;
}





void stargase()
{

 
}


void vol_meter()
{

   int length = 8 * (float)num_panels * ((float)current_volume / (float)600);
clear_scr();
  for (int x = 0; x < length; x ++)
  {
    for (int y = 0; y < 8;y++)
    {
      picture[num_panels*8-x][y] = green;
      picture[num_panels*8+x][y] = green;

    }
  }
}

void draw_picture()
{
  clear_scr();
  int colors[50] = {
    0,0,0,0,2,2,2,2,0,0,0,1,1,1,0,0,0,0,0    };


  int count =0;
  while (count < 30)
  {
    
    int color = random(3);
    int i = 0;
    int amount =0;
    if (color == 0)
      amount = 4;
    else
      amount = random(5);
      
    for (i;i < amount;i++)
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
  if (changed)
  {
    draw_picture();
    //Serial.println("dr");
  }
  if(current_beat)
  {
    move_forward(true);


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




void move_back(boolean cycle)
{
  int tmp[8];
  for (int i = 0; i < 8 ; i ++)
  {
    tmp[i] =   picture[num_panels* 16 -1][i] ;
  }
  for (int x = num_panels* 16-1; x > 0; x --)
  {
    for (int y = 0; y < 8;y++)
    {

      picture[x][y] = picture[x-1][y] ;

    }


  }
  if (cycle)
  {
    for (int i = 0; i < 8 ; i ++)
    {
      picture[0][i]=tmp[i] ;
    }
  }
  else
  {
    for (int i = 0; i < 8 ; i ++)
    {
      picture[0][i]=0 ;
    }
  }
}


void move_up(boolean cycle)
{
  int tmp[num_panels * 16];
  for (int i = 0; i < num_panels * 16 ; i ++)
  {
    tmp[i] =   picture[i][0] ;
  }
  for (int x = 0; x < num_panels* 16; x ++)
  {
    for (int y = 0; y < 7;y++)
    {

      picture[x][y] = picture[x][y+1] ;

    }


  }
  if (cycle)
  {
    for (int i = 0; i < num_panels * 16 ; i ++)
    {
      picture[i][7]=tmp[i] ;
    }
  }
  else
  {
    for (int i = 0; i < num_panels * 16 ; i ++)
    {
      picture[i][7]=0 ;
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
      picture[pos][y] = red_green ;

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
      int vol = analogRead(sound_in)- 512;
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




void setup() {
 // wdt_enable(WDTO_2S);
  Serial.begin(9600);
  pinMode(clock, OUTPUT);  
  pinMode(enable, OUTPUT);  
  pinMode(latch, OUTPUT);  
  pinMode(serial_red_1, OUTPUT);  
  pinMode(serial_green_1, OUTPUT);
  pinMode(serial_green_2, OUTPUT);
  pinMode(serial_red_2, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  pinMode(status_led, OUTPUT);
  pinMode(movement,INPUT);
  boolean ishigh = true;
 set_color(red);
 print();
// wdt_reset();

}


// ### DISPLAY API

void clear_scr()
{
  set_color(0);
}

void set_color(int color)
{
  for (int x = 0; x < num_panels * 16; x ++)
  {
    for (int y = 0; y < 8;y++)
    {
      picture[x][y] = color;
    }
  }
}


void print()
{

  digitalWrite(latch, LOW);
  digitalWrite(enable,LOW);
  digitalWrite(clock,LOW);
  delayMicroseconds(1);

  for(int panel= num_panels*2-1; panel >= 0; panel--)
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

// ### SOUND API #######
;

void volume()
{

  float avg = 0;
  for (int i = 0; i < 20; i++)
  {
    avg = avg * 0.9 + float(abs2(analogRead(sound_in)- 512)) * 0.1;
    // avg = avg * 0.9 + float(abs2(random(1024)- 512)) * 0.1;
  }
  running_vol_avg = running_vol_avg * 0.95 + float(abs2(avg)) * 0.05;
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


  if ( running_vol_avg * 1.2 < current_volume && current_volume > 50 )
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

