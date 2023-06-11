#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

namespace ariel
{
    class MagicalContainer
    {
    private:
        vector<int> container;
        vector<int> pri_container;
        bool isPrime(int num)
        {
            if (num <= 1)
            {
                return false;
            }
            for (int i = 2; i <= sqrt(num); ++i)
            {
                if (num % i == 0)
                {
                    return false;
                }
            }
            return true;
        }

    public:
        MagicalContainer();                        // defult constructor.
        MagicalContainer(MagicalContainer &other); // copy constructor.
        ~MagicalContainer();                       // destructor.

        void addElement(int element);
        size_t size() const;
        void removeElement(int element);

        //-----------------------------------------------------

        class AscendingIterator
        {
        private:
            const MagicalContainer *container;
            size_t current;

        public:
            AscendingIterator(const MagicalContainer &container);
            AscendingIterator(const AscendingIterator &other);
            AscendingIterator(const MagicalContainer &container, size_t current);

            AscendingIterator begin();
            AscendingIterator end();

            AscendingIterator &operator=(const AscendingIterator &other);
            bool operator==(const AscendingIterator &other) const;
            bool operator!=(const AscendingIterator &other) const;
            bool operator>(const AscendingIterator &other) const;
            bool operator<(const AscendingIterator &other) const;

            AscendingIterator &operator++();
            int operator*() const;
        };

        //------------------------------------------------------

        class SideCrossIterator
        {

        private:
            const MagicalContainer *container;
            std::vector<int>::size_type cross_it;
            std::vector<int>::size_type current;

        public:
            SideCrossIterator(const MagicalContainer &container, size_t index = 0, size_t crossindex = 0);
            SideCrossIterator(const SideCrossIterator &other);

            SideCrossIterator begin();
            SideCrossIterator end();

            SideCrossIterator &operator=(const SideCrossIterator &other);
            bool operator==(const SideCrossIterator &other) const;
            bool operator!=(const SideCrossIterator &other) const;
            bool operator>(const SideCrossIterator &other) const;
            bool operator<(const SideCrossIterator &other) const;

            SideCrossIterator &operator++();
            int operator*() const;
        };

        //-------------------------------------------------------------

        class PrimeIterator
        {
        private:
            const MagicalContainer *container;
            size_t current;

        public:
            PrimeIterator(const MagicalContainer &container);
            PrimeIterator(const PrimeIterator &other);

            PrimeIterator begin();
            PrimeIterator end();

            PrimeIterator &operator=(const PrimeIterator &other);
            bool operator==(const PrimeIterator &other) const;
            bool operator!=(const PrimeIterator &other) const;
            bool operator>(const PrimeIterator &other) const;
            bool operator<(const PrimeIterator &other) const;

            PrimeIterator &operator++();
            int operator*() const;
        };
    };
}
