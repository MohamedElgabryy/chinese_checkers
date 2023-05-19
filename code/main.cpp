//Ahmed Osama Mahmoud 20190015
//Ahmed Sameh Mohammed 20190032
//Abdelrahman Hussain Mohamed 20190289
//Mahmoud osama othman 20190491
//Walid Mohamed Ibrahim 20190614

#include <iostream>
#include "windows.h"
#include <vector>
#include <algorithm>
#include<bits/stdc++.h>
#define FAST_IO  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;
struct node{
    int row;
    int column;
    char color;
};
vector<pair<char,char>> Opposite={{'R','G'},{'G','R'},{'O','B'},{'B','O'},{'Y','I'},{'I','Y'}};
vector<pair<char,pair<int,int>>> FinalColor={{'R',{17,5}},{'I',{13,10}},{'G',{1,13}},
                                             {'O',{13,4}},{'B',{5,17}},{'Y',{5,5}}};
int colors;
vector<node>loadBoard(){
    vector<node>board(122);
    int i=0;
    ifstream boardFile;
    if(colors==6){
        boardFile.open("input.txt", ios::in);
    }
    else{
        boardFile.open("input2.txt", ios::in);
    }
    while(i<121) {
        char state[6];
        boardFile.read(state, 5);
        string str1, str2, str=state;
        char col;
        str1=str.substr(0,2);
        str2=str.substr(2,2);
        col=str[4];
        board[i].row= stoi(str1);
        board[i].column= stoi(str2);
        board[i].color= col;
        i++;
    }
    return board;
}
vector<node>board;
void startBoard(){
    board =loadBoard();
}
//بيرجع الون بتاع صف وعمود معينين
char myColor(int curRow, int curColumn,vector<node>& chooseboard) {
    for (int i = 0; i < chooseboard.size(); ++i) {
        if (chooseboard[i].row == curRow && chooseboard[i].column == curColumn) {
            return chooseboard[i].color;
        }
    }
}
//صف والععمود دول في حدود البورد ولا لا وبيتاكد انها وايت
bool isItInBoardAndWhite(int r, int c,vector<node>& chooseboard){
    for (int i = 0; i < chooseboard.size(); ++i) {
        if (chooseboard[i].row==r && chooseboard[i].column==c
            &&chooseboard[i].color=='W'){
            return true;
        }
    }
    return false;
}
//صف والععمود دول في حدود البورد ولا لا وهى وبيتاكد انها مش وايت
bool isItInBoardAndNotWhite(int r, int c,vector<node>& chooseboard){
    for (int i = 0; i < chooseboard.size(); ++i) {
        if (chooseboard[i].row==r && chooseboard[i].column==c
            &&  (chooseboard[i].color!='W')){
            return true;
        }
    }
    return false;
}
//بتاخد صف وعمود معينين بتجيب كل كل النود الفاضيه حواليه
vector<node>availableMoves(int curRow, int curColumn,vector<node>& chooseboard){
    char currentColor;
    vector<node>availableMoves(6);
    //currRow=5&curColumn=11-> parent node
    //children nodes:5,12 &5,10 &6,11 &6,10 &4,12 &4,11
    curColumn++;
    //currRow=5&curColumn=12
    if (isItInBoardAndWhite(curRow, curColumn,chooseboard) ){
        availableMoves[0].row=curRow;
        availableMoves[0].column=curColumn;
        availableMoves[0].color=myColor(curRow,curColumn,chooseboard);
    }
    curColumn--;
    //currRow=5&curColumn=11 -> parent node
    curColumn--;
    //currRow=5&curColumn=10
    if (isItInBoardAndWhite(curRow, curColumn,chooseboard) ){
        availableMoves[1].row=curRow;
        availableMoves[1].column=curColumn;
        availableMoves[1].color=myColor(curRow,curColumn,chooseboard);;
    }
    curColumn++;
    //currRow=5&curColumn=11 -> parent node
    curRow--;
    //currRow=4&curColumn=11
    if (isItInBoardAndWhite(curRow, curColumn,chooseboard) ){
        availableMoves[2].row=curRow;
        availableMoves[2].column=curColumn;
        availableMoves[2].color=myColor(curRow,curColumn,chooseboard);
    }
    curColumn++;
    //currRow=4&curColumn=12
    if (isItInBoardAndWhite(curRow, curColumn,chooseboard) ){
        availableMoves[3].row=curRow;
        availableMoves[3].column=curColumn;
        availableMoves[3].color=myColor(curRow,curColumn,chooseboard);
    }
    curColumn--;
    curRow++;
    //currRow=5&curColumn=11-> parent node
    curRow++;
    //currRow=6&curColumn=11 ->child node
    if (isItInBoardAndWhite(curRow, curColumn,chooseboard) ){
        availableMoves[4].row=curRow;
        availableMoves[4].column=curColumn;
        availableMoves[4].color=myColor(curRow,curColumn,chooseboard);
    }
    curColumn--;
    //currRow=6&curColumn=10 ->child node
    if (isItInBoardAndWhite(curRow, curColumn,chooseboard) ){
        availableMoves[5].row=curRow;
        availableMoves[5].column=curColumn;
        availableMoves[5].color=myColor(curRow,curColumn,chooseboard);
    }
    //change
    vector<node>availableMovesOnly;
    for (int i = 0; i < 6; ++i) {
        if(availableMoves[i].row!=0)
            availableMovesOnly.push_back(availableMoves[i]);
    }

    return availableMovesOnly;
    //  return availableMoves;
}

