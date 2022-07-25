#include <iostream>
#include<fstream>
#include<typeinfo>
#include<vector>
#include<random>
#include "Hex.h"

using namespace std;


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

    vector<Hex> vec;

    for(int i=0;i<gamenumber;i++)
        vec.push_back(Hex(0));


while(1){
	
	cout<<"------MENU------"<<endl;
	cout<<"1.Start new game(You can test UNDO feature '--' operator also test score function at user vs computer mode)"<<endl;
	cout<<"2.Select active game and play(HW3) "<<"("<<vec.size()<<" games are active now)"<<endl;
    cout<<"3.Compare two games(HW3)"<<endl;
    cout<<"4.Compare two games(HW4 overloading '==' operator)"<<endl;
	cout<<"5.See the marked cells in all games(HW3)"<<endl;
	cout<<"6.Exit"<<endl<<endl;
	cout<<"Please choose one: "<<endl;

	cin>>menu;

	if(menu==1){
		
		Hex newgame(0);
		newgame.playGame();
		newgame.score_x=0;
		newgame.score_o=0;
		newgame.gamefinish=0;
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
	vec[selection-1].gamefinish=0;
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
    	int game1,game2;

        for(int i=0;i<vec.size();i++)
        cout<<i+1<<'.'<<"Game "<<i+1<<endl;
        cout<<endl;

        cout<<"Select two games to compare(about marked cells)(Enter with space: '1 2' '2 3' '2 4' etc.)"<<endl;
        cin>>game1>>game2;

        if(vec[game1-1]==vec[game2-1]){
        	cout<<"Game "<<game1<<" has equal to Game "<<game2<<endl;
            cout<<"Game "<<game1<<" = "<<vec[game1-1].markedcells<<" Game "<<game2<<" = "<<vec[game2-1].markedcells<<endl;

        } else{
            cout<<"Game "<<game2<<" has not equal to Game "<<game1<<endl;
            cout<<"Game "<<game1<<" = "<<vec[game1-1].markedcells<<" Game "<<game2<<" = "<<vec[game2-1].markedcells<<endl;
            }
            cout<<endl<<endl;
    }

    

	if(menu==5){

		for(int i=0;i<vec.size();i++)

		cout<<i+1<<'.'<<"Game "<<i+1<<" has "<<vec[i].markedcells<<" marked cells."<<endl;
	
		cout<<endl<<"Total number of marks(stored in static member of 'Hex' class) = "<<Hex::allmarkedcells<<"."<<endl<<endl;

	}

	if(menu==6){

		break;
	}

}
	return 0;
}


