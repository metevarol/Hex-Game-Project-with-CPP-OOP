#include <iostream>
#include<fstream>
#include<typeinfo>
#include<vector>
#include<random>


using namespace std;

int gamefinish=0;
bool loadcheck=false;

enum celltype{

   userx = 'x', usero = 'o' , empty = '.'
};

class Hex{

	public:

	static int allmarkedcells;

	int markedcells;

	inline void createboard(int size); 
	inline void printboard(int size);
	void play(int row,int column,char playtype);
	void play(int size);
	int scan_x(int size);
	int scan_y(int size);
	int wincheckforx(int size,int row,int column);
	int wincheckforo(int size,int row,int column);
	void savefile(int size,int gamemode,int playerturn,char filename[30]);
	void loadfile(int &size,int &gamemode,int &playerturn,char filename[30]);
	void asciconverter(char rclog[30],int &row,int &column);
	void playGame();
    bool comparegames(int markedcells,Hex game2);
    inline int returnsize(int size);  //return size of board (width and height)

    Hex(int x){                       //constructor

        markedcells=x;
    }

	private:

	class Cell{

	int row;
	int column;
	char celltype;

	friend void Hex::createboard(int size);
	friend void Hex::printboard(int size);
	friend void Hex::play(int row,int column,char playtype);
	friend void Hex::play(int size);
	friend int Hex::scan_x(int size);
	friend int Hex::scan_y(int size);
	friend int Hex::wincheckforx(int size,int row,int column);
	friend int Hex::wincheckforo(int size,int row,int column);
	friend void Hex::playGame();
	friend void Hex::savefile(int size,int gamemode,int playerturn,char filename[30]);
	friend void Hex::loadfile(int &size,int &gamemode,int &playerturn,char filename[30]);


	};	

	vector< vector<Cell> > hexCells ;

};


// --------------------------------------MAIN FUNCTION-------------------------------------
int Hex::allmarkedcells=0;

int main(){

	int gamenumber;
	int menu;

	cout<<"**************WELCOME TO HEX GAME***************"<<endl<<endl;
	cout<<"How many games do you want to open ?(Least 5!)"<<endl;
	cin>>gamenumber;
	while(gamenumber<5){
			cout<<"You can open at least 5 games..."<<endl;	
			cin>>gamenumber;
	}

	//vector<Hex> vec(gamenumber);

    vector<Hex> vec;

    for(int i=0;i<5;i++)
        vec.push_back(Hex(0));


while(1){
	cout<<"------MENU------"<<endl;
	cout<<"1.Start new game"<<endl;
	cout<<"2.Select active game and play "<<"("<<vec.size()+1<<" games are active now)"<<endl;
    cout<<"3.Compare two games"<<endl;
	cout<<"4.See the marked cells in all games"<<endl;
	cout<<"5.Exit"<<endl<<endl;
	cout<<"Please choose one: "<<endl;

	cin>>menu;

	if(menu==1){
		Hex newgame(0);
		newgame.playGame();

		vec.push_back(newgame);
        cout<<endl<<endl;
	}
	if(menu==2){
	int selection;
	cout<<"Please select game:"<<endl;

	for(int i=0;i<vec.size();i++){

			cout<<i+1<<'.'<<"Game "<<i+1<<endl;
	}

	cin>>selection;

	vec[selection-1].playGame();
    cout<<endl<<endl;
	}

    if(menu==3){

        int game1,game2;
        bool check;

        for(int i=0;i<vec.size();i++)
        cout<<i+1<<'.'<<"Game "<<i+1<<endl;
        cout<<endl;

        cout<<"Select two games to compare(Enter with space: '1 2' '2 3' '2 4' etc.)"<<endl;
        cin>>game1>>game2;

        check=vec[game1-1].comparegames(vec[game1-1].markedcells,vec[game2-1]);

        if(check==true){
            cout<<"Game "<<game1<<" has more marks than Game "<<game2<<endl;
            cout<<"Game "<<game1<<" = "<<vec[game1-1].markedcells<<" Game "<<game2<<" = "<<vec[game2-1].markedcells<<endl;
        }
        else{
            cout<<"Game "<<game2<<" has more marks than Game "<<game1<<endl;
            cout<<"Game "<<game1<<" = "<<vec[game1-1].markedcells<<" Game "<<game2<<" = "<<vec[game2-1].markedcells<<endl;
            }
            cout<<endl<<endl;
    }

	if(menu==4){

		for(int i=0;i<vec.size();i++)

		cout<<i+1<<'.'<<"Game "<<i+1<<" has "<<vec[i].markedcells<<" marked cells."<<endl;
	
		cout<<endl<<"Total number of marks(stored in static member of 'Hex' class) = "<<Hex::allmarkedcells<<"."<<endl<<endl;

	}

	if(menu==5){
		break;
	}

}
	return 0;
}

// --------------------------------------CLASS FUNCTIONS-----------------------------------


	void Hex::createboard(int size){

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

void Hex::play(int row,int column,char playtype){
	
	allmarkedcells++;
	markedcells++;
	hexCells[row][column].celltype=playtype;
}

void Hex::play(int size){

	allmarkedcells++;
	markedcells++;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> randomint(0,size-1); // distribution in range [1, 6]

    int row = randomint(rng);
    int column = randomint(rng);

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
if(hexCells[row-1][column].celltype == 'x') {wincheckforx(size,row-1,column);}
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

    myfile<<size<<" "<<gamemode<<" "<<playerturn<<endl;

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
	     myfile>>size>>gamemode>>playerturn;
	     createboard(size);
        }


        if(i!=0)
        myfile>>row>>column>>hexCells[row][column].celltype;

        i++;
    }

}

void Hex::playGame(){

		int gamemode;
		int size;
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

        loadcheck = true; 

        cout<<endl<<"Game loaded from: "<<filename<<endl<<endl;
    		}


	if(gamemode==1){

		
		printboard(size);

		while(1){

		turn=1;
			
		cout<<"Please enter row and column(A1,B3..etc)(Enter SAVE ___.txt to save and exit the game and only 'Q' to exit.)"<<endl;

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

    	play(row,column,userx);

    	printboard(size);

    	cout<<"computer's move:"<<endl;

    	play(size);

    	printboard(size);

    	int a,b;

    	a=scan_x(size);

    	if(turncount>size-1&&a!=-1)
    	wincheckforx(size,a,0);
		
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

		turn=1;
		cout<<"Please enter row and column player one(A1,B3..etc)(Enter SAVE ___.txt to save and exit the game and only 'Q' to exit.)"<<endl;

		//if(turncount==0)
    	//cin.get();
    	cin.getline(rclog, 30);

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
    	turn=2;
    	cout<<"Please enter row and column player two(A1,B3..etc)(Enter SAVE ___.txt to save and exit the game and only 'Q' to exit.)"<<endl;

    	 cin.getline(rclog, 30);
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