//بتاخد صف وعمود وبتجيب كل النود اليه ممكن اروحلها من خلال الجمب
vector<node>availableLeaps(int curRow, int curColumn,vector<node>& chooseboard){

    vector<node>availableLeaps(6);
    //currRow=5&curColumn=11-> parent node
    //children nodes:
    curColumn+=2;
    //currRow=5&curColumn=13
    if (isItInBoardAndWhite(curRow, curColumn,chooseboard)
        && isItInBoardAndNotWhite(curRow, curColumn-1,chooseboard)){
        availableLeaps[0].row=curRow;
        availableLeaps[0].column=curColumn;
        availableLeaps[0].color='W';
    }
    curColumn-=2;//11
    //currRow=5&curColumn=11 -> parent node
    curColumn-=2;//9
    //currRow=5&curColumn=9
    if (isItInBoardAndWhite(curRow, curColumn,chooseboard)
        && isItInBoardAndNotWhite(curRow, curColumn+1,chooseboard)){
        availableLeaps[1].row=curRow;
        availableLeaps[1].column=curColumn;
        availableLeaps[1].color='W';
    }
    curColumn+=2;
    //currRow=5&curColumn=11 -> parent node
    curRow-=2;//3
    //currRow=3&curColumn=11
    if (isItInBoardAndWhite(curRow, curColumn,chooseboard)
        && isItInBoardAndNotWhite(curRow+1, curColumn,chooseboard)){
        availableLeaps[2].row=curRow;
        availableLeaps[2].column=curColumn;
        availableLeaps[2].color='W';
    }
    curColumn+=2;
    //currRow=3&curColumn=13
    if (isItInBoardAndWhite(curRow, curColumn,chooseboard)
        && isItInBoardAndNotWhite(curRow+1, curColumn-1,chooseboard)){
        availableLeaps[3].row=curRow;
        availableLeaps[3].column=curColumn;
        availableLeaps[3].color='W';
    }
    curColumn-=2;//11
    curRow+=2;//5
    //currRow=5&curColumn=11-> parent node
    curRow+=2;
    //currRow=7&curColumn=11 ->child node
    if (isItInBoardAndWhite(curRow, curColumn,chooseboard)
        && isItInBoardAndNotWhite(curRow-1, curColumn,chooseboard)){
        availableLeaps[4].row=curRow;
        availableLeaps[4].column=curColumn;
        availableLeaps[4].color='W';
    }

    curColumn-=2;
    //currRow=6&curColumn=10 ->child node
    if (isItInBoardAndWhite(curRow, curColumn,chooseboard)
        && isItInBoardAndNotWhite(curRow-1, curColumn+1,chooseboard)){
        availableLeaps[5].row=curRow;
        availableLeaps[5].column=curColumn;
        availableLeaps[5].color='W';
    }

    //changed
    vector<node>availableLeapsOnly;
    for (int i = 0; i < 6; ++i) {
        if(availableLeaps[i].row!=0)
            availableLeapsOnly.push_back(availableLeaps[i]);
    }

    return availableLeapsOnly;
    //   return availableLeaps;
}
bool searchInVector(vector<node> v ,node n){
    for (int i = 0; i < v.size(); ++i) {
        if(v[i].row==n.row&&v[i].column==n.column&&v[i].color==n.color)
            return true;
    }
    return false;
}
vector<node>allAvailableLeaps(int curRow, int curColumn,vector<node>& chooseboard){
    vector<node>allAvailableLeaps =availableLeaps(curRow,curColumn,chooseboard);
    for (int i = 0; i < allAvailableLeaps.size(); ++i) {
        vector<node>tempNodes=availableLeaps(allAvailableLeaps[i].row,allAvailableLeaps[i].column,chooseboard);
        for (int j = 0; j < tempNodes.size(); ++j) {
            if(!searchInVector(allAvailableLeaps,tempNodes[j])){
                allAvailableLeaps.push_back(tempNodes[j]);
            }
        }
    }
    return allAvailableLeaps;
}

