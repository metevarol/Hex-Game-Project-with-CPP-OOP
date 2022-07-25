#include <iostream>
#include<fstream>
#include<typeinfo>             

using namespace std;

bool loadcheck=false;

void savefile(const int &size,const int &gamemode,const int &playerturn,char board[12][12],char filename[30]){  //constant parameter by reference

    ofstream myfile(filename);

    myfile<<size<<" "<<gamemode<<" "<<playerturn<<endl;

    int i;
    decltype(i) j;                                                                                             //decltype statement

    for(i=0;i<size;i++){
        for(j=0;j<size;j++){

            myfile<<i<<" "<<j<<" "<<board[i][j]<<endl;
        }
    }

}

void loadfile(int &size,int &gamemode,int &playerturn,char board[12][12],char filename[30]){  //parameter by reference

    ifstream myfile(filename);

    int i=0;
    int row,column;

    while(myfile){

        if(i==0)
        myfile>>size>>gamemode>>playerturn;

        if(i!=0)
        myfile>>row>>column>>board[row][column];


        i++;
    }

}

void printboard(int size,char board[][12]){  //default arguments

     for(int i=0;i<size;i++){

        cout<<' '<<' '<< char(97+i);
     }
     cout<<endl;

     for(int i=0;i<size;i++){
        cout << i+1 <<" ";
            if(i==0){
                cout <<" ";
            }
            if(i==1){
                cout <<"  ";
            }
            if(i==2){
                cout <<"   ";
            }
            if(i==3){
                cout <<"    ";
            }
            if(i==4){
                cout <<"     ";
            }
            if(i==5){
                cout <<"      ";
            }
            if(i==6){
                cout <<"       ";
            }
            if(i==7){
                cout <<"        ";
            }
            if(i==8){
                cout <<"         ";
            }
            if(i==9){
                cout <<"         ";
            }
            if(i==10){
                cout <<"          ";
            }
            if(i==11){
                cout <<"           ";
            }

        for(int j=0;j<size;j++){
            cout << board [i][j]<<"  ";
        }
        cout << endl;
    }

}

enum playertype{playerx = 'x',playero = 'o'};  //enum

void userplay(int row,int column,char board[][12]){  //default arguments

    board[row][column]=playerx;

}

void userplay_o(int row,int column,char board[][12]){  //default arguments

    board[row][column]=playero;

}


void botplay(int size,int row,int column,char board[][12]){  //default arguments

if(row%2==0){

    if(column+3>size-1){
        goto place1;
    }
        if(column%3==0){

            if(row-3<0){
            goto place2;
        }
        if(board[row-3][column+3]=='x'||board[row-3][column+3]=='o'){

        goto place3;
    }
    
        if(row-3<0){
        goto place2;
        }
     place4:   
        board[row-3][column+3]='o';
    }
    else{
        if(board[row+2][column+3]=='x'||board[row+2][column+3]=='o'){

        goto place3;
    }
        if(row+2>size-1){
        goto place4;
        }

        place2:
        board[row+2][column+3]='o';

    }

}else{
    if(column-1<0){
        goto place4;
    }
        place1:
    if(column%3==0){
        if(row+3>size-1){
            goto place3;
        }
        if(row+3>size-1){
        goto place3;
        }
        place5:
        board[row+3][column-1]='o';
    }else{
        if(board[row-2][column-1]=='x'||board[row-2][column-1]=='o'){

        goto place5;
    }

        if(row-2<0){
        goto place5;
        }
        place3:
        board[row-2][column-1]='o';

    }

}


}

int gamefinish; //global variable for wincheck functions

int wincheckforx(int size,int row,int column,char board[][12]){  //default arguments

board[row][column]='X';

if(column == size -1){
    gamefinish = 1;
    return 0;
}

if(board[row-1][column] == 'x' && row > 0) {
    wincheckforx(size,row-1,column,board);
}
if(board[row-1][column+1] == 'x' && row > 0 && column < size -1){
    wincheckforx(size,row-1,column+1,board);
}
if(board[row-1][column-1] == 'x' && row > 0 && column > 0){
    wincheckforx(size,row-1,column-1,board);
}
if(board[row][column+1] == 'x' && column < size -1 ){
    wincheckforx(size,row,column+1,board);
}
if(board[row][column-1] == 'x' && column > 0){
    wincheckforx(size,row,column-1,board);
}
if(board[row+1][column] == 'x' && row < size -1){
    wincheckforx(size,row+1,column,board);
}
if(board[row+1][column+1] == 'x' && row < size -1 && column < size -1){
    wincheckforx(size,row+1,column+1,board);
}
if(board[row+1][column-1] == 'x' && row < size -1 && column > 0){
    wincheckforx(size,row+1,column-1,board);
}
if(gamefinish==0){

    board[row][column] = 'x';
}


}

