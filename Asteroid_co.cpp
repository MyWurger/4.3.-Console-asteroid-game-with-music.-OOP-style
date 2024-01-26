/***************************************************************************
 *      � � � � � � � � � � � �   � � � � � �   � 2   � �   � � � �        *
 *-------------------------------------------------------------------------*
 *                                                                         *
 * Project Name  : Fly_Plate                                               *
 * Project Type  : Win64 Console application                               *
 * File Name     : Asteroid_co.cpp                                         *
 * Language      : VS2022                         C++                      *
 * Programmers   : ������� �. �.                                           *
 * Modified By   :                                                         *
 * Created       : 01 / 11 / 2023                                          *
 * Last Revision : 16 / 11 / 2023                                          *
 * Comment(s)    : ������� �������������� ����� ����� ������������         *
 *                 �����������. ������������ ������� ���������.            *
 *                 ����������� ������. ����������.                         *
 **************************************************************************/

#include "Asteroid_co.h"	// ���������� ���� � ����������� �������
HDC hdc;                    // �������  �������� ����������

/*----------------------------------------------------------------*/
/*             � � � � � � � � � �    � � � � � � �               */
/*----------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*                 Location               */
/*----------------------------------------*/

// ������� ����� ��������������
// �����������
Location::Location(double InitX, double InitY)
{
	m_X = InitX;           // ����������� ����� ��������
	m_Y = InitY;
}

// ����������
Location:: ~Location()
{
	//������ ����
}

// ����������� ������ ��� ��������� X
double Location::GetX() const
{
	return (m_X);          // ������� �������� ���� x
}

// ����������� ������ ��� ��������� Y
double Location::GetY() const
{
	return (m_Y);          // ������� �������� ���� y
}

// ������ ��� ��������� X
void Location::SetX(double NewX)
{
	m_X = NewX;            // ���������� ���� x ������������ ��������
}

// ������ ��� ��������� Y
void Location::SetY(double NewY)
{
	m_Y = NewY;            // ���������� ���� y ������������ ��������
}


/*------------------------------------------------------------------------*/
/*                Point                   */
/*----------------------------------------*/

// ����������� ����� ����� �� Location
// �����������
Point::Point(double InitX, double InitY) : Location(InitX, InitY) // ��� ������������� ������ ����� ���������� ����������� ������
{
	m_Visible = false;      // ����������� ����� ����� ��������
}

// ����������
Point:: ~Point()
{
	// ������ ����
}

// ������ ��� ���������� �����
bool Point::IsVisible() const
{
	return (m_Visible);     // ������� �������� ���������� �����
}

// ������������� ���������� ���������� �����
void Point::SetVisible(bool NewVisible)
{
	m_Visible = NewVisible; // ���������� ���� ���������� ��������
}

// ����������� ������ �� ����� �����������. ����������� �����
void Point::MoveTo(double NewX, double NewY)
{
	Hide();                 // ������ ������ �� ������ �����������
	m_X = NewX;             // ������������� ����� �������� ���������� �
	m_Y = NewY;             // ������������� ����� �������� ���������� Y
	Show();                 // ���������� ������ �� ����� �����������
}

// �������� ����� �� ������
void Point::Show()
{
	m_Visible = true;                                 // ����� �����
	SetPixel(hdc, m_X, m_Y, RGB(178, 87, 84));        // ������ ������� �� 4-� �������� ��������. ������������ ����� ����� ������
	SetPixel(hdc, m_X + 1, m_Y, RGB(178, 87, 84));
	SetPixel(hdc, m_X, m_Y + 1, RGB(178, 87, 84));
	SetPixel(hdc, m_X + 1, m_Y + 1, RGB(178, 87, 84));
}

// ������ ����� � ������. ����������� �����
void Point::Hide()
{
	m_Visible = false;                                // ����� �� �����
	SetPixel(hdc, m_X, m_Y, RGB(12, 12, 12));         // ������ ������� �� 4-� �������� �������� ������ �������
	SetPixel(hdc, m_X + 1, m_Y, RGB(12, 12, 12));
	SetPixel(hdc, m_X, m_Y + 1, RGB(12, 12, 12));
	SetPixel(hdc, m_X + 1, m_Y + 1, RGB(12, 12, 12));
}




/*---------------------------------------------------------------------------------------------------------------------*/
/*            ���������           */
/*--------------------------------*/

/*------------------------------------------------------------------------*/
/*                Asteroid                */
/*----------------------------------------*/

// ����������� ����� �������� �� ���������� IAsteroid, �� Point � �� ����������� �� Location
// ������ ���������� ������ ���� ������������� �����������
// ����� ���������������� ������� � ���� ������ ����� ����� ������ ����
Asteroid::Asteroid(double InitX, double InitY) : Point(InitX, InitY)   // ��� ������������� ������ ����� ���������� ����������� ������
{
	m_size = 15;             // �������� ��� ��������� � ����������� �������
	m_number = -1;           // ����� ���������
}

// ����������
Asteroid:: ~Asteroid()
{
	// ������ ����
}

// ������ ��� ��������� �������� �������
double Asteroid::GetSize() const
{
	return (m_size);         // ������� �������� ������� ���������
}

// ������ ��� �������������� ��������� �������� �������
void Asteroid::SetSize(double NewSize)
{
	m_size = NewSize;        // ���������� ���� ����� ���������� ��������
}

// ������ ��� ��������� �������� ������
int Asteroid::GetNumber() const
{
	return (m_number);       // ������� �������� ������ ���������
}

// ������ ��� �������������� ��������� �������� ������
void Asteroid::SetNumber(int NewNumber)
{
	m_number = NewNumber;    // ���������� ���� ����� ���������� ��������
}

// ��������� �������� ��������� ���������� �����
void Asteroid::Body(HPEN Pen)
{
	MoveToEx(hdc, m_X, m_Y, nullptr);                        // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 2.5 * m_size, m_Y + 0.5 * m_size);     // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 2.5 * m_size, m_Y + 0.5 * m_size, nullptr);
	LineTo(hdc, m_X - 2.8 * m_size, m_Y + 0.4 * m_size);

	MoveToEx(hdc, m_X - 2.5 * m_size, m_Y + 0.5 * m_size, nullptr);
	LineTo(hdc, m_X - 2.8 * m_size, m_Y + 0.4 * m_size);

	MoveToEx(hdc, m_X - 2.8 * m_size, m_Y + 0.4 * m_size, nullptr);
	LineTo(hdc, m_X - 3.1 * m_size, m_Y + 0.45 * m_size);

	MoveToEx(hdc, m_X - 3.1 * m_size, m_Y + 0.45 * m_size, nullptr);
	LineTo(hdc, m_X - 3.9 * m_size, m_Y + 0 * m_size);

	MoveToEx(hdc, m_X - 3.9 * m_size, m_Y + 0 * m_size, nullptr);
	LineTo(hdc, m_X - 4.5 * m_size, m_Y - 0.1 * m_size);

	MoveToEx(hdc, m_X - 4.5 * m_size, m_Y - 0.1 * m_size, nullptr);
	LineTo(hdc, m_X - 5 * m_size, m_Y - 0.7 * m_size);

	MoveToEx(hdc, m_X - 5 * m_size, m_Y - 0.7 * m_size, nullptr);
	LineTo(hdc, m_X - 5.7 * m_size, m_Y - 1.3 * m_size);

	MoveToEx(hdc, m_X - 5.7 * m_size, m_Y - 1.3 * m_size, nullptr);
	LineTo(hdc, m_X - 6.1 * m_size, m_Y - 1.5 * m_size);

	MoveToEx(hdc, m_X - 6.1 * m_size, m_Y - 1.5 * m_size, nullptr);
	LineTo(hdc, m_X - 6.3 * m_size, m_Y - 2 * m_size);

	MoveToEx(hdc, m_X - 6.3 * m_size, m_Y - 2 * m_size, nullptr);
	LineTo(hdc, m_X - 6.25 * m_size, m_Y - 2.7 * m_size);

	MoveToEx(hdc, m_X - 6.25 * m_size, m_Y - 2.7 * m_size, nullptr);
	LineTo(hdc, m_X - 6.5 * m_size, m_Y - 3.5 * m_size);

	MoveToEx(hdc, m_X - 6.5 * m_size, m_Y - 3.5 * m_size, nullptr);
	LineTo(hdc, m_X - 6.2 * m_size, m_Y - 4.5 * m_size);

	MoveToEx(hdc, m_X - 6.2 * m_size, m_Y - 4.5 * m_size, nullptr);
	LineTo(hdc, m_X - 6.4 * m_size, m_Y - 5.5 * m_size);

	MoveToEx(hdc, m_X - 6.4 * m_size, m_Y - 5.5 * m_size, nullptr);
	LineTo(hdc, m_X - 6 * m_size, m_Y - 6.7 * m_size);

	MoveToEx(hdc, m_X - 6 * m_size, m_Y - 6.7 * m_size, nullptr);
	LineTo(hdc, m_X - 4.8 * m_size, m_Y - 7.5 * m_size);

	MoveToEx(hdc, m_X - 4.8 * m_size, m_Y - 7.5 * m_size, nullptr);
	LineTo(hdc, m_X - 4 * m_size, m_Y - 8.5 * m_size);

	MoveToEx(hdc, m_X - 4 * m_size, m_Y - 8.5 * m_size, nullptr);
	LineTo(hdc, m_X - 3.5 * m_size, m_Y - 8.9 * m_size);

	MoveToEx(hdc, m_X - 3.5 * m_size, m_Y - 8.9 * m_size, nullptr);
	LineTo(hdc, m_X - 2.3 * m_size, m_Y - 9.2 * m_size);

	MoveToEx(hdc, m_X - 2.3 * m_size, m_Y - 9.2 * m_size, nullptr);
	LineTo(hdc, m_X - 2.2 * m_size, m_Y - 8.8 * m_size);

	MoveToEx(hdc, m_X - 2.2 * m_size, m_Y - 8.8 * m_size, nullptr);
	LineTo(hdc, m_X - 1.2 * m_size, m_Y - 8.9 * m_size);

	MoveToEx(hdc, m_X - 1.2 * m_size, m_Y - 8.9 * m_size, nullptr);
	LineTo(hdc, m_X - 0.9 * m_size, m_Y - 8.7 * m_size);

	MoveToEx(hdc, m_X - 0.9 * m_size, m_Y - 8.7 * m_size, nullptr);
	LineTo(hdc, m_X - 0.6 * m_size, m_Y - 8.8 * m_size);

	MoveToEx(hdc, m_X - 0.6 * m_size, m_Y - 8.8 * m_size, nullptr);
	LineTo(hdc, m_X - 0 * m_size, m_Y - 8.5 * m_size);

	MoveToEx(hdc, m_X - 0 * m_size, m_Y - 8.5 * m_size, nullptr);
	LineTo(hdc, m_X + 0.8 * m_size, m_Y - 8.7 * m_size);

	MoveToEx(hdc, m_X + 0.8 * m_size, m_Y - 8.7 * m_size, nullptr);
	LineTo(hdc, m_X + 0.9 * m_size, m_Y - 8.5 * m_size);

	MoveToEx(hdc, m_X + 0.9 * m_size, m_Y - 8.5 * m_size, nullptr);
	LineTo(hdc, m_X + 1.5 * m_size, m_Y - 7.9 * m_size);

	MoveToEx(hdc, m_X + 1.5 * m_size, m_Y - 7.9 * m_size, nullptr);
	LineTo(hdc, m_X + 2 * m_size, m_Y - 7.67 * m_size);

	MoveToEx(hdc, m_X + 2 * m_size, m_Y - 7.67 * m_size, nullptr);
	LineTo(hdc, m_X + 2.7 * m_size, m_Y - 6.8 * m_size);

	MoveToEx(hdc, m_X + 2.7 * m_size, m_Y - 6.8 * m_size, nullptr);
	LineTo(hdc, m_X + 2.8 * m_size, m_Y - 6.2 * m_size);

	MoveToEx(hdc, m_X + 2.8 * m_size, m_Y - 6.2 * m_size, nullptr);
	LineTo(hdc, m_X + 2.75 * m_size, m_Y - 5.7 * m_size);

	MoveToEx(hdc, m_X + 2.75 * m_size, m_Y - 5.7 * m_size, nullptr);
	LineTo(hdc, m_X + 2.95 * m_size, m_Y - 5 * m_size);

	MoveToEx(hdc, m_X + 2.95 * m_size, m_Y - 5 * m_size, nullptr);
	LineTo(hdc, m_X + 3 * m_size, m_Y - 4.6 * m_size);

	MoveToEx(hdc, m_X + 3 * m_size, m_Y - 4.6 * m_size, nullptr);
	LineTo(hdc, m_X + 3.2 * m_size, m_Y - 4.4 * m_size);

	MoveToEx(hdc, m_X + 3.2 * m_size, m_Y - 4.4 * m_size, nullptr);
	LineTo(hdc, m_X + 3 * m_size, m_Y - 4.1 * m_size);

	MoveToEx(hdc, m_X + 3 * m_size, m_Y - 4.1 * m_size, nullptr);
	LineTo(hdc, m_X + 2.8 * m_size, m_Y - 2.7 * m_size);

	MoveToEx(hdc, m_X + 2.8 * m_size, m_Y - 2.7 * m_size, nullptr);
	LineTo(hdc, m_X + 2.9 * m_size, m_Y - 1.8 * m_size);

	MoveToEx(hdc, m_X + 2.9 * m_size, m_Y - 1.8 * m_size, nullptr);
	LineTo(hdc, m_X + 2.4 * m_size, m_Y - 1.35 * m_size);

	MoveToEx(hdc, m_X + 2.4 * m_size, m_Y - 1.35 * m_size, nullptr);
	LineTo(hdc, m_X + 1.3 * m_size, m_Y - 0 * m_size);

	MoveToEx(hdc, m_X + 1.3 * m_size, m_Y - 0 * m_size, nullptr);
	LineTo(hdc, m_X, m_Y);                                         // ��������� � ��������� ����� ���������
}