//بتاخد الون معين بترجع فيكتور بير من الصف وعمود يحتوى على الون دا
vector<pair<int,int>> Possiblemoves(char color,vector<node>& chooseboard){
    vector<pair<int,int>> greenloc;
    for (int i = 0; i < chooseboard.size(); ++i) {
        if (chooseboard[i].color==color){
            greenloc.emplace_back(make_pair(chooseboard[i].row,chooseboard[i].column));
        }
    }
    return greenloc;
}
//اقدر اتحرك فين من اماكني الحالية
vector<pair<node,node>> avialableNodes(vector<pair<int,int>> mine,vector<node>& chooseboard){
    vector<pair<node,node>> result;
    for(int i=0;i<mine.size();i++){
        //i_vec1.insert(i_vec1.end(), i_vec2.begin(), i_vec2.end())
        vector<node>Temp=availableMoves(mine[i].first,mine[i].second,chooseboard);
        node temp;
        temp.row=mine[i].first;temp.column=mine[i].second;
        for(int j=0;j<Temp.size();j++){//changed
            result.emplace_back(temp,Temp[j]);
        }
        //to be changed not doing recursion
        vector<node> Temp2= allAvailableLeaps(mine[i].first,mine[i].second,chooseboard);
//        vector<node> Temp2= availableLeaps(mine[i].first,mine[i].second,chooseboard);
        for(int j=0;j<Temp2.size();j++){//changed
            result.emplace_back(temp,Temp2[j]);
        }
    }
    return result;
}
void SetColor(int value){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  value);
}

