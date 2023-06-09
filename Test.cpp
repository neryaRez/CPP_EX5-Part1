#include "doctest.h"
#include "sources/MagicalContainer.hpp"
#include <stdexcept>

using namespace ariel;
using namespace std;

TEST_SUITE("MagicalContainer class"){
    MagicalContainer a;
    MagicalContainer a2;

    TEST_CASE("Add Function"){

        vector<int> b = {1,2,3,4,5,6,7,8,9,10};
        for (size_t i = 0; i < 10; i++)
        {
            a.addElement(b[i]);
        }

        MagicalContainer::AscendingIterator it_magic(a);

        for (size_t i =0; i< 10; i++)
        {
            CHECK_EQ( b[i], *it_magic);
            ++it_magic;
        }

        vector<int> c = {0,0,0,1,1,1,2};
       
        // trying to add 0 and 1 more than once!
        for (size_t i = 0; i < c.size(); i++)
        {
            a2.addElement(c[i]);
        }
        

        MagicalContainer::AscendingIterator it_magic2(a2); // points to 0.

        ++it_magic2; // points to 1 ,because 0 cannot added more than once !
        CHECK_EQ(*it_magic2, 1);
        ++it_magic2; // points to 2 ,because 1 cannot added more than once !
        CHECK_EQ(*it_magic2, 2);

        a2.addElement(3);
        CHECK_NOTHROW(a2.addElement(3));

        
    }

    TEST_CASE("Remove Function"){

        a.removeElement(5);
        a.removeElement(10);

        MagicalContainer::AscendingIterator it_magical(a);

        for (; it_magical != it_magical.end(); ++it_magical)
        {
             CHECK_NE(*it_magical, 5);
             CHECK_NE(*it_magical, 10);
        }

        CHECK_THROWS(a.removeElement(20));
        CHECK_THROWS(a.removeElement(5));
        CHECK_THROWS(a.removeElement(10));

        CHECK_NOTHROW(a2.removeElement(2));

    }

    TEST_CASE("Size Function"){

        CHECK(a.size() == 8);
        CHECK_FALSE(a.size() == 6);

        a.removeElement(9);
        CHECK(a.size() == 7);

        a.addElement(11);
        a.addElement(12);
        a.addElement(13);
        a.addElement(123);

        CHECK_EQ(a.size(), 11);

    }

    
}

TEST_SUITE("Ascending Iterator"){

    MagicalContainer con;

    TEST_CASE("Dereference and ++ operators"){

        con.addElement(1);
        con.addElement(-4);
        con.addElement(5);
        con.addElement(7);
        con.addElement(2);
        con.addElement(4);

        vector<int> sorted_vec = {-4,1,2,4,5,7};

        MagicalContainer::AscendingIterator it(con);

        for (size_t i = 0; i < sorted_vec.size(); i++)
        {
           CHECK_EQ(sorted_vec[i], *it);
           ++it;
        }

        CHECK_THROWS(++it); // End Should not be incremented . 

        MagicalContainer::AscendingIterator it2(con);

        CHECK_NOTHROW(++it2);
        
    }

    TEST_CASE("Begin and End"){

        MagicalContainer::AscendingIterator it(con);

        it = it.begin();

        CHECK_EQ(*it, -4);

        it = it.end();

        CHECK_THROWS(*it); // end should not be dreferenced

    }

    TEST_CASE("Assignment operator"){

        MagicalContainer::AscendingIterator it(con);

        it = ++it;
        CHECK_EQ(*it , 1);

        MagicalContainer::AscendingIterator it2(con);

        ++ ( ++ (++it2));

        it = it2; 

        CHECK_EQ(*it, *it2);

        MagicalContainer d;
        MagicalContainer::AscendingIterator it3(d);
        CHECK_THROWS(it3 = it);
        CHECK_NOTHROW(it2 = it);

    }

    TEST_CASE("Comparison operators"){

        MagicalContainer f;
        vector<int> vec_f = {1,2,3,4,5,6,7,8,9,10};

        for (size_t i = 0; i < 10; i++) f.addElement(vec_f[i]);

        MagicalContainer::AscendingIterator it(f), it2(f), it3(f), it4(f), it5(f);

        it5 = it.end();

        ++it2;

        ++(++it3);
        ++(++(++it4));

        CHECK(it2 > it);
        CHECK(it2 < it3);
        CHECK(it4 > it3);

        CHECK(((it5 > it4)&&(it5 > it3)&&(it5 > it2) &&(it5 > it)));

        MagicalContainer::AscendingIterator it6(f);
        ++it6;

        CHECK(it6 == it2);
        CHECK_FALSE(it6 == it4);
        CHECK_FALSE(it6 != it2);
        
        MagicalContainer f1;
        MagicalContainer::AscendingIterator it7(f1);
        it7 = it7.begin();

        CHECK_THROWS(it7 = it);

    }

    TEST_CASE("Change the Container During the Iterator"){

        MagicalContainer a;
        vector<int> vec_a = {1,3,5,7,9,11,13,15,17,19};

        for (size_t i = 0; i < vec_a.size(); i++) a.addElement(vec_a[i]);

        MagicalContainer::AscendingIterator it(a);

        ++it;

        ++it;

        ++it;

        a.removeElement(15);
        a.removeElement(17);

        for (; it !=it.end(); ++it)
        {
            CHECK_NE(*it, 15);
            CHECK_NE(*it, 17);
        }


    }


}

