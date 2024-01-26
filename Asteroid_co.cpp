/***************************************************************************
 *      Л А Б О Р А Т О Р Н А Я   Р А Б О Т А   № 2   П О   Т Р П О        *
 *-------------------------------------------------------------------------*
 *                                                                         *
 * Project Name  : Fly_Plate                                               *
 * Project Type  : Win64 Console application                               *
 * File Name     : Asteroid_co.cpp                                         *
 * Language      : VS2022                         C++                      *
 * Programmers   : Викулов Д. Г.                                           *
 * Modified By   :                                                         *
 * Created       : 01 / 11 / 2023                                          *
 * Last Revision : 16 / 11 / 2023                                          *
 * Comment(s)    : Игровое взаимодействие фигур через динамический         *
 *                 полиморфизм. Наследование Матрица переходов.            *
 *                 Абстрактные классы. Интерфейсы.                         *
 **************************************************************************/

#include "Asteroid_co.h"	// подключаем файл с объявлением классов
HDC hdc;                    // объявим  контекст устройства

/*----------------------------------------------------------------*/
/*             Р Е А Л И З А Ц И Я    М Е Т О Д О В               */
/*----------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*                 Location               */
/*----------------------------------------*/

// базовый класс МЕСТОПОЛОЖЕНИЕ
// конструктор
Location::Location(double InitX, double InitY)
{
	m_X = InitX;           // присваиваем полям значения
	m_Y = InitY;
}

// деструктор
Location:: ~Location()
{
	//пустое тело
}

// константный геттер для получения X
double Location::GetX() const
{
	return (m_X);          // вернуть значение поля x
}

// константный геттер для получения Y
double Location::GetY() const
{
	return (m_Y);          // вернуть значение поля y
}

// сеттер для получения X
void Location::SetX(double NewX)
{
	m_X = NewX;            // установить полю x передаваемое значение
}

// сеттер для получения Y
void Location::SetY(double NewY)
{
	m_Y = NewY;            // установить полю y передаваемое значение
}


/*------------------------------------------------------------------------*/
/*                Point                   */
/*----------------------------------------*/

// производный класс ТОЧКА от Location
// конструктор
Point::Point(double InitX, double InitY) : Location(InitX, InitY) // для инициализации старых полей используем конструктор предка
{
	m_Visible = false;      // присваиваем новым полям значения
}

// деструктор
Point:: ~Point()
{
	// пустое тело
}

// узнать про светимость точки
bool Point::IsVisible() const
{
	return (m_Visible);     // вернуть значение светимости точки
}

// принудительно установить светимость точки
void Point::SetVisible(bool NewVisible)
{
	m_Visible = NewVisible; // установить полю переданное значение
}

// переместить фигуру по новым координатам. Виртуальный метод
void Point::MoveTo(double NewX, double NewY)
{
	Hide();                 // прячем фигуру по старым координатам
	m_X = NewX;             // устанавливаем новое значение координаты Х
	m_Y = NewY;             // устанавливаем новое значение координаты Y
	Show();                 // показываем фигуру по новым координатам
}

// показать точку на экране
void Point::Show()
{
	m_Visible = true;                                 // точка видна
	SetPixel(hdc, m_X, m_Y, RGB(178, 87, 84));        // рисуем квадрат из 4-х соседних пикселей. Отрисовываем точку серым цветом
	SetPixel(hdc, m_X + 1, m_Y, RGB(178, 87, 84));
	SetPixel(hdc, m_X, m_Y + 1, RGB(178, 87, 84));
	SetPixel(hdc, m_X + 1, m_Y + 1, RGB(178, 87, 84));
}

// скрыть точку с экрана. Виртуальный метод
void Point::Hide()
{
	m_Visible = false;                                // точку не видно
	SetPixel(hdc, m_X, m_Y, RGB(12, 12, 12));         // рисуем квадрат из 4-х соседних пикселей цветом консоли
	SetPixel(hdc, m_X + 1, m_Y, RGB(12, 12, 12));
	SetPixel(hdc, m_X, m_Y + 1, RGB(12, 12, 12));
	SetPixel(hdc, m_X + 1, m_Y + 1, RGB(12, 12, 12));
}




/*---------------------------------------------------------------------------------------------------------------------*/
/*            Астероиды           */
/*--------------------------------*/

/*------------------------------------------------------------------------*/
/*                Asteroid                */
/*----------------------------------------*/

// производный класс АСТЕРОИД от интерфейса IAsteroid, от Point и по определению от Location
// фунции интерфейса должны быть принудительно реализованы
// тогда неиспользующиеся функции в этом классе будут иметь пустое тело
Asteroid::Asteroid(double InitX, double InitY) : Point(InitX, InitY)   // для инициализации старых полей используем конструктор предка
{
	m_size = 15;             // параметр для отрисовки и регулировки размера
	m_number = -1;           // номер астероида
}

// деструктор
Asteroid:: ~Asteroid()
{
	// пустое тело
}

// геттер для получения значения размера
double Asteroid::GetSize() const
{
	return (m_size);         // вернуть значение размера астероида
}

// сеттер для принудительной установки значения размера
void Asteroid::SetSize(double NewSize)
{
	m_size = NewSize;        // установить полю новое переданное значение
}

// геттер для получения значения номера
int Asteroid::GetNumber() const
{
	return (m_number);       // вернуть значение номера астероида
}

// сеттер для принудительной установки значения номера
void Asteroid::SetNumber(int NewNumber)
{
	m_number = NewNumber;    // установить полю новое переданное значение
}

// отрисовка контуров астероида переданным пером
void Asteroid::Body(HPEN Pen)
{
	MoveToEx(hdc, m_X, m_Y, nullptr);                        // установка начального значения прямой
	LineTo(hdc, m_X - 2.5 * m_size, m_Y + 0.5 * m_size);     // установка конечного значения прямой

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
	LineTo(hdc, m_X, m_Y);                                         // вернулись в начальную точку рисования
}

