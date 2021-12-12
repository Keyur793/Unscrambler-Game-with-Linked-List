/* program_5.cpp
    Unscrambler
    Author: Keyur Patel
    Date: 11/8/2021
    Class: CS 141, Fall 2021, UIC
    System: Visual Studio Code

*/
#include <iostream>   // For Input and Output
#include <iomanip>
#include <fstream>    // For file input and output
#include <cassert>    // For the assert statement
#include <cctype>     // access to tolower() or toupper() function
#include <vector>     // For vectors
#include <string>     // String operations
#include <algorithm>  // use of vector algorithms
#include <cmath>
#include <stddef.h>

using namespace std;

struct node{
    string nextcurrentBoardWords;
    vector<char> nextboardArray;
    node *next;
};


class Board{
    private:
        static vector<string> dictionaryWords; // stores all the dictionary words

    public:
        node *head, *tail;

        int boardSize;// stores the board size that the user inputs
        
        string wordsSelected;// stores the string of the words selected for the board
        string wordsSelectedWithCommas;//stores the string of the words selected for the board but seperated by commas
        string currentBoardWords;// stores the current baord as a string

        vector<char> boardArray;//stores the board in this array    
        vector<char> completedboardArray;// stores the completed board in this array
        vector<char> resetBoardArray;// stores the reset board
        
        void settoNull();
        static void readWordsIntoDictionary();// reads words into the dictionaryWords array
        void printBoard(vector<char> board);//prints the board
        void getRandomWords();//get random words for the board
        void resetBoard();// resets the board to the original 
        int checkWin();// checks for win
        void setResetArray(vector<char> board);// sets the reset arrsay
        void setBoardSize(int sizeInput);// sets the boardSize variable
        void rotateRow(int rowSelected, int numRotates);// function to rotate rows with the row selected and how many times to rotate
        void rotateCol(int colSelected, int numRotates);// function to rotate cols with the col selected and how many times to rotate   
        void createnewNode();
        int getdictionarySize();// function to return the dictionary size
        void displayeachNode();
        void setheadanddtailtoNull();
        int getlinkedlistSize();
        void deletelastNode();
        void deletelinkedList();
        
};
vector <string> Board::dictionaryWords;

void Board::setheadanddtailtoNull(){
    head=NULL;
    tail=NULL;
}

void Board::createnewNode(){
    
    node *temp = new node;
    temp->nextcurrentBoardWords = currentBoardWords;
    temp->nextboardArray = boardArray;
    temp->next = head;
    head = temp;
}


void Board::displayeachNode(){
    int count=0;
    
    node *temp=new node;
    temp=head;
    while(temp!=NULL){
      temp=temp->next;
      count++;
    }
    temp=head;
    cout << "   List is: " ;
    while(temp!=NULL){
        cout<<count << ":"<<temp->nextcurrentBoardWords;
        count--;
        if(count!=0){
            cout <<"-> ";
        }
        temp=temp->next;
    }
    cout << endl <<  endl;
} 

int Board::getlinkedlistSize(){
    int count=0;
    node *temp=new node;
    temp=head;
    while(temp!=NULL){
        temp=temp->next;
        count++;
    }
    return count;
}
void Board::deletelastNode(){
    node *toDelete;
    toDelete = head;

    head = head->next;
    boardArray = head->nextboardArray;
    currentBoardWords = head->nextcurrentBoardWords;
    free(toDelete);


}
void Board::deletelinkedList(){
    node *temp = head;
    while (temp != 0){
        head = temp->next;
        delete temp;
        temp = head;
    }
    delete head;
}


void Board::setBoardSize(int sizeInput){//sets the board size variable equal to the user input for board size
    boardSize=sizeInput;
}


void Board::setResetArray(vector<char> board){// sets the resetBoard array to the original scrambled array
    for(int i=0;i<board.size();i++){
        resetBoardArray.push_back(board.at(i));
    }
}


int Board::getdictionarySize(){//gets the size of dictionary
    return dictionaryWords.size();
}


int Board::checkWin(){//check for win by comparing the current board to the completed board
    for(int i=0;i<boardArray.size();i++){
        if(boardArray.at(i)!=completedboardArray.at(i)){
            return 0;
        }
    }
    return 1;
}


void Board::resetBoard(){//resets the board by setting the board equal to reset board array and resets the current board string 
    currentBoardWords="";
    for(int i=0;i<boardSize*boardSize;i++){
        boardArray.at(i) = resetBoardArray.at(i);
        currentBoardWords = currentBoardWords + boardArray.at(i);
    }
}


