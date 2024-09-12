/*  in this code you can find all the game and drawing logic and functions needed
    to make the game work
*/
#ifndef game_logic
#define game_logic
#include "variables.h"
#include "menuImg.h"

// all structs of game

typedef struct
{
    int x;
    int y;
} position;

typedef struct
{
    position pos;
    int color;
    int collision = 0;
} Part_Of_Pill;

struct Antidote
{
    Part_Of_Pill Pill1;
    Part_Of_Pill Pill2;
} Pill;

typedef struct
{
    int color;
    int collision = 0;
    bool timed = false;
} Virus;

// make matrix of elements
Part_Of_Pill PillMatrix[11][6];
Virus VirusMatrix[11][6];
int ColorMatrix[11][6];

// convert matrix positions to real numbers and matrix init
// 1 CELL = 20 px,
// en functies voor position

int MatrixPos(int pos)
{
    return pos * CELL;
}

int NextPos(int pos)
{
    return pos + 1;
}

int PreviousPos(int pos)
{
    return pos - 1;
}

// Draw functions
// all these functions are needed because my gameworld exist out of two different matrices, virus and pill matrix
void DrawPill(int color1, int color2)
{
    switch (color1)
    {
    case 0:
        M5.Lcd.fillRect(MatrixPos(Pill.Pill1.pos.x), MatrixPos(Pill.Pill1.pos.y), CELL, CELL, BLACK);
        break;

    case 1:
        M5.Lcd.fillRect(MatrixPos(Pill.Pill1.pos.x), MatrixPos(Pill.Pill1.pos.y), CELL, CELL, RED);
        break;

    case 2:
        M5.Lcd.fillRect(MatrixPos(Pill.Pill1.pos.x), MatrixPos(Pill.Pill1.pos.y), CELL, CELL, BLUE);
        break;

    case 3:
        M5.Lcd.fillRect(MatrixPos(Pill.Pill1.pos.x), MatrixPos(Pill.Pill1.pos.y), CELL, CELL, YELLOW);
        break;

    case 4:
        M5.Lcd.pushImage(MatrixPos(Pill.Pill1.pos.x), MatrixPos(Pill.Pill1.pos.y), imgWidth, imgHeight, bombImg);
        break;

    default:
        break;
    }

    switch (color2)
    {
    case 0:
        M5.Lcd.fillRect(MatrixPos(Pill.Pill2.pos.x), MatrixPos(Pill.Pill2.pos.y), CELL, CELL, BLACK);
        break;

    case 1:
        M5.Lcd.fillRect(MatrixPos(Pill.Pill2.pos.x), MatrixPos(Pill.Pill2.pos.y), CELL, CELL, RED);
        break;

    case 2:
        M5.Lcd.fillRect(MatrixPos(Pill.Pill2.pos.x), MatrixPos(Pill.Pill2.pos.y), CELL, CELL, BLUE);
        break;

    case 3:
        M5.Lcd.fillRect(MatrixPos(Pill.Pill2.pos.x), MatrixPos(Pill.Pill2.pos.y), CELL, CELL, YELLOW);
        break;

    case 4:
        M5.Lcd.pushImage(MatrixPos(Pill.Pill1.pos.x), MatrixPos(Pill.Pill1.pos.y), imgWidth, imgHeight, bombImg);
        break;

    default:
        break;
    }
}


// this is to show the next pill in line
void DrawNextPill()
{
    M5.Lcd.setCursor(85, 190);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(1.5);
    M5.Lcd.print("Next: ");
    switch (colorPill1)
    {
    case 0:
        M5.Lcd.fillRect(MatrixPos(6), 205, 15, 15, BLACK);
        break;

    case 1:
        M5.Lcd.fillRect(MatrixPos(6), 205, 15, 15, RED);
        break;

    case 2:
        M5.Lcd.fillRect(MatrixPos(6), 205, 15, 15, BLUE);
        break;

    case 3:
        M5.Lcd.fillRect(MatrixPos(6), 205, 15, 15, YELLOW);
        break;

    case 4:
        M5.Lcd.pushImage(MatrixPos(6), 205, imgWidth, imgHeight, bombImg);
        break;
    default:
        break;
    }

    switch (colorPill2)
    {
    case 0:
        M5.Lcd.fillRect(MatrixPos(6), 220, 15, 15, BLACK);
        break;

    case 1:
        M5.Lcd.fillRect(MatrixPos(6), 220, 15, 15, RED);
        break;

    case 2:
        M5.Lcd.fillRect(MatrixPos(6), 220, 15, 15, BLUE);
        break;

    case 3:
        M5.Lcd.fillRect(MatrixPos(6), 220, 15, 15, YELLOW);
        break;

    case 4:
        M5.Lcd.pushImage(MatrixPos(6), 205, imgWidth, imgHeight, bombImg);
        break;

    default:
        break;
    }
}

