#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

class TicTacToe{
    int n = 3;
    std::vector<std::vector<char> > table;
    int total_free;
    std::vector<char> is_row_free, is_col_free, is_diagonal_free;
    bool is_first_player = true;
    //left-dowm*, down*, right-down*, right*
    int dir_r[8]{1, 1, 1, 0,};
    int dir_c[8]{-1, 0, 1, 1};
    bool is_valid(int r, int c){
        return r >= 0 && r < n && c >= 0 && c < n;
    }
    void print(){
        std::ofstream board("board.txt");
        board << "\n<============================>\n";
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                board << table[i][j] << " ";
            }
            board << "\n";
        }
        board << "<============================>\n";
        board.close();
    }
    std::pair<int, int> read_location(){
        int r{-1}, c{-1};
        std::cout << "Player ";
        if(is_first_player)
            std::cout << "x";
        else
            std::cout << "o";
        std::cout << " turn. Enter empty location (r, c): ";
        while(true){
            std::cin >> r >> c;
            --r, --c;
            if(!is_valid(r, c)){
                std::cout << "\tWrong location, indices must be between 1 and n. Try again\n";
                continue;
            }
            else if(table[r][c] != '.'){
                std::cout << "\tThis location is not empty. Try again\n";
                continue;
            }
            else{
                break;
            }
        }
        return {r, c};
    }
    void update_total_free(int r, int c){
        char cur = table[r][c];
        if(is_col_free[c] == '.'){
            is_col_free[c] = cur;
        }
        else if(is_col_free[c] != cur && is_col_free[c] != '#'){
            total_free--;
            is_col_free[c] = '#';
        }
        if(is_row_free[r] == '.'){
            is_row_free[r] = cur;
        }
        else if(is_row_free[r] != cur && is_row_free[r] != '#'){
            total_free--;
            is_row_free[r] = '#';
        }
        if(r == c && is_diagonal_free[0] == '.'){
            is_diagonal_free[0] = cur;
        }
        else if(r == c && is_diagonal_free[0] != cur && is_diagonal_free[0] != '#'){
            total_free--;
            is_diagonal_free[0] = '#';
        }
        if(r + c == n - 1 && is_diagonal_free[1] == '.'){
            is_diagonal_free[1] = cur;
        }
        else if(r + c == n - 1 && is_diagonal_free[1] != cur && is_diagonal_free[1] != '#'){
            total_free--;
            is_diagonal_free[1] = '#';
        }
    }
    bool check_a_line(int r, int c, int direction){
        char cur = table[r][c];
        for(int i = 1; i < n; ++i){
            r += dir_r[direction];
            c += dir_c[direction];
            if(table[r][c] != cur){
                return false;
            }
        }
        return true;
    }
    bool is_winning(int r, int c){
        return (is_row_free[r] != '#' && check_a_line(r, 0, 3)) //right dir checks row
            || (is_col_free[c] != '#' && check_a_line(0, c, 1)) // down dir checks col
            || (is_diagonal_free[0] != '#' && r == c && check_a_line(0, 0, 2)) // maim diagonal
            || (is_diagonal_free[1] != '#' && r + c == n - 1 && check_a_line(0, n - 1, 0));  // second diagonal
    }
    /**
     * 0 -> normal
     * 1 -> win!
     * 2 -> tie!
     */
    int play(){
        auto [r, c] = read_location();
        
        if(is_first_player)
            table[r][c] = 'x';
        else
            table[r][c] = 'o';
        print();
        update_total_free(r, c);
        if(is_winning(r, c)){
            return 1;
        }
        else if(total_free == 0){
            return 2;
        }
        is_first_player = !is_first_player;
        return 0;
    }
public:
    TicTacToe(int _n = 3){
        std::cout << "\n*********Welcome*********\n\n";
        assert(_n >= 3 && _n < 10);
        n = _n;
        total_free = 2 * n + 2;
        table = std::vector<std::vector<char>>(n, std::vector<char>(n, '.'));
        is_row_free = is_col_free = std::vector<char>(n, '.');
        is_diagonal_free = std::vector<char>(2, '.');
    }
    void run(){
        print();
        int state = 0;
        while(state == 0){
            state = play();
        }
        if(state == 1){
            std::cout << "\n\tPlayer ";
            if(is_first_player)
                std::cout << "x";
            else 
                std::cout << "o";
            std::cout << " won!\n";
        }
        else if(state == 2){
            std::cout << "\n\tTie!\n";
        }
        std::cout << "\n***********Bye***********\n";
    }
};

int main(){
    int n;
    std::cout << "choose a number(3 - 9) to play with: ";
    std::cin >> n;
    TicTacToe game(n);
    game.run();
    return 0;
}
