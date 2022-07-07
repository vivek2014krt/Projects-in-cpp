#include <bits/stdc++.h>
#include <conio.h>
#include <unistd.h>
using namespace std;
#define CHARACTER_SIZE 256
class TrieNode
{
	TrieNode *children[CHARACTER_SIZE];
	bool isEndOfWord;

public:
	TrieNode *getNode()
	{
		TrieNode *pNode = new TrieNode;
		pNode->isEndOfWord = false;
		for (int i = 0; i < CHARACTER_SIZE; i++)
			pNode->children[i] = NULL;
		return pNode;
	}
	void insert(TrieNode *root, string username, string password)
	{
		TrieNode *temp;
		int index = int(username[0]);
		if (root->children[index] == NULL)
		{
			temp = getNode();
			root->children[index] = temp;
		}
		if (username.size() == 1)
		{
			root->isEndOfWord = true;
			if (!password.empty())
			{
				insert(root->children[index], password, "");
			}
			return;
		}
		insert(root->children[index], username.substr(1), password);
	}
	bool search(TrieNode *root, string username, string password)
	{
		int index = int(username[0]);
		if (root->children[index] == NULL)
		{
			return false;
		}
		if (username.size() > 1)
		{
			return search(root->children[index], username.substr(1), password);
		}
		if (root->isEndOfWord && !password.empty())
		{
			return search(root->children[index], password, "");
		}
		else
		{
			return root->isEndOfWord;
		}
	}
};
class registration
{
public:
	string first_name;
	string last_name;
	string mobile_no;
	string email_id;
	string username;
	string password;
	void input()
	{
		cout << "\n\t\tEnter your first name:- ";
		cin >> first_name;
		cout << "\n\t\tEnter your last name:- ";
		cin >> last_name;
		cout << "\n\t\tEnter your mobile no:- ";
		cin >> mobile_no;
		cout << "\n\t\tEnter your email id:- ";
		cin >> email_id;
		cout << "\n\t\tSet username:- ";
		cin >> username;
		cout << "\n\t\tSet password:- ";
		cin >> password;
	}
};

int highscore(int a[6][6])
{
	int max = -1;
	for(int i =0;i<6;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(a[i][j]>max)
			{
				max = a[i][j];
			}
		}
	}
	return max;
}

void menu()
{
    cout << endl;
    cout << "Enter w to move up" << endl;
    cout << "Enter s to move down" << endl;
    cout << "Enter d to move right" << endl;
    cout << "Enter a to move left" << endl;
    cout << "Enter q to quit" << endl;
    cout << endl;
}

void move_up(int a[6][6])
{
	int i, j, li, ri;
	for (j = 0; j < 6; j++)
	{
		li = 0, ri = j;
		for (i = 1; i < 6; i++)
		{
			if (a[i][j] != 0)
			{
				if (a[i - 1][j] == 0 || a[i - 1][j] == a[i][j])
				{
					if (a[li][ri] == a[i][j])
					{
						a[li][ri] *= 2;
						a[i][j] = 0;
					}
					else
					{
						if (a[li][ri] == 0)
						{
							a[li][ri] = a[i][j];
							a[i][j] = 0;
						}
						else
						{
							a[++li][ri] = a[i][j];
							a[i][j] = 0;
						}
					}
				}
				else
					li++;
			}
		}
	}
}

void move_down(int a[6][6])
{
	int i, j, li, ri;
	for (j = 0; j < 6; j++)
	{
		li = 5, ri = j;
		for (i = 4; i >= 0; i--)
		{
			if (a[i][j] != 0)
			{
				if (a[i + 1][j] == 0 || a[i + 1][j] == a[i][j])
				{
					if (a[li][ri] == a[i][j])
					{
						a[li][ri] *= 2;
						a[i][j] = 0;
					}
					else
					{
						if (a[li][ri] == 0)
						{
							a[li][ri] = a[i][j];
							a[i][j] = 0;
						}
						else
						{
							a[--li][ri] = a[i][j];
							a[i][j] = 0;
						}
					}
				}
				else
					li--;
			}
		}
	}
}

void move_left(int a[6][6])
{
	int i, j, li, ri;
	for (i = 0; i < 6; i++)
	{
		li = i, ri = 0;
		for (j = 1; j < 6; j++)
		{
			if (a[i][j] != 0)
			{
				if (a[i][j - 1] == 0 || a[i][j - 1] == a[i][j])
				{
					if (a[li][ri] == a[i][j])
					{
						a[li][ri] *= 2;
						a[i][j] = 0;
					}
					else
					{
						if (a[li][ri] == 0)
						{
							a[li][ri] = a[i][j];
							a[i][j] = 0;
						}
						else
						{
							a[li][++ri] = a[i][j];
							a[i][j] = 0;
						}
					}
				}
				else
					ri++;
			}
		}
	}
}

void move_right(int a[6][6])
{
	int i, j, li, ri;
	for (i = 0; i < 6; i++)
	{
		li = i, ri = 5;
		for (j = 4; j >= 0; j--)
		{
			if (a[i][j] != 0)
			{
				if (a[i][j + 1] == 0 || a[i][j + 1] == a[i][j])
				{
					if (a[li][ri] == a[i][j])
					{
						a[li][ri] *= 2;
						a[i][j] = 0;
					}
					else
					{
						if (a[li][ri] == 0)
						{
							a[li][ri] = a[i][j];
							a[i][j] = 0;
						}
						else
						{
							a[li][--ri] = a[i][j];
							a[i][j] = 0;
						}
					}
				}
				else
					ri--;
			}
		}
	}
}

