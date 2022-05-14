#include <bits/stdc++.h>
#include <iostream>  
#include <fstream>
#include <sstream>
#include <string>  
#include <map>  
using namespace std;

//Global 
int arr[81000+1];
map<int,int>mp;


//compare function to sort vector of pairs
bool cmp(pair<int, int>& a,
         pair<int, int>& b)
{
    return a.second > b.second;
}

//count the degree(no. of followers) of each account
void followersCount(int account) {
    mp[account]++;
}


void search(int n){

	//convert map to vector of pairs so it can be sorted
	vector<pair<int, int> > A;
	for (auto& it : mp) {
        A.push_back(it);
    }
    sort(A.begin(), A.end(), cmp);
	//arr is aray of IDs and their order in descending order
	int i=1;
	 for (auto& it : A) {
		//i: order
		//it.first: ID
        arr[i] = it.first;
		i++;
    }
	cout<<"Account ID: "<<arr[n]<<" , "<<"Followers: "<<mp[arr[n]]<<endl;
}


int main()
{
    set<int>s1;
    set<int>s2;
	ifstream myFile("twitter.csv"); //open the data file
    if (myFile.is_open())
    {
        string line;
        while(getline(myFile,line)) 
        {
            stringstream ss(line);
			string x;
			string y;
			getline(ss,x,',');    //follower
            getline(ss,y,',');    //account
			int follower, account;
			follower = stoi(x);
			account = stoi(y);
            //s1.insert(follower);
            //s2.insert(account);

            followersCount(account);
			//cout<<dest<<" "<<src<<endl;
        }

    }
	else{
		cout<<"Cannot open the file!"<<endl;
		return 0;
	}

    //cout<<s1.size()<<" "<<s2.size()<<endl;
	cout<<"Enter the influncer order: "; //take the input from the user
	int num; cin>>num;
	if(num<1 || num>81000){
		cout<<"Wrong input!"<<endl;
		return 0;
	}
	search(num);

	return 0;
}