// when there is only one part of a pill in the game, need to draw it
void DrawPartOfPill(int x, int y, int color)
{

    switch (color)
    {
    case 0:
        M5.Lcd.fillRect(MatrixPos(x), MatrixPos(y), CELL, CELL, BLACK);
        break;

    case 1:
        M5.Lcd.fillRect(MatrixPos(x), MatrixPos(y), CELL, CELL, RED);
        break;

    case 2:
        M5.Lcd.fillRect(MatrixPos(x), MatrixPos(y), CELL, CELL, BLUE);
        break;

    case 3:
        M5.Lcd.fillRect(MatrixPos(x), MatrixPos(y), CELL, CELL, YELLOW);
        break;

    case 4:
        M5.Lcd.pushImage(MatrixPos(x), MatrixPos(y), CELL, CELL, bombImg);
        break;

    default:
        break;
    }
}

void DrawVirus(int x, int y, int color)
{
    switch (color)
    {
    case 0:
        M5.Lcd.fillRect(MatrixPos(x), MatrixPos(y), CELL, CELL, BLACK);
        break;

    case 1:
        if (VirusMatrix[y][x].timed)
        {
            M5.Lcd.pushImage(MatrixPos(x), MatrixPos(y), imgWidth, imgHeight, redTimed_virus);
        }
        else
        {
            M5.Lcd.pushImage(MatrixPos(x), MatrixPos(y), imgWidth, imgHeight, red_virus);
        }
        break;

    case 2:
        if (VirusMatrix[y][x].timed)
        {
            M5.Lcd.pushImage(MatrixPos(x), MatrixPos(y), imgWidth, imgHeight, blueTimed_virus);
        }
        else
        {
            M5.Lcd.pushImage(MatrixPos(x), MatrixPos(y), imgWidth, imgHeight, blue_virus);
        }
        break;

    case 3:
        if (VirusMatrix[y][x].timed)
        {
            M5.Lcd.pushImage(MatrixPos(x), MatrixPos(y), imgWidth, imgHeight, yellowTimed_virus);
        }
        else
        {
            M5.Lcd.pushImage(MatrixPos(x), MatrixPos(y), imgWidth, imgHeight, yellow_virus);
        }
        break;

    case 4:
        M5.Lcd.pushImage(MatrixPos(x), MatrixPos(y), imgWidth, imgHeight, bombImg);
        break;

    default:
        break;
    }
}

// initialize functions

void InitializePill()
{
    Pill.Pill1.pos.x = init_x_Pill1;
    Pill.Pill1.pos.y = init_y_Pill1;
    Pill.Pill2.pos.x = init_x_Pill2;
    Pill.Pill2.pos.y = init_y_Pill2;
    Pill.Pill1.collision = 1;
    Pill.Pill2.collision = 1;
    Pill.Pill1.color = colorPill1;
    Pill.Pill2.color = colorPill2;
    colorPill1 = rand() % 3 + 1;
    colorPill2 = rand() % 3 + 1;

    NoCollision = true;
    initPill = true;
    number_of_rotations = 0;
    gamespeed = 1000;
    DrawPill(Pill.Pill1.color, Pill.Pill2.color);
    DrawNextPill();
}

void InitializeBomb()
{
    Pill.Pill1.pos.x = init_x_Pill1;
    Pill.Pill1.pos.y = init_y_Pill1;
    Pill.Pill2.pos.x = init_x_Pill2;
    Pill.Pill2.pos.y = init_y_Pill2;
    Pill.Pill1.collision = 0;
    Pill.Pill2.collision = 1;
    Pill.Pill1.color = 0;
    Pill.Pill2.color = 4;
    bombCheck = true;

    NoCollision = true;
    number_of_rotations = 0;
    gamespeed = 1000;
    DrawPill(Pill.Pill1.color, Pill.Pill2.color);
    DrawNextPill();
}

