#pragma once
/***************************************************************************
 *      � � � � � � � � � � � �   � � � � � �   � 2   � �   � � � �        *
 *-------------------------------------------------------------------------*
 *                                                                         *
 * Project Name  : Fly_Plate                                               *
 * Project Type  : Win64 Console application                               *
 * File Name     : Asteroid_co.h                                           *
 * Language      : VS2022                         C++                      *
 * Programmers   : ������� �. �.                                           *
 * Modified By   :                                                         *
 * Created       : 01 / 11 / 2023                                          *
 * Last Revision : 16 / 11 / 2023                                          *
 * Comment(s)    : ������� �������������� ����� ����� ������������         *
 *                 �����������. ������������ ������� ���������.            *
 *                 ����������� ������. ����������.                         *
 **************************************************************************/
#include "constants.h"
extern HDC hdc;


/*------------------------------------------------------------------------*/
/*                 Location               */
/*----------------------------------------*/

// ������� ����� ��������������
class Location
{
protected:
	double m_X;                             // ���������� X
	double m_Y;                             // ���������� Y
public:
	Location(double InitX, double InitY);   // �����������
	~Location();                            // ����������
	double GetX() const;                    // ����������� ������ ��� ��������� X
	double GetY() const;                    // ����������� ������ ��� ��������� Y
	void SetX(double NewX);                 // ������ ��� ��������� X
	void SetY(double NewY);                 // ������ ��� ��������� Y
};// Location


/*------------------------------------------------------------------------*/
/*                Point                   */
/*----------------------------------------*/

// ����������� ����� ����� �� Location
class Point : public Location
{
protected:
	bool m_Visible;                         // ���������� �����
public:
	Point(double InitX, double InitY);      // �����������
	~Point();                               // ����������
	bool IsVisible() const;                 // ������ ��� ���������� �����
	void SetVisible(bool NewVisible);       // ������������� ���������� ���������� �����
	void MoveTo(double NewX, double NewY);  // �������� ������
	virtual void Show();                    // �������� ����� �� ������
	virtual void Hide();                    // ������ ����� � ������
};// Point




/*---------------------------------------------------------------------------------------------------------------------*/
/*            ���������           */
/*--------------------------------*/

/*------------------------------------------------------------------------*/
/*               Interface                */
/*----------------------------------------*/

// ����� �������� ��� ���� �������� ����������, �� ������ ����������. ���-�� ������������, � ���-�� - ���
// ������� ���������� ������ ���� ������������� �����������
class IAsteroid
{
	virtual void Body(HPEN Pen) = 0;                    // ��������� �������� ���������
	virtual void Craters(HPEN Pen) = 0;                 // ��������� �������� ���������
	virtual void Galo(HPEN Pen, HBRUSH Brush) = 0;      // ��������� ������������ ����� ������ Body
	virtual void Bumps(HPEN Pen) = 0;                   // ��������� �������
	virtual void Core(HPEN Pen, HBRUSH Brush) = 0;      // ��������� ����
	virtual void Stripes(HPEN Pen, HBRUSH Brush) = 0;   // ��������� �������
	virtual void Nimbus(HPEN Pen, HBRUSH Brush) = 0;    // ��������� �����
	virtual void Rays(HPEN Pen) = 0;                    // ��������� �����
};// IAsteroid


/*------------------------------------------------------------------------*/
/*                Asteroid                */
/*----------------------------------------*/

// ����������� ����� �������� �� ���������� IAsteroid, �� Point � �� ����������� �� Location
// ������ ���������� ������ ���� ������������� �����������
// ����� ���������������� ������� � ���� ������ ����� ����� ������ ����
class Asteroid : public Point, public IAsteroid
{
protected:
	double m_size;                          // �������� ��� ��������� � ����������� �������
	int m_number;                           // ������ ����� ���������
public:
	Asteroid(double InitX, double InitY);   // ����������� ���������
	~Asteroid();                            // ����������
	double GetSize() const;                 // ������ ��� ��������� �������� �������
	void SetSize(double NewSize);           // ������ ��� �������������� ��������� �������� �������
	int GetNumber() const;                  // ������ ��� ��������� �������� ������
	void SetNumber(int NewNumber);          // ������ ��� �������������� ��������� �������� ������

