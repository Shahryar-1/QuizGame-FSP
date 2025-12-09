#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>
#include <windows.h>
#include <conio.h>

using namespace std;

// ----------------------
// Struct for MCQs
// -----------------------
struct MCQ 
{
    string question, A, B, C, D;
    int correct;
};

//Struct for Highscore

struct HighScore 
{
        string name;
        int score;
    };


// ----------------------
// Function Declarations
// ----------------------
int game(int);
int highscore(int);
int review(int);
int highscores(int,string);

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

//=======================
//====Review Questions===
//=======================

int review(int x)
{
    ifstream file("quizlog.txt");

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

//=======================
// HIGH SCORE FUNCTION
//======================= 

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

// ------------------------------
// GAME FUNCTION: Choose Category
// ------------------------------

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

    switch (n) 
    {
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
    string name;
    
    // Get current date and time
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    cout << "\n========================================\n";
    cout << "     SCIENCE QUIZ CHALLENGE\n";
    cout << "========================================\n";
    cout << "Date: " << 1 + ltm->tm_mon << "/" << ltm->tm_mday << "/" << 1900 + ltm->tm_year << "\n";
    cout << "Time: " << ltm->tm_hour << ":" << ltm->tm_min << "\n";
    cout << "========================================\n";
    
    cout<<"Enter your Name: ";
    cin >> name;
    cout<<endl;
    cout << "Please Enter difficulty level:\n";
    cout << " 1 - Easy\n";
    cout << " 2 - Medium\n";
    cout << " 3 - Hard\n";
    cout << "Your choice: ";
    cin >> difficulty;

    if (difficulty < 1 || difficulty > 3) {
        cout << "\n[ERROR] Invalid difficulty level!\n";
        return;
    }

    const int MAX = 100;
    MCQ questions[MAX], incorrect[MAX], correct[MAX];
    int count = 0, wrongcount = 0, rightcount = 0;

    ifstream file("science.txt");
    if (!file) {
        cout << "\n[ERROR] File 'science.txt' not found!\n";
        return;
    }

    // Load questions based on difficulty
    string line;
    while (getline(file, line) && count < MAX) 
    {
        stringstream ss(line);
        MCQ temp;
        getline(ss, temp.question, '|');
        getline(ss, temp.A, '|');
        getline(ss, temp.B, '|');
        getline(ss, temp.C, '|');
        getline(ss, temp.D, '|');
        string correctStr, diffStr;
        getline(ss, correctStr, '|');
        temp.correct = stoi(correctStr);
        getline(ss, diffStr, '|');
        if (stoi(diffStr) == difficulty) 
        {
            questions[count++] = temp;
        }
    }
    file.close();

    if (count == 0) 
    {
        cout << "\n[ERROR] No questions found for this difficulty level!\n";
        return;
    }

    srand(time(0));
    int totalAsked = 10;
    int score = 0;
    int totalPoints = 0;
    bool usedIndex[MAX] = {false};

    // Lifeline flags
    bool usedReplace = false, usedSkip = false, used5050 = false, usedExtraTime = false;

    // Points system based on difficulty
    int basePoints = (difficulty == 1) ? 5 : (difficulty == 2) ? 10 : 15;
    int bonusPoints = (difficulty == 1) ? 2 : (difficulty == 2) ? 5 : 8;
    int penaltyPoints = (difficulty == 1) ? 2 : (difficulty == 2) ? 3 : 5;

    cout << "\n========================================\n";
    cout << "       SCORING SYSTEM\n";
    cout << "========================================\n";
    cout << "Base Points per Question: " << basePoints << "\n";
    cout << "Fast Answer Bonus: +" << bonusPoints << " (if answered in 5 seconds)\n";
    cout << "Wrong Answer Penalty: -" << penaltyPoints << "\n";
    cout << "Time's Up Penalty: -" << (penaltyPoints / 2) << "\n";
    cout << "========================================\n";
    cout << "Quiz Starting! Total Questions: " << totalAsked << "\n";
    cout << "========================================\n";
    Sleep(3000);

    for (int i = 0; i < totalAsked; i++)
     {
        // Select random unused question
        int index;
        do {
            index = rand() % count;
        } while (usedIndex[index]);
        usedIndex[index] = true;

        MCQ q = questions[index];
        int secondsAllowed = 10;
        bool questionAnswered = false;

        while (!questionAnswered) 
        {
            system("cls");
            
            // Display question
            cout << "\n========================================\n";
            cout << "Question " << i + 1 << " of " << totalAsked << " | Total Points: " << totalPoints << "\n";
            cout << "========================================\n";
            cout << q.question << "\n\n";
            cout << "1. " << q.A << "\n";
            cout << "2. " << q.B << "\n";
            cout << "3. " << q.C << "\n";
            cout << "4. " << q.D << "\n";

            // Display available lifelines
            cout << "\n--- Lifelines Available ---\n";
            if (!usedReplace) cout << "0. Replace Question\n";
            if (!usedSkip) cout << "5. Skip (No Penalty)\n";
            if (!used5050) cout << "6. 50-50\n";
            if (!usedExtraTime) cout << "7. Extra 10 Seconds\n";
            cout << "---------------------------\n";

            cout << "\nTime Limit: " << secondsAllowed << " seconds\n";
            cout << "Potential Points: " << basePoints << " (+" << bonusPoints << " if fast)\n";
            cout << "Your answer (1-4 or lifeline): ";

            // Timer implementation
            int remaining = secondsAllowed;
            int anss = -1;
            bool inputReceived = false;
            auto startTime = chrono::steady_clock::now();

            while (remaining > 0) 
            {
                if (_kbhit()) 
                {
                    char ch = _getch();
                    if (ch >= '0' && ch <= '7') 
                    {
                        anss = ch - '0';
                        inputReceived = true;
                        cout << ch << endl;
                        break;
                    }
                }

                auto currentTime = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::seconds>(currentTime - startTime).count();
                int newRemaining = secondsAllowed - elapsed;

                if (newRemaining != remaining) 
                {
                    remaining = newRemaining;
                    cout << "\rTime remaining: " << remaining << " seconds " << flush;
                }
                Sleep(100);
            }

            // Calculate time taken for scoring
            auto endTime = chrono::steady_clock::now();
            int timeTaken = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();

            // Time's up
            if (!inputReceived) 
            {
                int penalty = penaltyPoints / 2;
                totalPoints -= penalty;
                if (totalPoints < 0) totalPoints = 0;
                cout << "\n\n[TIME'S UP!] -" << penalty << " points penalty\n";
                cout << "Moving to next question...\n";
                Sleep(2000);
                questionAnswered = true;
                continue;
            }

            // Handle lifelines and answers
            if (anss == 0) 
            {
                if (usedReplace) 
                {
                    cout << "\n[ERROR] Replace lifeline already used!\n";
                    Sleep(1500);
                    continue;
                }
                usedReplace = true;
                usedIndex[index] = false;
                i--;
                cout << "\n[LIFELINE] Question replaced!\n";
                Sleep(1500);
                questionAnswered = true;
            } else if (anss == 5) 
            {
                if (usedSkip) 
                {
                    cout << "\n[ERROR] Skip lifeline already used!\n";
                    Sleep(1500);
                    continue;
                }
                usedSkip = true;
                cout << "\n[LIFELINE] Question skipped without penalty.\n";
                Sleep(1500);
                questionAnswered = true;
            } else if (anss == 6) 
            {
                if (used5050) 
                {
                    cout << "\n[ERROR] 50-50 lifeline already used!\n";
                    Sleep(1500);
                    continue;
                }
                used5050 = true;
                cout << "\n[LIFELINE] 50-50 activated!\n";
                cout << "\nRemaining options:\n";
                if (q.correct == 1 || q.correct == 3) 
                {
                    cout << "1. " << q.A << "\n3. " << q.C << "\n";
                }
                 else 
                {
                    cout << "2. " << q.B << "\n4. " << q.D << "\n";
                }
                cout << "\nYour answer (1-4): ";
                char choice = _getch();
                anss = choice - '0';
                cout << choice << endl;
            } 
            else if (anss == 7) 
            {
                if (usedExtraTime) 
                {
                    cout << "\n[ERROR] Extra Time lifeline already used!\n";
                    Sleep(1500);
                    continue;
                }
                usedExtraTime = true;
                secondsAllowed += 10;
                cout << "\n[LIFELINE] Extra 10 seconds granted!\n";
                Sleep(1500);
                continue;
            }

            // Check answer
            if (anss >= 1 && anss <= 4) 
            {
                if (anss == q.correct) 
                {
                    int pointsEarned = basePoints;
                    if (timeTaken <= 5) 
                    {
                        pointsEarned += bonusPoints;
                        cout << "\nCORRECT! Well done! FAST BONUS!\n";
                        cout << "Points Earned: " << basePoints << " + " << bonusPoints << " = " << pointsEarned << "\n";
                    } else 
                    {
                        cout << "\nCORRECT! Well done!\n";
                        cout << "Points Earned: " << pointsEarned << "\n";
                    }
                    totalPoints += pointsEarned;
                    correct[rightcount++] = q;
                    score++;
                } 
                else 
                {
                    cout << "\nWRONG! Correct answer was: " << q.correct << "\n";
                    cout << "Penalty: -" << penaltyPoints << " points\n";
                    totalPoints -= penaltyPoints;
                    if (totalPoints < 0) totalPoints = 0;
                    incorrect[wrongcount++] = q;
                }
                cout << "Current Total: " << totalPoints << " points\n";
                Sleep(3000);
                questionAnswered = true;
            }
        }
    }

    int maxPossiblePoints = totalAsked * (basePoints + bonusPoints);

    // Display Results
    system("cls");
    cout << "\n========================================\n";
    cout << "       QUIZ COMPLETED!\n";
    cout << "========================================\n";
    cout << "Player Name: "<< name <<endl;
    cout << "Date: " << 1 + ltm->tm_mon << "/" << ltm->tm_mday << "/" << 1900 + ltm->tm_year << "\n";
    cout << "Time: " << ltm->tm_hour << ":" << ltm->tm_min << "\n";
    cout << "========================================\n";
    cout << "Difficulty Level: " << (difficulty == 1 ? "Easy" : difficulty == 2 ? "Medium" : "Hard") << "\n";
    cout << "Total Questions: " << totalAsked << "\n";
    cout << "Correct Answers: " << rightcount << "\n";
    cout << "Wrong Answers: " << wrongcount << "\n";
    cout << "Skipped/Timeout: " << (totalAsked - rightcount - wrongcount) << "\n";
    cout << "----------------------------------------\n";
    cout << "SCORING DETAILS:\n";
    cout << "Total Points Earned: " << totalPoints << "\n";
    cout << "Maximum Possible: " << maxPossiblePoints << "\n";
    cout << "========================================\n";

    // High Score System
    
    HighScore highScores[5];
    int highscorer = 0;

    // Read existing high scores
    ifstream inFile("highscore.txt");
    if (inFile) 
    {
        while (highscorer < 5 && inFile >> highScores[highscorer].name >> highScores[highscorer].score) 
        {
            highscorer++;
        }
        inFile.close();
    }

    // Check if current score qualifies for high score list
    bool isHighScore = false;
    int position = -1;

    if (highscorer < 5) 
    {
        isHighScore = true;
        position = highscorer;
    }
    else 
    {
        for (int i = 0; i < 5; i++) 
        {
            if (totalPoints > highScores[i].score) 
            {
                isHighScore = true;
                position = i;
                break;
            }
        }
    }

    if (isHighScore) 
    {
        cout << "\nCONGRATULATIONS! NEW HIGH SCORE!\n";
        cout << "You ranked #" << position + 1 << " in the leaderboard!\n";

        // Insert new high score at correct position
        for (int i = 4; i > position; i--) 
        {
            if (i - 1 < highscorer) 
            {
                highScores[i] = highScores[i - 1];
            }
        }

        highScores[position].name = name;
        highScores[position].score = totalPoints;

        if (highscorer < 5) highscorer++;

        // Write updated high scores to file
        ofstream outFile("highscore.txt");
        for (int i = 0; i < highscorer; i++) 
        {
            outFile << highScores[i].name << " " << highScores[i].score << "\n";
        }
        outFile.close();

        cout << "Your score has been saved!\n";
    }

    // Display High Scores
    cout << "\n========================================\n";
    cout << "       TOP 5 HIGH SCORES\n";
    cout << "========================================\n";
    for (int i = 0; i < highscorer; i++) 
    {
        cout << i + 1 << ". " << highScores[i].name << " - " << highScores[i].score << " points\n";
    }
    cout << "========================================\n";

    // Lifelines used summary
    cout << "\nLIFELINES USED:\n";
    cout << (usedReplace ? "Yes" : "No") << " Replace Question\n";
    cout << (usedSkip ? "Yes" : "No") << " Skip Without Penalty\n";
    cout << (used5050 ? "Yes" : "No") << " 50-50\n";
    cout << (usedExtraTime ? "Yes" : "No") << " Extra Time\n";
    cout << "========================================\n";

    // Review wrong answers
    if (wrongcount > 0) 
    {
        int choice;
        cout << "\nWould you like to review incorrect answers?\n";
        cout << "1. Yes\n2. No\n";
        cout << "Your choice: ";
        cin >> choice;

        if (choice == 1) 
        {
            system("cls");

            cout << "\n========================================\n";
            cout << "   INCORRECT ANSWERS REVIEW\n";
            cout << "========================================\n";

            for (int i = 0; i < wrongcount; i++) 
            {
                MCQ q = incorrect[i];
                cout << "\nQuestion " << i + 1 << ": " << q.question << "\n";
                cout << "1. " << q.A << "\n";
                cout << "2. " << q.B << "\n";
                cout << "3. " << q.C << "\n";
                cout << "4. " << q.D << "\n";
                cout << "Correct Answer: " << q.correct << "\n";
                cout << "----------------------------------------\n";
            }
        }
    }

    int want;
    cout<<"\nYou want to Review your Quiz: ";
    cout<<"1. Yes\n";
    cout<<"2. No\n";
    cin >> want;

    if(want==1)
    {
        ofstream logFile("quizlog.txt", ios::app);
        if(logFile)
        {
            time_t now2 = time(0);
            string dt = ctime(&now2);

            logFile << "====================\n";
            logFile << "Player: " << name << "\n";
            logFile << "Date: " << dt;
            logFile << "Total Score: " << totalPoints << "\n";
            logFile << "Total Questions Asked: " << totalAsked << "\n";

            logFile << "Correct Questions:\n";
            for(int i = 0; i < rightcount; i++)
            {
                MCQ q = correct[i];
                logFile << "Q: " << q.question << "\n";
                logFile << "1. " << q.A << "\n";
                logFile << "2. " << q.B << "\n";
                logFile << "3. " << q.C << "\n";
                logFile << "4. " << q.D << "\n";
                logFile << "Correct Answer: " << q.correct << "\n";
            }

            logFile << "Incorrect Questions:\n";
            for(int i = 0; i < wrongcount; i++)
            {
                MCQ q = incorrect[i];
                logFile << "Q: " << q.question << "\n";
                logFile << "1. " << q.A << " 2. " << q.B << " 3. " << q.C << " 4. " << q.D << "\n";
                logFile << "Correct Answer: " << q.correct << "\n";
            }

            logFile << "====================\n\n";
            logFile.close();

            cout << "\nYour quiz has been logged in quizlog.txt\n";
        }   
    }

    int replay;
    cout<<"\nYou Want to Play Again: \n";
    cout<<"1.Yes\n";
    cout<<"2.No\n";
    cin >> replay;

    if(replay==1)
    {
        science(x);
    }
    else
    {
        cout<<"Thanks For Playing, Have a Nice day!\n";
    }

    int visit;
    cout<<"You Want to Visit Highscorers list: \n";
    cout<<"1. Yes\n";
    cout<<"2. No \n";
    cin >> visit;

    if(visit==1)
    {
        highscore(visit);
    }
    
    cout << "\nPress any key to return to main menu...";
    _getch();
}

// ----------------------
// OTHER CATEGORY PLACEHOLDERS
// ----------------------

void sports(int x) { cout << "Sports category coming soon!\n"; }
void computer(int x) { cout << "Computer category coming soon!\n"; }
void history(int x) { cout << "History category coming soon!\n"; }
void iqlogic(int x) { cout << "IQ/Logic category coming soon!\n"; }

