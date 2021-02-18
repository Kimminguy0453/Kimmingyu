#include "Rank.h"
#include "ResoucesManager.h"


Rank::Rank()
{
}

void Rank::LoadRank()
{
	HANDLE hFile;
	DWORD ReadGame;
	int Score;

	hFile = CreateFile(TEXT("PaperGameRank.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		for (int i = 0; i < 5; i++)
		{
			ReadFile(hFile, &Score, sizeof(int), &ReadGame, NULL);
			PaperRank[i] = Score;
		}
		CloseHandle(hFile);
	}
	else
	{
		memset(&PaperRank, 0, sizeof(OPENFILENAME));
		SaveRank(SCENE_INDEX_PAPER);
	}

	hFile = CreateFile(TEXT("FilghtGameRank.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		for (int i = 0; i < 5; i++)
		{
			ReadFile(hFile, &Score, sizeof(int), &ReadGame, NULL);
			FlightRank[i] = Score;
		}
		CloseHandle(hFile);
	}
	else
	{
		memset(&FlightRank, 0, sizeof(OPENFILENAME));
		SaveRank(SCENE_INDEX_FLIGHT);
	}
}

void Rank::SaveRank(int type)
{
	HANDLE hFile; 
	DWORD WriteGame;
	if (type == SCENE_INDEX_PAPER)
	{
		for (int i= 0; i < 5; i++)
		{
			hFile = CreateFile(TEXT("PaperGameRank.txt"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
			WriteFile(hFile, &PaperRank[i], sizeof(int), &WriteGame, NULL);
		}
		CloseHandle(hFile);
	}
	else if (type == SCENE_INDEX_FLIGHT)
	{
		for (int i = 0; i < 5; i++)
		{
			hFile = CreateFile(TEXT("FilghtGameRank.txt"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
			WriteFile(hFile, &FlightRank[i], sizeof(int), &WriteGame, NULL);
		}
		CloseHandle(hFile);
	}
}

void Rank::RenewalRank(int Score, int type)
{
	int tmp;
	if (type == SCENE_INDEX_PAPER)
	{
		for (int i = 0; i < 5; i++)
		{
			if (PaperRank[i] < Score)
			{
				tmp = (PaperRank[i]);
				PaperRank[i] = Score;
				Score = tmp;
			}
			else if (PaperRank[i] == Score)
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
}
