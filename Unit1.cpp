//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TpongGame *pongGame;
int normalVertical;
int vertical, horizontal;
int interval = 17;
int highVertical;
int highInterval = 13;
int rightPaddlePoints = 0;
int leftPaddlePoints = 0;
AnsiString strRightPaddlePoints = "0";
AnsiString strLeftPaddlePoints = "0";
int maxGoals = 3;
int fontIncrement = 2;
int amountOfKicks = 0;
int allKicks = 0;
int currentKicks = 0;



void startGame( TImage* ball, TImage* leftPaddle, TImage* rightPaddle, TTimer* ballTimer, TShape* background, TLabel* score, TButton* newGameButton, TButton* continueGameButton, TLabel* amountOfKicksLabel, TButton* resetButton)
          {



        normalVertical = background -> Height/55;
        if(allKicks % 2 == 0) horizontal = background -> Width/90;
        else  horizontal = -1 * background -> Width/90;
        if(allKicks % 3 == 0) vertical = normalVertical;
        else  vertical = -normalVertical;
        if(allKicks % 5 != 0)
        {
          vertical = highVertical;
        }

        highVertical = background -> Height/55 - (background -> Height/55)/2;

        leftPaddle -> Top = background -> Height / 2 - leftPaddle -> Height / 2;
       leftPaddle -> Left = 50 + background -> Width/90;

       rightPaddle -> Top = background -> Height / 2 - rightPaddle -> Height / 2;
       rightPaddle -> Left = background -> Width - 50 - background -> Width/90;

        ball -> Top  = background -> Height / 2 - ball -> Height/2;
        ball -> Left  = background -> Width /2 - ball -> Width/2;

         ballTimer -> Interval = interval;

       score -> Visible = true;

       newGameButton -> Visible = false;
       continueGameButton -> Visible = false;
       ball -> Visible = true;

       ballTimer -> Enabled = true;
       amountOfKicksLabel -> Visible = false;
       resetButton -> Visible = false;

          return;
          }



//---------------------------------------------------------------------------
__fastcall TpongGame::TpongGame(TComponent* Owner)
        : TForm(Owner)
{

AnsiString message1 = "Witaj w grze Pong!";
AnsiString message2 = "Gracz czerwony steruje za pomoc¹ klawiszy A i Z.";
AnsiString message3 = "Gracz zielony steruje za pomoc¹ strza³ek góra i dó³.";
AnsiString message4 = "Pi³ka przyspiesza gdy uderzasz j¹ œrodkiem paletki.";
AnsiString message5 = "Mo¿esz dostosowaæ wielkoœæ paletek, pi³ki, zmieniaæ iloœæ goli oraz powiêkszaæ okno z gr¹.";
goals -> Caption = IntToStr(maxGoals);
ShowMessage(message1 + sLineBreak + sLineBreak + message2 + message3 + sLineBreak + message4 + sLineBreak + sLineBreak + message5);
leftPaddle -> Top = background -> Height / 2 - leftPaddle -> Height / 2;
rightPaddle -> Top = background -> Height / 2 - rightPaddle -> Height / 2;

 ball -> Top  = background -> Height / 2 - ball -> Height/2;
 ball -> Left  = background -> Width /2 - ball -> Width/2;


}
//---------------------------------------------------------------------------

