/***************************************************************************
 *      � � � � � � � � � � � �   � � � � � �   � 2   � �   � � � �        *
 *-------------------------------------------------------------------------*
 *                                                                         *
 * Project Name  : Fly_Plate                                               *
 * Project Type  : Win64 Console application                               *
 * File Name     : Secondary_functions.h                                   *
 * Language      : VS2022                         C++                      *
 * Programmers   : ������� �. �.  &&  �������� �. �  &&  ����� �. �.       *
 * Modified By   :                                                         *
 * Created       : 01 / 11 / 2023                                          *
 * Last Revision : 16 / 11 / 2023                                          *
 * Comment(s)    : ������� �������������� ����� ����� ������������         *
 *                 �����������. ������������ ������� ���������.            *
 *                 ����������� ������. ����������.                         *
 **************************************************************************/

#include "Asteroid_co.h"           // ���������� ������������ ���� � ��������
#include "Constants.h"             // ���������� ���� � ����������� ���������� ��������

/*******************************************************************/
/*              � � � � � � � � �    � � � � � � �                 */
/*******************************************************************/


// �������� ����� ���� �� �������� �������
bool Hit_FlyingPlate_Bullets(Bullet* CurBullet              // ��������� �������� ������ �������� �������
	                       , FlyingPlate* CurPlate);        // ��������� �������� ������ ���������

// �������� ����� ����� �� �������� �������
bool Hit_FlyingPlate_Bombs(Bomb* CurBomb                    // ��������� �������� ������ ����
	                     , FlyingPlate* CurPlate);          // ��������� �������� ������ �������� �������

// �������� ����� ����� �� ��������
bool Hit_Asteroids_Bombs(Bomb* CurBomb                      // ��������� �������� ������ ����
	                   , Asteroid* CurAsteroid);            // ��������� �������� ������ ���������

// �������� ����� ������� �� �������� �������
bool HitShip_Plate(Ship* CurShip                            // ��������� �������� ������ �������
	             , FlyingPlate* CurPlate                    // ��������� �������� ������ �������� �������
	             , int& schet);                             // ������� ����� ��������� �� ������ ��� ���������

// �������� ����� ���� �� ��������
bool HitBullet(Bullet* CurBullet                            // ��������� �������� ������ ����
             , Asteroid** CurAsteroid                       // ��������� �� ��������� �������� ������ ���������, ����� ����� ���������� � ���� ��������, � ������� ��������� ���� �����
             , Asteroid** Asteroids);                       // ������ ���������� ��� �������� ����� � ������ �� ����������

// �������� ����� ������� �� ��������
bool HitShip(Ship* CurShip                                  // ��������� �������� ������ �������
           , Asteroid** CurAsteroid                         // ��������� �� ��������� �������� ������ ���������, ����� ����� ���������� � ���� ��������, ������� ����� �����������
           , Asteroid** Asteroids);                         // ������ ���������� ��� �������� ����� � ������ �� ����������

// ����� �������� �������
void changeFlyingPlate(FlyingPlate** CurPlate               // ��������� �� ��������� �������� ������ �������� �������
	                 , FlyingPlate** Plates                 // ��������� �� ������ ������� ������� ���������� �� ������� ������ Plates � ��� �����������
	                 , Bomb* CurBomb                        // ��������� �������� ������ �����
	                 , int transition_matr_Flying_Plate[][CountBombs]  // ������� �������� �������� �������
	                 , int& schet);                         // ������� ����� ��������� �� ������ ��� ���������

// ����� ���������
void changeAsteroid(Asteroid** CurAsteroid                  // ��������� �� ��������� �������� ������ ���������
                  , Bullet* CurBullet                       // ��������� �������� ������ ����
                  , Asteroid** Asteroids                    // ��������� �� ������ ������� ������� ���������� �� ������� ������ Asteroid � ��� �����������
                  , int transition_matr[][CountBullets]     // ������� �������� ����������
                  , int dead_matr[][CountBullets]);         // ������� ������� ����������. ��� ��������� ��������� �� ����� ����� ����� ������� ����� ���������

// ����� �������
void changeShip(Ship** CurShip                              // ��������� �� ��������� �������� ������ ������� ��� ��������� �������� ���������
              , Asteroid* CurAsteroid                       // ��������� �������� ������ ��������
              , Ship** Ships                                // ��������� �� ������ ������� ������� ���������� �� ������� ������ Ship � ��� �����������
              , int ship_matr[][CountMeteor]);              // ������� ��������� �������

// ��������� ��������� �� ����� ����� ����� ���� ��� �� ������ ����� �������
void RespavnAsteroid(Asteroid* CurAsteroid);                // ��������� �������� ������ ���������

// ����� �������� ������ ���������� �� �����
void Count(int schet);                                      // ��������� �������� ������ ���������

//������� "�����"
void WriteEnd();