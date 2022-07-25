#ifndef HEX_H
#define HEX_H

#include <iostream>
#include <stdlib.h>
#include <cmath>
#include<fstream>
#include<typeinfo>
#include<vector>
#include<exception>
#include<random>
#include <deque> 

using namespace std;

namespace wetehex{


enum celltype{

   userx = 'x', usero = 'o' , empty = '.'
};

 class Cell{

 	public:
    int row;
    int column;
    char celltype;

  };

class AbstractHex{

	public:

	static int allmarkedcells;

	int markedcells=0;
    int size;
    int gamemode=0;
	int turn=0;
    int gamefinish=0;
    int lastrow,lastcolumn;
    int x_number=0,o_number=0;
    bool validgame = true;

	virtual void setSize(int size)=0;
	virtual void reset(int size)=0;
	virtual void print(int size)=0;
	virtual void play(int row,int column,char playtype)=0;      
	virtual void play()=0;
	virtual void writeToFile(int size,int gamemode,int playerturn,char filename[30])=0;
	virtual void readFromFile(int &size,int &gamemode,int &playerturn,char filename[30])=0;

	virtual int scan_x(int size)=0;
	virtual int scan_y(int size)=0;
	virtual int wincheckforx(int size,int row,int column)=0;
	virtual int wincheckforo(int size,int row,int column)=0;
	virtual bool isempty(int row,int column)=0;
	virtual Cell operator()(int row,int column)const=0;
	virtual Cell lastMove()=0;

	void asciconverter(char rclog[30],int &row,int &column);
    int returnsize(int size); 
	bool isEnd(int gamefinish);
	int numberOfMoves(){return markedcells;}
    void playGame();

    bool operator==(const AbstractHex &other);

 };

 class HexVector : public AbstractHex{

 	public:

 	void setSize(int size);
 	void reset(int size);
	void print(int size);
	void play(int row,int column,char playtype);      
	void play();
	void writeToFile(int size,int gamemode,int playerturn,char filename[30]);
	void readFromFile(int &size,int &gamemode,int &playerturn,char filename[30]);


	int scan_x(int size);
	int scan_y(int size);
	int wincheckforx(int size,int row,int column);
	int wincheckforo(int size,int row,int column);
	bool isempty(int row,int column);

	Cell operator()(int row,int column)const{ return hexCells[row][column]; }
	Cell lastMove();

    private:

 	vector< vector<Cell> > hexCells ;	

 };

 class HexArray1D : public AbstractHex{

 	public:

 	void setSize(int size);
 	void reset(int size);
	void print(int size);
	void play(int row,int column,char playtype);      
	void play();
	void writeToFile(int size,int gamemode,int playerturn,char filename[30]);
	void readFromFile(int &size,int &gamemode,int &playerturn,char filename[30]);


	int scan_x(int size);
	int scan_y(int size);
	int wincheckforx(int size,int row,int column);
	int wincheckforo(int size,int row,int column);
	bool isempty(int row,int column);

	Cell operator()(int row,int column)const{ return hexCells[row * size + column]; }
	Cell lastMove();

	private:

	Cell *hexCells;	
 };


template<class T>
class HexAdapter : public HexVector{

    private:

 	T hexCells ;	

 };

struct lastMoveError : public std::exception
{
	const char * what () const throw ()
    {
    	return "There is no lastMove because board is empty..";
    }
};


extern bool areGamesValid(AbstractHex *ptr[50],int numberofgames);

}//wetehex

#endif //HEX_H