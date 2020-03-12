#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

typedef struct MaxSum
{
	int left;
	int right;
	int sum;
}MaxSum;

void Brute_Force(const vector<int>OriginList, MaxSum & result)
{
	vector<MaxSum> MaxSumList;


	for (int i = 0; i < OriginList.size(); i++)
	{
		int tmpSum = OriginList[i];
		MaxSum newMaxSum;
		newMaxSum.sum = OriginList[i];
		newMaxSum.left = i + 1;
		for (int j = i + 1; j < OriginList.size(); j++)
		{
			tmpSum += OriginList[j];
			if (tmpSum > newMaxSum.sum)
			{
				newMaxSum.sum = tmpSum;
				newMaxSum.right = j + 1;
			}
		}
		MaxSumList.push_back(newMaxSum);

	}

	for (int i = 0; i < MaxSumList.size(); i++)
	{
		if (i == 0) result = MaxSumList[i];
		if (result.sum < MaxSumList[i].sum)
		{
			result = MaxSumList[i];
		}
	}
}

void Divide_N_Conquer(const vector<int> OriginList, MaxSum& Root)
{
	MaxSum Left;
	MaxSum Right;
	int pivot = Root.left + (Root.right - Root.left) / 2;

	if (Root.left == Root.right)
	{
		Root.sum = OriginList[Root.right - 1];
		return;
	}
	else if (Root.right - Root.left == 1)
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
		Divide_N_Conquer(OriginList, Left);

		Right.left = pivot + 1;
		Right.right = Root.right;
		Divide_N_Conquer(OriginList, Right);
	}
	//case1
	if (Left.right + 1 == Right.left)
	{
		if (Left.sum + Right.sum > Left.sum&& Left.sum + Right.sum > Right.sum)
		{
			Root.left = Left.left;
			Root.right = Right.right;
			Root.sum = Left.sum + Right.sum;
			//cout << "result1.1 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}
		else if (Left.sum >= Right.sum)
		{
			Root = Left;
			//cout << "result1.2 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}
		else
		{
			Root = Right;
			//cout << "result1.3 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}
	}
	//case2
	else
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
		tmpsum = Right.sum;
		for (int i = Right.left - 1; i >= Root.left; i--)
		{
			tmpsum += OriginList[i - 1];
			if (tmpsum > Right.sum)
			{
				Right.left = i;
				Right.sum = tmpsum;
			}
		}
		if (Left.sum >= Right.sum)
				{
					Root = Left;
					//cout << "result2.3 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
					return;
				}
		else
		{
			Root = Right;
			//cout << "result2.4 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}
	}
}

int main()
{
	string strInput;
	vector<int> OriginList;
	MaxSum ResultMaxSumDC;
	MaxSum ResultMaxSumBF;
	int n;

	//사용자에게 입력받을 때
	//cout << "배열을 입력하세요 : ";
	//getline(cin, strInput);

	//string strNum = "";
	//for (int i = 0; i < strInput.length(); i++)
	//{
	//	if (strInput.at(i) == ' ')
	//	{
	//		OriginList.push_back(atoi(strNum.c_str()));
	//		strNum = "";
	//	}
	//	else
	//	{
	//		strNum += strInput.at(i);
	//		continue;
	//	}

	//}
	//OriginList.push_back(atoi(strNum.c_str()));

	srand(static_cast<unsigned int>(time(NULL)));

	n = 10000;
	for (int count = 1; count <= n; ++count)
	{
		int n = rand() % 500 - 250;
		OriginList.push_back(n);
		//cout << n << " ";
	}
	//cout << endl;
	cout << n << " sequence" << endl;
	ResultMaxSumDC.left = 1;
	ResultMaxSumDC.right = OriginList.size();
	clock_t s = (int)clock();
	Divide_N_Conquer(OriginList, ResultMaxSumDC);
	float DCTime = (float)(clock() - s) / CLOCKS_PER_SEC;
	cout << "Divide and Conquer result (" << DCTime << "s) : " << ResultMaxSumDC.left << "(left) " << ResultMaxSumDC.right << "(right) " << ResultMaxSumDC.sum << "(sum)" << endl;
	s = (int)clock();
	Brute_Force(OriginList, ResultMaxSumBF);
	float BFTime = (float)(clock() - s) / CLOCKS_PER_SEC;
	cout << "Brute Force result (" << BFTime << "s) : " << ResultMaxSumBF.left << "(left) " << ResultMaxSumBF.right << "(right) " << ResultMaxSumBF.sum << "(sum)" << endl;


	return 0;
}