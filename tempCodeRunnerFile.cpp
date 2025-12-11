#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <algorithm>
#include <vector>
using namespace std;

// ----------------------
// Struct for MCQs
// -----------------------
struct MCQ {
    string question, A, B, C, D;
    int correct;
};

// Struct for High Score
struct HighScore {
    string playerName;
    int score;
    string category;
    string difficulty;
    string date;
};

// ----------------------
// Function Declarations
// ----------------------
int game(int);
int highscore(int);
int review(int);
void science(int);
void sports(int);
void computer(int);
void history(int);
void iqlogic(int);
void updateHighScore(string playerName, int score, string category, string difficulty, string date);
void saveQuizLog(string playerName, int score, int correct, int wrong, int skipped, string category, string difficulty, string date);
string getCurrentDateTime();

// ----------------------
// Get Current Date & Time
// ----------------------
// string getCurrentDateTime()
//  {
//     time_t now = time(0);
//     struct tm timeInfo;
//     localtime_s(&timeInfo, &now);
    
//     char buffer[80];
//     strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeInfo);
//     return string(buffer);
// }

// ----------------------
// MAIN FUNCTION
// ----------------------
int main() 
{
    int n;
    cout << "========================================\n";
    cout << "       QUIZ GAMING ARENA\n";
    cout << "========================================\n";
    cout << "1. Start Quiz\n";
    cout << "2. View High Scores\n";
    cout << "3. Review Quiz Logs\n";
    cout << "4. Exit Game\n";
    cout << "========================================\n";
    cout << "Your choice: ";
    cin >> n;
    
    if (n == 1) 
        game(n);
    else if (n == 2) 
        highscore(n);
    else if (n == 3)
        review(n);
    else if (n == 4) 
        cout << "\nThank you for playing! Goodbye!\n";
    else
        cout << "\nInvalid choice!\n";
    
    return 0;
}

//=======================
//====Review Quiz Logs===
//=======================
int review(int x)
{
    ifstream file("quizlog.txt");
    if(!file) 
    {
        cout << "\n[INFO] No quiz logs found yet!\n";
        cout << "Play some quizzes to see logs here.\n";
        return 0;
    }
    
    system("cls");
    cout << "\n========================================\n";
    cout << "          QUIZ LOG HISTORY\n";
    cout << "========================================\n";
    
    string line;
    while(getline(file, line)) 
    {
        cout << line << endl;
    }
    
    file.close();
    cout << "\nPress any key to return to main menu...";
    _getch();
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
        cout << "\n[INFO] No high scores recorded yet!\n";
        cout << "Be the first to set a high score!\n";
        return 0;
    }
    
    system("cls");
    cout << "\n========================================\n";
    cout << "         TOP 5 HIGH SCORES\n";
    cout << "========================================\n";
    
    string line;
    int rank = 1;
    while(getline(file, line)) 
    {
        if (line.find("Player:") != string::npos) 
        {
            cout << "\n#" << rank++ << " " << line << endl;
        } else {
            cout << line << endl;
        }
    }
    
    file.close();
    cout << "\nPress any key to return to main menu...";
    _getch();
    return 0;
}

