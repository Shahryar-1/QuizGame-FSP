#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// ----------------------
// Struct for MCQs
// ----------------------
struct MCQ {
    string question, A, B, C, D;
    int correct;
};

// ----------------------
// Function Declarations
// ----------------------
int game(int);
int highscore(int);

void science(int);
void sports(int);
void computer(int);
void history(int);
void iqlogic(int);

// ----------------------
// MAIN FUNCTION
// ----------------------
int main()
{
    int n;

    cout << "----------Quiz Game----------\n";
    cout << "----------Quiz Gaming Arena----------\n";
    cout << "Press 1 to Start quiz" << endl;
    cout << "Press 2 to view High Score" << endl;
    cout << "Press 3 to Exit Game" << endl;
    
    cin >> n;

    if (n == 1)
        game(n);
    else if (n == 2)
        highscore(n);
    else if (n == 3)
        cout << "Exiting...\n";

    return 0;
}

// ----------------------
// GAME FUNCTION: Choose Category
// ----------------------
int game(int x)
{
    int n;
   
    cout << "Welcome to the Quiz Game\n";
    cout << "Which Category you want?\n";
    cout << "Press 1 for Science\n";
    cout << "Press 2 for History\n";
    cout << "Press 3 for Sports\n";
    cout << "Press 4 for Computer\n";
    cout << "Press 5 for IQ/Logic\n";
    cin >> n;

    switch (n) {
        case 1:
            science(n);
            break;
        case 2:
            history(n);
            break;
        case 3:
            sports(n);
            break;
        case 4:
            computer(n);
            break;
        case 5:
            iqlogic(n);
            break;
        default:
            cout << "Invalid choice!\n";
    }

    return 0;
}

// ----------------------
// SCIENCE CATEGORY FUNCTION
// ----------------------
void science(int x)
{
    int difficulty;
    cout << "Please Enter difficulty level (1-Easy, 2-Medium, 3-Hard): ";
    cin >> difficulty;

    if(difficulty < 1 || difficulty > 3)
    {
        cout << "Invalid difficulty!\n";
        return;
    }

    switch(difficulty) {
        case 1: // Easy
        case 2: // Medium
        case 3: // Hard
        {
            const int MAX = 100;
            MCQ questions[MAX];
            int count = 0;

            ifstream file("science.txt");
            if(!file) {
                cout << "File not found!\n";
                return;
            }

            string line;
            while(getline(file, line) && count < MAX) {
                stringstream ss(line);

                getline(ss, questions[count].question, '|');
                getline(ss, questions[count].A, '|');
                getline(ss, questions[count].B, '|');
                getline(ss, questions[count].C, '|');
                getline(ss, questions[count].D, '|');

                string correctStr;
                getline(ss, correctStr, '|');
                questions[count].correct = stoi(correctStr);

                string diffStr;
                getline(ss, diffStr, '|'); // assuming last field is difficulty: 1,2,3
                if(stoi(diffStr) != difficulty) // filter by chosen difficulty
                    continue;

                count++;
            }
            file.close();

            if(count == 0) {
                cout << "No questions found for this difficulty!\n";
                return;
            }

            srand(time(0));
            int totalAsked = 10;
            int score = 0;
            bool usedIndex[MAX] = {false};

            for(int i = 0; i < totalAsked; i++) {
                int index;
                do {
                    index = rand() % count;
                } while(usedIndex[index]);

                usedIndex[index] = true;

                MCQ q = questions[index];

                cout << "\nQ" << i + 1 << " : " << q.question << "\n";
                cout << "1. " << q.A << "\n";
                cout << "2. " << q.B << "\n";
                cout << "3. " << q.C << "\n";
                cout << "4. " << q.D << "\n";
                cout << "0. Replaced this question\n";

                int ans;
                cout << "Your answer (0 to replace): ";
                cin >> ans;

                if(ans == 0) {
                    cout << "Question Replaced\n";
                    usedIndex[index] = false;
                    i--;
                    continue;
                }

                if(ans == q.correct) {
                    cout << "Correct Answer\n";
                    score++;
                } else {
                    cout << "Wrong Answer. Correct Option: " << q.correct << "\n";
                }
            }

            cout << "\n====================\n";
            cout << "Your Score: " << score << "\n";
            cout << "Total Asked Questions: " << totalAsked << "\n";
            cout << "====================\n";

            break;
        }
        default:
            cout << "Invalid difficulty!\n";
    }
}

// ----------------------
// OTHER CATEGORY PLACEHOLDERS
// ----------------------
void sports(int x) { cout << "Sports category coming soon!\n"; }
void computer(int x) { cout << "Computer category coming soon!\n"; }
void history(int x) { cout << "History category coming soon!\n"; }
void iqlogic(int x) { cout << "IQ/Logic category coming soon!\n"; }
int highscore(int x) { cout << "Highscore feature coming soon!\n"; return 0; }
