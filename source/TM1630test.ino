//参考
// くろべこblog
// https://kurobekoblog.com/tm1630led
// https://github.com/kurobeko/TM1630LED.git


const static uint8_t MODE = 0b00000001;   //5桁7セグメント
const static uint8_t DSET1 = 0b01000100;  //固定アドレス
const static uint8_t DSET2 = 0b01000000;  //移動アドレス
const static uint8_t ADRS = 0b11000000 | 0;   //アドレス00H
const static uint8_t DISP = 0b10001001;   //表示設定：2/16


uint8_t DIO = 9;
uint8_t CLK = 10;
uint8_t STB = 11;
uint16_t num;
uint8_t d[10] = { 0b01111110, 0b00001100, 0b10110110, 0b10011110, 0b11001100, 0b11011011, 0b11111010, 0b01001110, 0b11111110, 0b11011110 };


void setup() {
  // put your setup code here, to run once:
  pinMode(DIO, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(STB, OUTPUT);
  digitalWrite(STB, HIGH);
  digitalWrite(DIO, LOW);
  digitalWrite(CLK, LOW);
  Serial.begin(115200);
  }



void TM1630(uint8_t i, uint8_t j, uint8_t k, uint8_t l) {
  digitalWrite(STB, LOW);
  shiftOut(DIO, CLK, LSBFIRST, MODE);
  digitalWrite(STB, HIGH);

  digitalWrite(STB, LOW);
  shiftOut(DIO, CLK, LSBFIRST, DSET1);
  digitalWrite(STB, HIGH);

  // Seg-1
  digitalWrite(STB,LOW);
  shiftOut(DIO,CLK,LSBFIRST,ADRS);
  shiftOut(DIO,CLK,LSBFIRST,d[i]);
  digitalWrite(STB,HIGH);

// Seg-2
  digitalWrite(STB,LOW);
  shiftOut(DIO,CLK,LSBFIRST,ADRS|2);
  shiftOut(DIO,CLK,LSBFIRST,d[j]);
  digitalWrite(STB,HIGH);

// Seg-3
  digitalWrite(STB,LOW);
  shiftOut(DIO,CLK,LSBFIRST,ADRS|4);
  shiftOut(DIO,CLK,LSBFIRST,d[k]);
  digitalWrite(STB,HIGH);

// Seg-4
  digitalWrite(STB,LOW);
  shiftOut(DIO,CLK,LSBFIRST,ADRS|6);
  shiftOut(DIO,CLK,LSBFIRST,d[l]);
  digitalWrite(STB,HIGH);

  digitalWrite(STB, LOW);
  shiftOut(DIO,CLK,LSBFIRST,DISP);
  digitalWrite(STB, HIGH);


}



void loop() {
  uint8_t a,b,c,d;
  for (num = 0; num < 10000; num++) {
    a = num / 1000;
    b = (num % 1000) / 100;
    c = ((num % 1000)%100 / 10);
    d = ((num % 1000) % 100 % 10);
    delay(100);
    TM1630(a, b, c, d);
        Serial.print(d,DEC);
        Serial.println("");

  }
}
