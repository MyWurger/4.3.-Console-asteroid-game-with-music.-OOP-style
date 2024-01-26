/***************************************************************************
 *      Л А Б О Р А Т О Р Н А Я   Р А Б О Т А   № 2   П О   Т Р П О        *
 *-------------------------------------------------------------------------*
 *                                                                         *
 * Project Name  : Fly_Plate                                               *
 * Project Type  : Win64 Console application                               *
 * File Name     : Secondary_functions.cpp                                 *
 * Language      : VS2022                         C++                      *
 * Programmers   : Викулов Д. Г.                                           *
 * Modified By   :                                                         *
 * Created       : 01 / 11 / 2023                                          *
 * Last Revision : 16 / 11 / 2023                                          *
 * Comment(s)    : Игровое взаимодействие фигур через динамический         *
 *                 полиморфизм. Наследование Матрица переходов.            *
 *                 Абстрактные классы. Интерфейсы.                         *
 **************************************************************************/

#include "Secondary_functions.h"                            // подключаем заголовочный файл с прототипами вспомогательных функций 

// проверка удара пули об летающую тарелку
bool Hit_FlyingPlate_Bullets(Bullet* CurBullet              // указатель базового класса ЛЕТАЮЩИЕ ТАРЕЛКИ
	                       , FlyingPlate* CurPlate)         // указатель базового класса АСТЕРОИДЫ
{
	// упростим визуализацию условия
	double bulletX = CurBullet->GetX();                            // Координата X пули
	double bulletY = CurBullet->GetY() - CurBullet->GetCaliber();  // Смещаем координату Y на нос пули
	double caliber = CurBullet->GetCaliber();                      // калибр пули
	double plateLeftBorder = CurPlate->Left_Border();              // Левая граница летающей тарелки
	double plateRightBorder = CurPlate->Right_Border();            // Правая граница летающей тарелки
	double plateLowBorder = CurPlate->Low_Border();                // Нижняя граница летающей тарелки
	double plateHighBorder = CurPlate->High_Border();              // Верхняя граница летающей тарелки
	double isPlateVisible = CurPlate->IsVisible();                 // Летающая тарелка есть на экране

	// если пуля находится между правой и левой границей летающей тарелки и наивысшая часть пули достигла нижней части летающей тарелки,
	// но не вышла за пределы верхней части летающей тарелки, и летающая тарелка видна на экране
	if ((plateLeftBorder <= bulletX)
		&& (bulletX <= plateRightBorder)
		&& (plateLowBorder <= bulletY - caliber)
		&& (bulletY - caliber <= plateHighBorder)
		&& (isPlateVisible))
	{
		// вернуть флаг попадания пули в летающую тарелку
		return(true);
	}
	else
	{
		// иначе - в данную летающую тарелку пуля не попала
		return(false);
	}// if
}


// проверка удара бомбы об летающую тарелку
bool Hit_FlyingPlate_Bombs(Bomb* CurBomb                    // указатель базового класса ПУЛИ
	                     , FlyingPlate* CurPlate)           // указатель базового класса ЛЕТАЮЩИЕ ТАРЕЛКИ
{
	// упростим визуализацию условия
	double BombX = CurBomb->GetX();                         // Координата X бомбы
	double BombY = CurBomb->GetY();                         // Координата Y бомбы
	double radius = CurBomb->GetRadius() * 4;               // Радиус бомбы
	double plateLeftBorder = CurPlate->Left_Border();       // Левая граница летающей тарелки
	double plateRightBorder = CurPlate->Right_Border();     // Правая граница летающей тарелки
	double plateLowBorder = CurPlate->Low_Border();         // Нижняя граница летающей тарелки
	double plateHighBorder = CurPlate->High_Border();       // Верхняя граница летающей тарелки
	double isPlateVisible = CurPlate->IsVisible();          // Летающая тарелка есть на экране

	// если бомба находится между правой и левой границей летающей тарелки и наивысшая часть бомбы (с учётом радиуса) достигла нижней части летающей тарелки,
	// но не вышла за пределы верхней части летающей тарелки, и летающая тарелка видна на экране
	if ((plateLeftBorder <= BombX)
		&& (BombX <= plateRightBorder)
		&& (plateLowBorder <= BombY - radius)
		&& (BombY - radius <= plateHighBorder)
		&& (isPlateVisible))
	{
		// вернуть флаг попадания бомбы в летающую тарелку
		return(true);
	}
	else
	{
		// иначе - в данную летающую тарелку бомба не попала
		return(false);
	}// if 
}


