/***************************************************************************
 *      � � � � � � � � � � � �   � � � � � �   � 2   � �   � � � �        *
 *-------------------------------------------------------------------------*
 *                                                                         *
 * Project Name  : Fly_Plate                                               *
 * Project Type  : Win64 Console application                               *
 * File Name     : Secondary_functions.cpp                                 *
 * Language      : VS2022                         C++                      *
 * Programmers   : ������� �. �.                                           *
 * Modified By   :                                                         *
 * Created       : 01 / 11 / 2023                                          *
 * Last Revision : 16 / 11 / 2023                                          *
 * Comment(s)    : ������� �������������� ����� ����� ������������         *
 *                 �����������. ������������ ������� ���������.            *
 *                 ����������� ������. ����������.                         *
 **************************************************************************/

#include "Secondary_functions.h"                            // ���������� ������������ ���� � ����������� ��������������� ������� 

// �������� ����� ���� �� �������� �������
bool Hit_FlyingPlate_Bullets(Bullet* CurBullet              // ��������� �������� ������ �������� �������
	                       , FlyingPlate* CurPlate)         // ��������� �������� ������ ���������
{
	// �������� ������������ �������
	double bulletX = CurBullet->GetX();                            // ���������� X ����
	double bulletY = CurBullet->GetY() - CurBullet->GetCaliber();  // ������� ���������� Y �� ��� ����
	double caliber = CurBullet->GetCaliber();                      // ������ ����
	double plateLeftBorder = CurPlate->Left_Border();              // ����� ������� �������� �������
	double plateRightBorder = CurPlate->Right_Border();            // ������ ������� �������� �������
	double plateLowBorder = CurPlate->Low_Border();                // ������ ������� �������� �������
	double plateHighBorder = CurPlate->High_Border();              // ������� ������� �������� �������
	double isPlateVisible = CurPlate->IsVisible();                 // �������� ������� ���� �� ������

	// ���� ���� ��������� ����� ������ � ����� �������� �������� ������� � ��������� ����� ���� �������� ������ ����� �������� �������,
	// �� �� ����� �� ������� ������� ����� �������� �������, � �������� ������� ����� �� ������
	if ((plateLeftBorder <= bulletX)
		&& (bulletX <= plateRightBorder)
		&& (plateLowBorder <= bulletY - caliber)
		&& (bulletY - caliber <= plateHighBorder)
		&& (isPlateVisible))
	{
		// ������� ���� ��������� ���� � �������� �������
		return(true);
	}
	else
	{
		// ����� - � ������ �������� ������� ���� �� ������
		return(false);
	}// if
}


// �������� ����� ����� �� �������� �������
bool Hit_FlyingPlate_Bombs(Bomb* CurBomb                    // ��������� �������� ������ ����
	                     , FlyingPlate* CurPlate)           // ��������� �������� ������ �������� �������
{
	// �������� ������������ �������
	double BombX = CurBomb->GetX();                         // ���������� X �����
	double BombY = CurBomb->GetY();                         // ���������� Y �����
	double radius = CurBomb->GetRadius() * 4;               // ������ �����
	double plateLeftBorder = CurPlate->Left_Border();       // ����� ������� �������� �������
	double plateRightBorder = CurPlate->Right_Border();     // ������ ������� �������� �������
	double plateLowBorder = CurPlate->Low_Border();         // ������ ������� �������� �������
	double plateHighBorder = CurPlate->High_Border();       // ������� ������� �������� �������
	double isPlateVisible = CurPlate->IsVisible();          // �������� ������� ���� �� ������

	// ���� ����� ��������� ����� ������ � ����� �������� �������� ������� � ��������� ����� ����� (� ������ �������) �������� ������ ����� �������� �������,
	// �� �� ����� �� ������� ������� ����� �������� �������, � �������� ������� ����� �� ������
	if ((plateLeftBorder <= BombX)
		&& (BombX <= plateRightBorder)
		&& (plateLowBorder <= BombY - radius)
		&& (BombY - radius <= plateHighBorder)
		&& (isPlateVisible))
	{
		// ������� ���� ��������� ����� � �������� �������
		return(true);
	}
	else
	{
		// ����� - � ������ �������� ������� ����� �� ������
		return(false);
	}// if 
}


// �������� ����� ����� �� ��������
bool Hit_Asteroids_Bombs(Bomb* CurBomb                      // ��������� �������� ������ ����
	                   , Asteroid* CurAsteroid)             // ��������� �������� ������ ���������

{
	// �������� ������������ �������
	double bombX = CurBomb->GetX();                             // ���������� X �����
	double bombY = CurBomb->GetY();                             // ���������� Y �����
	double radius = CurBomb->GetRadius() * 4;                   // ������ �����
	double asteroidLeftBorder = CurAsteroid->Left_Border();     // ����� ������� ���������
	double asteroidRightBorder = CurAsteroid->Right_Border() + 5;   // ������ ������� ���������
	double asteroidLowBorder = CurAsteroid->Low_Border();           // ������ ������� ���������
	double asteroidHighBorder = CurAsteroid->High_Border();         // ������� ������� ���������
	double isAsteroidVisible = CurAsteroid->IsVisible();            // �������� ���� �� ������

	// ���� ����� ��������� ����� ������ � ����� �������� ��������� � ��������� ����� ����� (� ������ �������) �������� ������ ����� ���������,
	// �� �� ����� �� ������� ������� ����� ���������, � �������� ����� �� ������
	if ((asteroidLeftBorder <= bombX)
		&& (bombX <= asteroidRightBorder)
		&& (asteroidLowBorder <= bombY - radius)
		&& (bombY - radius <= asteroidHighBorder)
		&& (isAsteroidVisible))
	{
		// ������� ���� ��������� ����� � ��������
		return(true);
	}
	else
	{
		// ����� - � ������ �������� ����� �� ������
		return(false);
	}// if
}


// �������� ����� ������� �� �������� �������
bool HitShip_Plate(Ship* CurShip                            // ��������� �������� ������ �������
	             , FlyingPlate* CurPlate                    // ��������� �������� ������ �������� �������
	             , int& schet)                              // ������� ����� ��������� �� ������ ��� ���������
{
	// �������� ������������ �������
	double plateLeftBorder = CurPlate->Left_Border();       // ����� ������� �������� �������
	double plateRightBorder = CurPlate->Right_Border();     // ������ ������� �������� �������
	double plateLowBorder = CurPlate->Low_Border();         // ������ ������� �������� �������
	double plateHighBorder = CurPlate->High_Border();       // ������� ������� �������� �������
	double isPlateVisible = CurPlate->IsVisible();          // �������� ������� ���� �� ������

	double shipLeft = CurShip->Left_Border();               // ����� ������� �������
	double shipRight = CurShip->Right_Border();             // ������ ������� �������
	double shipHigh = CurShip->High_Border();               // ��� �������
	double shipLow = CurShip->Low_Border();                 // ���� �������

	// ���� ������ ������� �������� ������� ��������� ����� ����� � ������ �������� �������
	// � ������ ������� ������� ��������� ���� ������ ������� �������� ������� � ���� ����� �������� ������� � �������� ������� �� ������
	// ��� ����� ������� �������� ������� ������ ������ ������� ������� � ������ ������� ������� ������ ������ ������� �������� �������
	// � ������� ������� ������� ��������� ���� ������� ������ �������� ������� � ������ ������� ������� ��������� ���� ������ ������� �������� �������
	// � �������� ������� �����
	if (plateRightBorder >= shipLeft && shipRight >= plateRightBorder
		&& (shipLow <= plateHighBorder
		&& (shipHigh >= plateLowBorder)
		&& isPlateVisible)
		|| plateLeftBorder <= shipRight && shipRight <= plateRightBorder
		&& (shipLow <= plateHighBorder)
		&& (shipHigh >= plateLowBorder)
		&& isPlateVisible)
	{
		// ��������� ����, ��������� �������
		schet = schet + 1;
		// ������� ��������� ������� �� �����
		Count(schet);
		// ���� ��������� - ������� ���� ����� ������� �� �������� �������
		return(true);
	}
	else
	{
		// ���� ������� �� ������ �������� ������� �� ���������
		return(false);
	}// if
}