void setColor(char color){
    if(color=='W'){
        SetColor(7);
    }else if(color=='B'){
        SetColor(1);
    }else if(color=='I'){
        SetColor(5);
    }else if(color=='O'){
        SetColor(12|14);
    }else if(color=='R'){
        SetColor(4);
    }else if(color=='G'){
        SetColor(2);
    }else if(color=='Y'){
        SetColor(6);
    }
}
//بيطبع البورده ههههههه
void printboard(vector<node>& chooseboard){

    int k=0; int O=52;
    for(int i=1;i<5;i++){
        for(int h=O;h>0;h--){cout<<" ";}
        for(int j=i;j>0;j--){
            setColor(chooseboard[k].color);
            cout<<"(";
            string row1 = to_string(chooseboard[k].row);
            if(row1.length()==1)
                cout<<"0";
            cout<<chooseboard[k].row<<','<<chooseboard[k].column<<','<<chooseboard[k].color<<")"<<std::flush;
            k++;}
        O-=3;
        cout<<endl;
    }
    int U=13; O=2;
    for(int i=1;i<5;i++) {
        for (int h = 0; h < O; h++) { cout << " "; }
        for (int j = U; j > 0; j--) {
            setColor(chooseboard[k].color);
            cout << "(";
            string row1 = to_string(chooseboard[k].row);
            if(row1.length()==1)
                cout<<"0";
            cout << chooseboard[k].row << ',' ;
            string c1 = to_string(chooseboard[k].column);
            if(c1.length()==1)
                cout<<"0";
            cout << chooseboard[k].column << ',' << chooseboard[k].color << ")"<<std::flush;
            k++;
        }
        U--;
        O+=2;
        cout << endl<<"   ";
    }
    for(int h=0;h<12;h++){cout<<" ";}
    for(int i=1;i<10;i++){
        setColor(chooseboard[k].color);
        cout << "(";
        string row1 = to_string(chooseboard[k].row);
        if(row1.length()==1)
            cout<<"0";
        cout << chooseboard[k].row << ',' ;
        string c1 = to_string(chooseboard[k].column);
        if(c1.length()==1)
            cout<<"0";
        cout << chooseboard[k].column << ',' << chooseboard[k].color << ")"<<std::flush;
        k++;
    }
    cout<<endl<<"   ";

    int UU=10;O=8;
    for(int i=1;i<5;i++){
        for(int P=O;P>0;P--){cout<<" ";}
        for(int j=UU;j>0;j--){
            setColor(chooseboard[k].color);
            cout << "(";
            string row1 = to_string(chooseboard[k].row);
            if(row1.length()==1)
                cout<<"0";
            cout << chooseboard[k].row << ',' ;
            string c1 = to_string(chooseboard[k].column);
            if(c1.length()==1)
                cout<<"0";
            cout << chooseboard[k].column << ',' << chooseboard[k].color << ")"<<std::flush;
            k++;}
        UU++;O-=2;
        cout<<endl;
    }
    O=42;
    for(int i=4;i>0;i--){
        for(int h=O;h>0;h--){cout<<" ";}
        for(int j=i;j>0;j--){
            setColor(chooseboard[k].color);
            cout << "(";
            string row1 = to_string(chooseboard[k].row);
            if(row1.length()==1)
                cout<<"0";
            cout << chooseboard[k].row << ',' ;
            string c1 = to_string(chooseboard[k].column);
            if(c1.length()==1)
                cout<<"0";
            cout << chooseboard[k].column << ',' << chooseboard[k].color << ")"<<std::flush;
            k++;}
        O+=3;
        cout<<endl<<" ";
    }
}
//بيحرك الون من مكان اليه مكان
void move(int fromrow,int fromcolumn,int torow,int tocolumn, vector<node>& boardd){
    char color= myColor(fromrow,fromcolumn,boardd);
    for (int i = 0; i < boardd.size(); i++) {
        if (boardd[i].row==fromrow && boardd[i].column==fromcolumn){
            boardd[i].color='W';
        }
        if (boardd[i].row==torow && boardd[i].column==tocolumn){
            boardd[i].color=color;
        }
    }
}
//بيتاكد ان الحركه دى صح ولا لا
bool checkmove(vector<pair<node,node>> res,int fromrow,int fromcolumn,int torow,int tocolumn ) {

    for (int i = 0; i < res.size(); i++) {
        if(res[i].first.row==fromrow && res[i].first.column==fromcolumn && res[i].second.row==torow && res[i].second.column==tocolumn){
            return true;
        }
    }
    return false;
}
//بستخدمها علشان اعرف اماكن الون دا فين في البدايه
vector<node> GetColorCord(char color,vector<node>& chooseboard) {
    vector<node> Result;
    for (int i = 0; i < chooseboard.size(); i++) {
        if (chooseboard[i].color == color) {
            Result.emplace_back(chooseboard[i]);
        }
    }
    return Result;
}
const vector<pair<char,vector<node>>>Homes={{'R',GetColorCord('G',board)},{'G',GetColorCord('R',board)},{'I',GetColorCord('Y',board)},{'Y',GetColorCord('I',board)},
                                            {'B',GetColorCord('O',board)},{'O',GetColorCord('B',board)}};
//بتجيب النقطة العكس الي المفروض اروحلها عشان اقيس عليها في المينيماكس للون معين
pair<int,int> finall(char color){
    pair<int,int> Result;
    for(int i=0;i<FinalColor.size();i++){
        if(color==FinalColor[i].first){Result=FinalColor[i].second;break;}
    }
    return Result;
}

//تجيب مين اللون الي عكس اتجاهي
char oppositeColor(char color) {
    char OColor = ' ';
    for (auto & i : Opposite) {
        if (i.first == color) {
            OColor =i.second;
            break;
        }
    }
    return OColor;
}

