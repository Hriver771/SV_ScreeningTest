//정수값을 가지는 임의의 길이 배열이 있을 때 합이 최대가 되는 구간과 그 값을 구하는 프로그램을 작성하시요.이때 divide - and -conquer 방법과 아닌 방법으로 2가지를 구현하시요.그리고 구현한 2가지 방법이 배열 길이에 따른 처리속도가 어떻게 되는지요 ? (만일, 최대가 되는 구간이 둘 이상일때는 가장 처음에 나오는 구간을 출력)
//예)
//A가[12, -2, -24, 20, -2, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7]를 가지고 있을 때
//이때 합이 최대가 되는 구간은 left 8, right 11이고 그 합은 43
//A가[2, 2, -5, 4, 0]인 경우 left 1, right 2이고 그 합은 4

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

int main()
{
	string strInput;
	vector<int> OriginList;
	vector<MaxSum> MaxSumList;
	MaxSum result;

	cout << "배열을 입력하세요 : ";
	getline(cin, strInput);


	//// 문자열 출력 지울 부분
	//cout << "문자열	: " << strInput << endl;
	////요것도

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

	/////지울부분
	//cout << "숫자	: ";
	//for (int i = 0; i < OriginList.size(); i++)
	//{
	//	cout << OriginList[i] << " ";
	//}
	//cout << endl;
	////여기까지



	for (int i = 0; i < OriginList.size(); i++)
	{
		int tmpSum = OriginList[i];
		MaxSum newMaxSum;
		newMaxSum.sum = OriginList[i];
		newMaxSum.left = i+1;
		for (int j = i+1; j < OriginList.size(); j++)
		{
			tmpSum += OriginList[j];
			if (tmpSum > newMaxSum.sum)
			{
				newMaxSum.sum = tmpSum;
				newMaxSum.right = j+1;
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

	cout << "result : " << result.left << "(left) " << result.right << "(right) " << result.sum << "(sum)" << endl;





	return 0;
}