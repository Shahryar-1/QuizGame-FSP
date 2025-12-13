// Quiz Game - Without Struct Version
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <chrono>

using namespace std;

// ----------------------
// Function Declarations
// ----------------------
int highscore(int);
int review(int);

//=======================
//====Review Questions===
//=======================
int review(int x)
{
    ifstream file("quizlog.txt");
    if (!file) {
        cout << "File not found!\n";
        return 0;
    }
    string line;
    while (getline(file, line))
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
    if (!file)
    {
        cout << "No high scores yet!\n";
        return 0;
    }
    string line;
    cout << "\n========================================\n";
    cout << " TOP HIGH SCORES\n";
    cout << "========================================\n";
    while (getline(file, line))
    {
        cout << line << endl;
    }
    cout << "========================================\n";
    file.close();
    return 0;
}

// ----------------------
// MAIN FUNCTION
// ----------------------
int main()
{
 
    int n;
    cout << "=======================================\n";
    cout << "==             Quiz Game             ==\n";
    cout << "==        Quiz Gaming Arena          ==\n";
    cout << "=======================================\n";
    cout << "Press 1 to Start quiz" << endl;
    cout << "Press 2 to view High Score" << endl;
    cout << "Press 3 to Exit Game" << endl;
    cin >> n;

    if (n == 1)
    {
        // Category Selection
        int category;
        string filename;
        string categoryName;

        cout << "\nWelcome to the Quiz Game\n";
        cout << "Which Category you want?\n";
        cout << "Press 1 for Science\n";
        cout << "Press 2 for History\n";
        cout << "Press 3 for Sports\n";
        cout << "Press 4 for Computer\n";
        cout << "Press 5 for IQ/Logic\n";
        cout << "Your choice: ";
        cin >> category;

        if (category == 1) {
            filename = "science.txt";
            categoryName = "Science";
        }
        else if (category == 2) {
            filename = "history.txt";
            categoryName = "History";
        }
        else if (category == 3) {
            filename = "sports.txt";
            categoryName = "Sports";
        }
        else if (category == 4) {
            filename = "computer.txt";
            categoryName = "Computer";
        }
        else if (category == 5) {
            filename = "iq.txt";
            categoryName = "IQ/Logic";
        }
        else {
            cout << "\n[ERROR] Invalid category choice!\n";
            return 0;
        }

        // Start Quiz
        int difficulty;
        string name;

        // Get current date and time
        time_t now = time(0);
        tm* ltm = localtime(&now);

        cout << "\n========================================\n";
        cout << " " << categoryName << " QUIZ CHALLENGE\n";
        cout << "========================================\n";
        cout << "Date: " << 1 + ltm->tm_mon << "/" << ltm->tm_mday << "/" << 1900 + ltm->tm_year << "\n";
        cout << "Time: " << ltm->tm_hour << ":" << ltm->tm_min << "\n";
        cout << "========================================\n";
        cout << "Enter your Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "\nSelect Difficulty Level:\n";
        cout << "1. Easy\n2. Medium\n3. Hard\n";
        cout << "Your choice: ";
        cin >> difficulty;

        if (difficulty < 1 || difficulty > 3) {
            cout << "\n[ERROR] Invalid difficulty level!\n";
            return 0;
        }

        const int MAX = 100;
        // Arrays for questions
        string questions[MAX], optionA[MAX], optionB[MAX], optionC[MAX], optionD[MAX];
        int correctAnswer[MAX];
        
        // Arrays for incorrect questions
        string incorrectQ[MAX], incorrectA[MAX], incorrectB[MAX], incorrectC[MAX], incorrectD[MAX];
        int incorrectCorrect[MAX];
        
        // Arrays for correct questions
        string correctQ[MAX], correctA[MAX], correctB[MAX], correctC[MAX], correctD[MAX];
        int correctCorrect[MAX];
        
        int count = 0, wrongcount = 0, rightcount = 0;

        ifstream file(filename);
        if (!file) {
            cout << "\n[ERROR] File '" << filename << "' not found!\n";
            return 0;
        }

        // Load questions based on difficulty
        string line;
        while (getline(file, line) && count < MAX) {
            if (line.empty()) continue;

            stringstream ss(line);
            string tempQ, tempA, tempB, tempC, tempD, correctStr, diffStr;

            getline(ss, tempQ, '|');
            getline(ss, tempA, '|');
            getline(ss, tempB, '|');
            getline(ss, tempC, '|');
            getline(ss, tempD, '|');
            getline(ss, correctStr, '|');
            getline(ss, diffStr, '|');

            int tempCorrect = stoi(correctStr);
            int questionDiff = stoi(diffStr);

            if (questionDiff == difficulty) {
                questions[count] = tempQ;
                optionA[count] = tempA;
                optionB[count] = tempB;
                optionC[count] = tempC;
                optionD[count] = tempD;
                correctAnswer[count] = tempCorrect;
                count++;
            }
        }
        file.close();

        if (count == 0) {
            cout << "\n[ERROR] No questions found for this difficulty level!\n";
            return 0;
        }

        srand(time(0));
        int totalAsked = (count < 10) ? count : 10;
        int score = 0;
        int totalPoints = 0;
        bool usedIndex[MAX] = { false };

        // Lifeline flags
        bool usedReplace = false, usedSkip = false, used5050 = false, usedExtraTime = false;

        // Points system based on difficulty
        int basePoints = (difficulty == 1) ? 5 : (difficulty == 2) ? 10 : 15;
        int bonusPoints = (difficulty == 1) ? 2 : (difficulty == 2) ? 5 : 8;
        int penaltyPoints = (difficulty == 1) ? 2 : (difficulty == 2) ? 3 : 5;

        cout << "\n========================================\n";
        cout << " SCORING SYSTEM\n";
        cout << "========================================\n";
        cout << "Base Points per Question: " << basePoints << "\n";
        cout << "Fast Answer Bonus: +" << bonusPoints << " (if answered in 5 seconds)\n";
        cout << "Wrong Answer Penalty: -" << penaltyPoints << "\n";
        cout << "Time's Up Penalty: -" << (penaltyPoints / 2) << "\n";
        cout << "========================================\n";
        cout << "Quiz Starting! Total Questions: " << totalAsked << "\n";
        cout << "========================================\n";
        Sleep(3000);

        for (int i = 0; i < totalAsked; i++) {
            // Select random unused question
            int index;
            do {
                index = rand() % count;
            } while (usedIndex[index]);
            usedIndex[index] = true;

            int secondsAllowed = 10;
            bool questionAnswered = false;

            while (!questionAnswered) {
                system("cls");

                // Display question
                cout << "\n========================================\n";
                cout << "Question " << i + 1 << " of " << totalAsked << " | Total Points: " << totalPoints << "\n";
                cout << "========================================\n";
                cout << questions[index] << "\n\n";
                cout << "1. " << optionA[index] << "\n";
                cout << "2. " << optionB[index] << "\n";
                cout << "3. " << optionC[index] << "\n";
                cout << "4. " << optionD[index] << "\n";

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

                while (remaining > 0) {
                    if (_kbhit()) {
                        char ch = _getch();
                        if (ch >= '0' && ch <= '7') {
                            anss = ch - '0';
                            inputReceived = true;
                            cout << ch << endl;
                            break;
                        }
                    }

                    auto currentTime = chrono::steady_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::seconds>(currentTime - startTime).count();
                    int newRemaining = secondsAllowed - elapsed;

                    if (newRemaining != remaining) {
                        remaining = newRemaining;
                    }
                    Sleep(100);
                }

                // Calculate time taken for scoring
                auto endTime = chrono::steady_clock::now();
                int timeTaken = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();

                // Time's up
                if (!inputReceived) {
                    int penalty = penaltyPoints / 2;
                    totalPoints -= penalty;
                    if (totalPoints < 0) totalPoints = 0;
                    cout << "\n\n[TIME'S UP!] -" << penalty << " points penalty\n";
                    cout << "Correct answer was: " << correctAnswer[index] << "\n";
                    cout << "Moving to next question...\n";
                    
                    incorrectQ[wrongcount] = questions[index];
                    incorrectA[wrongcount] = optionA[index];
                    incorrectB[wrongcount] = optionB[index];
                    incorrectC[wrongcount] = optionC[index];
                    incorrectD[wrongcount] = optionD[index];
                    incorrectCorrect[wrongcount] = correctAnswer[index];
                    wrongcount++;
                    
                    Sleep(2000);
                    questionAnswered = true;
                    continue;
                }

                // Handle lifelines and answers
                if (anss == 0) {
                    if (usedReplace) {
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
                }
                else if (anss == 5) {
                    if (usedSkip) {
                        cout << "\n[ERROR] Skip lifeline already used!\n";
                        Sleep(1500);
                        continue;
                    }
                    usedSkip = true;
                    cout << "\n[LIFELINE] Question skipped without penalty.\n";
                    Sleep(1500);
                    questionAnswered = true;
                }
                else if (anss == 6) {
                    if (used5050) {
                        cout << "\n[ERROR] 50-50 lifeline already used!\n";
                        Sleep(1500);
                        continue;
                    }
                    used5050 = true;
                    cout << "\n[LIFELINE] 50-50 activated!\n";
                    cout << "\nRemaining options:\n";

                    if (correctAnswer[index] == 1 || correctAnswer[index] == 3) {
                        cout << "1. " << optionA[index] << "\n3. " << optionC[index] << "\n";
                    }
                    else {
                        cout << "2. " << optionB[index] << "\n4. " << optionD[index] << "\n";
                    }

                    cout << "\nYour answer (1-4): ";
                    char choice = _getch();
                    anss = choice - '0';
                    cout << choice << endl;

                    if (anss < 1 || anss > 4) {
                        cout << "\n[ERROR] Invalid input!\n";
                        Sleep(1500);
                        continue;
                    }
                    // Fall through to answer checking
                }
                else if (anss == 7) {
                    if (usedExtraTime) {
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
                if (anss >= 1 && anss <= 4) {
                    if (anss == correctAnswer[index]) {
                        int pointsEarned = basePoints;
                        if (timeTaken <= 5) {
                            pointsEarned += bonusPoints;
                            cout << "\nCORRECT! Well done! FAST BONUS!\n";
                            cout << "Points Earned: " << basePoints << " + " << bonusPoints << " = " << pointsEarned << "\n";
                        }
                        else {
                            cout << "\nCORRECT! Well done!\n";
                            cout << "Points Earned: " << pointsEarned << "\n";
                        }
                        totalPoints += pointsEarned;
                        
                        correctQ[rightcount] = questions[index];
                        correctA[rightcount] = optionA[index];
                        correctB[rightcount] = optionB[index];
                        correctC[rightcount] = optionC[index];
                        correctD[rightcount] = optionD[index];
                        correctCorrect[rightcount] = correctAnswer[index];
                        rightcount++;
                        
                        score++;
                    }
                    else {
                        cout << "\nWRONG! Correct answer was: " << correctAnswer[index] << "\n";
                        cout << "Penalty: -" << penaltyPoints << " points\n";
                        totalPoints -= penaltyPoints;
                        if (totalPoints < 0) totalPoints = 0;
                        
                        incorrectQ[wrongcount] = questions[index];
                        incorrectA[wrongcount] = optionA[index];
                        incorrectB[wrongcount] = optionB[index];
                        incorrectC[wrongcount] = optionC[index];
                        incorrectD[wrongcount] = optionD[index];
                        incorrectCorrect[wrongcount] = correctAnswer[index];
                        wrongcount++;
                    }
                    cout << "Current Total: " << totalPoints << " points\n";
                    Sleep(3000);
                    questionAnswered = true;
                }
                else {
                    cout << "\n[ERROR] Invalid input!\n";
                    Sleep(1500);
                }
            }
        }

        int maxPossiblePoints = totalAsked * (basePoints + bonusPoints);

        // Display Results
        system("cls");
        cout << "\n========================================\n";
        cout << " QUIZ COMPLETED!\n";
        cout << "========================================\n";
        cout << "Category: " << categoryName << "\n";
        cout << "Player Name: " << name << "\n";
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

        // High Score System - Using arrays instead of struct
        string highScoreNames[5];
        int highScorePoints[5];
        int highscorer = 0;
        
        // Read existing high scores
        ifstream inFile("highscore.txt");
        if (inFile) {
            while (highscorer < 5 && inFile >> highScoreNames[highscorer] >> highScorePoints[highscorer]) {
                highscorer++;
            }
            inFile.close();
        }

        // Check if current score qualifies for high score list
        bool isHighScore = false;
        int position = -1;

        if (highscorer < 5) {
            isHighScore = true;
            position = highscorer;
        }
        else {
            for (int i = 0; i < 5; i++) {
                if (totalPoints > highScorePoints[i]) {
                    isHighScore = true;
                    position = i;
                    break;
                }
            }
        }

        if (isHighScore) {
            cout << "\nCONGRATULATIONS! NEW HIGH SCORE!\n";
            cout << "You ranked #" << position + 1 << " in the leaderboard!\n";

            // Insert new high score at correct position
            for (int i = 4; i > position; i--) {
                if (i - 1 < highscorer) {
                    highScoreNames[i] = highScoreNames[i - 1];
                    highScorePoints[i] = highScorePoints[i - 1];
                }
            }
            highScoreNames[position] = name;
            highScorePoints[position] = totalPoints;
            if (highscorer < 5) highscorer++;

            // Write updated high scores to file
            ofstream outFile("highscore.txt");
            for (int i = 0; i < highscorer; i++) {
                outFile << highScoreNames[i] << " " << highScorePoints[i] << "\n";
            }
            outFile.close();
            cout << "Your score has been saved!\n";
        }

        // Display High Scores
        cout << "\n========================================\n";
        cout << " TOP 5 HIGH SCORES\n";
        cout << "========================================\n";
        for (int i = 0; i < highscorer; i++) {
            cout << i + 1 << ". " << highScoreNames[i] << " - " << highScorePoints[i] << " points\n";
        }
        cout << "========================================\n";

        // Lifelines summary
        cout << "\n--- Lifelines Used ---\n";
        cout << (usedReplace ? "[X]" : "[ ]") << " Replace Question\n";
        cout << (usedSkip ? "[X]" : "[ ]") << " Skip Without Penalty\n";
        cout << (used5050 ? "[X]" : "[ ]") << " 50-50\n";
        cout << (usedExtraTime ? "[X]" : "[ ]") << " Extra Time\n";
        cout << "----------------------\n";

        // Review wrong answers
        if (wrongcount > 0) {
            int choice;
            cout << "\nWould you like to review incorrect answers?\n";
            cout << "1. Yes\n2. No\n";
            cout << "Your choice: ";
            cin >> choice;

            if (choice == 1) {
                system("cls");
                cout << "\n========================================\n";
                cout << " INCORRECT ANSWERS REVIEW\n";
                cout << "========================================\n\n";

                for (int i = 0; i < wrongcount; i++) {
                    cout << "Question " << i + 1 << ": " << incorrectQ[i] << "\n\n";
                    cout << "1. " << incorrectA[i] << "\n";
                    cout << "2. " << incorrectB[i] << "\n";
                    cout << "3. " << incorrectC[i] << "\n";
                    cout << "4. " << incorrectD[i] << "\n\n";
                    cout << "Correct Answer: " << incorrectCorrect[i] << "\n";
                    cout << "----------------------------------------\n\n";
                }
                cout << "Press any key to continue...";
                _getch();
            }
        }

        int want;
        cout << "\nDo you want to save a review of your Quiz?\n";
        cout << "1. Yes\n2. No\n";
        cout << "Your choice: ";
        cin >> want;

        if (want == 1) {
            ofstream logFile("quizlog.txt", ios::app);
            if (logFile) {
                time_t now2 = time(0);
                string dt = ctime(&now2);

                logFile << "========================================\n";
                logFile << "Category: " << categoryName << "\n";
                logFile << "Player: " << name << "\n";
                logFile << "Date: " << dt;
                logFile << "Total Score: " << totalPoints << "\n";
                logFile << "Total Questions Asked: " << totalAsked << "\n";
                logFile << "\nCorrect Questions (" << rightcount << "):\n";
                for (int i = 0; i < rightcount; i++) {
                    logFile << "Q: " << correctQ[i] << "\n";
                    logFile << "1. " << correctA[i] << " 2. " << correctB[i] << " 3. " << correctC[i] << " 4. " << correctD[i] << "\n";
                    logFile << "Correct Answer: " << correctCorrect[i] << "\n\n";
                }

                logFile << "\nIncorrect Questions (" << wrongcount << "):\n";
                for (int i = 0; i < wrongcount; i++) {
                    logFile << "Q: " << incorrectQ[i] << "\n";
                    logFile << "1. " << incorrectA[i] << " 2. " << incorrectB[i] << " 3. " << incorrectC[i] << " 4. " << incorrectD[i] << "\n";
                    logFile << "Correct Answer: " << incorrectCorrect[i] << "\n\n";
                }
                logFile << "========================================\n\n";
                logFile.close();
                cout << "\nYour quiz has been logged in quizlog.txt\n";
            }
            else {
                cout << "\n[ERROR] Could not save quiz log!\n";
            }
        }

        int suggest;
        cout << "\nDo you want to suggest a question?\n";
        cout << "1. Yes\n2. No\n";
        cout << "Your choice: ";
        cin >> suggest;

        if (suggest == 1) {
            ofstream sugFile("suggestion.txt", ios::app);
            if (!sugFile) {
                cout << "\n[ERROR] Could not open suggestions file!\n";
            }
            else {
                cin.ignore();
                string question;
                cout << "\nEnter your question: ";
                getline(cin, question);

                time_t now3 = time(0);
                string dt2 = ctime(&now3);

                sugFile << "----------------------------------------\n";
                sugFile << "Category: " << categoryName << "\n";
                sugFile << "Submitted by: " << name << "\n";
                sugFile << "Date: " << dt2;
                sugFile << "Question: " << question << "\n";
                sugFile << "----------------------------------------\n\n";

                cout << "\nYour question has been saved successfully!\n";
                cout << "Thank you for your contribution!\n";
                sugFile.close();
            }
        }

        int visit;
        cout << "\nDo you want to visit the high scorers list?\n";
        cout << "1. Yes\n2. No\n";
        cout << "Your choice: ";
        cin >> visit;

        if (visit == 1) {
            system("cls");
            highscore(visit);
        }

        cout << "\n========================================\n";
        cout << " Thanks for playing!\n";
        cout << " Have a nice day!\n";
        cout << "========================================\n";
        cout << "\nPress any key to return to main menu...";
        _getch();
    }
    else if (n == 2) {
        system("cls");
        highscore(n);
        cout << "\nPress any key to continue...";
        _getch();
    }
    else if (n == 3) {
        cout << "Exiting...\n";
    }

    return 0;
}