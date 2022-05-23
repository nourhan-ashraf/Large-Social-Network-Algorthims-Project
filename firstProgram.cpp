#include <bits/stdc++.h>
using namespace std;
map<int,int>mapping;
map<int,int>mapping2;

//Time complexity is O(N*log(N))
set<int>adjList[810000];

int k=0;
void buildGraph(int follower, int account)   //O(log(N))
{
        if(!mapping.count(account)){    //map "count" takes O(log(N))
            k++;
            mapping[account] = k;      //give each vertex an index beside its ID to be more easier to loop on each vertex 
            mapping2[k] = account;
        }
        adjList[mapping[account]].insert(follower); //add list of following to each vertex
}


set<pair<int ,int>>ans;
vector<pair<int, pair<int,int>>>v;
//           index     id   size
//           v.first,    v.second.first , v.second.second


void printDegree(int num){
    for (int i = 1; i <=81305; i++) {
        int lst = adjList[i].size();
        ans.insert(make_pair(lst,mapping2[i])); 
                          //size, id
    }
   //(1000, 3197098), (500, 23618970), ....., etc

    int it = 81305;
    for(auto u:ans){
        v.push_back(make_pair(it, make_pair(u.second, u.first)));  //u.second -> id, u.first -> size
        it--;
    }
    for(auto j:v){
        if(num==j.first){
            cout<<"Account ID: "<<j.second.first<<" , "<<"Followers: "<<j.second.second<<endl;
            break;
        }
    }
    
}

int main()
{
    ifstream myFile("C:\\Users\\Noura\\Downloads\\twitter (1).csv"); //open the data file

    if (myFile.is_open())  
    {
        string line;
        while(getline(myFile,line)) //O(Nlog(N)) for N of lines of data
        {
            stringstream ss(line);
			string x;
			string y;
			getline(ss,x,',');    //follower
            getline(ss,y,',');    //account
			int follower, account;
			follower = stoi(x);  //convert from string to int 
			account = stoi(y);

           buildGraph(follower, account); 
        }

    }
	else{
		cout<<"Cannot open the file!"<<endl;
		return 0;
	}
//cout<<k<<endl;
    cout<<"Enter the influncer order: "; //take the input from the user
	int num; cin>>num;

	printDegree(num); 

	return 0;
}
