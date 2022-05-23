//Time complexity is O(E*log(E))

#include <bits/stdc++.h>
using namespace std;

map<int,int>mapping;  //map between the account and its index
map<int,int>mapping2; //map between the index and its account
set<int>adjList[810000]; //array (vertcies) of sets (set for each vertex)

int k=0;
void buildGraph(int follower, int account)   //O(log(E))
{
        if(!mapping.count(account)){    //map "count" takes O(log(E))
            k++;
            mapping[account] = k;      //give each vertex an index beside its ID to be more easier to loop on each vertex 
            mapping2[k] = account;
        }
        adjList[mapping[account]].insert(follower); //add list of following to each vertex
}


set<pair<int ,int>>ans;  //set of pairs of the ID and the size of each ID followers list sorted by the size 
vector<pair<int, pair<int,int>>>v; //vector of pairs of pairs to map between three values (index, ID, size) sorted by the size in deascending order
//           index     ,id             ,size
//           v.first,  ,v.second.first ,v.second.second


void printDegree(int num){  //O(V)
    for (int i = 1; i <=81305; i++) {  //O(V)
        int lst = adjList[i].size();
        ans.insert(make_pair(lst,mapping2[i])); 
                          //size, id
    }
    int it = 81305;
    for(auto u:ans){ //O(V)
        v.push_back(make_pair(it, make_pair(u.second, u.first)));  //u.second -> id, u.first -> size
        it--;
    }
    for(auto j:v){  //O(V)
        if(num==j.first){ 
            cout<<"Account ID: "<<j.second.first<<" , "<<"Followers: "<<j.second.second<<endl;
            break;
        }
    }
    
}

int main()
{
    ifstream myFile("twitter.txt"); //open the data file

    if (myFile.is_open())  
    {
        string line;
        while(getline(myFile,line)) //O(Elog(E)) for N of lines of data
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

    cout<<"Enter the influncer order: "; //take the input from the user
	int num; cin>>num;
	if(num<1 || num>81305){   //check if the input exceeds the number of accounts which is 81305 or it was smaller than 1
		cout<<"Wrong input!"<<endl;
		return 0;
	}
	printDegree(num);  //O(V)

	return 0;
}
