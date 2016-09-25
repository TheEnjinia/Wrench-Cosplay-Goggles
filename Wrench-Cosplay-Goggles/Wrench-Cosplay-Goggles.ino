/***************************************************
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit 16x8 LED Matrix backpacks
  ----> http://www.adafruit.com/products/2035
  ----> http://www.adafruit.com/products/2036
  ----> http://www.adafruit.com/products/2037
  ----> http://www.adafruit.com/products/2038
  ----> http://www.adafruit.com/products/2039
  ----> http://www.adafruit.com/products/2040
  ----> http://www.adafruit.com/products/2041
  ----> http://www.adafruit.com/products/2042
  ----> http://www.adafruit.com/products/2043
  ----> http://www.adafruit.com/products/2044
  ----> http://www.adafruit.com/products/2052

  These displays use I2C to communicate, 2 pins are required to
  interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution

  July 2016 modefied by Enjinia
  ----> http://enjinia.de/
  ----> http://enjinia.de/en/2016/07/31/making-the-goggles-for-the-wrench-cosplay/
  
 ****************************************************/



#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x16matrix left_eye[2] = {Adafruit_8x16matrix(), Adafruit_8x16matrix()};
Adafruit_8x16matrix right_eye[2] = {Adafruit_8x16matrix(), Adafruit_8x16matrix()};


//Adafruit_8x16matrix left0 = Adafruit_8x16matrix();
//Adafruit_8x16matrix left1 = Adafruit_8x16matrix();

static const uint8_t PROGMEM

X_bmp[4][8] =
{ { B11100000,
    B01110000,
    B00111000,
    B00011100,
    B00001110,
    B00000111,
    B00000011,
    B00000011
  },

  { B00000011,
    B00000011,
    B00000111,
    B00001110,
    B00011100,
    B00111000,
    B01110000,
    B11100000
  },

  { B00000111,
    B00001110,
    B00011100,
    B00111000,
    B01110000,
    B11100000,
    B11000000,
    B11000000
  },

  { B11000000,
    B11000000,
    B11100000,
    B01110000,
    B00111000,
    B00011100,
    B00001110,
    B00000111
  }
},
At_bmp[4][8] =
{ { B00000001,
    B00001111,
    B00010000,
    B00110001,
    B01100111,
    B10001000,
    B10010000,
    B10100000
  },
  { B10100000,
    B10100000,
    B10010000,
    B11011000,
    B01001111,
    B01110011,
    B00011000,
    B00001111
  },
  { B10000000,
    B11100000,
    B00110000,
    B00000100,
    B11110010,
    B01100001,
    B00100001,
    B01100001
  },
  { B01000001,
    B01000010,
    B01000010,
    B11001100,
    B11110000,
    B01100000,
    B00000110,
    B11111100
  }
},
O_L_bmp[4][8] =
{ { B00000000,
    B00000000,
    B00000000,
    B00001111,
    B00111111,
    B01100000,
    B01100000,
    B11000000
  },
  { B11000000,
    B01100000,
    B01100001,
    B00111111,
    B00001100,
    B00000000,
    B00000000,
    B00000000
  },
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B10000000,
    B11000000,
    B11000000,
    B11000000
  },
  { B11000000,
    B11000000,
    B11000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  }
},

O_R_bmp[4][8] =
{ {
    B00000000,
    B00000011,
    B00000110,
    B00000100,
    B00001100,
    B00001100,
    B00001100,
    B00001100
  },
  { B00001100,
    B00001100,
    B00000100,
    B00000011,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  { B11110000,
    B11111100,
    B00000110,
    B00000110,
    B00000110,
    B00000110,
    B00000110,
    B00000110
  },
  { B00000110,
    B00000110,
    B00011110,
    B11110000,
    B11000000,
    B00000000,
    B00000000,
    B00000000
  }
},


Hash_bmp[4][8] =
{ { B00000001,
    B00000001,
    B00000001,
    B00000001,
    B11111111,
    B11111111,
    B00000110,
    B00000110
  },
  { B00000110,
    B00000110,
    B00000110,
    B11111111,
    B00001000,
    B00001000,
    B00011000,
    B00011000
  },
  { B10001100,
    B10001100,
    B10001100,
    B00001100,
    B11111111,
    B11111111,
    B00011000,
    B00011000
  },
  { B00011000,
    B00011000,
    B00011000,
    B11111111,
    B00011000,
    B00010000,
    B00110000,
    B00110000
  }
}
,
Caret_bmp[4][8] =
{ { B00000000,
    B00000001,
    B00000011,
    B00000011,
    B00000110,
    B00000110,
    B00001100,
    B00001100
  },
  { B00011100,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  { B00000000,
    B10000000,
    B11000000,
    B11000000,
    B01100000,
    B01100000,
    B00110000,
    B00110000
  },
  { B00111000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  }
},


Tilde_bmp[4][8] =
{ { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00011100,
    B00111111,
    B00110011,
    B00000000
  },
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00001000,
    B11011000,
    B11111000,
    B11100000
  },
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  }
}
,

