#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<list>
#include<ctype.h>
using namespace std;
struct out
{
	int sca;
	int distance;
};
struct Node
{
	bool end;
	struct Node *arr[28];
	vector<int> ids;
};
void intialize(struct Node * & h)
{
	for (int i = 0; i < 28; i++)
		h->arr[i] = NULL;
	h->end = false;
}
void insert(string ss, int n, struct Node * head)
{
	struct Node * current = head;
	for (int i = 0; i < ss.length(); i++)
	{
		int j;
		if (ss[i] == '_')
			j = 26;
		else if (ss[i] == '-')
			j = 27;
		else
		{
			j = ss[i] - 'a';
		}
		if (current->arr[j] == NULL)
		{
			current->arr[j] = new Node();
			intialize(current->arr[j]);
		}
		current = current->arr[j];
	}
	current->end = true;
	current->ids.push_back(n);
}
void search(string ss, vector<int> &v, struct Node *head)
{
	v.clear();
	struct Node * current = head;
	bool f = false;
	int m = 0;
	for (int i = 0; i < ss.length(); i++)
	{
		int j;
		if (ss[i] == '_')
			j = 26;
		else if (ss[i] == '-')
			j = 27;
		else
		{
			j = ss[i] - 'a';
		}
		if (current->arr[j] == NULL)
		{
			f = true;
			break;
		}
		current = current->arr[j];
		m++;
	}
	if (f)
	{
		//cout << "notfound" << endl;
	}
	else if ((current->end == true) && m == ss.length())
	{
		//cout << "found" << endl;
		for (int i = 0; i < current->ids.size(); i++)
		{
			v.push_back(current->ids[i]);
		}
	}
}
vector<vector<int>> readfiles(int choice, vector<string> &synsets)
{
	synsets.clear();
	ifstream sysc;
	ifstream hyprs;
	if (choice == 1)
	{
		sysc.open("1synsets.txt");
		hyprs.open("2hypernyms.txt");

	}
	else if (choice == 2)
	{
		sysc.open("1synsets2.txt");
		hyprs.open("2hypernyms2.txt");
	}
	else if (choice == 3)
	{
		sysc.open("1synsets3.txt");
		hyprs.open("2hypernyms3.txt");
	}
	else if (choice==4)
	{
		sysc.open("1synsets4.txt");
		hyprs.open("2hypernyms4.txt");
	}
	else if (choice == 11)
	{
		sysc.open("1synsetssmall1.txt");
		hyprs.open("2hypernymssmall1.txt");
	}
	string ss;
	string str;
	while (getline(sysc, str))
	{
		ss = "";
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == ',')
			{
				for (int j = i + 1; j < str.length(); j++)
				{
					if (str[j] == ',')
						break;
					ss = ss + str[j];
				}
				break;
			}
		}
		synsets.push_back(ss);
	}
	vector<vector<int>> adjs(synsets.size());
	int count = 0;
	while (getline(hyprs, str))
	{
		ss = "";
		for (int i = 0; i < str.length(); i++)
		{

			if (str[i] != ',')
				ss = ss + str[i];
			if (str[i] == ',')
			{
				int h = stoi(ss);
				adjs[count].push_back(h);
				ss = "";
			}

		}
		int h = stoi(ss);
		adjs[count].push_back(h);
		count++;
	}
	return adjs;
}
void bfs(int a, int b, int & dis, int & sca,vector<vector<int>> adjs,int k)
{
	vector<bool> asyn(k);
	vector<bool> anodes(k);
	vector<int> adist(k);
	list<int> q;
	asyn[a] = true;
	q.push_back(a);
	adist[a] = 0;
	anodes[a] = true;
	while (!q.empty())
	{
		int x = q.front();
		q.pop_front();
		
		for (int i = 1; i < adjs[x].size(); i++)
		{
			if (!asyn[adjs[x][i]])
			{
				q.push_back(adjs[x][i]);
				asyn[adjs[x][i]] = true;
				anodes[adjs[x][i]] = true;
				adist[adjs[x][i]] = adist[x] + 1;
			}
		}
	}
	vector<bool> bsyn(k);
	vector<int> bnodes;
	vector<int> bdist(k);
	list<int> qb;
	bsyn[b] = true;
	qb.push_back(b);
	bdist[b] = 0;
	bnodes.push_back(b);
	while (!qb.empty())
	{
		int x = qb.front();
		qb.pop_front();
		
		for (int i = 1; i < adjs[x].size(); i++)
		{
			if (!bsyn[adjs[x][i]])
			{
				qb.push_back(adjs[x][i]);
				bsyn[adjs[x][i]] = true;
				bnodes.push_back(adjs[x][i]);
				bdist[adjs[x][i]] = bdist[x] + 1;
			}
		}
	}
	for (int i = 0; i < bnodes.size(); i++)
	{
		if (anodes[bnodes[i]])
		{
			sca = bnodes[i];
			dis = adist[bnodes[i]] + bdist[bnodes[i]];
			break;
		}
	}
   
}
void convert(string & ss)
{
	for (int i = 0; i < ss.length(); i++){
		ss[i] = tolower(ss[i]);
	}
}
void fillingtrie(vector<string> synsets,struct Node *head)
{
	for (int i = 0; i < synsets.size(); i++)
	{
		string str = "";
		for (int j = 0; j < synsets[i].length(); j++)
		{
			if (synsets[i][j] == ' ')
			{
				convert(str);
				//cout << str << "**";
				insert(str, i, head);
				str = "";
				
			}
			else
				str = str + synsets[i][j];
		}
		convert(str);
		//cout << str << endl;
		insert(str, i, head);
	}
}
void scabetweentwonouns(string s1, string s2,struct Node * head,vector<vector<int>> adjs,int k,int & fsca,int& fdis )
{
	vector<int> noofs1;
	vector<int> noofs2;
	vector<out> outs;
	convert(s1);
	convert(s2);
	search(s1, noofs1, head);
	search(s2, noofs2, head);
	int h = 0;
	for (int i = 0; i < noofs1.size(); i++)
	{
		for (int j = 0; j < noofs2.size(); j++)
		{
			int scaa, dis;
			bfs(noofs1[i], noofs2[j], dis, scaa, adjs, k);
			out xx;
			outs.push_back(xx);
			outs[h].sca = scaa;
			outs[h].distance = dis;
			h++;
		}
	}
	int p = 100000;
	int j = 0;
	for (int i = 0; i < outs.size(); i++)
	{
		if (p>outs[i].distance)
		{
			p = outs[i].distance;
			j = i;
		}
	}
	fsca = outs[j].sca;
	fdis = outs[j].distance;
}

int main()
{
	vector<string> synsets;
	vector<vector<int>> adjs;
	int choice;
	while (true)
	{
		cout << "for sample test 1 write 1" << endl;
		cout << "for sample test 2 write 2" << endl;
		cout << "for sample test 3 write 3" << endl;
		cout << "for sample test 4 write 4" << endl;
		cout << "for complete test 1 write 11" << endl;
		cin >> choice;
		adjs=readfiles(choice, synsets);
		struct Node *heads = new Node();
		intialize(heads);
		fillingtrie(synsets, heads);
		string a, c;
		int fdis, fsca;
		cout << "->enter the two nouns" << endl;
		cout << "->to  exit enter 'no no'" << endl;
		int jj = 0;
		while (cin >> a >> c)
		{
			if (a == "no"&&c == "no")
			{
				jj = 1;
				break;
			}
			scabetweentwonouns(a, c, heads, adjs, synsets.size(), fsca,fdis);
			cout <<"the shortest common ancestor is " <<synsets[fsca] << " and the distance -> " << fdis <<endl;
		}
		if (jj = 1)
			break;
	}
	return  0;
}