TEST_SUITE("Side Cross Iterator"){

    MagicalContainer g;

    TEST_CASE("Dereference and ++ operators"){

        vector<int> vec_g = {1,2,3,4,5,6,7,8,9,10};

        for (size_t i = 0; i < 10; i++) g.addElement(vec_g[i]);

        MagicalContainer::SideCrossIterator side(g);

        vector<int> sorted_side = {1,10,2,9,3,8,4,7,5,6};

        for (size_t i = 0; i < g.size(); i++)
        {
            CHECK_EQ(sorted_side[i],*side);
            ++side;
        }
        CHECK_THROWS(++side); // end should not be incremented

    }

    TEST_CASE("Begin and End"){

        MagicalContainer::SideCrossIterator  it(g);

        it = it.begin();

        CHECK_EQ(*it, 1);

        it = it.end();

        CHECK_THROWS(*it); // end should not be dreferenced
    }

    TEST_CASE("Assignment operator"){

        MagicalContainer::SideCrossIterator it(g);

        it = ++it;
        CHECK_EQ(*it , 10);

        MagicalContainer::SideCrossIterator it2(g);

        ++ ( ++ (++it2));

        it = it2; 

        CHECK_EQ(*it, *it2);

        MagicalContainer d;
        MagicalContainer::SideCrossIterator it3(d);
        CHECK_THROWS(it3 = it);
        CHECK_NOTHROW(it2 = it);

    }

    TEST_CASE("Comparison Operators"){
        MagicalContainer::SideCrossIterator it(g), it2(g), it3(g), it4(g);

        CHECK(((it == it2)&&(it2 ==it3)&&(it3 ==it4)));

        CHECK_FALSE(((it != it2)&&(it2 != it3)&&(it3 != it4)));

        ++it2, ++(++it3), ++(++(++it4));

        CHECK(((it2 > it)&&(it2 < it3) &&(it4 > it3)));
        
        CHECK_FALSE(((it2 < it)&&(it > it3)&&(it4 <it2)));

        MagicalContainer h;

        MagicalContainer::SideCrossIterator it5(h);

        CHECK_THROWS(it5 = it2);
        CHECK_THROWS(it5 = it2);


    }

        TEST_CASE("Change the Container During the Iterator"){

        MagicalContainer a;
        vector<int> vec_a = {1,3,5,7,9,11,13,15,17,19};

        for (size_t i = 0; i < vec_a.size(); i++) a.addElement(vec_a[i]);

        MagicalContainer::SideCrossIterator it(a);

         ++it;

        a.removeElement(15);
        a.removeElement(17);

        for (; it !=it.end(); ++it)
        {
            CHECK_NE(*it, 15);
            CHECK_NE(*it, 17);
        }


    }

}

TEST_SUITE("Prime Iterator"){

    MagicalContainer p;

    TEST_CASE("Dereference and ++ operators"){

        vector<int> vec_p = {1,2,3,4,5,6,7,8,9,10};

        for (size_t i = 0; i < 10; i++) p.addElement(vec_p[i]);

        MagicalContainer::PrimeIterator prime_it(p);

        vector<int> primes = {2,3,5,7};

        for (size_t i = 0; i < primes.size(); i++)
        {
            CHECK_EQ(primes[i],*prime_it);
            ++prime_it;
        }

        CHECK_THROWS(++prime_it); // end should not be incremented

    }

    TEST_CASE("Begin and End"){

        MagicalContainer::PrimeIterator it(p);

        it = it.begin();

        CHECK_EQ(*it, 2);

        it = it.end();

        CHECK_THROWS(*it); // end should not be dreferenced
    }

    TEST_CASE("Assignment operator"){

        MagicalContainer::PrimeIterator it(p);

        it = ++it;
        CHECK_EQ(*it , 3);

        MagicalContainer::PrimeIterator it2(p);

        ++ ( ++ (it2));

        it = it2; 

        CHECK_EQ(*it, *it2);

        MagicalContainer d;
        MagicalContainer::PrimeIterator it3(d);
        CHECK_THROWS(it3 = it);
        CHECK_NOTHROW(it2 = it);

    }

    TEST_CASE("Comparison Operators"){
        MagicalContainer::PrimeIterator it(p), it2(p), it3(p), it4(p);

        CHECK(((it == it2)&&(it2 ==it3)&&(it3 ==it4)));

        CHECK_FALSE(((it != it2)&&(it2 != it3)&&(it3 != it4)));

        ++it2, ++(++it3), ++(++(++it4));

        CHECK(((it2 > it)&&(it2 < it3) &&(it4 > it3)));
        
        CHECK_FALSE(((it2 < it)&&(it > it3)&&(it4 <it2)));

        MagicalContainer h;

        MagicalContainer::PrimeIterator it5(h);

        CHECK_THROWS(it5 = it2);
        CHECK_THROWS(it5 = it2);


    }

        TEST_CASE("Change the Container During the Iterator"){

        MagicalContainer a;
        vector<int> vec_a = {1,3,5,7,9,11,13,15,17,19};

        for (size_t i = 0; i < vec_a.size(); i++) a.addElement(vec_a[i]);

        MagicalContainer::SideCrossIterator it(a);

        ++it;

        a.removeElement(13);
        a.removeElement(17);

        for (; it !=it.end(); ++it)
        {
            CHECK_NE(*it, 13);
            CHECK_NE(*it, 17);
        }


    }

}


