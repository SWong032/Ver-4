/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: Sydney Wong
 *
 * Created on June 1, 2023, 8:59 PM
 * Purpose: Project 2 Ver 4-Blackjack
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function Prototypes
void exitGame(); //exit game
void selSort(vector<int>&); //selection sort
void bubSort(vector<int>&);
bool linSrch(const vector<int>&, int); //linear search
void Bets(int[][4], int); //betting feature
void Scores(const int[][4], const float); //scoring
void pTurn(int[][4], const char, const int); //player's turn
void dTurn(float&); //dealer's turn
void Winner(const int[][4], const float); //winner

// Function Overloading
void Bets(int playBet[][4], int limamt = 500); //player's bets & limited amount for bets

class BJgame{ //class for static variables
public:
    static const int nPlayer = 4; //number of players
    static const int bet = 500; //betting limit
};

    int main(int argc, char** argv) {
    // Initialize random seed
    srand(time(NULL));
    // Players' scoring
    int nPlayer = BJgame::nPlayer;
    int playScs[nPlayer][4] = {{0}}; // Using two-dimensional array for player scores
    float dealer = rand() % 10 + 12; // Dealer starts with random score between 12 and 21 (can't be 13 since it'll go over 21)

    // Draw two cards for each player
    playScs[0][0] += rand() % 10 + 2;
    playScs[1][0] += rand() % 10 + 2;
    playScs[2][0] += rand() % 10 + 2;
    playScs[3][0] += rand() % 10 + 2;
    string intro = "                                A Game of Blackjack";
    cout << intro << endl;

    // Print out instructions
    cout << endl;
    cout << "                                   -Instructions-        \n";
   
    cout << " ---------------------------------------------------------------------------------------- \n";
    cout << "|A simple multiplayer card game. An easy game of chance, just like rock, paper, scissors.|\n";
    cout << "|The goal of Blackjack is to beat the dealer or get close to 21. First step is to place  |\n";
    cout << "|in your bets. Players either choose hit or stand. If you choose hit, another card will  |\n";
    cout << "|be added to your deck to add to your card value. If you choose stand, you keep your card|\n";
    cout << "|value. Each player's card value will total up which will determine whether you win or   |\n";
    cout << "|lose. For example, your first card is a 10 and you choose to hit. The second card is 9  |\n";
    cout << "|which totals to 19, if the dealer's hand is 20, the player can hit or stand until the   |\n";
    cout << "|dealer reveals their hand. If the player's hand is closer to 21, you win. You lose if   |\n";
    cout << "|your hand went over 21 or under since your goal is to beat other players and the dealer.|\n";
    cout << "|                                  Best of luck!                                         |\n";
    cout << " ---------------------------------------------------------------------------------------- \n";
    cout << endl << endl;

    //Easy to read instructions
    cout << "***If you didn't bother reading the instructions, here's how it works.***\n";
    cout << "1. Win? You want to score under 21 and not over to beat the dealer.\n";
    cout << "2. How? The cards given to you are your score and it either adds or doesn't.\n";
    cout << "3. Add to your score? Choose hit.\n";
    cout << "4. Don't want to add to your score?  Choose stand.\n";
    cout << "5. Score = close to 21 & dealer & other players' hand is lower than yours. Win.\n";
    cout << "6. Score = lower than dealer & other player's hand. Lose.\n";
    cout << "7. Strategize because you placed bets, or not and just wing it.\n";
    cout << endl << endl;
    
    //Table to show player(s) the betting options
    cout << "              ---------------------------------------------------------- \n";
    cout << "             |                         {BETS}                           |\n"; 
    cout << "             |Yes. You can bet fake money with imaginary chips because  |\n"; 
    cout << "             |this is a legal family-friendly game so no one will go    |\n"; 
    cout << "             |into debt nor will someone come for you for money. Unless |\n"; 
    cout << "             |you owe real money in the real world aka outside this     |\n"; 
    cout << "             |computer screen. Players of this game can bet in the range|\n"; 
    cout << "             |from $1 to $500. Because this game is still in development|\n"; 
    cout << "             |players will only need to insert the amount they desire   |\n"; 
    cout << "             |before playing. Then after the game, it will determine    |\n"; 
    cout << "             |whether or not you or other players will keep or lose     |\n"; 
    cout << "             |their bets depending on the result.                       |\n";
    cout << "              ---------------------------------------------------------- \n";
    cout << endl;
    //key visuals-cards
    cout << "          --------------              -------------- \n";
    cout << "         |   _______    |            |         _    |\n";
    cout << "         |  |       |   |            |  |    -      |\n";
    cout << "         |  |       |   |            |  |  -        |\n";
    cout << "         |  |_______|   |            |  |_-         |\n";
    cout << "         |  |       |   |            |  |  -        |\n";
    cout << "         |  |       |   |            |  |    -      |\n";
    cout << "         |  |       |   |            |  |      -_   |\n";
    cout << "          --------------              -------------- \n";
    cout << endl;
    cout << "                        --------------              -------------- \n";
    cout << "                       |   _______    |            |   ________   |\n";
    cout << "                       |  |       |   |            |       |      |\n";
    cout << "                       |  |       |   |            |       |      |\n";
    cout << "                       |  |       |   |            |       |      |\n";
    cout << "                       |  |      _|   |            |       |      |\n";
    cout << "                       |  |_______|-_ |            |       |      |\n";
    cout << "                       |              |            |   ____|      |\n";
    cout << "                        --------------              -------------- \n";
    //spacing
    cout << endl << endl;
    cout << "                                       *Notice* \n"; //Note for development
    cout << "     [PLEASE BE AWARE THIS GAME IS IN DEVELOPMENT SO BUGS AND ERRORS MIGHT APPEAR.] \n";
    cout << endl;
    cout << "===============================================================================================\n";
    bool playing = true; //game starts

    ifstream inFile; 
    ofstream outFile;
    do {
        //files input-output try out
        if (outFile.is_open()) {
        outFile << "Play Fair" << endl;
        } else {
        cout << "-Watch the dealer's hand" << endl;
    }
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
    }else {
        cout << "-Pay Up" << endl;
    }
        Scores(playScs, dealer);

        // Players place bets
        int playBet[nPlayer][4] = {{0}}; //2 dimensional array for player bets
        Bets(playBet);

        // Player 1's turn
        pTurn(playScs, '1', 0);

        // Player 2's turn
        pTurn(playScs, '2', 1);
        
        // Player 3's turn
        pTurn(playScs, '3', 2);
        
        // Player 4's turn
        pTurn(playScs, '4', 3);

        // Dealer's turn
        dTurn(dealer);

        // Determine the winner
        Winner(playScs, dealer);

        // Exit the game
        exitGame();

        playing = false; //game ends

    } while (playing);
    inFile.close(); //close files
    outFile.close();
    return 0;
}

