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
			cout << "result1.1 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
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
	//case2(left)
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
		if (Left.right == Right.right)
		{
			if (Left.sum >= Right.sum)
			{
				Root = Left;
				cout << "result2.0(left) : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
				return;
			}
			else
			{
				Root = Right;
				cout << "result2.0(left) : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
				return;
			}
		}
		else if (Left.right >= Right.left - 1)
		{
			Root = Left;
			cout << "result2.1(left) : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}
		//if (Left.right >= Right.left)
		//{
		//	Root.left = Left.left;
		//	Root.right = Right.right;
		//	Root.sum = 0;
		//	for (int i = Root.left; i <= Root.right; i++)
		//	{
		//		Root.sum += OriginList[i - 1];
		//	}
		//	cout << "case2.left.1" << endl;
		//	//cout << "result2.1 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
		//	return;
		//}
		//else if (Left.right + 1 == Right.left)
		//{
		//	if (Left.sum < 0)
		//	{
		//		Root = Right;
		//		cout << "case2.left.2" << endl;
		//		return;
		//	}
		//	else if (Right.sum < 0)
		//	{
		//		Root = Left;
		//		cout << "case2.left.2" << endl;
		//		return;
		//	}
		//	else
		//	{
		//		Root.left = Left.left;
		//		Root.right = Right.right;
		//		Root.sum = Left.sum + Right.sum;
		//		cout << "case2.left.2" << endl;
		//		return;
		//	}
		//}
		else if (Left.sum >= Right.sum)
		{
			Root = Left;
			//cout << "case2.left.3" << endl;
			cout << "result2.2(left) : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}
		else
		{
			Root = Right;
			//cout << "case2.left.4" << endl;
			cout << "result2.3(left) : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}
	}
	//case2(right)
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
		if (Left.left == Right.left)
		{
			if (Left.sum >= Right.sum)
			{
				Root = Left;
				cout << "result2.0(right) : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
				return;
			}
			else
			{
				Root = Right;
				cout << "result2.0(right) : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
				return;
			}
		}
		else if (Left.right >= Right.left - 1)
		{
			Root = Right;
			cout << "result2.1(right) : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}
		//{
		//	Root.left = Left.left;
		//	Root.right = Right.right;
		//	Root.sum = 0;
		//	for (int i = Root.left; i <= Root.right; i++)
		//	{
		//		Root.sum += OriginList[i - 1];
		//	}
		//	cout << "case2.right.1" << endl;
		//	//cout << "result2.1 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
		//	return;
		//}
		//else if (Left.right + 1 == Right.left)
		//{
		//	if (Left.sum < 0)
		//	{
		//		Root = Right;
		//		cout << "case2.right.2" << endl;
		//		return;
		//	}
		//	else if (Right.sum < 0)
		//	{
		//		Root = Left;
		//		cout << "case2.right.2" << endl;
		//		return;
		//	}
		//	else
		//	{
		//		Root.left = Left.left;
		//		Root.right = Right.right;
		//		Root.sum = Left.sum + Right.sum;
		//		cout << "case2.right.2" << endl;
		//		return;
		//	}
		//}
		else if (Left.sum >= Right.sum)
		{
			Root = Left;
			//cout << "case2.right.3" << endl;
			cout << "result2.2(right) : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}
		else
		{
			Root = Right;
			//cout << "case2.right.4" << endl;
			cout << "result2.3(right) : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}
	}
	//case3
	else
	{
		if (Left.sum == Right.sum)
		{
			cout << "@@@@ case3 same @@@@" << endl;
		}
		int tmpsum = Left.sum;
		for (int i = Left.right + 1; i < Right.right; i++)
		{
			tmpsum += OriginList[i - 1];
		}
		tmpsum += Right.sum;
		if (tmpsum > Left.sum && tmpsum > Right.sum)
		{
			Root.left = Left.left;
			Root.right = Right.right;
			Root.sum = tmpsum;
			cout << "result3.0 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}
		else if (Left.sum >= Right.sum)
		{
			Root = Left;
			//cout << "case3.1" << endl;
			cout << "result3.1 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
			return;
		}
		else
		{
			Root = Right;
			//cout << "case3.2" << endl;
			cout << "result3.2 : " << Root.left << "(left) " << Root.right << "(right) " << Root.sum << "(sum)" << pivot << "(pivot)" << endl;
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
	for (int count = 1; count <= 20; ++count)
	{
		int n = rand() % 300 - 150;
		OriginList.push_back(n);
		cout << n << " ";
	}
	cout << endl;

	ResultMaxSumDC.left = 1;
	ResultMaxSumDC.right = OriginList.size();
	Divide_N_Conquer(OriginList, ResultMaxSumDC);
	cout << "Divide and Conquer result : " << ResultMaxSumDC.left << "(left) " << ResultMaxSumDC.right << "(right) " << ResultMaxSumDC.sum << "(sum)" << endl;
	Brute_Force(OriginList, ResultMaxSumBF);
	cout << "Brute Force result : " << ResultMaxSumBF.left << "(left) " << ResultMaxSumBF.right << "(right) " << ResultMaxSumBF.sum << "(sum)" << endl;


	return 0;
}