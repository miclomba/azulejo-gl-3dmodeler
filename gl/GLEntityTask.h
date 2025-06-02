/**
 * @file GLEntityTask.h
 * @brief Declaration of the GLEntityTask struct for handling asynchronous tasks related to GLEntity.
 */

#ifndef _3dmodeler_glentitytask_h
#define _3dmodeler_glentitytask_h

#include <functional>
#include <future>
#include <memory>

#include "configuration/config.h"

namespace _3dmodeler
{

    class GLEntity;

    /**
     * @struct GLEntityTask
     * @brief A struct for managing asynchronous tasks that produce GLEntity instances.
     *
     * This struct wraps an asynchronous task and provides mechanisms to execute and retrieve the result.
     */
    struct _3DMODELER_DLL_EXPORT GLEntityTask
    {
        /**
         * @brief Constructs a GLEntityTask with a given function.
         * @param lambda A function returning a pointer to a GLEntity instance.
         */
        GLEntityTask(std::function<GLEntity *()> lambda);

        /**
         * @brief Executes the stored task.
         */
        void operator()();

        /**
         * @brief Retrieves the future result of the task.
         * @return A future object holding the GLEntity pointer result.
         */
        std::future<GLEntity *> GetFuture();

    private:
        /**
         * @brief Packaged task encapsulating the asynchronous operation.
         */
        std::shared_ptr<std::packaged_task<GLEntity *()>> task_;
    };

} // namespace _3dmodeler

#endif // _3dmodeler_glentitytask_h