	// ����������� ������� ��� ������������� ������������
	// ���������� ����������
	void Body(HPEN Pen);                    // ��������� �������� ���������
	void Craters(HPEN Pen);                 // ��������� �������� ���������
	void Galo(HPEN Pen, HBRUSH Brush) {}    // ��������� ������������ ����� ������ Body. ����� �� �����
	void Bumps(HPEN Pen) {}                 // ��������� �������. ����� �� �����
	void Core(HPEN Pen, HBRUSH Brush) {}    // ��������� ����. ����� �� �����
	void Stripes(HPEN Pen, HBRUSH Brush) {} // ��������� �������. ����� �� �����
	void Nimbus(HPEN Pen, HBRUSH Brush) {}  // ��������� �����. ����� �� �����
	void Rays(HPEN Pen) {}                  // ��������� �����. ����� �� �����

	// ����������� �������
	// ������ ���������� � �������� � ������ ����. ���������� ����������
	void Show();                            // �������� �������� �� ������. ����������� �����
	void Hide();                            // ������ �������� � ������. ����������� �����

	virtual double Left_Border();           // ������� �������� ����� ����� ����� ���������/ ������ �������/ ������ ��������� �������/ ����������� �������
	virtual double Right_Border();          // ������� �������� ����� ������ ����� ���������/ ������ �������/ ������ ��������� �������/ ����������� �������
	virtual double High_Border();           // ������� �������� ����� ������� ����� ���������/ ������ �������/ ������ ��������� �������/ ����������� �������
	virtual double Low_Border();            // ������� �������� ����� ������ ����� ���������/ ������ �������/ ������ ��������� �������/ ����������� �������
};// Asteroid


// ��� ��������� ������ ���������� ������� �������� ����� ������ ���������
/*------------------------------------------------------------------------*/
/*              White_Warlic              */
/*----------------------------------------*/

// ����������� ����� ����� ������ �� Asteroid � �� ����������� �� Point � Location. � IAsteroid
class White_Warlic : public Asteroid
{
	// ������. �������� ��� ��������� ������� ������������ �����������. �������� � ������������
	// ����� �������� � ������������
public:
	White_Warlic(double InitX, double InitY);          // �����������
	~White_Warlic();                                   // ����������

	// ����������� ������� �� ����������
	void Galo(HPEN Pen, HBRUSH Brush);                 // ��������� ������������ ����� ������ Body
	// ������ ��������� ������ ������������ �� ������ Asteroid

	// ����������� �������
	void Show();                                       // �������� ������ ������� �� ������. ����������� �����
	void Hide();                                       // ������ ������ ������� � ������. ����������� �����
};// White_Warlic


/*------------------------------------------------------------------------*/
/*            Cold_White_Warlic           */
/*----------------------------------------*/

// ����������� ����� �������� ����� ������ �� ������ ������� � �� ����������� �� Asteroid, Point � Location. � IAsteroid. ������������ ������������
class Cold_White_Warlic : public White_Warlic
{
	// ������. �������� ��� ��������� �������. �������� � ������������
	// ����� �������� � ������������
public:
	Cold_White_Warlic(double InitX, double InitY);     // �����������
	~Cold_White_Warlic();                              // ����������

	// ����������� ������� �� ����������
	void Bumps(HPEN Pen);                              // ��������� �������
	void Core(HPEN Pen, HBRUSH Brush);                 // ��������� ����

	// ����������� �������
	void Show();                                       // �������� ��������� ������ ������� �� ������. ����������� �����
	void Hide();                                       // ������ ��������� ������ ������� � ������. ����������� �����
};// Cold_White_Warlic


/*------------------------------------------------------------------------*/
/*            Brown_Warlic           */
/*-----------------------------------*/

// ����������� ����� ���������� ������ �� Asteroid � �� ������������ �� Point � Location. � IAsteroid.
class Brown_Warlic : public Asteroid
{
	// ������. �������� ��� ��������� �������. �������� � ������������
	// ����� �������� � ������������
public:
	Brown_Warlic(double InitX, double InitY);    // �����������
	~Brown_Warlic();                             // ����������

	// ����������� ������� �� ����������
	void Stripes(HPEN Pen, HBRUSH Brush);        // ��������� �������

	// ����������� �������
	void Show();                                 // �������� ����������� ������� �� ������. ����������� �����
	void Hide();                                 // ������ ����������� ������� � ������. ����������� �����
};// Brown_Warlic


// ��� ���� ������ ���������� ������� ��� ����� �������
/*------------------------------------------------------------------------*/
/*            Neutron_Star           */
/*-----------------------------------*/

// ����������� ����� ���������� ������ �� Asteroid � �� ������������ �� Point � Location. � IAsteroid.
class Neutron_Star : public Asteroid
{
	// ������. �������� ��� ��������� �������. �������� � ������������
	// ����� �������� � ������������
public:
	Neutron_Star(double InitX, double InitY);       // �����������
	~Neutron_Star();                                // ����������

	// ����������� ������� �� ����������
	void Nimbus(HPEN Pen, HBRUSH Brush);            // ��������� �����
	void Rays(HPEN Pen);                            // ��������� �����

	// ����������� �������
	void Show();                                    // �������� ���������� ������ �� ������. ����������� �����
	void Hide();                                    // ������ ���������� ������ � ������. ����������� �����

	// ����������� �������
	double Left_Border();                           // ������� �������� ����� ����� ����� ���������� ������   / ������ ������. ����������� �����
	double Right_Border();                          // ������� �������� ����� ������ ����� ���������� ������  / ������ ������. ����������� �����
	double High_Border();                           // ������� �������� ����� ������� ����� ���������� ������ / ������ ������. ����������� �����
	double Low_Border();                            // ������� �������� ����� ������ ����� ���������� ������  / ������ ������. ����������� �����
};// Neutron_Star


/*------------------------------------------------------------------------*/
/*            Dead_Star           */
/*--------------------------------*/

// ����������� ����� ������� ������ �� Neutron_Star  � �� ������������ �� Asteroid, Point � Location. � IAsteroid.
class Dead_Star : public Neutron_Star
{
	// ������. �������� ��� ��������� �������. �������� � ������������
	// ����� �������� � ������������
public:
	Dead_Star(double InitX, double InitY);          // �����������
	~Dead_Star();                                   // ����������

	// ����������� ������� �� ����������
	void Core(HPEN Pen, HBRUSH Brush);              // ��������� �������� ����
	void Bumps(HPEN Pen);                           // ��������� �������

	// ����������� �������
	void Show();                                    // �������� ������� ������ �� ������. ����������� �����
	void Hide();                                    // ������ ������� ������ � ������. ����������� �����
};// Dead_Star




/*------------------------------------------------------------------------------------------------------*/
/*            �������� �������         */
/*-------------------------------------*/

/*------------------------------------------------------------------------*/
/*               Interface                */
/*----------------------------------------*/

// ����� �������� ��� ���� �������� �������� �������, �� ������ ����������. ���-�� ������������, � ���-�� - ���
// ������ ���������� ������ ���� ������������� �����������
class IFlyingPlate
{
	virtual void Skirt(HPEN Pen) = 0;                    // ��������� ������ "���� �������"
	virtual void Glass(HPEN Pen) = 0;                    // ��������� ������ �������� �������
	virtual void Windows(HPEN Pen, HBRUSH Brush) = 0;    // ��������� ���� ������ ���� �������� �������
	virtual void Legs(HPEN Pen) = 0;                     // ��������� �����/������� ���� �������� �������
	virtual void Back(HPEN Pen) = 0;                     // ��������� ���������� ���������� �������� �������            
};// IFlyingPlate


/*------------------------------------------------------------------------------------------------------*/
/*           FlyingPlate         */
/*-------------------------------*/

