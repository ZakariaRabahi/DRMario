#include <M5StickCPlus.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <EEPROM.h>
#include "game_logic.h"
#include "variables.h"
#include <time.h>
#include <unistd.h>


// the setup routine runs once when M5StickC starts up
void setup() {
  
  // initialize the M5StickC object
  M5.begin();
  M5.IMU.Init();
  Serial.begin(115200);
  Serial.flush();
  M5.Lcd.setSwapBytes(true); // for pushing images on screen
  EEPROM.begin(512);


  M5.Lcd.fillScreen(BLACK);
  delay(500);

  // text print
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 120);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);
  M5.Lcd.print("DrMario");

  // draw graphic
  delay(1000);
  M5.Lcd.fillRect(15, 55, 50, 50, ORANGE);
  delay(1000);
  M5.Lcd.fillCircle(40, 80, 30, RED);
  delay(1000);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.drawLine(0, 180, 100, 180, WHITE);
  M5.Lcd.drawLine(100, 0, 100, 180, WHITE);
  srand( time(NULL) * getpid());
}

// the loop routine runs over and over again forever
void loop(){
  M5.update();
  delay(gamespeed);


  if(menu){
    ShowMenu();
  }

  // part to initialize whole gameworld to blank
  if (GameField){
    InitializeVirusMatrix();
    InitializePillMatrix();
    InitializeColorMatrix();
    updateColorMatrix();
    AddVirusToMatrix(NumberOfVirus);

    GameField = false;
    delay(300);
  }  


  // part of code to initialize bomb when the time arrives
      if(bomb){
        InitializeBomb();
        initPill = false;
        bomb = false;
        if(!CheckPosDown()){
          gameover = true;
      }
    }
  
  
  // initialize pill at initial position 
   if(initPill){
    InitializePill();
    initPill = false;

    // if no space under to put new pill in game
    if(!CheckPosDown()){
      gameover = true;
    }
  }


  // while there is no collision move pill in game world
  if (NoCollision){
    float acc_x = 0, acc_y = 0, acc_z = 0;
    M5.IMU.getAccelData(&acc_x, &acc_y, &acc_z);
    NextPosDown();
    MovePillAround(acc_x, acc_y);
    CheckForCollision();
    
  }

  if (M5.BtnA.isPressed()){
    RotatePill();
    DrawPill(Pill.Pill1.color, Pill.Pill2.color);
  } 

  // if it is possible to load and save game:
  if (loadinglevel){

    if (M5.BtnB.wasPressed()){
      saveLevel();
    }

    if(M5.BtnA.wasPressed() && M5.BtnB.wasPressed()){
      loadLevel();
    }
  }

 // when game is over 
  if (gameover){
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(10, 90);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.printf("Score: %d ", score);
    initPill = false;
    NoCollision = false;
    GameField = false;
    bombInGame = false;
    bomb = false;
    bombCheck = false;
    TVirusInGame = false;
    timedVirus = false;
  }
}
