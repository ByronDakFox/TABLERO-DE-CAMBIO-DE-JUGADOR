//Vector ABCDEFG PD
const byte numeral[10] = { //catodo comun
  B11111100,//0   HEX-->0XF6 DEC 252
  //B00000010 //0 -->Anaodo Comun
  B01100000,//1
  B11011010,//2
  B11110010,//3
  B01100110,//4
  B10110110,//5
  B00111110,//6
  B11100000,//7
  B11111110,//8
  B11100110,//9
};
//definicion de pines del arduino para los segmentos
const int segmentosPins[8] = {6, 13, 12, 11, 10, 9, 8, 7}; //dp,G,F,E,D,C,B,A
const int digitosPins[4] = {5, 4, 3, 2}; //pines para encender cada display
//variales de conteo
int contador = 0, contador1 = 0;
int unidades = 0;
int decenas = 0;
int unidades1 = 0;
int decenas1 = 0;
int button = A0;
int button2 = A1;

void setup() {
  for (int i = 0; i < 8; i++) { //para los segmentos
    pinMode(segmentosPins[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) { //activar el display
    pinMode(digitosPins[i], OUTPUT);
  }
}
//Metodo para sepaar cifras
void SepararCifras(int num, int num2) {
  //85
  decenas = num / 10; //extrae decenas
  decenas1 = num2 / 10;
  //decenas=8
  unidades = num - decenas * 10;
  unidades1 = num2 - decenas1 * 10; //extrae unidades
  //unidades=5
}
//Metodo para contar
int Contar() {

  if (digitalRead(button) == 0) {
    while (digitalRead(button) == 0) {
      visuailza2(decenas, unidades, decenas1, unidades1);
    }
    contador++;
  }
  if (contador > 99) {
    contador = 0;
  }

  return contador;
}
int contar2() {
  if (digitalRead(button2) == 0) {
    while (digitalRead(button2) == 0) {
      visuailza2(decenas, unidades, decenas1, unidades1);
    }
    contador1++;
  }
  if (contador1 > 99) {
    contador1 = 0;
  }
  return contador1;
}
//metodo Visualizar

void visuailza2(int dec, int uni, int dec1, int uni1) {
  const int NumeroCompleto[4] = {numeral[dec], numeral[uni], numeral[dec1], numeral[uni1]};
  for (int cifra = 0; cifra < 4; cifra++) {
    for (int i = 0; i < 8; i++) {
      int segmentos = segmentosPins[i];
      digitalWrite(segmentos, !bitRead(NumeroCompleto[cifra], i));
    }
    digitalWrite(digitosPins[cifra], HIGH);
    delay(2);
    digitalWrite(digitosPins[cifra], LOW);
  }

}

void loop() {
  SepararCifras(Contar(), contar2());
  visuailza2(decenas, unidades, decenas1, unidades1);
}