// ����������� ����� ��������_������� �� ���������� IFlyingPlate, �� Point � �� ����������� �� Location
// ������ ���������� ������ ���� ������������� �����������
// ����� ���������������� ������� � ���� ������ ����� ����� ������ ����
class FlyingPlate : public Point, public IFlyingPlate
{
protected:
	double m_parametr;                                    // �������� ��� ��������� � ����������� �������
	int m_num_plate;                                      // ������ ����� �������� �������
public:
	FlyingPlate(int InitX, int InitY);                    // ����������� �������� �������
	~FlyingPlate();                                       // ����������
	double GetParametr() const;                           // ����������� ������ ��� ��������� �������� �������
	void SetParameter(int NewParametr);                   // ������ ��� �������������� ��������� �������� �������
	int GetNum() const;                                   // ����������� ������ ��� ��������� �������� ������
	void SetNum(int NewNum);                              // ������ ��� �������������� ��������� �������� ������� ������

	// ����������� ������� ��� ������������� ������������
	//���������� ����������
	void Skirt(HPEN Pen);                                 // ��������� ������ "���� �������"
	void Glass(HPEN Pen);                                 // ��������� ������ �������� �������
	void Windows(HPEN Pen, HBRUSH Brush);                 // ��������� ���� ������ ���� �������� �������
	void Legs(HPEN Pen);                                  // ��������� �����/������� ���� �������� �������
	void Back(HPEN Pen) {};                               // ��������� ���������� ���������� �������� �������. ����� �� �����
	// ����������� �������
	void Show();                                          // �������� �������� ������� �� ������. ����������� �����
	void Hide();                                          // ������ �������� ������� � ������. ����������� �����
	virtual int Left_Border();                            // ������� �������� ����� ����� ����� �������� �������/   �������� �������� �������
	virtual int Right_Border();                           // ������� �������� ����� ������ ����� �������� �������/  �������� �������� �������
	virtual int Low_Border();                             // ������� �������� ����� ������ ����� �������� �������/  �������� �������� �������
	virtual int High_Border();                            // ������� �������� ����� ������� ����� �������� �������/ �������� �������� �������
};// FlyingPlate


/*------------------------------------------------------------------------------------------------------*/
/*         Broke_FlyingPlate           */
/*-------------------------------------*/

// ����������� ����� �������� ��������_������� �� FlyingPlate � �� ����������� �� Point � Location. � IFlyingPlate
class Broke_FlyingPlate : public FlyingPlate
{
protected:
	// ������. �������� ��� ��������� �������. ������������ ���� ��������. �������� � ������������
	// �����. ��������-����. ������������ ���� ��������. �������� � ������������
public:
	Broke_FlyingPlate(int InitX, int InitY);     // �����������
	~Broke_FlyingPlate();                        // ����������
	void Glass(HPEN Pen);                        // ��������� ���������� ������ ��������� �������� �������
	void Show();                                 // �������� ��������� �������� ������� �� ������. ����������� �����
	void Hide();                                 // ������ ��������� �������� ������� � ������. ����������� �����
};// Broke_FlyingPlate


/*------------------------------------------------------------------------------------------------------*/
/*        Angry_FlyingPlate           */
/*------------------------------------*/

// ����������� ����� ���� ��������_������� �� FlyingPlate � �� ����������� �� Point � Location. � IFlyingPlate
class Angry_FlyingPlate : public FlyingPlate
{
protected:
	// ������. �������� ��� ��������� �������. ������������ ���� ��������. �������� � ������������
	// �����. ��������-����. ������������ ���� ��������. �������� � ������������
public:
	Angry_FlyingPlate(int InitX, int InitY);         // �����������
	~Angry_FlyingPlate();                            // ����������
	void Skirt(HPEN Pen);                            // ��������� ������ "���� �������" ���� �������� �������
	void Glass(HPEN Pen);                            // ��������� ������ ���� �������� �������
	void Windows(HPEN Pen, HBRUSH Brush);            // ��������� ���� ������ ���� ���� �������� �������
	void Legs(HPEN Pen);                             // ��������� �����/������� ���� ���� �������� �������
	void Show();                                     // �������� ���� �������� ������� �� ������. ����������� �����
	void Hide();                                     // ������ ���� �������� ������� � ������. ����������� �����

