#include "MagicalContainer.hpp"

namespace ariel
{

    MagicalContainer::MagicalContainer()
    {
    }
    MagicalContainer::MagicalContainer(MagicalContainer &other)
    {
        container = other.container;
    }
    MagicalContainer::~MagicalContainer() {}

    void MagicalContainer::addElement(int element)
    {
        container.push_back(element);
        sort(this->container.begin(), this->container.end());
        if (isPrime(element))
        {
            this->pri_container.push_back(element);
            sort(this->pri_container.begin(), this->pri_container.end());
        }
    }

    size_t MagicalContainer::size() const
    {
        return this->container.size();
    }

    void MagicalContainer::removeElement(int element)
    {
        auto it = std::find(container.begin(), container.end(), element);
        if (*it == element)
        {
            container.erase(it);
        }
        else
        {
            throw runtime_error("element not found in container!");
        }

        auto prime_it = std::find(this->pri_container.begin(), this->pri_container.end(), element);
        if (isPrime(element))
        {
            this->pri_container.erase(prime_it);
        }
    }

    //---------------------------------------------------------------------------------------------------------------

    MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer &container) : container(&container), current(0)
    {
    }

    MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer &container, size_t current) : container(&container), current(current)
    {
    }
    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) : container(other.container), current(other.current)
    {
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
    {
        return AscendingIterator(*container, 0);
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
    {
        return AscendingIterator(*container, container->container.size());
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
    {
        if (&this->container != &other.container)
        {
            throw runtime_error("the containers are not the same!");
        }
        if (this != &other)
        {
            container = other.container;
            this->current = other.current;
        }
        return *this;
    }

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
    {
        return this->current == other.current;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
    {
        return this->current > other.current;
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
    {
        return this->current < other.current;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
    {
        if (*this == end())
        {
            throw runtime_error("end of the container!");
        }
        this->current++;
        return *this;
    }

    int MagicalContainer::AscendingIterator::operator*() const
    {
        return container->container[this->current];
    }

    //---------------------------------------------------------------------------------------

    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &container, size_t current, size_t cross_it) : container(&container), current(0), cross_it(cross_it)
    {
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : container(other.container), current(other.current),cross_it(other.cross_it)
    {
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
    {
        return SideCrossIterator(*container);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
    {
        SideCrossIterator it(*container);
        it.current = container->container.size(); 
        return it;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
    {
        if (&this->container != &other.container)
        {
            throw runtime_error("the containers are not the same!");
        }
        if (this != &other)
        {
            this->container = other.container;
            this->current = other.current;
            this->cross_it = other.cross_it;
        }
        return *this;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
    {
        return (this->current == other.current) && (this->container == other.container);
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
    {
        return this->current > other.current;
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
    {
        return this->current < other.current;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
    {

        if (this->current >= this->container->size())
        {
            throw std::runtime_error("can not increament!");
        }
        if (this->cross_it > (this->container->size() / 2))
        {
            ++this->current;
            this->cross_it = static_cast<vector<int>::size_type>(this->container->size() - (this->cross_it));
        }
        else
        {
            ++this->current;
            this->cross_it = static_cast<vector<int>::size_type>((this->container->size() - 1) - (this->cross_it));
        }
        return *this;
    }

    int MagicalContainer::SideCrossIterator::operator*() const
    {
        return this->container->container[this->cross_it];
    }

    //---------------------------------------------------------------------------------------

    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &container) : container(&container), current(0)
    {
    }

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) : container(other.container), current(other.current)
    {
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
    {
        PrimeIterator prim(*container);
        prim.current = 0;

        return prim;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
    {
        PrimeIterator prim(*this->container);
        prim.current = container->pri_container.size();
        return prim;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
    {
        if (this->container != other.container)
        {
            throw runtime_error("the containers are not the same!");
        }
        if (this != &other)
        {
            container = other.container;
            current = other.current;
        }
        return *this;
    }

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
    {
        return this->current == other.current;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
    {
        return this->current > other.current;
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
    {
        return this->current < other.current;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
    {
        if (this->current >= container->pri_container.size())
        {
            throw runtime_error("there is no elements");
        }
        ++this->current;
        return *this;
    }

    int MagicalContainer::PrimeIterator::operator*() const
    {
        if (container->pri_container.empty())
        {
            throw runtime_error("there is no elements!");
        }
        return container->pri_container[current];
    }
}