void Board::rotateRow(int rowSelected, int numRotates){//rotates a random row or a row that the user selected numRotate times
    string rowLetters;//stores the letters of the row selected
    currentBoardWords="";//sets the currentBoard string to empty

    for(int i=0;i<boardSize;i++){//gets the letters from the row slected and stores it into rowLetters
        rowLetters=rowLetters+boardArray.at(i+(rowSelected*boardSize));
    }
    if(numRotates>=1){//rotates forwards if the number of rotates if greater than 1
        for(int i=0;i<numRotates;i++){//rotates numRotates times
            rowLetters = rowLetters.substr(rowLetters.length()-1,1)+ rowLetters.substr(0,rowLetters.length()-1);//puts the last char in the string to the beginning
        }
    }
    else if(numRotates<=-1){//rotates backwards if the number of rotates if greater than 1
        for(int i=0;(i<numRotates*-1);i++){//rotates numRotates times
            rowLetters = rowLetters.substr(1,rowLetters.length()-1) + rowLetters.substr(0,1);//puts the first character in the string to the end of the string
        }
    }
    for(int i=0;i<boardSize;i++){//puts the rowLetters back into the row selected
        boardArray.at(i+(rowSelected*boardSize)) = rowLetters.at(i);
    }
    for(int i=0;i<boardSize*boardSize;i++){//sets the new currentBoardWords string
        currentBoardWords = currentBoardWords + boardArray.at(i);
    }
}


void Board::rotateCol(int colSelected , int numRotates){//rotates a random col or a col that the user selected numRotate times
    string colLetters;//stores the letters of the col selected
    int colCount=0;//counts the row that the loop is on so that it can get the letters vertically
    currentBoardWords="";//sets the currentBoard string to empty
    for(int i=0;i<boardSize;i++){//gets the letters from the row slected and stores it into rowLetters
        colLetters = colLetters +boardArray.at(colSelected+colCount);
        colCount=colCount+boardSize;//adds the boardSize so that it goes to the next row
    }
    if(numRotates>=1){//rotates forwards if the number of rotates if greater than 1
        for(int i=0;i<numRotates;i++){//rotates numRotates times
            colLetters = colLetters.substr(colLetters.length()-1,1)+ colLetters.substr(0,colLetters.length()-1);//puts the last char in the string to the beginning
        }
    }
    else if(numRotates<=-1){//rotates backwards if the number of rotates if greater than 1
        for(int i=0;(i<numRotates*-1);i++){//rotates numRotates times
            colLetters = colLetters.substr(1,colLetters.length()-1) + colLetters.substr(0,1);//puts the first character in the string to the end of the string
        }
    }
    colCount=0;
    for(int i=0;i<boardSize;i++){//puts the colLetters back into the col selected
        boardArray.at(colSelected+colCount) = colLetters.at(i);
        colCount=colCount+boardSize;//adds the boardSize so that it goes to the next row
    }
    for(int i=0;i<boardSize*boardSize;i++){//sets the new currentBoardWords string
        currentBoardWords = currentBoardWords + boardArray.at(i);
    }
}


void Board::getRandomWords(){//gets random words to fill up the board
    int spaceLeft=boardSize*boardSize;//spaces counts the number of empty spaces left on the board
    int rnum=0;//random number to get a random words
    wordsSelected="";//string of the words selected
    wordsSelectedWithCommas="";//string of words selected seperated by commas

    boardArray.clear(); completedboardArray.clear();resetBoardArray.clear();//clears the board

    while(spaceLeft>2){//iterates while spaces left is less then 2 because there is no word that fits 2 spaces left
        rnum = rand()%(dictionaryWords.size());//gets a random number
        int temp = (boardSize*boardSize)-wordsSelected.length()-dictionaryWords.at(rnum).length();//stores the spaces left before adding the word to the wordsSelcted string
        while(temp<0){//if there is no space for the word then keep getting a different word until it fits
            rnum = rand()%(dictionaryWords.size());
            temp = (boardSize*boardSize)-wordsSelected.length()-dictionaryWords.at(rnum).length();
        }
       
        wordsSelected=wordsSelected+dictionaryWords.at(rnum)+" ";//adds the word selected to the wordsSelected string
        wordsSelectedWithCommas = wordsSelectedWithCommas + dictionaryWords.at(rnum)+ ", ";//adds the word selected to the comma seperated string

        spaceLeft = (boardSize*boardSize)-wordsSelected.size();//sets the spaces left which is Total Board Size minus the length of the wordsSelected with spaces
    }
    
    wordsSelected.pop_back();//removes the last space that is not needed  
    wordsSelectedWithCommas.pop_back();//removes the last space that is not needed
    wordsSelectedWithCommas.pop_back();//removes the last comma that is not needed

    while(wordsSelected.size()<(boardSize*boardSize)){//fills the open spaces left with empty spaces
        wordsSelected=wordsSelected + " ";
    }
    for(int i=0;i<wordsSelected.size();i++){//puts the words Selcted string into the completed board array and the current board array
        boardArray.push_back(wordsSelected.at(i));
        completedboardArray.push_back(wordsSelected.at(i));
    }
}

