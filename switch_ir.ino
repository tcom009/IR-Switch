#include "IRremote.h"
int receiver = 11;

IRrecv irrecv(receiver);
decode_results results;



const int relay1 = 7;
const int relay2 = 8;
const int relay3 = 12;
const int relay4 = 13;

const int btn1 = 2;
const int btn2 = 3;
const int btn3 = 4;
const int btn4 = 5;

int estadoLuz1 = 0;
int estadoLuz2 = 0;
int estadoLuz3 = 0;
int estadoLuz4 = 0;

int estadoBtn1 = 1;
int estadoBtn2 = 1;
int estadoBtn3 = 1;
int estadoBtn4 = 1;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);

}


void setEstadoLuz (int estado, int luz) {
  
  switch (luz) {
    case 1 :
      estadoLuz1 = estado;
      break;

    case 2 :
      estadoLuz2 = estado;
      break;

    case 3 :
      estadoLuz3 = estado;
      break;

    case 4 :
      estadoLuz4 = estado;
      break;

  }
}




void verificarBtn(int relay, int numeroBtn, int estadoLuz, int numeroLuz) {
  int lectura = digitalRead (numeroBtn);
  if ( lectura != HIGH) {
    delay (500);
    Serial.println ("el boton ha sido pulsado");

    if (estadoLuz == 1) {
      digitalWrite (relay, LOW);
      Serial.print ("Luz ");
      Serial.print (numeroLuz);
      Serial.println (" Apagada");
      
      setEstadoLuz (0, numeroLuz);
    }
    
    else {
      if (estadoLuz == 0) {
        digitalWrite (relay, HIGH);
        Serial.print ("Luz ");
        Serial.print (numeroLuz);
        Serial.println (" Encendida");
        estadoLuz = 1;
        setEstadoLuz (1, numeroLuz);
      }
    }
  }
}



void irFunction (){
  
    if (irrecv.decode(&results))

  {
    switch (results.value)
    {
      //foco 1

      case 0x0020DF8877:
        //encendido
        Serial.println("Luz 1 encendida por IR");
        digitalWrite (relay1, HIGH);
        estadoLuz1 = 1;

        break;


      case 0x0020DF48B7 :
        //apagado
        Serial.println("Luz 1 apagada por IR");
        digitalWrite (relay1, LOW);
        estadoLuz1 = 0;
        break;


      //foco2

      case  0x0020DFC837 :
        
        Serial.println("Luz 2 encendida por IR");
        digitalWrite (relay2, HIGH);
        estadoLuz2 = 1;
        break;

      case 0x0020DF28D7 :
        
        Serial.println("Luz 2 apagada por IR");
        digitalWrite (relay2, LOW);
        estadoLuz2 = 0;
        break;

      //foco3
     case 0x0020DFA857  :
        
        Serial.println("Luz 3 encendida por IR");
        digitalWrite (relay3, HIGH);
        estadoLuz3 = 1;
        break;

      case 0x0020DF6897 :
        
       Serial.println("Luz 3 apagada por IR");
        digitalWrite (relay3, LOW);
        estadoLuz3 = 0;
        break;

      
      //foco4 
      case 0x0020DFE817  :
        
        Serial.println("Luz 4 encendida por IR");
        digitalWrite (relay4, HIGH);
        estadoLuz4 = 1;
        break;

      case 0x0020DF18E7 :
        
        Serial.println("Luz 4 apagada por IR");
        digitalWrite (relay4, LOW);
        estadoLuz4 = 0;
        break;

    }
    irrecv.resume();
  }

  }



void loop(){

  
  irFunction();

  verificarBtn (relay1, btn1, estadoLuz1, 1);
  verificarBtn (relay2, btn2, estadoLuz2, 2);
  verificarBtn (relay3, btn3, estadoLuz3, 3);
  verificarBtn (relay4,btn4, estadoLuz4, 4);

}