	int Left_Border();                               // ������� �������� ����� ����� ����� ���� �������� �������
	int Right_Border();                              // ������� �������� ����� ������ ����� ���� �������� �������
	int Low_Border();                                // ������� �������� ����� ������ ����� ���� �������� �������
	int High_Border();                               // ������� �������� ����� ����� ����� ���� �������� �������
};// Angry_FlyingPlate


/*------------------------------------------------------------------------------------------------------*/
/*             Modify_FlyingPlate             */
/*--------------------------------------------*/

// ����������� ����� ���������������� ��������_������� �� Angry_FlyingPlate � �� ����������� �� FlyingPlate � Point � Location. � IFlyingPlate
class Modify_FlyingPlate : public Angry_FlyingPlate
{
protected:
	// ������. �������� ��� ��������� �������. ������������ ���� �����������. �������� � ������������
	// �����. ��������-����. ������������ ���� �����������. �������� � ������������
public:
	Modify_FlyingPlate(int InitX, int InitY);        // �����������
	~Modify_FlyingPlate();                           // ����������
	void Skirt(HPEN Pen);                            // ��������� ������ "���� �������" ���������������� �������� �������
	void Back(HPEN Pen);                             // ��������� ���������� ���������� ���������������� �������� �������
	void Windows(HPEN Pen, HBRUSH Brush);            // ��������� ���� ������ ���� ���������������� �������� �������
	void Show();                                     // �������� ���������������� �������� ������� �� ������. ����������� �����
	void Hide();                                     // ������ ���������������� �������� ������� � ������. ����������� �����

	int Left_Border();                               // ������� �������� ����� ����� ����� ���������������� �������� �������
	int Right_Border();                              // ������� �������� ����� ������ ����� ���������������� �������� �������
	int Low_Border();                                // ������� �������� ����� ������ ����� ���������������� �������� �������
	int High_Border();                               // ������� �������� ����� ����� ����� ���������������� �������� �������
};// Modify_FlyingPlate




/*-----------------------------------------------------------------------------------------------------------------------*/
/*             �������          */
/*------------------------------*/

/*------------------------------------------------------------------------*/
/*               Interface                */
/*----------------------------------------*/

// ����� ��������. ������ ����������. � ����� ������� ������ �����, � � ������ - ���
// ������ ���������� ������ ���� ������������� �����������
class IShip
{
	virtual void engines(HPEN Pen, HBRUSH Brush) = 0;   // ��������� ����������
	virtual void body(HPEN Pen, HBRUSH Brush) = 0;      // ��������� ������� �������
	virtual void cabin(HPEN Pen, HBRUSH Brush) = 0;     // ��������� ������ �������
};// IShip


/*------------------------------------------------------------------------*/
/*              Ship                */
/*----------------------------------*/

// ����������� ����� ������� �� Point � �� ����������� �� Location. ����������� �� ���������� IShip
class Ship : public Point, public IShip
{
protected:
	double m_scale;                       // ������. �������� ��� ��������� �������
	int s_number;                         // �����. �������� ��� ������� ��������� ��������
public:
	Ship(double InitX, double InitY);     // �����������
	~Ship();                              // ����������
	double GetScale() const;              // ������ ��� ��������� �������� �������
	void SetScale(double NewScale);       // ������ ��� �������������� ��������� �������� �������
	int GetSNumber() const;               // ����������� ������ ��� ��������� �������� ������ �������
	void SetSNumber(int NewSNumber);      // ������ ��� �������������� ��������� �������� �������� ������ �������
	void engines(HPEN Pen, HBRUSH Brush); // ��������� ����������
	void body(HPEN Pen, HBRUSH Brush);    // ��������� ������� �������
	void cabin(HPEN Pen, HBRUSH Brush);   // ��������� ������ �������

	// ����������� �������
	void Show();                          // �������� ������� �� ������. ����������� �����
	void Hide();                          // ������ ������� � ������. ����������� �����

	virtual double Left_Border();         // ������� ����� ����� ����� ������ �������/ ���������� �������
	virtual double Right_Border();        // ������� ����� ������ ����� ������ �������/ ���������� �������
	virtual double High_Border();         // ������� ����� ������� ����� ������ �������/ ���������� �������
	virtual double Low_Border();          // ������� ����� ������ ����� ������ �������/ ���������� �������
};// Ship


