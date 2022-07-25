
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include<fstream>
#include<typeinfo>
#include<vector>
#include<random>
#include<exception>
#include <deque> 
#include "Hex.h"

namespace wetehex{

    bool areGamesValid(AbstractHex *ptr[50],int numberofgames){

        for(int i=0;i<numberofgames;i++){

            if(abs((ptr[i]->x_number)-(ptr[i]->o_number))>1)
                return false;

            if(ptr[i]->validgame==false)
                return false;
        }

            
            
                return true;
    }

    int AbstractHex::allmarkedcells=0;


// --------------------------------------CLASS MEMBER FUNCTIONS-----------------------------------
    Cell HexVector::lastMove(){

        if(markedcells==0)
            throw lastMoveError();

        return hexCells[lastrow][lastcolumn];

    } 

    Cell HexArray1D::lastMove(){

        if(markedcells==0)
            throw lastMoveError();

        return hexCells[lastrow * size + lastcolumn];

    } 


    bool AbstractHex::operator==(const AbstractHex &other){

        for(int i = 0; i < size; i++)
        {
         for(int j = 0; j < size; j++)

            {   
                if((*this)(i,j).celltype!=other(i,j).celltype)
                    return false;
            }
        } 

        return true;

    }

    bool AbstractHex::isEnd(int gamefinish){

        if(gamefinish==1)
            return true;
        else
            return false;

    }

    bool HexVector::isempty(int row,int column){


        return hexCells[row][column].celltype!=empty;
    }

    bool HexArray1D::isempty(int row,int column){


        return hexCells[row * size + column].celltype!=empty;
    }

    void HexVector::play(int row,int column,char playtype){
    
    allmarkedcells++;
    markedcells++;

    lastrow = row;
    lastcolumn = column;

    hexCells[row][column].celltype=playtype;
}

    void HexArray1D::play(int row,int column,char playtype){
    
    allmarkedcells++;
    markedcells++;

    lastrow = row;
    lastcolumn = column;

    hexCells[row * size + column].celltype=playtype;
}

	void HexVector::play(){

    allmarkedcells++;
    markedcells++;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> randomint(0,size-1); // distribution in range [1, 6]

    int row = randomint(rng);
    int column = randomint(rng);

    lastrow = row;
    lastcolumn = column;

    if(hexCells[row][column].celltype!=empty){
            
            row = randomint(rng);
            column = randomint(rng);

        while(hexCells[row][column].celltype!=empty){

            row = randomint(rng);
            column = randomint(rng);
        }

        hexCells[row][column].celltype=usero;

    }else{

        hexCells[row][column].celltype=usero;
    }
    
}
    void HexArray1D::play(){

    allmarkedcells++;
    markedcells++;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> randomint(0,size-1); // distribution in range [1, 6]

    int row = randomint(rng);
    int column = randomint(rng);

    lastrow = row;
    lastcolumn = column;

    if(hexCells[row * size + column].celltype!=empty){
            
            row = randomint(rng);
            column = randomint(rng);

        while(hexCells[row * size + column].celltype!=empty){

            row = randomint(rng);
            column = randomint(rng);
        }

        hexCells[row * size + column].celltype=usero;

    }else{

        hexCells[row * size + column].celltype=usero;
    }
    
}

	void HexVector::setSize(int size){

        hexCells.resize(size*size); 

        for(int i = 0; i < size; i++)
        {
         for(int j = 0; j < size; j++)

            {   
                hexCells[i].push_back(Cell());
                hexCells[i][j].row=i;
                hexCells[i][j].column=j;
                hexCells[i][j].celltype=empty;
            
            }
        }   

    }

    void HexArray1D::setSize(int size){

        hexCells = (Cell*) malloc((size*size) * sizeof(Cell));


        for(int i = 0; i < size; i++)
        {
         for(int j = 0; j < size; j++)

            {   
                hexCells[i * size + j].row=i;
                hexCells[i * size + j].column=j;
                hexCells[i * size + j].celltype=empty;
            }
        }   

    }

    void HexVector::reset(int size){

        markedcells =0;

        for(int i = 0; i < size; i++)
        {
         for(int j = 0; j < size; j++)

            {   
                hexCells[i][j].celltype=empty;
            
            }
        }  
    }

    void HexArray1D::reset(int size){

        markedcells =0;

        for(int i = 0; i < size; i++)
        {
         for(int j = 0; j < size; j++)

            {   
                hexCells[i * size + j].celltype=empty;
            
            }
        }  
    }

	void HexVector::print(int size){


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

    void HexArray1D::print(int size){


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
            cout<<hexCells[i * size + j].celltype<<"  ";
           
        }
        cout<<endl;
    }

}