int wincheckforo(int size,int row,int column,char board[][12]){

board[row][column]='O';

if(row == size -1){
    gamefinish = 1;
    return 0;
}

if(board[row-1][column] == 'o' && row > 0) {
    wincheckforo(size,row-1,column,board);
}
if(board[row-1][column+1] == 'o' && row > 0 && column < size -1){
    wincheckforo(size,row-1,column+1,board);
}
if(board[row-1][column-1] == 'o' && row > 0 && column > 0){
    wincheckforo(size,row-1,column-1,board);
}
if(board[row][column+1] == 'o' && column < size -1 ){
    wincheckforo(size,row,column+1,board);
}
if(board[row][column-1] == 'o' && column > 0){
    wincheckforo(size,row,column-1,board);
}
if(board[row+1][column] == 'o' && row < size -1){
    wincheckforo(size,row+1,column,board);
}
if(board[row+1][column+1] == 'o' && row < size -1 && column < size -1){
    wincheckforo(size,row+1,column+1,board);
}
if(board[row+1][column-1] == 'o' && row < size -1 && column > 0){
    wincheckforo(size,row+1,column-1,board);
}
if(gamefinish==0){

    board[row][column] = 'o';
}


}


int main()
{   

    int gamemode;


    cout<<"Press (1) to play user vs computer game or press (2) to play two player game."<<endl;

    cin>>gamemode;

    switch(gamemode){

    case 1 : {

    char loadarr1[100];
    char loadfilename1[30];
    int l_size;
    int l_gamemode;
    int l_turn;
    char l_board[12][12];

    cout<<"If you wanna load game enter LOAD ___.txt or press (1) to continue." <<endl;

    cin.get();
    cin.getline(loadarr1, 30);
    

    if(loadarr1[0]=='L'){                                   //LOAD command verification

        for(int i=5,j=0;i<30;i++,j++){

        loadfilename1[j]=loadarr1[i];
    }

        loadfile(l_size,l_gamemode,l_turn,l_board,loadfilename1);

        loadcheck = true; 

        cout<<endl<<"Game loaded from: "<<loadfilename1<<endl<<endl;
    }

    

    int size1;
    int turn1;

    if(loadcheck!=true){
    cout<<"Please enter size of board(6-12)"<<endl;
    cin>>size1;

    if(size1<6||size1>12){

        while(size1<6||size1>12){
        cerr<<size1<<" is invalid board size try again:"<<endl<<endl;  // cerr object

        cout<<"Please enter size of board(6-12)"<<endl;
        cin>>size1;

       }      
    }
}
    if(loadcheck==true)
    size1=l_size;

    char board1 [size1][12];


    for(int i=0;i<size1;i++){
        for(int j=0;j<size1;j++){
            board1 [i][j] = '.';
        }
    }
if(loadcheck==true){

    for(int i=0;i<size1;i++){
        for(int j=0;j<size1;j++){
            board1 [i][j] = l_board[i][j];
        }
    }

}
    printboard(size1,board1);

    char rclog1[30];
    char filename1[30];
    int row;
    decltype(row) column;                                               //decltype statement 
    auto turncount=0;                                                  // auto statement

    
    start1:

    turn1=1;

    
    cout<<"Please enter row and column (Enter SAVE ___.txt to save game)"<<endl;
    if(turncount==0)
    cin.get();
    cin.getline(rclog1, 30);

    turncount++;

    if(rclog1[0]=='S'){

        for(int i=5,j=0;i<30;i++,j++){

        filename1[j]=rclog1[i];
    }

        savefile(size1,gamemode,turn1,board1,filename1);

        cout<<"Game saved to : "<<filename1<<endl;

        goto finish;
    }
    
    if(int(rclog1[2])!=0){
        row= (int(rclog1[1]-48)*10) + int(rclog1[2])-48 - 1;

    }else{

        row=int(rclog1[1]) - 49;
    }
        column = int(rclog1[0]) - 65;
    


    if(board1[row][column]=='x'||board1[row][column]=='o'){

        cerr<<"this is invalid selection"<<endl;  // cerr object
        goto start1;
    }
    cout<<"your move:"<<endl;

    
    userplay(row,column,board1);

    turn1=2;

    
    printboard(size1,board1);

    cout<<"computer's move:"<<endl;

    
    
    botplay(size1,row,column,board1);



    printboard(size1,board1);

    int i=0;
    int k=0;
    for(i=0;i<size1;i++){

        if(board1[i][0]== 'x'){
            break;
        }
    }
        wincheckforx(size1,i,0,board1);

        if(gamefinish==1){

            goto here1;
        }

        

    for(k=0;k<size1;k++){

        if(board1[0][k]== 'o'){
            break;
        }
    }
        wincheckforo(size1,0,k,board1);

        if(gamefinish==1){

            goto here2;
        }

    
    goto start1;

            here1:
    cout<<"Player won the game:"<<endl<<endl;
            
    printboard(size1,board1);

    goto finish;
            here2:

    cout<<"Computer won the game:"<<endl<<endl;
            
    printboard(size1,board1);       

    goto finish;

    break;
}
    case 2 :{

    char loadarr2[100];
    char loadfilename2[30];
    int l_size2;
    int l_gamemode2;
    int l_turn2;
    char l_board2[12][12];
    auto turncount2=0;         //auto statement

    cout<<"If you wanna load game enter LOAD ___.txt or press (1) to continue." <<endl;

    cin.get();
    cin.getline(loadarr2, 30);
    

    if(loadarr2[0]=='L'){

        for(int i=5,j=0;i<30;i++,j++){

        loadfilename2[j]=loadarr2[i];
    }

        loadfile(l_size2,l_gamemode2,l_turn2,l_board2,loadfilename2);

        loadcheck = true; 

        cout<<endl<<"Game loaded from: "<<loadfilename2<<endl<<endl;
    }
    
    int size;
    int turn;

    if(loadcheck!=true){
    cout<<"Please enter size of board"<<endl;
    cin>>size;


    if(size<6||size>12){

        while(size<6||size>12){
        cerr<<"Invalid board size try again:"<<endl<<endl;  // cerr object

        cout<<"Please enter size of board(6-12)"<<endl;
        cin>>size;

        }
        

    }
}
    if(loadcheck==true)
    size=l_size2;

    char board [size][12];

    //board nokta ile doldurma-----------

    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            board [i][j] = '.';
        }
    }

    if(loadcheck==true){

    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            board [i][j] = l_board2[i][j];
        }
    }

}
    printboard(size,board);

    //--------------------koordinat input alma------------
    char rclog[30];
    char filename[30];
    int row1,column1,row2,column2;

    start:
    
    if(loadcheck==true&&l_turn2==2&&turncount2==0) goto player2;

    cout<<"Please enter row and column player one (Enter SAVE ___.txt to save game)"<<endl;
    
    if(turncount2==0)
    cin.get();
    cin.getline(rclog, 30);

    if(rclog[0]=='S'){

        for(int i=5,j=0;i<30;i++,j++){

        filename[j]=rclog[i];
    }

        savefile(size,gamemode,turn,board,filename);

        cout<<"Game saved to : "<<filename<<endl;

        goto finish;
    }
    

    if(int(rclog[2])!=0){
        row1 = (int(rclog[1]-48)*10) + int(rclog[2])-48 - 1;

    }else{

        row1=int(rclog[1]) - 49;
    }
        column1 = int(rclog[0]) - 65;
    


    if(board[row1][column1]=='x'||board[row1][column1]=='o'){

        cerr<<"this is invalid selection"<<endl;  // cerr object
        goto start;
    }
    

    cout<<"player one's move:"<<endl;

    userplay(row1,column1,board);

    printboard(size,board);

    turn=1;

        int a;

        for(a=0;a<size;a++){

        if(board[a][0]== 'x'){
            break;
        }
    }
        wincheckforx(size,a,0,board);

        if(gamefinish==1){

            goto here3;
        }


    player2:


    cout<<"Please enter row and column player two (Enter SAVE ___.txt to save game)"<<endl;

    
    //cin.get();
    cin.getline(rclog, 30);

    if(rclog[0]=='S'){

        for(int i=5,j=0;i<30;i++,j++){

        filename[j]=rclog[i];
    }

        savefile(size,gamemode,turn,board,filename);

        cout<<"Game saved to : "<<filename<<endl;

        goto finish;
    }
    

    if(int(rclog[2])!=0){
        row2 = (int(rclog[1]-48)*10) + int(rclog[2])-48 - 1;

    }else{

        row2 =int(rclog[1]) - 49;
    }
        column2 = int(rclog[0]) - 65;
    

    if(board[row2][column2]=='x'||board[row2][column2]=='o'){

        cerr<<"this is invalid selection"<<endl;               // cerr object
        goto player2;
    }
    cout<<"player two's:"<<endl;

    userplay_o(row2,column2,board);

    printboard(size,board);

    turn=2;

    int b;
   
    for(b=0;b<size;b++){

        if(board[0][b]== 'o'){
            break;
        }
    }
        wincheckforo(size,0,b,board);

        if(gamefinish==1){

            goto here4;
        }



        turncount2++;

    goto start;

        here3:

    cout<<"Player 1 won the game:"<<endl<<endl;
            
    printboard(size,board);

    goto finish;
        
        here4:

    cout<<"Player 2 won the game:"<<endl<<endl;
            
    printboard(size,board);       

    goto finish;

    break;
}

    }

finish:
    return 0;
}