/*------------------------------------------------------------------------*/
/*              Broke_Ship                */
/*----------------------------------------*/

// ����������� ����� ��������� ������� ��  Ship � �� ����������� �� Point � Location. ����������� �� ���������� IShip
class Broke_Ship : public Ship
{
protected:
	// ������. �������� ��� ��������� �������. �������� � ������������
	// �����. �������� ��� ������� ��������� ��������. �������� � ������������
public:
	Broke_Ship(double InitX, double InitY);      // �����������.
	~Broke_Ship();                               // ����������
	void engines(HPEN Pen, HBRUSH Brush);        // ��������� ������ ���������
	void Show();                                 // �������� ��������� ������� �� ������. ����������� �����
	void Hide();                                 // ������ ��������� ������� � ������. ����������� �����
};// Broke_Ship


/*------------------------------------------------------------------------*/
/*             Infinity_Ship              */
/*----------------------------------------*/

// ����������� ����� ����������� ������� ��  Ship � �� ����������� �� Point � Location. ����������� �� ���������� IShip
class Infinity_Ship : public Ship
{
protected:
	// ������. �������� ��� ��������� �������. �������� � ������������
	// �����. �������� ��� ������� ��������� ��������. �������� � ������������
public:
	Infinity_Ship(double InitX, double InitY);   // �����������
	~Infinity_Ship();                            // ����������
	void engines(HPEN Pen, HBRUSH Brush);        // ��������� ����������
	void body(HPEN Pen, HBRUSH Brush);           // ��������� ������� �������
	void cabin(HPEN Pen, HBRUSH Brush);          // ��������� ������ �������

	// ����������� �������
	void Show();                                 // �������� ����������� ������� �� ������. ����������� �����
	void Hide();                                 // ������ ����������� ������� � ������. ����������� �����

	double Left_Border();         // ������� ����� ����� ����� ������ ������������ �������
	double Right_Border();        // ������� ����� ������ ����� ������ ������������ �������
	double High_Border();         // ������� ����� ������� ����� ������ ������������ �������
	double Low_Border();          // ������� ����� ������ ����� ������ ������������ �������
};// Infinity_Ship




/*------------------------------------------------------------------------------------------------------*/
/*              ����            */
/*------------------------------*/

/*------------------------------------------------------------------------*/
/*        ����������� ������� �����       */
/*----------------------------------------*/

class ABullet
{
protected:
	int m_caliber;                               // ������ ����
public:
	ABullet(int Initcaliber);                    // ����������� � ��������� �������� �������
	virtual ~ABullet();                          // ����������� ����������. ��� ������������ �����������, ��� �������� ������������������� ������ ����� ��������� �� ������� �����, ���������� ������������ ������ �� ����� ������
	int GetCaliber() const;                      // ������ ��� ��������� �������� �������

	// ������ ����������� �������
	virtual void SetCaliber(int NewCaliber) = 0; // ������ ��� �������������� ��������� �������� �������
};// ABullet


/*------------------------------------------------------------------------*/
/*              ������� ����           */
/*-------------------------------------*/

// ����������� ����� ���� �� Point � �� ����������� �� Location. � ABullet
class Bullet : public Point, public ABullet
{
protected:
	// ������ ���� - �������� ��� ���������
	int m_scale;                                  // ��������� ����
public:
	Bullet(double InitX, double InitY);           // �����������
	~Bullet();                                    // ����������

	int GetScale() const;                         // ����������� ������ ��� ��������� �������� ������
	void SetScale(int NewScale);                  // ������ ��� �������������� ��������� �������� ������

	// ��� �������������� ���������� �� ������������ �������� ������
	void SetCaliber(int NewCaliber);              // ������ ��� �������������� ��������� �������� �������

	// ����������� �������
	void Show();                                  // �������� ������� ���� �� ������. ����������� �����
	void Hide();                                  // ������ ������� ���� � ������. ����������� �����
};// Bullet


/*------------------------------------------------------------------------------------------------------*/
/*            ������  ����             */
/*-------------------------------------*/