//بتجيب النقط بتاعة لون معين بعيدة قد اية عن النقطة الي في راس المثلث
double GetHowFar(char color,vector<node>& chooseboard){
    //get green how far: sum(|how far from red|) - get green how far sum(|how far from green|)
    vector<node>R=GetColorCord(color,chooseboard);
    char opposite= oppositeColor(color);
    pair<int,int> Final= finall(opposite);
    double howfar=0.0;
    if(color=='R'||color=='G'||color=='Y'||color=='I') {
        for (int i = 0; i < R.size(); i++) {
            howfar += abs(R[i].row - Final.first);
            //numberofminimax=(Gethowfar(color)+-----------)-(Gethowfar(color)+--------)
        }
    }else{
        for (int i = 0; i < R.size(); i++) {
            howfar += abs(R[i].column - Final.second);
            //numberofminimax=(Gethowfar(color)+-----------)-(Gethowfar(color)+--------)
        }
    }
    return howfar;
}

void  Playerdecidetomove(vector<node>& chooseboard) {
    vector<pair<int, int>> greenposmove;
    vector<pair<int, int>> indigoposmove;
    vector<pair<int, int>> blueposmove;
    greenposmove = Possiblemoves('G',chooseboard);
    indigoposmove= Possiblemoves('I',chooseboard);
    blueposmove= Possiblemoves('B',chooseboard);
    vector<pair<node, node>> Result;
    vector<pair<node, node>> greenMoves=avialableNodes(greenposmove,chooseboard);//changed
    vector<pair<node, node>> indigoMoves=avialableNodes(indigoposmove,chooseboard);
    vector<pair<node, node>> blueMoves=avialableNodes(blueposmove,chooseboard);
//i_vec1.insert(i_vec1.end(), i_vec2.begin(), i_vec2.end())
    Result.insert(Result.end(),greenMoves.begin(),greenMoves.end());
    Result.insert(Result.end(),indigoMoves.begin(),indigoMoves.end());
    Result.insert(Result.end(),blueMoves.begin(),blueMoves.end());

    cout<<"Valid Moves:"<<endl;
    cout<<"---------------------------------"<<endl;
    for (int i = 0; i < Result.size(); i++) {
        setColor(chooseboard[i].color);
        cout<<"From "<<"(" << Result[i].first.row << ',' << Result[i].first.column
            << ")"<<" To "<< "(" << Result[i].second.row << ',' << Result[i].second.column << ',' << Result[i].second.color
            << ")" << endl<<std::flush;
    }
    cout<<"------------------------------------"<<endl;
    printboard(board);
    while(true){
        //iterate possible move and row and columns given by user should match one of those possible moves
        int torow, tocolumn;
        int fromrow, fromcolumn;
        setColor('W');
        cout << "Please Enter from Node and to node " << endl;
        cin >> fromrow >> fromcolumn >> torow >> tocolumn;
        if (checkmove(Result, fromrow, fromcolumn, torow, tocolumn)) {
            move(fromrow, fromcolumn, torow, tocolumn,chooseboard);
            break;//change
        }else{
            cout<<"Please Play Valid move"<<endl;
            cout<<"-----------------------------"<<endl;
        }
    }
}

//هل اللون الفلاني وصل للجول ولا لا
bool colorgoal(char color){
    bool flag=false;
    vector<node> minegoal;
    for(int i=0;i<Homes.size();i++){
        if(color==Homes[i].first){
            minegoal=Homes[i].second;
        }
    }
    for(int i=0;i<minegoal.size();i++){
        if(minegoal[i].color==color){
            flag=true;
        }else{
            flag=false;
            break;
        }
    }
    return flag;
}

//هل البلاير دة كسب ولا لا
bool Winner(char color1,char color2,char color3){
    if(colorgoal(color1)&& colorgoal(color2)&& colorgoal(color3)){
        return true;
    }else
        return false;
}
//هل في فايز ولا لا
double checkWinner(){
    bool X=Winner('Y','R','O');
    bool Y=Winner('B','G','I');
    if(X){return 1;}
    else if(Y){return 2;}
    else{return 0;}
}

