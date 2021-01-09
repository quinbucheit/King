/**
* Prompts the user for the dimensions of a chessboard and then uses dynamic programming
* to output the number of paths that the king can take from the first file of a chessboard
* to the last.
*
* Three facts to know about chess:
*
*   1. the columns of a chessboard are called files
*   2. the rows of a chessboard are called ranks
*   3. a king can move one square in any direction
*
* Execution snapshots:
*
*     Enter chessboard dimensions: 4 7
*   Paths from first to last file: 1220
*
*     Enter chessboard dimensions: 8 8
*   Paths from first to last file: 11814
*
*     Enter chessboard dimensions: 10 15
*   Paths from first to last file: 28781908
*
*     Enter chessboard dimensions: 20 20
*   Paths from first to last file: 17698806798
*
* Author: Quintin Bucheit
*/
#include <iostream>
#include <vector>

using namespace std;

unsigned long long num_paths = 0;

void paths(int, int);
bool valid(int, int, int, int);

int main() {
    int ranks; // rows on a chessboard
    int files; // columns on a chessboard

    cout << "  Enter chessboard dimensions: ";
    cin >> ranks >> files;

    paths(ranks, files);

    cout << "Paths from first to last file: " << num_paths << endl;
    return 0;
}

/*
* Uses dynamic programming to output the number of paths that the king can take from the 
* first file to the last on a chessboard. 
*/
void paths(int ranks, int files) {
    if (files <= 1) {
        num_paths += ranks;
        return;
    }

    /*
    * Fills each square of the first file of the chessboard with 1. The rest are filled
    * with 0s.
    */
    vector<vector<unsigned long long>> chessboard(ranks, vector<unsigned long long>(files));
    for (int r = 0; r < ranks; r++) {
        for (int f = 0; f < files; f++) {
            if (f == 0)
                chessboard[r][f] = 1;
            else
                chessboard[r][f] = 0;
        }
    }

    /*
    * Fills each square of the rest of the files of the chessboard with the number of
    * possible paths to that square.
    */
    for (int f = 1; f < files; f++) {
        for (int r = 0; r < ranks; r++) {
            chessboard[r][f] += chessboard[r][f - 1];
            if (valid(ranks, files, r - 1, f - 1)) {
                chessboard[r][f] += chessboard[r - 1][f - 1];
            }
            if (valid(ranks, files, r + 1, f - 1)) {
                chessboard[r][f] += chessboard[r + 1][f - 1];
            }
        }
    }

    /*
    * Adds up the numbers in the squares of the last file of the chessboard to get the
    * total number of possible paths.
    */
    for (int r = 0; r < ranks; r++) {
        num_paths += chessboard[r][files - 1];
    }
}

/*
* Returns true if specified location on the chessboard is valid. Assumes zero-based
* indexing.
*/
bool valid(int ranks, int files, int r, int f) {
    return r >= 0 && f >= 0 && r < ranks&& f < files;
}
