#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cstdbool>
#include <cmath>

using namespace std;

namespace ariel{

    class MagicalContainer
    {
    private:
        vector<int> data;
        vector<int*> primes;
        void update_primes();

    public:

        MagicalContainer();
        ~MagicalContainer();
        void addElement(int element);
        void removeElement(int element);
        int  size();
        bool is_prime(int element);
        

        class Iterator
        {
        
         protected:    

            int position;
            int index_order;
            MagicalContainer* my_container;
            char type;

        public:

            Iterator(MagicalContainer& my_cntainer);
            Iterator();
            Iterator(const Iterator& other);
            ~Iterator();

            Iterator& operator=(const Iterator& other);
            bool operator == (const Iterator& other) const;
            bool operator != (const Iterator& other) const;
            bool operator < (const Iterator& other) const;
            bool operator > (const Iterator& other) const;
            virtual int operator*() const;

            int get_position();
            int get_index_order();

        };

        class AscendingIterator: public Iterator{

        public:
            AscendingIterator();
            AscendingIterator(MagicalContainer& my_container);
            AscendingIterator(const AscendingIterator& other);
            ~AscendingIterator();

            AscendingIterator& operator++();
            AscendingIterator begin();
            AscendingIterator end();

        };

        class SideCrossIterator: public Iterator{

        private:
            int end_index;
            int start_index;
        
        public:
            SideCrossIterator();
            SideCrossIterator(MagicalContainer& my_container);
            SideCrossIterator(const SideCrossIterator& other);
            ~SideCrossIterator();
            
            SideCrossIterator& operator++();
            SideCrossIterator begin();
            SideCrossIterator end();

        };

        class PrimeIterator: public Iterator{

        public:
            PrimeIterator();
            PrimeIterator(MagicalContainer& my_container);
            PrimeIterator(const PrimeIterator& other);
            ~PrimeIterator();
             int operator*() const override;

            PrimeIterator& operator++();
            PrimeIterator begin();
            PrimeIterator end();

        };
        
    };

}