vector<pair<node, node>> GetAllValidToMoveAgent(vector<node>& chooseboard){
    vector<pair<int, int>> redposmove;
    vector<pair<int, int>> yellowposmove;
    vector<pair<int, int>> orangeposmove;
    redposmove = Possiblemoves('R',chooseboard);

    vector<pair<node, node>> Result;
//i_vec1.insert(i_vec1.end(), i_vec2.begin(), i_vec2.end())
    vector<pair<node, node>> redMoVes=avialableNodes(redposmove,chooseboard);//changed
    yellowposmove= Possiblemoves('Y',chooseboard);
    orangeposmove= Possiblemoves('O',chooseboard);

    Result.insert(Result.end(),redMoVes.begin(),redMoVes.end());
    if(colors==6){
        vector<pair<node, node>> yellowMoVes=avialableNodes(yellowposmove,chooseboard);
        vector<pair<node, node>> orangeMoVes=avialableNodes(orangeposmove,chooseboard);

        Result.insert(Result.end(),yellowMoVes.begin(),yellowMoVes.end());
        Result.insert(Result.end(),orangeMoVes.begin(),orangeMoVes.end());
    }

    return Result;
}
vector<pair<node, node>> GetAllValidToMovePlayer(vector<node>& chooseboard){
    vector<pair<int, int>> redposmove;
    vector<pair<int, int>> yellowposmove;
    vector<pair<int, int>> orangeposmove;
    redposmove = Possiblemoves('G',chooseboard);
    yellowposmove= Possiblemoves('B',chooseboard);
    orangeposmove= Possiblemoves('I',chooseboard);
    vector<pair<node, node>> Result;
    vector<pair<node, node>> redMoves=avialableNodes(redposmove,chooseboard);
    Result.insert(Result.end(),redMoves.begin(),redMoves.end());

//i_vec1.insert(i_vec1.end(), i_vec2.begin(), i_vec2.end())

    if(colors==6){
        vector<pair<node, node>> yellowMoves=avialableNodes(yellowposmove,chooseboard);
        vector<pair<node, node>> orangeMoves=avialableNodes(orangeposmove,chooseboard);
        Result.insert(Result.end(),yellowMoves.begin(),yellowMoves.end());
        Result.insert(Result.end(),orangeMoves.begin(),orangeMoves.end());
    }
    return Result;
}

