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

using namespace std;

using namespace wetehex;

void drivercode(AbstractHex *h){

	char* loadfile_name = (char*) "validgame2.txt";
	char* savefile_name = (char*) "testgame.txt";

	cout << "************************WELCOME TO TEST FUNCTION************************"<<endl<<endl;

	h->size = 6;

	h->setSize(h->size);
	cout << "-size set to 6 : "<<endl;
	h->print(h->size);

	h->readFromFile(h->size,h->gamemode,h->turn,loadfile_name);
	cout <<endl<< "-'readFromFile' function has called : "<<endl;
	h->print(h->size);

	h->reset(h->size);
	cout <<endl<< "-'reset' function has called : "<<endl;
	h->print(h->size);

	h->play();
	cout <<endl<< "-bot 'play' function has called : "<<endl;
	h->print(h->size);

	h->play(0,0,'x');
	cout <<endl<< "-user 'play' function has called for coordinat(A,1) playtype = x : "<<endl;
	h->print(h->size);

	h->writeToFile(h->size,h->gamemode,h->turn,savefile_name);
	cout <<endl<< "-'writeFromFile' function has called, game saved to testgame.txt : "<<endl;
	h->print(h->size);

	cout<<endl<<"'numberOfMoves' and 'lastMove' functions have called : "<<endl<<endl;;

	cout<<"numberOfMoves : "<<h->numberOfMoves()<<endl<<"lastMove : row = "<<h->lastMove().row<<
	" column = "<<h->lastMove().column<<" playtype = "<<h->lastMove().celltype<<endl<<endl;

	h->reset(h->size);
	cout <<endl<< "-'reset' function has called again : "<<endl;
	h->print(h->size);

	h->play(0,0,'x');
	h->play(1,2,'o');
	cout <<endl<< "-user 'play' function has called for"<<endl<<"coordinat(A,1) playtype = x and for coordinat(B,3) playtype = o : "<<endl;
	h->print(h->size);

	cout<<endl<<"'operator()' has called for (A,1) , (B,3) and (B,4) : "<<endl;

	cout<<endl<<"(*h)(0,0).celltype = "<<(*h)(0,0).celltype<<" (*h)(1,2).celltype  = "<<(*h)(1,2).celltype<<
	" (*h)(1,3).celltype  = "<<(*h)(1,3).celltype<<endl;

	h->reset(h->size);
	cout <<endl<< "-'reset' function has called again : "<<endl;
	h->print(h->size);

	try{
	cout<<endl<<"'lastMove' functions have called for exception test : "<<endl;
	h->lastMove();
     }catch(lastMoveError &err)
     {	
     	cout<<endl<<"Exception caught!"<<endl;
     	cout<< err.what() <<endl;
     }
}


int main(){

	HexVector h1,p1,m1;
	HexArray1D h2,p2,m2;
	HexAdapter< deque< deque<Cell> > > h3,p3;
	HexAdapter< vector< vector<Cell> > > h4,p4,m3;

	int menu;

	while(1){

	cout<<"------MENU------"<<endl;
	cout<<"Driver codes for test member functions"<<endl;
	cout<<"\t1.HexVector"<<endl;
    cout<<"\t2.HexArray1D"<<endl;
    cout<<"\t3.HexAdapter<deque>"<<endl;
    cout<<"\t4.HexAdapter<vector>"<<endl;
	cout<<"Other Tests"<<endl;
	cout<<"\t5.operator=="<<endl;
    cout<<"\t6.global valid check function"<<endl;
    cout<<"Standart play game"<<endl;
    cout<<"\t7.HexVector"<<endl;
    cout<<"\t8.HexArray1D"<<endl;
    cout<<"\t9.HexAdapter<vector>"<<endl;
    cout<<"\t10.HexAdapter<deque>"<<endl;
    cout<<"Exit"<<endl;
    cout<<"\t0.For Exit"<<endl;
    here:
	cout<<"Please choose one: "<<endl;
	cin>>menu;	

	if(menu==1){
		drivercode(&h1);
	}
	else if(menu==2){
		drivercode(&h2);
	}
	else if(menu==3){
		drivercode(&h3);
	}
	else if(menu==4){
		drivercode(&h4);
	}
	else if(menu==5){
	cout<< "HexVector set as : "<<endl;
	h1.size = 6;
	h1.setSize(h1.size);
	h1.play(2,3,'x');
	h1.play(1,1,'o');
	h1.play(4,3,'x');
	h1.print(h1.size);

	cout<< "HexArray1D set as : "<<endl;
	h2.size = 6;
	h2.setSize(h2.size);
	h2.play(2,3,'x');
	h2.play(1,1,'o');
	h2.play(4,3,'x');
	h2.print(h2.size);

	cout<<endl<<"operator== has called :"<<endl;

	if(h1==h2)
		cout << "Boards are equal"<<endl<<endl;
	else
		cout << "Boards are not equal"<<endl<<endl;

	cout<< "HexVector set as : "<<endl;
	h1.size = 6;
	h1.setSize(h1.size);
	h1.play(1,1,'x');
	h1.play(0,2,'o');
	h1.play(2,3,'x');
	h1.print(h1.size);

	cout<< "HexArray1D set as : "<<endl;
	h2.size = 5;
	h2.setSize(h2.size);
	h2.play(1,3,'x');
	h2.play(3,1,'o');
	h2.print(h2.size);

	cout<<endl<<"operator== has called :"<<endl;

	if(h1==h2)
		cout <<"Boards are equal"<<endl<<endl;
	else
		cout <<"Boards are not equal"<<endl<<endl;

	}
	else if(menu==6){

		char* loadfile_name1 = (char*) "validgame1.txt";
		char* loadfile_name2 = (char*) "validgame2.txt";
		char* loadfile_name3 = (char*) "unvalidgame1.txt";

		m1.readFromFile(m1.size,m1.gamemode,m1.turn,loadfile_name1);
		m2.readFromFile(m2.size,m2.gamemode,m2.turn,loadfile_name2);
		m3.readFromFile(m3.size,m3.gamemode,m3.turn,loadfile_name3);

		cout<<endl<<"Games are loaded from files.."<<endl<<endl;

		m1.print(m1.size);
		cout<<endl;
		m2.print(m2.size);
		cout<<endl;
		m3.print(m3.size);
		cout<<endl;

		AbstractHex *ptr[50];

		ptr[0] = &m1;
		ptr[1] = &m2;
		ptr[2] = &m3;


		if(areGamesValid(ptr,3)==true)
		cout<< "All games are valid"<<endl;
	else
		cout<< "At least one game is unvalid"<<endl;

	}
	else if(menu==7){
		p1.playGame();
	}
	else if(menu==8){
		p2.playGame();
	}
	else if(menu==9){
		p3.playGame();
	}
	else if(menu==10){
		p4.playGame();
	}
	else if(menu==0){
		break;
	}
	else{
		cout<<"Invalid selection"<<endl;
		goto here;
	}

	}

	return 0;
}