void InitializeVirusMatrix()
{
    for (int i = 0; i < MATRIXHEIGTH; i++)
    {
        for (int j = 0; j < MATRIXWIDTH; j++)
        {
            VirusMatrix[i][j].collision = 0;
            VirusMatrix[i][j].color = 0;
        }
    }
}

void InitializePillMatrix()
{
    for (int i = 0; i < MATRIXHEIGTH; i++)
    {
        for (int j = 0; j < MATRIXWIDTH; j++)
        {
            PillMatrix[i][j].collision = 0;
            PillMatrix[i][j].color = 0;
        }
    }
}

void InitializeColorMatrix()
{
    for (int i = 0; i < MATRIXHEIGTH; i++)
    {
        for (int j = 0; j < MATRIXWIDTH; j++)
        {
            ColorMatrix[i][j] = 0;
        }
    }
}

// update the colormatrix

void AddColorToMatrix(int x, int y, int color)
{
    ColorMatrix[y][x] = color;
}

void updateColorMatrix()
{
    for (int i = 0; i < MATRIXHEIGTH; i++)
    {
        for (int j = 0; j < MATRIXWIDTH; j++)
        {

            if (PillMatrix[i][j].color == 0 && VirusMatrix[i][j].color == 0)
            {
                ColorMatrix[i][j] = 0;
                DrawVirus(j, i, BLACK);
            }

            if (PillMatrix[i][j].color == 0 && VirusMatrix[i][j].color != 0)
            {
                ColorMatrix[i][j] = VirusMatrix[i][j].color;
                DrawVirus(j, i, VirusMatrix[i][j].color);
            }

            if (PillMatrix[i][j].color != 0 && VirusMatrix[i][j].color == 0)
            {
                ColorMatrix[i][j] = PillMatrix[i][j].color;
                DrawPartOfPill(j, i, PillMatrix[i][j].color);
            }
        }
    }
}

// to make new level
void NextLevel()
{
    if (LevelvirusCnt == 0)
    {
        GameField = true;
        NumberOfVirus += rand() % 2 + 1;
        LevelvirusCnt = NumberOfVirus;
        gamespeed *= 0.9;
    }
    if(bombInGame){
        TimeForBomb = rand() % 15 + 7;
    }
}

// functions to delete elements from all the matrices
void DeleteElFromMatrix(int x, int y)
{
    PillMatrix[y][x].collision = 0;
    PillMatrix[y][x].color = 0;
    if (VirusMatrix[y][x].collision == 1)
    {
        score++;
        LevelvirusCnt--;
    }
    VirusMatrix[y][x].collision = 0;
    VirusMatrix[y][x].color = 0;
    VirusMatrix[y][x].timed = false;

    NumberOfPills--;
    if (NumberOfPills % 2 == 0)
    {
        score++;
    }

    NextLevel();
    updateColorMatrix();
}

// to only delete a blok element
void DeleteBlokFromMatrix(int x, int y)
{
    PillMatrix[y][x].collision = 0;
    PillMatrix[y][x].color = 0;
    NumberOfPills--;
    if (NumberOfPills % 2 == 0)
    {
        score++;
    }
    updateColorMatrix();
}

// when pill has no support, it falls down
void PushBlocks()
{
    int k;
    // loop from end to top to be sure that all elements are pushed down
    for (int i = MATRIXHEIGTH - 1; i >= 0; i--)
    {
        for (int j = 0; j < MATRIXWIDTH; j++)
        {
            // looks for collision
            if (VirusMatrix[i][j].collision == 0 && PillMatrix[i][j].collision == 0)
            {
                for (k = i; k >= 0; k--) // loop from end to top
                {
                    if (VirusMatrix[k][j].collision == 1) // if first element above blank space is a virus, stop
                    { // because viruses does not fall down
                        break;
                    }
                    if (VirusMatrix[k][j].collision == 0 && PillMatrix[k][j].collision == 1)
                    { // if there are no virussen, you can push down every block
                        PillMatrix[i][j] = PillMatrix[k][j];
                        PillMatrix[k][j].collision = 0;
                        PillMatrix[k][j].color = 0;
                        updateColorMatrix();
                    }
                }
            }
        }
    }
}

