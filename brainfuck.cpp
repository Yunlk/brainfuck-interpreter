#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <fstream>
using namespace std;

#define ll long long int
#define MEMORY_SIZE 300000

string code = "";
vector<ll> memory(MEMORY_SIZE,0);
vector<ll> find_loop;
ll *p = &memory[0];
int flag = 0;

void brain_plus()
{(*p)++;}
void brain_diff()
{(*p)--;}
void brain_R()
{
	p++;
	if (p >= &memory[0] + MEMORY_SIZE)
		cout << "ERROR:U MOVE P TOOOO RIGHT AT ADDRESS:" << p << endl;
	flag = 1;
}
void brain_L()
{
	p--;
	if (p < &memory[0])
		cout << "ERROR:U MOVE P TOOOO LEFT AT ADDRESS:" << p << endl;
	flag = 1;
}
void brain_out()
{cout << (char)*p;}
void brain_in()
{cin >> *p;}
vector<ll> brain_find_LOOP(const string& code)
{
	vector<ll> where(code.size(), -1);
	stack<ll> stack;
	ll loop_start;
	for (ll i = 0; i < code.size(); i++)
	{
		if (code[i] == '[')
			stack.push(i);
		else if (code[i] == ']')
		{
			if (stack.empty())
			{
				cout << "ERROR:CAN'T FIND '[' BEFORE ']' ON:" << i + 1;
				flag = 1;
				continue;
			}
			else
			{
				loop_start = stack.top();
				stack.pop();
				where[loop_start] = i;
				where[i] = loop_start;
			}
		}
	}
	if (!stack.empty())
	{
		cout << "ERROR:CAN'T FIND ']' AFTER '[' ON:" << stack.top() + 1;
		flag = 1;
	}
	return where;
}
void brain_file_in()
{
	string tep;
	ifstream file("code.bf");
	if (!file.is_open()) 
	{
		cerr << "ERROR: I CAN'T OPEN FILE code.bf! PLS TRY READ BY CIN!" << endl;
		flag = 2;
	}
	while (getline(file, tep))
		code += tep;
	file.close();
}
void brain_cin_in()
{
	cout << "U CAN USE 'ctrl + z' TO STOP CIN" << endl;
	string tep;
	while (getline(cin, tep))
		code += tep;
	cin.clear();
}
void brain_GO()
{
	ll i = 0;
	find_loop = brain_find_LOOP(code);
	if (flag)
	{
		cout << endl << "EXIT...";
		return;
	}
	while (i < code.size())
	{
		switch (code[i])
		{
		case '+':brain_plus(); break;
		case '-':brain_diff(); break;
		case '>':brain_R(); break;
		case '<':brain_L(); break;
		case '.':brain_out(); break;
		case ',':brain_in(); break;
		case '[':
			if (*p == 0)
				i = find_loop[i];
			break;
		case ']':
			if (*p != 0)
				i = find_loop[i];
			break;
		}
		i++;
	}
}
int main()
{
	int tep;
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout << "FROM CIN || FILE?(FILE NAME IS'code.bf')" << endl;
	cout << "IF CIN : ENTER -> 1" << endl << "IF FILE : ENTER -> 2" << endl;
	cin >> tep;
	cin.ignore();
	switch (tep)
	{
		case 1:brain_cin_in(); break;
		case 2:
			brain_file_in();
			if (flag == 2)
				brain_cin_in();
			break;
	}
	brain_GO();
	return 0;

}