// проверка удара бомбы об астероид
bool Hit_Asteroids_Bombs(Bomb* CurBomb                      // указатель базового класса ПУЛИ
	                   , Asteroid* CurAsteroid)             // указатель базового класса АСТЕРОИДЫ

{
	// упростим визуализацию условия
	double bombX = CurBomb->GetX();                             // Координата X бомбы
	double bombY = CurBomb->GetY();                             // Координата Y бомбы
	double radius = CurBomb->GetRadius() * 4;                   // Радиус бомбы
	double asteroidLeftBorder = CurAsteroid->Left_Border();     // Левая граница астероида
	double asteroidRightBorder = CurAsteroid->Right_Border() + 5;   // Правая граница астероида
	double asteroidLowBorder = CurAsteroid->Low_Border();           // Нижняя граница астероида
	double asteroidHighBorder = CurAsteroid->High_Border();         // Верхняя граница астероида
	double isAsteroidVisible = CurAsteroid->IsVisible();            // Астероид есть на экране

	// если бомба находится между правой и левой границей астероида и наивысшая часть бомбы (с учётом радиуса) достигла нижней части астероида,
	// но не вышла за пределы верхней части астероида, и астероид виден на экране
	if ((asteroidLeftBorder <= bombX)
		&& (bombX <= asteroidRightBorder)
		&& (asteroidLowBorder <= bombY - radius)
		&& (bombY - radius <= asteroidHighBorder)
		&& (isAsteroidVisible))
	{
		// вернуть флаг попадания бомбы в астероид
		return(true);
	}
	else
	{
		// иначе - в данный астероид бомба не попала
		return(false);
	}// if
}


// проверка удара корабля об летающую тарелку
bool HitShip_Plate(Ship* CurShip                            // указатель базового класса КОРАБЛИ
	             , FlyingPlate* CurPlate                    // указатель базового класса ЛЕТАЮЩИЕ ТАРЕЛКИ
	             , int& schet)                              // счётчик очков передаётся по ссылке для изменения
{
	// упростим визуализацию условия
	double plateLeftBorder = CurPlate->Left_Border();       // Левая граница летающей тарелки
	double plateRightBorder = CurPlate->Right_Border();     // Правая граница летающей тарелки
	double plateLowBorder = CurPlate->Low_Border();         // Нижняя граница летающей тарелки
	double plateHighBorder = CurPlate->High_Border();       // Верхняя граница летающей тарелки
	double isPlateVisible = CurPlate->IsVisible();          // Летающая тарелка есть на экране

	double shipLeft = CurShip->Left_Border();               // Левая граница корабля
	double shipRight = CurShip->Right_Border();             // Правая граница корабля
	double shipHigh = CurShip->High_Border();               // Низ корабля
	double shipLow = CurShip->Low_Border();                 // Верх корабля

	// если правая граница летающей тарелки находится между левой и правой границей корабля
	// и нижняя граница корабля находится выше нижней границы летающей тарелки и ниже верха летающей тарелки и летающая тарелка не скрыта
	// или левая граница летающей тарелки меньше правой границы корабля и правая граница корабля меньше правой границы летающей тарелки
	// и верхняя граница корабля находится ниже верхней гранцы летающей тарелки и нижняя граница корабля находится ниже нижней границы летающей тарелки
	// и летающая тарелка видна
	if (plateRightBorder >= shipLeft && shipRight >= plateRightBorder
		&& (shipLow <= plateHighBorder
		&& (shipHigh >= plateLowBorder)
		&& isPlateVisible)
		|| plateLeftBorder <= shipRight && shipRight <= plateRightBorder
		&& (shipLow <= plateHighBorder)
		&& (shipHigh >= plateLowBorder)
		&& isPlateVisible)
	{
		// произошел удар, увеличили счётчик
		schet = schet + 1;
		// выводим изменённый счётчик на экран
		Count(schet);
		// удар произошел - вернули флаг удара корабля об летающую тарелку
		return(true);
	}
	else
	{
		// удар корабля об данную летающую тарелку не произошел
		return(false);
	}// if
}