// �������� ����� ���� �� ��������
bool HitBullet(Bullet* CurBullet                           // ��������� �������� ������ ����
	         , Asteroid** CurAsteroid                      // ��������� �� ��������� �������� ������ ���������, ����� ����� ���������� � ���� ��������, � ������� ��������� ���� �����
	         , Asteroid** Asteroids)                       // ������ ���������� ��� �������� ����� � ������ �� ����������
{
	// ��� �����
	int i;
	double bulletX, bulletY, asteroidLeftBorder, asteroidRightBorder, asteroidLowBorder, asteroidHighBorder;
	bool isAsteroidVisible;

	// �������� � ����� ���������� ��������� ������������
	for (i = 0; i < CountMeteor; i++)
	{
		// ����������� ������� ��������
		(*CurAsteroid) = Asteroids[i];

		// �������� ������������ �������
		bulletX = CurBullet->GetX();                            // ���������� X ����
		bulletY = CurBullet->GetY() - CurBullet->GetCaliber();  // ������� ���������� Y �� ��� ����
		asteroidLeftBorder = (*CurAsteroid)->Left_Border();     // ����� ������� ���������
		asteroidRightBorder = (*CurAsteroid)->Right_Border();   // ������ ������� ���������
		asteroidLowBorder = (*CurAsteroid)->Low_Border();       // ������ ������� ���������
		asteroidHighBorder = (*CurAsteroid)->High_Border();     // ������� ������� ���������
		isAsteroidVisible = (*CurAsteroid)->IsVisible();        // �������� ���� �� ������

		// ���� ���� ��������� ����� ������ � ����� �������� ��������� � ��������� ����� ���� �������� ������ ����� ���������,
		// �� �� ����� �� ������� ����� ���������. ��� ���� ������� �������� ����� �� ������
		if (asteroidLeftBorder <= bulletX && bulletX <= asteroidRightBorder &&
			asteroidLowBorder <= bulletY && bulletY <= asteroidHighBorder && isAsteroidVisible)
		{
			// ������������� ��������, � ������� ������ ����
			*CurAsteroid = Asteroids[i];
			// �����������, ��� ����� ���������� � ������� �������� ����������
			return (true);
		}// if
	}// for i

	// ���� �� ������ �� � ���� �� ����������
	return(false);
}


// �������� ����� ������� �� ��������
bool HitShip(Ship* CurShip                                 // ��������� �������� ������ �������
	       , Asteroid** CurAsteroid                        // ��������� �� ��������� �������� ������ ���������, ����� ����� ���������� � ���� ��������, ������� ����� �����������
	       , Asteroid** Asteroids)                         // ������ ���������� ��� �������� ����� � ������ �� ����������
{
	// ��� �����
	int i;
	double asteroidRight, asteroidLeft, shipLeft, shipRight, asteroidHigh, asteroidLow, shipHigh, shipLow;
	bool asteroidVisible;

	// �������� � ����� ���������� ��������� ������������. �������� �� ���� ����������
	for (i = 0; i < CountMeteor; i++)
	{
		// ����������� ������� ��������
		(*CurAsteroid) = Asteroids[i];

		// �������� ������������ �������
		asteroidRight = (*CurAsteroid)->Right_Border();    // ������ ������� ���������
		asteroidLeft = (*CurAsteroid)->Left_Border();      // ����� ������� ���������
		shipLeft = CurShip->Left_Border();                 // ����� ������� �������
		shipRight = CurShip->Right_Border();               // ������ ������� �������
		asteroidHigh = (*CurAsteroid)->High_Border();      // ��� ���������
		asteroidLow = (*CurAsteroid)->Low_Border();        // ���� ���������
		shipHigh = CurShip->High_Border();                 // ��� �������
		shipLow = CurShip->Low_Border();                   // ���� �������
		asteroidVisible = (*CurAsteroid)->IsVisible();     // �������� ���� �� ������

		// ���� ������ ������� ��������� ��������� ����� ����� � ������ �������� �������
		// � ������ ������� ������� ��������� ���� ������ ������� ��������� � ������� �������� �� �����
		// ��� ����� ������� ��������� ������ ������ ������� ������� � ������ ������� ������� ������ ������ ������� ���������
		// � ������� ������� ������� ��������� ���� ������� ������ ��������� � ������ ������� ������� ��������� ���� ������ ������� ���������
		// � ������� �������� �����
		if (((asteroidRight >= shipLeft && shipRight >= asteroidRight)
			&& (shipLow <= asteroidHigh && shipHigh >= asteroidLow)
			&& asteroidVisible)
			|| ((asteroidLeft <= shipRight && shipRight <= asteroidRight)
				&& (shipLow <= asteroidHigh && shipHigh >= asteroidLow)
				&& asteroidVisible))
		{
			// ������������� ��������, � ������� ����� �������
			*CurAsteroid = Asteroids[i];
			// �����������, ��� ����� ���������� � ������� �������� ��������
			return(true);
		}// if
	}// for i

   // ���� �� ���������
	return(false);
}