// ��������� �������� ��������� ���������� ������
void Asteroid::Craters(HPEN Pen)
{
	// ������ ������� �� ������
	// ����� ������ ������
	{
		MoveToEx(hdc, m_X - 1 * m_size, m_Y - 0 * m_size, nullptr);  // ��������� ���������� �������� ������
		LineTo(hdc, m_X - 2.5 * m_size, m_Y - 0.1 * m_size);         // ��������� ��������� �������� ������

		MoveToEx(hdc, m_X - 2.5 * m_size, m_Y - 0.1 * m_size, nullptr);
		LineTo(hdc, m_X - 3.5 * m_size, m_Y - 0.7 * m_size);

		MoveToEx(hdc, m_X - 3.5 * m_size, m_Y - 0.7 * m_size, nullptr);
		LineTo(hdc, m_X - 2.7 * m_size, m_Y - 1 * m_size);

		MoveToEx(hdc, m_X - 2.7 * m_size, m_Y - 1 * m_size, nullptr);
		LineTo(hdc, m_X - 2.3 * m_size, m_Y - 1.1 * m_size);

		MoveToEx(hdc, m_X - 2.3 * m_size, m_Y - 1.1 * m_size, nullptr);
		LineTo(hdc, m_X - 1.8 * m_size, m_Y - 0.9 * m_size);

		MoveToEx(hdc, m_X - 1.8 * m_size, m_Y - 0.9 * m_size, nullptr);
		LineTo(hdc, m_X - 1.7 * m_size, m_Y - 1 * m_size);

		MoveToEx(hdc, m_X - 1.7 * m_size, m_Y - 1 * m_size, nullptr);
		LineTo(hdc, m_X - 1.6 * m_size, m_Y - 0.9 * m_size);

		MoveToEx(hdc, m_X - 1.6 * m_size, m_Y - 0.9 * m_size, nullptr);
		LineTo(hdc, m_X - 0.6 * m_size, m_Y - 0.6 * m_size);

		MoveToEx(hdc, m_X - 0.6 * m_size, m_Y - 0.6 * m_size, nullptr);
		LineTo(hdc, m_X - 1 * m_size, m_Y - 0 * m_size);
	}

	// �������� ������
	{
		MoveToEx(hdc, m_X - 5 * m_size, m_Y - 1 * m_size, nullptr);
		LineTo(hdc, m_X - 5.5 * m_size, m_Y - 1.9 * m_size);

		MoveToEx(hdc, m_X - 5.5 * m_size, m_Y - 1.9 * m_size, nullptr);
		LineTo(hdc, m_X - 6.2 * m_size, m_Y - 2.3 * m_size);

		MoveToEx(hdc, m_X - 6.2 * m_size, m_Y - 2.3 * m_size, nullptr);
		LineTo(hdc, m_X - 6 * m_size, m_Y - 3.5 * m_size);

		MoveToEx(hdc, m_X - 6 * m_size, m_Y - 3.5 * m_size, nullptr);
		LineTo(hdc, m_X - 5.5 * m_size, m_Y - 4 * m_size);

		MoveToEx(hdc, m_X - 5.5 * m_size, m_Y - 4 * m_size, nullptr);
		LineTo(hdc, m_X - 5 * m_size, m_Y - 3.7 * m_size);

		MoveToEx(hdc, m_X - 5 * m_size, m_Y - 3.7 * m_size, nullptr);
		LineTo(hdc, m_X - 4.5 * m_size, m_Y - 3.6 * m_size);

		MoveToEx(hdc, m_X - 4.5 * m_size, m_Y - 3.6 * m_size, nullptr);
		LineTo(hdc, m_X - 4 * m_size, m_Y - 2.7 * m_size);

		MoveToEx(hdc, m_X - 4 * m_size, m_Y - 2.7 * m_size, nullptr);
		LineTo(hdc, m_X - 3.8 * m_size, m_Y - 1.8 * m_size);

		MoveToEx(hdc, m_X - 3.8 * m_size, m_Y - 1.8 * m_size, nullptr);
		LineTo(hdc, m_X - 4 * m_size, m_Y - 1.3 * m_size);

		MoveToEx(hdc, m_X - 4 * m_size, m_Y - 1.3 * m_size, nullptr);
		LineTo(hdc, m_X - 4.5 * m_size, m_Y - 1 * m_size);

		MoveToEx(hdc, m_X - 4.5 * m_size, m_Y - 1 * m_size, nullptr);
		LineTo(hdc, m_X - 5 * m_size, m_Y - 1 * m_size);
	}

	// ������-�������� ������
	{
		MoveToEx(hdc, m_X - 5.5 * m_size, m_Y - 4.3 * m_size, nullptr);
		LineTo(hdc, m_X - 5.8 * m_size, m_Y - 6 * m_size);

		MoveToEx(hdc, m_X - 5.8 * m_size, m_Y - 6 * m_size, nullptr);
		LineTo(hdc, m_X - 5.6 * m_size, m_Y - 6.3 * m_size);

		MoveToEx(hdc, m_X - 5.6 * m_size, m_Y - 6.3 * m_size, nullptr);
		LineTo(hdc, m_X - 4 * m_size, m_Y - 7.5 * m_size);

		MoveToEx(hdc, m_X - 4 * m_size, m_Y - 7.5 * m_size, nullptr);
		LineTo(hdc, m_X - 3.6 * m_size, m_Y - 7.4 * m_size);

		MoveToEx(hdc, m_X - 3.6 * m_size, m_Y - 7.4 * m_size, nullptr);
		LineTo(hdc, m_X - 3 * m_size, m_Y - 7 * m_size);

		MoveToEx(hdc, m_X - 3 * m_size, m_Y - 7 * m_size, nullptr);
		LineTo(hdc, m_X - 2.9 * m_size, m_Y - 6.4 * m_size);

		MoveToEx(hdc, m_X - 2.9 * m_size, m_Y - 6.4 * m_size, nullptr);
		LineTo(hdc, m_X - 3.5 * m_size, m_Y - 4.5 * m_size);

		MoveToEx(hdc, m_X - 3.5 * m_size, m_Y - 4.5 * m_size, nullptr);
		LineTo(hdc, m_X - 5 * m_size, m_Y - 4 * m_size);

		MoveToEx(hdc, m_X - 5 * m_size, m_Y - 4 * m_size, nullptr);
		LineTo(hdc, m_X - 5.5 * m_size, m_Y - 4.3 * m_size);
	}

	//���-������
	{
		MoveToEx(hdc, m_X + 0 * m_size, m_Y - 0 * m_size, nullptr);
		LineTo(hdc, m_X + 0.4 * m_size, m_Y - 0.6 * m_size);

		MoveToEx(hdc, m_X + 0.4 * m_size, m_Y - 0.6 * m_size, nullptr);
		LineTo(hdc, m_X + 1 * m_size, m_Y - 1.2 * m_size);

		MoveToEx(hdc, m_X + 1 * m_size, m_Y - 1.2 * m_size, nullptr);
		LineTo(hdc, m_X + 1.3 * m_size, m_Y - 1.8 * m_size);

		MoveToEx(hdc, m_X + 1.3 * m_size, m_Y - 1.8 * m_size, nullptr);
		LineTo(hdc, m_X + 1.8 * m_size, m_Y - 2 * m_size);

		MoveToEx(hdc, m_X + 1.8 * m_size, m_Y - 2 * m_size, nullptr);
		LineTo(hdc, m_X + 1.8 * m_size, m_Y - 2 * m_size);

		MoveToEx(hdc, m_X + 1.8 * m_size, m_Y - 2 * m_size, nullptr);
		LineTo(hdc, m_X + 2.3 * m_size, m_Y - 2.2 * m_size);

		MoveToEx(hdc, m_X + 2.3 * m_size, m_Y - 2.2 * m_size, nullptr);
		LineTo(hdc, m_X + 2.8 * m_size, m_Y - 2.1 * m_size);
	}

	//���-������ ��������
	{
		MoveToEx(hdc, m_X + 0.4 * m_size, m_Y - 1.5 * m_size, nullptr);
		LineTo(hdc, m_X + 0.8 * m_size, m_Y - 2 * m_size);

		MoveToEx(hdc, m_X + 0.8 * m_size, m_Y - 2 * m_size, nullptr);
		LineTo(hdc, m_X + 1.3 * m_size, m_Y - 3.5 * m_size);

		MoveToEx(hdc, m_X + 1.3 * m_size, m_Y - 3.5 * m_size, nullptr);
		LineTo(hdc, m_X + 0.9 * m_size, m_Y - 3.9 * m_size);

		MoveToEx(hdc, m_X + 0.9 * m_size, m_Y - 3.9 * m_size, nullptr);
		LineTo(hdc, m_X + 0.5 * m_size, m_Y - 3.7 * m_size);

		MoveToEx(hdc, m_X + 0.5 * m_size, m_Y - 3.7 * m_size, nullptr);
		LineTo(hdc, m_X + 0.2 * m_size, m_Y - 3.4 * m_size);

		MoveToEx(hdc, m_X + 0.2 * m_size, m_Y - 3.4 * m_size, nullptr);
		LineTo(hdc, m_X - 0.3 * m_size, m_Y - 2.7 * m_size);

		MoveToEx(hdc, m_X - 0.3 * m_size, m_Y - 2.7 * m_size, nullptr);
		LineTo(hdc, m_X - 0 * m_size, m_Y - 1.6 * m_size);

		MoveToEx(hdc, m_X - 0 * m_size, m_Y - 1.6 * m_size, nullptr);
		LineTo(hdc, m_X + 0.4 * m_size, m_Y - 1.5 * m_size);
	}

	{
		MoveToEx(hdc, m_X - 4.5 * m_size, m_Y - 3.9 * m_size, nullptr);
		LineTo(hdc, m_X - 3.4 * m_size, m_Y - 4.3 * m_size);

		MoveToEx(hdc, m_X - 3.4 * m_size, m_Y - 4.3 * m_size, nullptr);
		LineTo(hdc, m_X - 3 * m_size, m_Y - 5 * m_size);

		MoveToEx(hdc, m_X - 3 * m_size, m_Y - 5 * m_size, nullptr);
		LineTo(hdc, m_X - 2.5 * m_size, m_Y - 5 * m_size);

		MoveToEx(hdc, m_X - 2.5 * m_size, m_Y - 5 * m_size, nullptr);
		LineTo(hdc, m_X - 1.5 * m_size, m_Y - 4 * m_size);

		MoveToEx(hdc, m_X - 1.5 * m_size, m_Y - 4 * m_size, nullptr);
		LineTo(hdc, m_X - 1.7 * m_size, m_Y - 3.5 * m_size);

		MoveToEx(hdc, m_X - 1.7 * m_size, m_Y - 3.5 * m_size, nullptr);
		LineTo(hdc, m_X - 2 * m_size, m_Y - 2 * m_size);

		MoveToEx(hdc, m_X - 2 * m_size, m_Y - 2 * m_size, nullptr);
		LineTo(hdc, m_X - 2.5 * m_size, m_Y - 1.5 * m_size);

		MoveToEx(hdc, m_X - 2.5 * m_size, m_Y - 1.5 * m_size, nullptr);
		LineTo(hdc, m_X - 3 * m_size, m_Y - 2 * m_size);

		MoveToEx(hdc, m_X - 3 * m_size, m_Y - 2 * m_size, nullptr);
		LineTo(hdc, m_X - 4 * m_size, m_Y - 3.5 * m_size);

		MoveToEx(hdc, m_X - 4 * m_size, m_Y - 3.5 * m_size, nullptr);
		LineTo(hdc, m_X - 4.5 * m_size, m_Y - 3.9 * m_size);
	}

	//������-������
	{
		MoveToEx(hdc, m_X + 1 * m_size, m_Y - 4.5 * m_size, nullptr);
		LineTo(hdc, m_X - 0.5 * m_size, m_Y - 5 * m_size);

		MoveToEx(hdc, m_X - 0.5 * m_size, m_Y - 5 * m_size, nullptr);
		LineTo(hdc, m_X - 1 * m_size, m_Y - 6 * m_size);

		MoveToEx(hdc, m_X - 1 * m_size, m_Y - 6 * m_size, nullptr);
		LineTo(hdc, m_X - 1.6 * m_size, m_Y - 6.5 * m_size);

		MoveToEx(hdc, m_X - 1.6 * m_size, m_Y - 6.5 * m_size, nullptr);
		LineTo(hdc, m_X - 1.4 * m_size, m_Y - 7.5 * m_size);

		MoveToEx(hdc, m_X - 1.4 * m_size, m_Y - 7.5 * m_size, nullptr);
		LineTo(hdc, m_X - 1.2 * m_size, m_Y - 8.2 * m_size);

		MoveToEx(hdc, m_X - 1.2 * m_size, m_Y - 8.2 * m_size, nullptr);
		LineTo(hdc, m_X - 0.5 * m_size, m_Y - 8.2 * m_size);

		MoveToEx(hdc, m_X - 0.5 * m_size, m_Y - 8.2 * m_size, nullptr);
		LineTo(hdc, m_X + 0.1 * m_size, m_Y - 7.5 * m_size);

		MoveToEx(hdc, m_X + 0.1 * m_size, m_Y - 7.5 * m_size, nullptr);
		LineTo(hdc, m_X + 0.6 * m_size, m_Y - 8 * m_size);

		MoveToEx(hdc, m_X + 0.6 * m_size, m_Y - 8 * m_size, nullptr);
		LineTo(hdc, m_X + 0.8 * m_size, m_Y - 7 * m_size);

		MoveToEx(hdc, m_X + 0.8 * m_size, m_Y - 7 * m_size, nullptr);
		LineTo(hdc, m_X + 1.5 * m_size, m_Y - 6 * m_size);

		MoveToEx(hdc, m_X + 1.5 * m_size, m_Y - 6 * m_size, nullptr);
		LineTo(hdc, m_X + 1.7 * m_size, m_Y - 5.2 * m_size);

		MoveToEx(hdc, m_X + 1.7 * m_size, m_Y - 5.2 * m_size, nullptr);
		LineTo(hdc, m_X + 1.5 * m_size, m_Y - 4.6 * m_size);

		MoveToEx(hdc, m_X + 1.5 * m_size, m_Y - 4.6 * m_size, nullptr);
		LineTo(hdc, m_X + 1 * m_size, m_Y - 4.5 * m_size);

	}
}

// �������� �������� �� ������. ����������� �����
void Asteroid::Show()
{
	m_Visible = true;                         // �������� �����
	// ������� ���, ������� � ���� ����
	HPEN PenGreyPurple = CreatePen(PS_SOLID, 2, RGB(136, 112, 107));
	// ������ ���� PenGreyPurple  ��������
	SelectObject(hdc, PenGreyPurple);
	HBRUSH Brush = CreateSolidBrush(RGB(240, 248, 255));
	// ������ ������ � ������� ��������� �������� ������
	Galo(PenGreyPurple, Brush);               // ��������� ������������ ����� ������ Body
	Bumps(PenGreyPurple);                     // ��������� �������
	Core(PenGreyPurple, Brush);               // ��������� ����
	Stripes(PenGreyPurple, Brush);            // ��������� �������
	Nimbus(PenGreyPurple, Brush);             // ��������� �����
	Rays(PenGreyPurple);                      // ��������� �����
	Body(PenGreyPurple);                      // ��������� ����
	Craters(PenGreyPurple);                   // ��������� ��������

	DeleteObject(PenGreyPurple);              // ��������� ��������� ���� ������� PenGreyPurple
	DeleteObject(Brush);                      // ��������� ����� Brush
}

// ������ �������� � ������. ����������� �����
void Asteroid::Hide()
{
	m_Visible = false;                        // �������� �������
	// ������� ���, ������� � ���� ����
	HPEN PenBlack = CreatePen(PS_SOLID, 2, RGB(12, 12, 12));
	// ������ ���� PenBlack  ��������
	SelectObject(hdc, PenBlack);
	// ������ ������ � ������� ��������� ������ ������
	Body(PenBlack);
	Craters(PenBlack);

	DeleteObject(PenBlack);                   // ��������� ��������� ���� ������� PenBlack
}

// ������� �������� ����� ����� ����� ���������/ ������ �������/ ������ ��������� �������/ ����������� �������
double Asteroid::Left_Border()
{
	return (GetX() - 6.5 * GetSize());
}

// ������� �������� ����� ������ ����� ���������/ ������ �������/ ������ ��������� �������/ ����������� �������
double Asteroid::Right_Border()
{
	return (GetX() + 3.1 * GetSize());
}

// ������� �������� ����� ������� ����� ���������/ ������ �������/ ������ ��������� �������/ ����������� �������
double Asteroid::High_Border()
{
	return (GetY() + 0.46 * GetSize());
}

// ������� �������� ����� ������ ����� ���������/ ������ �������/ ������ ��������� �������/ ����������� �������
double Asteroid::Low_Border()
{
	return (GetY() - 9.1 * GetSize());
}


// ��� ��������� ������ ���������� ������� �������� ����� ������ ���������
/*------------------------------------------------------------------------*/
/*               White_Warlic             */
/*----------------------------------------*/

// ����������� ����� ����� ������ �� Asteroid � �� ����������� �� Point � Location. � IAsteroid
White_Warlic::White_Warlic(double InitX, double InitY) : Asteroid(InitX, InitY) // ��� ������������� ������ ����� ���������� ����������� ������
{
	m_number = 0;                  // ����� ���������
	m_size = 16;                   // �������� ��� ���������
}

// ����������
White_Warlic:: ~White_Warlic()
{
	// ������ ����
}

// ��������� ������������ ����� ������ Body �������� ������
void White_Warlic::Galo(HPEN Pen, HBRUSH Brush)
{
	Ellipse(hdc, m_X - 6 * m_size, m_Y + 0 * m_size, m_X + 2.7 * m_size, m_Y - 8.5 * m_size);
}

// �������� ������ ������� �� ������. ����������� �����
void White_Warlic::Show()
{
	m_Visible = true;              // ����� ������ �����
	// ������� ���, ������� � ���� ����
	HPEN PenSlivki = CreatePen(PS_SOLID, 3, RGB(255, 248, 231));
	// ������� ���, ������� � ���� ����
	HPEN PenBlue = CreatePen(PS_SOLID, 2, RGB(21, 23, 25));
	// ������� ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(240, 248, 255));
	// ������ �����  Brush ��������
	SelectObject(hdc, Brush);
	// ������ ���� PenSlivki ��������
	SelectObject(hdc, PenSlivki);
	// ������ ���� � ���� �������� ������ � ������
	Body(PenSlivki);
	Galo(PenSlivki, Brush);
	// ������ ���� PenBlue ��������
	SelectObject(hdc, PenBlue);
	// ������ ������� �������� ������
	Craters(PenBlue);

	DeleteObject(PenSlivki);            // ���������� ��������� ���� ������ ���� PenSlivki
	DeleteObject(PenBlue);              // ���������� ��������� ���� ������ ���� PenBlue
	DeleteObject(Brush);                // ���������� ��������� ���� ������ ����� Brush
}

// ������ ������ ������� � ������. ����������� �����
void White_Warlic::Hide()
{
	m_Visible = false;                  // ����� ������ �������
	// ������� ���, ������� � ���� ����
	HPEN PenBlack = CreatePen(PS_SOLID, 3, RGB(12, 12, 12));
	// ������� ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ������ ���� PenBlack ��������
	SelectObject(hdc, PenBlack);
	// ������������ ����, ���� � ������� ������ ����� � ������
	Body(PenBlack);                     // ����� ������
	Galo(PenBlack, Brush);              // ����� ������
	Craters(PenBlack);                  // ����� ������

	DeleteObject(PenBlack);             // ���������� ��������� ���� ������ ���� PenBlack
	DeleteObject(Brush);                // ���������� ��������� ���� ������ ����� Brush
}


/*------------------------------------------------------------------------*/
/*            Cold_White_Warlic           */
/*----------------------------------------*/

// ����������� ����� �������� ����� ������ �� ������ ������� � �� ����������� �� Asteroid, Point � Location. � IAsteroid. ������������ ������������
// ��� ������������� ������ ����� ���������� ����������� ������
Cold_White_Warlic::Cold_White_Warlic(double InitX, double InitY) : White_Warlic(InitX, InitY)
{
	m_number = 1;		// ����� ���������
	m_size = 11;		// �������� ��� ���������
}

// ����������
Cold_White_Warlic:: ~Cold_White_Warlic()
{
	// ������ ����
};

// ��������� �����-������ ������ ���������� �����
void Cold_White_Warlic::Bumps(HPEN Pen)
{
	MoveToEx(hdc, m_X - 0.6 * m_size, m_Y - 4 * m_size, nullptr);         // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 1.3 * m_size, m_Y - 4.5 * m_size);               // ��������� ��������� �������� ������
	MoveToEx(hdc, m_X + 1.3 * m_size, m_Y - 4.5 * m_size, nullptr);
	LineTo(hdc, m_X + 1.3 * m_size, m_Y - 5 * m_size);
	MoveToEx(hdc, m_X + 1.3 * m_size, m_Y - 5 * m_size, nullptr);
	LineTo(hdc, m_X + 3 * m_size, m_Y - 4.5 * m_size);

	MoveToEx(hdc, m_X - 2.4 * m_size, m_Y - 3.7 * m_size, nullptr);
	LineTo(hdc, m_X - 4.3 * m_size, m_Y - 3.2 * m_size);
	MoveToEx(hdc, m_X - 4.3 * m_size, m_Y - 3.2 * m_size, nullptr);
	LineTo(hdc, m_X - 4.3 * m_size, m_Y - 2.7 * m_size);
	MoveToEx(hdc, m_X - 4.3 * m_size, m_Y - 2.7 * m_size, nullptr);
	LineTo(hdc, m_X - 6.2 * m_size, m_Y - 3.2 * m_size);

	MoveToEx(hdc, m_X - 1.5 * m_size, m_Y - 3.2 * m_size, nullptr);
	LineTo(hdc, m_X - 1.2 * m_size, m_Y - 1.7 * m_size);
	MoveToEx(hdc, m_X - 1.2 * m_size, m_Y - 1.7 * m_size, nullptr);
	LineTo(hdc, m_X - 1.6 * m_size, m_Y - 1.7 * m_size);
	MoveToEx(hdc, m_X - 1.6 * m_size, m_Y - 1.7 * m_size, nullptr);
	LineTo(hdc, m_X - 1.3 * m_size, m_Y + 0.2 * m_size);

	MoveToEx(hdc, m_X - 1.8 * m_size, m_Y - 4.8 * m_size, nullptr);
	LineTo(hdc, m_X - 2.3 * m_size, m_Y - 6.5 * m_size);
	MoveToEx(hdc, m_X - 2.3 * m_size, m_Y - 6.5 * m_size, nullptr);
	LineTo(hdc, m_X - 1.8 * m_size, m_Y - 6.5 * m_size);
	MoveToEx(hdc, m_X - 1.8 * m_size, m_Y - 6.5 * m_size, nullptr);
	LineTo(hdc, m_X - 2.2 * m_size, m_Y - 8.5 * m_size);
}

// ��������� ���� ����������� ����� � ������
void Cold_White_Warlic::Core(HPEN Pen, HBRUSH Brush)
{
	// ����
	Ellipse(hdc, m_X - 2.5 * m_size, m_Y - 3 * m_size, m_X - 0.5 * m_size, m_Y - 5 * m_size);
}

