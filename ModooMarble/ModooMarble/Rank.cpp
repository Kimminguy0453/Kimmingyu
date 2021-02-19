#include "Rank.h"
#include "ResoucesManager.h"


Rank::Rank()
{
	memset(&PaperRank, 0, sizeof(int)*5);//배열 부분 0으로 초기화
	memset(&FlightRank, 0, sizeof(int)*5);
}

void Rank::LoadRank(int type)
{
	HANDLE hFile;
	DWORD ReadGame;
	int Score = 0;
	if (type == SCENE_INDEX_PAPER)
	{
		HANDLE hFile = CreateFile(TEXT("PaperGameRank.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		for (int i = 0; i < 5; i++)
		{
			DWORD readB;
			ReadFile(hFile, &Score, sizeof(int), &readB, NULL);
			PaperRank.push_back(Score);
		}
		CloseHandle(hFile);
	}
	else
	{
		HANDLE hFile = CreateFile(TEXT("FilghtGameRank.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		for (int i = 0; i < 5; i++)
		{
			DWORD readB;
			ReadFile(hFile, &Score, sizeof(int), &readB, NULL);
			FlightRank.push_back(Score);
		}
		CloseHandle(hFile);
	}
}

void Rank::SaveRank(int type)
{
	DWORD WriteGame;
	int score;
	if (type == SCENE_INDEX_PAPER)
	{
		HANDLE hFile = CreateFile(TEXT("PaperGameRank.txt"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		for (int i = 0; i < 5; i++)
			WriteFile(hFile, &PaperRank[i], sizeof(int), &WriteGame, NULL);
		CloseHandle(hFile);
	}
	else if (type == SCENE_INDEX_FLIGHT)
	{
		HANDLE hFile = CreateFile(TEXT("FilghtGameRank.txt"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		for (int i = 0; i < 5; i++)
			WriteFile(hFile, &FlightRank[i], sizeof(int), &WriteGame, NULL);
		CloseHandle(hFile);
	}
}

void Rank::RenewalRank(int Score, int type)
{
	int tmp;
	int score = Score;
	if (type == SCENE_INDEX_PAPER)
	{
		for (int i = 0; i < 5; i++)
		{
			if (PaperRank[i] < score)
			{
				tmp = PaperRank[i];
				PaperRank[i] = score;
				score = tmp;
			}
			else if (PaperRank[i] == score)
				break;
		}
	}
	else if (type == SCENE_INDEX_FLIGHT)
	{
		for (int i = 0; i < 5; i++)
		{
			if (FlightRank[i] < Score)
			{
				tmp = FlightRank[i];
				FlightRank[i] = Score;
				Score = tmp;
			}
			else if (FlightRank[i] == Score)
				break;
		}
	}
}

void Rank::InitGameType(int type)
{
	GameType = type;
}
Rank::~Rank()
{
	PaperRank.clear();
	FlightRank.clear();
}
