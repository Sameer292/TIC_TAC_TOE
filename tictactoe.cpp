#include <iostream>
// #include<stdlib.h>
using namespace std;
const char PLAYER1 = 'X';
const char PLAYER2 = 'O';
const char AI = 'A';
const char T = ' ';
char winner = ' ';
char response = ' ';
class HUMAN;
class BOARD
{

    char board[3][3];

public:
    friend class HUMAN;
    friend int minmax(bool isMax, BOARD &b1);
    friend void bestmove(BOARD &b1);
    friend char playerVplayer(BOARD &b, HUMAN &p1);
    friend char playerVcomputer(BOARD &b, HUMAN &p1);

    void printBoard()
    {
        system("cls");
        cout << " _____ ___ ____ _____  _    ____ _____ ___  _____ " << endl;
        cout << "|_   _|_ _/ ___|_   _|/ \\  / ___|_   _/ _ \\| ____|" << endl;
        cout << "  | |  | | |     | | / _ \\| |     | || | | | |__|  " << endl;
        cout << "  | |  | | |___  | |/ ___ \\ |____ | || |_| | |___  " << endl;
        cout << "  |_| |__ \\____  | |_/_/   \\_____ | |\\ ___/|_____|" << endl
             << endl;

        cout << "\t\t\t";
        cout << board[0][0] << "|" << board[0][1] << "|" << board[0][2] << endl;
        cout << "\t\t\t";
        cout << "-"
             << "|"
             << "-"
             << "|"
             << "-" << endl;
        cout << "\t\t\t";
        cout << board[1][0] << "|" << board[1][1] << "|" << board[1][2] << endl;
        cout << "\t\t\t";
        cout << "-"
             << "|"
             << "-"
             << "|"
             << "-" << endl;
        cout << "\t\t\t";
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
        int freespace = 9;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] != ' ')
                    freespace--;
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
            return T;

        return ' ';
    }
    void printWinner(char winner)
    {
        if (winner == PLAYER1)
            cout << "Player 1 is the winner!" << endl;
        else if (winner == AI)
            cout << "AI is the winner!" << endl;
        else
            cout << "It's a tie!" << endl;
    }
};

class HUMAN
{
    int x, y;

public:
    friend char playerVplayer(BOARD &b, HUMAN &p1);
    friend char playerVcomputer(BOARD &b, HUMAN &p1);

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

void bestmove(BOARD &b1)
{
    int score = 0;
    int bestscore = -999;
    int move[2];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (b1.board[i][j] == ' ')
            {
                b1.board[i][j] = AI;

                score = minmax(false, b1);
                b1.board[i][j] = ' ';
                if (score > bestscore)
                {
                    bestscore = score;
                    move[0] = i;
                    move[1] = j;
                }
            }
        }
    }
    b1.board[move[0]][move[1]] = AI;
}

int minmax(bool isMax, BOARD &b1)
{

    char res = b1.checkWinner();
    if (res != ' ')
    {
        if (res == 'X')
            return -10;
        else
            return 10;
    }
    if (isMax)
    {
        int bestScore = -9999;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (b1.board[i][j] == ' ')
                {
                    b1.board[i][j] = AI;
                    int score = minmax(false, b1);
                    b1.board[i][j] = ' ';
                    if (score > bestScore)
                        bestScore = score;
                }
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = 9999;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (b1.board[i][j] == ' ')
                {
                    b1.board[i][j] = PLAYER1;
                    int score = minmax(true, b1);
                    b1.board[i][j] = ' ';
                    if (score < bestScore)
                        bestScore = score;
                }
            }
        }
        return bestScore;
    }
}

char playerVplayer(BOARD &b, HUMAN &p1)
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

    return response;
}

char playerVcomputer(BOARD &b, HUMAN &p1)
{
    winner = ' ';
    response = ' ';
    while (winner == ' ' && b.checkfreeSpaces() != 0)
    {
        b.printBoard();
        bestmove(b);
        winner = b.checkWinner();
        if (winner != ' ' || b.checkfreeSpaces() == 0)
        {
            break;
        }
        b.printBoard();
        p1.player1Move(b);
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

    return response;
}

int main()
{

    int choose;
    BOARD b;
    HUMAN p1;

    do
    {
        // winner = ' ';
        // response = ' ';
        b.resetBoard();
        system("cls");
        cout << " _____ ___ ____ _____  _    ____ _____ ___  _____ " << endl;
        cout << "|_   _|_ _/ ___|_   _|/ \\  / ___|_   _/ _ \\| ____|" << endl;
        cout << "  | |  | | |     | | / _ \\| |     | || | | | |__|  " << endl;
        cout << "  | |  | | |___  | |/ ___ \\ |____ | || |_| | |___  " << endl;
        cout << "  |_| |__ \\____  | |_/_/   \\_____ | |\\ ___/|_____|" << endl
             << endl;
        cout << "\t\t\t";

        cout << "Choose mode: " << endl;
        cout << "\t\t\t";

        cout << "1.Player V Player"
             << "\n"
             << "\t\t\t"
             << "2.Player V Computer" << endl;
        cin >> choose;
        if (choose == 1)
        {
            playerVplayer(b, p1);
        }
        else
        {
            playerVcomputer(b, p1);
        }
    } while (response == 'y');

    return 0;
}
