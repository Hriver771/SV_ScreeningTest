# include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void PrintMatrix(const vector<vector<int>> mat)
{
	cout << "------------------------------------------------" << endl;
	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[i].size(); j++)
		{
			cout << mat[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "------------------------------------------------" << endl;
}

int GetMaxCost_Matrix(const vector<vector<int>> Cost)
{
	vector<int> maxCost_inRow;
	for (vector<int> Row : Cost)
	{
		maxCost_inRow.push_back(*max_element(Row.begin(), Row.end()));
	}
	return *max_element(maxCost_inRow.begin(), maxCost_inRow.end());
}

void HungarianAlgo(vector<vector<int>> Cost, const int N, const int M, const int Mode, int & TotalCost, vector<int> AssignmentIndex)
{
	//정방향으로 만들기
	if (N < M)
	{
		int maxCost = GetMaxCost_Matrix(Cost);
		for (int i = 0; i < M - N; i++)
		{
			vector<int> fictionalRow(M, maxCost);
			Cost.push_back(fictionalRow);
		}
	}
	else if (N > M)
	{
		int maxCost = GetMaxCost_Matrix(Cost);
		for (int i = 0; i < N - M; i++)
		{
			for (vector<int> Row : Cost)
			{
				Row.push_back(maxCost);
			}
		}
	}
	PrintMatrix(Cost);

	int MatrixSize = Cost.size();

	//row에서 가장 작은 값 빼주기
	for (int i = 0; i < MatrixSize; i++)
	{
		int minCost = *min_element(Cost[i].begin(), Cost[i].end());
		for (int j = 0; j < MatrixSize; j++)
		{
			Cost[i][j] -= minCost;
		}
	}
	PrintMatrix(Cost);

	////colum에서 가장 작은 값 빼주기
	//for (int j = 0; j < matrixSize; j++)
	//{
	//	vector<int> colum;
	//	for (vector<int> Row : Cost)
	//	{
	//		colum.push_back(Row[j]);
	//	}
	//	int minCost = *min_element(colum.begin(), colum.end());
	//	for (int i = 0; i < matrixSize; i++)
	//	{
	//		Cost[i][j] -= minCost;
	//	}
	//}
	//PrintMatrix(Cost);

	vector<int> CoveredRow;
	vector<int> CoveredCol;
	vector<vector<bool>> StarZeros(MatrixSize, vector<bool>(MatrixSize, false));
	vector<vector<bool>> PrimeZeros(Cost.size(), vector<bool>(Cost.size(), false));

	//step 2
	for (int i = 0; i < MatrixSize; i++)
	{
		for (int j = 0; j < MatrixSize; j++)
		{
			if (Cost[i][j] == 0)
			{
				StarZeros[i][j] = true;
			}
		}
	}
	//step 3
	for (int i = 0; i < MatrixSize; i++)
	{
		for (int j = 0; j < MatrixSize; j++)
		{
			if (StarZeros[i][j] == true)
			{
				CoveredCol.push_back(j);
			}
		}
	}
	if (CoveredCol.size() == MatrixSize)
	{
		//종료
	}

	//step 4
	for (int i = 0; i < MatrixSize; i++)
	{
		auto iterR = find(CoveredRow.begin(), CoveredRow.end(), i);
		if (iterR != CoveredRow.end())
		{
			for (int j = 0; j < MatrixSize; j++)
			{
				auto iterC = find(CoveredCol.begin(), CoveredCol.end(), j);
				if (iterC != CoveredCol.end())
				{
					if (Cost[i][j] == 0)
					{
						PrimeZeros[i][j] = true;
						auto iterStarRow = find(StarZeros[i].begin(), StarZeros[i].end(), true);

						if (iterStarRow == StarZeros[i].end())
						{
							//5단계로 간다
						}
						else
						{
							CoveredRow.push_back(i);
							int removeCol = distance(StarZeros[i].begin(), iterStarRow);
							auto removeColIter = find(CoveredCol.begin(), CoveredCol.end(), removeCol);
							CoveredCol.erase(removeColIter);
							
						}
					}
				}

			}
		}
		//6단계로 감
	}

	//step 5
	vector<vector<bool>> NewZeros(MatrixSize, vector<bool>(MatrixSize, false));
	for (int i = 0; i < MatrixSize; i++)
	{
		for (int j = 0; j < MatrixSize; j++)
		{
			if (PrimeZeros[i][j] == true)
			{
				for (int k = 0; k < MatrixSize; k++)
				{
					if (StarZeros[k][j] == true)
					{
						break;
					}
					if (k + 1 == MatrixSize)
					{
						NewZeros[i][j] = true;

					}
				}

			}
		}
	}
}

void main()
{
	int N;
	int M;
	int Mode;
	string strInput;
	vector<vector<int>> OriginMatrix;
	int TotalCost;
	vector<int> AssignmentIndex;

	cout << "Enter the number of worker(N): ";
	cin >> N;
	cout << "Enter the number of job(M): ";
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
		return;
	}
	for (vector<int> row : OriginMatrix)
	{
		if (row.size() != M)
		{
			cout << "Input error : not mached row size" << endl;
			return;
		}
	}

	Mode = 0;
	HungarianAlgo(OriginMatrix, N, M, Mode, TotalCost, AssignmentIndex);



}