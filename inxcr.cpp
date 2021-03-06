#include<fstream>
#include<iostream>
#include<vector>
#include<string>
#include<set>
using namespace std;
set<string> added;
bool valid(string str,int xpos){
	str[xpos] = 'b';
	string mapstr;
	for(int i = 0;i<18;i++){
		if(str[i] != ',')mapstr += str[i];
	}
	for(int i = 0;i<3;i++){
		if(mapstr[i*3]== mapstr[i*3+1] && mapstr[i*3+1] == mapstr[i*3+2]&&mapstr[i*3]!='b') return false;
		if(mapstr[i]== mapstr[i+3]&&mapstr[i+3]==mapstr[i+6]&&mapstr[i] !='b') return false;
	}
	if(mapstr[0]==mapstr[4]&&mapstr[4]==mapstr[8]&&mapstr[0]!='b') return false;
	if(mapstr[2]==mapstr[4]&&mapstr[4]==mapstr[6]&&mapstr[2]!='b') return false;
	if(added.find(mapstr) == added.end()){
		added.insert(mapstr);
		return true;	
	}
	else{
		return false;
	}
	
}
bool circlewin(string str){
	string mapstr;
	for(int i = 0;i<18;i++){
		if(str[i] != ',')mapstr += str[i];
	}
	for(int i = 0;i<3;i++){
		if(mapstr[i*3]== mapstr[i*3+1] && mapstr[i*3+1] == mapstr[i*3+2]&&mapstr[i*3]=='o') return true;
		if(mapstr[i]== mapstr[i+3]&&mapstr[i+3]==mapstr[i+6]&&mapstr[i] =='o') return true;
	}
	if(mapstr[0]==mapstr[4]&&mapstr[4]==mapstr[8]&&mapstr[0]=='o') return true;
	if(mapstr[2]==mapstr[4]&&mapstr[4]==mapstr[6]&&mapstr[2]=='o') return true;
	return false;
}
int main(){
	ifstream in("data.txt");
	string tmp;
	vector<string> maps;
	while(getline(in,tmp)){
		maps.push_back(tmp);
	}
	in.close();
	//0~625 possitive
	ofstream outx("input_x_new.txt");
	ofstream outy("input_y_new.txt");
	int cnt = 0;
	int cnty = 0;
	for(int i = 0;i<626;i++){
		for(int j = 0;j<18;j++){
			if(maps[i][j] == 'x'&&valid(maps[i],j)){
				for(int l = 0;l<9;l++){
						if(l== j/2){
							outy << "1.0";
						}
						else{
							outy << "0.0";
						}
						if(l!=8) outy << " ";
				}
				cnty++;
				outy << endl;
				for(int k = 0;k<18;k++){
					if(k == j){
						if(k != 0) outx << " ";
						outx << "1 0 0";
					}
					else if(maps[i][k]== ',') continue;
					else{
						if(maps[i][k] == 'x'){
							if(k != 0) outx << " ";
							outx << "0 1 0";
						}
						else if(maps[i][k] == 'o'){
							if(k != 0) outx << " ";
							outx << "0 0 1";
						}
						else if(maps[i][k] == 'b'){
							if(k != 0) outx << " ";
							outx << "1 0 0";
						}
					}
				}
				cnt++;
				outx << endl;
			}
			else continue;
		}
	}
	//negative
	for(int i = 626;i<958;i++){
		for(int j = 0;j<18;j++){
			if(maps[i][j] == 'o'&&circlewin(maps[i])){
				string newstr = maps[i];
				if(valid(newstr,j)) newstr[j] = 'b';
				else continue;
				for(int k = 0;k<18;k++){
					if(maps[i][k] == 'x'&&valid(newstr,k)){
						for(int l = 0;l<9;l++){
							if(l== j/2){
								outy << "1.0";
							}
							else{
								outy << "0.0";
							}
							if(l!=8) outy << " ";
						}
						cnty++;
						outy << endl;
						for(int m = 0;m<18;m++){
							if(m == j||m==k){
								if(m != 0) outx << " ";
								outx << "1 0 0";
							}
							else if(maps[i][m]== ',') continue;
							else{
								if(maps[i][m] == 'x'){
									if(m != 0) outx << " ";
									outx << "0 1 0";
								}
								else if(maps[i][m] == 'o'){
									if(m != 0) outx << " ";
									outx << "0 0 1";
								}
								else if(maps[i][m] == 'b'){
									if(m != 0) outx << " ";
									outx << "1 0 0";
								}
							}
						}
						cnt++;
						outx << endl;
					}
				}
			}
			else continue;
		}
	}
	cout << cnt << endl;
	cout << cnty << endl;
	outx.close();
	return 0;
}