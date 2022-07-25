
#include <iostream>
#include<fstream>
#include<typeinfo>
#include<vector>
#include<random>
#include "Hex.h"

int Hex::allmarkedcells=0;
//---------------------------------------GLOBAL FUNCTIONS-----------------------------------------
ostream & operator << (ostream &out, const Hex &h){

	out<<h.size;

	return out;

} 


istream & operator >> (istream &in,Hex &h){

	in>>h.size;

	return in;

} 

bool operator== (const Hex &h1,const Hex &h2){

	return (h1.markedcells==h2.markedcells);

}

// --------------------------------------CLASS MEMBER FUNCTIONS-----------------------------------

	
	int Hex::scoreuser(int size,int row,int column){

	if(row > 0){
if(hexCells[row-1][column].celltype == 'x') {score_x = score_x + 10;}
}

if(row > 0 && column < size -1){
if(hexCells[row-1][column+1].celltype == 'x'){score_x = score_x + 10;}
}    

if(row > 0 && column > 0){
if(hexCells[row-1][column-1].celltype == 'x'){score_x = score_x + 10;}
}    

if(column < size -1 ){
if(hexCells[row][column+1].celltype == 'x'){score_x = score_x + 10;}
}    

if(column > 0){
if(hexCells[row][column-1].celltype == 'x'){score_x = score_x + 10;}
}    
if(row < size -1){
if(hexCells[row+1][column].celltype == 'x'){score_x = score_x + 10;}
}

if(row < size -1 && column < size -1){
if(hexCells[row+1][column+1].celltype == 'x'){score_x = score_x + 10;}
}

if(row < size -1 && column > 0){
if(hexCells[row+1][column-1].celltype == 'x' && row < size -1 && column > 0){score_x = score_x + 10;}
}
	
}

int Hex::scorecomputer(int size,int row,int column){

	if(row > 0){
if(hexCells[row-1][column].celltype == 'o') {score_o = score_o + 10;}
}

if(row > 0 && column < size -1){
if(hexCells[row-1][column+1].celltype == 'o'){score_o = score_o + 10;}
}    

if(row > 0 && column > 0){
if(hexCells[row-1][column-1].celltype == 'o'){score_o = score_o + 10;}
}    

if(column < size -1 ){
if(hexCells[row][column+1].celltype == 'o'){score_o = score_o + 10;}
}    

if(column > 0){
if(hexCells[row][column-1].celltype == 'o'){score_o = score_o + 10;}
}    
if(row < size -1){
if(hexCells[row+1][column].celltype == 'o'){score_o = score_o + 10;}
}

if(row < size -1 && column < size -1){
if(hexCells[row+1][column+1].celltype == 'o'){score_o = score_o + 10;}
}

if(row < size -1 && column > 0){
if(hexCells[row+1][column-1].celltype == 'o' && row < size -1 && column > 0){score_o = score_o + 10;}
}
	
}
	

	Hex Hex::operator-- (){

	
	hexCells[rowarr[markedcells-1]][columnarr[markedcells-1]].celltype=empty;
   	markedcells--;
	
	return *this;

    }

    Hex Hex::operator-- (int){

	
	hexCells[rowarr[markedcells-1]][columnarr[markedcells-1]].celltype=empty;
   	markedcells--;
	
	return *this;

    }

    Hex::Cell& Hex::play(int row,int column,char playtype){
	
	allmarkedcells++;
	markedcells++;

    Hex::Cell temp;

    temp.celltype = playtype;

    
	
	rowarr[markedcells-1] = row;
    columnarr[markedcells-1] = column;

	return hexCells[row][column]=temp;
}

	Hex::Cell& Hex::play(){

	allmarkedcells++;
	markedcells++;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> randomint(0,size-1); // distribution in range [1, 6]

    int row = randomint(rng);
    int column = randomint(rng);


    rowarr[markedcells-1] = row;

    columnarr[markedcells-1] = column;

    Hex::Cell temp;

    temp.celltype = usero;

    if(hexCells[row][column].celltype!=empty){
			
			row = randomint(rng);
    		column = randomint(rng);

    	while(hexCells[row][column].celltype!=empty){

    		row = randomint(rng);
    		column = randomint(rng);
    	}

        return hexCells[row][column]=temp;

    }else{

        return hexCells[row][column]=temp;
    }
	
}

	void Hex::createboard(int size){

		hexCells = new Cell* [size];

        for (int i = 0; i < size; i++)
        hexCells[i] = new Cell [size];

		for(int i = 0; i < size; i++)
    	{
       	 for(int j = 0; j < size; j++)

        	{	
        		
        		hexCells[i][j].row=i;
        		hexCells[i][j].column=j;
        		hexCells[i][j].celltype=empty;
            
        	}
    	}	

	}

	void Hex::printboard(int size){


		for(int i=0;i<size;i++){

        cout<<' '<<' '<< char(97+i);
     		}
     	cout<<endl;

		for(int i = 0; i < size; i++){

		cout << i+1 <<' ';

		if(i>8){
			cout << string(i, ' ');

		}else
		cout << string(i+1, ' ');
			
        for(int j = 0; j < size; j++)
        {
       		cout<<hexCells[i][j].celltype<<"  ";
           
        }
        cout<<endl;
    }
	

}