// �������� ��������� ������ ������� �� ������. ����������� �����
void Cold_White_Warlic::Show()
{
	m_Visible = true;                      // �������� ����� ������ �����
	// ������� ���, ������� � ���� ������
	HPEN PenGrey = CreatePen(PS_SOLID, 3, RGB(35, 26, 36));
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 250, 240));
	HPEN PenBlue = CreatePen(PS_SOLID, 3, RGB(0, 0, 128));
	HPEN PenBlack = CreatePen(PS_SOLID, 3, RGB(12, 12, 12));
	// ������� ���� ������
	HBRUSH Brush = CreateSolidBrush(RGB(35, 26, 36));
	HBRUSH BrushWhite = CreateSolidBrush(RGB(255, 250, 240));
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ������ ���� PenGrey ��������
	SelectObject(hdc, PenGrey);
	// ������������ ����������� ���� ������� �������� ���������� ������
	Galo(PenGrey, Brush);
	// ������ ����� BrushWhite ��������
	SelectObject(hdc, BrushWhite);
	// ������������ ���� ���������� ������
	Core(PenGrey, BrushWhite);
	// ������ ���� PenWhite ��������
	SelectObject(hdc, PenWhite);
	// ������������ ������ �������� ������
	Bumps(PenWhite);
	// ������ ���� PenBlue ��������
	SelectObject(hdc, PenBlue);
	// ������������ �������� ������� ����������� ���������� ������
	Body(PenBlue);
	// ������ ���� PenBlack ��������
	SelectObject(hdc, PenBlack);
	// ������������ ������� ������� ����������� ���������� ������
	Craters(PenBlack);

	DeleteObject(PenBlack);             // ���������� ��������� ���� ������ ���� PenBlack
	DeleteObject(PenWhite);             // ���������� ��������� ���� ������ ���� PenWhite
	DeleteObject(PenBlue);              // ���������� ��������� ���� ������ ���� PenBlue
	DeleteObject(PenGrey);              // ���������� ��������� ���� ������ ���� PenGrey
	DeleteObject(Brush);                // ���������� ��������� ���� ������ ����� Brush
	DeleteObject(BrushWhite);           // ���������� ��������� ���� ������ ����� BrushWhite
}

// ������ ��������� ������ ������� � ������. ����������� �����
void Cold_White_Warlic::Hide()
{
	m_Visible = false;                  // �������� ����� ������ �������
	// ������� ���, ������� � ���� ����
	HPEN PenBlack = CreatePen(PS_SOLID, 3, RGB(12, 12, 12));
	// ������� ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ������ ���� PenBlack ��������
	SelectObject(hdc, PenBlack);
	// ������������ ����������� ���� ������� �������� ���������� ������
	Galo(PenBlack, Brush);
	// ������������ ���� ���������� ������
	Core(PenBlack, Brush);
	// ������������ ������ ���������� ������
	Bumps(PenBlack);
	// ������������ �������� ������� ����������� ���������� ������
	Body(PenBlack);
	// ������������ ������� ������� ����������� ���������� ������
	Craters(PenBlack);

	DeleteObject(PenBlack);             // ���������� ��������� ���� ������ ���� PenBlack
	DeleteObject(Brush);                // ���������� ��������� ���� ������ ����� Brush
}


/*------------------------------------------------------------------------*/
/*            Brown_Warlic           */
/*-----------------------------------*/

// ����������� ����� ���������� ������ �� Asteroid � �� ������������ �� Point � Location
Brown_Warlic::Brown_Warlic(double InitX, double InitY) : Asteroid(InitX, InitY) // ��� ������������� ������ ����� ���������� ����������� ������
{
	m_number = 2;					  // ����� ���������
	m_size = 13;					  // �������� ��� ���������
}

// ����������
Brown_Warlic:: ~Brown_Warlic()
{
	// ������ ����
}

// ��������� ������� ���������� �����
void Brown_Warlic::Stripes(HPEN Pen, HBRUSH Brush)
{
	// ������ ������
	Ellipse(hdc, m_X - 5 * m_size, m_Y + 0.5 * m_size, m_X + 2 * m_size, m_Y - 2 * m_size);
	// ������� ������
	Ellipse(hdc, m_X - 4.5 * m_size, m_Y - 7 * m_size, m_X + 1.5 * m_size, m_Y - 9.1 * m_size);

	MoveToEx(hdc, m_X - 6.2 * m_size, m_Y - 2.5 * m_size, nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 4 * m_size, m_Y - 2.4 * m_size);                  // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 4 * m_size, m_Y - 2.4 * m_size, nullptr);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 2 * m_size, m_Y - 2.4 * m_size);                  // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 2 * m_size, m_Y - 2.4 * m_size, nullptr);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 0 * m_size, m_Y - 2.5 * m_size);                  // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 0 * m_size, m_Y - 2.5 * m_size, nullptr);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 2.8 * m_size, m_Y - 2.7 * m_size);                // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 6.2 * m_size, m_Y - 6 * m_size, nullptr);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 4 * m_size, m_Y - 5.9 * m_size);                  // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 4 * m_size, m_Y - 5.9 * m_size, nullptr);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 2 * m_size, m_Y - 5.9 * m_size);                  // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 2 * m_size, m_Y - 5.9 * m_size, nullptr);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 0 * m_size, m_Y - 6 * m_size);                    // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 0 * m_size, m_Y - 6 * m_size, nullptr);         // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 2.8 * m_size, m_Y - 6.2 * m_size);                // ��������� ��������� �������� ������
}

// �������� ����������� ������� �� ������. ����������� �����
void Brown_Warlic::Show()
{
	m_Visible = true;                    // ���������� ������ �����
	// ������� ���, ������� � ���� ����
	HPEN PenRedOrange = CreatePen(PS_SOLID, 3, RGB(169, 29, 17));
	// ������� ���, ������� � ���� ����
	HPEN PenDeepRed = CreatePen(PS_SOLID, 2, RGB(123, 0, 28));
	// ������� ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(243, 71, 35));
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ������ ���� PenRedOrange ��������
	SelectObject(hdc, PenRedOrange);
	// ������ ������ ����������� ������� ������� �������� �������� ������
	Body(PenRedOrange);
	// ������ ������� ����������� ������� �������� ������
	Stripes(PenRedOrange, Brush);
	// ������ ���� PenDeepRed ��������
	SelectObject(hdc, PenDeepRed);
	// ������ ������� ����������� ������� ������� �������� �������� ������
	Craters(PenDeepRed);

	DeleteObject(PenDeepRed);            // ���������� ��������� ���� ������ ���� PenDeepRed
	DeleteObject(PenRedOrange);          // ���������� ��������� ���� ������ ���� PenRedOrange
	DeleteObject(Brush);                 // ���������� ��������� ���� ������ ����� Brush
}

// ������ ����������� ������� � ������. ����������� �����
void Brown_Warlic::Hide()
{
	m_Visible = false;                   // ���������� ������ �������
	// ������� ���, ������� � ���� ����
	HPEN PenBlack = CreatePen(PS_SOLID, 3, RGB(12, 12, 12));
	// ������� ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ������ ���� PenGrey ��������
	SelectObject(hdc, PenBlack);
	// ������ ������ ����������� ������� ������� �������� �������� ������
	Body(PenBlack);
	// ������ ������� ����������� ������� �������� ������
	Stripes(PenBlack, Brush);
	// ������ ������� ����������� ������� ������� �������� �������� ������
	Craters(PenBlack);
	DeleteObject(PenBlack);             // ���������� ��������� ���� ������ ���� PenBlack
	DeleteObject(Brush);                // ���������� ��������� ���� ������ ����� Brush
}


// ��� ���� ������ ���������� ������� ��� ����� �������
/*------------------------------------------------------------------------*/
/*            Neutron_Star           */
/*-----------------------------------*/

// ����������� ����� ���������� ������ �� Asteroid � �� ������������ �� Point � Location. � IAsteroid.
// �����������
Neutron_Star::Neutron_Star(double InitX, double InitY) : Asteroid(InitX, InitY) // ��� ������������� ������ ����� ���������� ����������� ������
{
	m_number = 3;                       // ����� ���������
	m_size = 13;				        // �������� ��� ���������
}

// ����������
Neutron_Star:: ~Neutron_Star()
{
	// ������ ����
}

// ��������� ����� ���������� ����� � ������
void Neutron_Star::Nimbus(HPEN Pen, HBRUSH Brush)
{
	// ����-���� ������ Body
	Ellipse(hdc, m_X - 8 * m_size, m_Y + 2 * m_size, m_X + 5 * m_size, m_Y - 11 * m_size);
}

// ��������� ����� ���������� �����
void Neutron_Star::Rays(HPEN Pen)
{
	MoveToEx(hdc, m_X - 1.8 * m_size, m_Y - 9 * m_size, nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 1.3 * m_size, m_Y - 11 * m_size);               // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 1.3 * m_size, m_Y - 11 * m_size, nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 0.7 * m_size, m_Y - 8.9 * m_size);              // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 1.8 * m_size, m_Y + 0.5 * m_size, nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 1.3 * m_size, m_Y + 2 * m_size);                // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 1.3 * m_size, m_Y + 2 * m_size, nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 0.7 * m_size, m_Y + 0.2 * m_size);              // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 3 * m_size, m_Y - 4.8 * m_size, nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 4.8 * m_size, m_Y - 4.2 * m_size);              // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 4.8 * m_size, m_Y - 4.2 * m_size, nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 3 * m_size, m_Y - 3.6 * m_size);                // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 6.2 * m_size, m_Y - 4.5 * m_size, nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 8 * m_size, m_Y - 4 * m_size);                  // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 8 * m_size, m_Y - 4 * m_size, nullptr);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 6.5 * m_size, m_Y - 3.2 * m_size);              // ��������� ��������� �������� ������
}

// �������� ���������� ������ �� ������. ����������� �����
void Neutron_Star::Show()
{
	m_Visible = true;                   // ���������� ������ �����
	// ������� ���, ������� � ���� ����
	HPEN PenBlue = CreatePen(PS_SOLID, 3, RGB(65, 105, 225));
	// ������� ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// ������� ���, ������� � ���� ����
	HPEN PenViolet = CreatePen(PS_SOLID, 2, RGB(153, 50, 204));
	// ������� ���, ������� � ���� ����
	HPEN PenWhite = CreatePen(PS_SOLID, 2, RGB(253, 245, 230));
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ������ ���� PenBlue ��������
	SelectObject(hdc, PenBlue);
	// ������ ���� ���������� ����� � ������
	Nimbus(PenBlue, Brush);
	// ������ ������ ���������� ������ ������� �������� �������� ������
	Body(PenBlue);
	// ������ ���� PenWhite ��������
	SelectObject(hdc, PenWhite);
	// ������ ���� ���������� ������ �������� ������
	Rays(PenBlue);
	// ������ ���� PenViolet ��������
	SelectObject(hdc, PenViolet);
	// ������ ������� ���������� ������ ������� �������� �������� ������
	Craters(PenViolet);

	DeleteObject(PenWhite);             // ���������� ��������� ���� ������ ���� PenWhite
	DeleteObject(PenViolet);            // ���������� ��������� ���� ������ ���� PenViolet
	DeleteObject(PenBlue);              // ���������� ��������� ���� ������ ���� PenBlue
	DeleteObject(Brush);                // ���������� ��������� ���� ������ ����� Brush
}

// ������ ���������� ������ � ������. ����������� �����
void Neutron_Star::Hide()
{
	m_Visible = false;                  // ���������� ������ �����
	// ������� ���, ������� � ���� ����
	HPEN PenBlack = CreatePen(PS_SOLID, 3, RGB(12, 12, 12));
	// ������� ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ������ ���� PenBlack ��������
	SelectObject(hdc, PenBlack);
	// ������ ���� ���������� ����� � ������
	Nimbus(PenBlack, Brush);
	// ������ ������ ���������� ������ ������� �������� �������� ������
	Body(PenBlack);
	// ������ ���� ���������� ������ �������� ������
	Rays(PenBlack);
	// ������ ������� ���������� ������ ������� �������� �������� ������
	Craters(PenBlack);

	DeleteObject(PenBlack);             // ���������� ��������� ���� ������ ���� PenBlack
	DeleteObject(Brush);                // ���������� ��������� ���� ������ ���� Brush
}

// ������� �������� ����� ����� ����� ���������� ������/ ������ ������. ����������� �����
double Neutron_Star::Left_Border()
{
	return(GetX() - 8 * GetSize());
}

// ������� �������� ����� ������ ����� ���������� ������/ ������ ������. ����������� �����
double Neutron_Star::Right_Border()
{
	return(GetX() + 5 * GetSize());
}

// ������� �������� ����� ������� ����� ���������� ������/ ������ ������. ����������� �����
double Neutron_Star::High_Border()
{
	return(GetY() + 2.2 * GetSize());
}

// ������� �������� ����� ������ ����� ���������� ������/ ������ ������. ����������� �����
double Neutron_Star::Low_Border()
{
	return(GetY() - 10 * GetSize());
}


/*------------------------------------------------------------------------*/
/*            Dead_Star           */
/*--------------------------------*/

// ����������� ����� ������� ������ �� Neutron_Star  � �� ������������ �� Asteroid, Point � Location. � IAsteroid.
// �����������
Dead_Star::Dead_Star(double InitX, double InitY) : Neutron_Star(InitX, InitY)
{
	m_number = CountMeteor - 1;      // ����� ���������
	m_size = 12;				     // �������� ��� ���������
};

// ����������
Dead_Star::	~Dead_Star()                                               
{
	// ������ ����
}

// ����������� ������� ��� ������������� ������������
// ��������� ���� �������� ����� � ������
void Dead_Star::Core(HPEN Pen, HBRUSH Brush)
{
	Ellipse(hdc, m_X - 4 * m_size, m_Y - 2 * m_size, m_X + 1 * m_size, m_Y - 7 * m_size);
}

// ��������� ����� �������� ����� � ������
void Dead_Star::Bumps(HPEN Pen)
{
	MoveToEx(hdc, m_X - 0.6 * m_size, m_Y - 4 * m_size, nullptr);         // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 1.3 * m_size, m_Y - 4.5 * m_size);                  // ��������� ��������� �������� ������
	MoveToEx(hdc, m_X + 1.3 * m_size, m_Y - 4.5 * m_size, nullptr);
	LineTo(hdc, m_X + 1.3 * m_size, m_Y - 5 * m_size);
	MoveToEx(hdc, m_X + 1.3 * m_size, m_Y - 5 * m_size, nullptr);
	LineTo(hdc, m_X + 3 * m_size, m_Y - 4.5 * m_size);

	MoveToEx(hdc, m_X - 2.4 * m_size, m_Y - 3.7 * m_size, nullptr);
	LineTo(hdc, m_X - 4.3 * m_size, m_Y - 3.2 * m_size);
	MoveToEx(hdc, m_X - 4.3 * m_size, m_Y - 3.2 * m_size, nullptr);
	LineTo(hdc, m_X - 4.3 * m_size, m_Y - 2.7 * m_size);
	MoveToEx(hdc, m_X - 4.3 * m_size, m_Y - 2.7 * m_size, nullptr);
	LineTo(hdc, m_X - 6.2 * m_size, m_Y - 3.2 * m_size);

	MoveToEx(hdc, m_X - 1.5 * m_size, m_Y - 3.2 * m_size, nullptr);
	LineTo(hdc, m_X - 1.2 * m_size, m_Y - 1.7 * m_size);
	MoveToEx(hdc, m_X - 1.2 * m_size, m_Y - 1.7 * m_size, nullptr);
	LineTo(hdc, m_X - 1.6 * m_size, m_Y - 1.7 * m_size);
	MoveToEx(hdc, m_X - 1.6 * m_size, m_Y - 1.7 * m_size, nullptr);
	LineTo(hdc, m_X - 1.3 * m_size, m_Y + 0.2 * m_size);

	MoveToEx(hdc, m_X - 1.8 * m_size, m_Y - 4.8 * m_size, nullptr);
	LineTo(hdc, m_X - 2.3 * m_size, m_Y - 6.5 * m_size);
	MoveToEx(hdc, m_X - 2.3 * m_size, m_Y - 6.5 * m_size, nullptr);
	LineTo(hdc, m_X - 1.8 * m_size, m_Y - 6.5 * m_size);
	MoveToEx(hdc, m_X - 1.8 * m_size, m_Y - 6.5 * m_size, nullptr);
	LineTo(hdc, m_X - 2.2 * m_size, m_Y - 8.5 * m_size);
}

// �������� ������ ������ �� ������. ����������� �����
void Dead_Star::Show()
{
	m_Visible = true;              // ������ ������ �����
	// ������� ���, ������� � ���� ����
	HPEN PenGreen = CreatePen(PS_SOLID, 3, RGB(152, 255, 152));
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ������ ���� PenGreen ��������
	SelectObject(hdc, PenGreen);
	// ������������ ���� �������� ����� � ������
	Nimbus(PenGreen, Brush);
	Brush = CreateSolidBrush(RGB(248, 0, 0));
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ������������ ���� �������� ����� � ������
	Core(PenGreen, Brush);
	// ��������� ������� �������� �����
	Bumps(PenGreen);

	DeleteObject(PenGreen);       // ���������� ��������� ���� ������ ���� PenBlue
	DeleteObject(Brush);          // ���������� ��������� ���� ������ ����� Brush
}

// ������ ������� ������ � ������. ����������� �����
void Dead_Star::Hide()            
{
	m_Visible = false;            // ������� ������ �������
	// ������� ���, ������� � ���� ����
	HPEN PenBlack = CreatePen(PS_SOLID, 3, RGB(12, 12, 12));
	// ������� ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ������ ���� PenBlack ��������
	SelectObject(hdc, PenBlack);
	// ������������ �� ������ ������
	Core(PenBlack, Brush);
	Bumps(PenBlack);
	Nimbus(PenBlack, Brush);

	DeleteObject(PenBlack);              // ���������� ��������� ���� ������ ���� PenBlue
	DeleteObject(PenBlack);              // ���������� ��������� ���� ������ ����� Brush
}




/*------------------------------------------------------------------------------------------------------*/
/*            �������� �������         */
/*-------------------------------------*/

/*------------------------------------------------------------------------------------------------------*/
/*           FlyingPlate         */
/*-------------------------------*/

// ����������� ����� ��������_������� �� ���������� IFlyingPlate, �� Point � �� ����������� �� Location
// ������ ���������� ������ ���� ������������� �����������
// ����������� �������� �������
FlyingPlate::FlyingPlate(int InitX, int InitY) : Point(InitX, InitY)
{
	m_parametr = 15;                   // �������� ��� ��������� � ����������� �������
	m_num_plate = 0;                   // ������ ����� �������� �������
}

// ����������
FlyingPlate::~FlyingPlate()
{
	// ������ ����
}

// ����������� ������ ��� ��������� �������� �������
double FlyingPlate::GetParametr() const                   
{
	return(m_parametr);               // ������� �������� ��������� ��� ���������
}

// ������ ��� �������������� ��������� �������� �������
void FlyingPlate::SetParameter(int NewParametr)
{
	m_parametr = NewParametr;         // ���������� ���������� �������� ���������
}

// ����������� ������ ��� ��������� �������� ������
int FlyingPlate::GetNum() const
{
	return(m_num_plate);              // ������� �������� ������ �������� �������
}

// ������ ��� �������������� ��������� �������� ������� ������
void FlyingPlate::SetNum(int NewNum)
{
	m_num_plate = NewNum;             // ���������� ���������� �������� ������
}

