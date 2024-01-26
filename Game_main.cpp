/***************************************************************************
 *      � � � � � � � � � � � �   � � � � � �   � 2   � �   � � � �        *
 *-------------------------------------------------------------------------*
 *                                                                         *
 * Project Name  : Fly_Plate                                               *
 * Project Type  : Win64 Console application                               *
 * File Name     : Game_main.cpp                                           *
 * Language      : VS2022                                                  *
 * Modified By   :                                                         *
 * Created       : 01 / 11 / 2023                                          *
 * Last Revision : 16 / 11 / 2023                                          *
 * Comment(s)    : ������� �������������� ����� ����� ������������         *
 *                 �����������. ������������ ������� ���������.            *
 *                 ����������� ������. ����������.                         *
 **************************************************************************/

#include "constants.h"             // ���������� ���� � ����������� ���������� ��������
#include "Secondary_functions.h"   // ���������� ������������ ���� � ����������� ��������������� �������     
#include "asteroid_co.h"           // ���������� ������������ ���� � ��������
#include <string>                  // ��� �������� ����������� ������ ��������� �����
#pragma comment (lib, "winmm.lib") // ������ �� ������

//������ ��� ����������� ���� ������� �������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
HWND GetConsoleWindow();           // ��������� ���������� ����, ������������ ��������, ��������� � ���������� ���������.


