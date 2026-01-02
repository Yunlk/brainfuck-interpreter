# brainfuck 解释器

### 这是什么？

[是](https://github.com/Yunlk/brainfuck-interpreter)

### 如何实现的？

#### +

```cpp
void brain_plus()
{(*p)++;}
```

#### -

```cpp
void brain_diff()
{(*p)--;}
```

#### >

```cpp
void brain_R()
{
	p++;
	if (p >= &memory[0] + MEMORY_SIZE)//防止越界
		cout << "ERROR:U MOVE P TOOOO RIGHT AT ADDRESS:" << p << endl;
	flag = 1;
}
```

#### <

```cpp
void brain_L()
{
	p--;
	if (p < &memory[0])//防止越界
		cout << "ERROR:U MOVE P TOOOO LEFT AT ADDRESS:" << p << endl;
	flag = 1;
}
```

#### .

```cpp
void brain_out()
{cout << (char)*p;}
```

#### ，

```cpp
void brain_in()
{cin >> *p;}
```

#### [ and ]

```cpp
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
			if (stack.empty())//如果括号不匹配
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
	if (!stack.empty())//如果括号不匹配
	{
		cout << "ERROR:CAN'T FIND ']' AFTER '[' ON:" << stack.top() + 1;
		flag = 1;
	}
	return where;
}
```

#### 从文件读入

```cpp
void brain_file_in()
{
	string tep;
	ifstream file("code.bf");
	if (!file.is_open()) 
	{
		cerr << "ERROR: I CAN'T OPEN FILE code.bf! PLS TRY READ BY CIN!" << endl;
		flag = 2;
	}
	while (getline(file, tep))//处理EOF
		code += tep;
	file.close();
}
```

#### 从键盘输入

```cpp
void brain_cin_in()
{
	cout << "U CAN USE 'ctrl + z' TO STOP CIN" << endl;
	string tep;
	while (getline(cin, tep))//处理EOF
		code += tep;
	cin.clear();
}
```

#### 解释

```cpp
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
```

‍