// ��������� ������ "���� �������"
void FlyingPlate::Skirt(HPEN Pen)
{
	// ���
	MoveToEx(hdc, m_X - 4 * m_parametr, m_Y - 2.4 * m_parametr, NULL);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 7* m_parametr, m_Y - 2.4 * m_parametr);            // ��������� ��������� �������� ������

	// ������ �������
	MoveToEx(hdc, m_X + 7 * m_parametr, m_Y - 2.4 * m_parametr, NULL);   // ��������� ��������� �������� ������
	LineTo(hdc, m_X + 7.2 * m_parametr, m_Y - 2.6 * m_parametr);         // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X + 7.2 * m_parametr, m_Y - 2.6 * m_parametr, NULL); // ��������� ��������� �������� ������
	LineTo(hdc, m_X + 7.1 * m_parametr, m_Y - 2.8 * m_parametr);         // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X + 7.1 * m_parametr, m_Y - 2.8 * m_parametr, NULL); // ��������� ��������� �������� ������
	LineTo(hdc, m_X + 4.8 * m_parametr, m_Y - 4 * m_parametr);           // ��������� ���������� �������� ������


	// ����� �������
	MoveToEx(hdc, m_X - 4 * m_parametr, m_Y - 2.4 * m_parametr, NULL);   // ��������� ��������� �������� ������
	LineTo(hdc, m_X - 4.2 * m_parametr, m_Y - 2.6 * m_parametr);         // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X - 4.2 * m_parametr, m_Y - 2.6 * m_parametr, NULL); // ��������� ��������� �������� ������
	LineTo(hdc, m_X - 4.1 * m_parametr, m_Y - 2.8 * m_parametr);         // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X - 4.1 * m_parametr, m_Y - 2.8 * m_parametr, NULL); // ��������� ��������� �������� ������
	LineTo(hdc, m_X - 1.8 * m_parametr, m_Y - 4 * m_parametr);           // ��������� ���������� �������� ������

	// ����
	MoveToEx(hdc, m_X - 1.8 * m_parametr, m_Y - 4 * m_parametr, NULL);   // ��������� ��������� �������� ������
	LineTo(hdc, m_X + 4.8 * m_parametr, m_Y - 4 * m_parametr);           // ��������� ���������� �������� ������
}

// ��������� ���� ������ ���� �������� �������
void FlyingPlate::Windows(HPEN Pen, HBRUSH Brush)
{
	//������������
	// �����
	Ellipse(hdc, m_X - 2 * m_parametr, m_Y - 2.7 * m_parametr, m_X - 1.1 * m_parametr, m_Y - 3.6 * m_parametr);

	// ��������
	Ellipse(hdc, m_X + 2 * m_parametr, m_Y - 2.7 * m_parametr, m_X + 1.1 * m_parametr, m_Y - 3.6 * m_parametr);

	// ������
	Ellipse(hdc, m_X + 5 * m_parametr, m_Y - 2.7 * m_parametr, m_X + 4.1 * m_parametr, m_Y - 3.6 * m_parametr);
}

// ��������� ������ �������� �������
void FlyingPlate::Glass(HPEN Pen)
{
	MoveToEx(hdc, m_X - 1.8 * m_parametr, m_Y - 4.2 * m_parametr, NULL);  // ��������� ��������� �������� ������
	LineTo(hdc, m_X - 1.5 * m_parametr, m_Y - 5 * m_parametr);            // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X + 4.8 * m_parametr, m_Y - 4.2 * m_parametr, NULL);  // ��������� ��������� �������� ������
	LineTo(hdc, m_X + 4.5 * m_parametr, m_Y - 5 * m_parametr);            // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X - 1.5 * m_parametr, m_Y - 5 * m_parametr, NULL);    // ��������� ��������� �������� ������
	LineTo(hdc, m_X - 1 * m_parametr, m_Y - 5.8 * m_parametr);            // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X + 4.5 * m_parametr, m_Y - 5 * m_parametr, NULL);    // ��������� ��������� �������� ������
	LineTo(hdc, m_X + 4 * m_parametr, m_Y - 5.8 * m_parametr);            // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X - 1 * m_parametr, m_Y - 5.8 * m_parametr, NULL);    // ��������� ��������� �������� ������
	LineTo(hdc, m_X - 0 * m_parametr, m_Y - 6.4 * m_parametr);            // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X + 4 * m_parametr, m_Y - 5.8 * m_parametr, NULL);    // ��������� ��������� �������� ������
	LineTo(hdc, m_X + 3 * m_parametr, m_Y - 6.4 * m_parametr);            // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X - 0 * m_parametr, m_Y - 6.4 * m_parametr, NULL);    // ��������� ��������� �������� ������
	LineTo(hdc, m_X + 1 * m_parametr, m_Y - 6.6 * m_parametr);            // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X + 3 * m_parametr, m_Y - 6.4 * m_parametr, NULL);    // ��������� ��������� �������� ������
	LineTo(hdc, m_X + 2 * m_parametr, m_Y - 6.6 * m_parametr);            // ��������� ���������� �������� ������
	
	MoveToEx(hdc, m_X + 2 * m_parametr, m_Y - 6.6 * m_parametr, NULL);    // ��������� ��������� �������� ������
	LineTo(hdc, m_X + 1 * m_parametr, m_Y - 6.6 * m_parametr);            // ��������� ���������� �������� ������
}

// ��������� �����/������� ���� �������� �������
void FlyingPlate::Legs(HPEN Pen)
{
	MoveToEx(hdc, m_X - 1.7 * m_parametr, m_Y - 2.3 * m_parametr, NULL);  // ��������� ��������� �������� ������
	LineTo(hdc, m_X - 1 * m_parametr, m_Y - 1.9 * m_parametr);            // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X + 4.8 * m_parametr, m_Y - 2.3 * m_parametr, NULL);  // ��������� ��������� �������� ������
	LineTo(hdc, m_X + 4.1 * m_parametr, m_Y - 1.9 * m_parametr);          // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X - 1 * m_parametr, m_Y - 1.9 * m_parametr, NULL);    // ��������� ��������� �������� ������
	LineTo(hdc, m_X - 0 * m_parametr, m_Y - 1.7 * m_parametr);            // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X + 4.1 * m_parametr, m_Y - 1.9 * m_parametr, NULL);  // ��������� ��������� �������� ������
	LineTo(hdc, m_X + 3.1 * m_parametr, m_Y - 1.7 * m_parametr);          // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X - 0 * m_parametr, m_Y - 1.7 * m_parametr, NULL);    // ��������� ��������� �������� ������
	LineTo(hdc, m_X + 0.8 * m_parametr, m_Y - 1.6 * m_parametr);          // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X + 3.1 * m_parametr, m_Y - 1.7 * m_parametr, NULL);  // ��������� ��������� �������� ������
	LineTo(hdc, m_X + 2.3 * m_parametr, m_Y - 1.6 * m_parametr);          // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X + 0.8 * m_parametr, m_Y - 1.6 * m_parametr, NULL);  // ��������� ��������� �������� ������
	LineTo(hdc, m_X + 2.3 * m_parametr, m_Y - 1.6 * m_parametr);          // ��������� ���������� �������� ������
}

// �������� �������� ������� �� ������. ����������� �����
void FlyingPlate::Show()
{
	m_Visible = true;                          // �������� ������� �����
	
	// ������� ���, ������� � ���� ����
	HPEN PenGrey = CreatePen(PS_SOLID, 4, RGB(144, 144, 144));
	// ������ ���� PenGrey ��������
	SelectObject(hdc, PenGrey);
	Skirt(PenGrey);                            // ��������� "���� �������"

	// ������� ���, ������� � ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(0, 51, 153));
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	Windows(PenGrey, Brush);                   // ��������� ���� ������ ���� �������� �������

	// ������� ���, ������� � ���� ����
	HPEN PenTwitter = CreatePen(PS_SOLID, 4, RGB(31, 206, 203));
	// ������ ���� PenTwitter ��������
	SelectObject(hdc, PenTwitter);
	Glass(PenTwitter);                         // ��������� ������ �������� �������

	// ������ ���� PenGrey ��������
	SelectObject(hdc, PenGrey);
	Legs(PenGrey);                             // ��������� �����/������� ���� �������� �������

	DeleteObject(PenGrey);                     // ��������� ��������� ���� ������� PenGrey
	DeleteObject(PenTwitter);                  // ��������� ��������� ���� ������� PenTwitter
	DeleteObject(Brush);                       // ��������� ����� Brush
}

// ������ �������� ������� � ������. ����������� �����
void FlyingPlate::Hide()
{
	m_Visible = false;                         // �������� ������� �� �����

	// ��������� ���� �� ������� ������ �������
	// ������� ���, ������� � ���� ����
	HPEN PenBlack = CreatePen(PS_SOLID, 4, RGB(12, 12, 12));
	
	// ������ ���� PenBlack ��������
	SelectObject(hdc, PenBlack);
	Skirt(PenBlack);                           // ��������� "���� �������"

	// ������� ���, ������� � ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	Windows(PenBlack, Brush);                  // ��������� ���� ������ ���� �������� �������
	Glass(PenBlack);                           // ��������� ������ �������� �������
	Legs(PenBlack);                            // ��������� �����/������� ���� �������� �������

	DeleteObject(PenBlack);                    // ��������� ��������� ���� ������� PenGreyPurple
	DeleteObject(Brush);                       // ��������� ����� Brush
}

// ������� �������� ����� ����� ����� �������� �������/   �������� �������� �������
int FlyingPlate:: Left_Border()                          
{
	return(GetX() - 4.3 * GetParametr());
}

// ������� �������� ����� ������ ����� �������� �������/  �������� �������� �������
int FlyingPlate::Right_Border()
{
	return(GetX() + 7.3 * GetParametr());
}

// ������� �������� ����� ������ ����� �������� �������/  �������� �������� �������
int FlyingPlate::Low_Border()                           
{
	return(GetY() - 6.6 * m_parametr);
}

// ������� �������� ����� ������� ����� �������� �������/ �������� �������� �������
int FlyingPlate::High_Border()
{
	return(GetY() - 1.6 * m_parametr);
}


/*------------------------------------------------------------------------------------------------------*/
/*         Broke_FlyingPlate           */
/*-------------------------------------*/

// ����������� ����� �������� ��������_������� �� FlyingPlate � �� ����������� �� Point � Location. � IFlyingPlate
// �����������
Broke_FlyingPlate::Broke_FlyingPlate(int InitX, int InitY):FlyingPlate(InitX, InitY)
{
	m_parametr = 15;                           // �������� ��� ��������� � ����������� �������          
	m_num_plate = 1;                           // ������ ����� �������� �������
}

// ����������
Broke_FlyingPlate:: ~Broke_FlyingPlate() 
{
	// ������ ����
}

// ��������� ���������� ������ ��������� �������� �������
void Broke_FlyingPlate::Glass(HPEN Pen)
{
	MoveToEx(hdc, m_X - 1.8 * m_parametr, m_Y - 4.2 * m_parametr, NULL);               // ��������� ��������� �������� ������
	LineTo(hdc, m_X - 1.5 * m_parametr, m_Y - 5 * m_parametr);                         // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X + 4.8 * m_parametr, m_Y - 4.2 * m_parametr, NULL);               // ��������� ��������� �������� ������
	LineTo(hdc, m_X + 4.5 * m_parametr, m_Y - 5 * m_parametr);                         // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X - 1.5 * m_parametr, m_Y - 5 * m_parametr, NULL);                 // ��������� ��������� �������� ������
	LineTo(hdc, m_X - 1 * m_parametr, m_Y - 5.8 * m_parametr);                         // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X - 1 * m_parametr, m_Y - 5.8 * m_parametr, NULL);                 // ��������� ��������� �������� ������
	LineTo(hdc, m_X - 0 * m_parametr, m_Y - 6.4 * m_parametr);                         // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X - 0 * m_parametr, m_Y - 6.4 * m_parametr, NULL);                 // ��������� ��������� �������� ������
	LineTo(hdc, m_X + 0.5 * m_parametr, m_Y - 5.5 * m_parametr);                       // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X + 0.5 * m_parametr, m_Y - 5.5 * m_parametr, NULL);               // ��������� ��������� �������� ������
	LineTo(hdc, m_X + 2 * m_parametr, m_Y - 6.2 * m_parametr);                         // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X + 2 * m_parametr, m_Y - 6.2 * m_parametr, NULL);                 // ��������� ��������� �������� ������
	LineTo(hdc, m_X + 2 * m_parametr, m_Y - 5 * m_parametr);                           // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X + 2 * m_parametr, m_Y - 5 * m_parametr, NULL);                   // ��������� ��������� �������� ������
	LineTo(hdc, m_X + 4 * m_parametr, m_Y - 5.8 * m_parametr);                         // ��������� ���������� �������� ������

	MoveToEx(hdc, m_X + 4 * m_parametr, m_Y - 5.8 * m_parametr, NULL);                 // ��������� ��������� �������� ������
	LineTo(hdc, m_X + 4.5 * m_parametr, m_Y - 5 * m_parametr);                         // ��������� ���������� �������� ������
}

// �������� ��������� �������� ������� �� ������. ����������� �����
void Broke_FlyingPlate::Show()
{
	m_Visible = true;                          // �������� �������� ������� �����
	
	// ������� ���, ������� � ���� ����
	HPEN PenGrey = CreatePen(PS_SOLID, 4, RGB(144, 144, 144));
	// ������ ���� PenGrey ��������
	SelectObject(hdc, PenGrey);
	Skirt(PenGrey);                            // ��������� "���� �������". ������������ �������

	// ������� ���, ������� � ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(252, 40, 71));
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	Windows(PenGrey, Brush);                   // ��������� ���� ������ ���� �������� �������. ������������ �����

	// ������� ���, ������� � ���� ����
	HPEN PenTwitter = CreatePen(PS_SOLID, 4, RGB(31, 206, 203));
	// ������ ���� PenTwitter ��������
	SelectObject(hdc, PenTwitter);
	Glass(PenTwitter);                         // ��������� ���������� ������ ��������� �������� �������
	
	// ������ ���� PenGrey ��������
	SelectObject(hdc, PenGrey);               
	Legs(PenGrey);                             // ��������� �����/������� ���� �������� �������. ������������ �������

	DeleteObject(PenGrey);                     // ��������� ��������� ���� ������� PenGrey
	DeleteObject(PenTwitter);                  // ��������� ��������� ���� ������� PenTwitter
	DeleteObject(Brush);                       // ��������� ����� Brush
}

// ������ �������� �������� ������� � ������. ����������� �����
void Broke_FlyingPlate::Hide()
{
	m_Visible = false;                         // �������� �������� ������� �� �����
	
	// ��������� ���� �� ������� ������ �������
	// ������� ���, ������� � ���� ����
	HPEN PenBlack = CreatePen(PS_SOLID, 4, RGB(12, 12, 12));
	// ������ ���� PenBlack  ��������
	SelectObject(hdc, PenBlack);
	Skirt(PenBlack);                           // ��������� "���� �������". ������������ �������

	// ������� ���, ������� � ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	Windows(PenBlack, Brush);                  // ��������� ���� ������ ���� �������� �������� �������. ������������ �������
	Glass(PenBlack);                           // ��������� ������ �������� �������� �������.
	Legs(PenBlack);                            // ��������� �����/������� ���� �������� �������. ������������ �������

	DeleteObject(PenBlack);                    // ��������� ��������� ���� ������� PenBlack
	DeleteObject(Brush);                       // ��������� ����� Brush
}


/*------------------------------------------------------------------------------------------------------*/
/*        Angry_FlyingPlate           */
/*------------------------------------*/

// ����������� ����� ���� ��������_������� �� FlyingPlate � �� ����������� �� Point � Location. � IFlyingPlate
Angry_FlyingPlate::Angry_FlyingPlate(int InitX, int InitY): FlyingPlate(InitX, InitY)  // �����������.
{
	m_parametr = 15;                           // �������� ��� ��������� � ����������� ������� 
	m_num_plate = 2;						   // ������ ����� �������� �������
}

// ����������
Angry_FlyingPlate::~Angry_FlyingPlate()
{
	// ������ ����
}

// ��������� ������ "���� �������" ���� �������� �������
void Angry_FlyingPlate:: Skirt(HPEN Pen)
{
	// ���
	MoveToEx(hdc, m_X - 4 * m_parametr, m_Y - 2.4 * m_parametr, NULL);                 // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 7 * m_parametr, m_Y - 2.4 * m_parametr);                         // ��������� ��������� �������� ������
	// ����
	MoveToEx(hdc, m_X - 4 * m_parametr, m_Y - 2.4 * m_parametr, NULL);                 // ��������� ���������� �������� ������
	LineTo(hdc, m_X -4 * m_parametr, m_Y - 3.5 * m_parametr);                          // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 7 * m_parametr, m_Y - 2.4 * m_parametr, NULL);                 // ��������� ���������� �������� ������
	LineTo(hdc, m_X +7 * m_parametr, m_Y - 3.5 * m_parametr);                          // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 7 * m_parametr, m_Y - 3.5 * m_parametr, NULL);                 // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 4 * m_parametr, m_Y - 3.5 * m_parametr);                         // ��������� ��������� �������� ������

	// ����
	MoveToEx(hdc, m_X - 4 * m_parametr, m_Y - 3.5 * m_parametr, NULL);                 // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 0.5 * m_parametr, m_Y - 5 * m_parametr);                         // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 7 * m_parametr, m_Y - 3.5 * m_parametr, NULL);                 // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 3.5 * m_parametr, m_Y - 5 * m_parametr);                         // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 0.5 * m_parametr, m_Y - 5 * m_parametr, NULL);                 // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 3.5 * m_parametr, m_Y - 5 * m_parametr);                         // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 0.5 * m_parametr, m_Y - 5 * m_parametr, NULL);                 // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 0 * m_parametr, m_Y - 6.2 * m_parametr);                         // ��������� ��������� �������� ������

	// ��������
	MoveToEx(hdc, m_X - 0 * m_parametr, m_Y - 5.9 * m_parametr, NULL);                 // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 3 * m_parametr, m_Y - 5.9 * m_parametr);                         // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 3.5 * m_parametr, m_Y - 5 * m_parametr, NULL);                 // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 3 * m_parametr, m_Y - 6.2 * m_parametr);                         // ��������� ��������� �������� ������

	// ���
	MoveToEx(hdc, m_X - 2 * m_parametr, m_Y - 2.4 * m_parametr, NULL);                 // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 0 * m_parametr, m_Y - 1.5 * m_parametr);                         // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 5 * m_parametr, m_Y - 2.4 * m_parametr, NULL);                 // ��������� ���������� �������� ������
	LineTo(hdc, m_X +3 * m_parametr, m_Y - 1.5 * m_parametr);                          // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 0 * m_parametr, m_Y - 1.5 * m_parametr, NULL);                 // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 3 * m_parametr, m_Y - 1.5 * m_parametr);                         // ��������� ��������� �������� ������

	//�����
	MoveToEx(hdc, m_X - 0 * m_parametr, m_Y - 5.9 * m_parametr, NULL);                 // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 0.5 * m_parametr, m_Y - 7.5 * m_parametr);                       // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 3 * m_parametr, m_Y - 5.9 * m_parametr, NULL);                 // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 3.5 * m_parametr, m_Y - 7.5 * m_parametr);                       // ��������� ��������� �������� ������

	// �������

	MoveToEx(hdc, m_X - 0.3 * m_parametr, m_Y - 5 * m_parametr, NULL);                 // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 2 * m_parametr, m_Y - 3.5 * m_parametr);                         // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 3.5 * m_parametr, m_Y - 5 * m_parametr, NULL);                 // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 5 * m_parametr, m_Y - 3.5 * m_parametr);                         // ��������� ��������� �������� ������
}