// ����������� ����� ������ ���� �� ������� ���� � �� ����������� �� Point � Location. � ABullet
class Yellow_Bullet : public Bullet
{
	// ������. �������� ��� ��������� �������. �������� � ������������
	// �����. �������� ��� �������. �������� � ������������
public:
	Yellow_Bullet(double InitX, double InitY);    // �����������
	~Yellow_Bullet();                             // ����������

	// ����������� �������
	void Show();                                  // �������� ����� ���� �� ������. ����������� �����
	// ��������������� ������ Hide() ���. ������������ ������������ ����������
};// Yellow_Bullet


/*------------------------------------------------------------------------------------------------------*/
/*            �������  ����            */
/*-------------------------------------*/

// ����������� ����� ������� ���� �� ������� ���� � �� ����������� �� Point � Location. � ABullet
class Red_Bullet : public Bullet
{
protected:
	int acceleration;                              // ���������
	// ���� m_caliber ������������ ������������. �������� � ������������
	// �����. �������� ��� �������. �������� � ������������
public:
	Red_Bullet(double InitX, double InitY);        // �����������
	~Red_Bullet();                                 // ����������
	int GetAcceleration() const;                   // ����������� ������ ��� ��������� �������� ���������
	void SetAcceleration(int NewAcceleration);     // ������ ��� ��������� �������� ���������

	// ����������� �������
	void Show();                                   // �������� ������� ���� �� ������. ����������� �����
	// ��������������� ������ Hide() ���. ������������ ������������ ����������
};// Red_Bullet


/*------------------------------------------------------------------------------------------------------*/
/*            ������  ����            */
/*-------------------------------------*/

// ������������� �������� - ���������� ����� ��������� �����
// ����������� ����� ������ ���� �� ������� ���� � �� ����������� �� Point � Location. � ABullet
class Green_Bullet : public Bullet
{
protected:
	int freeze;                                 // ��������� ����. ���� ����� �� �� ����� �������, � ����������� ���������
	// ���� m_caliber ������������ ������������. �������� � ������������
	// �����. �������� ��� �������. �������� � ������������
public:
	Green_Bullet(double InitX, double InitY);   // �����������
	~Green_Bullet();                            // ����������
	int GetFreeze() const;                      // ����������� ������ ��� �������� �������� ����������
	void Setfreeze(int NewFreeze);              // ������ ��� �������������� ��������� �������� �������� ����������

	// ����������� �������
	void Show();                                // �������� ������ ���� �� ������. ����������� �����
};// Green_Bullet


/*------------------------------------------------------------------------------------------------------*/
/*            �����  ����            */
/*-----------------------------------*/

// ���������� ��� ������� ����������� ����� �� ������������
// ����������� ����� ����� ���� �� ������� ���� � �� ����������� �� ������� ����, Point � Location. � ABullet
class Blue_Bullet : public Green_Bullet
{
	// ���� m_caliber ������������ �����������. �������� � ������������
	// �����. �������� ��� �������. �������� � ������������
public:
	Blue_Bullet(double InitX, double InitY);   // �����������
	~Blue_Bullet();                            // ����������

	// ����������� �������
	void Show();                               // �������� ����� ���� �� ������. ����������� �����
};// Blue_Bullet




/*------------------------------------------------------------------------------------------------------*/
/*              �����           */
/*------------------------------*/

/*------------------------------------------------------------------------*/
/*        ����������� ������� �����       */
/*----------------------------------------*/

class ABomb
{
protected:
	double m_radius;                               // ������ �����
	int extra_speed;                               // ���������
public:
	ABomb(double InitRadius, int InitExtraSpeed);  // ����������� � ��������� �������� ������� � ���������
	~ABomb();                                      // ����������
	double GetRadius() const;                      // ����������� ������ ��� ��������� �������� �������
	int GetExtra_speed() const;                    // ����������� ������ ��� ��������� �������� ���������
	void SetExtra_speed(int NewSpeed);             // ������ ��� �������������� ��������� �������� ���������
	virtual void SetRadius(double NewRadius) = 0;  // ������ ��� �������������� ��������� �������� �������

};// ABomb