void Board::readWordsIntoDictionary(){
   // Read in dictionary into dictionary vector
    ifstream inStream;                      // Declare an input stream for reading
    inStream.open( "commonWords.txt");       // Open dictionary file
    assert( inStream.fail() == false );     // Ensure file open worked
    
    // If you had previously used vector dictionary, then you might want to clear it
    // before continuing to use it, though that is not the case here.
    dictionaryWords.clear();
    
    // Keep repeating while input from the file yields a word
    string newWord;                         // Store a single input word
    while( inStream >> newWord) {           // While there is another word to be read
        // Add this new word to the end of the vector, growing it in the process
        dictionaryWords.push_back( newWord);
    }
    // Close the dictionary file
    inStream.close();
}


void Board::printBoard(vector<char> board){//print the board that was selected to display

    cout << endl
         << "    " << setfill(' ');
    for( int i=0; i<boardSize; i++) {
        cout << setw( 4) << (char)('A'+i);
    }
    // Display the heading above the solved board on the right
    cout << "         Goal Board";
    for( int row=0; row<boardSize; row++) {
        // Display a separator row of dash characters, like: "--------------"
		cout << "  \n      " << setw(boardSize*4+3) << setfill('-') << "   ";
        // Display a second row of dashes for the right-hand goal board
  		cout << "  " << setw(boardSize*4+3) << setfill('-') << "\n   ";
        
        // Display the row number
        cout << row << "";
        
        // Display the working board values on the left
		for(int col=0; col<boardSize; col++) {
			int index = row*boardSize + col; // compute the index into the 1D board vector
			cout << " | " << boardArray.at(index);
		}
		cout << " |   ";      // Last '|' at the end of each line.
  
        // Display the solved board values to the right
		for(int col=0; col<boardSize; col++) {
			int index = row*boardSize + col; // compute the index into the 1D board vector
			cout << " | " << completedboardArray.at(index);
		}
		cout << " | ";      // Last '|' at the end of each line.
	}
    cout << "\n      " << setw(boardSize*4) << setfill('-') << "";
    // Display the bottom line on the Goal board to the right
	cout << "     " << setw(boardSize*4) << setfill('-') << "\n";
    cout << "   Board string: " << currentBoardWords << endl;
    cout << "    Goal string: " << wordsSelected << endl;
    
}


void printMoveMenuOptions(int boardSize){//prints the menu options for rotating rows and cols//board size as parameter to display the domain of the user inputs 
    cout << "   Enter the row/column you would like to rotate, and the number of positions to rotate by." <<  endl;
    cout << "   This should be in the format of <R or C> <row/column number> <number of positions to rotate>," <<  endl;
    cout << "   where valid row and column numbers are between 0 and " << boardSize-1 << ","  <<endl;
    cout << "   E.g. R 0 1 would rotate the top row (row 0) of the board to the right once," <<  endl;
    cout << "        c 1 -2 would rotate the second column (col 1) of the board upwards twice." <<  endl;
    cout << "   Your choice: ";
}


void printBoardFunctions(vector <Board>& letterBoard){//displays the current board, current words, and words to spell
    letterBoard.at(0).printBoard(letterBoard.at(0).boardArray);//calls the print board function in the Board class
    if(letterBoard.at(0).checkWin()==0){
        letterBoard.at(0).displayeachNode();
    }
   
    //cout << "Current board words: " << letterBoard.at(0).currentBoardWords << endl;//prints the current words
}