// ��������� ������ ���� �������� �������
void Angry_FlyingPlate::Glass(HPEN Pen)
{
	MoveToEx(hdc, m_X - 0 * m_parametr, m_Y - 6.2 * m_parametr, NULL);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 0.5 * m_parametr, m_Y - 7 * m_parametr);               // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 3 * m_parametr, m_Y - 6.2 * m_parametr, NULL);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 2.5 * m_parametr, m_Y - 7 * m_parametr);               // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 0.5 * m_parametr, m_Y - 7 * m_parametr, NULL);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 1 * m_parametr, m_Y - 7.4 * m_parametr);               // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 2.5 * m_parametr, m_Y - 7 * m_parametr, NULL);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 2 * m_parametr, m_Y - 7.4 * m_parametr);               // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 2 * m_parametr, m_Y - 7.4 * m_parametr, NULL);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 1 * m_parametr, m_Y - 7.4 * m_parametr);               // ��������� ��������� �������� ������
}

// ��������� ���� ������ ���� ���� �������� �������
void Angry_FlyingPlate::Windows(HPEN Pen, HBRUSH Brush)
{
	// �����
	Ellipse(hdc, m_X - 2.9 * m_parametr, m_Y - 2.6 * m_parametr, m_X - 2.1 * m_parametr, m_Y - 3.4 * m_parametr);

	// ��������
	Ellipse(hdc, m_X - 0 * m_parametr, m_Y - 2.6 * m_parametr, m_X +3 * m_parametr, m_Y - 3.4 * m_parametr);

	// ������
	Ellipse(hdc, m_X + 5.2 * m_parametr, m_Y - 2.6 * m_parametr, m_X + 6 * m_parametr, m_Y - 3.4 * m_parametr);
}

// ��������� �����/������� ���� ���� �������� �������
void Angry_FlyingPlate::Legs(HPEN Pen)
{
	MoveToEx(hdc, m_X - 0 * m_parametr, m_Y - 1.3 * m_parametr, NULL);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 0.5 * m_parametr, m_Y - 1 * m_parametr);               // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 3 * m_parametr, m_Y - 1.3 * m_parametr, NULL);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 2.5 * m_parametr, m_Y - 1 * m_parametr);               // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 0.5 * m_parametr, m_Y - 1 * m_parametr, NULL);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 1.3 * m_parametr, m_Y - 0.7 * m_parametr);             // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 2.5 * m_parametr, m_Y - 1 * m_parametr, NULL);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 1.7 * m_parametr, m_Y - 0.7 * m_parametr);             // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 1.3 * m_parametr, m_Y - 0.7 * m_parametr, NULL);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 1.7 * m_parametr, m_Y - 0.7 * m_parametr);             // ��������� ��������� �������� ������
}

// �������� ���� �������� ������� �� ������. ����������� �����
void Angry_FlyingPlate::Show()
{
	m_Visible = true;                          // ���� �������� ������� �����

	// ������� ���, ������� � ���� ����
	HPEN PenBrown = CreatePen(PS_SOLID, 4, RGB(127, 24, 13));
	HPEN PenYellow = CreatePen(PS_SOLID, 4, RGB(254, 254, 34));
	HPEN PenTwitter = CreatePen(PS_SOLID, 4, RGB(31, 206, 203));
	// ������� ���, ������� � ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(254, 254, 34));
	
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ������ ���� PenBrown ��������
	SelectObject(hdc, PenBrown);
	Skirt(PenBrown);                           // ��������� ������ "���� �������" ���� �������� �������

	// ������ ���� PenTwitter ��������
	SelectObject(hdc, PenTwitter);
	Glass(PenBrown);                           // ��������� ������ ���� �������� �������

	// ������ ���� PenYellow ��������
	SelectObject(hdc, PenYellow);
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	Windows(PenYellow, Brush);                 // ��������� ���� ������ ���� ���� �������� �������           
	Legs(PenBrown);                            // ��������� �����/������� ���� ���� �������� �������

	DeleteObject(PenYellow);                   // ��������� ��������� ���� ������� PenYellow
	DeleteObject(Brush);                       // ��������� ����� Brush
	DeleteObject(PenBrown);                    // ��������� ��������� ���� ������� PenBrown
	DeleteObject(PenTwitter);                  // ��������� ��������� ���� ������� PenTwitter
}

// ������ ���� �������� ������� � ������. ����������� �����
void Angry_FlyingPlate::Hide()
{
	m_Visible = false;                         // ���� �������� ������� �� �����

	// ��������� ���� �� ������� ������ �������
	// ������� ���, ������� � ���� ����
	HPEN PenBlack = CreatePen(PS_SOLID, 4, RGB(12, 12, 12));
	// ������� ���, ������� � ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ������ ���� PenBlack ��������
	SelectObject(hdc, PenBlack);

	Skirt(PenBlack);                           // ��������� "���� �������"
	Glass(PenBlack);                           // ��������� ������ ���� �������� �������
	Windows(PenBlack, Brush);				   // ��������� ���� ������ ���� ���� �������� �������
	Legs(PenBlack);							   // ��������� �����/������� ���� �������� �������

	DeleteObject(PenBlack);                    // ��������� ��������� ���� ������� PenBlack
	DeleteObject(Brush);                       // ��������� ����� Brush
}

// ������� �������� ����� ����� ����� ���� �������� �������
int Angry_FlyingPlate::Left_Border()                              
{
	return(GetX() - 3.9 * GetParametr());
}

// ������� �������� ����� ������ ����� ���� �������� �������
int Angry_FlyingPlate::Right_Border()                              
{
	return(GetX() + 7.1 * GetParametr());
}

// ������� �������� ����� ������ ����� ���� �������� �������
int Angry_FlyingPlate::Low_Border()                               
{
	return(GetY() - 7.4 * m_parametr);
}

// ������� �������� ����� ����� ����� ���� �������� �������
int Angry_FlyingPlate::High_Border()
{
	return(GetY() - 0.7 * m_parametr);
}


/*------------------------------------------------------------------------------------------------------*/
/*             Modify_FlyingPlate             */
/*--------------------------------------------*/

// ����������� ����� ���������������� ��������_������� �� Angry_FlyingPlate � �� ����������� �� FlyingPlate � Point � Location. � IFlyingPlate
// �����������
Modify_FlyingPlate:: Modify_FlyingPlate(int InitX, int InitY): Angry_FlyingPlate(InitX, InitY)
{
	m_parametr = 15;                           // �������� ��� ��������� � ����������� �������
	m_num_plate = 3;						   // ������ ����� �������� �������
}

// ����������
Modify_FlyingPlate:: ~Modify_FlyingPlate()
{
	// ������ ����
}

// ��������� ���������� ���������� ���������������� �������� �������
void Modify_FlyingPlate::Back(HPEN Pen)
{
	MoveToEx(hdc, m_X - 4 * m_parametr, m_Y - 2.4 * m_parametr, NULL);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 7 * m_parametr, m_Y - 2.4 * m_parametr);               // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 4 * m_parametr, m_Y - 2.4 * m_parametr, NULL);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 4.4 * m_parametr, m_Y - 3 * m_parametr);               // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 7 * m_parametr, m_Y - 2.4 * m_parametr, NULL);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 7.4 * m_parametr, m_Y - 3.1 * m_parametr);             // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 4.4 * m_parametr, m_Y - 3.1 * m_parametr, NULL);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 4 * m_parametr, m_Y - 3.8 * m_parametr);               // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 7.4 * m_parametr, m_Y - 3.1 * m_parametr, NULL);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 7 * m_parametr, m_Y - 3.8 * m_parametr);               // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 4 * m_parametr, m_Y - 3.8 * m_parametr, NULL);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 7 * m_parametr, m_Y - 3.8 * m_parametr);               // ��������� ��������� �������� ������
}

// ��������� ������ "���� �������" ���������������� �������� �������
void Modify_FlyingPlate:: Skirt(HPEN Pen)
{

	MoveToEx(hdc, m_X - 2.9 * m_parametr, m_Y - 2.4 * m_parametr, NULL);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 1.8 * m_parametr, m_Y - 2 * m_parametr);               // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 5.9 * m_parametr, m_Y - 2.4 * m_parametr, NULL);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 4.8 * m_parametr, m_Y - 2 * m_parametr);               // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 1.8 * m_parametr, m_Y - 2 * m_parametr, NULL);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 0.7 * m_parametr, m_Y - 1.7 * m_parametr);             // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 4.8 * m_parametr, m_Y - 2 * m_parametr, NULL);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 3.7 * m_parametr, m_Y - 1.7 * m_parametr);             // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 0.7 * m_parametr, m_Y - 1.7 * m_parametr, NULL);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 0.5 * m_parametr, m_Y - 1.6 * m_parametr);             // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 3.7 * m_parametr, m_Y - 1.7 * m_parametr, NULL);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 2.5 * m_parametr, m_Y - 1.6 * m_parametr);             // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 0.5 * m_parametr, m_Y - 1.6 * m_parametr, NULL);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 2.5 * m_parametr, m_Y - 1.6 * m_parametr);             // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 2.9 * m_parametr, m_Y - 3.8 * m_parametr, NULL);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 1.9 * m_parametr, m_Y - 5 * m_parametr);               // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 5.9 * m_parametr, m_Y - 3.8 * m_parametr, NULL);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 4.9 * m_parametr, m_Y - 5 * m_parametr);               // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 1.9 * m_parametr, m_Y - 5 * m_parametr, NULL);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 0* m_parametr, m_Y - 5.9 * m_parametr);                // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 4.9 * m_parametr, m_Y - 5 * m_parametr, NULL);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 3 * m_parametr, m_Y - 5.9 * m_parametr);               // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 0 * m_parametr, m_Y - 5.9 * m_parametr, NULL);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 1 * m_parametr, m_Y - 6.1 * m_parametr);               // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X + 1 * m_parametr, m_Y - 6.1 * m_parametr, NULL);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 3 * m_parametr, m_Y - 5.9 * m_parametr);               // ��������� ��������� �������� ������

	// �����
	MoveToEx(hdc, m_X + 3.5 * m_parametr, m_Y - 5.9 * m_parametr, NULL);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 4 * m_parametr, m_Y - 7 * m_parametr);                 // ��������� ��������� �������� ������

	MoveToEx(hdc, m_X - 0.3 * m_parametr, m_Y - 5.9 * m_parametr, NULL);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 1 * m_parametr, m_Y - 7 * m_parametr);                 // ��������� ��������� �������� ������
}

// ��������� ���� ������ ���� ���������������� �������� �������
void Modify_FlyingPlate::Windows(HPEN Pen, HBRUSH Brush)
{
	Ellipse(hdc, m_X - 2.9 * m_parametr, m_Y - 2.6 * m_parametr, m_X - 2.1 * m_parametr, m_Y - 3.4 * m_parametr);

	// ��������
	Ellipse(hdc, m_X - 1 * m_parametr, m_Y - 2.6 * m_parametr, m_X - 0.2 * m_parametr, m_Y - 3.4 * m_parametr);

	Ellipse(hdc, m_X + 1 * m_parametr, m_Y - 2.6 * m_parametr, m_X + 1.8 * m_parametr, m_Y - 3.4 * m_parametr);

	Ellipse(hdc, m_X + 3 * m_parametr, m_Y - 2.6 * m_parametr, m_X + 3.8 * m_parametr, m_Y - 3.4 * m_parametr);

	Ellipse(hdc, m_X + 4.9 * m_parametr, m_Y - 2.6 * m_parametr, m_X + 5.7 * m_parametr, m_Y - 3.4 * m_parametr);
}

// �������� ���������������� �������� ������� �� ������. ����������� �����
void Modify_FlyingPlate:: Show()                                 
{
	m_Visible = true;                          // ���� �������� ������� �����

	// ������� ���, ������� � ���� ������
	HPEN PenBrown = CreatePen(PS_SOLID, 4, RGB(183, 132, 167));
	HPEN PenYellow = CreatePen(PS_SOLID, 4, RGB(254, 254, 34));
	HPEN PenTwitter = CreatePen(PS_SOLID, 4, RGB(31, 206, 203));
	HPEN PenMalin = CreatePen(PS_SOLID, 4, RGB(220, 20, 60));
	// ������� ���, ������� � ���� ������
	HBRUSH Brush = CreateSolidBrush(RGB(254, 254, 34));

	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ������ ���� PenBrown ��������
	SelectObject(hdc, PenBrown);
	Skirt(PenBrown);                           // ��������� ������ "���� �������" ���������������� �������� �������
	
	// ������ ���� PenMalin ��������
	SelectObject(hdc, PenMalin);
	Back(PenBrown);                            // ��������� ���������� ���������� ���������������� �������� �������

	// ������ ���� PenTwitter ��������
	SelectObject(hdc, PenTwitter);
	Glass(PenBrown);                           // ��������� ������ ���� �������� �������. ������������ �����

	// ������ ���� PenYellow ��������
	SelectObject(hdc, PenYellow);
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	Windows(PenYellow, Brush);                 // ��������� ���� ������ ���� ���������������� �������� �������
	Legs(PenBrown);                            // ��������� �����/������� ���� ���� �������� �������. ������������ �����
	
	DeleteObject(PenMalin);                    // ��������� ��������� ���� ������� PenMalin
	DeleteObject(PenYellow);                   // ��������� ��������� ���� ������� PenYellow
	DeleteObject(Brush);                       // ��������� ����� Brush
	DeleteObject(PenBrown);                    // ��������� ��������� ���� ������� PenBrown
	DeleteObject(PenTwitter);                  // ��������� ��������� ���� ������� PenTwitter
}

// ������ ���������������� �������� ������� � ������. ����������� �����
void Modify_FlyingPlate:: Hide()                             
{
	m_Visible = false;                         // ���������������� �������� ������� �� �����
	
	// ��������� ���� �� ������� ������ �������
	// ������� ���, ������� � ���� ����
	HPEN PenBlack = CreatePen(PS_SOLID, 4, RGB(12, 12, 12));
	// ������� ���, ������� � ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));

	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ������ ���� PenBlack ��������
	SelectObject(hdc, PenBlack);

	Skirt(PenBlack);                           // ��������� ������ "���� �������" ���������������� �������� �������
	Glass(PenBlack);                           // ��������� ������ ���� �������� �������. ������������ �����
	Back(PenBlack);                            // ��������� ���������� ���������� ���������������� �������� �������
	Windows(PenBlack, Brush);                  // ��������� ���� ������ ���� ���������������� �������� �������
	Legs(PenBlack);                            // ��������� �����/������� ���� ���� �������� �������. ������������ �����
	
	DeleteObject(PenBlack);                    // ��������� ��������� ���� ������� PenBlack
	DeleteObject(Brush);                       // ��������� ����� Brush
}

// ������� �������� ����� ����� ����� ���������������� �������� �������
int Modify_FlyingPlate:: Left_Border()
{
	return(GetX() - 4.6 * GetParametr());
}

// ������� �������� ����� ������ ����� ���������������� �������� �������
int Modify_FlyingPlate::Right_Border()                             
{
	return(GetX() + 7.6 * GetParametr());
}

// ������� �������� ����� ������ ����� ���������������� �������� �������
int Modify_FlyingPlate::Low_Border()
{
	return(GetY() - 7.4 * m_parametr);
}

// ������� �������� ����� ����� ����� ���������������� �������� �������
int Modify_FlyingPlate::High_Border()                               
{
	return(GetY() - 0.6 * m_parametr);
}




/*-----------------------------------------------------------------------------------------------------------------------*/
/*             �������          */
/*------------------------------*/

/*------------------------------------------------------------------------*/
/*              Ship                */
/*----------------------------------*/

// ����������� ����� ������� �� Point � �� ����������� �� Location. ����������� �� ���������� IShip
// �����������
Ship::Ship(double InitX, double InitY) : Point(InitX, InitY)
{
	m_scale = 6;                          // ������. �������� ��� ��������� �������
	s_number = 0;                         // �����. �������� ��� ������� ��������� ��������. �������� � ������������
}

// ����������
Ship::~Ship()
{
	// ������ ����
}

// ������ ��� ��������� �������� �������
double Ship::GetScale() const
{
	return (m_scale);
}

// ������ ��� �������������� ��������� �������� �������
void Ship::SetScale(double NewScale)
{
	m_scale = NewScale;
}

// ������ ��� ��������� �������� ������ �������
int Ship::GetSNumber() const
{
	return (s_number);
}

// ������ ��� �������������� ��������� �������� �������� ������ �������
void Ship::SetSNumber(int NewSNumber)
{
	s_number = NewSNumber;
}

// ��������� ������� ������� ���������� ����� � ������
void Ship::body(HPEN Pen, HBRUSH Brush)
{
	// ������
	// ������ �����
	MoveToEx(hdc, m_X - 4 * m_scale, m_Y - 0 * m_scale, nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 4 * m_scale, m_Y - 0 * m_scale);
	MoveToEx(hdc, m_X - 4 * m_scale, m_Y - 0 * m_scale, nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 7 * m_scale, m_Y + 1.5 * m_scale);
	MoveToEx(hdc, m_X + 4 * m_scale, m_Y - 0 * m_scale, nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 7 * m_scale, m_Y + 1.5 * m_scale);

	MoveToEx(hdc, m_X - 4 * m_scale, m_Y - 1 * m_scale, nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 4 * m_scale, m_Y - 1 * m_scale);
	MoveToEx(hdc, m_X - 4 * m_scale, m_Y - 1 * m_scale, nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 7 * m_scale, m_Y + 0.5 * m_scale);
	MoveToEx(hdc, m_X + 4 * m_scale, m_Y - 1 * m_scale, nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 7 * m_scale, m_Y + 0.5 * m_scale);
	// ������� �����
	MoveToEx(hdc, m_X - 7 * m_scale, m_Y + 1.5 * m_scale, nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 12 * m_scale, m_Y - 9 * m_scale);
	MoveToEx(hdc, m_X + 7 * m_scale, m_Y + 1.5 * m_scale, nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 12 * m_scale, m_Y - 9 * m_scale);
	MoveToEx(hdc, m_X - 12 * m_scale, m_Y - 9 * m_scale, nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 8 * m_scale, m_Y - 16 * m_scale);
	MoveToEx(hdc, m_X + 12 * m_scale, m_Y - 9 * m_scale, nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 8 * m_scale, m_Y - 16 * m_scale);
	MoveToEx(hdc, m_X - 8 * m_scale, m_Y - 16 * m_scale, nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 5 * m_scale, m_Y - 20 * m_scale);
	MoveToEx(hdc, m_X + 8 * m_scale, m_Y - 16 * m_scale, nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 5 * m_scale, m_Y - 20 * m_scale);
	MoveToEx(hdc, m_X - 6 * m_scale, m_Y + 1 * m_scale, nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 11 * m_scale, m_Y - 9 * m_scale);
	MoveToEx(hdc, m_X - 11 * m_scale, m_Y - 9 * m_scale, nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 9.5 * m_scale, m_Y - 13 * m_scale);
	MoveToEx(hdc, m_X + 6 * m_scale, m_Y + 1 * m_scale, nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 11 * m_scale, m_Y - 9 * m_scale);
	MoveToEx(hdc, m_X + 11 * m_scale, m_Y - 9 * m_scale, nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 9.5 * m_scale, m_Y - 13 * m_scale);
}

