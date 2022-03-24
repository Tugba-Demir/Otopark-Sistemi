#include <LCD5110_Basic.h>
#include <Servo.h>

#define btnGiris 2
#define btnCikis 6
#define ledAcik 4
#define ledKapali 5
int arabaSayisi = 0;
int kapasite = 5;
int bosAlan = 5;
int hangiButton;


Servo motor;
LCD5110 ekran(8,9,10,11,12);

extern uint8_t SmallFont[];

void setup() {
  Serial.begin(9600);
  pinMode(btnGiris,INPUT);
  pinMode(btnCikis,INPUT);
  pinMode(ledAcik,OUTPUT);
  pinMode(ledKapali,OUTPUT);
  motor.attach(3);

  ekran.InitLCD();
  ekran.setFont(SmallFont);
  ekran.clrScr();

  ekran.print("DEMIR",CENTER,15);
  ekran.print("OTOPARK'A",CENTER,20);
  ekran.print("HOS GELDINIZ",CENTER,25);
  delay(1000);

  yeniSayi();

}

void loop() {
  int btnGirisDeger = digitalRead(btnGiris);
  int btnCikisDeger = digitalRead(btnCikis);
  Serial.println(btnGirisDeger);
  
  if(btnGirisDeger == 1){
    hangiButton=1;
  }
  else if(btnCikisDeger == 1){
    hangiButton = 2; 
  }
  else if(btnGirisDeger==0 || btnCikisDeger==0){
    hangiButton = 0;
  }

  switch(hangiButton){
    case 0: motor.write(0); break; 
    case 1: Giris(); break;
    case 2: Cikis(); break;
  }
}

void Giris(){
  if(arabaSayisi>=kapasite){
    arabaSayisi=kapasite;
    motor.write(90);
  }
  else{
    arabaSayisi++;
    kapiDurum();
  }
  yeniSayi();
}
void Cikis(){
  if(arabaSayisi<=0){
    arabaSayisi = 0;
    bosAlan = kapasite;
    motor.write(90);
  }
  else{
    arabaSayisi--;
    kapiDurum();
  }
  yeniSayi();
}
void kapiDurum(){
  
  for(int i=90; i>0; i--){
    digitalWrite(ledAcik,HIGH);
    digitalWrite(ledKapali,LOW);
    motor.write(i);
    delay(20);
  }
  delay(1000);
  for(int i=0; i<=90; i++){
    motor.write(i);
    digitalWrite(ledAcik,LOW);
    digitalWrite(ledKapali,HIGH);
    delay(20);
  }
}
void yeniSayi(){
  bosAlan = kapasite-arabaSayisi;
  if(arabaSayisi>=kapasite){
    ekran.clrScr();
    ekran.print("OTOPARK DOLU!",CENTER,25);
  }
  else{
    ekran.clrScr();
    ekran.print(String(arabaSayisi),CENTER,15);
    ekran.print("Araba Var",CENTER,20);
    ekran.print(String(bosAlan),CENTER,35);
    ekran.print("Bos Alan Var",CENTER,40);
  }
  
}
