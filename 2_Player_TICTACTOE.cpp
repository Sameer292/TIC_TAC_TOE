#include <iostream>
#include <stdlib.h>
using namespace std;
const char PLAYER1 = 'X';
const char PLAYER2 = 'O';
class HUMAN;

class BOARD
{

    char board[3][3];

public:
    friend class HUMAN;
    void printBoard()
    {
        system("cls");
        cout << board[0][0] << "|" << board[0][1] << "|" << board[0][2] << endl;
        cout << "-"
             << "|"
             << "-"
             << "|"
             << "-" << endl;
        cout << board[1][0] << "|" << board[1][1] << "|" << board[1][2] << endl;
        cout << "-"
             << "|"
             << "-"
             << "|"
             << "-" << endl;
        cout << board[2][0] << "|" << board[2][1] << "|" << board[2][2] << endl;
    }
    void resetBoard()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = ' ';
            }
        }
    }
    int checkfreeSpaces()
    {
        int freespace = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                    freespace++;
            }
        }
        return freespace;
    }
    char checkWinner()
    {
        for (int i = 0; i < 3; i++)
        {
            if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
                return board[i][0];
        }
        for (int i = 0; i < 3; i++)
        {
            if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
                return board[0][i];
        }
        if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
        {

            return board[0][0];
        }
        if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
        {
            return board[0][2];
        }
        if (checkfreeSpaces() == 0)
            return 'T';
        else
            return ' ';
    }
    void printWinner(char winner)
    {
        if (winner == PLAYER1)
            cout << "Player 1 is the winner!" << endl;
        else if (winner == PLAYER2)
            cout << "Player 2 is the winner!" << endl;
        else
            cout << "It's a tie!" << endl;
    }
};

class HUMAN
{
    int x, y;

public:
    void player1Move(BOARD &b1);
    void player2Move(BOARD &b1);
};
void HUMAN::player1Move(BOARD &b1)
{
    do
    {
        x = 0, y = 0;
        cout << "PLAYER1: " << endl;
        cout << "Enter row(1-3): ";
        cin >> x;
        x--;
        cout << "Enter column(1-3): ";
        cin >> y;
        y--;
        if (b1.board[x][y] != ' ')
        {
            cout << "Invalid position!!!" << endl;
        }
        else
        {
            b1.board[x][y] = PLAYER1;
            break;
        }
    } while (b1.board[x][y] != ' ');
}
void HUMAN::player2Move(BOARD &b1)
{
    do
    {
        x = 0, y = 0;
        cout << "PLAYER2: " << endl;
        cout << "Enter row(1-3): ";
        cin >> x;
        x--;
        cout << "Enter column(1-3): ";
        cin >> y;
        y--;
        if (b1.board[x][y] != ' ')
        {
            cout << "Invalid position!!!" << endl;
        }
        else
        {
            b1.board[x][y] = PLAYER2;
            break;
        }
    } while (b1.board[x][y] != ' ');
}


int main()
{
    char winner = ' ';
    char response = ' ';
    BOARD b;
    HUMAN p1;
    do
    {
        winner = ' ';
        response = ' ';
        b.resetBoard();
        while (winner == ' ' && b.checkfreeSpaces() != 0)
        {
            b.printBoard();
            p1.player1Move(b);
            winner = b.checkWinner();
            if (winner != ' ' || b.checkfreeSpaces() == 0)
            {
                break;
            }
            b.printBoard();
            p1.player2Move(b);
            winner = b.checkWinner();
            if (winner != ' ' || b.checkfreeSpaces() == 0)
            {
                break;
            }
        }
        b.printBoard();
        b.printWinner(winner);
        cout << "Do you want to play again? ";
        cin >> response;
    } while (response == 'y');

    return 0;
}