// ����� �������� �������
void changeFlyingPlate(FlyingPlate** CurPlate               // ��������� �� ��������� �������� ������ �������� �������
	                 , FlyingPlate** Plates                 // ��������� �� ������ ������� ������� ���������� �� ������� ������ Plates � ��� �����������
	                 , Bomb* CurBomb                        // ��������� �������� ������ �����
	                 , int transition_matr_Flying_Plate[][CountBombs]  // ������� �������� �������� �������
	                 , int& schet)                          // ������� ����� ��������� �� ������ ��� ���������
{
	// ������ � �������� ������� ��������������� ��� �� ������ �� ������� ��������� - ������� ����������. ������� �������������
	if ((transition_matr_Flying_Plate[(*CurPlate)->GetNum()][CurBomb->GetNumb()] != (*CurPlate)->GetNum()))
	{
		// ���������� ��������
		schet = schet + 1;
		// ����� ���������� �������� �� �����
		Count(schet);
	}// if

	double CurrX;                       // ������� ���������� X �������� �������
	double CurrY;                       // ������� ���������� Y �������� �������       
	CurrX = (*CurPlate)->GetX();        // �������� � ��������� �������� �������
	CurrY = (*CurPlate)->GetY();        // �������� Y ��������� �������� �������
	CurBomb->Hide();                    // ������ �����
	(*CurPlate)->Hide();                // ������ ������� �������� �������

    // �������� ����� �������� ������� �������� ������� ���������
	(*CurPlate) = Plates[transition_matr_Flying_Plate[(*CurPlate)->GetNum()][CurBomb->GetNumb()]];
	// ������������� ���������� X ��� ����� �������� ������� �� ����� ������
	(*CurPlate)->SetX(CurrX);
	// ������������� ���������� Y ��� ����� �������� ������� �� ����� ������
	(*CurPlate)->SetY(CurrY);
	// ���������� ��������� �������� ������� ����� �����
	(*CurPlate)->Show();
}


// ����� ���������
void changeAsteroid(Asteroid** CurAsteroid                  // ��������� �� ��������� �������� ������ ���������
	              , Bullet* CurBullet                       // ��������� �������� ������ ����
	              , Asteroid** Asteroids                    // ��������� �� ������ ������� ������� ���������� �� ������� ������ Asteroid � ��� �����������
	              , int transition_matr[][CountBullets]     // ������� �������� ����������
	              , int dead_matr[][CountBullets])          // ������� ������� ����������. ��� ��������� ��������� �� ����� ����� ����� ������� ����� ���������

{
	double CurrX;                                           // ������� ���������� � ���������
	double CurrY;                                           // ������� ���������� Y ���������
	CurrX = (*CurAsteroid)->GetX();                         // �������� � ���������� ���������
	CurrY = (*CurAsteroid)->GetY();                         // �������� Y ���������� ���������
	CurBullet->Hide();                                      // ������ ����
	(*CurAsteroid)->Hide();                                 // ������ ������� ��������

	// ���� ������� �������� �������� ����������� � ������ ��������� ����� ��������� �� ����� �����
	// ����� ����� � ������� ������� ��� ��������� ������ ���������
	if (dead_matr[(*CurAsteroid)->GetNumber()][CurBullet->GetScale()] != DeadNumber)
	{
		// ������������� �������� � ���� �������
		(*CurAsteroid) = Asteroids[dead_matr[(*CurAsteroid)->GetNumber()][CurBullet->GetScale()]];
		// �������� ����� ���������� Y ��� ��������� ��������� ����������
		CurrY = rand() % (HighZoneSpavn - LowZoneSpavn + 1) + LowZoneSpavn;
		// ������ ���������� Y
		(*CurAsteroid)->SetY(CurrY);
		// ���������� ����� �������� �� ����� �����
		(*CurAsteroid)->Show();
		// ����������� ������������ �� ���� ����
		return;
	}// if

	// ���� �������� �� �������� �����������, � �������� ��������. �������� ����� �������� �������� ������� ���������
	(*CurAsteroid) = Asteroids[transition_matr[(*CurAsteroid)->GetNumber()][CurBullet->GetScale()]];
	// ������������� ���������� X ��� ������ ��������� �� ����� �������
	(*CurAsteroid)->SetX(CurrX);
	// ������������� ���������� Y ��� ������ ��������� �� ����� �������
	(*CurAsteroid)->SetY(CurrY);
	// ���������� �������� �� ����� �����
	(*CurAsteroid)->Show();
	return;
}


