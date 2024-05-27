#include <iostream>
#include <vector>
#define SIZE 7
using namespace std;

typedef vector<string> BOARD;

BOARD ordered_board = {"XXOOOXX", "XXOOOXX", "OOOOOOO", "OOONOOO", "OOOOOOO", "XXOOOXX", "XXOOOXX"};
int DELTA_ROW[] = {0, -2, 0, 2};
int DELTA_COL[] = {-2, 0, 2, 0};
int FULL_ROW[] = {0, -1, 0, 1};
int FULL_COL[] = {-1, 0, 1, 0};
// void print_board(BOARD& board) {
// 	for (int row = 0; row < board.size(); ++row) {
// 		for (int col = 0; col < board.size(); ++col)
// 			cout << board[row][col] << ' ';
// 		cout << endl;
// 	}
// 	cout << endl;
// }

// void print_solution(vector<BOARD>& history) {
// 	for (int i = 0; i < history.size(); ++i)
// 		print_board(history[i]);
// }
void print_coord(BOARD& coord) {
	for (int i = 0; i < coord.size(); i++)
        cout << coord[i] << endl;
}
bool contains(BOARD& board, const vector<BOARD>& history) {
	for (int i = 0; i < history.size(); i++)
		if (history[i] == board)
			return true;
	return false;
}
bool check_full (BOARD& board, pair<int, int> coordinates, int move, BOARD& coord) {
    char coord_of_move[2];
    string str;
    int row = coordinates.first + DELTA_ROW[move];
    int col = coordinates.second + DELTA_COL[move];
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE)
        return false;
    if (board[row][col] == 'O') {
        int row_f = coordinates.first + FULL_ROW[move];
        int col_f = coordinates.second + FULL_COL[move];
        if (board[row_f][col_f] == 'N') {
            board[coordinates.first][coordinates.second] = 'O';
            board[row][col] = 'N';
            board[row_f][col_f] = 'O';
            coord_of_move[0] = char (coordinates.first + 65);
            coord_of_move[1] = char (coordinates.second + 49);
            str.append(coord_of_move);
            str.erase(2, 1);
            switch (move) {
            case 0 :
                str.append(" LEFT");
                break;
            case 1 :
                str.append(" UP");
                break;
            case 2 :
                str.append(" RIGHT");
                break;
            case 3 :
                str.append(" DOWN");
                break;
            }
            coord.push_back(str);
            return true;
        }
    }
    return false;
}
bool second_loop (BOARD& board, int begin_loop, int move, BOARD& coord) {
    for (int row = begin_loop; row < begin_loop + 3; ++row)
        for (int col = 0; col < SIZE; ++col)
            if (board[row][col] == 'N')
                if (check_full(board, make_pair(row, col), move, coord))
                    return true;
    return false;
}
bool first_loop (BOARD& board, int begin_loop, int move, BOARD& coord) {
    for (int row = begin_loop; row < begin_loop + 2; ++row)
        for (int col = 2; col < 5; ++col)
            if (board[row][col] == 'N')
                if (check_full(board, make_pair(row, col), move, coord))
                    return true;
    return false;
}
bool find_full (BOARD& board, int move, BOARD& coord) {
    bool full_ele;
    full_ele = first_loop(board, 0, move, coord);
    if (!full_ele) {
        full_ele = second_loop(board, 2, move, coord);
        if (!full_ele)
            full_ele = first_loop(board, 5, move, coord);
    }
    return full_ele;
}
bool ordered (BOARD& board) {
    if (board == ordered_board)
        return true;
    else
        return false;
}
bool solve (BOARD board, vector<BOARD>& history, BOARD& coord) {
    if (ordered(board)) {
        history.push_back(board);
        return true;
    }
    history.push_back(board);
    for (int move = 0; move < 4; move++) {
        BOARD next_board = board;
        bool status = find_full(next_board, move, coord);
        if (status) {
            if (contains(next_board, history)) {
                coord.pop_back();
                continue;
            }
            if (solve(next_board, history, coord))
                return true;
        }
    }
    history.pop_back();
    coord.pop_back();
    return false;
}
int main() {
    string str;
    BOARD board, coord;
    vector<BOARD> history;
    for (int row = 0; row < SIZE; ++row) {
        getline(cin, str);
        board.push_back(str);
    }
    if (solve(board, history, coord)) {
        // print_solution(history);
		// cout << "Solved in " << history.size() - 1 << " steps:" << endl;
        print_coord(coord);
    }
    else
        cout << "Loser" << endl;   
}