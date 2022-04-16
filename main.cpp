#include <vector>
#include <iostream>

struct pos{
    std::size_t row;
    std::size_t col;
};

class Solver {
private: 
    std::vector<std::vector<int>> _board;
    pos get_empty() {
        pos empty{};
        for (std::size_t row = 0; row < 9; ++row) {
            for (std::size_t col = 0; col < 9; ++col) {
                if (_board[row][col] == -1) {
                    empty.row = row;
                    empty.col = col;
                    return empty;
                }
            }
        }
        return {row: 99, col: 99};
    }

    bool try_guess(int guess, size_t row, size_t col) {
        // see if number is ok at row
        for (std::size_t i = 0; i < 9; ++i) {
            if (guess == _board[i][col]) {
                return false;
            }
        }

        // see if number is ok at column
        for (std::size_t i = 0; i < 9; ++i) {
            if (guess == _board[row][i]) {
                return false;
            }
        }

        // calculate all positions for the square
        //TODO: probably there is a better way to calculate
        //      all valid positions here. Can't figure out 
        //      at this time though.
        std::vector<pos> square;
        std::vector<std::size_t> row_val;
        std::vector<std::size_t> col_val;
        
        int pos_r = row % 3;
        switch (pos_r) {
            case 0: 
                row_val.push_back(row);
                row_val.push_back(row + 1);
                row_val.push_back(row + 2);
                break;
            case 1:
                row_val.push_back(row - 1);
                row_val.push_back(row);
                row_val.push_back(row + 1);
                break;
            case 2:
                row_val.push_back(row - 2);
                row_val.push_back(row - 1);
                row_val.push_back(row);
                break;
        }

        int pos_c = col % 3;
        switch (pos_c) {
            case 0: 
                col_val.push_back(col);
                col_val.push_back(col + 1);
                col_val.push_back(col + 2);
                break;
            case 1:
                col_val.push_back(col - 1);
                col_val.push_back(col);
                col_val.push_back(col + 1);
                break;
            case 2:
                col_val.push_back(col - 2);
                col_val.push_back(col - 1);
                col_val.push_back(col);
                break;
        }

        for (auto r : row_val) {
            for (auto c : col_val) {
                square.push_back(pos {r, c});
            }
        }

        for (std::size_t i = 0; i < 9; ++i) {
            pos p = square[i];
            int val = _board[p.row][p.col];
            if (guess == val){
                return false;
            } 
        }

        return true;
    }


    bool solver() {
        pos empty = get_empty();
        if (empty.row == 99) {
            return true;
        }
        // if there is an empty position, try a number
        for (int i=1; i<10; i++) {
            bool ok = try_guess(i, empty.row, empty.col);
            if (ok) {
                _board[empty.row][empty.col] = i;
                // if number fits the board. call the solver recursevelly
                if (solver()) {
                    return true;
                }
            }
        } 
        _board[empty.row][empty.col] = -1;
        return false;
    }

public:

    Solver(std::vector<std::vector<int>> board) {
        _board = board;
    }

    bool solve(){
        return solver();
    }

    void print_board() {    
        for (std::size_t row = 0; row < 9; ++row) {
            for (std::size_t col = 0; col < 9; ++col) {
                if ((col % 3) == 0)
                    std::cout << "| ";
                if (_board[row][col] == -1) {
                    std::cout << ". ";    
                } else
                    std::cout << _board[row][col] << " ";
            }
            if ((row % 3) == 2) {
                std::cout << "\n------------------------";
            }
            std::cout << "\n";
        }
        std::cout << "\n\n";
    }

};

int main () {

    std::vector<std::vector<int>> board;

    board = {{5,3,-1,-1,7,-1,-1,-1,-1},
             {6,-1,-1,1,9,5,-1,-1,-1},
             {-1,9,8,-1,-1,-1,-1,6,-1},
             {8,-1,-1,-1,6,-1,-1,-1,3},
             {4,-1,-1,8,-1,3,-1,-1,1},
             {7,-1,-1,-1,2,-1,-1,-1,6},
             {-1,6,-1,-1,-1,-1,2,8,-1},
             {-1,-1,-1,4,1,9,-1,-1,5},
             {-1,-1,-1,-1,8,-1,-1,7,9}};

    

    Solver s(board);

    s.print_board();

    bool solved = s.solve();
    std::cout << "Solved: " << solved << "\n";  

    s.print_board();



}