// проверка удара пули об астероид
bool HitBullet(Bullet* CurBullet                           // указатель базового класса ПУЛИ
	         , Asteroid** CurAsteroid                      // указатель на указатель базового класса АСТЕРОИДЫ, чтобы сразу установить в него астероид, в который произошёл удар пулей
	         , Asteroid** Asteroids)                       // массив астероидов для проверки удара с каждым из астероидов
{
	// для цикла
	int i;
	double bulletX, bulletY, asteroidLeftBorder, asteroidRightBorder, asteroidLowBorder, asteroidHighBorder;
	bool isAsteroidVisible;

	// выясняем с каким астероидом произошло столкновение
	for (i = 0; i < CountMeteor; i++)
	{
		// присваиваем текущий астероид
		(*CurAsteroid) = Asteroids[i];

		// упростим визуализацию условия
		bulletX = CurBullet->GetX();                            // Координата X пули
		bulletY = CurBullet->GetY() - CurBullet->GetCaliber();  // Смещаем координату Y на нос пули
		asteroidLeftBorder = (*CurAsteroid)->Left_Border();     // Левая граница астероида
		asteroidRightBorder = (*CurAsteroid)->Right_Border();   // Правая граница астероида
		asteroidLowBorder = (*CurAsteroid)->Low_Border();       // Нижняя граница астероида
		asteroidHighBorder = (*CurAsteroid)->High_Border();     // Верхняя граница астероида
		isAsteroidVisible = (*CurAsteroid)->IsVisible();        // Астероид есть на экране

		// если пуля находится между правой и левой границей астероида и наивысшая часть пули достигла нижней части астероида,
		// но не дошла до верхней части астероида. При этом текущий астероид виден на экране
		if (asteroidLeftBorder <= bulletX && bulletX <= asteroidRightBorder &&
			asteroidLowBorder <= bulletY && bulletY <= asteroidHighBorder && isAsteroidVisible)
		{
			// устанавливаем астероид, в который попала пуля
			*CurAsteroid = Asteroids[i];
			// подтвердили, что нужно обращаться к матрице перехода астероидов
			return (true);
		}// if
	}// for i

	// пуля не попала ни в один из астероидов
	return(false);
}


// проверка удара корабля об астероид
bool HitShip(Ship* CurShip                                 // указатель базового класса КОРАБЛИ
	       , Asteroid** CurAsteroid                        // указатель на указатель базового класса АСТЕРОИДЫ, чтобы сразу установить в него астероид, который нужно переместить
	       , Asteroid** Asteroids)                         // массив астероидов для проверки удара с каждым из астероидов
{
	// для цикла
	int i;
	double asteroidRight, asteroidLeft, shipLeft, shipRight, asteroidHigh, asteroidLow, shipHigh, shipLow;
	bool asteroidVisible;

	// выясняем с каким астероидом произошло столкновение. Проходим по всем астероидам
	for (i = 0; i < CountMeteor; i++)
	{
		// присваиваем текущий астероид
		(*CurAsteroid) = Asteroids[i];

		// упростим визуализацию условия
		asteroidRight = (*CurAsteroid)->Right_Border();    // Правая граница астероида
		asteroidLeft = (*CurAsteroid)->Left_Border();      // Левая граница астероида
		shipLeft = CurShip->Left_Border();                 // Левая граница корабля
		shipRight = CurShip->Right_Border();               // Правая граница корабля
		asteroidHigh = (*CurAsteroid)->High_Border();      // Низ астероида
		asteroidLow = (*CurAsteroid)->Low_Border();        // Верх астероида
		shipHigh = CurShip->High_Border();                 // Низ корабля
		shipLow = CurShip->Low_Border();                   // Верх корабля
		asteroidVisible = (*CurAsteroid)->IsVisible();     // Астероид есть на экране

		// если правая граница астероида находится между левой и правой границей корабля
		// и нижняя граница корабля находится выше нижней границы астероида и текущий астероид не скрыт
		// или левая граница астероида меньше правой границы корабля и правая граница корабля меньше правой границы астороида
		// и верхняя граница корабля находится ниже верхней гранцы астероида и нижняя граница корабля находится ниже нижней границы астероида
		// и текущий астероид виден
		if (((asteroidRight >= shipLeft && shipRight >= asteroidRight)
			&& (shipLow <= asteroidHigh && shipHigh >= asteroidLow)
			&& asteroidVisible)
			|| ((asteroidLeft <= shipRight && shipRight <= asteroidRight)
				&& (shipLow <= asteroidHigh && shipHigh >= asteroidLow)
				&& asteroidVisible))
		{
			// устанавливаем астероид, в который попал корабль
			*CurAsteroid = Asteroids[i];
			// подтвердили, что нужно обращаться к матрице перехода кораблей
			return(true);
		}// if
	}// for i

   // удар не произошел
	return(false);
}


