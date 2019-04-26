#include <arduino.h>
#include <SD.h>
#include <SPI.h>
//#include <TimerOne.h>

//Variaveis para cartao SD
#define cs_pin 4 
#define conttemp 3
int RPM;
int x;
int y;
int tempo;
File meuArquivo;



void setup()
{
  RPM=0;
  tempo=0;
  pinMode(cs_pin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Inicializando cartao SD...");  
 if (!SD.begin(cs_pin)) 
  {
    Serial.println("Falha na Inicializacao!");
    //return;
  }
  Serial.println("Inicializacao concluida");
 Serial.print();
  
}
  
//____________________________________________________________________

void grava() // grava os dados do rpm no cartão sd
{  
                                if (meuArquivo=SD.open("Rpm.txt",FILE_WRITE)) 
                                {          
                                meuArquivo.println(RPM);
                                meuArquivo.close();
                                }      
}


     //_função de minutos desativado_______________________________________________

   /*  void t()
 {
  

//for (y=0;y<60;y++)
           // {
               //   for (x=0;x<60;x++)
                //  {
                 //  if(x==59)
                 //  {  
                  //  grava();
                  // }
                 // }
            
           // }

     //tempo=tempo+1;
 
 }  
*/
 //___________________________________________
void conta() // contatdor de pulso da interrupção
{
  RPM++;
}


void loop()  // programa principal
{ 
  RPM=0;  
  //attachInterrupt(0,conttemp,FALLING); // borda de decida conttemp é o pino 3
  attachInterrupt(digitalPinToInterrupt(conttemp), conta, FALLING);

  delay(5000);
  detachInterrupt(digitalPinToInterrupt(conttemp));
  //detachInterrupt(0); // desliga a interrupção;
  
  RPM= RPM*12;
  delay(10);
  Serial.print(RPM);
  delay(10);
  Serial.println(" RPM");
  grava(); 
}
 





