//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TpongGame : public TForm
{
__published:	// IDE-managed Components
        TShape *background;
        TImage *leftPaddle;
        TImage *ball;
        TImage *rightPaddle;
        TTimer *ballTimer;
        TLabel *score;
        TButton *newGameButton;
        TButton *continueGameButton;
        TLabel *endGameLabel;
        TButton *showOptionsButton;
        TTimer *leftPaddleUpMove;
        TTimer *leftPaddleDownMove;
        TTimer *rightPaddleUpMove;
        TTimer *rightPaddleDownMove;
        TPanel *ballAndPaddleProperties;
        TTrackBar *paddlesSize;
        TLabel *paddleSizeLabel;
        TTrackBar *ballSize;
        TLabel *ballSizeLabel;
        TPanel *amountOfGoalsPanel;
        TButton *rounds3;
        TButton *rounds5;
        TButton *rounds10;
        TButton *rounds20;
        TBevel *Bevel1;
        TEdit *amountOfGoalsEdit;
        TGroupBox *goalsBox;
        TBitBtn *setAmountOfGoalsButton;
        TTimer *golTimer;
        TLabel *golLabel;
        TLabel *goals;
        TLabel *amountOfKicksLabel;
        TButton *resetButton;
        TLabel *goalsLabel;
        TImage *bg1;
        void __fastcall ballTimerTimer(TObject *Sender);
        void __fastcall leftPaddleUpMoveTimer(TObject *Sender);
        void __fastcall leftPaddleDownMoveTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall rightPaddleUpMoveTimer(TObject *Sender);
        void __fastcall rightPaddleDownMoveTimer(TObject *Sender);
        void __fastcall newGameButtonClick(TObject *Sender);
        void __fastcall continueGameButtonClick(TObject *Sender);
        void __fastcall showOptionsButtonClick(TObject *Sender);
        void __fastcall rounds3Click(TObject *Sender);
        void __fastcall rounds5Click(TObject *Sender);
        void __fastcall rounds10Click(TObject *Sender);
        void __fastcall setAmountOfGoalsButtonClick(TObject *Sender);
        void __fastcall paddlesSizeChange(TObject *Sender);
        void __fastcall ballSizeChange(TObject *Sender);
        void __fastcall rounds20Click(TObject *Sender);
        void __fastcall amountOfGoalsEditChange(TObject *Sender);
        void __fastcall golTimerTimer(TObject *Sender);
        void __fastcall resetButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TpongGame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TpongGame *pongGame;
//---------------------------------------------------------------------------
#endif
