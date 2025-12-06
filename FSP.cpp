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
// HIGH SCORE FUNCTION
// ----------------------

int highscore(int x)
{
    ifstream file("highscore.txt");

    if(!file) 
    {
        cout << "File not found!\n";
        return 0;
    }

    string line;
     while(getline(file, line)) // read each line
    {
        cout << line << endl; 
    }
    file.close();
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

    const int MAX = 100;
    MCQ questions[MAX];
    MCQ incorrect[MAX];
    int count = 0, wrongcount = 0;

    ifstream file("science.txt");
    if(!file)
    {
        cout << "File not found!\n";
        return;
    }

    // Load questions
    string line;
    while(getline(file, line) && count < MAX)
    {
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
        getline(ss, diffStr, '|');

        if(stoi(diffStr) != difficulty)
            continue;

        count++;
    }
    file.close();

    if(count == 0)
    {
        cout << "No questions found for this difficulty!\n";
        return;
    }

    srand(time(0));

    int totalAsked = 10;
    int score = 0;
    bool usedIndex[MAX] = {false};

      bool usedReplace  = false;
      bool usedSkip = false;
      bool used5050 = false;
      bool usedExtraTime = false;

    for(int i = 0; i < totalAsked; i++)
    {
        int index;
        do {
            index = rand() % count;
        } while(usedIndex[index]);

        usedIndex[index] = true;

        MCQ q = questions[index];
        int secondsAllowed = 10;

        time_t questionStart = time(0);

        cout << "\nQ" << i+1 << " : " << q.question << "\n";
        cout << "1. " << q.A << "\n";
        cout << "2. " << q.B << "\n";
        cout << "3. " << q.C << "\n";
        cout << "4. " << q.D << "\n";
        cout << "\nYou have 10 seconds.\n";

        cout << "\n--- Lifelines (One Chance) ---\n";

        if(!usedReplace)   
            cout << "0. Replace question\n";
        if(!usedSkip)      
            cout << "5. Skip without penalty\n";
        if(!used5050)      
            cout << "6. 50-50\n";
        if(!usedExtraTime) 
            cout << "7. Extra 10 seconds\n";
        
            cout << "Your answer: ";

        int ans;
        cin >> ans;

// ---------------------
//      Lifelines
// ---------------------

// Replace question
        if(ans == 0)
        {
            if(usedReplace) 
            {
                cout << "You already used this lifeline!\n";
                continue; // question will count as normal, don't decrement i
            }

                usedReplace = true;
                usedIndex[index] = false;
                i--; // re-ask a new question
                continue;
        }


// Skip question
        if(ans == 5)
        {
            if(usedSkip) 
            {
                cout << "You already used Skip!\n";
                continue; // skip counts as asked, don't decrement
            }
                usedSkip = true;
                cout << "Question skipped.\n";
                continue;
        }

// 50-50
        if(ans == 6)
        {
            if(used5050) 
            {
                cout << "Already used!\n";
                continue;
            }
                used5050 = true;

                 if(q.correct == 1)
                cout << "1. " << q.A << "\n3. " << q.C << "\n";

                else if(q.correct == 2)
                cout << "2. " << q.B << "\n4. " << q.D << "\n";

                else if(q.correct == 3)
                cout << "1. " << q.A << "\n3. " << q.C << "\n";

                else
                cout << "2. " << q.B << "\n4. " << q.D << "\n";

                cout<<"Your Answer: ";
                cin >> ans;
        }

// Extra time
        if(ans == 7)
        {
            if(usedExtraTime)
            {
                cout << "Already used!\n";
                continue;
            }
                usedExtraTime = true;
                secondsAllowed += 10;
        }


//==========================================
//===============Timer======================
//==========================================

        time_t end = time(0);
        double taken = difftime(end, questionStart);

        if(taken > secondsAllowed)
        {
            cout << "Time's up! You took " << taken << " seconds.\n";
            score -= 2;
            usedIndex[index] = false;
            i--;
            continue;
        }

        // Result check
        if(ans == q.correct)
        {
            cout << "Correct!\n";
            score++;
        }
        else
        {
            cout << "Wrong. Correct: " << q.correct << "\n";
            incorrect[wrongcount++] = q;
        }
    }
    //======================================
    //=============Results==================
    //======================================
    cout << "\n====================\n";
    cout << "Your Score: " << score << "\n";
    cout << "Total Asked: " << totalAsked << "\n";

    int choice;
    cout << "\nView wrong answers? (1-Yes, 2-No): ";
    cin >> choice;
    if(choice == 1)
    {
        for(int i = 0; i < wrongcount; i++)
        {
            MCQ q = incorrect[i];
            cout << "\nQuestion: " << q.question << "\n";
            cout << "1. " << q.A << "\n";
            cout << "2. " << q.B << "\n";
            cout << "3. " << q.C << "\n";
            cout << "4. " << q.D << "\n";
            cout << "Correct: " << q.correct << "\n";
        }
    }
}


// ----------------------
// OTHER CATEGORY PLACEHOLDERS
// ----------------------
void sports(int x) { cout << "Sports category coming soon!\n"; }
void computer(int x) { cout << "Computer category coming soon!\n"; }
void history(int x) { cout << "History category coming soon!\n"; }
void iqlogic(int x) { cout << "IQ/Logic category coming soon!\n"; }