// ��������� ���������� ���������� ����� � ������
void Ship::engines(HPEN Pen, HBRUSH Brush)
{
	MoveToEx(hdc, m_X - 5 * m_scale, m_Y - 19 * m_scale, nullptr);      // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 5.5 * m_scale, m_Y - 18.5 * m_scale);
	MoveToEx(hdc, m_X - 5.5 * m_scale, m_Y - 18.5 * m_scale, nullptr);  // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 6.4 * m_scale, m_Y - 8 * m_scale);

	MoveToEx(hdc, m_X - 5 * m_scale, m_Y - 19 * m_scale, nullptr);      // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 4.5 * m_scale, m_Y - 18.5 * m_scale);
	MoveToEx(hdc, m_X - 4.5 * m_scale, m_Y - 18.5 * m_scale, nullptr);  // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 3.6 * m_scale, m_Y - 8 * m_scale);
	Ellipse(hdc, m_X - 3.5 * m_scale, m_Y - 8.2 * m_scale, m_X - 6.5 * m_scale, m_Y - 7.2 * m_scale);

	MoveToEx(hdc, m_X + 5 * m_scale, m_Y - 19 * m_scale, nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 5.5 * m_scale, m_Y - 18.5 * m_scale);
	MoveToEx(hdc, m_X + 5 * m_scale, m_Y - 19 * m_scale, nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 4.5 * m_scale, m_Y - 18.5 * m_scale);

	MoveToEx(hdc, m_X + 5.5 * m_scale, m_Y - 18.5 * m_scale, nullptr); // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 6.4 * m_scale, m_Y - 8 * m_scale);
	MoveToEx(hdc, m_X + 4.5 * m_scale, m_Y - 18.5 * m_scale, nullptr); // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 3.6 * m_scale, m_Y - 8 * m_scale);
	Ellipse(hdc, m_X + 3.5 * m_scale, m_Y - 8.2 * m_scale, m_X + 6.5 * m_scale, m_Y - 7.2 * m_scale);
}

// ��������� ������ ������� �������� ����� � ������
void Ship::cabin(HPEN Pen, HBRUSH Brush)
{
	// ������
	MoveToEx(hdc, m_X - 5 * m_scale, m_Y - 20 * m_scale, nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 4 * m_scale, m_Y - 23 * m_scale);
	MoveToEx(hdc, m_X + 5 * m_scale, m_Y - 20 * m_scale, nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 4 * m_scale, m_Y - 23 * m_scale);
	MoveToEx(hdc, m_X - 4 * m_scale, m_Y - 23 * m_scale, nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 3.5 * m_scale, m_Y - 26 * m_scale);
	MoveToEx(hdc, m_X + 4 * m_scale, m_Y - 23 * m_scale, nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 3.5 * m_scale, m_Y - 26 * m_scale);
	MoveToEx(hdc, m_X - 3.5 * m_scale, m_Y - 26 * m_scale, nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 2.5 * m_scale, m_Y - 28 * m_scale);
	MoveToEx(hdc, m_X + 3.5 * m_scale, m_Y - 26 * m_scale, nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 2.5 * m_scale, m_Y - 28 * m_scale);
	MoveToEx(hdc, m_X - 2.5 * m_scale, m_Y - 28 * m_scale, nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 1.7 * m_scale, m_Y - 29 * m_scale);
	MoveToEx(hdc, m_X + 2.5 * m_scale, m_Y - 28 * m_scale, nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 1.7 * m_scale, m_Y - 29 * m_scale);

	//���
	MoveToEx(hdc, m_X - 1.7 * m_scale, m_Y - 29 * m_scale, nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 0.7 * m_scale, m_Y - 31 * m_scale);
	MoveToEx(hdc, m_X + 1.7 * m_scale, m_Y - 29 * m_scale, nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 0.7 * m_scale, m_Y - 31 * m_scale);
	MoveToEx(hdc, m_X - 0.7 * m_scale, m_Y - 31 * m_scale, nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 0 * m_scale, m_Y - 31.5 * m_scale);
	MoveToEx(hdc, m_X + 0.7 * m_scale, m_Y - 31 * m_scale, nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 0 * m_scale, m_Y - 31.5 * m_scale);

	// ������
	MoveToEx(hdc, m_X - 1.4 * m_scale, m_Y - 28 * m_scale, nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 0.6 * m_scale, m_Y - 30 * m_scale);
	MoveToEx(hdc, m_X + 1.5 * m_scale, m_Y - 28 * m_scale, nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 0.6 * m_scale, m_Y - 30 * m_scale);
	MoveToEx(hdc, m_X - 0.6 * m_scale, m_Y - 30 * m_scale, nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 0 * m_scale, m_Y - 30.5 * m_scale);
	MoveToEx(hdc, m_X + 0.6 * m_scale, m_Y - 30 * m_scale, nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 0 * m_scale, m_Y - 30.5 * m_scale);
	MoveToEx(hdc, m_X - 1.4 * m_scale, m_Y - 28 * m_scale, nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 2.5 * m_scale, m_Y - 8 * m_scale);
	MoveToEx(hdc, m_X + 1.5 * m_scale, m_Y - 28 * m_scale, nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 2.5 * m_scale, m_Y - 8 * m_scale);
	MoveToEx(hdc, m_X - 2.5 * m_scale, m_Y - 8 * m_scale, nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 1.4 * m_scale, m_Y - 3 * m_scale);
	MoveToEx(hdc, m_X + 2.5 * m_scale, m_Y - 8 * m_scale, nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 1.5 * m_scale, m_Y - 3 * m_scale);
	LineTo(hdc, m_X + 2.5 * m_scale, m_Y - 8 * m_scale);
	MoveToEx(hdc, m_X - 1.4 * m_scale, m_Y - 3 * m_scale, nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 1.4 * m_scale, m_Y - 0 * m_scale);
	MoveToEx(hdc, m_X + 1.5 * m_scale, m_Y - 3 * m_scale, nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 1.5 * m_scale, m_Y - 0 * m_scale);
	
	// ���� ������
	Ellipse(hdc, m_X - 3 * m_scale, m_Y - 27 * m_scale, m_X - 2 * m_scale, m_Y - 21 * m_scale);
	Ellipse(hdc, m_X + 3 * m_scale, m_Y - 27 * m_scale, m_X + 2 * m_scale, m_Y - 21 * m_scale);

}

// �������� ������� �� ������. ����������� �����
void Ship::Show()
{
	m_Visible = true;                      //  ������� �����
	HPEN PenBlueLaguna = CreatePen(PS_SOLID, 2, RGB(37, 109, 123));
	// ������� ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(48, 213, 200));
	HPEN PenMalahit = CreatePen(PS_SOLID, 2, RGB(0, 127, 255));

	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ������ ���� PenBlueLaguna ��������
	SelectObject(hdc, PenBlueLaguna);
	// ��������� ������� ������� �������� ����� � ������
	body(PenBlueLaguna, Brush);
	// ��������� ������ ������� �������� ����� � ������
	cabin(PenBlueLaguna, Brush);
	// ������� ���, ������� � ���� ����
	// ������ ���� PenMalahit ��������
	SelectObject(hdc, PenMalahit);
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ��������� ���������� ���������� ����� � ������
	engines(PenMalahit, Brush);

	DeleteObject(PenBlueLaguna);          // ���������� ��������� ���� ������ ���� PenBlueLaguna
	DeleteObject(Brush);                  // ���������� ��������� ���� ������ ����� Brush
	DeleteObject(PenMalahit);             // ���������� ��������� ���� ������ ���� PenMalahit
}

// ������ ������� � ������. ����������� �����
void Ship::Hide()
{
	m_Visible = false;                    // ������� �������
	// ������� ���, ������� � ���� ����
	HPEN PenBlack = CreatePen(PS_SOLID, 2, RGB(12, 12, 12));
	// ������� ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// ������ ���� PenBlack ��������
	SelectObject(hdc, PenBlack);
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ��������� ���������� ���������� ����� � ������
	body(PenBlack, Brush);
	// ��������� ������ ������� �������� ����� � ������
	cabin(PenBlack, Brush);
	engines(PenBlack, Brush);

	DeleteObject(PenBlack);               // ���������� ��������� ���� ������ ���� PenBlack
	DeleteObject(Brush);                  // ���������� ��������� ���� ������ ����� Brush
}

// ������� ����� ����� ����� �������/ ���������� �������
double Ship::Left_Border()
{
	return (m_X - 12 * m_scale);
}

// ������� ����� ������ ����� �������/ ���������� �������
double Ship::Right_Border()
{
	return (m_X + 12 * m_scale);
}

// ������� ����� ������� ����� �������/ ���������� �������
double Ship::High_Border()
{
	return (m_Y + 1.5 * m_scale);
}

// ������� ����� ������ ����� �������/ ���������� �������
double Ship::Low_Border()
{
	return (m_Y - 31.5 * m_scale);
}


/*------------------------------------------------------------------------*/
/*              Broke_Ship                */
/*----------------------------------------*/

// ����������� ����� ��������� ������� �� Ship � �� ����������� �� Point � Location. ����������� �� ���������� IShip
// ��� ������������� ������ ����� ���������� ����������� ������
Broke_Ship::Broke_Ship(double InitX, double InitY) : Ship(InitX, InitY) 
{
	m_scale = 6;               // ������. �������� ��� ��������� �������
	s_number = 1;              // �����. �������� ��� ������� ��������� ��������. �������� � ������������
}

// ����������
Broke_Ship:: ~Broke_Ship()
{
	// ������ ����
}

// ��������� ���������� ���������� ����� � ������
void Broke_Ship::engines(HPEN Pen, HBRUSH Brush)
{
	MoveToEx(hdc, m_X - 5 * GetScale(), m_Y - 19 * GetScale(), nullptr);      // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 5.5 * GetScale(), m_Y - 18.5 * GetScale());
	MoveToEx(hdc, m_X - 5.5 * GetScale(), m_Y - 18.5 * GetScale(), nullptr);  // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 6.4 * GetScale(), m_Y - 8 * GetScale());

	MoveToEx(hdc, m_X - 5 * GetScale(), m_Y - 19 * GetScale(), nullptr);      // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 4.5 * GetScale(), m_Y - 18.5 * GetScale());
	MoveToEx(hdc, m_X - 4.5 * GetScale(), m_Y - 18.5 * GetScale(), nullptr);  // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 3.6 * GetScale(), m_Y - 8 * GetScale());
	Ellipse(hdc, m_X - 3.5 * GetScale(), m_Y - 8.2 * GetScale(), m_X - 6.5 * GetScale(), m_Y - 7.2 * GetScale());
}

// �������� ��������� ������� �� ������. ����������� �����
void Broke_Ship::Show()
{
	m_Visible = true;           // ��������� ������� �����
	// ������� ���, ������� � ���� ����
	HPEN PenBlueLaguna = CreatePen(PS_SOLID, 2, RGB(37, 109, 123));
	// ������� ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(48, 213, 200));
	HPEN PenBlack = CreatePen(PS_SOLID, 2, RGB(12, 12, 12));
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ������ ���� PenBlueLaguna ��������
	SelectObject(hdc, PenBlueLaguna);
	// ��������� ������� ������� �������� ����� � ������
	body(PenBlueLaguna, Brush);
	engines(PenBlueLaguna, Brush);
	// ��������� ������ ������� �������� ����� � ������
	cabin(PenBlueLaguna, Brush);

	// ���������� ���������
	DeleteObject(PenBlack);       // ���������� ��������� ���� ������ ���� PenBlueLaguna
	DeleteObject(PenBlueLaguna);  // ���������� ��������� ���� ������ ���� PenBlueLaguna
	DeleteObject(Brush);          // ���������� ��������� ���� ������ ����� Brush
}

// ������ ��������� ������� � ������. ����������� �����
void Broke_Ship::Hide()
{
	m_Visible = false;            // ��������� ������� �������
	// ������� ���, ������� � ���� ����
	HPEN PenBlack = CreatePen(PS_SOLID, 2, RGB(12, 12, 12));
	// ������� ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ������ ���� PenBlack ��������
	SelectObject(hdc, PenBlack);
	// ��������� ������� ������� �������� ����� � ������
	body(PenBlack, Brush);
	// ��������� ������ ������� �������� ����� � ������
	cabin(PenBlack, Brush);
	engines(PenBlack, Brush);

	// ���������� ���������
	DeleteObject(PenBlack);        // ���������� ��������� ���� ������ ���� PenBlueLaguna
	DeleteObject(Brush);           // ���������� ��������� ���� ������ ����� Brush
}


/*------------------------------------------------------------------------*/
/*             Infinity_Ship              */
/*----------------------------------------*/

// ����������� ����� ����������� ������� ��  Ship � �� ����������� �� Point � Location. ����������� �� ���������� IShip
Infinity_Ship::Infinity_Ship(double InitX, double InitY) : Ship(InitX, InitY)
{
	m_scale = 5;               // ������. �������� ��� ��������� �������
	s_number = 2;              // �����. �������� ��� ������� ��������� ��������. �������� � ������������
}

// ����������
Infinity_Ship:: ~Infinity_Ship()
{
	// ������ ����
}

// ��������� ����������
void Infinity_Ship::engines(HPEN Pen, HBRUSH Brush)
{
	MoveToEx(hdc, m_X - 2 * GetScale(), m_Y - 31 * GetScale(), nullptr);      // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 0.2 * GetScale(), m_Y - 31.5 * GetScale());

	MoveToEx(hdc, m_X - 0.2 * GetScale(), m_Y - 31.5 * GetScale(), nullptr);  // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 0.2 * GetScale(), m_Y - 31.5 * GetScale());

	MoveToEx(hdc, m_X + 0.2 * GetScale(), m_Y - 31.5 * GetScale(), nullptr);  // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 2.1 * GetScale(), m_Y - 31 * GetScale());


	MoveToEx(hdc, m_X - 2 * GetScale(), m_Y - 31 * GetScale(), nullptr);      // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 1 * GetScale(), m_Y - 33 * GetScale());

	MoveToEx(hdc, m_X + 2.1 * GetScale(), m_Y - 31 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 1.1 * GetScale(), m_Y - 33 * GetScale());

	MoveToEx(hdc, m_X - 1 * GetScale(), m_Y - 33 * GetScale(), nullptr);      // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 0.1 * GetScale(), m_Y - 34 * GetScale());

	MoveToEx(hdc, m_X + 1.1 * GetScale(), m_Y - 33 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 0.2 * GetScale(), m_Y - 34 * GetScale());

	MoveToEx(hdc, m_X - 0.1 * GetScale(), m_Y - 34 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 0.2 * GetScale(), m_Y - 34 * GetScale());

	// ����� �� �������
	MoveToEx(hdc, m_X - 1.2 * GetScale(), m_Y - 8.5 * GetScale(), nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 0.5 * GetScale(), m_Y - 6.5 * GetScale());

	MoveToEx(hdc, m_X + 1.2 * GetScale(), m_Y - 8.5 * GetScale(), nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 0.5 * GetScale(), m_Y - 6.5 * GetScale());

	MoveToEx(hdc, m_X - 0.5 * GetScale(), m_Y - 6.5 * GetScale(), nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 0 * GetScale(), m_Y - 6 * GetScale());

	MoveToEx(hdc, m_X - 0 * GetScale(), m_Y - 6 * GetScale(), nullptr);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 0.5 * GetScale(), m_Y - 6.5 * GetScale());

	MoveToEx(hdc, m_X - 2 * GetScale(), m_Y - 7.5 * GetScale(), nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 0.5 * GetScale(), m_Y - 3 * GetScale());

	MoveToEx(hdc, m_X + 2 * GetScale(), m_Y - 7.5 * GetScale(), nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 0.5 * GetScale(), m_Y - 3 * GetScale());

	MoveToEx(hdc, m_X - 0.5 * GetScale(), m_Y - 3 * GetScale(), nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 0.1 * GetScale(), m_Y - 2.5 * GetScale());

	MoveToEx(hdc, m_X + 0.5 * GetScale(), m_Y - 3 * GetScale(), nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 0.1 * GetScale(), m_Y - 2.5 * GetScale());

	// ������� �����
	// �����
	MoveToEx(hdc, m_X - 4.8 * GetScale(), m_Y - 2.5 * GetScale(), nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 3.7 * GetScale(), m_Y - 1.5 * GetScale());

	MoveToEx(hdc, m_X - 3.7 * GetScale(), m_Y - 1.5 * GetScale(), nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 3.1 * GetScale(), m_Y - 0.5 * GetScale());

	MoveToEx(hdc, m_X - 3.1 * GetScale(), m_Y - 0.5 * GetScale(), nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 2.7 * GetScale(), m_Y + 0.5 * GetScale());

	// ������
	MoveToEx(hdc, m_X + 4.8 * GetScale(), m_Y - 2.5 * GetScale(), nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 3.7 * GetScale(), m_Y - 1.5 * GetScale());

	MoveToEx(hdc, m_X + 3.7 * GetScale(), m_Y - 1.5 * GetScale(), nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 3.1 * GetScale(), m_Y - 0.5 * GetScale());

	MoveToEx(hdc, m_X + 3.1 * GetScale(), m_Y - 0.5 * GetScale(), nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 2.7 * GetScale(), m_Y + 0.5 * GetScale());

	// ����� �����
	MoveToEx(hdc, m_X - 10.5 * GetScale(), m_Y - 8.5 * GetScale(), nullptr);  // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 11 * GetScale(), m_Y - 6.5 * GetScale());

	MoveToEx(hdc, m_X - 11 * GetScale(), m_Y - 6.5 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 10.8 * GetScale(), m_Y - 6 * GetScale());

	MoveToEx(hdc, m_X - 10.8 * GetScale(), m_Y - 6 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 10.3 * GetScale(), m_Y - 4.5 * GetScale());


	MoveToEx(hdc, m_X - 9.5 * GetScale(), m_Y - 9 * GetScale(), nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 10 * GetScale(), m_Y - 6.5 * GetScale());

	MoveToEx(hdc, m_X - 10 * GetScale(), m_Y - 6.5 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 9.8 * GetScale(), m_Y - 6 * GetScale());

	MoveToEx(hdc, m_X - 9.8 * GetScale(), m_Y - 6 * GetScale(), nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 9.3 * GetScale(), m_Y - 4.5 * GetScale());

	// ������ �����
	MoveToEx(hdc, m_X + 10.5 * GetScale(), m_Y - 8.5 * GetScale(), nullptr);  // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 11 * GetScale(), m_Y - 6.5 * GetScale());

	MoveToEx(hdc, m_X + 11 * GetScale(), m_Y - 6.5 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 10.8 * GetScale(), m_Y - 6 * GetScale());

	MoveToEx(hdc, m_X + 10.8 * GetScale(), m_Y - 6 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 10.3 * GetScale(), m_Y - 4.5 * GetScale());


	MoveToEx(hdc, m_X + 9.5 * GetScale(), m_Y - 9 * GetScale(), nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 10 * GetScale(), m_Y - 6.5 * GetScale());

	MoveToEx(hdc, m_X + 10 * GetScale(), m_Y - 6.5 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 9.8 * GetScale(), m_Y - 6 * GetScale());

	MoveToEx(hdc, m_X + 9.8 * GetScale(), m_Y - 6 * GetScale(), nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 9.3 * GetScale(), m_Y - 4.5 * GetScale());
}

