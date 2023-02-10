#include <iostream>
#include <thread> // поток
#include <chrono>


//Многопоточность. Многопоточные приложения:
//Параллелизм - ускорить выполнение программы, распределив по всем ядрам
//и Конкурентность - одно ядро выполняет несколько потоков (прыжки по потокам одним ядром)
// ПРАВИЛО - Не блокировать главный поток!!! его блокируют только когда нужно остановить всю программу


void work(int a, int b) {
	std::cout << "Work started 1" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(3000)); //"лечь спать" на 3000 миллисек - тормозит поток
	std::cout << "Work thread 1:" << std::this_thread::get_id() << std::endl;
	std::cout << "Work ended 1!" << std::endl;

}

 //std::cout - не thread-safe, непотокобезопасный
int main()
{
	std::cout << "Main thread" << std::this_thread::get_id() << std::endl;
	std::thread t1(work, 5, 6); // указатель на work, принимает аргументы функции
	std::cout << "Hello 1 " << std::endl;
	t1.join(); // до join поток выполнится обязательно, и присоеденяется к главному потоку

	std::thread t2([](int a, int b) { // через лямбду проще можно реализовать
		std::cout << "Work started 2" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(3000)); 
		std::cout << "Work thread 2:" << std::this_thread::get_id() << std::endl;
		std::cout << "Work ended 2!" << std::endl;
		}, 7, 9);
	//t2.join();

	std::thread t3(work, 3, 2);
	std::cout << "Hello 3 " << std::endl;

	t3.join();
	t2.join();
}

//race condition - "гонка" состояний
// Парсер ini файлов v1 v2