void __fastcall TpongGame::ballTimerTimer(TObject *Sender)
{
        ball -> Left += horizontal;
        ball -> Top += vertical;

        //odbij od gornej sciany
        if(ball -> Top - 5 <= background -> Top)
        {
        vertical = -vertical;
        }

        // odbij od dolnej sciany
        if((ball -> Top + ball -> Width+5) > (background -> Height))
         {
         vertical = -vertical;
         }

         // odbijanie od paletek
        if((ball -> Top + (ball -> Height)/2 >= leftPaddle -> Top -12) && (ball -> Top <= leftPaddle -> Top + leftPaddle -> Height + 12))
       {
               if (ball -> Left <= leftPaddle -> Left + leftPaddle -> Width)
                {
                     if((ball -> Top + (ball -> Height)/2 > leftPaddle -> Top + (leftPaddle -> Height)/2 + (leftPaddle -> Height)/4)
                     || (ball -> Top + (ball -> Height)/2 < leftPaddle -> Top + (leftPaddle -> Height)/4))
                     {
                       ballTimer -> Interval = interval;
                       if(vertical > 0) vertical = normalVertical;
                          else vertical = -normalVertical;

                     }

                     else
                     {
                          ballTimer -> Interval = highInterval;
                          if(highInterval > 4)  highInterval-=1;

                          if(vertical > 0) vertical = highVertical;
                           else vertical = -highVertical;

                     }
                     sndPlaySound("kick.wav", SND_ASYNC);
                     horizontal = -horizontal;
                     amountOfKicks++;
                }
        }

        if((ball -> Top + (ball -> Height)/2 >= rightPaddle -> Top -12) && (ball -> Top <= rightPaddle -> Top + rightPaddle -> Height +12))
        {
                if (ball -> Left + ball -> Width >= rightPaddle -> Left)
                {
                      if((ball -> Top + (ball -> Height)/2 > rightPaddle -> Top + (rightPaddle -> Height)/2 + (rightPaddle -> Height)/4)
                      || (ball -> Top + (ball -> Height)/2 < rightPaddle -> Top + (rightPaddle -> Height)/4))
                     {
                           ballTimer -> Interval = interval;
                           if(vertical > 0) vertical = normalVertical;
                          else vertical = -normalVertical;
                     }

                     else
                     {
                          ballTimer -> Interval = highInterval;
                          if(highInterval > 4)  highInterval-=1;
                          if(vertical > 0) vertical = highVertical;
                           else vertical = -highVertical;

                     }

                     sndPlaySound("kick.wav", SND_ASYNC);
                     horizontal = -horizontal;
                     amountOfKicks++;
                }
        }

        //punkt dla gracza prawego
        if(ball -> Left < leftPaddle -> Left + leftPaddle -> Width - 20)
        {

                ballTimer->Enabled = false;
                ball->Visible = false;
                resetButton -> Visible = true;
                continueGameButton -> Visible = true;
                rightPaddlePoints += 1;
                score -> Caption = IntToStr(leftPaddlePoints) + " : " + IntToStr(rightPaddlePoints);
                golLabel -> Visible = true;
                golTimer -> Enabled = true;
                amountOfKicksLabel -> Visible = true;
                amountOfKicksLabel -> Caption = "Ilosc odbiæ: " + IntToStr(amountOfKicks);
                allKicks += amountOfKicks;
                currentKicks = amountOfKicks;
                amountOfKicks = 0;
        }

        //punkt dla gracza lewego
        if(ball -> Left + ball -> Width > rightPaddle -> Left + 20)
        {
                ballTimer->Enabled = false;
                ball->Visible = false;
                continueGameButton -> Visible = true;
                resetButton -> Visible = true;
                leftPaddlePoints += 1;
                score -> Caption = IntToStr(leftPaddlePoints) + " : " + IntToStr(rightPaddlePoints);
                golLabel -> Visible = true;
                golTimer -> Enabled = true;
                amountOfKicksLabel -> Visible = true;
                amountOfKicksLabel -> Caption = "Ilosc odbiæ: " + IntToStr(amountOfKicks);
                allKicks += amountOfKicks;
                currentKicks = amountOfKicks;
                amountOfKicks = 0;
        }


        //koniec gry
        if(leftPaddlePoints == maxGoals || rightPaddlePoints == maxGoals)
        {
          AnsiString nameOfPlayerWhoWon ="";
          if (leftPaddlePoints == maxGoals)
          {
              nameOfPlayerWhoWon = "Czerwony";
          }
          else
          {
             nameOfPlayerWhoWon = "Zielony";
          }

          sndPlaySound("snd/fanfare.wav", SND_ASYNC);
          endGameLabel -> Caption = "Wygrywa gracz " +   nameOfPlayerWhoWon + "!" + sLineBreak + "Ilosc odbiæ: " + IntToStr(currentKicks) + sLineBreak + "Ilosc wszystkich odbiæ: " + IntToStr(allKicks);
          endGameLabel -> Visible = true;
          newGameButton -> Visible = true;
          continueGameButton -> Visible = false;
          showOptionsButton -> Visible = true;
          ballTimer->Enabled = false;
          allKicks = 0;
          currentKicks = 0;
          resetButton -> Visible = false;
          amountOfKicksLabel -> Visible = false;


        }



}
//---------------------------------------------------------------------------

