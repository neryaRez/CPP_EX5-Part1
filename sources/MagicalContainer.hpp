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
        bool is_prime(int element);
    
    public:

        MagicalContainer();
        ~MagicalContainer();
        void addElement(int element);
        void removeElement(int element);
        int  size();
        
        

        class Iterator
        {
        
         protected:    

            int index_order;
            MagicalContainer* container;
            char type;

        public:

            Iterator(MagicalContainer& _container);
            Iterator();
            Iterator(const Iterator& other);
            ~Iterator();

           
            bool operator == (const Iterator& other) const;
            bool operator != (const Iterator& other) const;
            bool operator < (const Iterator& other) const;
            bool operator > (const Iterator& other) const;

            virtual int operator*() const = 0;
            

        };

        class AscendingIterator: public Iterator{

        public:
            AscendingIterator();
            AscendingIterator(MagicalContainer& _container);
            AscendingIterator(const AscendingIterator& other);
            ~AscendingIterator();

            int operator*() const override;
            AscendingIterator& operator=(const AscendingIterator& other);
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
            SideCrossIterator(MagicalContainer& _container);
            SideCrossIterator(const SideCrossIterator& other);
            ~SideCrossIterator();

            int operator*() const override;
            SideCrossIterator& operator=(const SideCrossIterator& other);
            SideCrossIterator& operator++();
            SideCrossIterator begin();
            SideCrossIterator end();

        };

        class PrimeIterator: public Iterator{

        public:
            PrimeIterator();
            PrimeIterator(MagicalContainer& _container);
            PrimeIterator(const PrimeIterator& other);
            ~PrimeIterator();

            int operator*() const override;
            PrimeIterator& operator=(const PrimeIterator& other);
            PrimeIterator& operator++();
            PrimeIterator begin();
            PrimeIterator end();

        };
        
    };

}