Asterisk_bmp[4][8] =
{ { B00000000,
    B00000000,
    B00000001,
    B00000001,
    B00000001,
    B00011001,
    B00011101,
    B00001111,
  },
  { B00000011,
    B00001111,
    B00011100,
    B00011000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
  },
  { B00000000,
    B00000000,
    B10000000,
    B10000000,
    B10000000,
    B10011000,
    B10111000,
    B11110000,
  },
  { B10000000,
    B11100000,
    B01110000,
    B00110000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
  }
},

Backslash_bmp[4][8] =
{ { B11000000,
    B11100000,
    B01110000,
    B00111000,
    B00011100,
    B00001110,
    B00000111,
    B00000011
  },
  { B00000001,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B10000000
  },
  { B11000000,
    B11100000,
    B01110000,
    B00111000,
    B00011100,
    B00001110,
    B00000111,
    B00000011
  }
},

Slash_bmp[4][8] =
{ { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000001
  },
  { B00000011,
    B00000111,
    B00001110,
    B00011100,
    B00111000,
    B01110000,
    B11100000,
    B11000000
  },
  { B00000011,
    B00000111,
    B00001110,
    B00011100,
    B00111000,
    B01110000,
    B11100000,
    B11000000
  },
  { B10000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  }
},

Equal_bmp[4][8] =
{ { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111111,
    B11111111,
    B11111111,
    B00000000
  },
  { B00000000,
    B11111111,
    B11111111,
    B11111111,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111111,
    B11111111,
    B11111111,
    B00000000
  },
  { B00000000,
    B11111111,
    B11111111,
    B11111111,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  }
},

Nine_bmp[4][8] =
{ { B00000111,
    B00011111,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011110,
    B00000111
  },
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00001111,
    B00000001
  },
  { B11100000,
    B11111000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B01111000,
    B11111000
  },
  { B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00110000,
    B00110000,
    B11100000,
    B10000000
  }
},

Apostrophe_L_bmp[4][8] =
{ { B00000000,
    B00000001,
    B00000011,
    B00000111,
    B00001111,
    B00000000,
    B00000000,
    B00000000
  },
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  { B00000000,
    B11100000,
    B11000000,
    B10000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  }
},

Apostrophe_R_bmp[4][8] =
{
  { B00000000,
    B00000111,
    B00000011,
    B00000001,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  { B00000000,
    B10000000,
    B11000000,
    B11100000,
    B11110000,
    B00000000,
    B00000000,
    B00000000
  },
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  }
},
Guillemet_L_bmp[4][8] =
{ { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000001,
    B00000111,
    B00001111
  },
  { B00001111,
    B00000111,
    B00000001,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  { B00000001,
    B00000111,
    B00011111,
    B00111110,
    B01111000,
    B11110000,
    B11000000,
    B10000000
  },
  { B10000000,
    B11000000,
    B11110000,
    B01111000,
    B00111110,
    B00011111,
    B00000111,
    B00000001,
  }
},

Guillemet_R_bmp[4][8] =
{ { B10000000,
    B11100000,
    B11111000,
    B01111100,
    B00011110,
    B00001111,
    B00000011,
    B00000001
  },
  { B00000001,
    B00000011,
    B00001111,
    B00011110,
    B01111100,
    B11111000,
    B11100000,
    B10000000,
  },
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B10000000,
    B11100000,
    B11110000
  },
  { B11110000,
    B11100000,
    B10000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  }
},
Question_bmp[4][8] =
{ { B00000111,
    B00011111,
    B00111000,
    B01100000,
    B11100000,
    B11000000,
    B01100000,
    B00000000
  },
  { B00000000,
    B00000000,
    B00000000,
    B00000001,
    B00000011,
    B00000000,
    B00000011,
    B00000011
  },
  { B11100000,
    B11111000,
    B00001110,
    B00000111,
    B00000111,
    B00001110,
    B00001110,
    B00011100
  },
  { B01110000,
    B11100000,
    B11000000,
    B11000000,
    B11000000,
    B00000000,
    B11000000,
    B11000000
  }
},