void __fastcall TpongGame::leftPaddleUpMoveTimer(TObject *Sender)
{
        int move = 0;
        if(leftPaddle -> Top <= 0) move = 0;
        else  move = background -> Height/30;
        leftPaddle -> Top -= move;

}
//---------------------------------------------------------------------------

void __fastcall TpongGame::leftPaddleDownMoveTimer(TObject *Sender)
{
        int move = 0;
        if(leftPaddle -> Top + leftPaddle -> Height >= background -> Height) move = 0;
        else  move = background -> Height/30;
        leftPaddle -> Top += move;
}
//---------------------------------------------------------------------------

void __fastcall TpongGame::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == 0x41) leftPaddleUpMove -> Enabled = true;
        if(Key == 0x5A) leftPaddleDownMove -> Enabled = true;

        if(Key == VK_UP) rightPaddleUpMove -> Enabled = true;
        if(Key == VK_DOWN) rightPaddleDownMove -> Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TpongGame::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == 0x41) leftPaddleUpMove -> Enabled = false;
        if(Key == 0x5A) leftPaddleDownMove -> Enabled = false;

        if(Key == VK_UP) rightPaddleUpMove -> Enabled = false;
        if(Key == VK_DOWN) rightPaddleDownMove -> Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TpongGame::rightPaddleUpMoveTimer(TObject *Sender)
{
        int move = 0;
        if(rightPaddle -> Top <= 0) move = 0;
        else  move = background -> Height/30;
        rightPaddle -> Top -= move;
}
//---------------------------------------------------------------------------

void __fastcall TpongGame::rightPaddleDownMoveTimer(TObject *Sender)
{
        int move = 0;
        if(rightPaddle -> Top + rightPaddle -> Height + 6 >= background -> Height) move = 0;
        else  move = background -> Height/30;
        rightPaddle -> Top += move;
}
//---------------------------------------------------------------------------


