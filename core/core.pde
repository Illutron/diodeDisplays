// LCD DISPLAY KODE
// cip ved stik HD74HC245 
// hukommelse tb62706an /http://pdf1.alldatasheet.com/datasheet-pdf/view/31602/TOSHIBA/TB62706.html

// HUSK AT DIR SKAL S®TTES TIL H¯J (STIK 14)  (sŒ fŒr du str¿m direkte fra kasserne)
// stik 5 er ground

// old pin interface
# define serial_red_1 7 // stik 1
# define serial_red_2 8 // stik 2
# define clock 2 // stik 6
# define latch 3 // stik 7
# define enable 4 // stik 8
# define serial_green_1 6 // stik 10
# define serial_green_2 5//stik 9


/* New version
# define serial_red_1 3 // stik 1
# define serial_red_2 2 // stik 2
# define clock 4 // stik 6
# define latch 6 // stik 7
# define enable 5 // stik 8

# define serial_green_2 8//stik 9
# define serial_green_1 7 // stik 10
*/
# define num_panels 6
# define red 1
# define green 2
# define red_green 3
# define black 0


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

   
 
   
}

byte getcolor()
{
  if (random(10) > analogRead(4)/100)
  {
     return random(1,3); 
  }
  return 0;
}



long lasttime = 0;
int color = 1;
void loop()
{

 
  print();
 
 if (millis() > lasttime + 500)
 {
 lasttime = millis();
   if ( color ==1 )
  {
    color = 2;
  }
  else
  {
   color = 1; 
  }
  
 for (int x =0; x < 8;x++)
 {
   
   for (int y =0; y < num_panels * 16;y++)
 {
   
    picture[y][x] = color;
 }
 }
 
 }
 
  for (int i = 0; i < num_panels; i ++)
  {
     for (int b=0; b <= i; b++)
     {
       picture[i * 16 + b][2] = red;
       picture[i * 16 + b][3] = green;
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
             digitalWrite(clock,LOW);
             delayMicroseconds(10);
             digitalWrite(clock,HIGH);
             delayMicroseconds(10);
             digitalWrite(clock,LOW);
             delayMicroseconds(2);
            
           }
        }
     }
  }

delayMicroseconds(2);
    digitalWrite(latch, HIGH);
    delayMicroseconds(2);
    digitalWrite(latch, LOW);
    digitalWrite(enable, LOW); 
    delayMicroseconds(2);
 
 
  
  
}