/***********************************************************************/
/*               � � � � � � � �    � � � � � � � � �                  */
/***********************************************************************/
int main()
{

	// �������� ���������� ������������ ������ �������
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// ��������� ������� �����
	// ������������ ��� ���������� ���������� � ������� ������ �������, ����� ��� ��� ������ � �����.
	CONSOLE_FONT_INFOEX fontInfo;
	// ��������� ������� �����, ����� ��������� CONSOLE_FONT_INFOEX ���������� � �������, ������� ������� ���������� � ������� ���������.
	fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	// ����� � ���������� ��������
	GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

	// ��������� ������ ������� ������
	fontInfo.dwFontSize.X = 14;
	fontInfo.dwFontSize.Y = 20;

	// ������������� �����
	SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

	// ������������ ��� ���������� ���������� � ������� ������ ������, ����� ��� �������, ��������� ������� � �������� ������.
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	// �������, ������� �������� ���������� � ������ ������ ������� � ��������� �� � ��������� bufferInfo.
	GetConsoleScreenBufferInfo(hConsole, &bufferInfo);

	// ��������� ������ ����� ������
	// ���� FOREGROUND_GREEN ���������, ��� ����� ���������� ������� ����.
	// ���� FOREGROUND_INTENSITY ���������, ��� ���� ������ ������ ���� ����� ����������� ��� �����.
	// ����� ��� ��� ����� �������������, �� �������� ���� ������� � � ����� ������� ��������������.

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	// �������� ���������� ���� �������
	HWND hwnd = GetConsoleWindow();
	// RECT - ��� ���������, ������������ � Windows API ��� ������������� ������������� �������.
	RECT rect;
	// �������� ������� ������� ���� ������� ����� �������������
	GetWindowRect(hwnd, &rect);
	// �������� ������� ���� �������
	MoveWindow(hwnd, rect.left, rect.top, 121 * 8, 46 * 16, TRUE);

	// ��������� ���� �����
	string filePath = "C:\\Users\\������� �������\\Music\\song.mp3";
	wstring wFilePath(filePath.length(), L' ');
	MultiByteToWideChar(CP_ACP, 0, filePath.c_str(), filePath.length(), &wFilePath[0], wFilePath.length());
	// ��� �������� ������������ ��� ����, ����� ���������, ��� ������� GetConsoleWindow() 
	// ������� ������� ���������� ���� �������, � �� NULL, ��� ����� ���������, ���� ���������� ������� �� 
	// ������� � ��������� �������, ���� ���� ��������� ������ ������ ��� ��������� �����������
	// ��������� ���� ��� ���������������
	if (mciSendString((TEXT("open \"") + wFilePath + TEXT("\" type mpegvideo alias music")).c_str(), NULL, 0, NULL) != 0) 
	{
		return 1;
	}

	// �������� ����������� ������ � ������� ������
	if (mciSendString(TEXT("play music repeat"), NULL, 0, NULL) != 0) 
	{
		return 2;
	}

	/****************************************************�������� ���������******************************************************/
	
	int x0 = 500;           // ��������� ���������� ������ �� OX
	int y0 = 800;           // ��������� ���������� ������ �� OY
	int i = 0;              // ��� �����
	int schet = 0;          // ���������� ��������� �����

	bool left = false;      // �������� ��� �������� �������� ������� �����
	bool right = true;      // �������� ��� �������� �������� ������� ������
	bool key = true;        // ���� ��� ������ � ������
	bool move;              // ���� �������� ����/�����         


	// ������ ����������
	Asteroid** Asteroids = new Asteroid * [CountMeteor];      // �������� ������������� ������� ���������� �� ������� ������ Asteroid � ��� �����������
	Asteroids[0] = new White_Warlic(x0 - 350, y0 - 450);      // ��������� �� ������ ������ White_Warlic
	Asteroids[1] = new Cold_White_Warlic(x0 + 200, y0 - 470); // ��������� �� ������ ������ Cold_White_Warlic
	Asteroids[2] = new Brown_Warlic(x0 - 50, y0 - 350);       // ��������� �� ������ ������ Brown_Warlic
	Asteroids[3] = new Neutron_Star(x0 + 550, y0 - 420);      // ��������� �� ������ ������ Neutron_Star
	Asteroids[4] = new Brown_Warlic(x0, y0);                  // ��������� �� ������ ������ Brown_Warlic. ���������������
	Asteroids[5] = new Cold_White_Warlic(x0, y0);             // ��������� �� ������ ������ Cold_White_Warlic. ���������������
	Asteroids[6] = new Neutron_Star(x0, y0);                  // ��������� �� ������ ������ Neutron_Star. ���������������
	Asteroids[7] = new Neutron_Star(x0, y0);                  // ��������� �� ������ ������ Neutron_Star. ���������������
	Asteroids[8] = new Dead_Star(x0, y0);                     // ��������� �� ������ ������ Dead_Star
	Asteroid* CurAsteroid = Asteroids[0];                     // ��������� �������� ������ ��������� �� ����� White_Warlic
	
	
	// ������ �������� �������
	FlyingPlate** Plates = new FlyingPlate * [CountFlyingPlates];   // �������� ������������� ������� ���������� �� ������� ������ FlyingPlate � ��� �����������
	Plates[0] = new FlyingPlate(x0 - 420, y0 - 600);                // ������ ������ FlyingPlate
	Plates[1] = new Broke_FlyingPlate(x0 - 420, y0 - 600);          // ������ ������ Broke_FlyingPlate
	Plates[2] = new Angry_FlyingPlate(x0 - 420, y0 - 600);          // ������ ������ Angry_FlyingPlate
	Plates[3] = new Modify_FlyingPlate(x0 - 420, y0 - 600);         // ������ ������ Modify_FlyingPlate
	FlyingPlate* CurPlate;                                          // ��������� ��������� �������� ������
	CurPlate = Plates[0];                                           // ��������� �������� ������ ��������� �� ����� FlyingPlate
	CurPlate->Show();


	// ������ �������� ��������
	Ship** Ships = new Ship * [CountShips];                   // �������� ������������� ������� ���������� �� ������� ������ Ship � ��� �����������
	Ships[0] = new Ship(x0, y0);                              // ������ ������ Ship
	Ships[1] = new Broke_Ship(x0, y0);                        // ������ ������ Broke_Ship
	Ships[2] = new Infinity_Ship(x0, y0);                     // ������ ������ Infinity_Ship
	Ship* CurShip;                                            // ��������� ��������� �������� ������
	CurShip = Ships[0];                                       // ��������� �������� ������ ��������� �� ����� Ship


	// ������ ����
	Bullet** Bullets = new Bullet * [CountBullets];           // �������� ������������� ������� ���������� �� ������� ������ Bullet � ��� �����������
	Bullets[0] = new Bullet(x0, y0);                          // ��������� �� ������ ������ Bullet
	Bullets[1] = new Yellow_Bullet(x0, y0);                   // ��������� �� ������ ������ Yellow_Bullet
	Bullets[2] = new Red_Bullet(x0, y0);                      // ��������� �� ������ ������ Red_Bullet
	Bullets[3] = new Green_Bullet(x0, y0);                    // ��������� �� ������ ������ Green_Bullet
	Bullets[4] = new Blue_Bullet(x0, y0);                     // ��������� �� ������ ������ Green_Bullet
	Bullet* CurBullet;                                        // ��������� ��������� �������� ������
	CurBullet = Bullets[0];                                   // ��������� �������� ������ ��������� �� ����� Bullet


	// ������ ����
	Bomb** Bombs = new Bomb * [CountBombs];                   // �������� ������������� ������� ���������� �� ������� ������ Bomb � ��� �����������
	Bombs[0] = new Bomb(x0 + 200, y0 + 500);                  // ��������� �� ������ ������ Bomb
	Bombs[1] = new Red_Bomb(x0 + 200, y0 + 500);              // ��������� �� ������ ������ Red_Bomb
	Bombs[2] = new Purple_Bomb(x0 + 200, y0 + 500);           // ��������� �� ������ ������ Purple_Bomb
	Bombs[3] = new Green_Bomb(x0 + 200, y0 + 500);            // ��������� �� ������ ������ Green_Bomb
	Bomb* CurBomb;                                            // ��������� ��������� �������� ������
	CurBomb = Bombs[0];                                       // ��������� �������� ������ ��������� �� ����� Bomb


	// ��� ��������� ��������������� ����������. ��� � 4-�� �� 7-�� ������� �������
	for (i = RealMeteor; i < CountMeteor; i++)
	{
		CurAsteroid = Asteroids[i];                           // ��������������� ����������� ������ �������� ���������
		CurAsteroid->SetNumber(i);                            // ������������� ��������� ����� ������
	}// for i

	// ������� ��������� ����������
	int transition_matr[CountMeteor][CountBullets] ={ {4,0,0,0,0}    // ����� ������
													 ,{1,6,1,1,1}     // �������� ����� ������
													 ,{2,2,7,2,2}     // ������� ������
													 ,{3,3,3,8,3}     // ���������� ������
													 ,{4,4,5,4,4}     // ������� ������. ���������������
													 ,{5,0,5,5,5}     // �������� ����� ������. ���������������
													 ,{6,6,6,1,6}     // ���������� ������. ���������������
													 ,{7,7,7,2,7}     // ���������� ������. ���������������
													 ,{8,8,8,8,3} };  // ������� ������. ���������������

	// ������� ������� ��� ��������� ���������� �� ����� �����
	 // ������� ������� ��� ��������� ���������� �� ����� �����
	int dead_matr[CountMeteor][CountBullets] = { {DeadNumber,DeadNumber,DeadNumber,DeadNumber,DeadNumber}     // ����� ������
												,{DeadNumber,DeadNumber,DeadNumber,DeadNumber,DeadNumber}     // �������� ����� ������
												,{DeadNumber,DeadNumber,DeadNumber,DeadNumber,DeadNumber}     // ������� ������
												,{DeadNumber,DeadNumber,DeadNumber,DeadNumber,DeadNumber}     // ���������� ������
												,{DeadNumber,DeadNumber,DeadNumber,DeadNumber,DeadNumber}     // ������� ������. ���������������
												,{DeadNumber,0,DeadNumber,DeadNumber,DeadNumber}              // �������� ����� ������. ���������������
												,{DeadNumber,DeadNumber,DeadNumber,1,DeadNumber}              // ���������� ������. ���������������
												,{DeadNumber,DeadNumber,DeadNumber,2,DeadNumber}              // ���������� ������. ���������������
												,{DeadNumber,DeadNumber,DeadNumber,DeadNumber, 3} };          // ������ ������. ���������������

	// ������� ��������� ��������
	int ship_matr[CountShips][CountMeteor] = { {1,0,1,0,1,0,0,0,0}     // ������� �������
											  ,{1,2,1,2,1,1,2,2,1}     // �������� �������
											  ,{2,2,2,2,2,2,2,2,0} };  // ����������� �������

	// ������� ��������� �������� �������
	int transition_matr_Flying_Plate[CountFlyingPlates][CountBombs] = { {1,0,0,0}     // ������� �������� �������
	                                                                   ,{1,2,1,1}     // �������� �������� �������
	                                                                   ,{2,2,3,2}     // ���� �������� �������
	                                                                   ,{3,3,3,0} };  // ���������������� �������� �������

	//���� ���������� ���������� - ����� ��������
	if (hwnd != NULL)
	{
		// �������� �������� ���������� (device context) ��� ���������� ���� hwnd,
		// ������� ����� �������������� ��� ��������� ������� � ������ �������� ��� �����
		hdc = GetWindowDC(hwnd);
		if (hdc != nullptr)
		{
			// ������� �������� ������� �� �����
			CurShip->Show();
			// ����� ���������� �� �����. �� ������ ������ 4 ���������
			for (i = 0; i < RealMeteor; i++)
			{
				CurAsteroid = Asteroids[i];                         // ��������������� ����������� ������ �������� ���������
				CurAsteroid->Show();                                // ������� �� ����� ������ �� ����������
			}// for i
			// ������� ���� �� ����� ������, ������� ������ � ������
			cout << "\t\t\t\t\t\tScore:" << schet;

			while (1)
			{
				/***************************************�������� ������� ���������� �����*****************************************************/
				// ����� �������� ��� ��������� ��������
				Sleep(35);                                          // 35 ��
				CurShip->Show();
				// ����� ESC - ����� �� ���������
				if (KEY_DOWN(VK_ESCAPE))
				{
					// ������� ����� � ����������� ���������
					system("cls");
					// ������� ������� "�����"
					WriteEnd();
					HWND consoleWindow = GetConsoleWindow();
					// ��������� ���������� ����
					PostMessage(consoleWindow, WM_CLOSE, 0, 0);
					exit(0);
				}

/*********************************************�������� �������� �������***********************************************/

				// �������� ������ � �������� ������� ����� �� ������
				if (right  && CurPlate->IsVisible())
				{
					// �������� �������� ������� ������ �� ��� Step
					(*CurPlate).MoveTo((*CurPlate).GetX() + Step, (*CurPlate).GetY());

					// �������� �� ����������� �������� �������� ������� ������
					// �������� ������ ���� �� �������� ������ ������� �������
					if ((*CurPlate).GetX() <= Right_Border_Plate+3 && (*CurPlate).GetX() >= Right_Border_Plate - 3)
					{
						// ����������� ���� �������� ������
						right = false;
						// ��������������� ���� �������� �����
						left = true;
					}// if
				}// if

				// �������� ����� � �������� ������� ����� �� ������
				if (left && CurPlate->IsVisible())
				{
					// �������� �������� ������� ����� �� ��� Step
					(*CurPlate).MoveTo((*CurPlate).GetX() - Step, (*CurPlate).GetY());


					// �������� �� ����������� �������� �������� ������� �����
					// �������� ����� ���� �� �������� ����� ������� �������
					if ((*CurPlate).GetX() <= Left_Border_Plate + 3 && (*CurPlate).GetX() >= Left_Border_Plate - 3)
					{
						// ��������������� ���� �������� ������
						right = true;
						// ����������� ���� �������� �����
						left = false;
					}// if
				}// if

/*********************************************� ��������� �������� ������� ������������***********************************************/

				// ����� ���� � �����.
				// 0 - ����� ����
				// 1 - ����� ����
				// 2 - ������� ����
				// 4 - ������ ����
				// 5 - ����� ����
				// ��� �������:
				// 1 - ����� �����
				// 2 - ������� �����
				// 3 - ���������� �����
				// 4 - ������ �����

				// SPACE - ��������

/*******************************���������� ���� ��� �����, ������� ����� �������� � ��������***********************************/

				// ������� ����� ��������� ������ ���� ���� ��� ����� �������� SPACE, ����� ��������� ��� �� ������
				// ���� ������ 1 � ���� �� ������ ���
				// ���������, ��� ���� ��� �� ������ � ����� ��� �� ������
				if (CurBullet->IsVisible() == false && CurBomb->IsVisible() == false)
				{
					// ����
					// ������ 1
					if (KEY_DOWN(49))
					{
						key = true;                  // ���� ����
						CurBullet = Bullets[0];      // ��������� �������� ������ ��������� �� ������� ����� Bullet
					}

					// ������ 2
					else if (KEY_DOWN(50))
					{
						key = true;                  // ���� ����
						CurBullet = Bullets[1];      // ��������� �������� ������ ��������� �� ����������� ����� Yellow_Bullet
					}

					// ������ 3
					else if (KEY_DOWN(51))
					{
						key = true;                  // ���� ����
						CurBullet = Bullets[2];      // ��������� �������� ������ ��������� �� ����������� ����� Red_Bullet      
					}

					// ������ 4
					else if (KEY_DOWN(52))
					{
						key = true;                  // ���� ����
						CurBullet = Bullets[3];      // ��������� �������� ������ ��������� �� ����������� ����� Green_Bullet
					}

					// ������ 5
					else if (KEY_DOWN(53))
					{
						key = true;                  // ���� ����
						CurBullet = Bullets[4];      // ��������� �������� ������ ��������� �� ����������� ����� Blue_Bullet
					}

					// �����
					// ������ 1 �� �������
					if (GetAsyncKeyState(VK_NUMPAD1))
					{
						key = false;                 // ���� �����
						CurBomb = Bombs[0];          // ��������� �������� ������ ��������� �� ����������� ����� Bomb
					}

					// ������ 2 �� �������
					else if (GetAsyncKeyState(VK_NUMPAD2))
					{
						key = false;                 // ���� �����
						CurBomb = Bombs[1];          // ��������� �������� ������ ��������� �� ����������� ����� Red_Bomb
					}

					// ������ 3 �� �������
					else if (GetAsyncKeyState(VK_NUMPAD3))
					{
						key = false;                 // ���� �����
						CurBomb = Bombs[2];          // ��������� �������� ������ ��������� �� ����������� ����� Purple_Bomb
					}

					// ������ 4 �� �������
					else if (GetAsyncKeyState(VK_NUMPAD4))
					{
						key = false;                 // ���� �����
						CurBomb = Bombs[3];          // ��������� �������� ������ ��������� �� ����������� ����� Green_Bomb
					}

					// ���� ����� ������
					if (KEY_DOWN(VK_SPACE))
					{
						// ��� ���� �� ����� ����/ �����
						if (key)
						{
							// ���������� ���������� ���� ��� ��������� � ���� �������
							CurBullet->SetX(CurShip->GetX() - 0 * CurShip->GetScale());
							CurBullet->SetY(CurShip->GetY() - 40 * CurShip->GetScale() - CurBullet->GetCaliber());
							// �������� ���� �� ���� �����������
							CurBullet->Show();
						}
						// ��� ����
						else
						{
							// ���������� ���������� ����� ��� ��������� � ���� �������
							CurBomb->SetX(CurShip->GetX() + 1.5 * CurShip->GetScale());
							CurBomb->SetY(CurShip->GetY() - 37 * CurShip->GetScale() + 3 * CurBomb->GetRadius());
							// �������� ����� �� ���� �����������
							CurBomb->Show();
						}// if
					}// if
				}// if

/****************************************************���� ��� ����� �������****************************************************/

/*********************************************************�������� ����********************************************************/

				// �������� ���� �� ��������� � �������� ������� � ��������
				if (CurBullet->IsVisible())
				{
					// ���� ����, ��� ���� ��� �� ���������
					move = true;
					// ���������� ��� �������� ������� �� ������� ��� ������ �������� ���� �����
					for (i = 0; i < CountFlyingPlates; i++)
					{
						// ��������� ������� ������������ ���� � �������� �������
						if (Hit_FlyingPlate_Bullets(CurBullet, Plates[i]))
						{
							// ������ ����
							CurBullet->Hide();
							// ������� ���� �������� ����
							move = false;
						}

						// �����, ���� �� ������ �� � ���� �� �������
						else if (move)
						{
							// �������� ����
							CurBullet->MoveTo(CurBullet->GetX(), CurBullet->GetY() - CurBullet->GetCaliber());
							// ���� ��� �������� � �������� ���� ������ � false
							move = false;

						}// if
					}// for i

					// �������� ���� �� ��������� ������ � ������, ���� ���� �����-�� ���� ���� �� ������
					if (CurBullet->IsVisible())
					{
						// ���� ������ � ��������.��������� ������������ � ������ �� ���������� �������, ����� ������, � ����� ������ �������� ������ ����
						if (HitBullet(CurBullet, &CurAsteroid, Asteroids))
						{
							// ����������� ������� ������ ����������, ���� ����� ���������, � ������� ������ ������������� ������� �� �������, �� ��������� � ������� �������� ���������, �.�. ��������� ����� ���������
							if ((transition_matr[(CurAsteroid)->GetNumber()][CurBullet->GetScale()] != (CurAsteroid)->GetNumber()))
							{
								schet = schet + 1;
							}
							// ������ �������� �������� ������� ���������, ��������, ��� ����� ������� �������� ����������� �� ������ �����, �������� ���������� �� ����� ����� �������� dead_matr
							changeAsteroid(&CurAsteroid, CurBullet, Asteroids, transition_matr, dead_matr);
							Count(schet);
						}

						// �����, ���� �� ������ �� � ���� �� ���������� �� ������ ����, �� �������� ����
						else
						{
							CurBullet->MoveTo(CurBullet->GetX(), CurBullet->GetY() - CurBullet->GetCaliber() - 8);
						}// if(HitBullet(CurBullet, &CurAsteroid, Asteroids))
					}// if (CurBullet->IsVisible())
				}// if

/*******************************************************�������� ���� ��������**************************************************/

/**********************************************************�������� �����*******************************************************/

				// �������� ����� �� ��������� � �������� ������� � ��������
				if (CurBomb->IsVisible())
				{
					// ���� ����, ��� ����� ��� �� ���������
					move = true;
					// ���������� ��� �������� ������� �� ������� ��� ������ �������� ����� �����
					for (i = 0; i < CountFlyingPlates; i++)
					{
						// ��������� ������� ������������ ����� � �������� �������
						if (Hit_FlyingPlate_Bombs(CurBomb, Plates[i]))
						{
							// ������ �������� ������� �������� ������� ���������
							changeFlyingPlate(&CurPlate, Plates, CurBomb, transition_matr_Flying_Plate, schet);
							// ������� ���� ��������
							move = false;
						}

						// �����, ���� �� ������ �� � ���� �� �������
						else if (move)
						{
							// �������� �����
							CurBomb->MoveTo(CurBomb->GetX(), CurBomb->GetY() - CurBomb->GetRadius() - CurBomb->GetExtra_speed());
							// ���� ��� �������� � �������� ���� ������ � false
							move = false;
						}// if
					}// for i

					// ���������� ��� ��������� �� ������� ��� ������ �������� ����� �����
					for (i = 0; i < CountMeteor; i++)
					{
						// ������������� i-�� �������� ��� ��������������
						CurAsteroid = Asteroids[i];
						// ��������� ������� ������������ ����� � ���������
						if (Hit_Asteroids_Bombs(CurBomb, CurAsteroid))
						{
							// �������� �� ������������ ������
							// ������ �����
							CurBomb->Hide();
							// ����� ������ �� ������ ���������
							move = false;
						}

						// ���� ����� �� ������ �� � ���� �� ����������, �� �������� � ���� ��� �� ������� ���������� while
						else if (move)
						{
							// �������� �����
							CurBomb->MoveTo(CurBomb->GetX(), CurBomb->GetY() - CurBomb->GetRadius() - CurBomb->GetExtra_speed());
							// ���� ��� �������� � �������� ���� ������ � false
							move = false;
						}// if
					}// for i
				}// if

/****************************************************�������� ����� ��������****************************************************/

/****************************************************�������� ���������� �����**************************************************/

				// �������� �����
			    // ���� �� ����� �� ����� ������� �������
				if (CurShip->GetX() - step >= ShipXMin)
				{
					// � ������ 37 <- - ������� ����� �� ����������
					if (KEY_DOWN(VK_LEFT))
					{
						CurShip->MoveTo(CurShip->GetX() - step, CurShip->GetY());  // ������� ����� �� step 
					}// // if (KEY_DOWN(VK_LEFT))
				}// if (CurShip->GetX() - step >= ShipXMin)

				// �������� ������
				// ���� �� ����� �� ������ ������� �������
				if (CurShip->GetX() + step <= ShipXMax)
				{
					// � ������ 39 -> - ������� ������ �� ����������
					if (KEY_DOWN(VK_RIGHT))
					{
						CurShip->MoveTo(CurShip->GetX() + step, CurShip->GetY());   // ������� ������ �� step 
					}// if (KEY_DOWN(VK_RIGHT))
				}// if (CurShip->Right_Border() + step <= ShipXMax)

				// �������� ����
				// ���� �� ����� �� ������ ������� �������
				if (CurShip->GetY() + step <= ShipYMax)
				{
					// � ������ 40 -> ������� ���� �� ����������
					if (KEY_DOWN(VK_DOWN))
					{
						CurShip->MoveTo(CurShip->GetX(), CurShip->GetY() + step);    // ������� ���� �� step 
					}// if (KEY_DOWN(VK_DOWN))
				}// if (CurShip->High_Border() + step <= ShipYMax)

				// �������� �����
				// ���� �� ����� �� ������� ������� ������� 
				if (ShipYMin <= CurShip->GetY() - step)
				{
					// � ������ 38 -> - ������� ����� �� ����������
					if (KEY_DOWN(VK_UP))
					{
						CurShip->MoveTo(CurShip->GetX(), CurShip->GetY() - step);    // ������� ����� �� step 
					}// if (KEY_DOWN(VK_UP))
				}// if (CurShip->Low_Border() >= ShipYMin)

/*************************************************�������� ���������� ����� ��������********************************************/

/**************************************************����� ���������� ����� ��� �����*********************************************/
				
                // ��������� ������������ ������� � ������ �� �������� �������
			    // ���� ������ ������� ��������� ��������� ����� ����� � ������ �������� �������
				// � ������ ������� ������� ��������� ���� ������ ������� ��������� � �������� �� �����

				// ��� ����� ������� ��������� ������ ������ ������� ������� � ������ ������� ������� ������ ������ ������� ���������
				// � ������� ������� ������� ��������� ���� ������� ������ ��������� � ������ ������� ������� ��������� ���� ������ ������� ���������

				if (HitShip(CurShip, &CurAsteroid, Asteroids))
				{
					// ����������� ������� �� 1
					schet = schet + 1;
					// ������� ��������� ������� �� �����
					Count(schet);
					// ������ ������� ����� ����� �������� ������� ���������
					changeShip(&CurShip, CurAsteroid, Ships, ship_matr);
				}//if (HitShip(CurShip, &CurAsteroid, Asteroids))


				// ������������ ������� � �������� ��������
				// ��������� ������������ ������� � ������ �� �������
				for (int i = 0; i < CountFlyingPlates; i++)
				{
					if (HitShip_Plate(CurShip, Plates[i], schet))
					{
					    // �������� ������� �������
						CurShip->Hide();
						// �������� ������� �������� �������
						CurPlate->Hide();

						// ������� ��������
						// ������� ����� � ����������� ���������
						system("cls");
						// ������� ������� "�����"
						WriteEnd();
						HWND consoleWindow = GetConsoleWindow();
						// ��������� ���������� ����
						PostMessage(consoleWindow, WM_CLOSE, 0, 0);
						return -1;
					}// if (HitShip(CurShip, CurAsteroid))
				}// for i

/******************************************************��������� ����� �������**************************************************/

/***************************************�������� ��������� � �������� ������ �� ������� �������*********************************/

				// �������� ���������� �� ����� �� ������� �������
				for (i = 0; i < CountMeteor; i++)
				{
					// ��������������� ����������� ������ �������� ���������
					CurAsteroid = Asteroids[i];
					// �������� ����� - �� �������
					if (CurAsteroid->IsVisible())
					{
						// ���� ������ ������� ��������� ����� �� ������� ������� �������
						if (CurAsteroid->High_Border() >= YMaxAster)
						{
							// �������� ���������� �� ����� �����
							RespavnAsteroid(CurAsteroid);
						}

						else
						{
							// ����� - �� �����. �������� �� ���������
							CurAsteroid->MoveTo(CurAsteroid->GetX(), CurAsteroid->GetY() + stepAsteroid);
						}// if (CurAsteroid->High_Border() >= YMaxAster)

					}// if (CurAsteroid->IsVisible())

				}// for i
/********************************************************�������� �������*******************************************************/

			}// while 1

		}// end if

	}// end if

	// ������������� ��������������� ������
	if (mciSendString(TEXT("stop music"), NULL, 0, NULL) != 0) {
		return 3;
	}

	// ��������� ����
	if (mciSendString(TEXT("close music"), NULL, 0, NULL) != 0) {
		return 4;
	}

	return 0;
}//end main()


HWND GetConcolWindow()
{
	char str[128];
	LPWSTR title = (LPWSTR)"xxxxxxxxxxxxxxxxxx";
	GetConsoleTitle((LPWSTR)str, sizeof((LPWSTR)str));    // �������� ��������� ����
	SetConsoleTitle(title);
	Sleep(100);                                           // ���� ����� ��������� ���� (100 ��);
	HWND hwnd = FindWindow(nullptr, (LPWSTR)title);       // ���������� ���������� ����
	SetConsoleTitle((LPWSTR)str);
	return hwnd;                                          //������� ���������� ����
}//end GetConcolWindow()