// check for colors 4 in a row
void Check4InARow()
{
    int i, j;

    // Check rows
    for (i = 0; i < MATRIXHEIGTH; i++)
    {
        for (j = 0; j < MATRIXWIDTH; j++)
        {
            if (PillMatrix[i][j].collision == 1 || VirusMatrix[i][j].collision == 1)
            {
                int k;
                int countx = 0;
                int county = 0;
                // check horizontaal
                for (k = 0; j + k < MATRIXWIDTH; k++)
                { // check if all elements after are of the same color
                    if (ColorMatrix[i][j + k] == ColorMatrix[i][j])
                    {
                        countx++;
                    }
                    else
                    {
                        break;
                    }
                }

                for (k = 0; i + k < MATRIXHEIGTH; k++)
                {// same
                    if (ColorMatrix[i + k][j] == ColorMatrix[i][j])
                    {
                        county++;
                    }
                    else
                    {
                        break;
                    }
                }

                if (countx >= 4)
                {// delete elements in a row of minimum 4 elements on x-axis
                    for (int l = 0; l < countx; l++)
                    {
                        DeleteElFromMatrix(j + l, i);
                    }
                    PushBlocks();
                }

                if (county >= 4)
                {// delete elements in a row of minimum 4 elements on y-axis
                    for (int l = 0; l < county; l++)
                    {
                        DeleteElFromMatrix(j, i + l);
                    }
                    PushBlocks();
                }
            }
        }
    }
}

// check if timed virus has been killed before end of time, else end level
void checkTimedVirus()
{

    if (timedVirus)
    {
        if (VirusMatrix[timedVirus_y][timedVirus_x].timed)
        {
            M5.Lcd.fillRect(5, 190, 60, 40, BLACK);
            M5.Lcd.setCursor(5, 190);
            M5.Lcd.setTextColor(WHITE);
            M5.Lcd.setTextSize(1);
            M5.Lcd.printf("Time:");
            M5.Lcd.setCursor(5, 210);
            M5.Lcd.setTextColor(WHITE);
            M5.Lcd.setTextSize(3);
            M5.Lcd.print(TimeForVirus);
            TimeForVirus = TimeForVirus - 1;
        }
        if (TimeForVirus < -1 && VirusMatrix[timedVirus_y][timedVirus_x].timed)
        {
            gameover = true;
        }

        if (!VirusMatrix[timedVirus_y][timedVirus_x].timed)
        {
            M5.Lcd.fillRect(5, 190, 60, 40, BLACK);
        }
    }
}

// add pill to matrix (gameworld) to know where the pills are in the game
void AddPillToMatrix()
{
    PillMatrix[Pill.Pill1.pos.y][Pill.Pill1.pos.x].collision = 1;
    PillMatrix[Pill.Pill1.pos.y][Pill.Pill1.pos.x].color = Pill.Pill1.color;
    PillMatrix[Pill.Pill2.pos.y][Pill.Pill2.pos.x].collision = 1;
    PillMatrix[Pill.Pill2.pos.y][Pill.Pill2.pos.x].color = Pill.Pill2.color;
    NumberOfPills += 2;

    updateColorMatrix();
    delay(50);
    PushBlocks();
}

// make virus element
void AddVirusToMatrix(int count)
{
    // code to make the elements
    for (int i = 0; i < count; i++)
    {
        // x:5 - y:9 are max values
        int y = rand() % 8 + 2;
        int x = rand() % 5;
        int color = rand() % 3 + 1;
        VirusMatrix[y][x].collision = 1;
        VirusMatrix[y][x].color = color;
        VirusMatrix[y][x].timed = false;
        DrawVirus(x, y, color);
        // part of code to draw it
        updateColorMatrix();
    }

    if (TVirusInGame)
    {
        // add timed virus
        timedVirus = true;
        TimeForVirus = rand() % 20 + 10;
        LevelvirusCnt += 1;
        int Timedcolor = rand() % 3 + 1;
        timedVirus_x = rand() % 5;
        timedVirus_y = rand() % 8 + 2;
        VirusMatrix[timedVirus_y][timedVirus_x].collision = 1;
        VirusMatrix[timedVirus_y][timedVirus_x].color = Timedcolor;
        VirusMatrix[timedVirus_y][timedVirus_x].timed = true;
        DrawVirus(timedVirus_x, timedVirus_y, Timedcolor);
        // part of code to draw it
        updateColorMatrix();
    }
}

