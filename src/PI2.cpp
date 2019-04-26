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

void conta() // contatdor de pulso da interrupção
{
  RPM++; // incrementa um a cada vez que a interupçãofor ativa
}

void setup()
{
  RPM=0; //zera a variavel rpm
  //tempo=0; variavel não usado
  pinMode(cs_pin, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(conttemp), conta, FALLING);//borda de decida conttemp é o pino 3
  Serial.println("Inicializando cartao SD...");  
 if (!SD.begin(cs_pin)) 
  {
    Serial.println("Falha na Inicializacao!");
    //return; // desabilitado retorno do SD card se não abrir cartão
  }
  Serial.println("Inicializacao concluida");
  
}
  
//____________________________________________________________________

void grava() // grava os dados do rpm no cartão sd
{  
                                if (meuArquivo=SD.open("Rpm.txt",FILE_WRITE)) // abri arquivo RPM.txt sempre no fim de linha
                                {          
                                meuArquivo.println(RPM); // grava no arquivo em cartão 
                                meuArquivo.close(); // fecha arquivode gravação
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



void loop()  // programa principal
{ 
  RPM=0;  
  delay(5000);
  //detachInterrupt(digitalPinToInterrupt(conttemp));  // desliga a interrupção
  RPM= RPM*12;
  Serial.print(RPM);
  Serial.println(" RPM");
  grava(); 
}
 