// ����� �������
void changeShip(Ship** CurShip                         // ��������� �� ��������� �������� ������ ������� ��� ��������� �������� ���������
	          , Asteroid* CurAsteroid                  // ��������� �������� ������ ��������
	          , Ship** Ships                           // ��������� �� ������ ������� ������� ���������� �� ������� ������ Ship � ��� �����������
	          , int ship_matr[][CountMeteor])          // ������� ��������� �������
{
	// ��� ����� ���������� X �������/ ���������
	double CurrX;
	// ��� ����� ���������� Y �������/ ���������
	double CurrY;

	// ����������� � ���������� ����� ������������
	// ������ ��������
	CurAsteroid->Hide();
	// �������� ���������� Y �� ��������� ��� ��������� ����������
	CurrY = rand() % (HighZoneSpavn - LowZoneSpavn + 1) + LowZoneSpavn;
	// ������������� ���������� Y �������� ���������
	CurAsteroid->SetY(CurrY);
	// ���������� �������� �� ����� �����
	CurAsteroid->Show();

	// ����������� � ������� ����� ������������
	CurrX = (*CurShip)->GetX();                      // �������� � ������� ��� ����, ����� ����� �������� �� ��� �� �����
	CurrY = (*CurShip)->GetY();                      // �������� Y ������� ��� ����, ����� ����� �������� �� ��� �� �����
	(*CurShip)->Hide();                              // ������ ������� �������

	// �������� ����� ������� �������� ������� ���������
	(*CurShip) = Ships[ship_matr[(*CurShip)->GetSNumber()][CurAsteroid->GetNumber()]];
	// ������������� ���������� X ��� ������ ������� �� ����� �������
	(*CurShip)->SetX(CurrX);
	// ������������� ���������� Y ��� ������ ������� �� ����� �������
	(*CurShip)->SetY(CurrY);
	// ���������� ������� �� ����� �����
	(*CurShip)->Show();
	return;
}


// ��������� ��������� �� ����� ����� ����� ���� ��� �� ������ ����� �������
void RespavnAsteroid(Asteroid* CurAsteroid)                 // ��������� �������� ������ ���������
{
	double CurrY;                                           // ���������� Y ��� ���������

	// ���� �������� ����� �� ������� ������ ������� ������� ��� ����������
	if (CurAsteroid->High_Border() >= YMaxAster)
	{
		// ������ ���
		CurAsteroid->Hide();
		// �������� ���������� Y �� ��������� ��� ���������
		CurrY = rand() % (HighZoneSpavn - LowZoneSpavn + 1) + LowZoneSpavn;
		// ������������� ���������� Y �������� ���������
		CurAsteroid->SetY(CurrY);
		// ���������� �������� �� ����� �����
		CurAsteroid->Show();
		// ������� �� �������
		return;
	}// if (CurAsteroid->High_Border() >= YMaxAster)

	return;
}


// ����� �������� ������ ���������� �� �����
void Count(int schet)                                       // ��������� �������� ������ ���������
{
	// �������� ���������� ������������ ���������� ������ (�������) � ��������� ��� � ���������� hConsole
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// COORD - ��� ���������, ������������ � Windows API, ������� ������������ ��� ������������� ��������� ������� �� ������ ��� � �������.
	COORD position;
	// ������������� �������� �� ������ X � Y ������� 0.
	position.X = 0;
	position.Y = 0;
	// ������������� ������� ������� � ������� ����� ���� �������. ����� �����, ��� ������ ������ ��� ������� � �������, ��� ����� ������������ � ��������� ������� ������������ �������.
	SetConsoleCursorPosition(hConsole, position);
	// DWORD written - ��� ����������, ������������ � Windows API, ������� ������������ ��� �������� ���������� ���������� ���� ��� �������� ��� ���������� �������� �����/������.
	DWORD written;

	// FillConsoleOutputCharacter - ��� ������� �� Windows API, ������� ������������ ��� ���������� ������������� ���������� ����� �������
	// ������������ ��������. ��� ��������� ���� ����������: ������ - ���������� ������� (HANDLE), ������ - ������ ��� ����������,
	// ������ - ���������� ����� ��� ����������, ��������� - ��������� ������� ���������� (COORD),
	// ����� - ��������� �� ���������� written, � ������� ����� �������� ���������� �����, ������� ���� ���������� ���������.

	FillConsoleOutputCharacter(hConsole, ' ', 80 * 2, position, &written); // ������� 1 ������ �������

	// ������� �����-�� ���������� � ��������� ������� �������
	position.X = 100;
	position.Y = 0;
	SetConsoleCursorPosition(hConsole, position);
	// ������� ����������
	std::cout << "\t\t\t\t\t\tScore:" << schet;
	return;
}


