#include<iostream>
#include<vector>
#include<stack>
// #include<queue>
#include<set>
using namespace std;

#define N 3

struct puzzleState {
    vector<vector<int>> board;
    int x, y, depth;

    puzzleState(vector<vector<int>> b, int i, int j, int d): 
        board(b), x(i), y(j), depth(d) {}

};

int rows[] = {0, 0, -1, 1};
int cols[] = {-1, 1, 0, 0};

bool check_goalState(vector<vector<int>> board){
    vector<vector<int>> goal_state = {{1,2,3},{4,5,6},{7,8,0}};

    return (board == goal_state);
}

void print_board(vector<vector<int>> board){
    for(auto row :board){
        for(auto num: row){
            cout<< num <<" ";
        }
        cout<<endl;
    }
    cout << "---x----x----" <<endl;
}

bool isValid(int x, int y){
    return (x >= 0 && x < N && y >= 0 && y < N);
}

void solvePuzzle(vector<vector<int>> &start, int x, int y){
    stack<puzzleState> st;
    
    set<vector<vector<int>>> visited;

    st.push(puzzleState(start, x, y, 0));
    visited.insert(start);

    while(!st.empty()){
        puzzleState curr = st.top();
        st.pop(); 

        cout<<"depth :"<<curr.depth<<endl;
        print_board(curr.board);

        if(check_goalState(curr.board)){
            cout<< "Reached the goal state" <<endl;
            cout<< "goal state depth:" << curr.depth <<endl;
            return;
        }

        for(int i=0; i<4; i++){
            int newX = curr.x + rows[i];
            int newY = curr.y + cols[i];
            
            if(isValid(newX, newY)){
                vector<vector<int>> newBoard = curr.board;

                swap(newBoard[curr.x][curr.y], newBoard[newX][newY]);

            

                if(visited.find(newBoard) == visited.end()){
                    visited.insert(newBoard);
                    st.push(puzzleState(newBoard, newX, newY, curr.depth+1));
                }
            }
        }
    }

    cout<< "No solution found"<<endl;

}

int main(){
    vector<vector<int>> start = {{1, 2, 3}, {4, 0, 5}, {6, 7, 8}};
    int x = 1, y = 1; 

    cout << "Initial State: " << endl;
    print_board(start);

    solvePuzzle(start, x, y);

return 0;
}