// ��������� ������� �������
void Infinity_Ship::body(HPEN Pen, HBRUSH Brush)
{
	// ��� ������
	MoveToEx(hdc, m_X - 5 * GetScale(), m_Y + 1 * GetScale(), nullptr);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 5 * GetScale(), m_Y + 1 * GetScale());

	MoveToEx(hdc, m_X - 5 * GetScale(), m_Y + 1 * GetScale(), nullptr);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 6 * GetScale(), m_Y - 0 * GetScale());

	MoveToEx(hdc, m_X + 5 * GetScale(), m_Y + 1 * GetScale(), nullptr);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 6 * GetScale(), m_Y - 0 * GetScale());

	MoveToEx(hdc, m_X - 6 * GetScale(), m_Y - 0 * GetScale(), nullptr);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 6 * GetScale(), m_Y - 0.5 * GetScale());

	MoveToEx(hdc, m_X + 6 * GetScale(), m_Y - 0 * GetScale(), nullptr);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 6 * GetScale(), m_Y - 0.5 * GetScale());

	MoveToEx(hdc, m_X - 6 * GetScale(), m_Y - 0.5 * GetScale(), nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 5.5 * GetScale(), m_Y - 1.5 * GetScale());

	MoveToEx(hdc, m_X + 6 * GetScale(), m_Y - 0.5 * GetScale(), nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 5.5 * GetScale(), m_Y - 1.5 * GetScale());

	MoveToEx(hdc, m_X - 5.5 * GetScale(), m_Y - 1.5 * GetScale(), nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 3.8 * GetScale(), m_Y - 5 * GetScale());

	MoveToEx(hdc, m_X - 3.8 * GetScale(), m_Y - 5 * GetScale(), nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 1 * GetScale(), m_Y - 9 * GetScale());

	MoveToEx(hdc, m_X + 5.5 * GetScale(), m_Y - 1.5 * GetScale(), nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 3.8 * GetScale(), m_Y - 5 * GetScale());

	MoveToEx(hdc, m_X + 3.8 * GetScale(), m_Y - 5 * GetScale(), nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 1 * GetScale(), m_Y - 9 * GetScale());

	MoveToEx(hdc, m_X - 1 * GetScale(), m_Y - 9 * GetScale(), nullptr);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 0.1 * GetScale(), m_Y - 10 * GetScale());

	MoveToEx(hdc, m_X + 1 * GetScale(), m_Y - 9 * GetScale(), nullptr);       // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 0.3 * GetScale(), m_Y - 10 * GetScale());

	MoveToEx(hdc, m_X - 0.1 * GetScale(), m_Y - 10 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 0.2 * GetScale(), m_Y - 10 * GetScale());

	// ����� �����
	MoveToEx(hdc, m_X - 5 * GetScale(), m_Y + 0.3 * GetScale(), nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 5 * GetScale(), m_Y + 0.3 * GetScale());

	MoveToEx(hdc, m_X - 5 * GetScale(), m_Y + 0.3 * GetScale(), nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 6 * GetScale(), m_Y - 0.7 * GetScale());

	MoveToEx(hdc, m_X + 5 * GetScale(), m_Y + 0.3 * GetScale(), nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 6 * GetScale(), m_Y - 0.7 * GetScale());


	// ������ ������
	MoveToEx(hdc, m_X - 2.7 * GetScale(), m_Y - 7 * GetScale(), nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 4.3 * GetScale(), m_Y - 12 * GetScale());

	MoveToEx(hdc, m_X + 2.7 * GetScale(), m_Y - 7 * GetScale(), nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 4.4 * GetScale(), m_Y - 12 * GetScale());

	MoveToEx(hdc, m_X - 4.3 * GetScale(), m_Y - 12 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 5 * GetScale(), m_Y - 15 * GetScale());

	MoveToEx(hdc, m_X + 4.4 * GetScale(), m_Y - 12 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 5 * GetScale(), m_Y - 15 * GetScale());

	MoveToEx(hdc, m_X - 5 * GetScale(), m_Y - 15 * GetScale(), nullptr);      // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 4.8 * GetScale(), m_Y - 19 * GetScale());

	MoveToEx(hdc, m_X + 5 * GetScale(), m_Y - 15 * GetScale(), nullptr);      // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 4.9 * GetScale(), m_Y - 19 * GetScale());

	MoveToEx(hdc, m_X - 4.8 * GetScale(), m_Y - 19 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 4 * GetScale(), m_Y - 25 * GetScale());

	MoveToEx(hdc, m_X + 4.9 * GetScale(), m_Y - 19 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 4.1 * GetScale(), m_Y - 25 * GetScale());

	MoveToEx(hdc, m_X - 4 * GetScale(), m_Y - 25 * GetScale(), nullptr);      // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 3 * GetScale(), m_Y - 29 * GetScale());

	MoveToEx(hdc, m_X + 4.1 * GetScale(), m_Y - 25 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 3.1 * GetScale(), m_Y - 29 * GetScale());

	MoveToEx(hdc, m_X - 3 * GetScale(), m_Y - 29 * GetScale(), nullptr);      // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 2 * GetScale(), m_Y - 31 * GetScale());

	MoveToEx(hdc, m_X + 3.1 * GetScale(), m_Y - 29 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 2.1 * GetScale(), m_Y - 31 * GetScale());

	// �����
	MoveToEx(hdc, m_X - 1.7 * GetScale(), m_Y - 7 * GetScale(), nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 3.3 * GetScale(), m_Y - 12 * GetScale());

	MoveToEx(hdc, m_X + 1.7 * GetScale(), m_Y - 7 * GetScale(), nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 3.4 * GetScale(), m_Y - 12 * GetScale());

	MoveToEx(hdc, m_X - 3.3 * GetScale(), m_Y - 12 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 4 * GetScale(), m_Y - 15 * GetScale());

	MoveToEx(hdc, m_X + 3.4 * GetScale(), m_Y - 12 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 4 * GetScale(), m_Y - 15 * GetScale());

	MoveToEx(hdc, m_X - 4 * GetScale(), m_Y - 15 * GetScale(), nullptr);      // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 3.8 * GetScale(), m_Y - 19 * GetScale());

	MoveToEx(hdc, m_X + 4 * GetScale(), m_Y - 15 * GetScale(), nullptr);      // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 3.9 * GetScale(), m_Y - 19 * GetScale());

	MoveToEx(hdc, m_X - 3.8 * GetScale(), m_Y - 19 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 3 * GetScale(), m_Y - 25 * GetScale());

	MoveToEx(hdc, m_X + 3.9 * GetScale(), m_Y - 19 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 3.1 * GetScale(), m_Y - 25 * GetScale());

	MoveToEx(hdc, m_X - 3 * GetScale(), m_Y - 25 * GetScale(), nullptr);      // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 2 * GetScale(), m_Y - 29 * GetScale());

	MoveToEx(hdc, m_X + 3.1 * GetScale(), m_Y - 25 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 2.1 * GetScale(), m_Y - 29 * GetScale());

	MoveToEx(hdc, m_X - 2 * GetScale(), m_Y - 29 * GetScale(), nullptr);      // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 1 * GetScale(), m_Y - 31 * GetScale());

	MoveToEx(hdc, m_X + 2.1 * GetScale(), m_Y - 29 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 1.1 * GetScale(), m_Y - 31 * GetScale());

	// ������� ����� �������
	MoveToEx(hdc, m_X - 4.5 * GetScale(), m_Y - 12 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 12 * GetScale(), m_Y - 8 * GetScale());

	MoveToEx(hdc, m_X + 4.5 * GetScale(), m_Y - 12 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 12 * GetScale(), m_Y - 8 * GetScale());

	MoveToEx(hdc, m_X - 4.2 * GetScale(), m_Y - 5 * GetScale(), nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 12 * GetScale(), m_Y - 4 * GetScale());

	MoveToEx(hdc, m_X - 12 * GetScale(), m_Y - 8 * GetScale(), nullptr);      // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 12.3 * GetScale(), m_Y - 6 * GetScale());

	MoveToEx(hdc, m_X - 12.3 * GetScale(), m_Y - 6 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 12 * GetScale(), m_Y - 4 * GetScale());

	MoveToEx(hdc, m_X + 4.2 * GetScale(), m_Y - 5 * GetScale(), nullptr);     // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 12 * GetScale(), m_Y - 4 * GetScale());

	MoveToEx(hdc, m_X + 12 * GetScale(), m_Y - 8 * GetScale(), nullptr);      // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 12.4 * GetScale(), m_Y - 6 * GetScale());

	MoveToEx(hdc, m_X + 12.4 * GetScale(), m_Y - 6 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 12 * GetScale(), m_Y - 4 * GetScale());

	// ���������
	MoveToEx(hdc, m_X - 11.6 * GetScale(), m_Y - 8 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 12.6 * GetScale(), m_Y - 11 * GetScale());

	MoveToEx(hdc, m_X - 11.9 * GetScale(), m_Y - 4 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 12.6 * GetScale(), m_Y - 2 * GetScale());

	MoveToEx(hdc, m_X - 12.6 * GetScale(), m_Y - 2 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 13.5 * GetScale(), m_Y - 2 * GetScale());

	MoveToEx(hdc, m_X - 13.5 * GetScale(), m_Y - 2 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 14.5 * GetScale(), m_Y - 6 * GetScale());

	MoveToEx(hdc, m_X - 14.5 * GetScale(), m_Y - 6 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 14 * GetScale(), m_Y - 10.5 * GetScale());

	MoveToEx(hdc, m_X - 14 * GetScale(), m_Y - 10.5 * GetScale(), nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 13.5 * GetScale(), m_Y - 11.5 * GetScale());

	MoveToEx(hdc, m_X - 13.5 * GetScale(), m_Y - 11.5 * GetScale(), nullptr); // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 13 * GetScale(), m_Y - 11.5 * GetScale());

	MoveToEx(hdc, m_X - 12.6 * GetScale(), m_Y - 11 * GetScale(), nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X - 13 * GetScale(), m_Y - 11.5 * GetScale());

	MoveToEx(hdc, m_X + 11.7 * GetScale(), m_Y - 8.1 * GetScale(), nullptr);  // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 12.6 * GetScale(), m_Y - 11 * GetScale());

	MoveToEx(hdc, m_X + 11.9 * GetScale(), m_Y - 4 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 12.6 * GetScale(), m_Y - 2 * GetScale());

	MoveToEx(hdc, m_X + 12.6 * GetScale(), m_Y - 2 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 13.5 * GetScale(), m_Y - 2 * GetScale());

	MoveToEx(hdc, m_X + 12.6 * GetScale(), m_Y - 11 * GetScale(), nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 12.9 * GetScale(), m_Y - 11.5 * GetScale());

	MoveToEx(hdc, m_X + 13.5 * GetScale(), m_Y - 2 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 14.5 * GetScale(), m_Y - 6 * GetScale());

	MoveToEx(hdc, m_X + 14.5 * GetScale(), m_Y - 6 * GetScale(), nullptr);    // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 14 * GetScale(), m_Y - 10.5 * GetScale());

	MoveToEx(hdc, m_X + 14 * GetScale(), m_Y - 10.5 * GetScale(), nullptr);   // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 13.5 * GetScale(), m_Y - 11.5 * GetScale());

	MoveToEx(hdc, m_X + 13.5 * GetScale(), m_Y - 11.5 * GetScale(), nullptr); // ��������� ���������� �������� ������
	LineTo(hdc, m_X + 13 * GetScale(), m_Y - 11.5 * GetScale());
}

// ��������� ������ �������
void Infinity_Ship::cabin(HPEN Pen, HBRUSH Brush)
{
	Ellipse(hdc, m_X - 1.9 * m_scale, m_Y - 27 * m_scale, m_X + 2.5 * m_scale, m_Y - 15 * m_scale);

	Ellipse(hdc, m_X - 13.5 * m_scale, m_Y - 2 * m_scale, m_X - 12.5 * m_scale, m_Y - 1 * m_scale);

	Ellipse(hdc, m_X + 13.5 * m_scale, m_Y - 2 * m_scale, m_X + 12.5 * m_scale, m_Y - 1 * m_scale);
}

// �������� ����������� ������� �� ������. ����������� �����
void Infinity_Ship::Show()
{
	m_Visible = true;           // ����������� ������� �����
	// ������� ���, ������� � ���� ����
	HPEN PenPurple = CreatePen(PS_SOLID, 2, RGB(115, 102, 189));
	HPEN PenOrange = CreatePen(PS_SOLID, 2, RGB(195, 118, 41));
	HPEN PenBlue = CreatePen(PS_SOLID, 2, RGB(48, 213, 200));
	// ������� ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(48, 213, 200));
	// ������ ���� PenPurple ��������
	SelectObject(hdc, PenPurple);
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ��������� ������� ������������ ������� �������� ����� � ������
	body(PenPurple, Brush);
	SelectObject(hdc, PenBlue);
	cabin(PenPurple, Brush);
	SelectObject(hdc, PenOrange);
	engines(PenOrange, Brush);

	// ���������� ���������
	DeleteObject(PenBlue);       // ���������� ��������� ���� ������ ���� PenPurple
	DeleteObject(PenPurple);     // ���������� ��������� ���� ������ ���� PenPurple
	DeleteObject(PenOrange);     // ���������� ��������� ���� ������ ���� PenPurple
	DeleteObject(Brush);         // ���������� ��������� ���� ������ ����� Brush
}

// ������ ����������� ������� � ������. ����������� �����
void Infinity_Ship::Hide()
{
	m_Visible = false;           // ����������� ������� �� �����
	// ������� ���, ������� � ���� ����
	HPEN PenBlack = CreatePen(PS_SOLID, 2, RGB(12, 12, 12));
	// ������� ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ������ ���� PenBlack ��������
	SelectObject(hdc, PenBlack);
	// ��������� ������� ������� �������� ����� � ������
	body(PenBlack, Brush);
	cabin(PenBlack, Brush);
	SelectObject(hdc, PenBlack);
	engines(PenBlack, Brush);

	// ���������� ���������
	DeleteObject(PenBlack);      // ���������� ��������� ���� ������ ���� PenBlueLaguna
	DeleteObject(Brush);         // ���������� ��������� ���� ������ ����� Brush
}

// ������� ����� ����� ����� ������ ������������ �������
double Infinity_Ship::Left_Border()
{
	return (m_X - 14.7 * GetScale());
}

// ������� ����� ������ ����� ������ ������������ �������
double Infinity_Ship::Right_Border()
{
	return(m_X + 14.7 * GetScale());
}

// ������� ����� ������� ����� ������ ������������ �������
double Infinity_Ship::High_Border()
{
	return(m_Y + 1 * GetScale());
}

// ������� ����� ������ ����� ������ �������
double Infinity_Ship::Low_Border()
{
	return(m_Y - 36 * GetScale());
}




/*------------------------------------------------------------------------------------------------------*/
/*              ����            */
/*------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
/*        ����������� ������� �����       */
/*----------------------------------------*/

ABullet::ABullet(int Initcaliber)    // ����������� 
{
	m_caliber = Initcaliber;         // �������� ������� ����
}

ABullet::~ABullet()                  // ����������
{
	// ������ ����
}

int ABullet::GetCaliber() const      // ����������� ������ ��� ��������� �������� �������
{
	return (m_caliber);              // ������� �������� �������
}


/*------------------------------------------------------------------------------------------------------*/
/*              ������� ����           */
/*-------------------------------------*/

// ����������� ����� ���� �� Point � �� ����������� �� Location. � ABullet
// �����������
Bullet::Bullet(double InitX, double InitY) : Point(InitX, InitY), ABullet(10)
{
	m_scale = 0;                 // ��������� ���� ��������
}

// ����������
Bullet::~Bullet()
{
	// ������ ����
}

// �������� �������� ������ ����
int Bullet::GetScale()const
{
	return(m_scale);
}

// ���������� ������������� �������� ������ ����
void Bullet::SetScale(int NewScale)
{
	m_scale = NewScale;
}

// ��� �������������� ���������� �� ������������ �������� ������
// ������ ��� �������������� ��������� �������� �������
void Bullet::SetCaliber(int NewCaliber)
{
	m_caliber = NewCaliber;
}

// �������� ������� ���� �� ������. ����������� �����
void Bullet::Show()
{
	// ������� ���, ������� � ���� ����
	HPEN PenWhite = CreatePen(PS_SOLID, 5, RGB(255, 250, 250));
	// ������� ������� ������� ��� ���� � ������ ����� ������� - ���� �� �������� �� �������
	if (HighBorderBullet <= GetY() - GetCaliber())
	{
		m_Visible = true;              // ���� ����� �� ������
		// ������ ���� PenWhite ��������
		SelectObject(hdc, PenWhite);
		// ��������� ���������� �������� ������
		MoveToEx(hdc, m_X, m_Y, nullptr);
		// ��������� ��������� �������� ������
		LineTo(hdc, m_X, m_Y + 1 * m_caliber);
	}
	// ����� - ����� �� ������� �������. �������� ����
	else
	{
		Hide();
	}

	DeleteObject(PenWhite);            // ���������� ��������� ���� ������ ���� PenWhite
}

// ������ ���� � ������. ����������� �����
void Bullet::Hide()
{
	m_Visible = false;                  // ���� �� ����� �� ������
	// ������� ���, ������� � ���� ����
	HPEN PenBlack = CreatePen(PS_SOLID, 5, RGB(12, 12, 12));
	// ������ ���� PenBlack ��������
	SelectObject(hdc, PenBlack);
	// ��������� ���������� �������� ������
	MoveToEx(hdc, m_X, m_Y, nullptr);
	// ��������� ��������� �������� ������
	LineTo(hdc, m_X, m_Y + 1.5 * m_caliber);

	DeleteObject(PenBlack);             // ���������� ��������� ���� ������ ���� PenBlack
}


