#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

// Tausif Hussan - This code will calculate a bowling leagues average bowling scores from a txt file using 3 arrays. This will calculate average scores from 5 attempts

using namespace std;

#define MAX_PLAYERS 10 
//constant for the player array
#define MAX_SCORES 5 
//constant for the score array

//Read the file and retun the player names, scores, count of the player and count of the scores. First the getline function
//is used to get the line from the file and after it I make the string line to stream. After this again the getline
//function is used to read the data. The score number and player count is used to track the number
//of player inside the array and number of scores for each player
bool GetBowlingData(string filename, string* playerNames, int playerScores[][MAX_SCORES], int* playerCount, int* scoreCount) {
	ifstream stream;
	string line;
	*scoreCount = 0; //setting the score count to zero
	*playerCount = 0; //setting the player count zero

	stream.open(filename, ios::in); //opening the file

	if (!stream.good()) { //if can not open the file
		return false;
	}

	while (getline(stream, line)) { //read the lines from the file
		stringstream sstream(line); //convert the line to the stream 
		string data;
		while (getline(sstream, data, ' ')) { //read the data until the space arrived
			playerNames[*playerCount] = data; //first one is the player name
			*scoreCount = 0; //reset the score count
			while (getline(sstream, data, ' ')) { //read the second data until all data is finished, it is the score that current player have
				playerScores[*playerCount][*scoreCount] = stoi(data); //convert the score to int from string and add to the array with specific player and specific score position
				(* scoreCount)++; //increase the score count, so we can track the number of score for the players

			}

			(* playerCount)++; //increase the player count, so we can track the players
		}
		
	}

	return true; //return true if all is well
}

//calculates the average scores from the player score array and store it in the average score array. The 2D array of
//players score is passed along with the average array. The player count and score count is also passed so we can know
//how much players are in the array and what are the score counts. After this for each player the score is summed up and 
//divided by the score count to get the average for each player and then it is stored to the average array. The average array
//has same index 'i' for the perticular ith player.
void GetAverageScore(int playerScores[][MAX_SCORES], float averageScores[], int playerCount, int scoreCount) {
	int avg = 0;
	for (int i = 0; i < playerCount; i++) { //loop over all the players
		avg = 0; //reset the average for next player
		for (int j = 0; j < scoreCount; j++) { //loop over all the scores of player 'i'
			avg += playerScores[i][j]; //add the score to calculate the sum
		}

		averageScores[i] = avg /(float) scoreCount; //calculate average for player 'i'
	}
}

//simply print the player name and average score by visiting each player and average data.
void PrettyPrintResults(string playerNames[], float averageScores[], int playerCount) {
	cout << "********Average Player Scores********" << endl;
  cout << "\n";

	for (int i = 0; i < playerCount; i++) { //loop over the players 
		cout << "Player Name: " << playerNames[i] << " Average Score: " << averageScores[i]<<endl; //display the average and name of player 'i'
	}
}

int main() {
	//arrays to store the data
	string playerNames[MAX_PLAYERS];
	int playerScores[MAX_PLAYERS][MAX_SCORES];
	int playerCount = 0;
	int scoreCount = 0;
	float averageScores[MAX_PLAYERS];

	//calling the functions
	bool result = GetBowlingData("BowlingScores.txt", playerNames, playerScores, &playerCount, &scoreCount);
	GetAverageScore(playerScores, averageScores, playerCount, scoreCount);
	PrettyPrintResults(playerNames, averageScores, playerCount);
	
	return 0;
}