void __fastcall TpongGame::newGameButtonClick(TObject *Sender)
{
        amountOfGoalsPanel -> Visible = false;
        ballAndPaddleProperties -> Visible = false;
        endGameLabel -> Visible = false;
        showOptionsButton -> Visible = false;

        rightPaddlePoints = 0;
        leftPaddlePoints = 0;
        score -> Caption = IntToStr(leftPaddlePoints) + " : " + IntToStr(rightPaddlePoints);
        amountOfKicks = 0;
        allKicks = 0;
        currentKicks = 0;
        
        startGame(ball, leftPaddle, rightPaddle, ballTimer, background, score, newGameButton, continueGameButton, amountOfKicksLabel, resetButton);
        ballTimer -> Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TpongGame::paddlesSizeChange(TObject *Sender)
{
        rightPaddle -> Height = 40 + paddlesSize -> Position*5;
        leftPaddle -> Height = 40 + paddlesSize -> Position*5;

        leftPaddle -> Top = background -> Height / 2 - leftPaddle -> Height / 2;
        rightPaddle -> Top = background -> Height / 2 - rightPaddle -> Height / 2;

        AnsiString strPosition = "";
        strPosition = IntToStr(paddlesSize -> Position);
        paddleSizeLabel -> Caption = "Rozmiar paletek (" + strPosition + ")";
        paddlesSize -> Hint =  strPosition;
}
//---------------------------------------------------------------------------

void __fastcall TpongGame::ballSizeChange(TObject *Sender)
{
        ball ->  Height = 15 + ballSize -> Position * 15;
        ball ->  Width = 15 + ballSize -> Position * 15;
        ball -> Top  = background -> Height / 2 - ball -> Height/2;
        ball -> Left  = background -> Width /2 - ball -> Width/2;



        AnsiString strPosition = "";
        strPosition = IntToStr(ballSize -> Position);
        ballSizeLabel -> Caption = "Rozmiar pilki (" + strPosition + ")";
        ballSize -> Hint =  strPosition;
}
//---------------------------------------------------------------------------



void __fastcall TpongGame::rounds3Click(TObject *Sender)
{
    goals -> Caption = rounds3 -> Caption;
    maxGoals = rounds3 -> Caption.ToInt();
}
//---------------------------------------------------------------------------

void __fastcall TpongGame::rounds5Click(TObject *Sender)
{
        goals -> Caption = rounds5 -> Caption;
        maxGoals = rounds5 -> Caption.ToInt();
}
//---------------------------------------------------------------------------

void __fastcall TpongGame::rounds10Click(TObject *Sender)
{
        goals -> Caption = rounds10 -> Caption;
        maxGoals = rounds10 -> Caption.ToInt();
}
//---------------------------------------------------------------------------


void __fastcall TpongGame::setAmountOfGoalsButtonClick(TObject *Sender)
{
     AnsiString strGoals = amountOfGoalsEdit -> Text;
     bool isNumber = true;

     for(int i = 1; i <= strGoals.Length(); i++)
     {
       if(strGoals[i] < '0' || strGoals[i] > '9') isNumber = false;
     }

     if(!isNumber) Application -> MessageBox("Wpisz liczbe.",NULL, MB_ICONWARNING);
     else if(amountOfGoalsEdit -> Text == "") Application -> MessageBox("Pole nie mo¿e byc puste.",NULL, MB_ICONWARNING);
     else if(amountOfGoalsEdit -> Text.ToInt() == 0) Application -> MessageBox("Liczba goli musi byc wieksza od 0.",NULL, MB_ICONWARNING);
     else
     {
     maxGoals = amountOfGoalsEdit -> Text.ToInt();
     goals -> Caption = amountOfGoalsEdit -> Text;
     }
}
//---------------------------------------------------------------------------

void __fastcall TpongGame::rounds20Click(TObject *Sender)
{
   goals -> Caption = rounds20 -> Caption;
   maxGoals = rounds20 -> Caption.ToInt();
}
//---------------------------------------------------------------------------


void __fastcall TpongGame::continueGameButtonClick(TObject *Sender)
{
       startGame(ball, leftPaddle, rightPaddle, ballTimer, background, score, newGameButton, continueGameButton, amountOfKicksLabel, resetButton);
}
//---------------------------------------------------------------------------

void __fastcall TpongGame::showOptionsButtonClick(TObject *Sender)
{
       amountOfGoalsPanel -> Visible = true;
       ballAndPaddleProperties -> Visible = true;
       ball -> Visible = true;
        ball -> Top  = background -> Height / 2 - ball -> Height/2;
        ball -> Left  = background -> Width /2 - ball -> Width/2;
}
//---------------------------------------------------------------------------

void __fastcall TpongGame::amountOfGoalsEditChange(TObject *Sender)
{
        if(amountOfGoalsEdit -> Text == "") setAmountOfGoalsButton -> Enabled = false;
        else setAmountOfGoalsButton -> Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TpongGame::golTimerTimer(TObject *Sender)
{
       golLabel -> Font -> Size += fontIncrement;
       if(golLabel -> Font -> Size >= 50)
       {
         fontIncrement = -fontIncrement;
       }
       if(golLabel -> Font -> Size <= 0)
       {
         fontIncrement = -fontIncrement;
         golTimer -> Enabled = false;
         golLabel -> Visible = false;
       }

}
//---------------------------------------------------------------------------


void __fastcall TpongGame::resetButtonClick(TObject *Sender)
{
        amountOfGoalsPanel -> Visible = true;
        ballAndPaddleProperties -> Visible = true;
        ball -> Visible = true;
        ball -> Top  = background -> Height / 2 - ball -> Height/2;
        ball -> Left  = background -> Width /2 - ball -> Width/2;
         rightPaddlePoints = 0;
        leftPaddlePoints = 0;
        score -> Caption = IntToStr(leftPaddlePoints) + " : " + IntToStr(rightPaddlePoints);
        amountOfKicks = 0;
        allKicks = 0;
        currentKicks = 0;
        newGameButton -> Visible = true;
        continueGameButton -> Visible = false;
        resetButton -> Visible = false;

}
//---------------------------------------------------------------------------


