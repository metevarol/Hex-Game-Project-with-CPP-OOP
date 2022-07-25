#include <iostream>
#include<fstream>
#include<typeinfo>
#include<vector>
#include<random>

using namespace std;


enum celltype{

   userx = 'x', usero = 'o' , empty = '.'
};


class Hex{

	public:
    
    class Cell;

	static int allmarkedcells;

	int markedcells=0;
    int size;
    int gamefinish=0;
    int score_x=0,score_o=0;

	inline void createboard(int size); 
	inline void printboard(int size);

	Cell &play(int row,int column,char playtype);      //NEW PLAY FUNCTIONS
	Cell &play();
	
	Hex operator-- ();									//UNDO FUNCTIONS
	Hex operator-- (int);

	friend ostream & operator << (ostream &out, const Hex &h);     //INSERTION AND EXTRACTION OPERATORS FOR SCREEN AND FILES
	friend istream & operator >> (istream &in,Hex &h);
	
	int scoreuser(int size,int row,int column);         //RECURSIVE SCORE FUNCTIONS
	int scorecomputer(int size,int row,int column);

	friend bool operator==(const Hex &h1,const Hex &h2);

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

    int* rowarr=new int[100];
    int* columnarr=new int[100];
    int* marr= nullptr;              //NULL PTR

    explicit Hex(int x){                       //EXPLICIT

        markedcells=x;
    }
    
    

    class Cell{

    int row;
    int column;
    char celltype;

    friend class Hex;

    };  
    
	private:


	Cell** hexCells;

};