// ������� "�����"
void WriteEnd()
{
	// �������� ���������� ������������ ���������� ������ (�������) � ��������� ��� � ���������� console
	HWND console = GetConsoleWindow();
	// LOGFONT - ��� ��������� �� Windows API, ������� ������������ ��� ����������� ��������� ������.
	LOGFONT lf;
	// memset - ��� ������� ����������� ���������� C, ������� ������������ ��� ���������� ����� ������ ������������ ���������.
	// ��� ��������� ��� ���������: ��������� �� ���� ������, �������� ��� ���������� � ���������� ����, ������� ������ ���� ���������.
	// ��������� ��� ������, ���������� ���������� lf, �������� ����������.
	memset(&lf, 0, sizeof(LOGFONT));

	// lf.lfHeight - ��� ���� ��������� LOGFONT, ������� ������������ ������ ������ � ������� (pt).
	lf.lfHeight = 60;
	// lf.lfWeight - ��� ���� ��������� LOGFONT, ������� ������������ �������� ������. �������� FW_NORMAL ��������� �� ���������� �������� ������
	lf.lfWeight = FW_NORMAL;
	// wcscpy_s - ��� ������� ����������� ���������� C, ������� ������������ ��� ����������� ������ ���� wchar_t (������� �������)
	// �� ������ ������ � ������. ��� ��������� ��� ���������: ��������� �� ������� �����, ��������� �� �������� ������ � ������������
	// ���������� ��������, ������� ����� ����������� � ������� �����.
	wcscpy_s(lf.lfFaceName, L"Arial");
	// CreateFontIndirect - ��� ������� WinAPI, ������� ������������ ��� �������� ������ �� ������ ������ � ��������� LOGFONT.
	HFONT hFont = CreateFontIndirect(&lf);
	// SelectObject - ��� ������� WinAPI, ������� ������������ ��� ��������� ������� (� ������ ������ ������)
	// � ��������� ���������� (device context), �� ���� ��������� ������ � ���������� ����������.
	SelectObject(hdc, hFont);

	// SetTextColor � SetBkMode - ��� ������� WinAPI ��� ��������� ����� ������ � ������ ���� ��������������.
	SetTextColor(hdc, RGB(127, 255, 212));
	// SetBkMode ������������ ��� ��������� ������ ����. � ������ ������ �� ������������� ����� TRANSPARENT, ������� �������� ���������� ���.
	SetBkMode(hdc, TRANSPARENT);

	// SIZE size;
	SIZE size;

	// ��� LPCWSTR ���������������� ��������� �������:
	// - LP - ��� �������, ������������ "��������� ��";
	// - C - ��� �������, ����������� �� ��, ��� ������ �������� ���������� (read-only);
	// - WSTR - ��� ���������� �� "wide string", �.�. ��������� ������.
	LPCWSTR text = L"� � � � �";
	// GetTextExtentPoint32 - ��� ������� WinAPI, ������� ������������ ��� ���������� ������ � ������ ��������� ������, ������������ � �������������� ���������� ��������� ���������� (hdc) � ������.
	GetTextExtentPoint32(hdc, text, wcslen(text), &size);

	// �������������, ��� ����� ���������� �������. � ������ ������ ��������� ������� � �������� ��������� � ������
	int consoleWidth = 148 * 8;
	int consoleHeight = 57 * 16;
	int centerX = (consoleWidth - size.cx) / 2;
	int centerY = (consoleHeight - size.cy) / 2;

	// TextOut - ��� ������� WinAPI, ������� ������������ ��� ������ ��������� ������ �� ���������� � ��������� ������������.
	TextOut(hdc, centerX, centerY, text, wcslen(text));
	DeleteObject(hFont);
	ReleaseDC(console, hdc);
	// �������� ����� ��������� �������
	Sleep(1300);
}