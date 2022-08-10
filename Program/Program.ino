#include <multilcd.h>        
#include <LiquidCrystal.h>    //Библиотеки необходимы для работы
 
LiquidCrystal lcd1(22, 23, 25, 26, 27, 28);
LiquidCrystal lcd2(22, 24, 25, 26, 27, 28);       //Подключение LCD-дисплея
MultiLcd lcd;
float max;
float adc_int[200]; 
double xold = 0;
float AkWh;
float AkWhp;
float AkWhq;
long int timing;
bool flag=false;
bool flag1=false;
byte fi [8] = {
  B00010,
  B10101,
  B10101,
  B10101,
  B01110,
  B00100,
  B00100,
  B00100
};

void setup() {
 
 Serial.begin(9600);
 while (!Serial) {
  }
 
  lcd.attach(lcd1);
  lcd.attach(lcd2);           //Инициализация работы с LCD дисплеем
  lcd.createChar(0,fi);       //Подключение частей дисплея и создание спец символов
  lcd.begin(40,2,1,2);
 
  pinMode(29,INPUT_PULLUP);
}
 
void loop() {               
for(int i=0; i<=199; i++){                  
          adc_int[i] = abs(analogRead(A4));           //Считывание величины активного и реактивного тока
           }
          max = adc_int[0];
   for(int i=0; i<=199; i++){   
           if(max<adc_int[i])
           max=adc_int[i];   
           }
 
  float IR = max * (5.0 / 1023.0);
  IR=IR*0.707;
 
for(int i=0; i<=199; i++){
          adc_int[i] = abs(analogRead(A5)); 
           }
         max = adc_int[0];
   for(int i=0; i<=199; i++){   
           if(max<adc_int[i])
           max=adc_int[i];   
           }
 
  float IX = max * (5.0 / 1023.0);
  IX=IX*0.707;
 
float I = sqrt(square(IR)+square(IX));          //Расчёт напряжения, косинуса фи, 
I=I*3.7;                                        //активной, реактивной, полной мощности
float VR = IR*5.00;
float VX = VR;
float V = VX*69.58;
float cosf = IR/(I/3.7);
float sinf = IX/(I/3.7);
float P=I*V*cosf;
float Q=I*V*sinf;
float S=sqrt(square(P)+square(Q));
 
int   xnew =  millis()/1000 - xold;
      xold = millis()/1000;
 
float kW = S/1000 * xnew;                       //Расчёт затраченной энергии
      kW = kW/3600;                             //полной, активной и реактивной
      AkWh = kW + AkWh;
float kWp = P/1000*xnew;
      kWp = kWp/3600;
      AkWhp = AkWhp + kWp;
float kWq = Q/1000*xnew;
      kWq = kWq/3600;
      AkWhq = AkWhq + kWq;                    
 


lcd.clear();                            
lcd.print("P =");
lcd.setCursor(4,0);                           //Вывод параметров на дисплей
lcd.print(P);                                 //в зависимости от выбранного режима
lcd.setCursor(10,0);
lcd.print("Wt");
lcd.setCursor(12,0);
lcd.print(" Q =");
lcd.setCursor(17,0);
lcd.print(Q);
lcd.setCursor(23,0);
lcd.print("var");
lcd.setCursor(26,0);
lcd.print(" S =");
lcd.setCursor(31,0);
lcd.print(S);
lcd.setCursor(37,0);
lcd.print("VA");
lcd.setCursor(0,1);
lcd.print("U =");
lcd.setCursor(4,1);
lcd.print(V);
lcd.setCursor(10,1);
lcd.print("V");
lcd.setCursor(12,1);
lcd.print(" I =");
lcd.setCursor(17,1);
lcd.print(I);
lcd.setCursor(21,1);
lcd.print("A");
lcd.setCursor(26,1);
lcd.print(" Cos");
lcd.setCursor(30,1);
lcd.write(byte(0));
lcd.setCursor(31,1);
lcd.print(" =");
lcd.setCursor(34,1);
lcd.print(cosf);
lcd.setCursor(0,2);
lcd.print("Active E = ");
lcd.setCursor(11,2);
lcd.print(AkWhp);
lcd.setCursor(16,2);
lcd.print("kWh");
lcd.setCursor(20,2);
lcd.print("Reactive E = ");
lcd.setCursor(31,2);
lcd.print(AkWhq);
lcd.setCursor(36,2);
lcd.print("kWh");
lcd.setCursor(11,3);
lcd.print("Full E = ");
lcd.setCursor(20,3);
lcd.print(AkWh);
lcd.setCursor(25,3);
lcd.print("kWh");
delay(1000);}