// смена летающей тарелки
void changeFlyingPlate(FlyingPlate** CurPlate               // указатель на указатель базового класса ЛЕТАЮЩИЕ ТАРЕЛКИ
	                 , FlyingPlate** Plates                 // указатель на первый элемент массива указателей на объекты класса Plates и его наследников
	                 , Bomb* CurBomb                        // указатель базового класса БОМБЫ
	                 , int transition_matr_Flying_Plate[][CountBombs]  // матрица перехода летающих тарелок
	                 , int& schet)                          // счётчик очков передаётся по ссылке для изменения
{
	// попали в летающую тарелку соответствующей для неё бомбой по матрице переходов - тарелка поменяется. Счётчик увеличивается
	if ((transition_matr_Flying_Plate[(*CurPlate)->GetNum()][CurBomb->GetNumb()] != (*CurPlate)->GetNum()))
	{
		// увеличение счётчика
		schet = schet + 1;
		// вывод изменённого счётчика на экран
		Count(schet);
	}// if

	double CurrX;                       // текущая координата X летающей тарелки
	double CurrY;                       // текущая координата Y летающей тарелки       
	CurrX = (*CurPlate)->GetX();        // получили Х очередной летающей тарелки
	CurrY = (*CurPlate)->GetY();        // получили Y очередной летающей тарелки
	CurBomb->Hide();                    // прячем бомбу
	(*CurPlate)->Hide();                // прячем текущую летающую тарелку

    // выбираем новую летающую тарелку согласно матрице переходов
	(*CurPlate) = Plates[transition_matr_Flying_Plate[(*CurPlate)->GetNum()][CurBomb->GetNumb()]];
	// устанавливаем координату X для новой летающей тарелки на место старой
	(*CurPlate)->SetX(CurrX);
	// устанавливаем координату Y для новой летающей тарелки на место старой
	(*CurPlate)->SetY(CurrY);
	// показываем изменённую летающую тарелку новом месте
	(*CurPlate)->Show();
}


// смена астероида
void changeAsteroid(Asteroid** CurAsteroid                  // указатель на указатель базового класса АСТЕРОИДЫ
	              , Bullet* CurBullet                       // указатель базового класса ПУЛИ
	              , Asteroid** Asteroids                    // указатель на первый элемент массива указателей на объекты класса Asteroid и его наследников
	              , int transition_matr[][CountBullets]     // матрица перехода астероидов
	              , int dead_matr[][CountBullets])          // матрица смертей астероидов. Для появления астероида на новом месте после полного цикла переходов

{
	double CurrX;                                           // текущая координата Х астероида
	double CurrY;                                           // текущая координата Y астероида
	CurrX = (*CurAsteroid)->GetX();                         // получили Х очередного астероида
	CurrY = (*CurAsteroid)->GetY();                         // получили Y очередного астероида
	CurBullet->Hide();                                      // прячем пулю
	(*CurAsteroid)->Hide();                                 // прячем текущий астероид

	// если текущий астероид подлежит уничтожению и новому астероиду нужно появиться на новом месте
	// нашли номер в матрице смертей для появления нового астероида
	if (dead_matr[(*CurAsteroid)->GetNumber()][CurBullet->GetScale()] != DeadNumber)
	{
		// установливаем астероид с этим номером
		(*CurAsteroid) = Asteroids[dead_matr[(*CurAsteroid)->GetNumber()][CurBullet->GetScale()]];
		// выбираем новую координату Y для диапазона появления астероидов
		CurrY = rand() % (HighZoneSpavn - LowZoneSpavn + 1) + LowZoneSpavn;
		// меняем координату Y
		(*CurAsteroid)->SetY(CurrY);
		// показываем новый астероид на новом месте
		(*CurAsteroid)->Show();
		// заканчиваем рассмотрение на этом шаге
		return;
	}// if

	// если астероид не подлежит уничтожению, а подлежит переходу. Выбираем новый астероид согласно матрице переходов
	(*CurAsteroid) = Asteroids[transition_matr[(*CurAsteroid)->GetNumber()][CurBullet->GetScale()]];
	// устанавливаем координату X для нового астероида на место старого
	(*CurAsteroid)->SetX(CurrX);
	// устанавливаем координату Y для нового астероида на место старого
	(*CurAsteroid)->SetY(CurrY);
	// показываем астероид на новом месте
	(*CurAsteroid)->Show();
	return;
}