//=======================
// UPDATE HIGH SCORE FILE
//=======================
void updateHighScore(string playerName, int score, string category, string difficulty, string date) 
{
    vector<HighScore> scores;
    
    // Read existing high scores
    ifstream inFile("highscore.txt");
    if (inFile) {
        string line;
        while (getline(inFile, line)) {
            if (line.find("Player:") != string::npos) 
            {
                HighScore hs;
                // Parse player name
                size_t pos = line.find("Player: ");
                if (pos != string::npos) {
                    hs.playerName = line.substr(pos + 8);
                }
                
                // Parse score
                if (getline(inFile, line) && line.find("Score: ") != string::npos) {

                    pos = line.find("Score: ");
                    hs.score = stoi(line.substr(pos + 7));
                }
                
                // Parse category
                if (getline(inFile, line) && line.find("Category: ") != string::npos) 
                {
                    pos = line.find("Category: ");
                    hs.category = line.substr(pos + 10);
                }
                
                // Parse difficulty
                if (getline(inFile, line) && line.find("Difficulty: ") != string::npos) 
                {
                    pos = line.find("Difficulty: ");
                    hs.difficulty = line.substr(pos + 12);
                }
                
                // Parse date
                if (getline(inFile, line) && line.find("Date: ") != string::npos) 
                {
                    pos = line.find("Date: ");
                    hs.date = line.substr(pos + 6);
                }
                
                scores.push_back(hs);
                getline(inFile, line); // Read separator line
            }
        }
        inFile.close();
    }
    
    // Add new score
    HighScore newScore;
    newScore.playerName = playerName;
    newScore.score = score;
    newScore.category = category;
    newScore.difficulty = difficulty;
    newScore.date = date;
    scores.push_back(newScore);
    
    // Sort by score (descending)
    sort(scores.begin(), scores.end(), [](const HighScore& a, const HighScore& b) 
    {
        return a.score > b.score;
    });
    
    // Keep only top 5
    if (scores.size() > 5) 
    {
        scores.resize(5);
    }
    
    // Write back to file
    ofstream outFile("highscore.txt");
    if (outFile) 
    {
        for (const auto& hs : scores) 
        {
            outFile << "Player: " << hs.playerName << "\n";
            outFile << "Score: " << hs.score << "\n";
            outFile << "Category: " << hs.category << "\n";
            outFile << "Difficulty: " << hs.difficulty << "\n";
            outFile << "Date: " << hs.date << "\n";
            outFile << "----------------------------------------\n";
        }
        outFile.close();
    }
}

//=======================
// SAVE QUIZ LOG
//=======================
void saveQuizLog(string playerName, int score, int correct, int wrong, int skipped, string category, string difficulty, string date)
 {
    ofstream file("quizlog.txt", ios::app);
    if (file) 
    {
        file << "========================================\n";
        file << "Player: " << playerName << "\n";
        file << "Category: " << category << "\n";
        file << "Difficulty: " << difficulty << "\n";
        file << "Date & Time: " << date << "\n";
        file << "----------------------------------------\n";
        file << "Total Score: " << score << " points\n";
        file << "Correct Answers: " << correct << "\n";
        file << "Wrong Answers: " << wrong << "\n";
        file << "Skipped/Timeout: " << skipped << "\n";
        file << "========================================\n\n";
        file.close();
    }
}

// ------------------------------
// GAME FUNCTION: Choose Category
// ------------------------------
int game(int x) 
{
    int n;
    system("cls");
    cout << "\n========================================\n";
    cout << "       SELECT QUIZ CATEGORY\n";
    cout << "========================================\n";
    cout << "1. Science\n";
    cout << "2. History\n";
    cout << "3. Sports\n";
    cout << "4. Computer\n";
    cout << "5. IQ/Logic\n";
    cout << "========================================\n";
    cout << "Your choice: ";
    cin >> n;
    
    switch (n) 
    {
        case 1: science(n); break;
        case 2: history(n); break;
        case 3: sports(n); break;
        case 4: computer(n); break;
        case 5: iqlogic(n); break;
        default: cout << "\nInvalid choice!\n";
    }
    return 0;
}

