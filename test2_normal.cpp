//�������� ������ ������ ���� �迭�� ���� �� ���� �ִ밡 �Ǵ� ������ �� ���� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.�̶� divide - and -conquer ����� �ƴ� ������� 2������ �����Ͻÿ�.�׸��� ������ 2���� ����� �迭 ���̿� ���� ó���ӵ��� ��� �Ǵ����� ? (����, �ִ밡 �Ǵ� ������ �� �̻��϶��� ���� ó���� ������ ������ ���)
//��)
//A��[12, -2, -24, 20, -2, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7]�� ������ ���� ��
//�̶� ���� �ִ밡 �Ǵ� ������ left 8, right 11�̰� �� ���� 43
//A��[2, 2, -5, 4, 0]�� ��� left 1, right 2�̰� �� ���� 4

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

	cout << "�迭�� �Է��ϼ��� : ";
	getline(cin, strInput);


	//// ���ڿ� ��� ���� �κ�
	//cout << "���ڿ�	: " << strInput << endl;
	////��͵�

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

	/////����κ�
	//cout << "����	: ";
	//for (int i = 0; i < OriginList.size(); i++)
	//{
	//	cout << OriginList[i] << " ";
	//}
	//cout << endl;
	////�������



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