double scoree(vector<node>& boardd){
    return( (GetHowFar('R',boardd)+ GetHowFar('Y',boardd)+ GetHowFar('O',boardd))-
            (GetHowFar('G',boardd)+ GetHowFar('B',boardd)+ GetHowFar('I',boardd)));
}
double  minimax(int depth,bool IsMaximizing, vector<node> boardd ,bool firstTime=true){

    double result = checkWinner();
    if(depth == 0 || result != 0) {
        return result;
    }
    if(IsMaximizing){
        double finalScore=-1000000000;
        int fromrow,fromcolumn,torow,tocolumn;
        vector<pair<node,node>> Agentmoves=GetAllValidToMoveAgent(boardd);
        for(int i=0;i<Agentmoves.size();i++){
            vector<node> tempBoard =boardd;
            move(Agentmoves[i].first.row,Agentmoves[i].first.column,
                 Agentmoves[i].second.row,Agentmoves[i].second.column,tempBoard);
            double score= scoree(tempBoard);

            minimax(depth-1,false,tempBoard, false);
            if(finalScore<score){
                finalScore=score;
                fromrow=Agentmoves[i].first.row;
                fromcolumn=Agentmoves[i].first.column;
                tocolumn=Agentmoves[i].second.column;
                torow=Agentmoves[i].second.row;
            }
        }
        if(firstTime){
            move(fromrow,fromcolumn,torow,tocolumn,board);
        }
        return finalScore;
    }else{
        double finalScore=100000000;
        int fromrow,fromcolumn,torow,tocolumn;
        vector<pair<node,node>> Playermoves=GetAllValidToMovePlayer(boardd);
        for(int i=0;i<Playermoves.size();i++){
            vector<node> tempBoard =boardd;
            move(Playermoves[i].first.row,Playermoves[i].first.column,
                 Playermoves[i].second.row,Playermoves[i].second.column,tempBoard);
            double score=scoree(tempBoard);
            minimax(depth-1,true,tempBoard, false);
            if(finalScore>score){
                finalScore=score;
                fromrow=Playermoves[i].first.row;
                fromcolumn=Playermoves[i].first.column;
                tocolumn=Playermoves[i].second.column;
                torow=Playermoves[i].second.row;
            }
        }
        if(firstTime){
            move(fromrow,fromcolumn,torow,tocolumn,board);
        }
        return finalScore;
    }

}
double  alphaBeta(int depth,bool IsMaximizing, vector<node> boardd , double bestScore,bool firstTime=true){

    double result = checkWinner();
    if(depth == 0 || result != 0) {
        return scoree(boardd);
    }
    if(IsMaximizing){
        double finalScore=-1000000000;
        int fromrow,fromcolumn,torow,tocolumn;
        vector<pair<node,node>> Agentmoves=GetAllValidToMoveAgent(boardd);
        for(int i=0;i<Agentmoves.size();i++){
            vector<node> tempBoard =boardd;
            move(Agentmoves[i].first.row,Agentmoves[i].first.column,
                 Agentmoves[i].second.row,Agentmoves[i].second.column,tempBoard);
//            double score= scoree(tempBoard);
            double currntScore = alphaBeta(depth-1,false,tempBoard, finalScore,false);
            if(!firstTime && finalScore>bestScore){
                break;
            }
            if(finalScore<currntScore){
                finalScore=currntScore;
                fromrow=Agentmoves[i].first.row;
                fromcolumn=Agentmoves[i].first.column;
                tocolumn=Agentmoves[i].second.column;
                torow=Agentmoves[i].second.row;
            }
        }
        if(firstTime){
            move(fromrow,fromcolumn,torow,tocolumn,board);
        }
        return finalScore;
    }else{
        double finalScore=100000000;
        int fromrow,fromcolumn,torow,tocolumn;
        vector<pair<node,node>> Playermoves=GetAllValidToMovePlayer(boardd);
        for(int i=0;i<Playermoves.size();i++){
            vector<node> tempBoard =boardd;
            move(Playermoves[i].first.row,Playermoves[i].first.column,
                 Playermoves[i].second.row,Playermoves[i].second.column,tempBoard);
//            double score=scoree(tempBoard);
            double currntScore = alphaBeta(depth-1,true,tempBoard ,finalScore,false);
            if(!firstTime && finalScore<bestScore){
                break;
            }
            if(finalScore>currntScore){
                finalScore=currntScore;
                fromrow=Playermoves[i].first.row;
                fromcolumn=Playermoves[i].first.column;
                tocolumn=Playermoves[i].second.column;
                torow=Playermoves[i].second.row;
            }
        }
        if(firstTime){
            move(fromrow,fromcolumn,torow,tocolumn,board);
        }
        return finalScore;
    }

}

int main() {
    FAST_IO
    cout<<"======Hello in chiness Checker======="<<endl;
    while (true){
        cout<<"1-> 2 Colors"<<endl;
        cout<<"2-> 6 Colors"<<endl;
        int colorsNo;cin >> colorsNo;
        if(colorsNo == 1){
            colors=2;
            break;
        }else if (colorsNo == 2){
            colors=6;
            break;
        }else{
            cout<<"Wrong input"<<endl;
        }
    }
    startBoard();
    int depth;
    while (true){
        cout<<"please Choice Level Easy(1) Medium(3) Hard(5)"<<endl;
        cin>>depth;
        if(depth>0 && depth<6){
            break;
        }
        else
            cout<<"Wrong input"<<endl;
    }
    int algo;
    while (true){
        cout<<"(1)MinMax"<<endl;
        cout<<"(2)AlphaBeta"<<endl;
        cin>>algo;
        if(algo==1 || algo==2){
            break;
        }
        else
            cout<<"Wrong input"<<endl;
    }
    while(true){
        //printboard(board);
        Playerdecidetomove(board);
        if(checkWinner()==2){cout<<"Player is Winnner"<<endl;break;}
        if(algo==1){
            minimax(depth,true,board);
        }else{
            alphaBeta(depth,true,board,0.0);
        }
        if(checkWinner()==1){cout<<"Computer is Winnner"<<endl;break;}
        printboard(board);
    }
    return 0;
}