void menuOptionR(vector <Board>& letterBoard){//handles the Rotating menu options. with object as a parameter
    char userInputRowOrCol;//stores the input of row or col option selected
    char roworcolSelected;//stores the input if the number row or col selected
    int numRotates;//stores the input of the number of rotates selected
    cout << endl;
   //printMoveMenuOptions(letterBoard.at(0).boardSize);//calls printMoveMenuOptions function to print the rotating menu options
    cout << "   Enter the row/column to rotate, and # of (+/-) rotations:";
    cin >> roworcolSelected;//takes in user input for number row or col
    roworcolSelected=toupper(roworcolSelected);
    cin>> numRotates;//takes in user input for the number of rotates
    while(numRotates>letterBoard.at(0).boardSize-1||numRotates<-(letterBoard.at(0).boardSize-1)){
        cout << "   *** Shift value should be between -3 and 3. Retry." << endl;
        cout << "   Enter the row/column to rotate, and # of (+/-) rotations: " ;
        cin >> roworcolSelected;//takes in user input for number row or col
        roworcolSelected=toupper(roworcolSelected);
        cin >> numRotates;
        cout << endl;
    }
    for(int i=0;i<letterBoard.at(0).boardSize;i++){
        char temp='0'+i;
        if(roworcolSelected=='A'+i){
            letterBoard.at(0).rotateCol(roworcolSelected-'A',numRotates);
        }
        else if(roworcolSelected==temp){
            letterBoard.at(0).rotateRow(i,numRotates);
        }
    }
    // while(roworcolSelected!='A'&&roworcolSelected!='B'&&roworcolSelected!='C'&&roworcolSelected!='D'){//keeps asking for a row or col number if the number is not valid
    //    // cout <<"    Number must be between 0 and " <<letterBoard.at(0).boardSize-1  << ". Try again." <<  endl <<  endl;
    //     printMoveMenuOptions(letterBoard.at(0).boardSize);
    //     cin  >> roworcolSelected>>numRotates;
    // }

    // if(userInputRowOrCol=='R'){//if R is selected then run the rotateRow functon with the row or col selected and num rotates as parameter
    //     letterBoard.at(0).rotateRow(roworcolSelected-'A',numRotates);
    // }
    // else if(userInputRowOrCol=='C'){//if C is selected then run the rotateCol functon with the row or col selected and num rotates as parameter
    //     letterBoard.at(0).rotateCol(roworcolSelected-'A',numRotates);
    // }
    

    letterBoard.at(0).printBoard(letterBoard.at(0).boardArray);//prints the board
    letterBoard.at(0).createnewNode();
    if(letterBoard.at(0).checkWin()==0){
        letterBoard.at(0).displayeachNode();
    }



    //cout << "Current board words: " <<letterBoard.at(0).currentBoardWords<< endl;//prints the current words of the board
}


void changeBoarrdOptions(vector <Board>& letterBoard,int scrambleNumTimesInput){//handles all the main board menu options with the letterBoardd object and num scrambles as a parameter 
    char userMenuOptionInput;
    
    while(true){
        cout << "Enter one of the following:" << endl;
        cout << "   R Rotate a row or column " <<  endl;
        cout << "   G Generate a new board with new random words " <<  endl;
        cout << "   U Undo most recent move " <<  endl;
        cout << "   Q to quit." <<  endl;
        cout << letterBoard.at(0).getlinkedlistSize()<<". Your choice: ";

        cin >> userMenuOptionInput;
        cout << endl;

        userMenuOptionInput = toupper(userMenuOptionInput);//sets the user input to uppercase

        if(userMenuOptionInput=='R'){//if R is selcted them call the R menu option function wwith sending the Board object as parameter
            menuOptionR(letterBoard);
        }
        else if(userMenuOptionInput=='G'){//if G is selcted then get a new board and scramble it
            int size;
            int numShuffles;
            cout << "Choose board size. It must be a single digit >=4: ";
            cin >> size;
            letterBoard.at(0).setBoardSize(size);
            cout << "   Choose single-digit number of times to scramble board: ";
            cin >> numShuffles;
            letterBoard.at(0).getRandomWords();//gets new words and fill the board
            for(int i=0;i<numShuffles;i++){//scrambles the board from the same input from the first scamble input
                int randRow =  rand()%letterBoard.at(0).boardSize;  //gets random roww
                int randColm = rand()%letterBoard.at(0).boardSize;  //gets random col
                letterBoard.at(0).rotateRow(randRow,1);//rotates the random row selected by 1
                letterBoard.at(0).rotateCol(randColm,1);//rotates the random col selected by 1
            }
            letterBoard.at(0).deletelinkedList();
            letterBoard.at(0).createnewNode();

            printBoardFunctions(letterBoard);//prints the board

        }
        else if(userMenuOptionInput=='Q'){// if Q is slected then break out of the loop and exit the program
            cout << " Thank you for playing! " <<  endl;
            cout << "Exiting program... ";
            break;
        }
        else if (userMenuOptionInput=='U'){
            if(letterBoard.at(0).getlinkedlistSize()==1){
                cout <<"   *** You cannot undo past the beginning of the game.  Retry. ***" << endl;
                printBoardFunctions(letterBoard);//prints the board
            }
            else{
                letterBoard.at(0).deletelastNode();
                cout << "   * Undoing move * " <<  endl;
                printBoardFunctions(letterBoard);//prints the board


            }
        }
        if(letterBoard.at(0).checkWin()==1){//if the checkWin function return 1 then display the win statments, break out the loop, and exit the program
            cout << "Congratulations, you won!" <<  endl;
            cout << "Exiting program...";
            break;
        }
    }
}


