#ifndef SPIN_H
#define SPIN_H

#include <type_traits>
#include <future>
#include <utility>
#include <thread>

namespace cppext
{
    template<typename LambdaWithNoArgs>
        auto spin(LambdaWithNoArgs func)
        {
            auto task = std::packaged_task<std::result_of_t<LambdaWithNoArgs()>()>{ std::move(func) };
            auto res = task.get_future();
            std::thread{ std::move(task) }.detach();
            return res;
        }
}

#endif