Z_bmp[4][8] =
{ { B11111111,
    B11111111,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  { B00000111,
    B00001110,
    B00011100,
    B00111000,
    B01110000,
    B11100000,
    B11111111,
    B11111111
  },
  { B11111111,
    B11111111,
    B00000111,
    B00001110,
    B00011100,
    B00111000,
    B01110000,
    B11100000
  },
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111111,
    B11111111
  }
},


Semicolon_bmp[4][8] =
{ { B00000000,
    B00000000,
    B00000011,
    B00000011,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  { B00000000,
    B00000011,
    B00000011,
    B00000000,
    B00000000,
    B00000011,
    B00000010,
    B00000000
  },
  { B00000000,
    B00000000,
    B11000000,
    B11000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  { B00000000,
    B11000000,
    B11000000,
    B11000000,
    B11000000,
    B10000000,
    B00000000,
    B00000000
  }
},

Exclamation_bmp[4][8] =
{ { B00000011,
    B00000011,
    B00000011,
    B00000011,
    B00000011,
    B00000011,
    B00000011,
    B00000011
  },
  { B00000011,
    B00000001,
    B00000001,
    B00000000,
    B00000000,
    B00000011,
    B00000011,
    B00000000
  },
  { B11000000,
    B11000000,
    B11000000,
    B11000000,
    B11000000,
    B11000000,
    B11000000,
    B10000000
  },
  { B10000000,
    B10000000,
    B00000000,
    B00000000,
    B00000000,
    B11000000,
    B11000000,
    B00000000
  }
}

;

void clearEyes(Adafruit_8x16matrix *left_matrix, Adafruit_8x16matrix *right_matrix) {
  left_matrix[0].clear();
  left_matrix[1].clear();
  left_matrix[0].writeDisplay();
  left_matrix[1].writeDisplay();

  right_matrix[0].clear();
  right_matrix[1].clear();
  right_matrix[0].writeDisplay();
  right_matrix[1].writeDisplay();
}

void drawEye(const uint8_t (*bitmap)[8], Adafruit_8x16matrix *matrix) {
  matrix[0].clear();
  matrix[1].clear();

  matrix[0].drawBitmap(0, 0, bitmap[0], 8, 8, LED_ON);
  matrix[0].drawBitmap(8, 0, bitmap[1], 8, 8, LED_ON);
  matrix[1].drawBitmap(0, 0, bitmap[2], 8, 8, LED_ON);
  matrix[1].drawBitmap(8, 0, bitmap[3], 8, 8, LED_ON);

  matrix[0].writeDisplay();
  matrix[1].writeDisplay();
}


void setup() {
  Serial.begin(9600);
  Serial.setTimeout(20);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  left_eye[0].setRotation(3);   //We war using the displays vertically.
  left_eye[1].setRotation(3);
  left_eye[0].begin(0x70);
  left_eye[1].begin(0x71 );

  right_eye[0].setRotation(3);
  right_eye[1].setRotation(3);
  right_eye[0].begin(0x72);
  right_eye[1].begin(0x73 );
  clearEyes(left_eye, right_eye);
}



void loop() {
  int Emote;
  if (Serial.available()) {

    Emote = Serial.readString().toInt();
    // set the brightness of the LED:
    switch (Emote) {
      case 0:    // your hand is on the sensor
        drawEye(X_bmp, left_eye);
        drawEye(X_bmp, right_eye);
        break;
      case 1:    // your hand is on the sensor
        drawEye(At_bmp, left_eye);
        drawEye(At_bmp, right_eye);
        break;

      case 2:    // your hand is on the sensor
        drawEye(O_L_bmp, left_eye);
        drawEye(O_R_bmp, right_eye);
        break;
      case 3:    // your hand is on the sensor
        drawEye(Hash_bmp, left_eye);
        drawEye(Hash_bmp, right_eye);
        break;
      case 4:    // your hand is on the sensor
        drawEye(Caret_bmp, left_eye);
        drawEye(Tilde_bmp, right_eye);
        break;
      case 5:    // your hand is on the sensor
        drawEye(Asterisk_bmp, left_eye);
        drawEye(Asterisk_bmp, right_eye);
        break;
      case 6:    // your hand is on the sensor
        drawEye(Caret_bmp, left_eye);
        drawEye(Caret_bmp, right_eye);
        break;
      case 7:    // your hand is on the sensor
        drawEye(Backslash_bmp, left_eye);
        drawEye(Slash_bmp, right_eye);
        break;
      case 8:    // your hand is on the sensor
        drawEye(Slash_bmp, left_eye);
        drawEye(Backslash_bmp, right_eye);
        break;
      case 9:    // your hand is on the sensor
        drawEye(Equal_bmp, left_eye);
        drawEye(Equal_bmp, right_eye);
        break;
      case 10:    // your hand is on the sensor
        drawEye(Nine_bmp, left_eye);
        drawEye(Nine_bmp, right_eye);
        break;
      case 11:    // your hand is on the sensor
        drawEye(Apostrophe_L_bmp, left_eye);
        drawEye(Apostrophe_R_bmp, right_eye);
        break;
      case 12:    // your hand is on the sensor
        drawEye(Guillemet_L_bmp, left_eye);
        drawEye(Guillemet_R_bmp, right_eye);
        break;
      case 13:    // your hand is on the sensor
        drawEye(Question_bmp, left_eye);
        drawEye(Question_bmp, right_eye);
        break;
      case 14:    // your hand is on the sensor
        drawEye(Z_bmp, left_eye);
        drawEye(Z_bmp, right_eye);
        break;
      case 15:    // your hand is on the sensor
        drawEye(Semicolon_bmp, left_eye);
        drawEye(Semicolon_bmp, right_eye);
        break;
      case 16:    // your hand is on the sensor
        drawEye(Exclamation_bmp, left_eye);
        drawEye(Exclamation_bmp, right_eye);
        break;

      default:
        clearEyes(left_eye, right_eye);
    }
    delay(5);
  }

  /*
    drawEye(X_bmp, left_eye);
    drawEye(X_bmp, right_eye);
    delay(500);
    drawEye(At_bmp, left_eye);
    drawEye(At_bmp, right_eye);
    delay(500);
    drawEye(O_L_bmp, left_eye);
    drawEye(O_R_bmp, right_eye);
    delay(500);
    drawEye(Hash_bmp, left_eye);
    drawEye(Hash_bmp, right_eye);
    delay(500);
    drawEye(Caret_bmp, left_eye);
    drawEye(Tilde_bmp, right_eye);
    delay(500);
    drawEye(Asterisk_bmp, left_eye);
    drawEye(Asterisk_bmp, right_eye);
    delay(500);
    drawEye(Backslash_bmp, left_eye);
    drawEye(Slash_bmp, right_eye);
    delay(500);
    drawEye(Slash_bmp, left_eye);
    drawEye(Backslash_bmp, right_eye);
    delay(500);
    drawEye(Equal_bmp, left_eye);
    drawEye(Equal_bmp, right_eye);
    delay(500);
    drawEye(Nine_bmp, left_eye);
    drawEye(Nine_bmp, right_eye);
    delay(500);
    drawEye(Apostrophe_L_bmp, left_eye);
    drawEye(Apostrophe_R_bmp, right_eye);
    delay(500);
    drawEye(Guillemet_L_bmp, left_eye);
    drawEye(Guillemet_R_bmp, right_eye);
    delay(500);
    drawEye(Question_bmp, left_eye);
    drawEye(Question_bmp, right_eye);
    delay(500);
    drawEye(Z_bmp, left_eye);
    drawEye(Z_bmp, right_eye);
    delay(500);
    drawEye(Semicolon_bmp, left_eye);
    drawEye(Semicolon_bmp, right_eye);
    delay(500);
    drawEye(Exclamation_bmp, left_eye);
    drawEye(Exclamation_bmp, right_eye);
    delay(500);
  */
}



