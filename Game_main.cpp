/***************************************************************************
 *      Л А Б О Р А Т О Р Н А Я   Р А Б О Т А   № 2   П О   Т Р П О        *
 *-------------------------------------------------------------------------*
 *                                                                         *
 * Project Name  : Fly_Plate                                               *
 * Project Type  : Win64 Console application                               *
 * File Name     : Game_main.cpp                                           *
 * Language      : VS2022                                                  *
 * Modified By   :                                                         *
 * Created       : 01 / 11 / 2023                                          *
 * Last Revision : 16 / 11 / 2023                                          *
 * Comment(s)    : Игровое взаимодействие фигур через динамический         *
 *                 полиморфизм. Наследование Матрица переходов.            *
 *                 Абстрактные классы. Интерфейсы.                         *
 **************************************************************************/

#include "constants.h"             // подключаем файл с объявлением глобальных констант
#include "Secondary_functions.h"   // подключаем заголовочный файл с прототипами вспомогательных функций     
#include "asteroid_co.h"           // подключаем заголовочный файл с классами
#include <string>                  // для указания абсолютного адреса звукового файла
#pragma comment (lib, "winmm.lib") // работа со звуком

//макрос для определения кода нажатой клавиши
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
HWND GetConsoleWindow();           // извлекает дескриптор окна, используемый консолью, связанной с вызывающим процессом.