void beginGameOptions(vector <Board>& letterBoard){//handles the beginning game options
    int boardSizeInput=0;//stores the board size that the user selected >=4
    int scrambleNumTimesInput = 0; // stores the input for num scrambles >=1
    cout << "   Choose board size. It must be a single digit >=4:";
    cin >> boardSizeInput ;//takes in input for board size
    while(boardSizeInput<4){//keeps asking for a boardSize if the input is not valid
        cout << "The board size must be at least 4. Retry." <<  endl;
        cout << "   Choose board size. It must be a single digit >=4:";
        cin >> boardSizeInput ;
        cout <<  endl;
    }

    letterBoard.at(0).setBoardSize(boardSizeInput); //sets the boardSize var in the Board class
    letterBoard.at(0).getRandomWords(); //gets random words and fill up the board

    cout << "   Choose single-digit number of times to scramble board:";
    cin >> scrambleNumTimesInput ;//takes in input for num scrambles

    while(scrambleNumTimesInput<1){//keeps asking for num scrambles if the input is not valid
        cout << "The number of times you select must be at least 1. Retry." <<  endl;
        cout << "   Choose single-digit number of times to scramble board:";
        cin >> scrambleNumTimesInput ;
        cout <<  endl;
    }

    for(int i=0;i<scrambleNumTimesInput;i++){//scrambles the number of times the user has selcted
        int randRow =  rand()%letterBoard.at(0).boardSize;  //gets random row
        int randColm = rand()%letterBoard.at(0).boardSize;  // gets random col
        letterBoard.at(0).rotateRow(randRow,1); // calls the rotate row function to rotates the random row by 1
        letterBoard.at(0).rotateCol(randColm,1); // calls the rotate col functiont to rotate the rando col by 1
    }
    letterBoard.at(0).setheadanddtailtoNull();
    letterBoard.at(0).createnewNode();
    letterBoard.at(0).printBoard(letterBoard.at(0).boardArray);//calls the print board function in the Class to print board
    letterBoard.at(0).displayeachNode();
    letterBoard.at(0).setResetArray(letterBoard.at(0).boardArray);//sets the resetArray in the class
    //cout << "Current board words: " << letterBoard.at(0).currentBoardWords << endl <<  endl;//displays the current board lettersd
    changeBoarrdOptions(letterBoard,scrambleNumTimesInput);//calls menu options to select the main board menu options
}


int main(){
    vector <Board> letterBoard;//vector of objects
    Board B1;//creates object B1
    letterBoard.push_back(B1);//appends object B1 into the objects vecter
    letterBoard.at(0).readWordsIntoDictionary();//calls the read words function to read all the dictionary words from txt file

    cout << "Program 6: Unscrambler Undo" <<  endl << "CS 141, Fall 2021, UIC" <<  endl <<  endl;
    cout << "You will be presented with a board that is filled with scrambled words." << endl;
    cout <<  "Rotate the rows and columns to get the words displayed in the right order. "  <<  endl;
    cout << "Press 'U' to undo moves." <<  endl <<  endl;
    cout << letterBoard.at(0).getdictionarySize() << " words have been read in from the dictionary." <<  endl;//displays the size of the dictionary array in the board class


    beginGameOptions(letterBoard);
    
    return 0;
}