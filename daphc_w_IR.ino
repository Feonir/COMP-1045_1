/*
 * This sketch combines the Wave HC example with the IR_RECV example with some slight modifications 
 * to make a IR Remote Jukebox of sorts using the arduino.
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff for the IR Code
 * http://arcfn.com
 * No Copyright was listed on the Daphc sketch but their website is
 * http://www.ladyada.net/make/waveshield/index.html
 */
 
#include <WaveHC.h>
#include <WaveUtil.h>
#include <IRremote.h>
#include <FatReader.h>
#include <SdReader.h>
#include <avr/pgmspace.h>

SdReader card;    // This object holds the information for the card
FatVolume vol;    // This holds the information for the partition on the card
FatReader root;   // This holds the information for the volumes root directory
FatReader file;   // This object represent the WAV file 
WaveHC wave;      // This is the only wave (audio) object, since we will only play one at a time

uint8_t dirLevel; // indent level for file/dir names    (for prettyprinting)
dir_t dirBuf;     // buffer for directory reads

int RECV_PIN = 7; //Pin 7 for IR input

IRrecv irrecv(RECV_PIN); 

decode_results results;

/*
 * Define macro to put error messages in flash memory
 */
#define error(msg) error_P(PSTR(msg))

// Function definitions (we define them here, but the code is below)
void play(FatReader &dir);

//////////////////////////////////// SETUP
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps for debugging
  
  irrecv.enableIRIn(); // Start the receiver
  
  putstring_nl("\nWave test!");  // say we woke up!
  
  putstring("Free RAM: ");       // This can help with debugging, running out of RAM is bad
  Serial.println(FreeRam());

  //  if (!card.init(true)) { //play with 4 MHz spi if 8MHz isn't working for you
  if (!card.init()) {         //play with 8 MHz spi (default faster!)  
    error("Card init. failed!");  // Something went wrong, lets print out why
  }
  
  // enable optimize read - some cards may timeout. Disable if you're having problems
  card.partialBlockRead(true);
  
  // Now we will look for a FAT partition!
  uint8_t part;
  for (part = 0; part < 5; part++) {   // we have up to 5 slots to look in
    if (vol.init(card, part)) 
      break;                           // we found one, lets bail
  }
  if (part == 5) {                     // if we ended up not finding one  :(
    error("No valid FAT partition!");  // Something went wrong, lets print out why
  }
  
  // Lets tell the user about what we found
  putstring("Using partition ");
  Serial.print(part, DEC);
  putstring(", type is FAT");
  Serial.println(vol.fatType(), DEC);     // FAT16 or FAT32?
  
  // Try to open the root directory
  if (!root.openRoot(vol)) {
    error("Can't open root dir!");      // Something went wrong,
  }
  
  // Whew! We got past the tough parts.
  putstring_nl("Files found (* = fragmented):");

  // Print out all of the files in all the directories.
  root.ls(LS_R | LS_FLAG_FRAGMENTED);
}

//////////////////////////////////// LOOP
void loop() {
    if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX); //Outputs the received IR value in Hex.
    playByName(results.value); //Method for playing the .Wav files.
    irrecv.resume(); // Receive the next value
    }
}

/////////////////////////////////// HELPERS
/*
 * print error message and halt
 */
void error_P(const char *str) {
  PgmPrint("Error: ");
  SerialPrint_P(str);
  sdErrorCheck();
  while(1);
}
/*
 * print error message and halt if SD I/O error, great for debugging!
 */
void sdErrorCheck(void) {
  if (!card.errorCode()) return;
  PgmPrint("\r\nSD I/O error: ");
  Serial.print(card.errorCode(), HEX);
  PgmPrint(", ");
  Serial.println(card.errorData(), HEX);
  while(1);
}

void playByName(long input) {
  char name[10];
  
  // copy flash string to RAM
  //Button 1 - change the value after 0x to list new IR button
  if(input==0xFD08F7){
      strcpy_P(name, PSTR("1.WAV")); //Change filename to song you wish to play. Ensure it is in the root of the SD card.
  if (!file.open(root, name)) error("open by name"); 
  if (!wave.create(file)) error("wave.create");
      wave.play();  //Play the song.
  }
  //Button 2
  if(input==0xFD8877){
      strcpy_P(name, PSTR("2.WAV"));
  if (!file.open(root, name)) error("open by name"); 
  if (!wave.create(file)) error("wave.create");
      wave.play();  
  }
  //Button 3  
  if(input==0xFD48B7){
      strcpy_P(name, PSTR("3.WAV"));
  if (!file.open(root, name)) error("open by name"); 
  if (!wave.create(file)) error("wave.create");
      wave.play();  
  }
  //Button 4
  if(input==0xFD28D7){
      strcpy_P(name, PSTR("4.WAV"));
  if (!file.open(root, name)) error("open by name"); 
  if (!wave.create(file)) error("wave.create");
      wave.play();  
  }
  //Button 5
  if(input==0xFDA857){
      strcpy_P(name, PSTR("5.WAV"));
  if (!file.open(root, name)) error("open by name"); 
  if (!wave.create(file)) error("wave.create");
      wave.play();  
  }
  //Button 6
  if(input==0xFD6897){
      strcpy_P(name, PSTR("6.WAV"));
  if (!file.open(root, name)) error("open by name"); 
  if (!wave.create(file)) error("wave.create");
      wave.play();  
  }
  //Button 7
  if(input==0xFD18E7){
      strcpy_P(name, PSTR("7.WAV"));
  if (!file.open(root, name)) error("open by name"); 
  if (!wave.create(file)) error("wave.create");
      wave.play();  
  }
  //Button 8
  if(input==0xFD9867){
      strcpy_P(name, PSTR("8.WAV"));
  if (!file.open(root, name)) error("open by name"); 
  if (!wave.create(file)) error("wave.create");
      wave.play();  
  }
  //Button 9
  if(input==0xFD58A7){
      strcpy_P(name, PSTR("9.WAV"));
  if (!file.open(root, name)) error("open by name"); 
  if (!wave.create(file)) error("wave.create");
      wave.play();  
  } //End of if statements for button and song listing.
} //End of Sketch