// смена корабля
void changeShip(Ship** CurShip                         // указатель на указатель базового класса КОРАБЛЬ для изменения значения указателя
	          , Asteroid* CurAsteroid                  // указатель базового класса АСТЕРОИД
	          , Ship** Ships                           // указатель на первый элемент массива указателей на объекты класса Ship и его наследников
	          , int ship_matr[][CountMeteor])          // матрица переходов корабля
{
	// для смены координаты X корабля/ астероида
	double CurrX;
	// для смены координаты Y корабля/ астероида
	double CurrY;

	// разбираемся с астероидом после столкновения
	// прячем астероид
	CurAsteroid->Hide();
	// выбираем координату Y из диапазона для появления астероидов
	CurrY = rand() % (HighZoneSpavn - LowZoneSpavn + 1) + LowZoneSpavn;
	// устанавливаем координату Y текущему астероиду
	CurAsteroid->SetY(CurrY);
	// показываем астероид на новом месте
	CurAsteroid->Show();

	// разбираемся с кораблём после столкновения
	CurrX = (*CurShip)->GetX();                      // получили Х корабля для того, чтобы новый появился на том же месте
	CurrY = (*CurShip)->GetY();                      // получили Y корабля для того, чтобы новый появился на том же месте
	(*CurShip)->Hide();                              // прячем текущий корабль

	// Выбираем новый корабль согласно матрице переходов
	(*CurShip) = Ships[ship_matr[(*CurShip)->GetSNumber()][CurAsteroid->GetNumber()]];
	// устанавливаем координату X для нового корабля на место старого
	(*CurShip)->SetX(CurrX);
	// устанавливаем координату Y для нового корабля на место старого
	(*CurShip)->SetY(CurrY);
	// показываем корабль на новом месте
	(*CurShip)->Show();
	return;
}


// появление астероида на новом месте после того как он достиг конца консоли
void RespavnAsteroid(Asteroid* CurAsteroid)                 // указатель базового класса АСТЕРОИДЫ
{
	double CurrY;                                           // координата Y для установки

	// если астероид вышел за пределы нижней границы консоли для астероидов
	if (CurAsteroid->High_Border() >= YMaxAster)
	{
		// прячем его
		CurAsteroid->Hide();
		// выбираем координату Y из диапазона для появления
		CurrY = rand() % (HighZoneSpavn - LowZoneSpavn + 1) + LowZoneSpavn;
		// устанавливаем координату Y текущему астероиду
		CurAsteroid->SetY(CurrY);
		// показывпем астероид на новом месте
		CurAsteroid->Show();
		// выходим из функции
		return;
	}// if (CurAsteroid->High_Border() >= YMaxAster)

	return;
}