/*------------------------------------------------------------------------*/
/*              ������� �����          */
/*-------------------------------------*/

// ����������� ����� ����� �� Point � �� ����������� �� Location. � ABomb
class Bomb : public Point, public ABomb
{
protected: 
	// ������ ����� - �������� ��� ���������
	// ��������� - �������� ��� �������� �����
	int m_numb;                                    // ��������� ����
public:
	// ����������� � ��������� �������� ������, �������, ��������� �� ���������
	Bomb(int InitX, int InitY, int InitNumb = 0, int InitRadius = 9, int ExtraSpeed = 0);
	~Bomb();                                       // ����������
	void SetRadius(double NewRadius);              // ������ ��� �������������� ��������� �������� �������
	int GetNumb() const;                           // ����������� ������ ��� ��������� �������� ������
	void SetNumb(int NewNumb);                     // ������ ��� �������������� ��������� �������� ������
	
	// ����������� ������� 
	void Show();                                   // �������� ������� ����� �� ������. ����������� �����
	void Hide();                                   // ������ ������� ����� � ������. ����������� �����
};// Bomb


/*------------------------------------------------------------------------------------------------------*/
/*            �������  �����           */
/*-------------------------------------*/

// ����������� ����� ������� ����� �� ������� ����� � �� ����������� �� Point � Location. � ABomb 
// ������� �� ������: ������� ���������
class Red_Bomb : public Bomb
{
	// ������ ����� - �������� ��� ���������
    // ��������� - �������� ��� �������� �����
	// ��������� ���� ������ ���� ��������

public:
	// ����������� � ��������� �������� ������, ������� �� ���������. ��������� ��������������� � ������������
	Red_Bomb(int InitX, int InitY, int InitNumb = 1, int InitRadius = 9);
	~Red_Bomb();                                   // ����������
	
	// ����������� �������
	void Show();                                   // �������� ������� ����� �� ������. ����������� �����
	// ������ ������� ����� � ������. ����� ������ � ��������, �.�. ��������� ������� ����������
};// Red_Bullet


/*------------------------------------------------------------------------------------------------------*/
/*          ����������  �����          */
/*-------------------------------------*/

// ����������� ����� ���������� ����� �� ������� ����� � �� ����������� �� Point � Location. � ABomb 
class Purple_Bomb : public Bomb
{
	// ������ ����� - �������� ��� ���������
    // ��������� - �������� ��� �������� �����
    // ��������� ���� ������ ���� ��������

public:
	// ����������� � ��������� �������� ������,������� �� ���������. ��������� ��������������� � ������������
	Purple_Bomb(int InitX, int InitY, int InitNumb = 2, int InitRadius = 12);
	~Purple_Bomb();                                // ����������
	
	// ����������� �������
	void Show();                                   // �������� ���������� ����� �� ������. ����������� �����
	void Hide();                                   // ������ ���������� ����� � ������. ����������� �����
};// Purple_Bomb


/*------------------------------------------------------------------------------------------------------*/
/*            ������  �����           */
/*-------------------------------------*/

// ����������� ����� ������� ����� �� ������� ����� � �� ����������� �� Point � Location. � ABomb 
class Green_Bomb : public Bomb
{
protected:
	// ������ ����� - �������� ��� ���������
    // ��������� - �������� ��� �������� �����
    // ��������� ���� ������ ���� ��������
	int step;                                      // ��������� ������ �����. ����� ����� �� �� ����� �������, � ����������� ���������
	
public:
	// ����������� � ��������� �������� ������, ������� �� ���������. ��������� � ��������� �������� ����� �� ��������� ��������������� � ������������
	Green_Bomb(int InitX, int InitY, int InitNumb = 3, int InitRadius = 9);
	~Green_Bomb();                                 // ����������
	int GetStep() const;                           // ����������� ������ ��� �������� �������� ����������
	void SetStep(int NewStep);                     // ������ ��� �������������� ��������� �������� �������� ����������
	
	// ����������� �������
	void Show();                                   // �������� ������ ����� �� ������. ����������� �����
	// ������ ������� ����� � ������. ����� ������ � ��������, �.�. ��������� ������� ����������
};// Green_Bomb