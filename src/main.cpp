#include "Vector.h"
#include "LinkedList.h"
#include <iostream>
#include <time.h>

int main()
{

    int NUMBER_OF_ELEMENTS=50000;
	unsigned int RANGE=500000;

    clock_t first_clock,second_clock;


    long double add_time_list=0;
	long double add_time_vector=0;
	long double average_time_vector=0;
	long double average_time_list=0;
    long double delete_time_list=0;
    long double delete_time_vector=0;

//WSZYSTKIE TESTY DODAWANIA SA PRZEPROWADZANE 10 RAZY A NASTEPNIE WYCIAGANY JEST CZAS SREDNI
    std::cout<<"Sredni czas wstawiania za pomocą funkcji append dla opowiednio:"<<std::endl;


   for (size_t i=0;i<RANGE;i=i+50000)
    {
      for(int n=0;n<10;n++)
        {aisdi::Vector<int> *test_vector=new aisdi::Vector<int>;

        first_clock=clock();
		for (int i=0;i<=NUMBER_OF_ELEMENTS;i++)
		{
			test_vector->append(7);
		}
		second_clock=clock();
		add_time_vector=(long double)(second_clock-first_clock)/CLOCKS_PER_SEC;
		average_time_vector=average_time_vector+add_time_vector;

        delete test_vector;
        }

        std::cout<<"test_vectora dla "<<NUMBER_OF_ELEMENTS<<" elementow wynosi:"<<average_time_vector/10<<"\n";
        average_time_vector=0;


        for(int n=0;n<10;n++)
        {
        aisdi::LinkedList<int> *test_list=new aisdi::LinkedList<int>;

        first_clock=clock();
		for (int i=0;i<=NUMBER_OF_ELEMENTS;i++)
		{
			test_list->append(7);
		}
		second_clock=clock();
		add_time_list=(long double)(second_clock-first_clock)/CLOCKS_PER_SEC;
		average_time_list=average_time_list+add_time_list;

        delete test_list;
        }

        std::cout<<"listy dla "<<NUMBER_OF_ELEMENTS<<" elementow wynosi:"<<average_time_list/10<<"\n";
        average_time_list=0;
        std::cout<<"\n";


		NUMBER_OF_ELEMENTS+=50000;
    }



        NUMBER_OF_ELEMENTS=10000;
        RANGE=100000;

     std::cout<<"Sredni czas wstawiania za pomocą funkcji prepend dla opowiednio:"<<std::endl;
    for (size_t i=0;i<RANGE;i=i+10000)
    {
      for(int n=0;n<10;n++)
        {aisdi::Vector<int> *test_vector=new aisdi::Vector<int>;

        first_clock=clock();
		for (int i=0;i<=NUMBER_OF_ELEMENTS;i++)
		{
			test_vector->prepend(7);
		}
		second_clock=clock();
		add_time_vector=(long double)(second_clock-first_clock)/CLOCKS_PER_SEC;
		average_time_vector=average_time_vector+add_time_vector;

        delete test_vector;
        }
        std::cout<<"test_vectora dla "<<NUMBER_OF_ELEMENTS<<" elementow wynosi:"<<average_time_vector/10<<"\n";
        average_time_vector=0;


        for(int n=0;n<10;n++)
        {
        aisdi::LinkedList<int> *test_list=new aisdi::LinkedList<int>;

        first_clock=clock();
		for (int i=0;i<=NUMBER_OF_ELEMENTS;i++)
		{
			test_list->prepend(7);
		}
		second_clock=clock();
		add_time_list=(long double)(second_clock-first_clock)/CLOCKS_PER_SEC;
		average_time_list=average_time_list+add_time_list;

        delete test_list;
        }
        std::cout<<"listy dla "<<NUMBER_OF_ELEMENTS<<" elementow wynosi:"<<average_time_list/10<<"\n";
        average_time_list=0;
        std::cout<<"\n";

        NUMBER_OF_ELEMENTS+=10000;
    }




        NUMBER_OF_ELEMENTS=1000000;
        aisdi::Vector<int> test_vector;
        aisdi::LinkedList<int> test_list;
        for (int i=0;i<=NUMBER_OF_ELEMENTS;i++)
		{
			test_list.append(7);
			test_vector.append(7);
		}
		first_clock=clock();
		test_vector.insert(test_vector.begin()+50000,10);
		second_clock=clock();
		long double add_middle_vector=(long double)(second_clock-first_clock)/CLOCKS_PER_SEC;
		std::cout<<"Czas wstawiania do srodka vectora 10^6 elementow: "<<add_middle_vector<<std::endl;

		first_clock=clock();
		test_list.insert(test_list.begin()+50000,10);
		second_clock=clock();
		long double add_middle_list=(long double)(second_clock-first_clock)/CLOCKS_PER_SEC;
		std::cout<<"Czas wstawiania do srodka listy 10^6 elementow: "<<add_middle_list<<std::endl;




        first_clock=clock();
        test_vector.erase(test_vector.begin(),test_vector.end());
        second_clock=clock();
		delete_time_vector=(long double)(second_clock-first_clock)/CLOCKS_PER_SEC;
		std::cout<<"Czas usuwania z test_vectora "<<NUMBER_OF_ELEMENTS<<" elementow wynosi: "<<delete_time_vector<<std::endl;

		first_clock=clock();
        test_list.erase(test_list.begin(),test_list.end());
        second_clock=clock();
		delete_time_list=(long double)(second_clock-first_clock)/CLOCKS_PER_SEC;
		std::cout<<"Czas usuwania z listy "<<NUMBER_OF_ELEMENTS<<" elementow wynosi:"<<delete_time_list<<"\n";


	return 0;
}
