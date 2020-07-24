#include <SoftwareSerial.h>;
 
//define variaveis
#define RX_LEITOR   2 
#define TX_LEITOR   3 
#define RX_BT   4 
#define TX_BT   5
#define Reset   8 


SoftwareSerial objHC05Serial(RX_BT, RX_BT); // RX, TX
SoftwareSerial objLeitorSerial(RX_LEITOR, TX_LEITOR); // RX, TX
 
//Armazena o caracter recebido
char tagString[12];
int readByte;
int index = 0;
 
void setup() {
 
  Serial.begin(9600);
  objHC05Serial.begin(9600);
  objLeitorSerial.begin(9600);
  pinMode(Reset, OUTPUT);
  digitalWrite(Reset, HIGH);

}
 
void loop() {
 
  index = 0;
 
  //enquanto existir dado na porta serial
  if(objLeitorSerial.available() > 0) {
 
      //recebe o dado
      readByte = objLeitorSerial.read();
 
      //enquando não encontrar o retorno de carro
      while (index < 13 && readByte != 12) {
            //armazena o byte no array
            tagString[index] = readByte;
            //realiza a leirua do proximo byte
            readByte = objLeitorSerial.read();
            //incrementa contador
            index ++;
      }
 
      //se for o retorno de carro, chama metodo que envia a tag para o modulo hc05
      if(readByte == 12) {
        SendTag(tagString);
      } 
 
    delay(1000);
  }
}
 
//Envia um array de char contendo o numero do cartão para a TX do HC05
void SendTag(char datamessage[]){
    //escreve o dado na porta serial
    objHC05Serial.println(datamessage);
    Serial.println(datamessage); 
    //limpa o array para a proxima leitura e reseta o leitor
    clearTag(tagString);
}
 
//Metodo que limpa um array passado por parametro e reseta o leitor
void clearTag(char arrTag[]){
  digitalWrite(Reset, LOW);
  digitalWrite(Reset, HIGH);
  delay(150);
  for(int i = 0; i < strlen(arrTag); i++){
    arrTag[i] = 0;
  }
}