void insert(int a[6][6])
{
	int li, ri;
	srand(time(0));
	while (1)
	{
		li = rand() % 6;
		ri = rand() % 6;
		if (a[li][ri] == 0)
		{
			a[li][ri] = pow(2, li % 2 + 1);
			break;
		}
	}
}

void view_grid(int a[6][6])
{
	
	cout << "\n\n\n\n";
	int i, j;
	for (i = 0; i < 6; i++)
	{
		cout << "\t\t\t\t-------------------------\n\t\t\t\t";
		for (j = 0; j < 6; j++)
		{
			if (a[i][j] == 0)
				cout << "|   ";
			else
				cout << "| " << a[i][j] << " ";
		}
		cout << "|" << endl;
	}
	cout << "\t\t\t\t-------------------------\n";
}

int compare(int tmp[6][6], int a[6][6])
{
	int fl = 1, i, j;
	for (i = 0; i < 6; i++)
		for (j = 0; j < 6; j++)
			if (tmp[i][j] != a[i][j])
			{
				fl = 0;
				break;
			}
	return fl;
}

int filled(int a[6][6])
{
	int fl = 0, gl = 0, i, j;
	for (i = 0; i < 6; i++)
		for (j = 0; j < 6; j++)
			if (a[i][j] == 0)
			{
				fl = 1;
				break;
			}

	for (i = 0; i < 5; i++)
		for (j = 0; j < 5; j++)
			if (a[i + 1][j] == a[i][j] || a[i][j + 1] == a[i][j])
			{
				gl = 1;
				break;
			}

	if (fl || gl)
		return 1;
	else
		return 0;
}

int main()
{
	TrieNode t;
	TrieNode *root = t.getNode();
	string password, username;
	system("CLS");
	system("Color B5");
	cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t--------------------------";
	cout << "\n\t\t\t\t\t|LOGIN & PLAY - 2048 GAME|";
	cout << "\n\t\t\t\t\t--------------------------";
	sleep(1);
	while (1)
	{
		start:
		system("CLS");
		cout << "\n\n\n\n\n\t\t\t\t\t***MENU***";
		cout << "\n\t\t\t1.LOGIN TO PLAY";
		cout << "\n\t\t\t2.REGISTER IF YOU ARE PLAYING FOR THE FIRST TIME";
		cout << "\n\t\t\t3.EXIT";
		int choice;
		cout << "\n\t\t\tEnter your choice:- ";
		cin >> choice;
		if (choice == 1)
		{
			int check2 = 0;
			while (check2 < 3)
			{
				int flag = 1;
				system("CLS");
				cout << "\n\n\n\n\n\t\t\t\t\t**LOGIN**";
				cout << "\n\t\t\tEnter username:- ";
				cin >> username;
				cout << "\n\t\t\tEnter password:- ";
				cin >> password;
				if (!t.search(root, username, password))
				{
					check2++;
					cout << "\n\t\t\t**WRONG USERNAME OR PASSWORD**";
					sleep(1);
					if (check2 >= 3)
					{
						system("CLS");
						cout << "\n\n\n\n\n\t\t\t\t**LOGIN LIMIT EXCEED**";
						sleep(1);
						exit(0);
					}
				}
				else
				{
					system("cls");
					cout<<"\n\n\n\t\t\tLGIN SUCCESSFUL\n\n\n\t\t\tPRESS ANY KEY TO CONTINUE";
					getch();
					system("cls");
					int i1, i2, i3, i4, i, j;
					int a[6][6] = {0}, tmp[6][6] = {0};
					srand(time(0));
					i1 = rand() % 6;
					i2 = rand() % 6;
					while (1)
					{
						i3 = rand() % 6;
						i4 = rand() % 6;
						if (i3 != i1 && i4 != i2)
							break;
					}
					a[i1][i2] = 2;
					a[i3][i4] = 4;
					view_grid(a);

					int ch;
					while (1)
					{
						for (i = 0; i < 6; i++)
							for (j = 0; j < 6; j++)
								tmp[i][j] = a[i][j];
						menu();
						ch = getch();
						system("cls");
						if (ch == 119)
							move_up(a);
						if (ch == 115)
							move_down(a);
						if (ch == 97)
							move_left(a);
						if (ch == 100)
							move_right(a);
						if (ch == 113)
							goto start;

						if (!compare(tmp, a))
							insert(a);
						view_grid(a);

						if (!filled(a))
						{
							cout << "\n\n\t\t\tGAME OVER!\n\n\n";
							cout << "\n\n\t\t\tYour score : "<<highscore(a);
							getch();
							goto start;
						}
					}
				}
			}
		}
		else if(choice==2)
        {
            system("CLS");
            cout<<"\n\n\n\n\n\t\t\t\t\t\t\t**REGISTRATION**";
            registration r;
            r.input();
            t.insert(root,r.username,r.password);
        }
		else if(choice==3)
        {
            exit(0);
        }
        else
        {
            cout<<"\n\t\t\t\t\t\tWRONG CHOICE ENTERED";
        }
	}

	return 0;
}
