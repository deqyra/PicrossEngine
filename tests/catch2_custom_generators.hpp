#ifndef TESTS__CATCH2_CUSTOM_GENERATORS_HPP
#define TESTS__CATCH2_CUSTOM_GENERATORS_HPP

#include "../lib/catch2/catch2.hpp"

#include <cstddef>
#include <iterator>
#include <algorithm>
#include <memory>
#include <vector>
#include <tuple>

#include "../core/cell_t.hpp"

namespace Catch
{
    namespace Generators
    {
        template<typename T>
        class ArrayGenerator : public IGenerator<T>
        {
            private:
                T* _copiedArray;
                std::size_t _pos;
                std::size_t _count;

            public:
                ArrayGenerator(const T* const array, std::size_t size);
                virtual ~ArrayGenerator();
                virtual bool next();
                virtual T const& get() const;
        };

        template<typename T>
        class VectorGenerator : public IGenerator<T>
        {
            private:
                std::vector<T> _copiedVector;
                std::size_t _pos;

            public:
                VectorGenerator(const std::vector<T> vector, std::size_t size = 0);
                virtual ~VectorGenerator();
                virtual bool next();
                virtual T const& get() const;
        };

        template<typename T>
        ArrayGenerator<T>::ArrayGenerator(const T* const array, std::size_t size) :
            _copiedArray(new T[size]),
            _pos(0),
            _count(size)
        {
            std::copy(array, array + size, _copiedArray);
        }

        template<typename T>
        ArrayGenerator<T>::~ArrayGenerator()
        {
            delete[] _copiedArray;
        }

        template<typename T>
        bool ArrayGenerator<T>::next()
        {
            return ++_pos < _count;
        }

        template<typename T>
        T const& ArrayGenerator<T>::get() const
        {
            return _copiedArray[_pos];
        }

        template<typename T>
        VectorGenerator<T>::VectorGenerator(const std::vector<T> vector, std::size_t size) :
            _copiedVector(vector.begin(), size == 0 ? vector.end() : vector.begin() + size),
            _pos(0)
        {
        }

        template<typename T>
        VectorGenerator<T>::~VectorGenerator()
        {
        }

        template<typename T>
        bool VectorGenerator<T>::next()
        {
            return ++_pos < _copiedVector.size();
        }

        template<typename T>
        T const& VectorGenerator<T>::get() const
        {
            return _copiedVector[_pos];
        }
    }
}

template<typename T>
Catch::Generators::GeneratorWrapper<T> vector(std::vector<T> vector, std::size_t size = 0)
{
    return Catch::Generators::GeneratorWrapper<T>(std::unique_ptr<Catch::Generators::IGenerator<T>>(new Catch::Generators::VectorGenerator<T>(vector, size)));
}

template<typename T>
Catch::Generators::GeneratorWrapper<T> array(const T* const array, std::size_t size)
{
    return Catch::Generators::GeneratorWrapper<T>(std::unique_ptr<Catch::Generators::IGenerator<T>>(new Catch::Generators::ArrayGenerator<T>(array, size)));
}

#endif//TESTS__CATCH2_CUSTOM_GENERATORS_HPP