// вывод счётчика сбитых астероидов на экран
void Count(int schet)                                       // указатель базового класса АСТЕРОИДЫ
{
	// получает дескриптор стандартного устройства вывода (консоли) и сохраняет его в переменной hConsole
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// COORD - это структура, определенная в Windows API, которая используется для представления координат позиции на экране или в консоли.
	COORD position;
	// Устанавливаем значения ее членов X и Y равными 0.
	position.X = 0;
	position.Y = 0;
	// Устанавливаем позицию курсора в верхний левый угол консоли. После этого, при выводе текста или графики в консоль, они будут отображаться в указанной позиции относительно курсора.
	SetConsoleCursorPosition(hConsole, position);
	// DWORD written - это переменная, определенная в Windows API, которая используется для хранения количества записанных байт или символов при выполнении операций ввода/вывода.
	DWORD written;

	// FillConsoleOutputCharacter - это функция из Windows API, которая используется для заполнения определенного количество ячеек консоли
	// определенным символом. Она принимает пять аргументов: первый - дескриптор консоли (HANDLE), второй - символ для заполнения,
	// третий - количество ячеек для заполнения, четвертый - начальная позиция заполнения (COORD),
	// пятый - указатель на переменную written, в которую будет записано количество ячеек, которые были фактически заполнены.

	FillConsoleOutputCharacter(hConsole, ' ', 80 * 2, position, &written); // Очищаем 1 строку сначала

	// Выводим какую-то информацию в очищенную область консоли
	position.X = 100;
	position.Y = 0;
	SetConsoleCursorPosition(hConsole, position);
	// выводим информацию
	std::cout << "\t\t\t\t\t\tScore:" << schet;
	return;
}


// надпись "конец"
void WriteEnd()
{
	// получает дескриптор стандартного устройства вывода (консоли) и сохраняет его в переменной console
	HWND console = GetConsoleWindow();
	// LOGFONT - это структура из Windows API, которая используется для определения атрибутов шрифта.
	LOGFONT lf;
	// memset - это функция стандартной библиотеки C, которая используется для заполнения блока памяти определенным значением.
	// Она принимает три аргумента: указатель на блок памяти, значение для заполнения и количество байт, которые должны быть заполнены.
	// заполняет всю память, занимаемую структурой lf, нулевыми значениями.
	memset(&lf, 0, sizeof(LOGFONT));

	// lf.lfHeight - это член структуры LOGFONT, который представляет высоту шрифта в пунктах (pt).
	lf.lfHeight = 60;
	// lf.lfWeight - это член структуры LOGFONT, который представляет жирность шрифта. Значение FW_NORMAL указывает на нормальную жирность шрифта
	lf.lfWeight = FW_NORMAL;
	// wcscpy_s - это функция стандартной библиотеки C, которая используется для копирования строки типа wchar_t (широкие символы)
	// из одного буфера в другой. Она принимает три аргумента: указатель на целевой буфер, указатель на исходную строку и максимальное
	// количество символов, которые можно скопировать в целевой буфер.
	wcscpy_s(lf.lfFaceName, L"Arial");
	// CreateFontIndirect - это функция WinAPI, которая используется для создания шрифта на основе данных в структуре LOGFONT.
	HFONT hFont = CreateFontIndirect(&lf);
	// SelectObject - это функция WinAPI, которая используется для установки объекта (в данном случае шрифта)
	// в контексте устройства (device context), то есть связывает объект с контекстом устройства.
	SelectObject(hdc, hFont);

	// SetTextColor и SetBkMode - это функции WinAPI для установки цвета текста и режима фона соответственно.
	SetTextColor(hdc, RGB(127, 255, 212));
	// SetBkMode используется для установки режима фона. В данном случае мы устанавливаем режим TRANSPARENT, который означает прозрачный фон.
	SetBkMode(hdc, TRANSPARENT);

	// SIZE size;
	SIZE size;

	// Тип LPCWSTR расшифровывается следующим образом:
	// - LP - это префикс, обозначающий "указатель на";
	// - C - это префикс, указывающий на то, что строка является константой (read-only);
	// - WSTR - это сокращение от "wide string", т.е. юникодной строки.
	LPCWSTR text = L"К о н е ц";
	// GetTextExtentPoint32 - это функция WinAPI, которая используется для вычисления ширины и высоты текстовой строки, отображаемой с использованием указанного контекста устройства (hdc) и шрифта.
	GetTextExtentPoint32(hdc, text, wcslen(text), &size);

	// прямоугольник, где будет рисоваться надпись. В данном случае параметры консоли и значения координат её центра
	int consoleWidth = 148 * 8;
	int consoleHeight = 57 * 16;
	int centerX = (consoleWidth - size.cx) / 2;
	int centerY = (consoleHeight - size.cy) / 2;

	// TextOut - это функция WinAPI, которая используется для вывода текстовой строки на устройство с заданными координатами.
	TextOut(hdc, centerX, centerY, text, wcslen(text));
	DeleteObject(hFont);
	ReleaseDC(console, hdc);
	// задержка перед стиранием надписи
	Sleep(1300);
}