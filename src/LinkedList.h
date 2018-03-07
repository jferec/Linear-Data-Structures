
#ifndef AISDI_LINEAR_LINKEDLIST_H
#define AISDI_LINEAR_LINKEDLIST_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace aisdi
{

    template <typename Type>
    struct Node
    {
        Type value;
        Node *prev;
        Node *next;

        ~Node()
        {
            next=nullptr;
            prev=nullptr;
        }
        Node()
        {
            next=nullptr;
            prev=nullptr;
        }
        Node(Type value)
        {
            this->value = value;
            next=nullptr;
            prev=nullptr;

        }

    };

    template <typename Type>
    class LinkedList
    {
    public:
        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;
        using value_type = Type;
        using pointer = Type*;
        using reference = Type&;
        using const_pointer = const Type*;
        using const_reference = const Type&;

        class Iterator;
        using iterator = Iterator;
        class ConstIterator;
        using const_iterator = ConstIterator;



        LinkedList()   //pusta lista
        {
            headguard=new Node<Type>();
            tailguard=new Node<Type>();
            headguard->next=tailguard;
            tailguard->prev=headguard;

        }

        LinkedList(std::initializer_list<Type> l):LinkedList()
        {
            auto it=l.begin();
            while(it!=l.end())
                this->append(*it++);

        }

        LinkedList(const LinkedList& other):LinkedList() //dodajemy elementy ze starej listy do nowej
        {
            auto it=other.begin();
            while(it!=other.end())
                this->append(*it++);
        }

        LinkedList(LinkedList&& other):LinkedList()
        {

                while(!other.isEmpty())
                {
                    append(*(other.begin()));//dodajemy element starej do nowej listy
                    other.erase(other.begin());//usuwamy element ze starej listy (ten ktory dodalismy)
                }

        }


        ~LinkedList()
        {

            Node<Type>* temp= headguard->next;
            Node<Type>* curr= headguard->next;
            while(temp!=tailguard)
                {
                temp=curr;
                curr=curr->next;
                delete temp;
                }
            delete headguard;
        }

        LinkedList& operator=(const LinkedList& other)
        {
            erase(begin(), end());// usuwamy wszystkie elementy ze starej listy

            for(auto it=other.begin();it!=(other.end());++it)
                append(*it);// dodajemy z other  do nowej wszystkie elementy


            return *this;
        }

        LinkedList& operator=(LinkedList&& other)
        {
            while(!isEmpty())//usuwamy wszystkie elementy ze starej listy
                erase(begin());
            while(!other.isEmpty()) {
                append(*(other.begin()));//dodajemy z other do starej wszystkie elementy
                other.erase(other.begin());//usuwamy z other wszystkie elementy
            }
            return* this;
        }

        bool isEmpty() const
        {
            return headguard->next==tailguard;
        }

        size_type getSize() const
        {
            if(isEmpty())
                return 0;
            else
            {

                Node<Type>* temp = headguard->next;
                int l=0;
                while(temp!=tailguard)
                {
                    l++;
                    temp=temp->next;
                }

                return l;
            }
        }

        void append(const Type& item)
        {
            Node<Type>* n= new Node<Type>(item);
            tailguard->prev->next=n;
            n->prev=tailguard->prev;
            tailguard->prev=n;
            n->next=tailguard;
        }

        void prepend(const Type& item)
        {
            Node<Type>* n= new Node<Type>(item);
            n->next=headguard->next;
            headguard->next->prev = n;
            n->prev=headguard;
            headguard->next=n;

        }

        void insert(const const_iterator& insertPosition, const Type& item)
        {

            Node<Type>* n = new Node<Type>(item);
            n->next = insertPosition.iter;
            n->prev=insertPosition.iter->prev;
            insertPosition.iter->prev->next = n;
            insertPosition.iter->prev = n
;        }


        Type popFirst()
        {
            if(isEmpty())
                throw std::out_of_range("Error, list is empty");
            Type temp=*begin();
            erase(begin());
            return temp;
        }
        Type popLast()
        {
            if(isEmpty())
                throw std::out_of_range("Error, list is empty");
            Type temp=*(end()-1);
            erase(end()-1);
            return temp;
        }

        void erase(const const_iterator& possition)
        {
            if(possition.iter->next==nullptr || possition.iter->prev==nullptr)
            {
                throw std::out_of_range("Can't erase headguard/tailguard");
            }

            possition.iter->next->prev=possition.iter->prev;
            possition.iter->prev->next=possition.iter->next;
            delete possition.iter;
        }

        void erase(const const_iterator& firstIncluded, const const_iterator& lastExcluded)
        {
            auto it = firstIncluded;
            while(it!=lastExcluded)
                   erase(it++);
        }

        iterator begin()
        {
            return iterator(headguard->next);

        }

        iterator end()
        {
            return iterator(tailguard);
        }

        const_iterator cbegin() const
        {
            return const_iterator(headguard->next);
        }

        const_iterator cend() const
        {
            return const_iterator(tailguard);
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
        Node<Type> *headguard;
        Node<Type> *tailguard;
    };

    template <typename Type>
    class LinkedList<Type>::ConstIterator
    {
    private:
        Node<Type>* iter;
        friend void LinkedList <Type>::insert(const const_iterator&, const Type&);
        friend void LinkedList <Type>::erase(const const_iterator&);

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = typename LinkedList::value_type;
        using difference_type = typename LinkedList::difference_type;
        using pointer = typename LinkedList::const_pointer;
        using reference = typename LinkedList::const_reference;

        explicit ConstIterator()
        {
        }

        ConstIterator(Node<Type>* p)
        {
            iter=p;
        }


        reference operator*() const
        {
            if(iter->next!=nullptr && iter->prev!=nullptr)
                return iter->value;
            else throw std::out_of_range("Iterator out of range");
        }

        ConstIterator& operator++() // preincr
        {
            if(iter->next!=nullptr)
            {
                iter=iter->next;
                return *this;
            }
            else throw std::out_of_range("Iterator out of range");
        }

        ConstIterator operator++(int) // postincr
        {
            if(iter->next!=nullptr)
            {
                ConstIterator temp= *this;
                iter=iter->next;
                return temp;
            }
            else throw std::out_of_range("Iterator out of range");
        }

        ConstIterator& operator--() //preincr
        {
            if(iter->prev->prev!=nullptr )
            {
                iter=iter->prev;
                return *this;
            }
            else throw std::out_of_range("Iterator out of range");
        }

        ConstIterator operator--(int)   //postincr
        {
            if(iter->prev->prev!=nullptr)
            {
                ConstIterator temp= *this;
                iter=iter->prev;
                return temp;
            }
            else throw std::out_of_range("Iterator out of range");
        }

        ConstIterator operator+(difference_type d) const
        {
            ConstIterator temp=*this;
            if(d>=0){
                for(int i =0; i < d; i++)
                    ++temp;
                }
            else
                for(int i = 0; i > d; i--)
                {
                    --temp;
                }
            return temp;
        }

        ConstIterator operator-(difference_type d) const
        {
            ConstIterator temp=*this;
            if(d>=0){
                for(int i =0; i < d; i++)
                    --temp;
                }
            else
                for(int i = 0; i > d; i--)
                {
                    ++temp;
                }
            return temp;
        }


        bool operator==(const ConstIterator & other)const
        {

            return iter==other.iter;
        }

        bool operator!=(const ConstIterator & other) const
        {
            return iter!=other.iter;

        }




    };

    template <typename Type>
    class LinkedList<Type>::Iterator : public LinkedList<Type>::ConstIterator
    {
    public:
        using pointer = typename LinkedList::pointer;
        using reference = typename LinkedList::reference;

        explicit Iterator()
        {}

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

#endif // AISDI_LINEAR_LINKEDLIST_H
