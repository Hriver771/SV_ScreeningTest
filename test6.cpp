# include <vector>
#include <iostream>
#include <string>

using namespace std;

void PrintMatrix(const vector<vector<int>> mat)
{
	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[i].size(); j++)
		{
			cout << mat[i][j] << "\t";
		}
		cout << endl;
	}
}

int main()
{
	int N;
	int M;
	string strInput;
	vector<vector<int>> OriginMatrix;

	cout << "Enter the number of N: ";
	cin >> N;
	cout << "Enter the number of M: ";
	cin >> M;
	getchar(); //"\n" 무시하기 위해서

	for (int i = 0; i < N; i++)
	{
		vector<int> newRow;
		getline(cin, strInput);

		string strNum = "";
		for (int j = 0; j < strInput.length(); j++)
		{

			if (strInput.at(j) == ' ')
			{
				newRow.push_back(atoi(strNum.c_str()));
				strNum = "";
			}
			else
			{
				strNum += strInput.at(j);
				continue;
			}
		}
		newRow.push_back(atoi(strNum.c_str()));
		OriginMatrix.push_back(newRow);
	}

	if (OriginMatrix.size() != N)
	{
		cout << "Input error : not mached colum size" << endl;
	}
	for (vector<int> row : OriginMatrix)
	{
		if (row.size() != M)
		{
			cout << "Input error : not mached row size" << endl;
		}
	}

	PrintMatrix(OriginMatrix);


}