int Hex::returnsize(int size){

	return size;
}



int Hex::scan_x(int size){

int i;
bool check=false;

for(i=0;i<size;i++){

	if(hexCells[i][0].celltype==userx){
			check=true;
            break;
        }
}

if(check==true)
return i;
else
return -1;

}

int Hex::scan_y(int size){

int i;
bool check=false;

for(i=0;i<size;i++){

	if(hexCells[0][i].celltype==usero){
			check=true;
            break;
        }
}

if(check==true)
return i;
else
return -1;

}

int Hex::wincheckforx(int size,int row,int column){  //default arguments

hexCells[row][column].celltype='X';


if(column == size -1){
    gamefinish = 1;
    return 0;
}

if(row > 0){
if(hexCells[row-1][column].celltype == 'x') {wincheckforx(size,row-1,column); }
}

if(row > 0 && column < size -1){
if(hexCells[row-1][column+1].celltype == 'x'){wincheckforx(size,row-1,column+1);}
}    

if(row > 0 && column > 0){
if(hexCells[row-1][column-1].celltype == 'x'){wincheckforx(size,row-1,column-1);}
}    

if(column < size -1 ){
if(hexCells[row][column+1].celltype == 'x'){wincheckforx(size,row,column+1);}
}    

if(column > 0){
if(hexCells[row][column-1].celltype == 'x'){wincheckforx(size,row,column-1);}
}    
if(row < size -1){
if(hexCells[row+1][column].celltype == 'x'){wincheckforx(size,row+1,column);}
}

if(row < size -1 && column < size -1){
if(hexCells[row+1][column+1].celltype == 'x'){wincheckforx(size,row+1,column+1);}
}

if(row < size -1 && column > 0){
if(hexCells[row+1][column-1].celltype == 'x' && row < size -1 && column > 0){wincheckforx(size,row+1,column-1);}
}

if(gamefinish==0){

    hexCells[row][column].celltype = 'x';
}


}

int Hex::wincheckforo(int size,int row,int column){

hexCells[row][column].celltype='O';


if(row == size -1){
    gamefinish = 1;
    return 0;
}

if(row > 0){
if(hexCells[row-1][column].celltype == 'o') {wincheckforx(size,row-1,column);}
}

if(row > 0 && column < size -1){
if(hexCells[row-1][column+1].celltype == 'o'){wincheckforx(size,row-1,column+1);}
}    

if(row > 0 && column > 0){
if(hexCells[row-1][column-1].celltype == 'o'){wincheckforx(size,row-1,column-1);}
}    

if(column < size -1 ){
if(hexCells[row][column+1].celltype == 'o'){wincheckforx(size,row,column+1);}
}    

if(column > 0){
if(hexCells[row][column-1].celltype == 'o'){wincheckforx(size,row,column-1);}
}    
if(row < size -1){
if(hexCells[row+1][column].celltype == 'o'){wincheckforx(size,row+1,column);}
}

if(row < size -1 && column < size -1){
if(hexCells[row+1][column+1].celltype == 'o'){wincheckforx(size,row+1,column+1);}
}

if(row < size -1 && column > 0){
if(hexCells[row+1][column-1].celltype == 'o' && row < size -1 && column > 0){wincheckforx(size,row+1,column-1);}
}

if(gamefinish==0){

    hexCells[row][column].celltype = 'o';
}

}
void Hex::asciconverter(char rclog[30],int &row,int &column){

	if(int(rclog[2])!=0){
        row= (int(rclog[1]-48)*10) + int(rclog[2])-48 - 1;

    	}else
        row=int(rclog[1]) - 49;
    
        column = int(rclog[0]) - 65;

}