//function prototypes
// Function to place bets 
void Bets(int playBet[][4], int limamt) { //player's bet, limit amount to bet
    cout << "Player 1, place your bet $: ";
    cin >> playBet[0][0];

    cout << "Player 2, place your bet $: ";
    cin >> playBet[1][0];

    cout << "Player 3, place your bet $: ";
    cin >> playBet[2][0];
    
    cout << "Player 4, place your bet $: ";
    cin >> playBet[3][0];
    
    // Default bet amount if invalid input
    if (playBet[0][0] <= 0)
        playBet[0][0] = limamt;
    if (playBet[1][0] <= 0)
        playBet[1][0] = limamt;
    if (playBet[2][0] <= 0)
        playBet[2][0] = limamt;
    if (playBet[3][0] <= 0)
        playBet[3][0] = limamt;
}

// Function to display scores
void Scores(const int playScs[][4], const float dealerS){ //player's scores, dealer's score
    cout << endl;
    cout << "~SCOREBOARD~" << endl;
    cout << "Player 1 score: " << playScs[0][0] << endl;
    cout << "Player 2 score: " << playScs[1][0] << endl;
    cout << "Player 3 score: " << playScs[2][0] << endl;
    cout << "Player 4 score: " << playScs[3][0] << endl;
    cout << "Dealer score: " << dealerS << endl;
    cout << endl;
}

// Function for each player's turn
void pTurn(int playScs[][4], const char playNum, const int index){ //player's scores, player number, index to update scores
    cout << "Player " << playNum << ", would you like to hit or stand? (Press h or s)" << endl;
    char choice;
    cin >> choice;
//player's choices
    if (choice == 'h') {
        playScs[index][0] += static_cast<int>(rand() % 10 + 2);
        if (playScs[index][0] > 21) {
            cout << "Player " << playNum << " busts! Better luck next time!" << endl;
        }
    }
    else if (choice == 's') {
        cout << "Player " << playNum << " stands." << endl;
    }

    Scores(playScs, 0); // Update the scoreboard after each turn
}


// Function for dealer's turn
void dTurn(float& dealerS) { //dealer's turn, dealer's score
    cout << "Dealer's turn:" << endl;
    while (dealerS < 17) {
        dealerS += static_cast<int>(rand() % 10 + 2);
        cout << "Dealer's score: " << dealerS << endl;
    }
    cout << "Dealer stands." << endl;
}


// Function to determine the winner
void Winner(const int playScs[][4], const float dealerS) { //player's scores, dealer's score
    if (dealerS > 21) {
        cout << "Dealer busts! All players win!" << endl;
    }
    else if (dealerS >= 17 && dealerS <= 21) { //if dealer scores between 17 to 21
        bool p1 = playScs[0][0] <= 21 && playScs[0][0] > dealerS;
        bool p2 = playScs[1][0] <= 21 && playScs[1][0] > dealerS;
        bool p3 = playScs[2][0] <= 21 && playScs[2][0] > dealerS;
        bool p4 = playScs[3][0] <= 21 && playScs[3][0] > dealerS;
        //results
        if (!p1 && !p2 && !p3 && !p4) {
            cout << "Dealer beats everyone! All bets goes to the Dealer!" << endl;
        }
        else {
            if (p1) {
                cout << "Player 1 beats the dealer! Congrats on beating everyone else!" << endl;
            }
            if (p2) {
                cout << "Player 2 beats the dealer! Congrats on beating everyone else!" << endl;
            }
            if (p3) {
                cout << "Player 3 beats the dealer! Congrats on beating everyone else!" << endl;
            }
            if (p4) {
                cout << "Player 4 beats the dealer! Congrats on beating everyone else!" << endl;
            }
        }
    }
    else {
        cout << "All players bust! Dealer wins!" << endl;
    }
}

// Selection sort
void selSort(vector<int>& arr) { //used to sort players' and dealer's scores 
    
    for (size_t i = 0; i < arr.size() - 1; i++) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}
void bubSort(vector<int>& arr) { //compares players and dealer's hand
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
// Linear search to search for players scores and compare them to each other
bool linSrch(const vector<int>& arr, int target) {
    return find(arr.begin(), arr.end(), target) != arr.end();
}

// Exit the game if requested
void exitGame() {
    cout << endl;
    cout << "Do you want to exit the game? (y/n)" << endl;
    char choice;
    cin >> choice;

    if (choice == 'y' || choice == 'Y') { //if user choose to exit
        cout << "You have exited the game." << endl;
        exit(0);
    }
    if (choice == 'n' || choice == 'N'){ //if user choose to not exit
        cout << "You chose the wrong option. Leave." << endl;
        exit(0);
    }
}
    