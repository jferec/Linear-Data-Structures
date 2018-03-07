#ifndef AISDI_LINEAR_VECTOR_H
#define AISDI_LINEAR_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#define SIZE_OF_ARRAY 5000
namespace aisdi
{


    template <typename Type>
    class Vector
    {

    public:
        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;
        using value_type = Type;
        using pointer = Type*;
        using reference = Type&;
        using const_pointer = const Type*;
        using const_reference = const Type&;

        class ConstIterator;
        class Iterator;
        using iterator = Iterator;
        using const_iterator = ConstIterator;

        Vector()
        {
            curr_size=SIZE_OF_ARRAY;
            array=new Type[curr_size];
            next_empty_slot=0;
        }

        Vector(std::initializer_list<Type> l)
        {
            next_empty_slot=0;
            curr_size=l.size()+5;
            array=new Type[curr_size];

            for(auto it1= l.begin(); it1!=l.end();it1++)
                    append(*it1);
        }

        Vector(const Vector& other) //dodajemy elementy ze starego wektora do nowego
        {
            next_empty_slot = 0;
            curr_size = other.getSize();
            array = new Type[curr_size];


            for(ConstIterator it1= other.begin(); it1!=other.end();it1++)
                append(*it1);

        }

        Vector(Vector&& other)  //skopiowanie elementow ze starego wektora do nowego i usuniecie starego
        {

            array = other.array;
            curr_size = other.getSize();
            next_empty_slot = other.next_empty_slot;

            other.array = new Type[SIZE_OF_ARRAY];
            other.curr_size = 0;
            other.next_empty_slot = 0;


        }

        ~Vector()
        {
            delete[] array;
        }

        Vector& operator=(const Vector& other) //usun stary wektor a nastepnie przekopuj do nowego z other
        {
            delete[]array;
            next_empty_slot=0;
            curr_size = other.getSize();
            array = new Type[curr_size];

            for(ConstIterator it1= other.begin(); it1!=other.end();it1++)
                append(*it1);

            return *this;
        }

        Vector& operator=(Vector&& other)// usun stary wektor nastepnie przekopiuj do nowego z other i wyczysc other
        {
            delete[]array;
            next_empty_slot=0;
            curr_size=other.getSize();
            array = new Type[curr_size];

            for(ConstIterator it1= other.begin(); it1!=other.end();it1++)
                append(*it1);

            other.erase(other.begin(),other.end());
            return *this;
        }

        bool isEmpty() const
        {
            return next_empty_slot==0;
        }

        size_type getSize() const
        {
            return next_empty_slot;
        }


        void append(const Type& item)
        {
            if(curr_size<next_empty_slot)
                resize();

            array[next_empty_slot]=item;
            next_empty_slot++;

        }

        void prepend(const Type& item)
        {
            if(curr_size<next_empty_slot)
                resize();

            for(int i=next_empty_slot; i>0; i--)
                 array[i]=array[i-1];

            array[0] = item;
            next_empty_slot++;
        }

        void insert(const const_iterator& insertPosition, const Type& item)
        {
            if(insertPosition.index>next_empty_slot)
                throw std::logic_error("Logic error; can't insert element beyond vector");
            if (curr_size<next_empty_slot)
                resize();

            if (insertPosition == cbegin()) {
                prepend(item);
                return;
            }
            if (insertPosition == cend()) {
                append(item);
                return;
            }

            int insert_index = insertPosition.index;

            for(int i =next_empty_slot; i>insert_index;i--)
                 array[i]=array[i-1];

            array[insert_index] = item;
            next_empty_slot++;

        }

        Type popFirst()
        {
            if(isEmpty())
                throw std::out_of_range("Vector is empty");
            Type temp = array[0];

            for(int i=1;i<(int)next_empty_slot;i++)
                array[i-1]=array[i];
            next_empty_slot--;

            return temp;
        }


        void resize()
        {
            curr_size *= 2;
            Type *bigger_array;

            bigger_array = new Type[curr_size];
            for (int i = 0; i < (int)next_empty_slot; i++)
                bigger_array[i] = array[i];
            delete [] array;
            array=bigger_array;
        }

        Type popLast()
        {
            if(isEmpty())
                throw std::out_of_range("Vector is empty, pop not available");
            Type temp = array[next_empty_slot-1];
            next_empty_slot--;

            return temp;
        }

        void erase(const const_iterator& possition)
        {

            if(possition.index>=next_empty_slot || isEmpty())
                throw std::out_of_range("Iterator is out of range");


            for(int i=possition.index;i<(int)next_empty_slot;i++)
                array[i]=array[i+1];
            next_empty_slot--;
        }