void Hex::savefile(int size,int gamemode,int playerturn,char filename[30]){  //constant parameter by reference

    ofstream myfile(filename);

    myfile<<*this<<" "<<gamemode<<" "<<playerturn<<endl;

    int i;
    int j;                                                                                             //decltype statement

    for(i=0;i<size;i++){
        for(j=0;j<size;j++){

            myfile<<i<<" "<<j<<" "<<hexCells[i][j].celltype<<endl;
        }
    }

}


void Hex::loadfile(int &size,int &gamemode,int &playerturn,char filename[30]){  //parameter by reference

    ifstream myfile(filename);

    int i=0;
    int row,column;

  
    while(myfile){

        if(i==0){
	     myfile>>*this>>gamemode>>playerturn;
	     createboard(size);
        }


        if(i!=0)
        myfile>>row>>column>>hexCells[row][column].celltype;

        i++;
    }

}

void Hex::playGame(){

		int gamemode;
		//int size;
		char rclog[30];
		char filename[30];
		int row,column;
		int turncount=0;
		int turn;
		char loadlog[30];

		cout<<"Please enter size of board(least 5x5)"<<endl;
		cin>>size;

		if(size<5){

        while(size<5){
        cerr<<size<<" is invalid board size try again:"<<endl<<endl;  // cerr object

       	cout<<"Please enter size of board(least 5x5)"<<endl;
        cin>>size;
       			}      
    		}

		createboard(size);		

		cout<<"Press (1) to play user vs computer game or press (2) to play two player game."<<endl;
		cin>>gamemode;

		cout<<"If you wanna load game enter LOAD ___.txt or press (1) to continue." <<endl;

		cin.get();
    	cin.getline(loadlog, 30);

    	if(loadlog[0]=='L'){                                   //LOAD command verification

        for(int i=5,j=0;i<30;i++,j++){

        filename[j]=loadlog[i];
    		}

    	
        loadfile(size,gamemode,turn,filename);

        //loadcheck = true; 

        cout<<endl<<"Game loaded from: "<<filename<<endl<<endl;
    		}


	if(gamemode==1){

		
		printboard(size);

		while(1){

		turn=1;
		here:	
		cout<<"Please enter row and column(A1,B3..etc)(Enter SAVE ___.txt to save and exit the game and only 'Q' to exit.)"<<endl;
		cout<<"Please enter XUNDO(prefix) or UNDOX(postfix) if you wanna undo steps"<<endl;

		//if(turncount==0)
    	//cin.get();
    	cin.getline(rclog, 30);
    	turncount++;

    	if(rclog[0]=='X'){

    		--(*this);

    		if(markedcells%2==0)
    		cout<<"your move:"<<endl;
    		else
    		cout<<"computer's move:"<<endl;	
    		printboard(size);
    		goto here;
    	}
    	if(rclog[0]=='U'){

    		(*this)--;

    		if(markedcells%2==0)
    		cout<<"your move:"<<endl;
    		else
    		cout<<"computer's move:"<<endl;	
    		printboard(size);
    		goto here;
    	}

    	if(rclog[0]=='Q'){
    		break;
    	}

    	if(rclog[0]=='S'){

        for(int i=5,j=0;i<30;i++,j++){

        filename[j]=rclog[i];
    			}

        savefile(size,gamemode,turn,filename);

        cout<<endl<<"Game saved to : "<<filename<<endl;
        cout<<"See you !!!"<<endl;

       	break; 
    	}
		
		

    	asciconverter(rclog,row,column);

        if(hexCells[row][column].celltype!=empty){

        cerr<<"this is invalid selection"<<endl;  // cerr object

        cout<<"Please enter row and column(A1,B3..etc)"<<endl;

        cin.getline(rclog, 30);

        asciconverter(rclog,row,column);

    }
		

    	cout<<"your move:"<<endl;
    	cout<<"your score:"<<score_x<<endl;

    	//userturn=true;
    	play(row,column,userx);
		

    	printboard(size);

    	cout<<"computer's move:"<<endl;
		cout<<"computer's score:"<<score_o<<endl;

    	//userturn=false;
    	
    	Cell temp = play();
    	


    	printboard(size);

    	int a,b;

    	a=scan_x(size);

    	if(turncount>size-1&&a!=-1)
    	wincheckforx(size,a,0);
    	scoreuser(size,a,0);
		
		//cout<<a<<endl;

    	if(gamefinish==1){

    	cout<<"Player won the game:"<<endl<<endl;
            
    	printboard(size);
    		break;
    	}

    	b=scan_y(size);
    	//cout<<b<<endl;

    	if(turncount>size-1&&a!=-1)
    	wincheckforo(size,0,b);
    	scorecomputer(size,0,b);

    	if(gamefinish==1){
		cout<<"Computer won the game:"<<endl<<endl;
            
    	printboard(size);

    		break;
    	}


	}

  }
		
		if(gamemode==2){

		int a,b;

		printboard(size);

		while(1){

		turncount++;
		here1:
		turn=1;
		cout<<"Please enter row and column player one(A1,B3..etc)(Enter SAVE ___.txt to save and exit the game and only 'Q' to exit.)"<<endl;
		cout<<"Please enter XUNDO(prefix) or UNDOX(postfix) if you wanna undo steps"<<endl;
		//if(turncount==0)
    	//cin.get();
    	cin.getline(rclog, 30);

    	if(rclog[0]=='X'){

    		--(*this);

    		if(markedcells%2==0)
    		cout<<"Player one's move:"<<endl;
    		else
    		cout<<"Player two's move:"<<endl;
    		printboard(size);
    		goto here2;
    	}
    	if(rclog[0]=='U'){

    		(*this)--;

    		if(markedcells%2==0)
    		cout<<"your move:"<<endl;
    		else
    		cout<<"computer's move:"<<endl;	
    		printboard(size);
    		goto here;
    	}

    	if(rclog[0]=='Q'){
    		break;
    	}
    	if(rclog[0]=='S'){

        for(int i=5,j=0;i<30;i++,j++){

        filename[j]=rclog[i];
    			}

        savefile(size,gamemode,turn,filename);

        cout<<endl<<"Game saved to : "<<filename<<endl;
        cout<<"See you !!!"<<endl;

       	break; 
    	}

    	asciconverter(rclog,row,column);

        if(hexCells[row][column].celltype!=empty){

        cerr<<"this is invalid selection"<<endl;  // cerr object

        cout<<"Please enter row and column player one(A1,B3..etc)"<<endl;

        cin.getline(rclog, 30);

        asciconverter(rclog,row,column);

    }
    	cout<<"Player one's move:"<<endl;

    	//userturn=true;
    	play(row,column,userx);

    	printboard(size);

    	a=scan_x(size);

    	if(turncount>size-1&&a!=-1)
    	wincheckforx(size,a,0);
		
		//cout<<a<<endl;

    	if(gamefinish==1){

    	cout<<"Player one won the game:"<<endl<<endl;
            
    	printboard(size);
    		break;
    	}
    	here2:
    	turn=2;
    	cout<<"Please enter row and column player two(A1,B3..etc)(Enter SAVE ___.txt to save and exit the game and only 'Q' to exit.)"<<endl;
    	cout<<"Please enter XUNDO(prefix) or UNDOX(postfix) if you wanna undo steps"<<endl;

    	 cin.getline(rclog, 30);

    	 if(rclog[0]=='X'){

    		--(*this);

    		if(markedcells%2==0)
    		cout<<"Player one's move:"<<endl;
    		else
    		cout<<"Player two's move:"<<endl;
    		printboard(size);
    		goto here1;
    	}
    	if(rclog[0]=='U'){

    		(*this)--;

    		if(markedcells%2==0)
    		cout<<"your move:"<<endl;
    		else
    		cout<<"computer's move:"<<endl;	
    		printboard(size);
    		goto here;
    	}

    	 if(rclog[0]=='Q'){
    		break;
    	}
    	if(rclog[0]=='S'){

        for(int i=5,j=0;i<30;i++,j++){

        filename[j]=rclog[i];
    			}

        savefile(size,gamemode,turn,filename);

        cout<<endl<<"Game saved to : "<<filename<<endl;
        cout<<"See you !!!"<<endl;

       	break; 
    	}

    	asciconverter(rclog,row,column);

        if(hexCells[row][column].celltype!=empty){

        cerr<<"this is invalid selection"<<endl;  // cerr object

        cout<<"Please enter row and column two(A1,B3..etc)"<<endl;

        cin.getline(rclog, 30);

        asciconverter(rclog,row,column);

    }
    	cout<<"Player two's move:"<<endl;

    	play(row,column,usero);

    	printboard(size);


    	b=scan_y(size);
    	//cout<<b<<endl;

    	if(turncount>size-1&&a!=-1)
    	wincheckforo(size,0,b);

    	if(gamefinish==1){
		cout<<"Player two won the game:"<<endl<<endl;
            
    	printboard(size);

    		break;
    	}

		}

	}

}

 bool Hex::comparegames(int markedcells,Hex game2){

    if(markedcells>game2.markedcells)
        return true;
    else
        return false;

 }