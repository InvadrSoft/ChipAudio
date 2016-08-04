//
// Created by Myles Inglis on 09/06/2016.
//

#ifndef CHIPAUDIO_WAVETABLE_HPP
#define CHIPAUDIO_WAVETABLE_HPP

#include <stdexcept>
#include <vector>

namespace chip
{
    /**
     * Class representing a waveform table, as used by oscillators etc.
     */
    class WaveTable
    {
    public:
        /**
         * Enumeration of all valid WaveTable sizes.
         */
        enum TableSize
        {
            SIZE_2 = 2, SIZE_4 = 4, SIZE_8 = 8, SIZE_16 = 16,
            SIZE_32 = 32, SIZE_64 = 64, SIZE_128 = 128, SIZE_256 = 256,
            SIZE_512 = 512, SIZE_1024 = 1024
        };

        /**
         * Constructs a WaveTable with given size. Default size is 32 steps.
         * @param size Number of steps in the WaveTable (optional)
         */
        WaveTable(TableSize size = SIZE_32) : table_(size) {}

        /**
         * @return The size of the WaveTable in steps
         */
        std::size_t size() { return table_.size(); }

        /**
         * Access a step of the WaveTable by index.
         * @param n Index of step
         * @return Reference to the step
         */
        double& operator[](std::size_t n) { return table_[n]; }

        void set(unsigned int n, double value) { operator[](n) = value; }

        /**
         * Assign values from initializer list to WaveTable.
         * Throws a length_error if size of initializer list doesn't match size of the WaveTable.
         * @param initList Initializer list of double values
         * @return Reference to this WaveTable
         */
        WaveTable& operator=(std::initializer_list<double> initList)
        {
            if(initList.size() != table_.size() )
            {
                throw std::length_error("Size of initializer list doesn't match table size.");
            }
            table_ = initList;
            return *this;
        }

    private:
        std::vector<double> table_;
    };
}

#endif //CHIPAUDIO_WAVETABLE_HPP
