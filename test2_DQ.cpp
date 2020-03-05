//[12, -2, -24, 20, -2, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7]를 가지고 있을 때

#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef struct MaxSum
{
	int left;
	int right;
	int sum;
}MaxSum;

//typedef struct Ele
//{
//	int value;
//	int index;
//}Ele;

void FindMaxSum(vector<int> OriginList, MaxSum & Root)
{
	MaxSum Left;
	MaxSum Right;
	int pivot = Root.left + (Root.right - Root.left) / 2;

	if (Root.left == Root.right)
	{
		Root.sum = OriginList[Root.right - 1];
		return;
	}
	else if(Root.right - Root.left == 1)
	{
		Left.left = Root.left;
		Left.right = Root.left;
		Left.sum = OriginList[Root.left - 1];

		Right.left = Root.right;
		Right.right = Root.right;
		Right.sum = OriginList[Root.right - 1];
	}
	else
	{
		Left.left = Root.left;
		Left.right = pivot;
		FindMaxSum(OriginList, Left);

		Right.left = pivot + 1;
		Right.right = Root.right;
		FindMaxSum(OriginList, Right);
	}

	//하나만 붙어 있을 경우
	

	//둘다 붙어 있을 경우
	if (Left.right + 1 == Right.left)
	{
		if (Left.sum + Right.sum > Left.sum && Left.sum + Right.sum > Right.sum)
		{
			Root.left = Left.left;
			Root.right = Right.right;
			Root.sum = Left.sum + Right.sum;
			cout << "result1.1 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot <<"(pivot)" << endl;
			return;
		}
		else if (Left.sum >= Right.sum)
		{
			Root = Left;
			cout << "result1.2 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}
		else
		{
			Root = Right;
			cout << "result1.3 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}
	}
	else if (Left.right == pivot)
	{
		int tmpsum = Left.sum;
		for (int i = Left.right + 1; i <= Root.right; i++)
		{
			tmpsum += OriginList[i - 1];
			if (tmpsum > Left.sum)
			{
				Left.right = i;
				Left.sum = tmpsum;
			}
		}
		if (Left.right + 1 == Right.left || Left.right >= Right.left)
		{
			Root.left = Left.left;
			Root.right = Right.right;
			Root.sum = 0;
			for (int i = Root.left; i <= Root.right; i++)
			{
				Root.sum += OriginList[i - 1];
			}
			cout << "result2.1 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}
		else if (Left.sum >= Right.sum)
		{
			Root = Left;
			cout << "result2.2 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}
		else
		{
			Root = Right;
			cout << "result2.3 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}
	}
	else if (Right.left == pivot + 1)
	{
		int tmpsum = Right.sum;
		for (int i = Right.left - 1; i >= Root.left; i--)
		{
			tmpsum += OriginList[i - 1];
			if (tmpsum > Right.sum)
			{
				Right.left = i;
				Right.sum = tmpsum;
			}
		}
		if (Left.right + 1 == Right.left || Left.right >= Right.left)
		{
			Root.left = Left.left;
			Root.right = Right.right;
			Root.sum = 0;
			for (int i = Root.left; i <= Root.right; i++)
			{
				Root.sum += OriginList[i - 1];
			}
			cout << "result2.1 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}
		else if (Left.sum >= Right.sum)
		{
			Root = Left;
			cout << "result2.2 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}
		else
		{
			Root = Right;
			cout << "result2.3 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}
	}
	//둘다 떨어져 있을 경우
	else
	{
		if (Left.sum >= Right.sum)
		{
			Root = Left;
			cout << "result3.1 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}
		else
		{
			Root = Right;
			cout << "result3.2 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}

	}

}

int main()
{
	string strInput;
	vector<int> OriginList;
	MaxSum ResultMaxSum;

	cout << "배열을 입력하세요 : ";
	getline(cin, strInput);

	string strNum = "";
	for (int i = 0; i < strInput.length(); i++)
	{
		if (strInput.at(i) == ' ')
		{
			OriginList.push_back(atoi(strNum.c_str()));
			strNum = "";
		}
		else
		{
			strNum += strInput.at(i);
			continue;
		}
	}
	OriginList.push_back(atoi(strNum.c_str()));

	ResultMaxSum.left = 1;
	ResultMaxSum.right = OriginList.size();
	FindMaxSum(OriginList, ResultMaxSum);

	cout << "result : " << ResultMaxSum.left << "(left) " << ResultMaxSum.right << "(right) " << ResultMaxSum.sum << "(sum)" << endl;
	

	return 0;
}