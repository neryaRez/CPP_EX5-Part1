#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cstdbool>
#include <cmath>

using namespace std;

namespace ariel{

    /**@MagcalCntainer
     * 
     * This class represents Container which can be used to iterating in 3 different ways:
     * 
     * @category Ascending order - passes through the vector and represents all of the data in ascending order.
     * @category SideCrossIterator - passes throgh the vector, such that it holds 2 pointers, 1 for start and 1 for end,
     * as it increases the start and decreases the end immidiately for each time thrghout the loop.
     * @category Primes only - represents only the prime numbers.
     * 
     * All of the Iterators should operate their methods in O(1).
     * Therefore there is a vector of the addresses of each prime number from the base vector. 
     * 
     * @param data - the base vector
     * @param primes - the vector of the addresses of the primes from the base vector.
     * 
     * @method update_primes() - to update the primes vector, for every deletion and insertion.
     * @method is_prime(int element)- to check if a given number is prime.
     * @method size() - return the size of the base vector, "data".
     * 
    */

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

        /**@Iterator
         * An abstract class represents an iterator with comparison operators, and a pointer to MagicalContainer.
         * 
         * Has 3 derived classes - in order to operate the special iterators as mentioned before, at the desription of 
         * the "MagicalContainer" class.
         * 
         * @param Integer called "index_order"- to represent the logical order for each derived class.
         * @param  char called "type" - to represent each derived class, of what kind of iterator is it.
         * 
         * Has virtual method of a "dereferensing operator" for each derived class.
        */
        
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

        /**@AscendingIterator
         * Derived class of Iterator.
         * Represents the ascending order operator.
         * Has its own implementation to the "dereferensing operator".
         * 
         * @method begin() - returns the start_point of the iterator.
         * @method end()   - returns the end_point of the iterator.
         * @overload operator ++ - to increase the iterator by its logical order.
         * 
        */

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

           /**@SideCrossIterator
         * Derived class of Iterator.
         * Represents the SideCross order operator.
         * Has its own implementation to the "dereferensing operator".
         * 
         * @method begin() - returns the start_point of the iterator.
         * @method end()   - returns the end_point of the iterator.
         * @overload operator ++ - to increase the iterator by its logical order.
         * 
        */

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

              /**@PrimeIterator
         * Derived class of Iterator.
         * Represents the Prime order operator.
         * Has its own implementation to the "dereferensing operator".
         * 
         * @method begin() - returns the start_point of the iterator.
         * @method end()   - returns the end_point of the iterator.
         * @overload operator ++ - to increase the iterator by its logical order.
         * 
        */
        
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