// отрисовка кратеров астероида переданным цветом
void Asteroid::Craters(HPEN Pen)
{
	// рисуем кратеры по точкам
	// самый нижний кратер
	{
		MoveToEx(hdc, m_X - 1 * m_size, m_Y - 0 * m_size, nullptr);  // установка начального значения прямой
		LineTo(hdc, m_X - 2.5 * m_size, m_Y - 0.1 * m_size);         // установка конечного значения прямой

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

	// западный кратер
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

	// северо-западный кратер
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

	//юго-восток
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

	//юго-восток западнее
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

	//северо-восток
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

// показать астероид на экране. Виртуальный метод
void Asteroid::Show()
{
	m_Visible = true;                         // астероид виден
	// зададим тип, толщину и цвет пера
	HPEN PenGreyPurple = CreatePen(PS_SOLID, 2, RGB(136, 112, 107));
	// делаем перо PenGreyPurple  активным
	SelectObject(hdc, PenGreyPurple);
	HBRUSH Brush = CreateSolidBrush(RGB(240, 248, 255));
	// рисуем контур и кратеры астероида заданным цветом
	Galo(PenGreyPurple, Brush);               // отрисовка закрашенного круга внутри Body
	Bumps(PenGreyPurple);                     // отрисовка полосок
	Core(PenGreyPurple, Brush);               // отрисовка ядра
	Stripes(PenGreyPurple, Brush);            // отрисовка полосок
	Nimbus(PenGreyPurple, Brush);             // отрисовка нимба
	Rays(PenGreyPurple);                      // отрисовка лучей
	Body(PenGreyPurple);                      // отрисовка тела
	Craters(PenGreyPurple);                   // отрисовка кратеров

	DeleteObject(PenGreyPurple);              // уничтожим созданные нами объекты PenGreyPurple
	DeleteObject(Brush);                      // уничтожим кисть Brush
}

// скрыть астероид с экрана. Виртуальный метод
void Asteroid::Hide()
{
	m_Visible = false;                        // астероид невиден
	// зададим тип, толщину и цвет пера
	HPEN PenBlack = CreatePen(PS_SOLID, 2, RGB(12, 12, 12));
	// делаем перо PenBlack  активным
	SelectObject(hdc, PenBlack);
	// рисуем контур и кратеры астероида черным цветом
	Body(PenBlack);
	Craters(PenBlack);

	DeleteObject(PenBlack);                   // уничтожим созданные нами объекты PenBlack
}

// вернуть значение самой левой точки астероида/ белого карлика/ белого остывшего карлика/ коричневого карлика
double Asteroid::Left_Border()
{
	return (GetX() - 6.5 * GetSize());
}

// вернуть значение самой правой точки астероида/ белого карлика/ белого остывшего карлика/ коричневого карлика
double Asteroid::Right_Border()
{
	return (GetX() + 3.1 * GetSize());
}

// вернуть значение самой высокой точки астероида/ белого карлика/ белого остывшего карлика/ коричневого карлика
double Asteroid::High_Border()
{
	return (GetY() + 0.46 * GetSize());
}

// вернуть значение самой низкой точки астероида/ белого карлика/ белого остывшего карлика/ коричневого карлика
double Asteroid::Low_Border()
{
	return (GetY() - 9.1 * GetSize());
}


// для следующей группы астероидов функции возврата точек границ одинаковы
/*------------------------------------------------------------------------*/
/*               White_Warlic             */
/*----------------------------------------*/

// производный класс БЕЛЫЙ КАРЛИК от Asteroid и по определению от Point и Location. И IAsteroid
White_Warlic::White_Warlic(double InitX, double InitY) : Asteroid(InitX, InitY) // для инициализации старых полей используем конструктор предка
{
	m_number = 0;                  // номер астероида
	m_size = 16;                   // параметр для отрисовки
}

// деструктор
White_Warlic:: ~White_Warlic()
{
	// пустое тело
}

// отрисовка закрашенного круга внутри Body заданным цветом
void White_Warlic::Galo(HPEN Pen, HBRUSH Brush)
{
	Ellipse(hdc, m_X - 6 * m_size, m_Y + 0 * m_size, m_X + 2.7 * m_size, m_Y - 8.5 * m_size);
}

// показать Белого карлика на экране. Виртуальный метод
void White_Warlic::Show()
{
	m_Visible = true;              // белый карлик виден
	// зададим тип, толщину и цвет пера
	HPEN PenSlivki = CreatePen(PS_SOLID, 3, RGB(255, 248, 231));
	// зададим тип, толщину и цвет пера
	HPEN PenBlue = CreatePen(PS_SOLID, 2, RGB(21, 23, 25));
	// зададим цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(240, 248, 255));
	// делаем кисть  Brush активной
	SelectObject(hdc, Brush);
	// делаем перо PenSlivki активным
	SelectObject(hdc, PenSlivki);
	// рисуем тело и круг заданным цветом и кистью
	Body(PenSlivki);
	Galo(PenSlivki, Brush);
	// делаем перо PenBlue активным
	SelectObject(hdc, PenBlue);
	// рисуем кратеры заданным цветом
	Craters(PenBlue);

	DeleteObject(PenSlivki);            // уничтожаем созданный нами объект пера PenSlivki
	DeleteObject(PenBlue);              // уничтожаем созданный нами объект пера PenBlue
	DeleteObject(Brush);                // уничтожаем созданный нами объект кисти Brush
}

// скрыть белого карлика с экрана. Виртуальный метод
void White_Warlic::Hide()
{
	m_Visible = false;                  // белый карлик невиден
	// зададим тип, толщину и цвет пера
	HPEN PenBlack = CreatePen(PS_SOLID, 3, RGB(12, 12, 12));
	// зададим цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// делаем перо PenBlack активным
	SelectObject(hdc, PenBlack);
	// отрисовываем тело, круг и кратеры черным пером и кистью
	Body(PenBlack);                     // метод предка
	Galo(PenBlack, Brush);              // метод предка
	Craters(PenBlack);                  // метод предка

	DeleteObject(PenBlack);             // уничтожаем созданный нами объект пера PenBlack
	DeleteObject(Brush);                // уничтожаем созданный нами объект кисти Brush
}


/*------------------------------------------------------------------------*/
/*            Cold_White_Warlic           */
/*----------------------------------------*/

// производный класс ОСТЫВШИЙ БЕЛЫЙ КАРЛИК от Белого карлика и по определению от Asteroid, Point и Location. И IAsteroid. Вертикальное наследование
// для инициализации старых полей используем конструктор предка
Cold_White_Warlic::Cold_White_Warlic(double InitX, double InitY) : White_Warlic(InitX, InitY)
{
	m_number = 1;		// номер астероида
	m_size = 11;		// параметр для отрисовки
}

// деструктор
Cold_White_Warlic:: ~Cold_White_Warlic()
{
	// пустое тело
};

// отрисовка линий-молний внутри переданным пером
void Cold_White_Warlic::Bumps(HPEN Pen)
{
	MoveToEx(hdc, m_X - 0.6 * m_size, m_Y - 4 * m_size, nullptr);         // установка начального значения прямой
	LineTo(hdc, m_X + 1.3 * m_size, m_Y - 4.5 * m_size);               // установка конечного значения прямой
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

// отрисовка ядра переданными пером и кистью
void Cold_White_Warlic::Core(HPEN Pen, HBRUSH Brush)
{
	// круг
	Ellipse(hdc, m_X - 2.5 * m_size, m_Y - 3 * m_size, m_X - 0.5 * m_size, m_Y - 5 * m_size);
}

// показать остывшего белого карлика на экране. Виртуальный метод
void Cold_White_Warlic::Show()
{
	m_Visible = true;                      // остывший белый карлик виден
	// зададим тип, толщину и цвет перьев
	HPEN PenGrey = CreatePen(PS_SOLID, 3, RGB(35, 26, 36));
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 250, 240));
	HPEN PenBlue = CreatePen(PS_SOLID, 3, RGB(0, 0, 128));
	HPEN PenBlack = CreatePen(PS_SOLID, 3, RGB(12, 12, 12));
	// зададим цвет кистей
	HBRUSH Brush = CreateSolidBrush(RGB(35, 26, 36));
	HBRUSH BrushWhite = CreateSolidBrush(RGB(255, 250, 240));
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// делаем перо PenGrey активным
	SelectObject(hdc, PenGrey);
	// отрисовываем закрашенный круг методом родителя переданным цветом
	Galo(PenGrey, Brush);
	// делаем кисть BrushWhite активной
	SelectObject(hdc, BrushWhite);
	// отрисовываем ядро переданным цветом
	Core(PenGrey, BrushWhite);
	// делаем перо PenWhite активным
	SelectObject(hdc, PenWhite);
	// отрисовываем молнии заданным цветом
	Bumps(PenWhite);
	// делаем перо PenBlue активным
	SelectObject(hdc, PenBlue);
	// отрисовываем свечение методом прародителя переданным цветом
	Body(PenBlue);
	// делаем перо PenBlack активным
	SelectObject(hdc, PenBlack);
	// отрисовываем кратеры методом прародителя переданным цветом
	Craters(PenBlack);

	DeleteObject(PenBlack);             // уничтожаем созданный нами объект пера PenBlack
	DeleteObject(PenWhite);             // уничтожаем созданный нами объект пера PenWhite
	DeleteObject(PenBlue);              // уничтожаем созданный нами объект пера PenBlue
	DeleteObject(PenGrey);              // уничтожаем созданный нами объект пера PenGrey
	DeleteObject(Brush);                // уничтожаем созданный нами объект кисти Brush
	DeleteObject(BrushWhite);           // уничтожаем созданный нами объект кисти BrushWhite
}

// скрыть остывшего белого карлика с экрана. Виртуальный метод
void Cold_White_Warlic::Hide()
{
	m_Visible = false;                  // остывший белый карлик невиден
	// зададим тип, толщину и цвет пера
	HPEN PenBlack = CreatePen(PS_SOLID, 3, RGB(12, 12, 12));
	// зададим цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// делаем перо PenBlack активным
	SelectObject(hdc, PenBlack);
	// отрисовываем закрашенный круг методом родителя переданным цветом
	Galo(PenBlack, Brush);
	// отрисовываем ядро переданным цветом
	Core(PenBlack, Brush);
	// отрисовываем молнии переданным цветом
	Bumps(PenBlack);
	// отрисовываем свечение методом прародителя переданным цветом
	Body(PenBlack);
	// отрисовываем кратеры методом прародителя переданным цветом
	Craters(PenBlack);

	DeleteObject(PenBlack);             // уничтожаем созданный нами объект пера PenBlack
	DeleteObject(Brush);                // уничтожаем созданный нами объект кисти Brush
}


/*------------------------------------------------------------------------*/
/*            Brown_Warlic           */
/*-----------------------------------*/

// производный класс Коричневый карлик от Asteroid и по отпределению от Point и Location
Brown_Warlic::Brown_Warlic(double InitX, double InitY) : Asteroid(InitX, InitY) // для инициализации старых полей используем конструктор предка
{
	m_number = 2;					  // номер астероида
	m_size = 13;					  // параметр для отрисовки
}

// деструктор
Brown_Warlic:: ~Brown_Warlic()
{
	// пустое тело
}

// отрисовка полосок переданным пером
void Brown_Warlic::Stripes(HPEN Pen, HBRUSH Brush)
{
	// нижний эллипс
	Ellipse(hdc, m_X - 5 * m_size, m_Y + 0.5 * m_size, m_X + 2 * m_size, m_Y - 2 * m_size);
	// верхний эллипс
	Ellipse(hdc, m_X - 4.5 * m_size, m_Y - 7 * m_size, m_X + 1.5 * m_size, m_Y - 9.1 * m_size);

	MoveToEx(hdc, m_X - 6.2 * m_size, m_Y - 2.5 * m_size, nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X - 4 * m_size, m_Y - 2.4 * m_size);                  // установка конечного значения прямой

	MoveToEx(hdc, m_X - 4 * m_size, m_Y - 2.4 * m_size, nullptr);       // установка начального значения прямой
	LineTo(hdc, m_X - 2 * m_size, m_Y - 2.4 * m_size);                  // установка конечного значения прямой

	MoveToEx(hdc, m_X - 2 * m_size, m_Y - 2.4 * m_size, nullptr);       // установка начального значения прямой
	LineTo(hdc, m_X - 0 * m_size, m_Y - 2.5 * m_size);                  // установка конечного значения прямой

	MoveToEx(hdc, m_X - 0 * m_size, m_Y - 2.5 * m_size, nullptr);       // установка начального значения прямой
	LineTo(hdc, m_X + 2.8 * m_size, m_Y - 2.7 * m_size);                // установка конечного значения прямой

	MoveToEx(hdc, m_X - 6.2 * m_size, m_Y - 6 * m_size, nullptr);       // установка начального значения прямой
	LineTo(hdc, m_X - 4 * m_size, m_Y - 5.9 * m_size);                  // установка конечного значения прямой

	MoveToEx(hdc, m_X - 4 * m_size, m_Y - 5.9 * m_size, nullptr);       // установка начального значения прямой
	LineTo(hdc, m_X - 2 * m_size, m_Y - 5.9 * m_size);                  // установка конечного значения прямой

	MoveToEx(hdc, m_X - 2 * m_size, m_Y - 5.9 * m_size, nullptr);       // установка начального значения прямой
	LineTo(hdc, m_X - 0 * m_size, m_Y - 6 * m_size);                    // установка конечного значения прямой

	MoveToEx(hdc, m_X - 0 * m_size, m_Y - 6 * m_size, nullptr);         // установка начального значения прямой
	LineTo(hdc, m_X + 2.8 * m_size, m_Y - 6.2 * m_size);                // установка конечного значения прямой
}

// показать коричневого карлика на экране. Виртуальный метод
void Brown_Warlic::Show()
{
	m_Visible = true;                    // коричневый карлик виден
	// зададим тип, толщину и цвет пера
	HPEN PenRedOrange = CreatePen(PS_SOLID, 3, RGB(169, 29, 17));
	// зададим тип, толщину и цвет пера
	HPEN PenDeepRed = CreatePen(PS_SOLID, 2, RGB(123, 0, 28));
	// зададим цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(243, 71, 35));
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// делаем перо PenRedOrange активным
	SelectObject(hdc, PenRedOrange);
	// рисуем контур коричневого карлика методом родителя заданным цветом
	Body(PenRedOrange);
	// рисуем полоски коричневого карлика заданным цветом
	Stripes(PenRedOrange, Brush);
	// делаем перо PenDeepRed активным
	SelectObject(hdc, PenDeepRed);
	// рисуем кратеры коричневого карлика методом родителя заданным цветом
	Craters(PenDeepRed);

	DeleteObject(PenDeepRed);            // уничтожаем созданный нами объект пера PenDeepRed
	DeleteObject(PenRedOrange);          // уничтожаем созданный нами объект пера PenRedOrange
	DeleteObject(Brush);                 // уничтожаем созданный нами объект кисти Brush
}

// скрыть коричневого карлика с экрана. Виртуальный метод
void Brown_Warlic::Hide()
{
	m_Visible = false;                   // коричневый карлик невиден
	// зададим тип, толщину и цвет пера
	HPEN PenBlack = CreatePen(PS_SOLID, 3, RGB(12, 12, 12));
	// зададим цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// делаем перо PenGrey активным
	SelectObject(hdc, PenBlack);
	// рисуем контур коричневого карлика методом родителя заданным цветом
	Body(PenBlack);
	// рисуем полоски коричневого карлика заданным цветом
	Stripes(PenBlack, Brush);
	// рисуем кратеры коричневого карлика методом родителя заданным цветом
	Craters(PenBlack);
	DeleteObject(PenBlack);             // уничтожаем созданный нами объект пера PenBlack
	DeleteObject(Brush);                // уничтожаем созданный нами объект кисти Brush
}


// для этой группы астероидов границы уже будут другими
/*------------------------------------------------------------------------*/
/*            Neutron_Star           */
/*-----------------------------------*/

// производный класс Нейтронная звезда от Asteroid и по отпределению от Point и Location. И IAsteroid.
// конструктор
Neutron_Star::Neutron_Star(double InitX, double InitY) : Asteroid(InitX, InitY) // для инициализации старых полей используем конструктор предка
{
	m_number = 3;                       // номер астероида
	m_size = 13;				        // параметр для отрисовки
}

// деструктор
Neutron_Star:: ~Neutron_Star()
{
	// пустое тело
}

// отрисовка нимба переданным пером и кистью
void Neutron_Star::Nimbus(HPEN Pen, HBRUSH Brush)
{
	// нимб-круг вокруг Body
	Ellipse(hdc, m_X - 8 * m_size, m_Y + 2 * m_size, m_X + 5 * m_size, m_Y - 11 * m_size);
}

// отрисовка лучей переданным пером
void Neutron_Star::Rays(HPEN Pen)
{
	MoveToEx(hdc, m_X - 1.8 * m_size, m_Y - 9 * m_size, nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X - 1.3 * m_size, m_Y - 11 * m_size);               // установка конечного значения прямой

	MoveToEx(hdc, m_X - 1.3 * m_size, m_Y - 11 * m_size, nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X - 0.7 * m_size, m_Y - 8.9 * m_size);              // установка конечного значения прямой

	MoveToEx(hdc, m_X - 1.8 * m_size, m_Y + 0.5 * m_size, nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X - 1.3 * m_size, m_Y + 2 * m_size);                // установка конечного значения прямой

	MoveToEx(hdc, m_X - 1.3 * m_size, m_Y + 2 * m_size, nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X - 0.7 * m_size, m_Y + 0.2 * m_size);              // установка конечного значения прямой

	MoveToEx(hdc, m_X + 3 * m_size, m_Y - 4.8 * m_size, nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X + 4.8 * m_size, m_Y - 4.2 * m_size);              // установка конечного значения прямой

	MoveToEx(hdc, m_X + 4.8 * m_size, m_Y - 4.2 * m_size, nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X + 3 * m_size, m_Y - 3.6 * m_size);                // установка конечного значения прямой

	MoveToEx(hdc, m_X - 6.2 * m_size, m_Y - 4.5 * m_size, nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X - 8 * m_size, m_Y - 4 * m_size);                  // установка конечного значения прямой

	MoveToEx(hdc, m_X - 8 * m_size, m_Y - 4 * m_size, nullptr);       // установка начального значения прямой
	LineTo(hdc, m_X - 6.5 * m_size, m_Y - 3.2 * m_size);              // установка конечного значения прямой
}

// показать нейтронную звезду на экране. Виртуальный метод
void Neutron_Star::Show()
{
	m_Visible = true;                   // нейтронная звезда видна
	// зададим тип, толщину и цвет пера
	HPEN PenBlue = CreatePen(PS_SOLID, 3, RGB(65, 105, 225));
	// зададим цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// зададим тип, толщину и цвет пера
	HPEN PenViolet = CreatePen(PS_SOLID, 2, RGB(153, 50, 204));
	// зададим тип, толщину и цвет пера
	HPEN PenWhite = CreatePen(PS_SOLID, 2, RGB(253, 245, 230));
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// делаем перо PenBlue активным
	SelectObject(hdc, PenBlue);
	// рисуем нимб переданным пером и кистью
	Nimbus(PenBlue, Brush);
	// рисуем контур нейтронной звезды методом родителя заданным цветом
	Body(PenBlue);
	// делаем перо PenWhite активным
	SelectObject(hdc, PenWhite);
	// рисуем лучи нейтронной звезды заданным цветом
	Rays(PenBlue);
	// делаем перо PenViolet активным
	SelectObject(hdc, PenViolet);
	// рисуем кратеры нейтронной звезды методом родителя заданным цветом
	Craters(PenViolet);

	DeleteObject(PenWhite);             // уничтожаем созданный нами объект пера PenWhite
	DeleteObject(PenViolet);            // уничтожаем созданный нами объект пера PenViolet
	DeleteObject(PenBlue);              // уничтожаем созданный нами объект пера PenBlue
	DeleteObject(Brush);                // уничтожаем созданный нами объект кисти Brush
}

// скрыть нейтронную звезду с экрана. Виртуальный метод
void Neutron_Star::Hide()
{
	m_Visible = false;                  // нейтронная звезда видна
	// зададим тип, толщину и цвет пера
	HPEN PenBlack = CreatePen(PS_SOLID, 3, RGB(12, 12, 12));
	// зададим цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// делаем перо PenBlack активным
	SelectObject(hdc, PenBlack);
	// рисуем нимб переданным пером и кистью
	Nimbus(PenBlack, Brush);
	// рисуем контур нейтронной звезды методом родителя заданным цветом
	Body(PenBlack);
	// рисуем лучи нейтронной звезды заданным цветом
	Rays(PenBlack);
	// рисуем кратеры нейтронной звезды методом родителя заданным цветом
	Craters(PenBlack);

	DeleteObject(PenBlack);             // уничтожаем созданный нами объект пера PenBlack
	DeleteObject(Brush);                // уничтожаем созданный нами объект пера Brush
}

// вернуть значение самой левой точки нейтронной звезды/ мёртвой звезды. Виртуальный метод
double Neutron_Star::Left_Border()
{
	return(GetX() - 8 * GetSize());
}

// вернуть значение самой правой точки нейтронной звезды/ мёртвой звезды. Виртуальный метод
double Neutron_Star::Right_Border()
{
	return(GetX() + 5 * GetSize());
}

// вернуть значение самой верхней точки нейтронной звезды/ мёртвой звезды. Виртуальный метод
double Neutron_Star::High_Border()
{
	return(GetY() + 2.2 * GetSize());
}

// вернуть значение самой нижней точки нейтронной звезды/ мёртвой звезды. Виртуальный метод
double Neutron_Star::Low_Border()
{
	return(GetY() - 10 * GetSize());
}


/*------------------------------------------------------------------------*/
/*            Dead_Star           */
/*--------------------------------*/

// производный класс Мертвая звезда от Neutron_Star  и по отпределению от Asteroid, Point и Location. И IAsteroid.
// конструктор
Dead_Star::Dead_Star(double InitX, double InitY) : Neutron_Star(InitX, InitY)
{
	m_number = CountMeteor - 1;      // номер астероида
	m_size = 12;				     // параметр для отрисовки
};

// деструктор
Dead_Star::	~Dead_Star()                                               
{
	// пустое тело
}

// виртуальные функции для динамического полиморфизма
// отрисовка ядра заданным пером и цветом
void Dead_Star::Core(HPEN Pen, HBRUSH Brush)
{
	Ellipse(hdc, m_X - 4 * m_size, m_Y - 2 * m_size, m_X + 1 * m_size, m_Y - 7 * m_size);
}

// отрисовка лучей заданным пером и цветом
void Dead_Star::Bumps(HPEN Pen)
{
	MoveToEx(hdc, m_X - 0.6 * m_size, m_Y - 4 * m_size, nullptr);         // установка начального значения прямой
	LineTo(hdc, m_X + 1.3 * m_size, m_Y - 4.5 * m_size);                  // установка конечного значения прямой
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

// показать мёртвую звезду на экране. Виртуальный метод
void Dead_Star::Show()
{
	m_Visible = true;              // мёртвая звезда видна
	// зададим тип, толщину и цвет пера
	HPEN PenGreen = CreatePen(PS_SOLID, 3, RGB(152, 255, 152));
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// делаем перо PenGreen активным
	SelectObject(hdc, PenGreen);
	// отрисовываем нимб заданным пером и цветом
	Nimbus(PenGreen, Brush);
	Brush = CreateSolidBrush(RGB(248, 0, 0));
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// отрисовываем ядро заданным пером и цветом
	Core(PenGreen, Brush);
	// отрисовка полосок заданным пером
	Bumps(PenGreen);

	DeleteObject(PenGreen);       // уничтожаем созданный нами объект пера PenBlue
	DeleteObject(Brush);          // уничтожаем созданный нами объект кисти Brush
}

// скрыть мертвую звезду с экрана. Виртуальный метод
void Dead_Star::Hide()            
{
	m_Visible = false;            // мертвая звезда невидна
	// зададим тип, толщину и цвет пера
	HPEN PenBlack = CreatePen(PS_SOLID, 3, RGB(12, 12, 12));
	// зададим цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// делаем перо PenBlack активным
	SelectObject(hdc, PenBlack);
	// отрисовываем всё черным цветом
	Core(PenBlack, Brush);
	Bumps(PenBlack);
	Nimbus(PenBlack, Brush);

	DeleteObject(PenBlack);              // уничтожаем созданный нами объект пера PenBlue
	DeleteObject(PenBlack);              // уничтожаем созданный нами объект кисти Brush
}




/*------------------------------------------------------------------------------------------------------*/
/*            Летающие тарелки         */
/*-------------------------------------*/

/*------------------------------------------------------------------------------------------------------*/
/*           FlyingPlate         */
/*-------------------------------*/

// производный класс ЛЕТАЮЩАЯ_ТАРЕЛКА от интерфейса IFlyingPlate, от Point и по определению от Location
// фунции интерфейса должны быть принудительно реализованы
// конструктор летающей тарелки
FlyingPlate::FlyingPlate(int InitX, int InitY) : Point(InitX, InitY)
{
	m_parametr = 15;                   // параметр для отрисовки и регулировки размера
	m_num_plate = 0;                   // личный номер летающей тарелки
}

// деструктор
FlyingPlate::~FlyingPlate()
{
	// пустое тело
}

// константный геттер для получения значения размера
double FlyingPlate::GetParametr() const                   
{
	return(m_parametr);               // вернули значение параметра для отрисовки
}

// сеттер для принудительной установки значения размера
void FlyingPlate::SetParameter(int NewParametr)
{
	m_parametr = NewParametr;         // установили переданное значение параметра
}

// константный геттер для получения значения номера
int FlyingPlate::GetNum() const
{
	return(m_num_plate);              // вернули значение номера летающей тарелки
}

// сеттер для принудительной установки значения личного номера
void FlyingPlate::SetNum(int NewNum)
{
	m_num_plate = NewNum;             // установили переданное значение номера
}

// отрисовка нижней "юбки корабля"
void FlyingPlate::Skirt(HPEN Pen)
{
	// низ
	MoveToEx(hdc, m_X - 4 * m_parametr, m_Y - 2.4 * m_parametr, NULL);   // установка начального значения прямой
	LineTo(hdc, m_X + 7* m_parametr, m_Y - 2.4 * m_parametr);            // установка конечного значения прямой

	// правая сторона
	MoveToEx(hdc, m_X + 7 * m_parametr, m_Y - 2.4 * m_parametr, NULL);   // установка конечного значения прямой
	LineTo(hdc, m_X + 7.2 * m_parametr, m_Y - 2.6 * m_parametr);         // установка начального значения прямой

	MoveToEx(hdc, m_X + 7.2 * m_parametr, m_Y - 2.6 * m_parametr, NULL); // установка конечного значения прямой
	LineTo(hdc, m_X + 7.1 * m_parametr, m_Y - 2.8 * m_parametr);         // установка начального значения прямой

	MoveToEx(hdc, m_X + 7.1 * m_parametr, m_Y - 2.8 * m_parametr, NULL); // установка конечного значения прямой
	LineTo(hdc, m_X + 4.8 * m_parametr, m_Y - 4 * m_parametr);           // установка начального значения прямой


	// левая сторона
	MoveToEx(hdc, m_X - 4 * m_parametr, m_Y - 2.4 * m_parametr, NULL);   // установка конечного значения прямой
	LineTo(hdc, m_X - 4.2 * m_parametr, m_Y - 2.6 * m_parametr);         // установка начального значения прямой

	MoveToEx(hdc, m_X - 4.2 * m_parametr, m_Y - 2.6 * m_parametr, NULL); // установка конечного значения прямой
	LineTo(hdc, m_X - 4.1 * m_parametr, m_Y - 2.8 * m_parametr);         // установка начального значения прямой

	MoveToEx(hdc, m_X - 4.1 * m_parametr, m_Y - 2.8 * m_parametr, NULL); // установка конечного значения прямой
	LineTo(hdc, m_X - 1.8 * m_parametr, m_Y - 4 * m_parametr);           // установка начального значения прямой

	// верх
	MoveToEx(hdc, m_X - 1.8 * m_parametr, m_Y - 4 * m_parametr, NULL);   // установка конечного значения прямой
	LineTo(hdc, m_X + 4.8 * m_parametr, m_Y - 4 * m_parametr);           // установка начального значения прямой
}

// отрисовка окон внутри тела летающей тарелки
void FlyingPlate::Windows(HPEN Pen, HBRUSH Brush)
{
	//иллюминаторы
	// левый
	Ellipse(hdc, m_X - 2 * m_parametr, m_Y - 2.7 * m_parametr, m_X - 1.1 * m_parametr, m_Y - 3.6 * m_parametr);

	// середина
	Ellipse(hdc, m_X + 2 * m_parametr, m_Y - 2.7 * m_parametr, m_X + 1.1 * m_parametr, m_Y - 3.6 * m_parametr);

	// правый
	Ellipse(hdc, m_X + 5 * m_parametr, m_Y - 2.7 * m_parametr, m_X + 4.1 * m_parametr, m_Y - 3.6 * m_parametr);
}

// отрисовка стекла летающей тарелки
void FlyingPlate::Glass(HPEN Pen)
{
	MoveToEx(hdc, m_X - 1.8 * m_parametr, m_Y - 4.2 * m_parametr, NULL);  // установка конечного значения прямой
	LineTo(hdc, m_X - 1.5 * m_parametr, m_Y - 5 * m_parametr);            // установка начального значения прямой

	MoveToEx(hdc, m_X + 4.8 * m_parametr, m_Y - 4.2 * m_parametr, NULL);  // установка конечного значения прямой
	LineTo(hdc, m_X + 4.5 * m_parametr, m_Y - 5 * m_parametr);            // установка начального значения прямой

	MoveToEx(hdc, m_X - 1.5 * m_parametr, m_Y - 5 * m_parametr, NULL);    // установка конечного значения прямой
	LineTo(hdc, m_X - 1 * m_parametr, m_Y - 5.8 * m_parametr);            // установка начального значения прямой

	MoveToEx(hdc, m_X + 4.5 * m_parametr, m_Y - 5 * m_parametr, NULL);    // установка конечного значения прямой
	LineTo(hdc, m_X + 4 * m_parametr, m_Y - 5.8 * m_parametr);            // установка начального значения прямой

	MoveToEx(hdc, m_X - 1 * m_parametr, m_Y - 5.8 * m_parametr, NULL);    // установка конечного значения прямой
	LineTo(hdc, m_X - 0 * m_parametr, m_Y - 6.4 * m_parametr);            // установка начального значения прямой

	MoveToEx(hdc, m_X + 4 * m_parametr, m_Y - 5.8 * m_parametr, NULL);    // установка конечного значения прямой
	LineTo(hdc, m_X + 3 * m_parametr, m_Y - 6.4 * m_parametr);            // установка начального значения прямой

	MoveToEx(hdc, m_X - 0 * m_parametr, m_Y - 6.4 * m_parametr, NULL);    // установка конечного значения прямой
	LineTo(hdc, m_X + 1 * m_parametr, m_Y - 6.6 * m_parametr);            // установка начального значения прямой

	MoveToEx(hdc, m_X + 3 * m_parametr, m_Y - 6.4 * m_parametr, NULL);    // установка конечного значения прямой
	LineTo(hdc, m_X + 2 * m_parametr, m_Y - 6.6 * m_parametr);            // установка начального значения прямой
	
	MoveToEx(hdc, m_X + 2 * m_parametr, m_Y - 6.6 * m_parametr, NULL);    // установка конечного значения прямой
	LineTo(hdc, m_X + 1 * m_parametr, m_Y - 6.6 * m_parametr);            // установка начального значения прямой
}

// отрисовка ножек/нижнего окна летающей тарелки
void FlyingPlate::Legs(HPEN Pen)
{
	MoveToEx(hdc, m_X - 1.7 * m_parametr, m_Y - 2.3 * m_parametr, NULL);  // установка конечного значения прямой
	LineTo(hdc, m_X - 1 * m_parametr, m_Y - 1.9 * m_parametr);            // установка начального значения прямой

	MoveToEx(hdc, m_X + 4.8 * m_parametr, m_Y - 2.3 * m_parametr, NULL);  // установка конечного значения прямой
	LineTo(hdc, m_X + 4.1 * m_parametr, m_Y - 1.9 * m_parametr);          // установка начального значения прямой

	MoveToEx(hdc, m_X - 1 * m_parametr, m_Y - 1.9 * m_parametr, NULL);    // установка конечного значения прямой
	LineTo(hdc, m_X - 0 * m_parametr, m_Y - 1.7 * m_parametr);            // установка начального значения прямой

	MoveToEx(hdc, m_X + 4.1 * m_parametr, m_Y - 1.9 * m_parametr, NULL);  // установка конечного значения прямой
	LineTo(hdc, m_X + 3.1 * m_parametr, m_Y - 1.7 * m_parametr);          // установка начального значения прямой

	MoveToEx(hdc, m_X - 0 * m_parametr, m_Y - 1.7 * m_parametr, NULL);    // установка конечного значения прямой
	LineTo(hdc, m_X + 0.8 * m_parametr, m_Y - 1.6 * m_parametr);          // установка начального значения прямой

	MoveToEx(hdc, m_X + 3.1 * m_parametr, m_Y - 1.7 * m_parametr, NULL);  // установка конечного значения прямой
	LineTo(hdc, m_X + 2.3 * m_parametr, m_Y - 1.6 * m_parametr);          // установка начального значения прямой

	MoveToEx(hdc, m_X + 0.8 * m_parametr, m_Y - 1.6 * m_parametr, NULL);  // установка конечного значения прямой
	LineTo(hdc, m_X + 2.3 * m_parametr, m_Y - 1.6 * m_parametr);          // установка начального значения прямой
}

// показать летающую тарелку на экране. Виртуальный метод
void FlyingPlate::Show()
{
	m_Visible = true;                          // летающая тарелка видна
	
	// зададим тип, толщину и цвет пера
	HPEN PenGrey = CreatePen(PS_SOLID, 4, RGB(144, 144, 144));
	// делаем перо PenGrey активным
	SelectObject(hdc, PenGrey);
	Skirt(PenGrey);                            // отрисовка "юбки корабля"

	// зададим тип, толщину и цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(0, 51, 153));
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	Windows(PenGrey, Brush);                   // отрисовка окон внутри тела летающей тарелки

	// зададим тип, толщину и цвет пера
	HPEN PenTwitter = CreatePen(PS_SOLID, 4, RGB(31, 206, 203));
	// делаем перо PenTwitter активным
	SelectObject(hdc, PenTwitter);
	Glass(PenTwitter);                         // отрисовка стекла летающей тарелки

	// делаем перо PenGrey активным
	SelectObject(hdc, PenGrey);
	Legs(PenGrey);                             // отрисовка ножек/нижнего окна летающей тарелки

	DeleteObject(PenGrey);                     // уничтожим созданные нами объекты PenGrey
	DeleteObject(PenTwitter);                  // уничтожим созданные нами объекты PenTwitter
	DeleteObject(Brush);                       // уничтожим кисть Brush
}

// скрыть летающую тарелку с экрана. Виртуальный метод
void FlyingPlate::Hide()
{
	m_Visible = false;                         // летающая тарелка не видна

	// Отрисовка того же объекта цветом консоли
	// зададим тип, толщину и цвет пера
	HPEN PenBlack = CreatePen(PS_SOLID, 4, RGB(12, 12, 12));
	
	// делаем перо PenBlack активным
	SelectObject(hdc, PenBlack);
	Skirt(PenBlack);                           // отрисовка "юбки корабля"

	// зададим тип, толщину и цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	Windows(PenBlack, Brush);                  // отрисовка окон внутри тела летающей тарелки
	Glass(PenBlack);                           // отрисовка стекла летающей тарелки
	Legs(PenBlack);                            // отрисовка ножек/нижнего окна летающей тарелки

	DeleteObject(PenBlack);                    // уничтожим созданные нами объекты PenGreyPurple
	DeleteObject(Brush);                       // уничтожим кисть Brush
}

// вернуть значение самой левой точки летающей тарелки/   сломаной летающей тарелки
int FlyingPlate:: Left_Border()                          
{
	return(GetX() - 4.3 * GetParametr());
}

// вернуть значение самой правой точки летающей тарелки/  сломаной летающей тарелки
int FlyingPlate::Right_Border()
{
	return(GetX() + 7.3 * GetParametr());
}

// вернуть значение самой низкой точки летающей тарелки/  сломаной летающей тарелки
int FlyingPlate::Low_Border()                           
{
	return(GetY() - 6.6 * m_parametr);
}

// вернуть значение самой высокой точки летающей тарелки/ сломаной летающей тарелки
int FlyingPlate::High_Border()
{
	return(GetY() - 1.6 * m_parametr);
}


/*------------------------------------------------------------------------------------------------------*/
/*         Broke_FlyingPlate           */
/*-------------------------------------*/

// производный класс Сломаная Летающая_Тарелка от FlyingPlate и по определению от Point и Location. И IFlyingPlate
// конструктор
Broke_FlyingPlate::Broke_FlyingPlate(int InitX, int InitY):FlyingPlate(InitX, InitY)
{
	m_parametr = 15;                           // параметр для отрисовки и регулировки размера          
	m_num_plate = 1;                           // личный номер летающей тарелки
}

// деструктор
Broke_FlyingPlate:: ~Broke_FlyingPlate() 
{
	// пустое тело
}

// отрисовка сломанного стекла сломанной летающей тарелки
void Broke_FlyingPlate::Glass(HPEN Pen)
{
	MoveToEx(hdc, m_X - 1.8 * m_parametr, m_Y - 4.2 * m_parametr, NULL);               // установка конечного значения прямой
	LineTo(hdc, m_X - 1.5 * m_parametr, m_Y - 5 * m_parametr);                         // установка начального значения прямой

	MoveToEx(hdc, m_X + 4.8 * m_parametr, m_Y - 4.2 * m_parametr, NULL);               // установка конечного значения прямой
	LineTo(hdc, m_X + 4.5 * m_parametr, m_Y - 5 * m_parametr);                         // установка начального значения прямой

	MoveToEx(hdc, m_X - 1.5 * m_parametr, m_Y - 5 * m_parametr, NULL);                 // установка конечного значения прямой
	LineTo(hdc, m_X - 1 * m_parametr, m_Y - 5.8 * m_parametr);                         // установка начального значения прямой

	MoveToEx(hdc, m_X - 1 * m_parametr, m_Y - 5.8 * m_parametr, NULL);                 // установка конечного значения прямой
	LineTo(hdc, m_X - 0 * m_parametr, m_Y - 6.4 * m_parametr);                         // установка начального значения прямой

	MoveToEx(hdc, m_X - 0 * m_parametr, m_Y - 6.4 * m_parametr, NULL);                 // установка конечного значения прямой
	LineTo(hdc, m_X + 0.5 * m_parametr, m_Y - 5.5 * m_parametr);                       // установка начального значения прямой

	MoveToEx(hdc, m_X + 0.5 * m_parametr, m_Y - 5.5 * m_parametr, NULL);               // установка конечного значения прямой
	LineTo(hdc, m_X + 2 * m_parametr, m_Y - 6.2 * m_parametr);                         // установка начального значения прямой

	MoveToEx(hdc, m_X + 2 * m_parametr, m_Y - 6.2 * m_parametr, NULL);                 // установка конечного значения прямой
	LineTo(hdc, m_X + 2 * m_parametr, m_Y - 5 * m_parametr);                           // установка начального значения прямой

	MoveToEx(hdc, m_X + 2 * m_parametr, m_Y - 5 * m_parametr, NULL);                   // установка конечного значения прямой
	LineTo(hdc, m_X + 4 * m_parametr, m_Y - 5.8 * m_parametr);                         // установка начального значения прямой

	MoveToEx(hdc, m_X + 4 * m_parametr, m_Y - 5.8 * m_parametr, NULL);                 // установка конечного значения прямой
	LineTo(hdc, m_X + 4.5 * m_parametr, m_Y - 5 * m_parametr);                         // установка начального значения прямой
}

// показать сломанную летающую тарелку на экране. Виртуальный метод
void Broke_FlyingPlate::Show()
{
	m_Visible = true;                          // сломаная летающая тарелка видна
	
	// зададим тип, толщину и цвет пера
	HPEN PenGrey = CreatePen(PS_SOLID, 4, RGB(144, 144, 144));
	// делаем перо PenGrey активным
	SelectObject(hdc, PenGrey);
	Skirt(PenGrey);                            // отрисовка "юбки корабля". Родительская функция

	// зададим тип, толщину и цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(252, 40, 71));
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	Windows(PenGrey, Brush);                   // отрисовка окон внутри тела летающей тарелки. Родительский метод

	// зададим тип, толщину и цвет пера
	HPEN PenTwitter = CreatePen(PS_SOLID, 4, RGB(31, 206, 203));
	// делаем перо PenTwitter активным
	SelectObject(hdc, PenTwitter);
	Glass(PenTwitter);                         // отрисовка сломанного стекла сломанной летающей тарелки
	
	// делаем перо PenGrey активным
	SelectObject(hdc, PenGrey);               
	Legs(PenGrey);                             // отрисовка ножек/нижнего окна летающей тарелки. родительская функция

	DeleteObject(PenGrey);                     // уничтожим созданные нами объекты PenGrey
	DeleteObject(PenTwitter);                  // уничтожим созданные нами объекты PenTwitter
	DeleteObject(Brush);                       // уничтожим кисть Brush
}

// скрыть сломаную летающую тарелку с экрана. Виртуальный метод
void Broke_FlyingPlate::Hide()
{
	m_Visible = false;                         // сломаная летающая тарелка не видна
	
	// Отрисовка того же объекта цветом консоли
	// зададим тип, толщину и цвет пера
	HPEN PenBlack = CreatePen(PS_SOLID, 4, RGB(12, 12, 12));
	// делаем перо PenBlack  активным
	SelectObject(hdc, PenBlack);
	Skirt(PenBlack);                           // отрисовка "юбки корабля". Родительская функция

	// зададим тип, толщину и цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	Windows(PenBlack, Brush);                  // отрисовка окон внутри тела сломаной летающей тарелки. Родительская функция
	Glass(PenBlack);                           // отрисовка стекла сломаной летающей тарелки.
	Legs(PenBlack);                            // отрисовка ножек/нижнего окна летающей тарелки. Родительская функция

	DeleteObject(PenBlack);                    // уничтожим созданные нами объекты PenBlack
	DeleteObject(Brush);                       // уничтожим кисть Brush
}


/*------------------------------------------------------------------------------------------------------*/
/*        Angry_FlyingPlate           */
/*------------------------------------*/

// производный класс Злая Летающая_Тарелка от FlyingPlate и по определению от Point и Location. И IFlyingPlate
Angry_FlyingPlate::Angry_FlyingPlate(int InitX, int InitY): FlyingPlate(InitX, InitY)  // конструктор.
{
	m_parametr = 15;                           // параметр для отрисовки и регулировки размера 
	m_num_plate = 2;						   // личный номер летающей тарелки
}

// деструктор
Angry_FlyingPlate::~Angry_FlyingPlate()
{
	// пустое тело
}

// отрисовка нижней "юбки корабля" злой летающей тарелки
void Angry_FlyingPlate:: Skirt(HPEN Pen)
{
	// низ
	MoveToEx(hdc, m_X - 4 * m_parametr, m_Y - 2.4 * m_parametr, NULL);                 // установка начального значения прямой
	LineTo(hdc, m_X + 7 * m_parametr, m_Y - 2.4 * m_parametr);                         // установка конечного значения прямой
	// бока
	MoveToEx(hdc, m_X - 4 * m_parametr, m_Y - 2.4 * m_parametr, NULL);                 // установка начального значения прямой
	LineTo(hdc, m_X -4 * m_parametr, m_Y - 3.5 * m_parametr);                          // установка конечного значения прямой

	MoveToEx(hdc, m_X + 7 * m_parametr, m_Y - 2.4 * m_parametr, NULL);                 // установка начального значения прямой
	LineTo(hdc, m_X +7 * m_parametr, m_Y - 3.5 * m_parametr);                          // установка конечного значения прямой

	MoveToEx(hdc, m_X + 7 * m_parametr, m_Y - 3.5 * m_parametr, NULL);                 // установка начального значения прямой
	LineTo(hdc, m_X - 4 * m_parametr, m_Y - 3.5 * m_parametr);                         // установка конечного значения прямой

	// верх
	MoveToEx(hdc, m_X - 4 * m_parametr, m_Y - 3.5 * m_parametr, NULL);                 // установка начального значения прямой
	LineTo(hdc, m_X - 0.5 * m_parametr, m_Y - 5 * m_parametr);                         // установка конечного значения прямой

	MoveToEx(hdc, m_X + 7 * m_parametr, m_Y - 3.5 * m_parametr, NULL);                 // установка начального значения прямой
	LineTo(hdc, m_X + 3.5 * m_parametr, m_Y - 5 * m_parametr);                         // установка конечного значения прямой

	MoveToEx(hdc, m_X - 0.5 * m_parametr, m_Y - 5 * m_parametr, NULL);                 // установка начального значения прямой
	LineTo(hdc, m_X + 3.5 * m_parametr, m_Y - 5 * m_parametr);                         // установка конечного значения прямой

	MoveToEx(hdc, m_X - 0.5 * m_parametr, m_Y - 5 * m_parametr, NULL);                 // установка начального значения прямой
	LineTo(hdc, m_X - 0 * m_parametr, m_Y - 6.2 * m_parametr);                         // установка конечного значения прямой

	// внимание
	MoveToEx(hdc, m_X - 0 * m_parametr, m_Y - 5.9 * m_parametr, NULL);                 // установка начального значения прямой
	LineTo(hdc, m_X + 3 * m_parametr, m_Y - 5.9 * m_parametr);                         // установка конечного значения прямой

	MoveToEx(hdc, m_X + 3.5 * m_parametr, m_Y - 5 * m_parametr, NULL);                 // установка начального значения прямой
	LineTo(hdc, m_X + 3 * m_parametr, m_Y - 6.2 * m_parametr);                         // установка конечного значения прямой

	// низ
	MoveToEx(hdc, m_X - 2 * m_parametr, m_Y - 2.4 * m_parametr, NULL);                 // установка начального значения прямой
	LineTo(hdc, m_X - 0 * m_parametr, m_Y - 1.5 * m_parametr);                         // установка конечного значения прямой

	MoveToEx(hdc, m_X + 5 * m_parametr, m_Y - 2.4 * m_parametr, NULL);                 // установка начального значения прямой
	LineTo(hdc, m_X +3 * m_parametr, m_Y - 1.5 * m_parametr);                          // установка конечного значения прямой

	MoveToEx(hdc, m_X - 0 * m_parametr, m_Y - 1.5 * m_parametr, NULL);                 // установка начального значения прямой
	LineTo(hdc, m_X + 3 * m_parametr, m_Y - 1.5 * m_parametr);                         // установка конечного значения прямой

	//рожки
	MoveToEx(hdc, m_X - 0 * m_parametr, m_Y - 5.9 * m_parametr, NULL);                 // установка начального значения прямой
	LineTo(hdc, m_X - 0.5 * m_parametr, m_Y - 7.5 * m_parametr);                       // установка конечного значения прямой

	MoveToEx(hdc, m_X + 3 * m_parametr, m_Y - 5.9 * m_parametr, NULL);                 // установка начального значения прямой
	LineTo(hdc, m_X + 3.5 * m_parametr, m_Y - 7.5 * m_parametr);                       // установка конечного значения прямой

	// полоски

	MoveToEx(hdc, m_X - 0.3 * m_parametr, m_Y - 5 * m_parametr, NULL);                 // установка начального значения прямой
	LineTo(hdc, m_X - 2 * m_parametr, m_Y - 3.5 * m_parametr);                         // установка конечного значения прямой

	MoveToEx(hdc, m_X + 3.5 * m_parametr, m_Y - 5 * m_parametr, NULL);                 // установка начального значения прямой
	LineTo(hdc, m_X + 5 * m_parametr, m_Y - 3.5 * m_parametr);                         // установка конечного значения прямой
}

// отрисовка стекла злой летающей тарелки
void Angry_FlyingPlate::Glass(HPEN Pen)
{
	MoveToEx(hdc, m_X - 0 * m_parametr, m_Y - 6.2 * m_parametr, NULL);       // установка начального значения прямой
	LineTo(hdc, m_X + 0.5 * m_parametr, m_Y - 7 * m_parametr);               // установка конечного значения прямой

	MoveToEx(hdc, m_X + 3 * m_parametr, m_Y - 6.2 * m_parametr, NULL);       // установка начального значения прямой
	LineTo(hdc, m_X + 2.5 * m_parametr, m_Y - 7 * m_parametr);               // установка конечного значения прямой

	MoveToEx(hdc, m_X + 0.5 * m_parametr, m_Y - 7 * m_parametr, NULL);       // установка начального значения прямой
	LineTo(hdc, m_X + 1 * m_parametr, m_Y - 7.4 * m_parametr);               // установка конечного значения прямой

	MoveToEx(hdc, m_X + 2.5 * m_parametr, m_Y - 7 * m_parametr, NULL);       // установка начального значения прямой
	LineTo(hdc, m_X + 2 * m_parametr, m_Y - 7.4 * m_parametr);               // установка конечного значения прямой

	MoveToEx(hdc, m_X + 2 * m_parametr, m_Y - 7.4 * m_parametr, NULL);       // установка начального значения прямой
	LineTo(hdc, m_X + 1 * m_parametr, m_Y - 7.4 * m_parametr);               // установка конечного значения прямой
}

// отрисовка окон внутри тела злой летающей тарелки
void Angry_FlyingPlate::Windows(HPEN Pen, HBRUSH Brush)
{
	// левый
	Ellipse(hdc, m_X - 2.9 * m_parametr, m_Y - 2.6 * m_parametr, m_X - 2.1 * m_parametr, m_Y - 3.4 * m_parametr);

	// середина
	Ellipse(hdc, m_X - 0 * m_parametr, m_Y - 2.6 * m_parametr, m_X +3 * m_parametr, m_Y - 3.4 * m_parametr);

	// правый
	Ellipse(hdc, m_X + 5.2 * m_parametr, m_Y - 2.6 * m_parametr, m_X + 6 * m_parametr, m_Y - 3.4 * m_parametr);
}

// отрисовка ножек/нижнего окна злой летающей тарелки
void Angry_FlyingPlate::Legs(HPEN Pen)
{
	MoveToEx(hdc, m_X - 0 * m_parametr, m_Y - 1.3 * m_parametr, NULL);       // установка начального значения прямой
	LineTo(hdc, m_X + 0.5 * m_parametr, m_Y - 1 * m_parametr);               // установка конечного значения прямой

	MoveToEx(hdc, m_X + 3 * m_parametr, m_Y - 1.3 * m_parametr, NULL);       // установка начального значения прямой
	LineTo(hdc, m_X + 2.5 * m_parametr, m_Y - 1 * m_parametr);               // установка конечного значения прямой

	MoveToEx(hdc, m_X + 0.5 * m_parametr, m_Y - 1 * m_parametr, NULL);       // установка начального значения прямой
	LineTo(hdc, m_X + 1.3 * m_parametr, m_Y - 0.7 * m_parametr);             // установка конечного значения прямой

	MoveToEx(hdc, m_X + 2.5 * m_parametr, m_Y - 1 * m_parametr, NULL);       // установка начального значения прямой
	LineTo(hdc, m_X + 1.7 * m_parametr, m_Y - 0.7 * m_parametr);             // установка конечного значения прямой

	MoveToEx(hdc, m_X + 1.3 * m_parametr, m_Y - 0.7 * m_parametr, NULL);     // установка начального значения прямой
	LineTo(hdc, m_X + 1.7 * m_parametr, m_Y - 0.7 * m_parametr);             // установка конечного значения прямой
}

// показать злую летающую тарелку на экране. Виртуальный метод
void Angry_FlyingPlate::Show()
{
	m_Visible = true;                          // злая летающая тарелка видна

	// зададим тип, толщину и цвет пера
	HPEN PenBrown = CreatePen(PS_SOLID, 4, RGB(127, 24, 13));
	HPEN PenYellow = CreatePen(PS_SOLID, 4, RGB(254, 254, 34));
	HPEN PenTwitter = CreatePen(PS_SOLID, 4, RGB(31, 206, 203));
	// зададим тип, толщину и цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(254, 254, 34));
	
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// делаем перо PenBrown активным
	SelectObject(hdc, PenBrown);
	Skirt(PenBrown);                           // отрисовка нижней "юбки корабля" злой летающей тарелки

	// делаем перо PenTwitter активным
	SelectObject(hdc, PenTwitter);
	Glass(PenBrown);                           // отрисовка стекла злой летающей тарелки

	// делаем перо PenYellow активным
	SelectObject(hdc, PenYellow);
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	Windows(PenYellow, Brush);                 // отрисовка окон внутри тела злой летающей тарелки           
	Legs(PenBrown);                            // отрисовка ножек/нижнего окна злой летающей тарелки

	DeleteObject(PenYellow);                   // уничтожим созданные нами объекты PenYellow
	DeleteObject(Brush);                       // уничтожим кисть Brush
	DeleteObject(PenBrown);                    // уничтожим созданные нами объекты PenBrown
	DeleteObject(PenTwitter);                  // уничтожим созданные нами объекты PenTwitter
}

// скрыть злую летающую тарелку с экрана. Виртуальный метод
void Angry_FlyingPlate::Hide()
{
	m_Visible = false;                         // злая летающая тарелка не видна

	// отрисовка того же объекта цветом консоли
	// зададим тип, толщину и цвет пера
	HPEN PenBlack = CreatePen(PS_SOLID, 4, RGB(12, 12, 12));
	// зададим тип, толщину и цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// делаем перо PenBlack активным
	SelectObject(hdc, PenBlack);

	Skirt(PenBlack);                           // отрисовка "юбки корабля"
	Glass(PenBlack);                           // отрисовка стекла злой летающей тарелки
	Windows(PenBlack, Brush);				   // отрисовка окон внутри тела злой летающей тарелки
	Legs(PenBlack);							   // отрисовка ножек/нижнего окна летающей тарелки

	DeleteObject(PenBlack);                    // уничтожим созданные нами объекты PenBlack
	DeleteObject(Brush);                       // уничтожим кисть Brush
}

// вернуть значение самой левой точки злой летающей тарелки
int Angry_FlyingPlate::Left_Border()                              
{
	return(GetX() - 3.9 * GetParametr());
}

// вернуть значение самой правой точки злой летающей тарелки
int Angry_FlyingPlate::Right_Border()                              
{
	return(GetX() + 7.1 * GetParametr());
}

// вернуть значение самой низкой точки злой летающей тарелки
int Angry_FlyingPlate::Low_Border()                               
{
	return(GetY() - 7.4 * m_parametr);
}

// вернуть значение самой левой точки злой летающей тарелки
int Angry_FlyingPlate::High_Border()
{
	return(GetY() - 0.7 * m_parametr);
}


/*------------------------------------------------------------------------------------------------------*/
/*             Modify_FlyingPlate             */
/*--------------------------------------------*/

// производный класс Модифицированная Летающая_Тарелка от Angry_FlyingPlate и по определению от FlyingPlate и Point и Location. И IFlyingPlate
// конструктор
Modify_FlyingPlate:: Modify_FlyingPlate(int InitX, int InitY): Angry_FlyingPlate(InitX, InitY)
{
	m_parametr = 15;                           // параметр для отрисовки и регулировки размера
	m_num_plate = 3;						   // личный номер летающей тарелки
}

// деструктор
Modify_FlyingPlate:: ~Modify_FlyingPlate()
{
	// пустое тело
}

// отрисовка выпуклости посередине модифицированной летающей тарелки
void Modify_FlyingPlate::Back(HPEN Pen)
{
	MoveToEx(hdc, m_X - 4 * m_parametr, m_Y - 2.4 * m_parametr, NULL);       // установка начального значения прямой
	LineTo(hdc, m_X + 7 * m_parametr, m_Y - 2.4 * m_parametr);               // установка конечного значения прямой

	MoveToEx(hdc, m_X - 4 * m_parametr, m_Y - 2.4 * m_parametr, NULL);       // установка начального значения прямой
	LineTo(hdc, m_X - 4.4 * m_parametr, m_Y - 3 * m_parametr);               // установка конечного значения прямой

	MoveToEx(hdc, m_X + 7 * m_parametr, m_Y - 2.4 * m_parametr, NULL);       // установка начального значения прямой
	LineTo(hdc, m_X + 7.4 * m_parametr, m_Y - 3.1 * m_parametr);             // установка конечного значения прямой

	MoveToEx(hdc, m_X - 4.4 * m_parametr, m_Y - 3.1 * m_parametr, NULL);     // установка начального значения прямой
	LineTo(hdc, m_X - 4 * m_parametr, m_Y - 3.8 * m_parametr);               // установка конечного значения прямой

	MoveToEx(hdc, m_X + 7.4 * m_parametr, m_Y - 3.1 * m_parametr, NULL);     // установка начального значения прямой
	LineTo(hdc, m_X + 7 * m_parametr, m_Y - 3.8 * m_parametr);               // установка конечного значения прямой

	MoveToEx(hdc, m_X - 4 * m_parametr, m_Y - 3.8 * m_parametr, NULL);       // установка начального значения прямой
	LineTo(hdc, m_X + 7 * m_parametr, m_Y - 3.8 * m_parametr);               // установка конечного значения прямой
}

// отрисовка нижней "юбки корабля" модифицированной летающей тарелки
void Modify_FlyingPlate:: Skirt(HPEN Pen)
{

	MoveToEx(hdc, m_X - 2.9 * m_parametr, m_Y - 2.4 * m_parametr, NULL);     // установка начального значения прямой
	LineTo(hdc, m_X - 1.8 * m_parametr, m_Y - 2 * m_parametr);               // установка конечного значения прямой

	MoveToEx(hdc, m_X + 5.9 * m_parametr, m_Y - 2.4 * m_parametr, NULL);     // установка начального значения прямой
	LineTo(hdc, m_X + 4.8 * m_parametr, m_Y - 2 * m_parametr);               // установка конечного значения прямой

	MoveToEx(hdc, m_X - 1.8 * m_parametr, m_Y - 2 * m_parametr, NULL);       // установка начального значения прямой
	LineTo(hdc, m_X - 0.7 * m_parametr, m_Y - 1.7 * m_parametr);             // установка конечного значения прямой

	MoveToEx(hdc, m_X + 4.8 * m_parametr, m_Y - 2 * m_parametr, NULL);       // установка начального значения прямой
	LineTo(hdc, m_X + 3.7 * m_parametr, m_Y - 1.7 * m_parametr);             // установка конечного значения прямой

	MoveToEx(hdc, m_X - 0.7 * m_parametr, m_Y - 1.7 * m_parametr, NULL);     // установка начального значения прямой
	LineTo(hdc, m_X + 0.5 * m_parametr, m_Y - 1.6 * m_parametr);             // установка конечного значения прямой

	MoveToEx(hdc, m_X + 3.7 * m_parametr, m_Y - 1.7 * m_parametr, NULL);     // установка начального значения прямой
	LineTo(hdc, m_X + 2.5 * m_parametr, m_Y - 1.6 * m_parametr);             // установка конечного значения прямой

	MoveToEx(hdc, m_X + 0.5 * m_parametr, m_Y - 1.6 * m_parametr, NULL);     // установка начального значения прямой
	LineTo(hdc, m_X + 2.5 * m_parametr, m_Y - 1.6 * m_parametr);             // установка конечного значения прямой

	MoveToEx(hdc, m_X - 2.9 * m_parametr, m_Y - 3.8 * m_parametr, NULL);     // установка начального значения прямой
	LineTo(hdc, m_X - 1.9 * m_parametr, m_Y - 5 * m_parametr);               // установка конечного значения прямой

	MoveToEx(hdc, m_X + 5.9 * m_parametr, m_Y - 3.8 * m_parametr, NULL);     // установка начального значения прямой
	LineTo(hdc, m_X + 4.9 * m_parametr, m_Y - 5 * m_parametr);               // установка конечного значения прямой

	MoveToEx(hdc, m_X - 1.9 * m_parametr, m_Y - 5 * m_parametr, NULL);       // установка начального значения прямой
	LineTo(hdc, m_X - 0* m_parametr, m_Y - 5.9 * m_parametr);                // установка конечного значения прямой

	MoveToEx(hdc, m_X + 4.9 * m_parametr, m_Y - 5 * m_parametr, NULL);       // установка начального значения прямой
	LineTo(hdc, m_X + 3 * m_parametr, m_Y - 5.9 * m_parametr);               // установка конечного значения прямой

	MoveToEx(hdc, m_X - 0 * m_parametr, m_Y - 5.9 * m_parametr, NULL);       // установка начального значения прямой
	LineTo(hdc, m_X + 1 * m_parametr, m_Y - 6.1 * m_parametr);               // установка конечного значения прямой

	MoveToEx(hdc, m_X + 1 * m_parametr, m_Y - 6.1 * m_parametr, NULL);       // установка начального значения прямой
	LineTo(hdc, m_X + 3 * m_parametr, m_Y - 5.9 * m_parametr);               // установка конечного значения прямой

	// рожки
	MoveToEx(hdc, m_X + 3.5 * m_parametr, m_Y - 5.9 * m_parametr, NULL);     // установка начального значения прямой
	LineTo(hdc, m_X + 4 * m_parametr, m_Y - 7 * m_parametr);                 // установка конечного значения прямой

	MoveToEx(hdc, m_X - 0.3 * m_parametr, m_Y - 5.9 * m_parametr, NULL);     // установка начального значения прямой
	LineTo(hdc, m_X - 1 * m_parametr, m_Y - 7 * m_parametr);                 // установка конечного значения прямой
}

// отрисовка окон внутри тела модифицированной летающей тарелки
void Modify_FlyingPlate::Windows(HPEN Pen, HBRUSH Brush)
{
	Ellipse(hdc, m_X - 2.9 * m_parametr, m_Y - 2.6 * m_parametr, m_X - 2.1 * m_parametr, m_Y - 3.4 * m_parametr);

	// середина
	Ellipse(hdc, m_X - 1 * m_parametr, m_Y - 2.6 * m_parametr, m_X - 0.2 * m_parametr, m_Y - 3.4 * m_parametr);

	Ellipse(hdc, m_X + 1 * m_parametr, m_Y - 2.6 * m_parametr, m_X + 1.8 * m_parametr, m_Y - 3.4 * m_parametr);

	Ellipse(hdc, m_X + 3 * m_parametr, m_Y - 2.6 * m_parametr, m_X + 3.8 * m_parametr, m_Y - 3.4 * m_parametr);

	Ellipse(hdc, m_X + 4.9 * m_parametr, m_Y - 2.6 * m_parametr, m_X + 5.7 * m_parametr, m_Y - 3.4 * m_parametr);
}

// показать модифицированную летающую тарелку на экране. Виртуальный метод
void Modify_FlyingPlate:: Show()                                 
{
	m_Visible = true;                          // злая летающая тарелка видна

	// зададим тип, толщину и цвет перьев
	HPEN PenBrown = CreatePen(PS_SOLID, 4, RGB(183, 132, 167));
	HPEN PenYellow = CreatePen(PS_SOLID, 4, RGB(254, 254, 34));
	HPEN PenTwitter = CreatePen(PS_SOLID, 4, RGB(31, 206, 203));
	HPEN PenMalin = CreatePen(PS_SOLID, 4, RGB(220, 20, 60));
	// зададим тип, толщину и цвет кистей
	HBRUSH Brush = CreateSolidBrush(RGB(254, 254, 34));

	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// делаем перо PenBrown активным
	SelectObject(hdc, PenBrown);
	Skirt(PenBrown);                           // отрисовка нижней "юбки корабля" модифицированной летающей тарелки
	
	// делаем перо PenMalin активным
	SelectObject(hdc, PenMalin);
	Back(PenBrown);                            // отрисовка выпуклости посередине модифицированной летающей тарелки

	// делаем перо PenTwitter активным
	SelectObject(hdc, PenTwitter);
	Glass(PenBrown);                           // отрисовка стекла злой летающей тарелки. Родительский метод

	// делаем перо PenYellow активным
	SelectObject(hdc, PenYellow);
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	Windows(PenYellow, Brush);                 // отрисовка окон внутри тела модифицированной летающей тарелки
	Legs(PenBrown);                            // отрисовка ножек/нижнего окна злой летающей тарелки. Родительский метод
	
	DeleteObject(PenMalin);                    // уничтожим созданные нами объекты PenMalin
	DeleteObject(PenYellow);                   // уничтожим созданные нами объекты PenYellow
	DeleteObject(Brush);                       // уничтожим кисть Brush
	DeleteObject(PenBrown);                    // уничтожим созданные нами объекты PenBrown
	DeleteObject(PenTwitter);                  // уничтожим созданные нами объекты PenTwitter
}

// скрыть модифицированную летающую тарелку с экрана. Виртуальный метод
void Modify_FlyingPlate:: Hide()                             
{
	m_Visible = false;                         // мидифицированная летающая тарелка не видна
	
	// отрисовка того же объекта цветом консоли
	// зададим тип, толщину и цвет пера
	HPEN PenBlack = CreatePen(PS_SOLID, 4, RGB(12, 12, 12));
	// зададим тип, толщину и цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));

	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// делаем перо PenBlack активным
	SelectObject(hdc, PenBlack);

	Skirt(PenBlack);                           // отрисовка нижней "юбки корабля" модифицированной летающей тарелки
	Glass(PenBlack);                           // отрисовка стекла злой летающей тарелки. Родительский метод
	Back(PenBlack);                            // отрисовка выпуклости посередине модифицированной летающей тарелки
	Windows(PenBlack, Brush);                  // отрисовка окон внутри тела модифицированной летающей тарелки
	Legs(PenBlack);                            // отрисовка ножек/нижнего окна злой летающей тарелки. Родительский метод
	
	DeleteObject(PenBlack);                    // уничтожим созданные нами объекты PenBlack
	DeleteObject(Brush);                       // уничтожим кисть Brush
}

// вернуть значение самой левой точки модифицированной летающей тарелки
int Modify_FlyingPlate:: Left_Border()
{
	return(GetX() - 4.6 * GetParametr());
}

// вернуть значение самой правой точки модифицированной летающей тарелки
int Modify_FlyingPlate::Right_Border()                             
{
	return(GetX() + 7.6 * GetParametr());
}

// вернуть значение самой низкой точки модифицированной летающей тарелки
int Modify_FlyingPlate::Low_Border()
{
	return(GetY() - 7.4 * m_parametr);
}

// вернуть значение самой левой точки модифицированной летающей тарелки
int Modify_FlyingPlate::High_Border()                               
{
	return(GetY() - 0.6 * m_parametr);
}




/*-----------------------------------------------------------------------------------------------------------------------*/
/*             Корабли          */
/*------------------------------*/

/*------------------------------------------------------------------------*/
/*              Ship                */
/*----------------------------------*/

// производный класс Корабль от Point и по определению от Location. Производный от интерфейса IShip
// конструктор
Ship::Ship(double InitX, double InitY) : Point(InitX, InitY)
{
	m_scale = 6;                          // размер. Параметр для отрисовки объекта
	s_number = 0;                         // номер. Параметр для матрицы переходов кораблей. Меняется в конструкторе
}

// деструктор
Ship::~Ship()
{
	// пустое тело
}

// геттер для получения значения размера
double Ship::GetScale() const
{
	return (m_scale);
}

// сеттер для принудительной установки значения размера
void Ship::SetScale(double NewScale)
{
	m_scale = NewScale;
}

// геттер для получения значения номера корабля
int Ship::GetSNumber() const
{
	return (s_number);
}

// сеттер для принудительной установки значения значения номера корабля
void Ship::SetSNumber(int NewSNumber)
{
	s_number = NewSNumber;
}

// отрисовка корпуса корабля переданным пером и кистью
void Ship::body(HPEN Pen, HBRUSH Brush)
{
	// корпус
	// нижняя часть
	MoveToEx(hdc, m_X - 4 * m_scale, m_Y - 0 * m_scale, nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X + 4 * m_scale, m_Y - 0 * m_scale);
	MoveToEx(hdc, m_X - 4 * m_scale, m_Y - 0 * m_scale, nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X - 7 * m_scale, m_Y + 1.5 * m_scale);
	MoveToEx(hdc, m_X + 4 * m_scale, m_Y - 0 * m_scale, nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X + 7 * m_scale, m_Y + 1.5 * m_scale);

	MoveToEx(hdc, m_X - 4 * m_scale, m_Y - 1 * m_scale, nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X + 4 * m_scale, m_Y - 1 * m_scale);
	MoveToEx(hdc, m_X - 4 * m_scale, m_Y - 1 * m_scale, nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X - 7 * m_scale, m_Y + 0.5 * m_scale);
	MoveToEx(hdc, m_X + 4 * m_scale, m_Y - 1 * m_scale, nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X + 7 * m_scale, m_Y + 0.5 * m_scale);
	// боковая часть
	MoveToEx(hdc, m_X - 7 * m_scale, m_Y + 1.5 * m_scale, nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X - 12 * m_scale, m_Y - 9 * m_scale);
	MoveToEx(hdc, m_X + 7 * m_scale, m_Y + 1.5 * m_scale, nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X + 12 * m_scale, m_Y - 9 * m_scale);
	MoveToEx(hdc, m_X - 12 * m_scale, m_Y - 9 * m_scale, nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X - 8 * m_scale, m_Y - 16 * m_scale);
	MoveToEx(hdc, m_X + 12 * m_scale, m_Y - 9 * m_scale, nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 8 * m_scale, m_Y - 16 * m_scale);
	MoveToEx(hdc, m_X - 8 * m_scale, m_Y - 16 * m_scale, nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X - 5 * m_scale, m_Y - 20 * m_scale);
	MoveToEx(hdc, m_X + 8 * m_scale, m_Y - 16 * m_scale, nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 5 * m_scale, m_Y - 20 * m_scale);
	MoveToEx(hdc, m_X - 6 * m_scale, m_Y + 1 * m_scale, nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X - 11 * m_scale, m_Y - 9 * m_scale);
	MoveToEx(hdc, m_X - 11 * m_scale, m_Y - 9 * m_scale, nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X - 9.5 * m_scale, m_Y - 13 * m_scale);
	MoveToEx(hdc, m_X + 6 * m_scale, m_Y + 1 * m_scale, nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X + 11 * m_scale, m_Y - 9 * m_scale);
	MoveToEx(hdc, m_X + 11 * m_scale, m_Y - 9 * m_scale, nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 9.5 * m_scale, m_Y - 13 * m_scale);
}

// отрисовка двигателей переданным пером и кистью
void Ship::engines(HPEN Pen, HBRUSH Brush)
{
	MoveToEx(hdc, m_X - 5 * m_scale, m_Y - 19 * m_scale, nullptr);      // установка начального значения прямой
	LineTo(hdc, m_X - 5.5 * m_scale, m_Y - 18.5 * m_scale);
	MoveToEx(hdc, m_X - 5.5 * m_scale, m_Y - 18.5 * m_scale, nullptr);  // установка начального значения прямой
	LineTo(hdc, m_X - 6.4 * m_scale, m_Y - 8 * m_scale);

	MoveToEx(hdc, m_X - 5 * m_scale, m_Y - 19 * m_scale, nullptr);      // установка начального значения прямой
	LineTo(hdc, m_X - 4.5 * m_scale, m_Y - 18.5 * m_scale);
	MoveToEx(hdc, m_X - 4.5 * m_scale, m_Y - 18.5 * m_scale, nullptr);  // установка начального значения прямой
	LineTo(hdc, m_X - 3.6 * m_scale, m_Y - 8 * m_scale);
	Ellipse(hdc, m_X - 3.5 * m_scale, m_Y - 8.2 * m_scale, m_X - 6.5 * m_scale, m_Y - 7.2 * m_scale);

	MoveToEx(hdc, m_X + 5 * m_scale, m_Y - 19 * m_scale, nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X + 5.5 * m_scale, m_Y - 18.5 * m_scale);
	MoveToEx(hdc, m_X + 5 * m_scale, m_Y - 19 * m_scale, nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X + 4.5 * m_scale, m_Y - 18.5 * m_scale);

	MoveToEx(hdc, m_X + 5.5 * m_scale, m_Y - 18.5 * m_scale, nullptr); // установка начального значения прямой
	LineTo(hdc, m_X + 6.4 * m_scale, m_Y - 8 * m_scale);
	MoveToEx(hdc, m_X + 4.5 * m_scale, m_Y - 18.5 * m_scale, nullptr); // установка начального значения прямой
	LineTo(hdc, m_X + 3.6 * m_scale, m_Y - 8 * m_scale);
	Ellipse(hdc, m_X + 3.5 * m_scale, m_Y - 8.2 * m_scale, m_X + 6.5 * m_scale, m_Y - 7.2 * m_scale);
}

// отрисовка кабины корабля заданным пером и кистью
void Ship::cabin(HPEN Pen, HBRUSH Brush)
{
	// кабина
	MoveToEx(hdc, m_X - 5 * m_scale, m_Y - 20 * m_scale, nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X - 4 * m_scale, m_Y - 23 * m_scale);
	MoveToEx(hdc, m_X + 5 * m_scale, m_Y - 20 * m_scale, nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X + 4 * m_scale, m_Y - 23 * m_scale);
	MoveToEx(hdc, m_X - 4 * m_scale, m_Y - 23 * m_scale, nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X - 3.5 * m_scale, m_Y - 26 * m_scale);
	MoveToEx(hdc, m_X + 4 * m_scale, m_Y - 23 * m_scale, nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X + 3.5 * m_scale, m_Y - 26 * m_scale);
	MoveToEx(hdc, m_X - 3.5 * m_scale, m_Y - 26 * m_scale, nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X - 2.5 * m_scale, m_Y - 28 * m_scale);
	MoveToEx(hdc, m_X + 3.5 * m_scale, m_Y - 26 * m_scale, nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X + 2.5 * m_scale, m_Y - 28 * m_scale);
	MoveToEx(hdc, m_X - 2.5 * m_scale, m_Y - 28 * m_scale, nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X - 1.7 * m_scale, m_Y - 29 * m_scale);
	MoveToEx(hdc, m_X + 2.5 * m_scale, m_Y - 28 * m_scale, nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X + 1.7 * m_scale, m_Y - 29 * m_scale);

	//нос
	MoveToEx(hdc, m_X - 1.7 * m_scale, m_Y - 29 * m_scale, nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X - 0.7 * m_scale, m_Y - 31 * m_scale);
	MoveToEx(hdc, m_X + 1.7 * m_scale, m_Y - 29 * m_scale, nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X + 0.7 * m_scale, m_Y - 31 * m_scale);
	MoveToEx(hdc, m_X - 0.7 * m_scale, m_Y - 31 * m_scale, nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X - 0 * m_scale, m_Y - 31.5 * m_scale);
	MoveToEx(hdc, m_X + 0.7 * m_scale, m_Y - 31 * m_scale, nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X + 0 * m_scale, m_Y - 31.5 * m_scale);

	// кабина
	MoveToEx(hdc, m_X - 1.4 * m_scale, m_Y - 28 * m_scale, nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X - 0.6 * m_scale, m_Y - 30 * m_scale);
	MoveToEx(hdc, m_X + 1.5 * m_scale, m_Y - 28 * m_scale, nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X + 0.6 * m_scale, m_Y - 30 * m_scale);
	MoveToEx(hdc, m_X - 0.6 * m_scale, m_Y - 30 * m_scale, nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X - 0 * m_scale, m_Y - 30.5 * m_scale);
	MoveToEx(hdc, m_X + 0.6 * m_scale, m_Y - 30 * m_scale, nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X + 0 * m_scale, m_Y - 30.5 * m_scale);
	MoveToEx(hdc, m_X - 1.4 * m_scale, m_Y - 28 * m_scale, nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X - 2.5 * m_scale, m_Y - 8 * m_scale);
	MoveToEx(hdc, m_X + 1.5 * m_scale, m_Y - 28 * m_scale, nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X + 2.5 * m_scale, m_Y - 8 * m_scale);
	MoveToEx(hdc, m_X - 2.5 * m_scale, m_Y - 8 * m_scale, nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X - 1.4 * m_scale, m_Y - 3 * m_scale);
	MoveToEx(hdc, m_X + 2.5 * m_scale, m_Y - 8 * m_scale, nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 1.5 * m_scale, m_Y - 3 * m_scale);
	LineTo(hdc, m_X + 2.5 * m_scale, m_Y - 8 * m_scale);
	MoveToEx(hdc, m_X - 1.4 * m_scale, m_Y - 3 * m_scale, nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X - 1.4 * m_scale, m_Y - 0 * m_scale);
	MoveToEx(hdc, m_X + 1.5 * m_scale, m_Y - 3 * m_scale, nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 1.5 * m_scale, m_Y - 0 * m_scale);
	
	// окна кабины
	Ellipse(hdc, m_X - 3 * m_scale, m_Y - 27 * m_scale, m_X - 2 * m_scale, m_Y - 21 * m_scale);
	Ellipse(hdc, m_X + 3 * m_scale, m_Y - 27 * m_scale, m_X + 2 * m_scale, m_Y - 21 * m_scale);

}

// показать корабль на экране. Виртуальный метод
void Ship::Show()
{
	m_Visible = true;                      //  корабль виден
	HPEN PenBlueLaguna = CreatePen(PS_SOLID, 2, RGB(37, 109, 123));
	// зададим цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(48, 213, 200));
	HPEN PenMalahit = CreatePen(PS_SOLID, 2, RGB(0, 127, 255));

	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// делаем перо PenBlueLaguna активным
	SelectObject(hdc, PenBlueLaguna);
	// отрисовка корпуса корабля заданным пером и кистью
	body(PenBlueLaguna, Brush);
	// отрисовка кабины корабля заданным пером и кистью
	cabin(PenBlueLaguna, Brush);
	// зададим тип, толщину и цвет пера
	// делаем перо PenMalahit активным
	SelectObject(hdc, PenMalahit);
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// отрисовка двигателей переданным пером и кистью
	engines(PenMalahit, Brush);

	DeleteObject(PenBlueLaguna);          // уничтожаем созданный нами объект пера PenBlueLaguna
	DeleteObject(Brush);                  // уничтожаем созданный нами объект кисти Brush
	DeleteObject(PenMalahit);             // уничтожаем созданный нами объект пера PenMalahit
}

// скрыть корабль с экрана. Виртуальный метод
void Ship::Hide()
{
	m_Visible = false;                    // корабль невиден
	// зададим тип, толщину и цвет пера
	HPEN PenBlack = CreatePen(PS_SOLID, 2, RGB(12, 12, 12));
	// зададим цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// делаем перо PenBlack активным
	SelectObject(hdc, PenBlack);
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// отрисовка двигателей переданным пером и кистью
	body(PenBlack, Brush);
	// отрисовка кабины корабля заданным пером и кистью
	cabin(PenBlack, Brush);
	engines(PenBlack, Brush);

	DeleteObject(PenBlack);               // уничтожаем созданный нами объект пера PenBlack
	DeleteObject(Brush);                  // уничтожаем созданный нами объект кисти Brush
}

// вернуть самую левую точку корабля/ сломанного корабля
double Ship::Left_Border()
{
	return (m_X - 12 * m_scale);
}

// вернуть самую правую точку корабля/ сломанного корабля
double Ship::Right_Border()
{
	return (m_X + 12 * m_scale);
}

// вернуть самую верхнюю точку корабля/ сломанного корабля
double Ship::High_Border()
{
	return (m_Y + 1.5 * m_scale);
}

// вернуть самую нижнюю точку корабля/ сломанного корабля
double Ship::Low_Border()
{
	return (m_Y - 31.5 * m_scale);
}


/*------------------------------------------------------------------------*/
/*              Broke_Ship                */
/*----------------------------------------*/

// производный класс Сломанный Корабль от Ship и по определению от Point и Location. Производный от интерфейса IShip
// для инициализации старых полей используем конструктор предка
Broke_Ship::Broke_Ship(double InitX, double InitY) : Ship(InitX, InitY) 
{
	m_scale = 6;               // размер. Параметр для отрисовки объекта
	s_number = 1;              // номер. Параметр для матрицы переходов кораблей. Меняется в конструкторе
}

// деструктор
Broke_Ship:: ~Broke_Ship()
{
	// пустое тело
}

// отрисовка двигателей переданным пером и кистью
void Broke_Ship::engines(HPEN Pen, HBRUSH Brush)
{
	MoveToEx(hdc, m_X - 5 * GetScale(), m_Y - 19 * GetScale(), nullptr);      // установка начального значения прямой
	LineTo(hdc, m_X - 5.5 * GetScale(), m_Y - 18.5 * GetScale());
	MoveToEx(hdc, m_X - 5.5 * GetScale(), m_Y - 18.5 * GetScale(), nullptr);  // установка начального значения прямой
	LineTo(hdc, m_X - 6.4 * GetScale(), m_Y - 8 * GetScale());

	MoveToEx(hdc, m_X - 5 * GetScale(), m_Y - 19 * GetScale(), nullptr);      // установка начального значения прямой
	LineTo(hdc, m_X - 4.5 * GetScale(), m_Y - 18.5 * GetScale());
	MoveToEx(hdc, m_X - 4.5 * GetScale(), m_Y - 18.5 * GetScale(), nullptr);  // установка начального значения прямой
	LineTo(hdc, m_X - 3.6 * GetScale(), m_Y - 8 * GetScale());
	Ellipse(hdc, m_X - 3.5 * GetScale(), m_Y - 8.2 * GetScale(), m_X - 6.5 * GetScale(), m_Y - 7.2 * GetScale());
}

// показать сломанный корабль на экране. Виртуальный метод
void Broke_Ship::Show()
{
	m_Visible = true;           // сломанный корабль виден
	// зададим тип, толщину и цвет пера
	HPEN PenBlueLaguna = CreatePen(PS_SOLID, 2, RGB(37, 109, 123));
	// зададим цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(48, 213, 200));
	HPEN PenBlack = CreatePen(PS_SOLID, 2, RGB(12, 12, 12));
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// делаем перо PenBlueLaguna активным
	SelectObject(hdc, PenBlueLaguna);
	// отрисовка корпуса корабля заданным пером и кистью
	body(PenBlueLaguna, Brush);
	engines(PenBlueLaguna, Brush);
	// отрисовка кабины корабля заданным пером и кистью
	cabin(PenBlueLaguna, Brush);

	// Завершение рисования
	DeleteObject(PenBlack);       // уничтожаем созданный нами объект пера PenBlueLaguna
	DeleteObject(PenBlueLaguna);  // уничтожаем созданный нами объект пера PenBlueLaguna
	DeleteObject(Brush);          // уничтожаем созданный нами объект кисти Brush
}

// скрыть сломанный корабль с экрана. Виртуальный метод
void Broke_Ship::Hide()
{
	m_Visible = false;            // сломанный корабль невиден
	// зададим тип, толщину и цвет пера
	HPEN PenBlack = CreatePen(PS_SOLID, 2, RGB(12, 12, 12));
	// зададим цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// делаем перо PenBlack активным
	SelectObject(hdc, PenBlack);
	// отрисовка корпуса корабля заданным пером и кистью
	body(PenBlack, Brush);
	// отрисовка кабины корабля заданным пером и кистью
	cabin(PenBlack, Brush);
	engines(PenBlack, Brush);

	// Завершение рисования
	DeleteObject(PenBlack);        // уничтожаем созданный нами объект пера PenBlueLaguna
	DeleteObject(Brush);           // уничтожаем созданный нами объект кисти Brush
}


/*------------------------------------------------------------------------*/
/*             Infinity_Ship              */
/*----------------------------------------*/

// производный класс Бесконечный Корабль от  Ship и по определению от Point и Location. Производный от интерфейса IShip
Infinity_Ship::Infinity_Ship(double InitX, double InitY) : Ship(InitX, InitY)
{
	m_scale = 5;               // размер. Параметр для отрисовки объекта
	s_number = 2;              // номер. Параметр для матрицы переходов кораблей. Меняется в конструкторе
}

// деструктор
Infinity_Ship:: ~Infinity_Ship()
{
	// пустое тело
}

// отрисовка двигателей
void Infinity_Ship::engines(HPEN Pen, HBRUSH Brush)
{
	MoveToEx(hdc, m_X - 2 * GetScale(), m_Y - 31 * GetScale(), nullptr);      // установка начального значения прямой
	LineTo(hdc, m_X - 0.2 * GetScale(), m_Y - 31.5 * GetScale());

	MoveToEx(hdc, m_X - 0.2 * GetScale(), m_Y - 31.5 * GetScale(), nullptr);  // установка начального значения прямой
	LineTo(hdc, m_X + 0.2 * GetScale(), m_Y - 31.5 * GetScale());

	MoveToEx(hdc, m_X + 0.2 * GetScale(), m_Y - 31.5 * GetScale(), nullptr);  // установка начального значения прямой
	LineTo(hdc, m_X + 2.1 * GetScale(), m_Y - 31 * GetScale());


	MoveToEx(hdc, m_X - 2 * GetScale(), m_Y - 31 * GetScale(), nullptr);      // установка начального значения прямой
	LineTo(hdc, m_X - 1 * GetScale(), m_Y - 33 * GetScale());

	MoveToEx(hdc, m_X + 2.1 * GetScale(), m_Y - 31 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 1.1 * GetScale(), m_Y - 33 * GetScale());

	MoveToEx(hdc, m_X - 1 * GetScale(), m_Y - 33 * GetScale(), nullptr);      // установка начального значения прямой
	LineTo(hdc, m_X - 0.1 * GetScale(), m_Y - 34 * GetScale());

	MoveToEx(hdc, m_X + 1.1 * GetScale(), m_Y - 33 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 0.2 * GetScale(), m_Y - 34 * GetScale());

	MoveToEx(hdc, m_X - 0.1 * GetScale(), m_Y - 34 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 0.2 * GetScale(), m_Y - 34 * GetScale());

	// линии на корабле
	MoveToEx(hdc, m_X - 1.2 * GetScale(), m_Y - 8.5 * GetScale(), nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X - 0.5 * GetScale(), m_Y - 6.5 * GetScale());

	MoveToEx(hdc, m_X + 1.2 * GetScale(), m_Y - 8.5 * GetScale(), nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X + 0.5 * GetScale(), m_Y - 6.5 * GetScale());

	MoveToEx(hdc, m_X - 0.5 * GetScale(), m_Y - 6.5 * GetScale(), nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X - 0 * GetScale(), m_Y - 6 * GetScale());

	MoveToEx(hdc, m_X - 0 * GetScale(), m_Y - 6 * GetScale(), nullptr);       // установка начального значения прямой
	LineTo(hdc, m_X + 0.5 * GetScale(), m_Y - 6.5 * GetScale());

	MoveToEx(hdc, m_X - 2 * GetScale(), m_Y - 7.5 * GetScale(), nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X - 0.5 * GetScale(), m_Y - 3 * GetScale());

	MoveToEx(hdc, m_X + 2 * GetScale(), m_Y - 7.5 * GetScale(), nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X + 0.5 * GetScale(), m_Y - 3 * GetScale());

	MoveToEx(hdc, m_X - 0.5 * GetScale(), m_Y - 3 * GetScale(), nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X - 0.1 * GetScale(), m_Y - 2.5 * GetScale());

	MoveToEx(hdc, m_X + 0.5 * GetScale(), m_Y - 3 * GetScale(), nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X + 0.1 * GetScale(), m_Y - 2.5 * GetScale());

	// боковые линии
	// левая
	MoveToEx(hdc, m_X - 4.8 * GetScale(), m_Y - 2.5 * GetScale(), nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X - 3.7 * GetScale(), m_Y - 1.5 * GetScale());

	MoveToEx(hdc, m_X - 3.7 * GetScale(), m_Y - 1.5 * GetScale(), nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X - 3.1 * GetScale(), m_Y - 0.5 * GetScale());

	MoveToEx(hdc, m_X - 3.1 * GetScale(), m_Y - 0.5 * GetScale(), nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X - 2.7 * GetScale(), m_Y + 0.5 * GetScale());

	// правая
	MoveToEx(hdc, m_X + 4.8 * GetScale(), m_Y - 2.5 * GetScale(), nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X + 3.7 * GetScale(), m_Y - 1.5 * GetScale());

	MoveToEx(hdc, m_X + 3.7 * GetScale(), m_Y - 1.5 * GetScale(), nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X + 3.1 * GetScale(), m_Y - 0.5 * GetScale());

	MoveToEx(hdc, m_X + 3.1 * GetScale(), m_Y - 0.5 * GetScale(), nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X + 2.7 * GetScale(), m_Y + 0.5 * GetScale());

	// левое крыло
	MoveToEx(hdc, m_X - 10.5 * GetScale(), m_Y - 8.5 * GetScale(), nullptr);  // установка начального значения прямой
	LineTo(hdc, m_X - 11 * GetScale(), m_Y - 6.5 * GetScale());

	MoveToEx(hdc, m_X - 11 * GetScale(), m_Y - 6.5 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X - 10.8 * GetScale(), m_Y - 6 * GetScale());

	MoveToEx(hdc, m_X - 10.8 * GetScale(), m_Y - 6 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X - 10.3 * GetScale(), m_Y - 4.5 * GetScale());


	MoveToEx(hdc, m_X - 9.5 * GetScale(), m_Y - 9 * GetScale(), nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X - 10 * GetScale(), m_Y - 6.5 * GetScale());

	MoveToEx(hdc, m_X - 10 * GetScale(), m_Y - 6.5 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X - 9.8 * GetScale(), m_Y - 6 * GetScale());

	MoveToEx(hdc, m_X - 9.8 * GetScale(), m_Y - 6 * GetScale(), nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X - 9.3 * GetScale(), m_Y - 4.5 * GetScale());

	// правое крыло
	MoveToEx(hdc, m_X + 10.5 * GetScale(), m_Y - 8.5 * GetScale(), nullptr);  // установка начального значения прямой
	LineTo(hdc, m_X + 11 * GetScale(), m_Y - 6.5 * GetScale());

	MoveToEx(hdc, m_X + 11 * GetScale(), m_Y - 6.5 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 10.8 * GetScale(), m_Y - 6 * GetScale());

	MoveToEx(hdc, m_X + 10.8 * GetScale(), m_Y - 6 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 10.3 * GetScale(), m_Y - 4.5 * GetScale());


	MoveToEx(hdc, m_X + 9.5 * GetScale(), m_Y - 9 * GetScale(), nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X + 10 * GetScale(), m_Y - 6.5 * GetScale());

	MoveToEx(hdc, m_X + 10 * GetScale(), m_Y - 6.5 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 9.8 * GetScale(), m_Y - 6 * GetScale());

	MoveToEx(hdc, m_X + 9.8 * GetScale(), m_Y - 6 * GetScale(), nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X + 9.3 * GetScale(), m_Y - 4.5 * GetScale());
}

// отрисовка корпуса корабля
void Infinity_Ship::body(HPEN Pen, HBRUSH Brush)
{
	// низ ракеты
	MoveToEx(hdc, m_X - 5 * GetScale(), m_Y + 1 * GetScale(), nullptr);       // установка начального значения прямой
	LineTo(hdc, m_X + 5 * GetScale(), m_Y + 1 * GetScale());

	MoveToEx(hdc, m_X - 5 * GetScale(), m_Y + 1 * GetScale(), nullptr);       // установка начального значения прямой
	LineTo(hdc, m_X - 6 * GetScale(), m_Y - 0 * GetScale());

	MoveToEx(hdc, m_X + 5 * GetScale(), m_Y + 1 * GetScale(), nullptr);       // установка начального значения прямой
	LineTo(hdc, m_X + 6 * GetScale(), m_Y - 0 * GetScale());

	MoveToEx(hdc, m_X - 6 * GetScale(), m_Y - 0 * GetScale(), nullptr);       // установка начального значения прямой
	LineTo(hdc, m_X - 6 * GetScale(), m_Y - 0.5 * GetScale());

	MoveToEx(hdc, m_X + 6 * GetScale(), m_Y - 0 * GetScale(), nullptr);       // установка начального значения прямой
	LineTo(hdc, m_X + 6 * GetScale(), m_Y - 0.5 * GetScale());

	MoveToEx(hdc, m_X - 6 * GetScale(), m_Y - 0.5 * GetScale(), nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X - 5.5 * GetScale(), m_Y - 1.5 * GetScale());

	MoveToEx(hdc, m_X + 6 * GetScale(), m_Y - 0.5 * GetScale(), nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X + 5.5 * GetScale(), m_Y - 1.5 * GetScale());

	MoveToEx(hdc, m_X - 5.5 * GetScale(), m_Y - 1.5 * GetScale(), nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X - 3.8 * GetScale(), m_Y - 5 * GetScale());

	MoveToEx(hdc, m_X - 3.8 * GetScale(), m_Y - 5 * GetScale(), nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X - 1 * GetScale(), m_Y - 9 * GetScale());

	MoveToEx(hdc, m_X + 5.5 * GetScale(), m_Y - 1.5 * GetScale(), nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X + 3.8 * GetScale(), m_Y - 5 * GetScale());

	MoveToEx(hdc, m_X + 3.8 * GetScale(), m_Y - 5 * GetScale(), nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X + 1 * GetScale(), m_Y - 9 * GetScale());

	MoveToEx(hdc, m_X - 1 * GetScale(), m_Y - 9 * GetScale(), nullptr);       // установка начального значения прямой
	LineTo(hdc, m_X - 0.1 * GetScale(), m_Y - 10 * GetScale());

	MoveToEx(hdc, m_X + 1 * GetScale(), m_Y - 9 * GetScale(), nullptr);       // установка начального значения прямой
	LineTo(hdc, m_X + 0.3 * GetScale(), m_Y - 10 * GetScale());

	MoveToEx(hdc, m_X - 0.1 * GetScale(), m_Y - 10 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 0.2 * GetScale(), m_Y - 10 * GetScale());

	// линия внизу
	MoveToEx(hdc, m_X - 5 * GetScale(), m_Y + 0.3 * GetScale(), nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X + 5 * GetScale(), m_Y + 0.3 * GetScale());

	MoveToEx(hdc, m_X - 5 * GetScale(), m_Y + 0.3 * GetScale(), nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X - 6 * GetScale(), m_Y - 0.7 * GetScale());

	MoveToEx(hdc, m_X + 5 * GetScale(), m_Y + 0.3 * GetScale(), nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X + 6 * GetScale(), m_Y - 0.7 * GetScale());


	// корпус ракеты
	MoveToEx(hdc, m_X - 2.7 * GetScale(), m_Y - 7 * GetScale(), nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X - 4.3 * GetScale(), m_Y - 12 * GetScale());

	MoveToEx(hdc, m_X + 2.7 * GetScale(), m_Y - 7 * GetScale(), nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X + 4.4 * GetScale(), m_Y - 12 * GetScale());

	MoveToEx(hdc, m_X - 4.3 * GetScale(), m_Y - 12 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X - 5 * GetScale(), m_Y - 15 * GetScale());

	MoveToEx(hdc, m_X + 4.4 * GetScale(), m_Y - 12 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 5 * GetScale(), m_Y - 15 * GetScale());

	MoveToEx(hdc, m_X - 5 * GetScale(), m_Y - 15 * GetScale(), nullptr);      // установка начального значения прямой
	LineTo(hdc, m_X - 4.8 * GetScale(), m_Y - 19 * GetScale());

	MoveToEx(hdc, m_X + 5 * GetScale(), m_Y - 15 * GetScale(), nullptr);      // установка начального значения прямой
	LineTo(hdc, m_X + 4.9 * GetScale(), m_Y - 19 * GetScale());

	MoveToEx(hdc, m_X - 4.8 * GetScale(), m_Y - 19 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X - 4 * GetScale(), m_Y - 25 * GetScale());

	MoveToEx(hdc, m_X + 4.9 * GetScale(), m_Y - 19 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 4.1 * GetScale(), m_Y - 25 * GetScale());

	MoveToEx(hdc, m_X - 4 * GetScale(), m_Y - 25 * GetScale(), nullptr);      // установка начального значения прямой
	LineTo(hdc, m_X - 3 * GetScale(), m_Y - 29 * GetScale());

	MoveToEx(hdc, m_X + 4.1 * GetScale(), m_Y - 25 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 3.1 * GetScale(), m_Y - 29 * GetScale());

	MoveToEx(hdc, m_X - 3 * GetScale(), m_Y - 29 * GetScale(), nullptr);      // установка начального значения прямой
	LineTo(hdc, m_X - 2 * GetScale(), m_Y - 31 * GetScale());

	MoveToEx(hdc, m_X + 3.1 * GetScale(), m_Y - 29 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 2.1 * GetScale(), m_Y - 31 * GetScale());

	// линии
	MoveToEx(hdc, m_X - 1.7 * GetScale(), m_Y - 7 * GetScale(), nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X - 3.3 * GetScale(), m_Y - 12 * GetScale());

	MoveToEx(hdc, m_X + 1.7 * GetScale(), m_Y - 7 * GetScale(), nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X + 3.4 * GetScale(), m_Y - 12 * GetScale());

	MoveToEx(hdc, m_X - 3.3 * GetScale(), m_Y - 12 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X - 4 * GetScale(), m_Y - 15 * GetScale());

	MoveToEx(hdc, m_X + 3.4 * GetScale(), m_Y - 12 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 4 * GetScale(), m_Y - 15 * GetScale());

	MoveToEx(hdc, m_X - 4 * GetScale(), m_Y - 15 * GetScale(), nullptr);      // установка начального значения прямой
	LineTo(hdc, m_X - 3.8 * GetScale(), m_Y - 19 * GetScale());

	MoveToEx(hdc, m_X + 4 * GetScale(), m_Y - 15 * GetScale(), nullptr);      // установка начального значения прямой
	LineTo(hdc, m_X + 3.9 * GetScale(), m_Y - 19 * GetScale());

	MoveToEx(hdc, m_X - 3.8 * GetScale(), m_Y - 19 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X - 3 * GetScale(), m_Y - 25 * GetScale());

	MoveToEx(hdc, m_X + 3.9 * GetScale(), m_Y - 19 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 3.1 * GetScale(), m_Y - 25 * GetScale());

	MoveToEx(hdc, m_X - 3 * GetScale(), m_Y - 25 * GetScale(), nullptr);      // установка начального значения прямой
	LineTo(hdc, m_X - 2 * GetScale(), m_Y - 29 * GetScale());

	MoveToEx(hdc, m_X + 3.1 * GetScale(), m_Y - 25 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 2.1 * GetScale(), m_Y - 29 * GetScale());

	MoveToEx(hdc, m_X - 2 * GetScale(), m_Y - 29 * GetScale(), nullptr);      // установка начального значения прямой
	LineTo(hdc, m_X - 1 * GetScale(), m_Y - 31 * GetScale());

	MoveToEx(hdc, m_X + 2.1 * GetScale(), m_Y - 29 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 1.1 * GetScale(), m_Y - 31 * GetScale());

	// боковые части корпуса
	MoveToEx(hdc, m_X - 4.5 * GetScale(), m_Y - 12 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X - 12 * GetScale(), m_Y - 8 * GetScale());

	MoveToEx(hdc, m_X + 4.5 * GetScale(), m_Y - 12 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 12 * GetScale(), m_Y - 8 * GetScale());

	MoveToEx(hdc, m_X - 4.2 * GetScale(), m_Y - 5 * GetScale(), nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X - 12 * GetScale(), m_Y - 4 * GetScale());

	MoveToEx(hdc, m_X - 12 * GetScale(), m_Y - 8 * GetScale(), nullptr);      // установка начального значения прямой
	LineTo(hdc, m_X - 12.3 * GetScale(), m_Y - 6 * GetScale());

	MoveToEx(hdc, m_X - 12.3 * GetScale(), m_Y - 6 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X - 12 * GetScale(), m_Y - 4 * GetScale());

	MoveToEx(hdc, m_X + 4.2 * GetScale(), m_Y - 5 * GetScale(), nullptr);     // установка начального значения прямой
	LineTo(hdc, m_X + 12 * GetScale(), m_Y - 4 * GetScale());

	MoveToEx(hdc, m_X + 12 * GetScale(), m_Y - 8 * GetScale(), nullptr);      // установка начального значения прямой
	LineTo(hdc, m_X + 12.4 * GetScale(), m_Y - 6 * GetScale());

	MoveToEx(hdc, m_X + 12.4 * GetScale(), m_Y - 6 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 12 * GetScale(), m_Y - 4 * GetScale());

	// двигатели
	MoveToEx(hdc, m_X - 11.6 * GetScale(), m_Y - 8 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X - 12.6 * GetScale(), m_Y - 11 * GetScale());

	MoveToEx(hdc, m_X - 11.9 * GetScale(), m_Y - 4 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X - 12.6 * GetScale(), m_Y - 2 * GetScale());

	MoveToEx(hdc, m_X - 12.6 * GetScale(), m_Y - 2 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X - 13.5 * GetScale(), m_Y - 2 * GetScale());

	MoveToEx(hdc, m_X - 13.5 * GetScale(), m_Y - 2 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X - 14.5 * GetScale(), m_Y - 6 * GetScale());

	MoveToEx(hdc, m_X - 14.5 * GetScale(), m_Y - 6 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X - 14 * GetScale(), m_Y - 10.5 * GetScale());

	MoveToEx(hdc, m_X - 14 * GetScale(), m_Y - 10.5 * GetScale(), nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X - 13.5 * GetScale(), m_Y - 11.5 * GetScale());

	MoveToEx(hdc, m_X - 13.5 * GetScale(), m_Y - 11.5 * GetScale(), nullptr); // установка начального значения прямой
	LineTo(hdc, m_X - 13 * GetScale(), m_Y - 11.5 * GetScale());

	MoveToEx(hdc, m_X - 12.6 * GetScale(), m_Y - 11 * GetScale(), nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X - 13 * GetScale(), m_Y - 11.5 * GetScale());

	MoveToEx(hdc, m_X + 11.7 * GetScale(), m_Y - 8.1 * GetScale(), nullptr);  // установка начального значения прямой
	LineTo(hdc, m_X + 12.6 * GetScale(), m_Y - 11 * GetScale());

	MoveToEx(hdc, m_X + 11.9 * GetScale(), m_Y - 4 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 12.6 * GetScale(), m_Y - 2 * GetScale());

	MoveToEx(hdc, m_X + 12.6 * GetScale(), m_Y - 2 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 13.5 * GetScale(), m_Y - 2 * GetScale());

	MoveToEx(hdc, m_X + 12.6 * GetScale(), m_Y - 11 * GetScale(), nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X + 12.9 * GetScale(), m_Y - 11.5 * GetScale());

	MoveToEx(hdc, m_X + 13.5 * GetScale(), m_Y - 2 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 14.5 * GetScale(), m_Y - 6 * GetScale());

	MoveToEx(hdc, m_X + 14.5 * GetScale(), m_Y - 6 * GetScale(), nullptr);    // установка начального значения прямой
	LineTo(hdc, m_X + 14 * GetScale(), m_Y - 10.5 * GetScale());

	MoveToEx(hdc, m_X + 14 * GetScale(), m_Y - 10.5 * GetScale(), nullptr);   // установка начального значения прямой
	LineTo(hdc, m_X + 13.5 * GetScale(), m_Y - 11.5 * GetScale());

	MoveToEx(hdc, m_X + 13.5 * GetScale(), m_Y - 11.5 * GetScale(), nullptr); // установка начального значения прямой
	LineTo(hdc, m_X + 13 * GetScale(), m_Y - 11.5 * GetScale());
}

// отрисовка кабины корабля
void Infinity_Ship::cabin(HPEN Pen, HBRUSH Brush)
{
	Ellipse(hdc, m_X - 1.9 * m_scale, m_Y - 27 * m_scale, m_X + 2.5 * m_scale, m_Y - 15 * m_scale);

	Ellipse(hdc, m_X - 13.5 * m_scale, m_Y - 2 * m_scale, m_X - 12.5 * m_scale, m_Y - 1 * m_scale);

	Ellipse(hdc, m_X + 13.5 * m_scale, m_Y - 2 * m_scale, m_X + 12.5 * m_scale, m_Y - 1 * m_scale);
}

// показать бесконечный корабль на экране. Виртуальный метод
void Infinity_Ship::Show()
{
	m_Visible = true;           // бесконечный корабль виден
	// зададим тип, толщину и цвет пера
	HPEN PenPurple = CreatePen(PS_SOLID, 2, RGB(115, 102, 189));
	HPEN PenOrange = CreatePen(PS_SOLID, 2, RGB(195, 118, 41));
	HPEN PenBlue = CreatePen(PS_SOLID, 2, RGB(48, 213, 200));
	// зададим цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(48, 213, 200));
	// делаем перо PenPurple активным
	SelectObject(hdc, PenPurple);
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// отрисовка корпуса бесконечного корабля заданным пером и кистью
	body(PenPurple, Brush);
	SelectObject(hdc, PenBlue);
	cabin(PenPurple, Brush);
	SelectObject(hdc, PenOrange);
	engines(PenOrange, Brush);

	// Завершение рисования
	DeleteObject(PenBlue);       // уничтожаем созданный нами объект пера PenPurple
	DeleteObject(PenPurple);     // уничтожаем созданный нами объект пера PenPurple
	DeleteObject(PenOrange);     // уничтожаем созданный нами объект пера PenPurple
	DeleteObject(Brush);         // уничтожаем созданный нами объект кисти Brush
}

// скрыть бесконечный корабль с экрана. Виртуальный метод
void Infinity_Ship::Hide()
{
	m_Visible = false;           // бесконечный корабль не виден
	// зададим тип, толщину и цвет пера
	HPEN PenBlack = CreatePen(PS_SOLID, 2, RGB(12, 12, 12));
	// зададим цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// делаем перо PenBlack активным
	SelectObject(hdc, PenBlack);
	// отрисовка корпуса корабля заданным пером и кистью
	body(PenBlack, Brush);
	cabin(PenBlack, Brush);
	SelectObject(hdc, PenBlack);
	engines(PenBlack, Brush);

	// Завершение рисования
	DeleteObject(PenBlack);      // уничтожаем созданный нами объект пера PenBlueLaguna
	DeleteObject(Brush);         // уничтожаем созданный нами объект кисти Brush
}

// вернуть самую левую точку фигуры бесконечного корабля
double Infinity_Ship::Left_Border()
{
	return (m_X - 14.7 * GetScale());
}

// вернуть самую правую точку фигуры бесконечного корабля
double Infinity_Ship::Right_Border()
{
	return(m_X + 14.7 * GetScale());
}

// вернуть самую верхнюю точку фигуры бесконечного корабля
double Infinity_Ship::High_Border()
{
	return(m_Y + 1 * GetScale());
}

// вернуть самую нижнюю точку фигуры корабля
double Infinity_Ship::Low_Border()
{
	return(m_Y - 36 * GetScale());
}




/*------------------------------------------------------------------------------------------------------*/
/*              Пули            */
/*------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
/*        Абстрактный базовый класс       */
/*----------------------------------------*/

ABullet::ABullet(int Initcaliber)    // конструктор 
{
	m_caliber = Initcaliber;         // значение калибра пули
}

ABullet::~ABullet()                  // деструктор
{
	// пустое тело
}

int ABullet::GetCaliber() const      // константный геттер для получения значения размера
{
	return (m_caliber);              // вернуть значение калибра
}


/*------------------------------------------------------------------------------------------------------*/
/*              Обычная пуля           */
/*-------------------------------------*/

// производный класс Пуля от Point и по определению от Location. И ABullet
// конструктор
Bullet::Bullet(double InitX, double InitY) : Point(InitX, InitY), ABullet(10)
{
	m_scale = 0;                 // присвоили полю значение
}

// деструктор
Bullet::~Bullet()
{
	// пустое тело
}

// получить значение номера пули
int Bullet::GetScale()const
{
	return(m_scale);
}

// установить принудительно значение номера пули
void Bullet::SetScale(int NewScale)
{
	m_scale = NewScale;
}

// Для принудительной реализации из абстрактного базового класса
// сеттер для принудительной установки значения размера
void Bullet::SetCaliber(int NewCaliber)
{
	m_caliber = NewCaliber;
}

// показать обычную пулю на экране. Виртуальный метод
void Bullet::Show()
{
	// зададим тип, толщину и цвет пера
	HPEN PenWhite = CreatePen(PS_SOLID, 5, RGB(255, 250, 250));
	// верхняя граница консоли для пули с учётом длины калибра - пуля не вылетела за консоль
	if (HighBorderBullet <= GetY() - GetCaliber())
	{
		m_Visible = true;              // пуля видна на экране
		// делаем перо PenWhite активным
		SelectObject(hdc, PenWhite);
		// установка начального значения прямой
		MoveToEx(hdc, m_X, m_Y, nullptr);
		// установка конечного значения прямой
		LineTo(hdc, m_X, m_Y + 1 * m_caliber);
	}
	// иначе - вышли за пределы консоли. Скрываем пулю
	else
	{
		Hide();
	}

	DeleteObject(PenWhite);            // уничтожаем созданный нами объект пера PenWhite
}

// скрыть пулю с экрана. Виртуальный метод
void Bullet::Hide()
{
	m_Visible = false;                  // пуля не видна на экране
	// зададим тип, толщину и цвет пера
	HPEN PenBlack = CreatePen(PS_SOLID, 5, RGB(12, 12, 12));
	// делаем перо PenBlack активным
	SelectObject(hdc, PenBlack);
	// установка начального значения прямой
	MoveToEx(hdc, m_X, m_Y, nullptr);
	// установка конечного значения прямой
	LineTo(hdc, m_X, m_Y + 1.5 * m_caliber);

	DeleteObject(PenBlack);             // уничтожаем созданный нами объект пера PenBlack
}


/*------------------------------------------------------------------------------------------------------*/
/*            Желтая  пуля             */
/*-------------------------------------*/

// производный класс Желтая пуля от обычной пули и по определению от Point и Location. И ABullet
// Калибр. Параметр для отрисовки объекта. Меняется в конструкторе
// Номер. Параметр для матрицы. Меняется в конструкторе
Yellow_Bullet::Yellow_Bullet(double InitX, double InitY) : Bullet(InitX, InitY)
{
	m_scale = 1;
	m_caliber = 30;
}

// деструктор
Yellow_Bullet:: ~Yellow_Bullet()
{
	// пустое тело
}

// показать жёлтую пулю на экране. Виртуальный метод
void Yellow_Bullet::Show()
{
	// зададим тип, толщину и цвет пера
	HPEN PenYellow = CreatePen(PS_SOLID, 5, RGB(253, 233, 16));
	// верхняя граница консоли для пули с учётом длины калибра - пуля не вылетела за консоль
	if (HighBorderBullet <= GetY() - GetCaliber())
	{
		m_Visible = true;                // пуля видна на экране
		// делаем перо PenYellow активным
		SelectObject(hdc, PenYellow);
		// установка начального значения прямой
		MoveToEx(hdc, m_X, m_Y, nullptr);
		// установка конечного значения прямой
		LineTo(hdc, m_X, m_Y + 1 * m_caliber);
	}
	// иначе - вышли за пределы консоли. Скрываем пулю. Вызываем метод с уровня предка с использованием поля m_caliber текущего уровня
	else
	{
		Hide();
	}

	DeleteObject(PenYellow);             // уничтожаем созданный нами объект пера PenYellow
}


/*------------------------------------------------------------------------------------------------------*/
/*            Красная  пуля            */
/*-------------------------------------*/

// производный класс Красная пуля от обычной пули и по определению от Point и Location. И ABullet
// поле m_caliber используется родительское. Меняется в конструкторе
// Номер. Параметр для матрицы. Меняется в конструкторе
Red_Bullet::Red_Bullet(double InitX, double InitY) : Bullet(InitX, InitY)
{
	acceleration = 15;
	m_scale = 2;
	m_caliber = 10;
	SetCaliber(acceleration + GetCaliber());
}

// деструктор
Red_Bullet:: ~Red_Bullet()
{
	// пустое тело
};

// константный геттер для получения значения ускорения
int Red_Bullet::GetAcceleration() const
{
	return (acceleration);
}

// сеттер для установки значения ускорения
void Red_Bullet::SetAcceleration(int NewAcceleration)
{
	acceleration = NewAcceleration;
}

// показать красную пулю на экране. Виртуальный метод
void Red_Bullet::Show()
{
	// зададим тип, толщину и цвет пера
	HPEN PenRed = CreatePen(PS_SOLID, 5, RGB(255, 36, 0));
	// верхняя граница консоли для пули с учётом длины калибра - пуля не вылетела за консоль
	if (HighBorderBullet <= GetY() - GetCaliber())
	{
		m_Visible = true;                  // пуля видна на экране
		// делаем перо PenRed активным
		SelectObject(hdc, PenRed);
		// установка начального значения прямой
		MoveToEx(hdc, m_X, m_Y, nullptr);
		// установка конечного значения прямой
		LineTo(hdc, m_X, m_Y + acceleration);
	}
	// иначе - вышли за пределы консоли. Скрываем пулю. Вызываем метод с уровня предка с использованием поля m_caliber текущего уровня
	else
	{
		Hide();
	}

	DeleteObject(PenRed);             // уничтожаем созданный нами объект пера PenRed
}


/*------------------------------------------------------------------------------------------------------*/
/*            Зелёная  пуля            */
/*-------------------------------------*/

// производный класс Зелёная пуля от обычной пули и по определению от Point и Location. И ABullet
// поле m_caliber используется родительское. Меняется в конструкторе
// Номер. Параметр для матрицы. Меняется в конструкторе
Green_Bullet::Green_Bullet(double InitX, double InitY) : Bullet(InitX, InitY)
{
	freeze = 0;
	m_scale = 3;
	m_caliber = 10;
}

// деструктор
Green_Bullet:: ~Green_Bullet()
{
	// пустое тело
};

// константный геттер для текущего значения торможения
int Green_Bullet::GetFreeze() const
{
	return (freeze);
}

// сеттер для принудительно установки текущего значения торможения
void Green_Bullet::Setfreeze(int NewFreeze)
{
	freeze = NewFreeze;
}

// показать зелёную пулю на экране. Виртуальный метод
void Green_Bullet::Show()
{
	// зададим тип, толщину и цвет пера
	HPEN PenMalahit = CreatePen(PS_SOLID, 5, RGB(52, 201, 36));
	// верхняя граница консоли для пули с учётом длины калибра - пуля не вылетела за консоль и количество шагов пули <=15
	if ((HighBorderBullet <= GetY() - GetCaliber()) && (freeze <= 15))
	{
		freeze = freeze + 1;        // увеличить счётчик шагов
		m_Visible = true;           // зелёная пуля видна на экране
		// делаем перо PenMalahit активным
		SelectObject(hdc, PenMalahit);
		// установка начального значения прямой
		MoveToEx(hdc, m_X, m_Y, nullptr);
		// установка конечного значения прямой
		LineTo(hdc, m_X, m_Y + 1.5 * m_caliber);
	}
	// иначе - вышли за пределы консоли или набрали нужное количество шагов для остановки. Скрываем пулю. Вызываем метод с уровня предка с использованием поля m_caliber текущего уровня
	else
	{
		Hide();
		freeze = 0;                 // обнуляем счётчик шагов
	}

	DeleteObject(PenMalahit);       // уничтожаем созданный нами объект пера PenRed
}


/*------------------------------------------------------------------------------------------------------*/
/*            Синяя  пуля            */
/*-----------------------------------*/

// производный класс Синяя пуля от  Зелёная пуля от и по определению от обычной пули и Point и Location
// конструктор
// используется поле родителя
Blue_Bullet::Blue_Bullet(double InitX, double InitY) : Green_Bullet(InitX, InitY)
{
	freeze = 0;
	m_scale = 4;
	m_caliber = 10;
}

// деструктор
Blue_Bullet::~Blue_Bullet()
{
	// пустое тело
}

// виртуальные функции
void Blue_Bullet::Show()            // показать синюю пулю на экране. Виртуальный метод
{
	// зададим тип, толщину и цвет пера
	HPEN PenEgg = CreatePen(PS_SOLID, 5, RGB(0, 204, 204));
	// верхняя граница консоли для пули с учётом длины калибра - пуля не вылетела за консоль и количество шагов пули <=20
	if ((HighBorderBullet <= GetY() - GetCaliber()) && (freeze <= 10))
	{
		freeze = freeze + 1;        // увеличить счётчик шагов
		m_Visible = true;           // синяя пуля видна на экране
		// делаем перо PenEgg активным
		SelectObject(hdc, PenEgg);
		// установка начального значения прямой
		MoveToEx(hdc, m_X, m_Y, nullptr);
		// установка конечного значения прямой
		LineTo(hdc, m_X, m_Y + 1 * m_caliber);
	}
	// иначе - вышли за пределы консоли или набрали нужное количество шагов для остановки. Скрываем пулю. Вызываем метод с уровня предка с использованием поля m_caliber текущего уровня
	else
	{
		Hide();
		freeze = 0;                 // обнуляем счётчик шагов
	}

	DeleteObject(PenEgg);           // уничтожаем созданный нами объект пера PenEgg
}




/*------------------------------------------------------------------------------------------------------*/
/*              Бомбы           */
/*------------------------------*/

/*------------------------------------------------------------------------*/
/*        Абстрактный базовый класс       */
/*----------------------------------------*/

// конструктор с передачей значения радиуса и ускорения
ABomb::ABomb(double InitRadius, int InitExtraSpeed)
{
	m_radius = InitRadius;                             // установили значение радиуса
	extra_speed = InitExtraSpeed;                      // установили значение ускорения
}

// деструктор
ABomb::	~ABomb()                                       
{
	// пустое тело
}

// константный геттер для получения значения радиуса
double ABomb::GetRadius() const
{
	return(m_radius);
}

// константный геттер для получения значения ускорения
int ABomb::GetExtra_speed() const
{
	// вернули значение ускорения
	return(extra_speed);
}

// сеттер для принудительной установки значения ускорения
void ABomb::SetExtra_speed(int NewSpeed) 
{
	extra_speed = NewSpeed;
}


/*------------------------------------------------------------------------*/
/*              Обычная бомба          */
/*-------------------------------------*/

// производный класс БОМБА от Point и по определению от Location. И ABomb
// радиус бомбы - параметр для отрисовки
// ускорение - параметр для движения бомбы
// конструктор работает через конструкторы предков
Bomb::Bomb(int InitX, int InitY, int InitNumb, int InitRadius, int InitExtraSpeed) : Point(InitX, InitY), ABomb(InitRadius, InitExtraSpeed)
{
	m_numb = InitNumb;                    // установили значение номера бомбы
}

// деструктор
Bomb::~Bomb()                                                  
{
	// пустое тело
}

// сеттер для принудительной установки значения радиуса. Реализация для абстрактного базового класса
void Bomb::SetRadius(double NewRadius)                            
{
	// установили значение радиуса
	m_radius = NewRadius;
}

// константный геттер для получения значения номера
int Bomb::GetNumb()const
{
	// вернули значение номера бомбы
	return(m_numb);
}

// сеттер для принудительной установки значения номера
void Bomb::SetNumb(int NewNumb)                                
{
	m_numb = NewNumb;
}

// показать обычную бомбу на экране. Виртуальный метод
void Bomb::Show()                                           
{
	// зададим тип, толщину и цвет пера
	HPEN PenWhite = CreatePen(PS_SOLID, 4, RGB(234, 230, 202));
	// зададим тип, толщину и цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(234, 230, 202));

	// не вышли за пределы консоли с учетом радиуса
	if (HighBorderBullet <= GetY() - 3 * GetRadius())
	{
		m_Visible = true;                 // бомба видна на экране
		// делаем перо PenWhite активным
		SelectObject(hdc, PenWhite);
		// делаем кисть Brush активной
		SelectObject(hdc, Brush);
		// отрисовка бомбы
		Ellipse(hdc, m_X - 1.5 * m_radius, m_Y - 2.2 * m_radius, m_X - 0.6 * m_radius, m_Y - 3.1 * m_radius);
	}

	// иначе - вышли за пределы консоли. Скрываем бомбу
	else
	{
		Hide();
	}

	DeleteObject(Brush);                  // уничтожаем созданный нами объект кисти Brush
	DeleteObject(PenWhite);               // уничтожаем созданный нами объект пера PenWhite
}

// скрыть обычную бомбу с экрана. Виртуальный метод
void Bomb::Hide()
{
	m_Visible = false;                    // бомба не видна на экране

	// отрисовка той же бомбы цветом консоли
	// зададим тип, толщину и цвет пера
	HPEN PenBlack = CreatePen(PS_SOLID, 4, RGB(12, 12, 12));
	// зададим тип, толщину и цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));

	// делаем перо PenBlack активным
	SelectObject(hdc, PenBlack);
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// отрисовка бомбы
	Ellipse(hdc, m_X - 1.5 * m_radius, m_Y - 2.2 * m_radius, m_X - 0.6 * m_radius, m_Y - 3.1 * m_radius);
	
	DeleteObject(Brush);                  // уничтожаем созданный нами объект кисти Brush 
	DeleteObject(PenBlack); 			  // уничтожаем созданный нами объект пера PenWhite
}


/*------------------------------------------------------------------------------------------------------*/
/*            Красная  бомба           */
/*-------------------------------------*/

// производный класс Красная бомба от обычной бомбы и по определению от Point и Location. И ABomb 
// Отличие от других: наличие ускорения
// конструктор с передачей пераметров по умолчанию
Red_Bomb::Red_Bomb(int InitX, int InitY, int InitNumb, int InitRadius) : Bomb(InitX, InitY, InitNumb, InitRadius)
{
	extra_speed = 3;                      // установили значение ускорения
}

// деструктор
Red_Bomb:: ~Red_Bomb()                                              
{
	// пустое тело
}

// показать красную бомбу на экране. Виртуальный метод
void Red_Bomb::Show()
{
	// зададим тип, толщину и цвет пера
	HPEN PenRed = CreatePen(PS_SOLID, 4, RGB(196, 30, 58));
	// зададим тип, толщину и цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(196, 30, 58));

	// не вышли за пределы консоли с учетом радиуса
	if (HighBorderBullet <= GetY() - 3 * GetRadius())
	{
		m_Visible = true;                 // красная бомба видна на экране
		// делаем перо PenRed активным
		SelectObject(hdc, PenRed);
	    // делаем кисть Brush активной
		SelectObject(hdc, Brush);
		// отрисовка красной бомбы
		Ellipse(hdc, m_X - 1.5 * m_radius, m_Y - 2.2 * m_radius, m_X - 0.6 * m_radius, m_Y - 3.1 * m_radius);
	}

	// иначе - вышли за пределы консоли. Скрываем красную бомбу
	else
	{
		Hide();                           // родительский метод Hide, т.к. радиусы бомб одинаковые
	}

	DeleteObject(Brush);                  // уничтожаем созданный нами объект кисти Brush 
	DeleteObject(PenRed);				  // уничтожаем созданный нами объект пера PenRed
}


/*------------------------------------------------------------------------------------------------------*/
/*          Фиолетовая  бомба          */
/*-------------------------------------*/

// производный класс Фиолетовая бомба от обычной бомбы и по определению от Point и Location. И ABomb 
// конструктор с передачей параметров по умолчанию и вызов родительских конструкторов
Purple_Bomb::Purple_Bomb(int InitX, int InitY, int InitNumb, int InitRadius) : Bomb(InitX, InitY, InitNumb, InitRadius)
{
	extra_speed = 0;                      // ускорения нет
}

// деструктор
Purple_Bomb::~Purple_Bomb()                                              
{
	// пустое тело
}

// показать фиолетовую бомбу на экране. Виртуальный метод
void Purple_Bomb::Show()
{
	// зададим тип, толщину и цвет пера
	HPEN PenPurple = CreatePen(PS_SOLID, 4, RGB(244, 0, 161));
	// зададим тип, толщину и цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(196, 30, 58));

	// не вышли за пределы консоли с учетом радиуса
	if (HighBorderBullet <= GetY() - 3 * GetRadius())
	{
		m_Visible = true;                 // фиолетовая бомба видна на экране
		// делаем перо PenPurple активным
		SelectObject(hdc, PenPurple);
		// делаем кисть Brush активной
		SelectObject(hdc, Brush);
		// отрисовка фиолетовой бомбы
		Ellipse(hdc, m_X - 0.3 * m_radius, m_Y - 1.9 * m_radius, m_X - 1.5 * m_radius, m_Y - 3 * m_radius);
	}

	// иначе - вышли за пределы консоли. Скрываем фиолетовую бомбу
	else
	{
		Hide();
	}

	DeleteObject(Brush);                  // уничтожаем созданный нами объект кисти Brush
	DeleteObject(PenPurple);              // уничтожаем созданный нами объект пера PenPurple
}

// скрыть фиолетовую бомбу с экрана. Виртуальный метод
void Purple_Bomb::Hide()
{
	m_Visible = false;                    // фиолетовая бомба не видна на экране
	
	// отрисовка той же бомбы цветом консоли
	// зададим тип, толщину и цвет пера
	HPEN PenBlack = CreatePen(PS_SOLID, 4, RGB(12, 12, 12));
	// зададим тип, толщину и цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));

	// делаем перо PenBlack активным
	SelectObject(hdc, PenBlack);
	// делаем кисть Brush активной
	SelectObject(hdc, Brush);
	// отрисовка бомбы
	Ellipse(hdc, m_X - 0.3 * m_radius, m_Y - 1.9 * m_radius, m_X - 1.5 * m_radius, m_Y - 3 * m_radius);

	DeleteObject(Brush);                  // уничтожаем созданный нами объект кисти Brush 
	DeleteObject(PenBlack);				  // уничтожаем созданный нами объект пера PenRed
}


/*------------------------------------------------------------------------------------------------------*/
/*            Зелёная  бомба           */
/*-------------------------------------*/

// производный класс Зеленая бомба от обычной бомбы и по определению от Point и Location. И ABomb 
// конструктор с передачей параметров по умолчанию. Вызов родительского конструктора
Green_Bomb::Green_Bomb(int InitX, int InitY, int InitNumb, int InitRadius) : Bomb(InitX, InitY, InitNumb, InitRadius)
{
	extra_speed = 0;                      // ускорения нет
	step = 0;                             // заморозка Зелёной бомбы. Бомба летит не до конца консоли, а определённую дистанцию
}

// деструктор
Green_Bomb::~Green_Bomb()
{
	// пустое тело
}

// константный геттер для текущего значения торможения
int Green_Bomb::GetStep() const
{
	// вернули значение торможения
	return(step);
}

// сеттер для принудительной установки текущего значения торможения
void  Green_Bomb::SetStep(int NewStep)
{
	step = NewStep;
}

// показать зелёную бомбу на экране. Виртуальный метод
void Green_Bomb::Show()
{
	// зададим тип, толщину и цвет пера
	HPEN PenGreen = CreatePen(PS_SOLID, 4, RGB(0, 255, 127));
	// зададим тип, толщину и цвет кисти
	HBRUSH Brush = CreateSolidBrush(RGB(0, 255, 127));

	// верхняя граница консоли для бомбы с учётом радиуса - бомба не вылетела за консоль и количество шагов бомбы <=30
	if ((HighBorderBullet <= GetY() - 3 * GetRadius()) && (step <= 30))
	{
		step = step + 1;                  // увеличить счётчик шагов
		m_Visible = true;                 // бомба видна на экране

		// делаем перо PenGreen активным
		SelectObject(hdc, PenGreen);
		// делаем кисть Brush активной
		SelectObject(hdc, Brush);
		// отрисовка зелёной бомбы
		Ellipse(hdc, m_X - 1.5 * m_radius, m_Y - 2.2 * m_radius, m_X - 0.6 * m_radius, m_Y - 3.1 * m_radius);
	}

	// иначе - вышли за пределы консоли или набрали нужное количество шагов для остановки. Скрываем бомбу. Вызываем метод с уровня предка
	else
	{
		Hide();                           // скрываем бомбу
		step = 0;                         // обнуляем счётчик шагов
	}

	DeleteObject(PenGreen);               // уничтожаем созданный нами объект пера PenGreen
	DeleteObject(Brush);                  // уничтожаем созданный нами объект кисти Brush
}