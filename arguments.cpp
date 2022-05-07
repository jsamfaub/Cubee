#include <string.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int numOfPossibleArgs;
extern int numOfPlayers;
string level="data/levels/";
extern string levelPath;
vector<string> possibleArgs={"-np","-l","-c"};
void usage(string arg, string parameter);
void handleArguments(int argc,char **argv){
	numOfPossibleArgs=possibleArgs.size();
	for(int i=1;i<argc;i++){
		for(int j=0;j<numOfPossibleArgs;j++){
			if(strcmp(argv[i],possibleArgs[j].c_str())==0){
				if(strcmp(possibleArgs[j].c_str(),"-np")==0){
					if(argc==i+1){
						usage(possibleArgs[j],"[number of players]");
					}else{
						int num=atoi(argv[i+1]);
						cout<<(num=atoi(argv[i+1]))<<num<<endl;
						if(num<3&&num>0){
							numOfPlayers=num;
							i++;
						}else{
							cout<<"Choose a number between 1 and 2 after -np"<<endl;
						}
					}
				}
				if(strcmp(possibleArgs[j].c_str(),"-l")==0){
					cout<<"levelname"<<possibleArgs[j].c_str()<<endl;
					if(argc==i+1){
						usage(possibleArgs[j],"[levelname].lvl (lvl files in the data/levels/ folder)");
					}else{
						level+=argv[i+1];
						levelPath=level;
						i++;
					}
					
				}
				if(strcmp(possibleArgs[j].c_str(),"-c")==0){
					cout<<"controls"<<possibleArgs[j].c_str()<<endl;
				}
			}
		}
	}
}

void usage(string arg, string parameter){
	cout<<"Usage: "<<arg<<" "<<parameter<<endl;
}
