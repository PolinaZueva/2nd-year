#ifndef TUPLE_PRINT_H
#define TUPLE_PRINT_H

#include <iostream>
#include <string>
#include <tuple>

template<typename Tuple, unsigned index, unsigned tuple_size>  //доступ к элементу по индексу
class TuplePrint {
public:
	//рекурсивно, когда индекс равен размеру кортежа, то конец
	static void print(std::ostream& out, const Tuple& tuple) {  //std::ostream — это базовый класс для всех потоков вывода, включая std::cout, std::ofstream
		out << std::get<index>(tuple) << ", ";
		TuplePrint<Tuple, index + 1, tuple_size>::print(out, tuple);
	}
};

//для последнего элемента кортежа
template<typename Tuple, unsigned tuple_size>
class TuplePrint<Tuple, tuple_size, tuple_size> {
public:
	static void print(std::ostream& out, const Tuple& tuple) {
		out << std::get<tuple_size>(tuple);
	}
};

//перегрузка оператора <<
template<typename... Args> 
std::ostream& operator<<(std::ostream& out, const std::tuple<Args...>& tuple) {
	out << "(";
	if (sizeof...(Args) > 0) {  //кортеж не пуст?
		TuplePrint<std::tuple<Args...>, 0, sizeof...(Args) - 1>::print(out, tuple);
	}
	out << ")";
	return out;
}

#endif // TUPLE_PRINT_H