// check positions functions for collision

bool CheckLeftPos()
{
    if (PillMatrix[Pill.Pill1.pos.y][Pill.Pill1.pos.x - 1].collision != 1 &&
        PillMatrix[Pill.Pill2.pos.y][Pill.Pill2.pos.x - 1].collision != 1 &&
        VirusMatrix[Pill.Pill1.pos.y][Pill.Pill1.pos.x - 1].collision != 1 &&
        VirusMatrix[Pill.Pill2.pos.y][Pill.Pill2.pos.x - 1].collision != 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CheckRigthPos()
{
    if (PillMatrix[Pill.Pill1.pos.y][Pill.Pill1.pos.x + 1].collision != 1 &&
        PillMatrix[Pill.Pill2.pos.y][Pill.Pill2.pos.x + 1].collision != 1 &&
        VirusMatrix[Pill.Pill1.pos.y][Pill.Pill1.pos.x + 1].collision != 1 &&
        VirusMatrix[Pill.Pill2.pos.y][Pill.Pill2.pos.x + 1].collision != 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CheckPosDown()
{
    if (PillMatrix[Pill.Pill1.pos.y + 1][Pill.Pill1.pos.x].collision != 1 &&
        PillMatrix[Pill.Pill2.pos.y + 1][Pill.Pill2.pos.x].collision != 1 &&
        VirusMatrix[Pill.Pill1.pos.y + 1][Pill.Pill1.pos.x].collision != 1 &&
        VirusMatrix[Pill.Pill2.pos.y + 1][Pill.Pill2.pos.x].collision != 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CheckPosUp()
{
    if (PillMatrix[Pill.Pill1.pos.y - 1][Pill.Pill1.pos.x].collision != 1 &&
        PillMatrix[Pill.Pill2.pos.y - 1][Pill.Pill2.pos.x].collision != 1 &&
        VirusMatrix[Pill.Pill1.pos.y - 1][Pill.Pill1.pos.x].collision != 1 &&
        VirusMatrix[Pill.Pill2.pos.y - 1][Pill.Pill2.pos.x].collision != 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CheckBordersLeft()
{
    if (Pill.Pill1.pos.x > 0 && Pill.Pill2.pos.x > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CheckBordersRigth()
{
    if (Pill.Pill1.pos.x < width && Pill.Pill2.pos.x < width)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// functions to move and rotate Pill

void RotatePill()
{

    switch (number_of_rotations)
    {
    case 0:
        if (CheckLeftPos() && CheckBordersLeft())
        {
            DrawPill(0, 0);
            Pill.Pill2.pos.x = Pill.Pill1.pos.x - 1;
            Pill.Pill2.pos.y = Pill.Pill1.pos.y;
            number_of_rotations += 1;
            DrawPill(Pill.Pill1.color, Pill.Pill2.color);
        }
        break;

    case 1:
        if (CheckPosDown() && CheckPosUp())
        {
            DrawPill(0, 0);
            Pill.Pill2.pos.x = Pill.Pill1.pos.x;
            Pill.Pill2.pos.y = Pill.Pill1.pos.y - 1;
            number_of_rotations += 1;
            DrawPill(Pill.Pill1.color, Pill.Pill2.color);
        }
        break;

    case 2:
        if (CheckRigthPos() && CheckBordersRigth())
        {
            DrawPill(0, 0);
            Pill.Pill2.pos.x = Pill.Pill1.pos.x + 1;
            Pill.Pill2.pos.y = Pill.Pill1.pos.y;
            number_of_rotations += 1;
            DrawPill(Pill.Pill1.color, Pill.Pill2.color);
        }
        break;

    case 3:
        if (CheckPosDown() && CheckPosUp())
        {
            DrawPill(0, 0);
            Pill.Pill2.pos.x = Pill.Pill1.pos.x;
            Pill.Pill2.pos.y = Pill.Pill1.pos.y + 1;
            number_of_rotations += 1;
            DrawPill(Pill.Pill1.color, Pill.Pill2.color);
        }
        break;

    default:
        break;
    }
}

void NextPosDown()
{ // next pos
    DrawPill(0, 0);
    Pill.Pill1.pos.y += SPEED;
    Pill.Pill2.pos.y += SPEED;
    DrawPill(Pill.Pill1.color, Pill.Pill2.color);
}

void movePillLeft()
{
    if (CheckBordersLeft())
    {
        DrawPill(0, 0);
        if (CheckLeftPos())
        {
            Pill.Pill1.pos.x -= SPEED;
            Pill.Pill2.pos.x -= SPEED;
        }
        DrawPill(Pill.Pill1.color, Pill.Pill2.color);
    }
}

void movePillRight()
{

    if (CheckBordersRigth())
    {
        DrawPill(0, 0);
        if (CheckRigthPos())
        {
            Pill.Pill1.pos.x += SPEED;
            Pill.Pill2.pos.x += SPEED;
        }
        DrawPill(Pill.Pill1.color, Pill.Pill2.color);
    }
}

void MovePillAround(float acc_x, float acc_y)
{// main function to move left and right according to how much you tilt your device, also effects game speed
    if (acc_x > MIN_TILT)
    {
        movePillLeft();
    }
    else if (acc_x < -MIN_TILT)
    {
        movePillRight();
    }

    if (acc_y > MIN_TILT)
    {
        gamespeed *= 0.7;
    }
    else if (acc_y < -MIN_TILT)
    {
        // Up
        gamespeed *= 3;
    }
}

void explode()
{
// this part of code is to eleminate all elements around a bomb
    DeleteElFromMatrix(Pill.Pill2.pos.x, Pill.Pill2.pos.y);
    DeleteElFromMatrix(Pill.Pill2.pos.x, Pill.Pill2.pos.y + 1);
    DeleteElFromMatrix(Pill.Pill2.pos.x, Pill.Pill2.pos.y - 1);
    DeleteElFromMatrix(Pill.Pill2.pos.x + 1, Pill.Pill2.pos.y);
    DeleteElFromMatrix(Pill.Pill2.pos.x - 1, Pill.Pill2.pos.y);
    DeleteElFromMatrix(Pill.Pill2.pos.x + 1, Pill.Pill2.pos.y + 1);
    DeleteElFromMatrix(Pill.Pill2.pos.x + 1, Pill.Pill2.pos.y - 1);
    DeleteElFromMatrix(Pill.Pill2.pos.x - 1, Pill.Pill2.pos.y + 1);
    DeleteElFromMatrix(Pill.Pill2.pos.x - 1, Pill.Pill2.pos.y - 1);
    bombCheck = false;
    PushBlocks();
}

// check for collision in game

void CheckForCollision()
{
    if (Pill.Pill2.pos.y == heigth && bombCheck) // check with bomb
    {
        explode();
        NoCollision = false;
        initPill = true;
        Check4InARow();
        updateColorMatrix();
    }

    if (!CheckPosDown() && bombCheck) // check with bomb
    {
        NoCollision = false;
        initPill = true;
        explode();
        Check4InARow();
        updateColorMatrix();
    }

    if (Pill.Pill1.pos.y == heigth || Pill.Pill2.pos.y == heigth) // check without bomb
    {
        NoCollision = false;
        initPill = true;
        AddPillToMatrix();
        updateColorMatrix();
        Check4InARow();
        if(bombInGame){
            TimeForBomb--;
        }
        if (TimeForBomb == 0 && bombInGame)
        {
            bomb = true;
        }
    }

    if (!CheckPosDown()) // check without bomb
    {
        NoCollision = false;
        initPill = true;
        AddPillToMatrix();
        Check4InARow();
        TimeForBomb--; // decreasing time until initializing bomb
        if (TimeForBomb == 0 && bombInGame) // if it is time to add bomb in game according to the time for bomb
        {
            bomb = true;
        }
        updateColorMatrix();
        checkTimedVirus(); // check if after adding pill and collision and all, if time is ok to continue
    }
}

void ShowMenu()
{
// this code is to initalize the main menu and the choices possible to make
    switch (menuOption)
    {
    case 0:
        M5.Lcd.pushImage(0, 0, 135, 240, nobomb_novirus);
        if (M5.BtnA.wasPressed())
        {
            menuOption++;
        }
        else if (M5.BtnB.wasPressed())
        {
            M5.Lcd.fillScreen(BLACK);
            bombInGame = false;
            TVirusInGame = false;
            menu = false;
            initPill = true;
            GameField = true;
            gamespeed = 1000;
            loadinglevel = true;
        }
        break;

    case 1:
        M5.Lcd.pushImage(0, 0, 135, 240, nobomb_virus);
        if (M5.BtnA.wasPressed())
        {
            menuOption++;
        }
        else if (M5.BtnB.wasPressed())
        {
            M5.Lcd.fillScreen(BLACK);
            bombInGame = false;
            TVirusInGame = true;
            menu = false;
            initPill = true;
            GameField = true;
            gamespeed = 1000;
            loadinglevel = true;
        }
        break;

    case 2:
        M5.Lcd.pushImage(0, 0, 135, 240, bomb_no_virus);
        if (M5.BtnA.wasPressed())
        {
            menuOption++;
        }
        else if (M5.BtnB.wasPressed())
        {
            M5.Lcd.fillScreen(BLACK);
            bombInGame = true;
            TVirusInGame = false;
            menu = false;
            initPill = true;
            GameField = true;
            gamespeed = 1000;
            loadinglevel = true;
        }
        break;

    case 3:
        M5.Lcd.pushImage(0, 0, 135, 240, bomb_and_virus);
        if (M5.BtnA.wasPressed())
        {
            menuOption = 0;
        }
        else if (M5.BtnB.wasPressed())
        {
            M5.Lcd.fillScreen(BLACK);
            bombInGame = true;
            TVirusInGame = true;
            menu = false;
            initPill = true;
            GameField = true;
            gamespeed = 1000;
            loadinglevel = true;
        }
        break;

    default:
        break;
    }
}

void saveLevel()
{
    int address = 0;

    /* first save game variables
            - booleans from level to know which type of level we are
            - game world
            - number of viruses left and their time
            - score

    */
    EEPROM.writeByte(address, TimeForBomb);
    address++;
    EEPROM.writeByte(address, TimeForVirus);
    address++;
    EEPROM.writeByte(address, NumberOfVirus);
    address++;
    EEPROM.writeByte(address, LevelvirusCnt);
    address++;
    EEPROM.writeByte(address, NumberOfPills);
    address++;
    EEPROM.writeByte(address, score);
    address++;

    for (int i = 0; i < MATRIXHEIGTH; i++)
    {
        for (int j = 0; j < MATRIXWIDTH; j++)
        {
            EEPROM.writeByte(address, PillMatrix[i][j].collision);
            address++;
            EEPROM.writeByte(address,PillMatrix[i][j].color);
            address++;

            EEPROM.writeByte(address, VirusMatrix[i][j].collision);
            address++;
            EEPROM.writeByte(address,VirusMatrix[i][j].color);
            address++;
            EEPROM.writeByte(address,VirusMatrix[i][j].timed);
            address++;
        }
    }
    EEPROM.commit();
    delay(500);
}

void loadLevel(){
    Serial.print("test loadlevel");
    M5.Lcd.fillScreen(BLACK);
    int address = 0;
    // load necessary game variables
    TimeForBomb = EEPROM.readByte(address);
    address++;
    TimeForVirus= EEPROM.readByte(address);
    address++;
    NumberOfVirus = EEPROM.readByte(address);
    address++;
    LevelvirusCnt = EEPROM.readByte(address);
    address++;
    NumberOfPills = EEPROM.readByte(address);
    address++;
    score = EEPROM.readByte(address);
    address++;

    // load game field
    for (int i = 0; i < MATRIXHEIGTH; i++)
    {
        for (int j = 0; j < MATRIXWIDTH; j++)
        {
            PillMatrix[i][j].collision = EEPROM.readByte(address);
            address++;
            PillMatrix[i][j].color = EEPROM.readByte(address);
            address++;

            VirusMatrix[i][j].collision = EEPROM.readByte(address);
            address++;
            VirusMatrix[i][j].color = EEPROM.readByte(address);
            address++;
            VirusMatrix[i][j].timed = EEPROM.readByte(address);
            address++;
        }
    }
updateColorMatrix();
delay(1000);
}

#endif /* game_logic */