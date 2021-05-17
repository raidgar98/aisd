#pragma once

#include <random>
#include <fstream>

namespace algs
{
    using num_t = uint32_t;

    struct irandom_generator
    {
        virtual num_t operator()() = 0;
    };

    namespace helpers
    {
        struct std_random_generator : public irandom_generator
        {
            std_random_generator(const num_t i_begin, const num_t i_end) : range{i_begin, i_end} {}

            virtual num_t operator()() override
            {
                return range(engine);
            }

        private:
            std::uniform_int_distribution<num_t> range;
            std::random_device engine{};
        };

        template<typename stream_t>
        struct safe_file_opener
        {
            stream_t stream;

            explicit safe_file_opener(const std::string_view& filename) : stream{filename.data()} { if(!stream.good()) throw filename; }
            ~safe_file_opener() { stream.close(); }

        };
        /*
        size
        rand_1
        rand_2
        ...
        rand_count
        */
        inline void generate_file_with_random_stuff(const std::string_view& filename, const size_t count = 10'000)
        {
            safe_file_opener<std::ofstream> handle{ filename };
            std_random_generator generator{ 0, 1'000'000 };
            handle.stream << count << std::endl;
            for(size_t i = 0; i < count; ++i) handle.stream << generator() << std::endl;
        }
    };
}