// ----------------------
// SCIENCE CATEGORY FUNCTION
// ----------------------
void science(int x) {
    string playerName;
    cout << "\nEnter Player Name: ";
    cin.ignore();
    getline(cin, playerName);
    
    string quizDateTime = getCurrentDateTime();
    
    int difficulty;
    system("cls");
    cout << "\n========================================\n";
    cout << "       SCIENCE QUIZ CHALLENGE\n";
    cout << "========================================\n";
    cout << "Select Difficulty Level:\n";
    cout << "1. Easy\n";
    cout << "2. Medium\n";
    cout << "3. Hard\n";
    cout << "========================================\n";
    cout << "Your choice: ";
    cin >> difficulty;
    
    if (difficulty < 1 || difficulty > 3) 
    {
        cout << "\n[ERROR] Invalid difficulty level!\n";
        Sleep(2000);
        return;
    }
    
    string difficultyStr = (difficulty == 1) ? "Easy" : (difficulty == 2) ? "Medium" : "Hard";
    
    const int MAX = 100;
    MCQ questions[MAX], incorrect[MAX], correct[MAX];
    int count = 0, wrongcount = 0, rightcount = 0;
    
    ifstream file("science.txt");
    if (!file) {
        cout << "\n[ERROR] File 'science.txt' not found!\n";
        Sleep(2000);
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
        
        if (stoi(diffStr) == difficulty) {
            questions[count++] = temp;
        }
    }
    file.close();
    
    if (count == 0) 
    {
        cout << "\n[ERROR] No questions found for this difficulty level!\n";
        Sleep(2000);
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
    
    system("cls");
    cout << "\n========================================\n";
    cout << "          SCORING SYSTEM\n";
    cout << "========================================\n";
    cout << "Base Points: " << basePoints << " per question\n";
    cout << "Fast Bonus: +" << bonusPoints << " (answer within 5 sec)\n";
    cout << "Wrong Penalty: -" << penaltyPoints << "\n";
    cout << "Timeout Penalty: -" << (penaltyPoints / 2) << "\n";
    cout << "========================================\n";
    cout << "Total Questions: " << totalAsked << "\n";
    cout << "========================================\n";
    cout << "\nStarting in 3 seconds...\n";
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
            cout << "Question " << i + 1 << " of " << totalAsked << " | Points: " << totalPoints << "\n";
            cout << "========================================\n";
            cout << q.question << "\n\n";
            cout << "1. " << q.A << "\n";
            cout << "2. " << q.B << "\n";
            cout << "3. " << q.C << "\n";
            cout << "4. " << q.D << "\n";
            
            // Display lifelines
            cout << "\n--- Lifelines ---\n";
            if (!usedReplace) cout << "0. Replace Question\n";
            if (!usedSkip) cout << "5. Skip (No Penalty)\n";
            if (!used5050) cout << "6. 50-50\n";
            if (!usedExtraTime) cout << "7. Extra 10 Seconds\n";
            cout << "-----------------\n";
            
            cout << "\nTime: " << secondsAllowed << "s | Potential: " << basePoints;
            if (secondsAllowed >= 5) cout << " (+" << bonusPoints << " if fast)";
            cout << "\nYour answer: ";
            
            // Timer
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
            
            auto endTime = chrono::steady_clock::now();
            int timeTaken = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();
            
            // Time's up
            if (!inputReceived) 
            {
                int penalty = penaltyPoints / 2;
                totalPoints -= penalty;
                if (totalPoints < 0) totalPoints = 0;
                cout << "\n\n[TIME'S UP!] -" << penalty << " points\n";
                Sleep(2000);
                questionAnswered = true;
                continue;
            }
            
            // Handle lifelines
            if (anss == 0) { // Replace
                if (usedReplace) 
                {
                    cout << "\n[ERROR] Already used!\n";
                    Sleep(1500);
                    continue;
                }
                usedReplace = true;
                usedIndex[index] = false;
                i--;
                cout << "\n[LIFELINE] Question replaced!\n";
                Sleep(1500);
                questionAnswered = true;
            }
            else if (anss == 5) 
            { // Skip
                if (usedSkip) 
                {
                    cout << "\n[ERROR] Already used!\n";
                    Sleep(1500);
                    continue;
                }
                usedSkip = true;
                cout << "\n[LIFELINE] Question skipped!\n";
                Sleep(1500);
                questionAnswered = true;
            }
            else if (anss == 6) 
            { // 50-50
                if (used5050)
                 {
                    cout << "\n[ERROR] Already used!\n";
                    Sleep(1500);
                    continue;
                }
                used5050 = true;
                cout << "\n[LIFELINE] 50-50 activated!\n";
                cout << "\nRemaining options:\n";

                if (q.correct == 1 || q.correct == 3) 
                {
                    cout << "1. " << q.A << "\n3. " << q.C << "\n";
                } else {
                    cout << "2. " << q.B << "\n4. " << q.D << "\n";
                }
                cout << "\nYour answer: ";
                char choice = _getch();
                anss = choice - '0';
                cout << choice << endl;
            }
            else if (anss == 7) { // Extra time
                if (usedExtraTime) 
                {
                    cout << "\n[ERROR] Already used!\n";
                    Sleep(1500);
                    continue;
                }
                usedExtraTime = true;
                secondsAllowed += 10;
                cout << "\n[LIFELINE] +10 seconds!\n";
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
                        cout << "\nCORRECT! FAST BONUS!\n";
                        cout << "Points: " << basePoints << " + " << bonusPoints << " = " << pointsEarned << "\n";
                    } 
                    else 
                    {
                        cout << "\nCORRECT! Correct\n";
                        cout << "Points Earned: " << pointsEarned << "\n";
                    }
                    totalPoints += pointsEarned;
                    correct[rightcount++] = q;
                    score++;
                } else 
                {
                    cout << "\nWRONG! Incorrect\n";
                    cout << "Correct answer: Option " << q.correct << "\n";
                    cout << "Penalty: -" << penaltyPoints << " points\n";
                    totalPoints -= penaltyPoints;
                    if (totalPoints < 0) totalPoints = 0;
                    incorrect[wrongcount++] = q;
                }
                cout << "Total Points: " << totalPoints << "\n";
                Sleep(3000);
                questionAnswered = true;
            }
        }
    }
    
    int maxPossiblePoints = totalAsked * (basePoints + bonusPoints);
    int skipped = totalAsked - rightcount - wrongcount;
    
    // Display Results

    system("cls");
    cout << "\n========================================\n";
    cout << "         QUIZ COMPLETED!\n";
    cout << "========================================\n";
    cout << "Player: " << playerName << "\n";
    cout << "Category: Science\n";
    cout << "Difficulty: " << difficultyStr << "\n";
    cout << "Date: " << quizDateTime << "\n";
    cout << "----------------------------------------\n";
    cout << "Correct: " << rightcount << "/" << totalAsked << "\n";
    cout << "Wrong: " << wrongcount << "\n";
    cout << "Skipped/Timeout: " << skipped << "\n";
    cout << "----------------------------------------\n";
    cout << "FINAL SCORE: " << totalPoints << " points\n";
    cout << "Max Possible: " << maxPossiblePoints << "\n";
    cout << "========================================\n";
    
    // Lifelines summary
    cout << "\nLifelines Used:\n";
    cout << (usedReplace ? "Correct" : "Incorrect") << " Replace\n";
    cout << (usedSkip ? "Correct" : "Incorrect") << " Skip\n";
    cout << (used5050 ? "Correct" : "Incorrect") << " 50-50\n";
    cout << (usedExtraTime ? "Correct" : "Incorrect") << " Extra Time\n";
    
    // Save to files
    updateHighScore(playerName, totalPoints, "Science", difficultyStr, quizDateTime);
    saveQuizLog(playerName, totalPoints, rightcount, wrongcount, skipped, "Science", difficultyStr, quizDateTime);
    
    cout << "\nScore saved to high score list!\n";
    cout << " Quiz log updated!\n";
    
    // Review incorrect answers
    if (wrongcount > 0)
     {
        int choice;
        cout << "\nReview incorrect answers?\n";
        cout << "1. Yes\n2. No\n";
        cout << "Choice: ";
        cin >> choice;
        
        if (choice == 1)
         {
            system("cls");
            cout << "\n========================================\n";
            cout << "      INCORRECT ANSWERS REVIEW\n";
            cout << "========================================\n";
            for (int i = 0; i < wrongcount; i++) {
                MCQ q = incorrect[i];
                cout << "\n" << i + 1 << ". " << q.question << "\n";
                cout << "   1. " << q.A << "\n";
                cout << "   2. " << q.B << "\n";
                cout << "   3. " << q.C << "\n";
                cout << "   4. " << q.D << "\n";
                cout << "   Correct: Option " << q.correct << "\n";
                cout << "----------------------------------------\n";
            }
        }
    }
    
    cout << "\nPress any key to return to main menu...";
    _getch();
}

// ----------------------
// OTHER CATEGORY PLACEHOLDERS
// ----------------------

void sports(int x)
 {
    cout << "\n[INFO] Sports category coming soon!\n";
    Sleep(2000);
}

void computer(int x)
 {
    cout << "\n[INFO] Computer category coming soon!\n";
    Sleep(2000);
}

void history(int x) 
{
    cout << "\n[INFO] History category coming soon!\n";
    Sleep(2000);
}

void iqlogic(int x) 
{
    cout << "\n[INFO] IQ/Logic category coming soon!\n";
    Sleep(2000);
}