/*------------------------------------------------------------------------------------------------------*/
/*            ������  ����             */
/*-------------------------------------*/

// ����������� ����� ������ ���� �� ������� ���� � �� ����������� �� Point � Location. � ABullet
// ������. �������� ��� ��������� �������. �������� � ������������
// �����. �������� ��� �������. �������� � ������������
Yellow_Bullet::Yellow_Bullet(double InitX, double InitY) : Bullet(InitX, InitY)
{
	m_scale = 1;
	m_caliber = 30;
}

// ����������
Yellow_Bullet:: ~Yellow_Bullet()
{
	// ������ ����
}

// �������� ����� ���� �� ������. ����������� �����
void Yellow_Bullet::Show()
{
	// ������� ���, ������� � ���� ����
	HPEN PenYellow = CreatePen(PS_SOLID, 5, RGB(253, 233, 16));
	// ������� ������� ������� ��� ���� � ������ ����� ������� - ���� �� �������� �� �������
	if (HighBorderBullet <= GetY() - GetCaliber())
	{
		m_Visible = true;                // ���� ����� �� ������
		// ������ ���� PenYellow ��������
		SelectObject(hdc, PenYellow);
		// ��������� ���������� �������� ������
		MoveToEx(hdc, m_X, m_Y, nullptr);
		// ��������� ��������� �������� ������
		LineTo(hdc, m_X, m_Y + 1 * m_caliber);
	}
	// ����� - ����� �� ������� �������. �������� ����. �������� ����� � ������ ������ � �������������� ���� m_caliber �������� ������
	else
	{
		Hide();
	}

	DeleteObject(PenYellow);             // ���������� ��������� ���� ������ ���� PenYellow
}


/*------------------------------------------------------------------------------------------------------*/
/*            �������  ����            */
/*-------------------------------------*/

// ����������� ����� ������� ���� �� ������� ���� � �� ����������� �� Point � Location. � ABullet
// ���� m_caliber ������������ ������������. �������� � ������������
// �����. �������� ��� �������. �������� � ������������
Red_Bullet::Red_Bullet(double InitX, double InitY) : Bullet(InitX, InitY)
{
	acceleration = 15;
	m_scale = 2;
	m_caliber = 10;
	SetCaliber(acceleration + GetCaliber());
}

// ����������
Red_Bullet:: ~Red_Bullet()
{
	// ������ ����
};

// ����������� ������ ��� ��������� �������� ���������
int Red_Bullet::GetAcceleration() const
{
	return (acceleration);
}

// ������ ��� ��������� �������� ���������
void Red_Bullet::SetAcceleration(int NewAcceleration)
{
	acceleration = NewAcceleration;
}

// �������� ������� ���� �� ������. ����������� �����
void Red_Bullet::Show()
{
	// ������� ���, ������� � ���� ����
	HPEN PenRed = CreatePen(PS_SOLID, 5, RGB(255, 36, 0));
	// ������� ������� ������� ��� ���� � ������ ����� ������� - ���� �� �������� �� �������
	if (HighBorderBullet <= GetY() - GetCaliber())
	{
		m_Visible = true;                  // ���� ����� �� ������
		// ������ ���� PenRed ��������
		SelectObject(hdc, PenRed);
		// ��������� ���������� �������� ������
		MoveToEx(hdc, m_X, m_Y, nullptr);
		// ��������� ��������� �������� ������
		LineTo(hdc, m_X, m_Y + acceleration);
	}
	// ����� - ����� �� ������� �������. �������� ����. �������� ����� � ������ ������ � �������������� ���� m_caliber �������� ������
	else
	{
		Hide();
	}

	DeleteObject(PenRed);             // ���������� ��������� ���� ������ ���� PenRed
}


/*------------------------------------------------------------------------------------------------------*/
/*            ������  ����            */
/*-------------------------------------*/

// ����������� ����� ������ ���� �� ������� ���� � �� ����������� �� Point � Location. � ABullet
// ���� m_caliber ������������ ������������. �������� � ������������
// �����. �������� ��� �������. �������� � ������������
Green_Bullet::Green_Bullet(double InitX, double InitY) : Bullet(InitX, InitY)
{
	freeze = 0;
	m_scale = 3;
	m_caliber = 10;
}

// ����������
Green_Bullet:: ~Green_Bullet()
{
	// ������ ����
};

// ����������� ������ ��� �������� �������� ����������
int Green_Bullet::GetFreeze() const
{
	return (freeze);
}

// ������ ��� ������������� ��������� �������� �������� ����������
void Green_Bullet::Setfreeze(int NewFreeze)
{
	freeze = NewFreeze;
}

// �������� ������ ���� �� ������. ����������� �����
void Green_Bullet::Show()
{
	// ������� ���, ������� � ���� ����
	HPEN PenMalahit = CreatePen(PS_SOLID, 5, RGB(52, 201, 36));
	// ������� ������� ������� ��� ���� � ������ ����� ������� - ���� �� �������� �� ������� � ���������� ����� ���� <=15
	if ((HighBorderBullet <= GetY() - GetCaliber()) && (freeze <= 15))
	{
		freeze = freeze + 1;        // ��������� ������� �����
		m_Visible = true;           // ������ ���� ����� �� ������
		// ������ ���� PenMalahit ��������
		SelectObject(hdc, PenMalahit);
		// ��������� ���������� �������� ������
		MoveToEx(hdc, m_X, m_Y, nullptr);
		// ��������� ��������� �������� ������
		LineTo(hdc, m_X, m_Y + 1.5 * m_caliber);
	}
	// ����� - ����� �� ������� ������� ��� ������� ������ ���������� ����� ��� ���������. �������� ����. �������� ����� � ������ ������ � �������������� ���� m_caliber �������� ������
	else
	{
		Hide();
		freeze = 0;                 // �������� ������� �����
	}

	DeleteObject(PenMalahit);       // ���������� ��������� ���� ������ ���� PenRed
}


/*------------------------------------------------------------------------------------------------------*/
/*            �����  ����            */
/*-----------------------------------*/

// ����������� ����� ����� ���� ��  ������ ���� �� � �� ����������� �� ������� ���� � Point � Location
// �����������
// ������������ ���� ��������
Blue_Bullet::Blue_Bullet(double InitX, double InitY) : Green_Bullet(InitX, InitY)
{
	freeze = 0;
	m_scale = 4;
	m_caliber = 10;
}

// ����������
Blue_Bullet::~Blue_Bullet()
{
	// ������ ����
}

// ����������� �������
void Blue_Bullet::Show()            // �������� ����� ���� �� ������. ����������� �����
{
	// ������� ���, ������� � ���� ����
	HPEN PenEgg = CreatePen(PS_SOLID, 5, RGB(0, 204, 204));
	// ������� ������� ������� ��� ���� � ������ ����� ������� - ���� �� �������� �� ������� � ���������� ����� ���� <=20
	if ((HighBorderBullet <= GetY() - GetCaliber()) && (freeze <= 10))
	{
		freeze = freeze + 1;        // ��������� ������� �����
		m_Visible = true;           // ����� ���� ����� �� ������
		// ������ ���� PenEgg ��������
		SelectObject(hdc, PenEgg);
		// ��������� ���������� �������� ������
		MoveToEx(hdc, m_X, m_Y, nullptr);
		// ��������� ��������� �������� ������
		LineTo(hdc, m_X, m_Y + 1 * m_caliber);
	}
	// ����� - ����� �� ������� ������� ��� ������� ������ ���������� ����� ��� ���������. �������� ����. �������� ����� � ������ ������ � �������������� ���� m_caliber �������� ������
	else
	{
		Hide();
		freeze = 0;                 // �������� ������� �����
	}

	DeleteObject(PenEgg);           // ���������� ��������� ���� ������ ���� PenEgg
}




/*------------------------------------------------------------------------------------------------------*/
/*              �����           */
/*------------------------------*/

/*------------------------------------------------------------------------*/
/*        ����������� ������� �����       */
/*----------------------------------------*/

// ����������� � ��������� �������� ������� � ���������
ABomb::ABomb(double InitRadius, int InitExtraSpeed)
{
	m_radius = InitRadius;                             // ���������� �������� �������
	extra_speed = InitExtraSpeed;                      // ���������� �������� ���������
}

// ����������
ABomb::	~ABomb()                                       
{
	// ������ ����
}

// ����������� ������ ��� ��������� �������� �������
double ABomb::GetRadius() const
{
	return(m_radius);
}

// ����������� ������ ��� ��������� �������� ���������
int ABomb::GetExtra_speed() const
{
	// ������� �������� ���������
	return(extra_speed);
}

// ������ ��� �������������� ��������� �������� ���������
void ABomb::SetExtra_speed(int NewSpeed) 
{
	extra_speed = NewSpeed;
}


/*------------------------------------------------------------------------*/
/*              ������� �����          */
/*-------------------------------------*/

// ����������� ����� ����� �� Point � �� ����������� �� Location. � ABomb
// ������ ����� - �������� ��� ���������
// ��������� - �������� ��� �������� �����
// ����������� �������� ����� ������������ �������
Bomb::Bomb(int InitX, int InitY, int InitNumb, int InitRadius, int InitExtraSpeed) : Point(InitX, InitY), ABomb(InitRadius, InitExtraSpeed)
{
	m_numb = InitNumb;                    // ���������� �������� ������ �����
}

// ����������
Bomb::~Bomb()                                                  
{
	// ������ ����
}

// ������ ��� �������������� ��������� �������� �������. ���������� ��� ������������ �������� ������
void Bomb::SetRadius(double NewRadius)                            
{
	// ���������� �������� �������
	m_radius = NewRadius;
}

// ����������� ������ ��� ��������� �������� ������
int Bomb::GetNumb()const
{
	// ������� �������� ������ �����
	return(m_numb);
}

// ������ ��� �������������� ��������� �������� ������
void Bomb::SetNumb(int NewNumb)                                
{
	m_numb = NewNumb;
}

// �������� ������� ����� �� ������. ����������� �����
void Bomb::Show()                                           
{
	// ������� ���, ������� � ���� ����
	HPEN PenWhite = CreatePen(PS_SOLID, 4, RGB(234, 230, 202));
	// ������� ���, ������� � ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(234, 230, 202));

	// �� ����� �� ������� ������� � ������ �������
	if (HighBorderBullet <= GetY() - 3 * GetRadius())
	{
		m_Visible = true;                 // ����� ����� �� ������
		// ������ ���� PenWhite ��������
		SelectObject(hdc, PenWhite);
		// ������ ����� Brush ��������
		SelectObject(hdc, Brush);
		// ��������� �����
		Ellipse(hdc, m_X - 1.5 * m_radius, m_Y - 2.2 * m_radius, m_X - 0.6 * m_radius, m_Y - 3.1 * m_radius);
	}

	// ����� - ����� �� ������� �������. �������� �����
	else
	{
		Hide();
	}

	DeleteObject(Brush);                  // ���������� ��������� ���� ������ ����� Brush
	DeleteObject(PenWhite);               // ���������� ��������� ���� ������ ���� PenWhite
}

// ������ ������� ����� � ������. ����������� �����
void Bomb::Hide()
{
	m_Visible = false;                    // ����� �� ����� �� ������

	// ��������� ��� �� ����� ������ �������
	// ������� ���, ������� � ���� ����
	HPEN PenBlack = CreatePen(PS_SOLID, 4, RGB(12, 12, 12));
	// ������� ���, ������� � ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));

	// ������ ���� PenBlack ��������
	SelectObject(hdc, PenBlack);
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ��������� �����
	Ellipse(hdc, m_X - 1.5 * m_radius, m_Y - 2.2 * m_radius, m_X - 0.6 * m_radius, m_Y - 3.1 * m_radius);
	
	DeleteObject(Brush);                  // ���������� ��������� ���� ������ ����� Brush 
	DeleteObject(PenBlack); 			  // ���������� ��������� ���� ������ ���� PenWhite
}


/*------------------------------------------------------------------------------------------------------*/
/*            �������  �����           */
/*-------------------------------------*/

// ����������� ����� ������� ����� �� ������� ����� � �� ����������� �� Point � Location. � ABomb 
// ������� �� ������: ������� ���������
// ����������� � ��������� ���������� �� ���������
Red_Bomb::Red_Bomb(int InitX, int InitY, int InitNumb, int InitRadius) : Bomb(InitX, InitY, InitNumb, InitRadius)
{
	extra_speed = 3;                      // ���������� �������� ���������
}

// ����������
Red_Bomb:: ~Red_Bomb()                                              
{
	// ������ ����
}

// �������� ������� ����� �� ������. ����������� �����
void Red_Bomb::Show()
{
	// ������� ���, ������� � ���� ����
	HPEN PenRed = CreatePen(PS_SOLID, 4, RGB(196, 30, 58));
	// ������� ���, ������� � ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(196, 30, 58));

	// �� ����� �� ������� ������� � ������ �������
	if (HighBorderBullet <= GetY() - 3 * GetRadius())
	{
		m_Visible = true;                 // ������� ����� ����� �� ������
		// ������ ���� PenRed ��������
		SelectObject(hdc, PenRed);
	    // ������ ����� Brush ��������
		SelectObject(hdc, Brush);
		// ��������� ������� �����
		Ellipse(hdc, m_X - 1.5 * m_radius, m_Y - 2.2 * m_radius, m_X - 0.6 * m_radius, m_Y - 3.1 * m_radius);
	}

	// ����� - ����� �� ������� �������. �������� ������� �����
	else
	{
		Hide();                           // ������������ ����� Hide, �.�. ������� ���� ����������
	}

	DeleteObject(Brush);                  // ���������� ��������� ���� ������ ����� Brush 
	DeleteObject(PenRed);				  // ���������� ��������� ���� ������ ���� PenRed
}


/*------------------------------------------------------------------------------------------------------*/
/*          ����������  �����          */
/*-------------------------------------*/

// ����������� ����� ���������� ����� �� ������� ����� � �� ����������� �� Point � Location. � ABomb 
// ����������� � ��������� ���������� �� ��������� � ����� ������������ �������������
Purple_Bomb::Purple_Bomb(int InitX, int InitY, int InitNumb, int InitRadius) : Bomb(InitX, InitY, InitNumb, InitRadius)
{
	extra_speed = 0;                      // ��������� ���
}

// ����������
Purple_Bomb::~Purple_Bomb()                                              
{
	// ������ ����
}

// �������� ���������� ����� �� ������. ����������� �����
void Purple_Bomb::Show()
{
	// ������� ���, ������� � ���� ����
	HPEN PenPurple = CreatePen(PS_SOLID, 4, RGB(244, 0, 161));
	// ������� ���, ������� � ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(196, 30, 58));

	// �� ����� �� ������� ������� � ������ �������
	if (HighBorderBullet <= GetY() - 3 * GetRadius())
	{
		m_Visible = true;                 // ���������� ����� ����� �� ������
		// ������ ���� PenPurple ��������
		SelectObject(hdc, PenPurple);
		// ������ ����� Brush ��������
		SelectObject(hdc, Brush);
		// ��������� ���������� �����
		Ellipse(hdc, m_X - 0.3 * m_radius, m_Y - 1.9 * m_radius, m_X - 1.5 * m_radius, m_Y - 3 * m_radius);
	}

	// ����� - ����� �� ������� �������. �������� ���������� �����
	else
	{
		Hide();
	}

	DeleteObject(Brush);                  // ���������� ��������� ���� ������ ����� Brush
	DeleteObject(PenPurple);              // ���������� ��������� ���� ������ ���� PenPurple
}

// ������ ���������� ����� � ������. ����������� �����
void Purple_Bomb::Hide()
{
	m_Visible = false;                    // ���������� ����� �� ����� �� ������
	
	// ��������� ��� �� ����� ������ �������
	// ������� ���, ������� � ���� ����
	HPEN PenBlack = CreatePen(PS_SOLID, 4, RGB(12, 12, 12));
	// ������� ���, ������� � ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));

	// ������ ���� PenBlack ��������
	SelectObject(hdc, PenBlack);
	// ������ ����� Brush ��������
	SelectObject(hdc, Brush);
	// ��������� �����
	Ellipse(hdc, m_X - 0.3 * m_radius, m_Y - 1.9 * m_radius, m_X - 1.5 * m_radius, m_Y - 3 * m_radius);

	DeleteObject(Brush);                  // ���������� ��������� ���� ������ ����� Brush 
	DeleteObject(PenBlack);				  // ���������� ��������� ���� ������ ���� PenRed
}


/*------------------------------------------------------------------------------------------------------*/
/*            ������  �����           */
/*-------------------------------------*/

// ����������� ����� ������� ����� �� ������� ����� � �� ����������� �� Point � Location. � ABomb 
// ����������� � ��������� ���������� �� ���������. ����� ������������� ������������
Green_Bomb::Green_Bomb(int InitX, int InitY, int InitNumb, int InitRadius) : Bomb(InitX, InitY, InitNumb, InitRadius)
{
	extra_speed = 0;                      // ��������� ���
	step = 0;                             // ��������� ������ �����. ����� ����� �� �� ����� �������, � ����������� ���������
}

// ����������
Green_Bomb::~Green_Bomb()
{
	// ������ ����
}

// ����������� ������ ��� �������� �������� ����������
int Green_Bomb::GetStep() const
{
	// ������� �������� ����������
	return(step);
}

// ������ ��� �������������� ��������� �������� �������� ����������
void  Green_Bomb::SetStep(int NewStep)
{
	step = NewStep;
}

// �������� ������ ����� �� ������. ����������� �����
void Green_Bomb::Show()
{
	// ������� ���, ������� � ���� ����
	HPEN PenGreen = CreatePen(PS_SOLID, 4, RGB(0, 255, 127));
	// ������� ���, ������� � ���� �����
	HBRUSH Brush = CreateSolidBrush(RGB(0, 255, 127));

	// ������� ������� ������� ��� ����� � ������ ������� - ����� �� �������� �� ������� � ���������� ����� ����� <=30
	if ((HighBorderBullet <= GetY() - 3 * GetRadius()) && (step <= 30))
	{
		step = step + 1;                  // ��������� ������� �����
		m_Visible = true;                 // ����� ����� �� ������

		// ������ ���� PenGreen ��������
		SelectObject(hdc, PenGreen);
		// ������ ����� Brush ��������
		SelectObject(hdc, Brush);
		// ��������� ������ �����
		Ellipse(hdc, m_X - 1.5 * m_radius, m_Y - 2.2 * m_radius, m_X - 0.6 * m_radius, m_Y - 3.1 * m_radius);
	}

	// ����� - ����� �� ������� ������� ��� ������� ������ ���������� ����� ��� ���������. �������� �����. �������� ����� � ������ ������
	else
	{
		Hide();                           // �������� �����
		step = 0;                         // �������� ������� �����
	}

	DeleteObject(PenGreen);               // ���������� ��������� ���� ������ ���� PenGreen
	DeleteObject(Brush);                  // ���������� ��������� ���� ������ ����� Brush
}