        void erase(const const_iterator& firstIncluded, const const_iterator& lastExcluded)
        {
            size_type delete_index_begin = firstIncluded.index;
            size_type delete_index_end = lastExcluded.index;

            if(firstIncluded==lastExcluded)
                return;

            if(firstIncluded.index>=lastExcluded.index)
                throw std::logic_error("Logic error; end>begin");

            if(delete_index_end - delete_index_begin > next_empty_slot/2)
            {
                size_type new_size= getSize() - (delete_index_end - delete_index_begin);
                Type *new_array = new Type[new_size];

                ConstIterator curr_iterator=cbegin();

                int i = 0;
                while(curr_iterator!=cend())
                {
                    if (curr_iterator.index < delete_index_begin || curr_iterator.index >= delete_index_end)
                    {
                        new_array[i] = *curr_iterator;
                        i++;
                    }
                    ++curr_iterator;
                }

                delete[] array;
                array = new_array;
                next_empty_slot = i;
                curr_size = new_size;
            }
            else
            {
                while (delete_index_end < next_empty_slot) {
                    array[delete_index_begin] = array[delete_index_end];
                    delete_index_begin++;
                    delete_index_end++;
                }

                while (delete_index_end > delete_index_begin) {
                    popLast();
                    delete_index_end--;
                }
            }
        }

        iterator begin()
        {

            return iterator(cbegin());

        }

        iterator end()
        {
            return iterator(cend());
        }


        const_iterator cbegin() const
        {

            return ConstIterator(this,&(array[0]),0);
        }

        const_iterator cend() const
        {
            return ConstIterator(this,&(array[next_empty_slot]),next_empty_slot);
        }

        const_iterator begin() const
        {
            return cbegin();
        }

        const_iterator end() const
        {
            return cend();
        }

    private:

        Type *array;
        size_type next_empty_slot;
        size_type curr_size;

    };

    template <typename Type>
    class Vector<Type>::ConstIterator
    {


    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = typename Vector::value_type;
        using difference_type = typename Vector::difference_type;
        using pointer = typename Vector::const_pointer;
        using reference = typename Vector::const_reference;



        explicit ConstIterator()
        {
            iter= nullptr;
        }
        ConstIterator(const Vector<Type> *iterVec2,Type* actual,int index2):index(index2),iterVec(iterVec2),iter(actual)
        {}

        reference operator*() const
        {
            if(iterVec->getSize()<=index)
                throw std::out_of_range("Iterator is out of range");

            return *iter;
        }

        ConstIterator& operator++() //pre
        {
            if(iterVec->getSize()<=index)
                throw std::out_of_range("Iterator is out of range");
            iter++;
            index++;

            return *this;
        }

        ConstIterator operator++(int) //post
        {
            if(iterVec->getSize()<=index)
                throw std::out_of_range("Iterator is out of range");
            ConstIterator temp= *this;
            index++;
            iter++;

            return temp;

        }

        ConstIterator& operator--() //pre
        {
            if(index==0)
                throw std::out_of_range("Iterator is out of range");
            iter--;
            index--;
            return *this;

        }

        ConstIterator operator--(int) //post
        {
            if(index==0)
                throw std::out_of_range("Iterator is out of range");
            ConstIterator temp= *this;
            iter--;
            index--;
            return temp;
        }

        ConstIterator operator+(difference_type d) const
        {
            if((index+d)>(iterVec->next_empty_slot))
                throw std::out_of_range("Iterator is out of range");

            return ConstIterator(iterVec,&(iterVec->array[index+d]) , index+d);
        }

        ConstIterator operator-(difference_type d) const
        {
            if((index-d)<0)
                throw std::out_of_range("Iterator is out of range");

            return ConstIterator(iterVec,&(iterVec->array[index-d]) , index-d);
        }

        bool operator==(const ConstIterator& other) const
        {
            return iter == other.iter;
        }

        bool operator!=(const ConstIterator& other) const
        {
            return iter != other.iter;
        }

        size_type index;

        private:
            const Vector<Type> *iterVec;
            Type *iter;



    };

    template <typename Type>
    class Vector<Type>::Iterator : public Vector<Type>::ConstIterator
    {
    public:
        using pointer = typename Vector::pointer;
        using reference = typename Vector::reference;


        explicit Iterator() {
        }

        Iterator(const ConstIterator& other)
                : ConstIterator(other)
        {}

        Iterator& operator++()
        {
            ConstIterator::operator++();
            return *this;
        }

        Iterator operator++(int)
        {
            auto result = *this;
            ConstIterator::operator++();
            return result;
        }

        Iterator& operator--()
        {
            ConstIterator::operator--();
            return *this;
        }

        Iterator operator--(int)
        {
            auto result = *this;
            ConstIterator::operator--();
            return result;
        }

        Iterator operator+(difference_type d) const
        {
            return ConstIterator::operator+(d);
        }

        Iterator operator-(difference_type d) const
        {
            return ConstIterator::operator-(d);
        }

        reference operator*() const
        {
            // ugly cast, yet reduces code duplication.
            return const_cast<reference>(ConstIterator::operator*());
        }


    };

}

#endif // AISDI_LINEAR_VECTOR_H
