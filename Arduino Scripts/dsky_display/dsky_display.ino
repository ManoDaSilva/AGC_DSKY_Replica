/*receives serial data.

  INPUT
  Serial String with the following structure:
  -Position 0: UPLINK
  -Position 1: ATT
  -Position 2: STBY
  -Position 3: KEY
  -Position 4: ERR
  -Position 5: TEMP
  -Position 6: GIMBAL
  -Position 7: PROG
  -Position 8: RESTART
  -Position 9: TRACKER
  -Position 10: ALT
  -Position 11: VEL
  -Position 12: PLACEHOLDER LED
  -Position 13: COMP ACTY
  -Position 14 and 15: PROGRAM Value
  -Position 16 and 17: VERB Value
  -Position 18 and 19: NOUN Value
  -Position 20, 21, 22, 23, 24, 25: R1 Value
  -Position 26, 27, 28, 29, 30, 31: R2 Value
  -Position 32, 33, 34, 35, 36, 37: R3 Value


*/

#define UPLINK 12
#define ATT 11
#define STBY 10
#define KEY 9
#define ERR 8

#define TEMP 14
#define GIMBAL 15
#define PROG 16
#define RESTART 17
#define TRACKER 18


const byte numChars = 40;
char receivedChars[numChars];   // an array to store the received data
boolean newData = false;
#include <SoftwareSerial.h>
#include <Nextion.h>

String oldprog;
String oldverb;
String oldnoun;
String prog;
String verb;
String noun;
String oldr1;
String oldr2;
String oldr3;
String r1;
String r2;
String r3;
int compactystatus;
int oldcompactystatus;


SoftwareSerial nextion(2, 3);// Nextion TX to pin 2 and RX to pin 3 of Arduino

Nextion myNextion(nextion, 9600); //create a Nextion object named myNextion using the nextion serial port @ 9600bps


void setup() {
  // put your setup code here, to run once:
  pinMode(UPLINK, OUTPUT);
  pinMode(ATT, OUTPUT);
  pinMode(STBY, OUTPUT);
  pinMode(KEY, OUTPUT);
  pinMode(ERR, OUTPUT);
  pinMode(TEMP, OUTPUT);
  pinMode(GIMBAL, OUTPUT);
  pinMode(PROG, OUTPUT);
  pinMode(RESTART, OUTPUT);
  pinMode(TRACKER, OUTPUT);

  Serial.begin(115200);
  myNextion.init();

}

void loop() {
  // put your main code here, to run repeatedly:

  recvWithEndMarker();
  processNewData();




}


void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void processNewData() {
  if (newData == true) {
    //Serial.println(receivedChars);
    writeToLED();
    writeToDisplay();
    newData = false;
  }
}

void writeToLED() {
  setLEDStatus(UPLINK, (int)receivedChars[0] - 48);
  setLEDStatus(ATT, (int)receivedChars[1] - 48);
  setLEDStatus(STBY, (int)receivedChars[2] - 48);
  setLEDStatus(KEY, (int)receivedChars[3] - 48);
  setLEDStatus(ERR, (int)receivedChars[4] - 48);
  setLEDStatus(TEMP, (int)receivedChars[5] - 48);
  setLEDStatus(GIMBAL, (int)receivedChars[6] - 48);
  setLEDStatus(PROG, (int)receivedChars[7] - 48);
  setLEDStatus(RESTART, (int)receivedChars[8] - 48);
  setLEDStatus(TRACKER, (int)receivedChars[9] - 48);
}

void writeToDisplay() {
  prog = formatChar(receivedChars[14]) + formatChar(receivedChars[15]);
  verb = formatChar(receivedChars[16]) + formatChar(receivedChars[17]);
  noun = formatChar(receivedChars[18]) + formatChar(receivedChars[19]);
  r1 = formatChar(receivedChars[20]) + formatChar(receivedChars[21]) + formatChar(receivedChars[22]) + formatChar(receivedChars[23]) + formatChar(receivedChars[24]) + formatChar(receivedChars[25]);
  r2 = formatChar(receivedChars[26]) + formatChar(receivedChars[27]) + formatChar(receivedChars[28]) + formatChar(receivedChars[29]) + formatChar(receivedChars[30]) + formatChar(receivedChars[31]);
  r3 = formatChar(receivedChars[32]) + formatChar(receivedChars[33]) + formatChar(receivedChars[34]) + formatChar(receivedChars[35]) + formatChar(receivedChars[36]) + formatChar(receivedChars[37]);
  if (prog != oldprog) {
    myNextion.setComponentText("p", prog);
    oldprog = prog;
  }
  if (verb != oldverb) {
    myNextion.setComponentText("v", verb);
    oldverb = verb;
  }
  if (noun != oldnoun) {
    myNextion.setComponentText("n", noun);
    oldnoun = noun;
  }
  if (r1 != oldr1) {
    myNextion.setComponentText("r1", r1);
    oldr1 = r1;
  }
  if (r2 != oldr2) {
    myNextion.setComponentText("r2", r2);
    oldr2 = r2;
  }
  if (r3 != oldr3) {
    myNextion.setComponentText("r3", r3);
    oldr3 = r3;
  }
  compactystatus = (int)receivedChars[13] - 48;
  if (compactystatus != oldcompactystatus) {
    setCompActyStatus((int)receivedChars[13] - 48);
    oldcompactystatus = compactystatus;
  }


}


void setLEDStatus(int pin, int state) {
  //Serial.println(pin);
  //Serial.println(state);
  switch (state) {
    case 0: //TURN OFF
      digitalWrite(pin, LOW);
      break;
    case 1: //TURN ON
      digitalWrite(pin, HIGH);
      break;
    case 2: //BLINK
      digitalWrite(pin, HIGH);
      //PLZ IMPLEMENT ME!
      break;
    case 3: //IGNORE
      //DO NOTHING HERE
      break;
  }
}

void setCompActyStatus(int state) {
  switch (state) {
    case 0: //TURN OFF
      myNextion.setComponentTextColor("t6", false);
      break;
    case 1: //TURN ON
      myNextion.setComponentTextColor("t6", true);
      break;
    case 3: //IGNORE
      //DO NOTHING HERE
      break;
  }
}

String formatChar(char input) {
  String output;
  switch (input) {
    case 32:
      output = " ";
      break;
    case 43:
      output = "+";
      break;
    case 45:
      output = "-";
      break;
    default:
      output = String((int)input - 48);
      break;
  }
  return output;
}