/***********************************************************************/
/*               О С Н О В Н А Я    П Р О Г Р А М М А                  */
/***********************************************************************/
int main()
{

	// Получаем дескриптор стандартного вывода консоли
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// Загружаем текущий шрифт
	// Используется для сохранения информации о текущем шрифте консоли, такой как его размер и стиль.
	CONSOLE_FONT_INFOEX fontInfo;
	// Установка размера важна, когда структура CONSOLE_FONT_INFOEX передается в функции, которые требуют информацию о размере структуры.
	fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	// Здесь и происходит передача
	GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

	// параметры нового размера шрифта
	fontInfo.dwFontSize.X = 14;
	fontInfo.dwFontSize.Y = 20;

	// Устанавливаем шрифт
	SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

	// Используется для сохранения информации о текущем буфере экрана, такой как размеры, положение курсора и атрибуты текста.
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	// Функция, которая получает информацию о буфере экрана консоли и сохраняет ее в структуру bufferInfo.
	GetConsoleScreenBufferInfo(hConsole, &bufferInfo);

	// Установка нового цвета текста
	// Флаг FOREGROUND_GREEN указывает, что текст использует зеленый цвет.
	// Флаг FOREGROUND_INTENSITY указывает, что цвет текста должен быть более интенсивным или ярким.
	// Когда эти два флага комбинируются, то задается цвет зеленый и с более высокой интенсивностью.

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	// Получаем дескриптор окна консоли
	HWND hwnd = GetConsoleWindow();
	// RECT - это структура, используемая в Windows API для представления прямоугольной области.
	RECT rect;
	// Получаем текущие размеры окна консоли через прямоугольник
	GetWindowRect(hwnd, &rect);
	// Изменяем размеры окна консоли
	MoveWindow(hwnd, rect.left, rect.top, 121 * 8, 46 * 16, TRUE);

	// Указываем путь файла
	string filePath = "C:\\Users\\Дмитрий Викулов\\Music\\song.mp3";
	wstring wFilePath(filePath.length(), L' ');
	MultiByteToWideChar(CP_ACP, 0, filePath.c_str(), filePath.length(), &wFilePath[0], wFilePath.length());
	// эта проверка производится для того, чтобы убедиться, что функция GetConsoleWindow() 
	// успешно вернула дескриптор окна консоли, а не NULL, что может произойти, если вызывающий процесс не 
	// запущен в окружении консоли, либо если произошла другая ошибка при получении дескриптора
	// Открываем файл для воспроизведения
	if (mciSendString((TEXT("open \"") + wFilePath + TEXT("\" type mpegvideo alias music")).c_str(), NULL, 0, NULL) != 0) 
	{
		return 1;
	}

	// Начинаем проигрывать музыку в фоновом режиме
	if (mciSendString(TEXT("play music repeat"), NULL, 0, NULL) != 0) 
	{
		return 2;
	}

	/****************************************************ОСНОВНАЯ ПРОГРАММА******************************************************/
	
	int x0 = 500;           // начальная координата фигуры по OX
	int y0 = 800;           // начальная координата фигуры по OY
	int i = 0;              // для цикла
	int schet = 0;          // количество набранных очков

	bool left = false;      // параметр для движения летающей тарелки влево
	bool right = true;      // параметр для движения летающей тарелки вправо
	bool key = true;        // ключ для работы с пулями
	bool move;              // флаг движения пули/бомбы         


	// массив астероидов
	Asteroid** Asteroids = new Asteroid * [CountMeteor];      // создание динамического массива указателей на объекты класса Asteroid и его наследников
	Asteroids[0] = new White_Warlic(x0 - 350, y0 - 450);      // указатель на объект класса White_Warlic
	Asteroids[1] = new Cold_White_Warlic(x0 + 200, y0 - 470); // указатель на объект класса Cold_White_Warlic
	Asteroids[2] = new Brown_Warlic(x0 - 50, y0 - 350);       // указатель на объект класса Brown_Warlic
	Asteroids[3] = new Neutron_Star(x0 + 550, y0 - 420);      // указатель на объект класса Neutron_Star
	Asteroids[4] = new Brown_Warlic(x0, y0);                  // указатель на объект класса Brown_Warlic. Вспомогательный
	Asteroids[5] = new Cold_White_Warlic(x0, y0);             // указатель на объект класса Cold_White_Warlic. Вспомогательный
	Asteroids[6] = new Neutron_Star(x0, y0);                  // указатель на объект класса Neutron_Star. Вспомогательный
	Asteroids[7] = new Neutron_Star(x0, y0);                  // указатель на объект класса Neutron_Star. Вспомогательный
	Asteroids[8] = new Dead_Star(x0, y0);                     // указатель на объект класса Dead_Star
	Asteroid* CurAsteroid = Asteroids[0];                     // указатель базового класса ссылается на класс White_Warlic
	
	
	// массив летающих тарелок
	FlyingPlate** Plates = new FlyingPlate * [CountFlyingPlates];   // создание динамического массива указателей на объекты класса FlyingPlate и его наследников
	Plates[0] = new FlyingPlate(x0 - 420, y0 - 600);                // объект класса FlyingPlate
	Plates[1] = new Broke_FlyingPlate(x0 - 420, y0 - 600);          // объект класса Broke_FlyingPlate
	Plates[2] = new Angry_FlyingPlate(x0 - 420, y0 - 600);          // объект класса Angry_FlyingPlate
	Plates[3] = new Modify_FlyingPlate(x0 - 420, y0 - 600);         // объект класса Modify_FlyingPlate
	FlyingPlate* CurPlate;                                          // объявляем указатель базового класса
	CurPlate = Plates[0];                                           // указатель базового класса ссылается на класс FlyingPlate
	CurPlate->Show();


	// массив летающих кораблей
	Ship** Ships = new Ship * [CountShips];                   // создание динамического массива указателей на объекты класса Ship и его наследников
	Ships[0] = new Ship(x0, y0);                              // объект класса Ship
	Ships[1] = new Broke_Ship(x0, y0);                        // объект класса Broke_Ship
	Ships[2] = new Infinity_Ship(x0, y0);                     // объект класса Infinity_Ship
	Ship* CurShip;                                            // объявляем указатель базового класса
	CurShip = Ships[0];                                       // указатель базового класса ссылается на класс Ship


	// массив пуль
	Bullet** Bullets = new Bullet * [CountBullets];           // создание динамического массива указателей на объекты класса Bullet и его наследников
	Bullets[0] = new Bullet(x0, y0);                          // указатель на объект класса Bullet
	Bullets[1] = new Yellow_Bullet(x0, y0);                   // указатель на объект класса Yellow_Bullet
	Bullets[2] = new Red_Bullet(x0, y0);                      // указатель на объект класса Red_Bullet
	Bullets[3] = new Green_Bullet(x0, y0);                    // указатель на объект класса Green_Bullet
	Bullets[4] = new Blue_Bullet(x0, y0);                     // указатель на объект класса Green_Bullet
	Bullet* CurBullet;                                        // объявляем указатель базового класса
	CurBullet = Bullets[0];                                   // указатель базового класса ссылается на класс Bullet


	// массив бомб
	Bomb** Bombs = new Bomb * [CountBombs];                   // создание динамического массива указателей на объекты класса Bomb и его наследников
	Bombs[0] = new Bomb(x0 + 200, y0 + 500);                  // указатель на объект класса Bomb
	Bombs[1] = new Red_Bomb(x0 + 200, y0 + 500);              // указатель на объект класса Red_Bomb
	Bombs[2] = new Purple_Bomb(x0 + 200, y0 + 500);           // указатель на объект класса Purple_Bomb
	Bombs[3] = new Green_Bomb(x0 + 200, y0 + 500);            // указатель на объект класса Green_Bomb
	Bomb* CurBomb;                                            // объявляем указатель базового класса
	CurBomb = Bombs[0];                                       // указатель базового класса ссылается на класс Bomb


	// даём нумерацию вспомогательным астероидам. Идём с 4-го по 7-ой элемент массива
	for (i = RealMeteor; i < CountMeteor; i++)
	{
		CurAsteroid = Asteroids[i];                           // последовательно присваиваем адреса объектов указателю
		CurAsteroid->SetNumber(i);                            // устанавливаем нумерацию через сеттер
	}// for i

	// матрица переходов астероидов
	int transition_matr[CountMeteor][CountBullets] ={ {4,0,0,0,0}    // белый карлик
													 ,{1,6,1,1,1}     // остывший белый карлик
													 ,{2,2,7,2,2}     // красный карлик
													 ,{3,3,3,8,3}     // нейтронная звезда
													 ,{4,4,5,4,4}     // красный карлик. Вспомогательный
													 ,{5,0,5,5,5}     // остывший белый карлик. Вспомогательный
													 ,{6,6,6,1,6}     // нейтронная звезда. Вспомогательный
													 ,{7,7,7,2,7}     // нейтронная звезда. Вспомогательный
													 ,{8,8,8,8,3} };  // мертвая звезда. Вспомогательный

	// матрица смертей для появления астероидов на новом месте
	 // матрица смертей для появления астероидов на новом месте
	int dead_matr[CountMeteor][CountBullets] = { {DeadNumber,DeadNumber,DeadNumber,DeadNumber,DeadNumber}     // белый карлик
												,{DeadNumber,DeadNumber,DeadNumber,DeadNumber,DeadNumber}     // остывший белый карлик
												,{DeadNumber,DeadNumber,DeadNumber,DeadNumber,DeadNumber}     // красный карлик
												,{DeadNumber,DeadNumber,DeadNumber,DeadNumber,DeadNumber}     // нейтронная звезда
												,{DeadNumber,DeadNumber,DeadNumber,DeadNumber,DeadNumber}     // красный карлик. Вспомогательный
												,{DeadNumber,0,DeadNumber,DeadNumber,DeadNumber}              // остывший белый карлик. Вспомогательный
												,{DeadNumber,DeadNumber,DeadNumber,1,DeadNumber}              // нейтронная звезда. Вспомогательный
												,{DeadNumber,DeadNumber,DeadNumber,2,DeadNumber}              // нейтронная звезда. Вспомогательный
												,{DeadNumber,DeadNumber,DeadNumber,DeadNumber, 3} };          // мёртвая звезда. Вспомогательный

	// матрица переходов кораблей
	int ship_matr[CountShips][CountMeteor] = { {1,0,1,0,1,0,0,0,0}     // обычный корабль
											  ,{1,2,1,2,1,1,2,2,1}     // сломаный корабль
											  ,{2,2,2,2,2,2,2,2,0} };  // бесконечный корабль

	// матрица переходов летающих тарелок
	int transition_matr_Flying_Plate[CountFlyingPlates][CountBombs] = { {1,0,0,0}     // обычная летающая тарелка
	                                                                   ,{1,2,1,1}     // сломаная летающая тарелка
	                                                                   ,{2,2,3,2}     // злая летающая тарелка
	                                                                   ,{3,3,3,0} };  // модифицированная летающая тарелка

	//если дескриптор существует - можем работать
	if (hwnd != NULL)
	{
		// получить контекст устройства (device context) для указанного окна hwnd,
		// который может использоваться для рисования графики и других операций над окном
		hdc = GetWindowDC(hwnd);
		if (hdc != nullptr)
		{
			// выводим летающий корабль на экран
			CurShip->Show();
			// вывод астероидов на экран. На экране всегда 4 астероида
			for (i = 0; i < RealMeteor; i++)
			{
				CurAsteroid = Asteroids[i];                         // последовательно присваиваем адреса объектов указателю
				CurAsteroid->Show();                                // выводим на экран каждый из астероидов
			}// for i
			// выводим счёт на экран цветом, который задали в начале
			cout << "\t\t\t\t\t\tScore:" << schet;

			while (1)
			{
				/***************************************ОСНОВНЫЕ СОБЫТИЯ ПРОИСХОДЯТ ЗДЕСЬ*****************************************************/
				// малый интервал для плавности движения
				Sleep(35);                                          // 35 мс
				CurShip->Show();
				// нажат ESC - выход из программы
				if (KEY_DOWN(VK_ESCAPE))
				{
					// очищаем экран и заканчиваем программу
					system("cls");
					// выводим надпись "конец"
					WriteEnd();
					HWND consoleWindow = GetConsoleWindow();
					// закрываем консольное окно
					PostMessage(consoleWindow, WM_CLOSE, 0, 0);
					exit(0);
				}

/*********************************************ДВИЖЕНИЕ ЛЕТАЮЩЕЙ ТАРЕЛКИ***********************************************/

				// движение вправо и летающая тарелка видна на экране
				if (right  && CurPlate->IsVisible())
				{
					// сдвигаем летающую тарелку вправо на шаг Step
					(*CurPlate).MoveTo((*CurPlate).GetX() + Step, (*CurPlate).GetY());

					// проверка на продолжение движения летающей тарелки вправо
					// сдвигаем вправо пока не достигли правой границы консоли
					if ((*CurPlate).GetX() <= Right_Border_Plate+3 && (*CurPlate).GetX() >= Right_Border_Plate - 3)
					{
						// блокируется флаг движения вправо
						right = false;
						// устанавливается флаг движения влево
						left = true;
					}// if
				}// if

				// движение влево и летающая тарелка видна на экране
				if (left && CurPlate->IsVisible())
				{
					// сдвигаем летающую тарелку влево на шаг Step
					(*CurPlate).MoveTo((*CurPlate).GetX() - Step, (*CurPlate).GetY());


					// проверка на продолжение движения летающей тарелки влево
					// сдвигаем влево пока не достигли левой границы консоли
					if ((*CurPlate).GetX() <= Left_Border_Plate + 3 && (*CurPlate).GetX() >= Left_Border_Plate - 3)
					{
						// устанавливается флаг движения вправо
						right = true;
						// блокируется флаг движения влево
						left = false;
					}// if
				}// if

/*********************************************С ДВИЖЕНИЕМ ЛЕТАЮЩЕЙ ТАРЕЛКИ ОПРЕДЕЛИЛИСЬ***********************************************/

				// выбор пули и бомбы.
				// 0 - белая пуля
				// 1 - жёлтая пуля
				// 2 - красная пуля
				// 4 - зелёная пуля
				// 5 - синяя пуля
				// для нумпада:
				// 1 - белая бомба
				// 2 - красная бомба
				// 3 - фиолетовая бомба
				// 4 - зелёная бомба

				// SPACE - стрельба

/*******************************Определяем пулю или бомбу, которой будем стрелять и стреляем***********************************/

				// корабль может выпускать только одну пулю или бомбу нажатием SPACE, когда остальных нет на экране
				// если нажата 1 и пули на экране нет
				// проверяем, что пули нет на экране и бомбы нет на экране
				if (CurBullet->IsVisible() == false && CurBomb->IsVisible() == false)
				{
					// ПУЛИ
					// нажата 1
					if (KEY_DOWN(49))
					{
						key = true;                  // флаг пули
						CurBullet = Bullets[0];      // указатель базового класса ссылается на базовый класс Bullet
					}

					// нажата 2
					else if (KEY_DOWN(50))
					{
						key = true;                  // флаг пули
						CurBullet = Bullets[1];      // указатель базового класса ссылается на производный класс Yellow_Bullet
					}

					// нажата 3
					else if (KEY_DOWN(51))
					{
						key = true;                  // флаг пули
						CurBullet = Bullets[2];      // указатель базового класса ссылается на производный класс Red_Bullet      
					}

					// нажата 4
					else if (KEY_DOWN(52))
					{
						key = true;                  // флаг пули
						CurBullet = Bullets[3];      // указатель базового класса ссылается на производный класс Green_Bullet
					}

					// нажата 5
					else if (KEY_DOWN(53))
					{
						key = true;                  // флаг пули
						CurBullet = Bullets[4];      // указатель базового класса ссылается на производный класс Blue_Bullet
					}

					// БОМБЫ
					// нажата 1 на нумпаде
					if (GetAsyncKeyState(VK_NUMPAD1))
					{
						key = false;                 // флаг бомбы
						CurBomb = Bombs[0];          // указатель базового класса ссылается на производный класс Bomb
					}

					// нажата 2 на нумпаде
					else if (GetAsyncKeyState(VK_NUMPAD2))
					{
						key = false;                 // флаг бомбы
						CurBomb = Bombs[1];          // указатель базового класса ссылается на производный класс Red_Bomb
					}

					// нажата 3 на нумпаде
					else if (GetAsyncKeyState(VK_NUMPAD3))
					{
						key = false;                 // флаг бомбы
						CurBomb = Bombs[2];          // указатель базового класса ссылается на производный класс Purple_Bomb
					}

					// нажата 4 на нумпаде
					else if (GetAsyncKeyState(VK_NUMPAD4))
					{
						key = false;                 // флаг бомбы
						CurBomb = Bombs[3];          // указатель базового класса ссылается на производный класс Green_Bomb
					}

					// если нажат пробел
					if (KEY_DOWN(VK_SPACE))
					{
						// для пуль по флагу пули/ бомбы
						if (key)
						{
							// установили координаты пули для появления с носа корабля
							CurBullet->SetX(CurShip->GetX() - 0 * CurShip->GetScale());
							CurBullet->SetY(CurShip->GetY() - 40 * CurShip->GetScale() - CurBullet->GetCaliber());
							// показали пулю по этим координатам
							CurBullet->Show();
						}
						// для бомб
						else
						{
							// установили координаты бомбы для появления с носа корабля
							CurBomb->SetX(CurShip->GetX() + 1.5 * CurShip->GetScale());
							CurBomb->SetY(CurShip->GetY() - 37 * CurShip->GetScale() + 3 * CurBomb->GetRadius());
							// показали бомбу по этим координатам
							CurBomb->Show();
						}// if
					}// if
				}// if

/****************************************************Пуля или бомба выбрана****************************************************/

/*********************************************************Движение пули********************************************************/

				// проверка пули на попадание в летающую тарелку и астероид
				if (CurBullet->IsVisible())
				{
					// флаг того, что пуля ещё не двигалась
					move = true;
					// перебираем все летающие тарелки по порядку при каждом движении пули вверх
					for (i = 0; i < CountFlyingPlates; i++)
					{
						// проверяем условие столкновение пули и летающей тарелки
						if (Hit_FlyingPlate_Bullets(CurBullet, Plates[i]))
						{
							// прячем пулю
							CurBullet->Hide();
							// убираем флаг движения пули
							move = false;
						}

						// иначе, если не попали ни в одну из тарелок
						else if (move)
						{
							// сдвигаем пулю
							CurBullet->MoveTo(CurBullet->GetX(), CurBullet->GetY() - CurBullet->GetCaliber());
							// один раз сдвинули и перевели флаг сдвига в false
							move = false;

						}// if
					}// for i

					// проверка пули на попадание только в случае, если хоть какая-то пуля есть на экране
					if (CurBullet->IsVisible())
					{
						// пуля попала в астероид.Проверяем столкновение с каждым из астероидов массива, чтобы понять, в какой именно астероид попала пуля
						if (HitBullet(CurBullet, &CurAsteroid, Asteroids))
						{
							// увеличиваем счётчик сбитых астероидов, если номер астероида, в который должен осуществиться переход по матрице, не совпадает с номером текущего астероида, т.е. произошла смена астероида
							if ((transition_matr[(CurAsteroid)->GetNumber()][CurBullet->GetScale()] != (CurAsteroid)->GetNumber()))
							{
								schet = schet + 1;
							}
							// меняем астероид согласно матрице переходов, учитывая, что когда переход начинает повторяться по новому кругу, астероид появляется на новом месте согласно dead_matr
							changeAsteroid(&CurAsteroid, CurBullet, Asteroids, transition_matr, dead_matr);
							Count(schet);
						}

						// иначе, если не попали ни в один из астероидов на данном шаге, то сдвигаем пулю
						else
						{
							CurBullet->MoveTo(CurBullet->GetX(), CurBullet->GetY() - CurBullet->GetCaliber() - 8);
						}// if(HitBullet(CurBullet, &CurAsteroid, Asteroids))
					}// if (CurBullet->IsVisible())
				}// if

/*******************************************************Движение пули окончено**************************************************/

/**********************************************************Движение Бомбы*******************************************************/

				// проверка бомбы на попадание в летающую тарелку и астероид
				if (CurBomb->IsVisible())
				{
					// флаг того, что бомба ещё не двигалась
					move = true;
					// перебираем все летающие тарелки по порядку при каждом движении бомбы вверх
					for (i = 0; i < CountFlyingPlates; i++)
					{
						// проверяем условие столкновение бомбы и летающей тарелки
						if (Hit_FlyingPlate_Bombs(CurBomb, Plates[i]))
						{
							// меняем летающую тарелку согласно матрице переходов
							changeFlyingPlate(&CurPlate, Plates, CurBomb, transition_matr_Flying_Plate, schet);
							// убираем флаг движения
							move = false;
						}

						// иначе, если не попали ни в одну из тарелок
						else if (move)
						{
							// сдвигаем бомбу
							CurBomb->MoveTo(CurBomb->GetX(), CurBomb->GetY() - CurBomb->GetRadius() - CurBomb->GetExtra_speed());
							// один раз сдвинули и перевели флаг сдвига в false
							move = false;
						}// if
					}// for i

					// перебираем все астероиды по порядку при каждом движении бомбы вверх
					for (i = 0; i < CountMeteor; i++)
					{
						// устанавливаем i-ый астероид для рассматривания
						CurAsteroid = Asteroids[i];
						// проверяем условие столкновение бомбы и астероида
						if (Hit_Asteroids_Bombs(CurBomb, CurAsteroid))
						{
							// астероид не уничтожается бомбой
							// прячем бомбу
							CurBomb->Hide();
							// бомба больше не должна двигаться
							move = false;
						}

						// если бомба не попала ни в один из астероидов, то сдвигаем её один раз за текущее выполнение while
						else if (move)
						{
							// сдвигаем бомбу
							CurBomb->MoveTo(CurBomb->GetX(), CurBomb->GetY() - CurBomb->GetRadius() - CurBomb->GetExtra_speed());
							// один раз сдвинули и перевели флаг сдвига в false
							move = false;
						}// if
					}// for i
				}// if

/****************************************************Движение Бомбы окончено****************************************************/

/****************************************************Движение воздушного судна**************************************************/

				// ДВИЖЕНИЕ ВЛЕВО
			    // если не вышли за левую границу консоли
				if (CurShip->GetX() - step >= ShipXMin)
				{
					// и нажата 37 <- - стрелка влево на клавиатуре
					if (KEY_DOWN(VK_LEFT))
					{
						CurShip->MoveTo(CurShip->GetX() - step, CurShip->GetY());  // смещаем влево на step 
					}// // if (KEY_DOWN(VK_LEFT))
				}// if (CurShip->GetX() - step >= ShipXMin)

				// ДВИЖЕНИЕ ВПРАВО
				// если не вышли за правую границу консоли
				if (CurShip->GetX() + step <= ShipXMax)
				{
					// и нажата 39 -> - стрелка вправо на клавиатуре
					if (KEY_DOWN(VK_RIGHT))
					{
						CurShip->MoveTo(CurShip->GetX() + step, CurShip->GetY());   // смещаем вправо на step 
					}// if (KEY_DOWN(VK_RIGHT))
				}// if (CurShip->Right_Border() + step <= ShipXMax)

				// ДВИЖЕНИЕ ВНИЗ
				// если не вышли за нижнюю границу консоли
				if (CurShip->GetY() + step <= ShipYMax)
				{
					// и нажата 40 -> стрелка вниз на клавиатуре
					if (KEY_DOWN(VK_DOWN))
					{
						CurShip->MoveTo(CurShip->GetX(), CurShip->GetY() + step);    // смещаем вниз на step 
					}// if (KEY_DOWN(VK_DOWN))
				}// if (CurShip->High_Border() + step <= ShipYMax)

				// ДВИЖЕНИЕ ВВЕРХ
				// если не вышли за верхнюю границу консоли 
				if (ShipYMin <= CurShip->GetY() - step)
				{
					// и нажата 38 -> - стрелка вверх на клавиатуре
					if (KEY_DOWN(VK_UP))
					{
						CurShip->MoveTo(CurShip->GetX(), CurShip->GetY() - step);    // смещаем вверх на step 
					}// if (KEY_DOWN(VK_UP))
				}// if (CurShip->Low_Border() >= ShipYMin)

/*************************************************Движение воздушного судна окончено********************************************/

/**************************************************Смена воздушного судна при ударе*********************************************/
				
                // проверяем столкновение корабля с каждой из летающих тарелок
			    // если правая граница астероида находится между левой и правой границей корабля
				// и нижняя граница корабля находится выше нижней границы астероида и астероид не скрыт

				// или левая граница астероида меньше правой границы корабля и правая граница корабля меньше правой границы астороида
				// и верхняя граница корабля находится ниже верхней гранцы астероида и нижняя граница корабля находится ниже нижней границы астероида

				if (HitShip(CurShip, &CurAsteroid, Asteroids))
				{
					// увеличиваем счётчик на 1
					schet = schet + 1;
					// выводим изменённый счетчик на экран
					Count(schet);
					// меняем корабль после удара согласно матрице переходов
					changeShip(&CurShip, CurAsteroid, Ships, ship_matr);
				}//if (HitShip(CurShip, &CurAsteroid, Asteroids))


				// столкновение корабля с летающей тарелкой
				// проверяем столкновение корабля с каждой из тарелок
				for (int i = 0; i < CountFlyingPlates; i++)
				{
					if (HitShip_Plate(CurShip, Plates[i], schet))
					{
					    // спрятать текущий корабль
						CurShip->Hide();
						// спрятать текущую летающую тарелку
						CurPlate->Hide();

						// корабль врезался
						// очищаем экран и заканчиваем программу
						system("cls");
						// выводим надпись "конец"
						WriteEnd();
						HWND consoleWindow = GetConsoleWindow();
						// закрываем консольное окно
						PostMessage(consoleWindow, WM_CLOSE, 0, 0);
						return -1;
					}// if (HitShip(CurShip, CurAsteroid))
				}// for i

/******************************************************Воздушное судно сменено**************************************************/

/***************************************Движение астероида и проверка выхода за пределы консоли*********************************/

				// проверка астероидов на выход за пределы консоли
				for (i = 0; i < CountMeteor; i++)
				{
					// последовательно присваиваем адреса объектов указателю
					CurAsteroid = Asteroids[i];
					// астероид виден - он активен
					if (CurAsteroid->IsVisible())
					{
						// если нижняя граница астероида вышла за пределы границы консоли
						if (CurAsteroid->High_Border() >= YMaxAster)
						{
							// астероид появляется на новом месте
							RespavnAsteroid(CurAsteroid);
						}

						else
						{
							// иначе - не вышли. Астероид не двигается
							CurAsteroid->MoveTo(CurAsteroid->GetX(), CurAsteroid->GetY() + stepAsteroid);
						}// if (CurAsteroid->High_Border() >= YMaxAster)

					}// if (CurAsteroid->IsVisible())

				}// for i
/********************************************************Астероид сдвинут*******************************************************/

			}// while 1

		}// end if

	}// end if

	// Останавливаем воспроизведение музыки
	if (mciSendString(TEXT("stop music"), NULL, 0, NULL) != 0) {
		return 3;
	}

	// Закрываем файл
	if (mciSendString(TEXT("close music"), NULL, 0, NULL) != 0) {
		return 4;
	}

	return 0;
}//end main()


HWND GetConcolWindow()
{
	char str[128];
	LPWSTR title = (LPWSTR)"xxxxxxxxxxxxxxxxxx";
	GetConsoleTitle((LPWSTR)str, sizeof((LPWSTR)str));    // получить заголовок окна
	SetConsoleTitle(title);
	Sleep(100);                                           // ждем смены заголовка окна (100 мс);
	HWND hwnd = FindWindow(nullptr, (LPWSTR)title);       // определяем дескриптор окна
	SetConsoleTitle((LPWSTR)str);
	return hwnd;                                          //вернуть дескриптор окна
}//end GetConcolWindow()