int AbstractHex::returnsize(int size){

	return size;
}



int HexVector::scan_x(int size){

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

int HexArray1D::scan_x(int size){

int i;
bool check=false;

for(i=0;i<size;i++){

    if(hexCells[i * size +0].celltype==userx){
            check=true;
            break;
        }
}

if(check==true)
return i;
else
return -1;

}

int HexVector::scan_y(int size){

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

int HexArray1D::scan_y(int size){

int i;
bool check=false;

for(i=0;i<size;i++){

    if(hexCells[0 * size + i].celltype==usero){
            check=true;
            break;
        }
}

if(check==true)
return i;
else
return -1;

}

int HexVector::wincheckforx(int size,int row,int column){  //default arguments

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

int HexArray1D::wincheckforx(int size,int row,int column){  //default arguments

hexCells[row * size + column].celltype='X';


if(column == size -1){
    gamefinish = 1;
    return 0;
}

if(row > 0){
if(hexCells[(row-1) * size + column].celltype == 'x') {wincheckforx(size,row-1,column); }
}

if(row > 0 && column < size -1){
if(hexCells[(row-1) * size + (column+1)].celltype == 'x'){wincheckforx(size,row-1,column+1);}
}    

if(row > 0 && column > 0){
if(hexCells[(row-1) * size + (column-1)].celltype == 'x'){wincheckforx(size,row-1,column-1);}
}    

if(column < size -1 ){
if(hexCells[row * size + (column+1)].celltype == 'x'){wincheckforx(size,row,column+1);}
}    

if(column > 0){
if(hexCells[row * size + (column-1)].celltype == 'x'){wincheckforx(size,row,column-1);}
}    
if(row < size -1){
if(hexCells[(row+1) * size + column].celltype == 'x'){wincheckforx(size,row+1,column);}
}

if(row < size -1 && column < size -1){
if(hexCells[(row+1) * size + (column+1)].celltype == 'x'){wincheckforx(size,row+1,column+1);}
}

if(row < size -1 && column > 0){
if(hexCells[(row+1) * size + (column-1)].celltype == 'x' && row < size -1 && column > 0){wincheckforx(size,row+1,column-1);}
}

if(gamefinish==0){

    hexCells[row * size + column].celltype = 'x';
}


}

int HexVector::wincheckforo(int size,int row,int column){

hexCells[row][column].celltype='O';


if(row == size -1){
    gamefinish = 1;
    return 0;
}

if(row > 0){
if(hexCells[row-1][column].celltype == 'o') {wincheckforo(size,row-1,column);}
}

if(row > 0 && column < size -1){
if(hexCells[row-1][column+1].celltype == 'o'){wincheckforo(size,row-1,column+1);}
}    

if(row > 0 && column > 0){
if(hexCells[row-1][column-1].celltype == 'o'){wincheckforo(size,row-1,column-1);}
}    

if(column < size -1 ){
if(hexCells[row][column+1].celltype == 'o'){wincheckforo(size,row,column+1);}
}    

if(column > 0){
if(hexCells[row][column-1].celltype == 'o'){wincheckforo(size,row,column-1);}
}    
if(row < size -1){
if(hexCells[row+1][column].celltype == 'o'){wincheckforo(size,row+1,column);}
}

if(row < size -1 && column < size -1){
if(hexCells[row+1][column+1].celltype == 'o'){wincheckforo(size,row+1,column+1);}
}

if(row < size -1 && column > 0){
if(hexCells[row+1][column-1].celltype == 'o' && row < size -1 && column > 0){wincheckforo(size,row+1,column-1);}
}

if(gamefinish==0){

    hexCells[row][column].celltype = 'o';
}

}

int HexArray1D::wincheckforo(int size,int row,int column){

hexCells[row * size + column].celltype='O';


if(row == size -1){
    gamefinish = 1;
    return 0;
}

if(row > 0){
if(hexCells[(row-1) * size + column].celltype == 'o') {wincheckforo(size,row-1,column); }
}

if(row > 0 && column < size -1){
if(hexCells[(row-1) * size + (column+1)].celltype == 'o'){wincheckforo(size,row-1,column+1);}
}    

if(row > 0 && column > 0){
if(hexCells[(row-1) * size + (column-1)].celltype == 'o'){wincheckforo(size,row-1,column-1);}
}    

if(column < size -1 ){
if(hexCells[row * size + (column+1)].celltype == 'o'){wincheckforo(size,row,column+1);}
}    

if(column > 0){
if(hexCells[row * size + (column-1)].celltype == 'o'){wincheckforo(size,row,column-1);}
}    
if(row < size -1){
if(hexCells[(row+1) * size + column].celltype == 'o'){wincheckforo(size,row+1,column);}
}

if(row < size -1 && column < size -1){
if(hexCells[(row+1) * size + (column+1)].celltype == 'o'){wincheckforo(size,row+1,column+1);}
}

if(row < size -1 && column > 0){
if(hexCells[(row+1) * size + (column-1)].celltype == 'o' && row < size -1 && column > 0){wincheckforo(size,row+1,column-1);}
}

if(gamefinish==0){

    hexCells[row *size + column].celltype = 'o';
}

}


void AbstractHex::asciconverter(char rclog[30],int &row,int &column){

	if(int(rclog[2])!=0){
        row= (int(rclog[1]-48)*10) + int(rclog[2])-48 - 1;

    	}else
        row=int(rclog[1]) - 49;
    
        column = int(rclog[0]) - 65;

}


void HexVector::writeToFile(int size,int gamemode,int playerturn,char filename[30]){  //constant parameter by reference

    ofstream myfile(filename);

    myfile<<size<<" "<<gamemode<<" "<<playerturn<<endl;

    int i;
    int j;                                                                                             //decltype statement

    for(i=0;i<size;i++){
        for(j=0;j<size;j++){

            myfile<<i<<" "<<j<<" "<<hexCells[i][j].celltype<<endl;
        }
    }

}

void HexArray1D::writeToFile(int size,int gamemode,int playerturn,char filename[30]){  //constant parameter by reference

    ofstream myfile(filename);

    myfile<<size<<" "<<gamemode<<" "<<playerturn<<endl;

    int i;
    int j;                                                                                             //decltype statement

    for(i=0;i<size;i++){
        for(j=0;j<size;j++){

            myfile<<i<<" "<<j<<" "<<hexCells[i * size + j].celltype<<endl;
        }
    }

}


void HexVector::readFromFile(int &size,int &gamemode,int &playerturn,char filename[30]){  //parameter by reference

    ifstream myfile(filename);

    int i=0;
    int row,column;
    int loadx_number=0,loado_number=0;

  
    while(myfile){

        if(i==0){
         myfile>>size>>gamemode>>playerturn;
         setSize(size);
        }

        if(i!=0){
        myfile>>row>>column>>hexCells[row][column].celltype;

        if(hexCells[row][column].celltype=='x')
            loadx_number++;
        if(hexCells[row][column].celltype=='o')
            loado_number++;
        if(hexCells[row][column].celltype!='.'&&hexCells[row][column].celltype!='x'&&hexCells[row][column].celltype!='o')
            validgame = false;    
        }
    
        i++;
    }

    x_number = loadx_number;
    o_number = loado_number;

}

void HexArray1D::readFromFile(int &size,int &gamemode,int &playerturn,char filename[30]){  //parameter by reference

    ifstream myfile(filename);

    int i=0;
    int row,column;
    int loadx_number=0,loado_number=0;
  
    while(myfile){

        if(i==0){
         myfile>>size>>gamemode>>playerturn;
         setSize(size);
        }

        if(i!=0){
         myfile>>row>>column>>hexCells[row * size + column].celltype;

        if(hexCells[row * size + column].celltype=='x')
            loadx_number++;
        if(hexCells[row * size + column].celltype=='o')
            loado_number++;
        if(hexCells[row * size + column].celltype!='.'&&hexCells[row * size + column].celltype!='x'&&hexCells[row * size + column].celltype!='o')
            validgame = false;    
        }

        i++;
    }

    x_number = loadx_number;
    o_number = loado_number;

}

void AbstractHex::playGame(){

		char rclog[30];
		char filename[30];
		int row,column;
		int turncount=0;
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

		setSize(size);		

		cout<<"Press (1) to play user vs computer game or press (2) to play two player game."<<endl;
		cin>>gamemode;

		cout<<"If you wanna load game enter LOAD ___.txt or press (1) to continue." <<endl;

		cin.get();
    	cin.getline(loadlog, 30);

    	if(loadlog[0]=='L'){                                   //LOAD command verification

        for(int i=5,j=0;i<30;i++,j++){

        filename[j]=loadlog[i];
    		}

    	
        readFromFile(size,gamemode,turn,filename);

        //loadcheck = true; 

        cout<<endl<<"Game loaded from: "<<filename<<endl<<endl;
    		}


	if(gamemode==1){

		
		print(size);

		while(1){

		turn=1;
		here:	
		cout<<"Please enter row and column(A1,B3..etc)(Enter SAVE ___.txt to save and exit the game and only 'Q' to exit.)"<<endl;
		cout<<"Please enter XUNDO(prefix) or UNDOX(postfix) if you wanna undo steps"<<endl;

		//if(turncount==0)
    	//cin.get();
    	cin.getline(rclog, 30);
    	turncount++;

        if(rclog[0]=='Q'){
            break;
        }

    	if(rclog[0]=='S'){

        for(int i=5,j=0;i<30;i++,j++){

        filename[j]=rclog[i];
    			}

        writeToFile(size,gamemode,turn,filename);

        cout<<endl<<"Game saved to : "<<filename<<endl;
        cout<<"See you !!!"<<endl;

       	break; 
    	}
		
    	asciconverter(rclog,row,column);

        if(isempty(row,column)){

        cerr<<"this is invalid selection"<<endl;  // cerr object

        cout<<"Please enter row and column(A1,B3..etc)"<<endl;

        cin.getline(rclog, 30);

        asciconverter(rclog,row,column);

    }
		
    	cout<<"your move:"<<endl;
    
        x_number++;
    	play(row,column,userx);
		

    	print(size);

    	cout<<"computer's move:"<<endl;
    
    	o_number++;
    	play();
    	
    	print(size);

    	int a,b;

    	a=scan_x(size);

    	if(turncount>size-1&&a!=-1)
    	wincheckforx(size,a,0);
	

    	if(gamefinish==1){

    	cout<<"Player won the game:"<<endl<<endl;
            
    	print(size);
    		break;
    	}

    	b=scan_y(size);

    	if(turncount>size-1&&a!=-1)
    	wincheckforo(size,0,b);

    	if(gamefinish==1){
		cout<<"Computer won the game:"<<endl<<endl;
            
    	print(size);

    		break;
    	}


	}

  }
		
		if(gamemode==2){

		int a,b;

		print(size);

		while(1){

		turncount++;
		here1:
		turn=1;
		cout<<"Please enter row and column player one(A1,B3..etc)(Enter SAVE ___.txt to save and exit the game and only 'Q' to exit.)"<<endl;
		cout<<"Please enter XUNDO(prefix) or UNDOX(postfix) if you wanna undo steps"<<endl;

    	cin.getline(rclog, 30);

    	if(rclog[0]=='Q'){
    		break;
    	}
    	if(rclog[0]=='S'){

        for(int i=5,j=0;i<30;i++,j++){

        filename[j]=rclog[i];
    			}

        writeToFile(size,gamemode,turn,filename);

        cout<<endl<<"Game saved to : "<<filename<<endl;
        cout<<"See you !!!"<<endl;

       	break; 
    	}

    	asciconverter(rclog,row,column);

        if(isempty(row,column)){

        cerr<<"this is invalid selection"<<endl;  // cerr object

        cout<<"Please enter row and column player one(A1,B3..etc)"<<endl;

        cin.getline(rclog, 30);

        asciconverter(rclog,row,column);

    }
    	cout<<"Player one's move:"<<endl;

    	x_number++;
    	play(row,column,userx);

    	print(size);

    	a=scan_x(size);

    	if(turncount>size-1&&a!=-1)
    	wincheckforx(size,a,0);
		
    	if(gamefinish==1){

    	cout<<"Player one won the game:"<<endl<<endl;
            
    	print(size);
    		break;
    	}
    	here2:
    	turn=2;
    	cout<<"Please enter row and column player two(A1,B3..etc)(Enter SAVE ___.txt to save and exit the game and only 'Q' to exit.)"<<endl;
    	cout<<"Please enter XUNDO(prefix) or UNDOX(postfix) if you wanna undo steps"<<endl;

    	 cin.getline(rclog, 30);

    	 if(rclog[0]=='Q'){
    		break;
    	}
    	if(rclog[0]=='S'){

        for(int i=5,j=0;i<30;i++,j++){

        filename[j]=rclog[i];
    			}

        writeToFile(size,gamemode,turn,filename);

        cout<<endl<<"Game saved to : "<<filename<<endl;
        cout<<"See you !!!"<<endl;

       	break; 
    	}

    	asciconverter(rclog,row,column);

        if(isempty(row,column)){

        cerr<<"this is invalid selection"<<endl;  // cerr object

        cout<<"Please enter row and column two(A1,B3..etc)"<<endl;

        cin.getline(rclog, 30);

        asciconverter(rclog,row,column);

    }
    	cout<<"Player two's move:"<<endl;

        o_number++;
    	play(row,column,usero);

    	print(size);

    	b=scan_y(size);

    	if(turncount>size-1&&a!=-1)
    	wincheckforo(size,0,b);

    	if(gamefinish==1){
		cout<<"Player two won the game:"<<endl<<endl;
            
    	print(size);

    		break;
    	}

		}

	}

}
    

}// wetehex 