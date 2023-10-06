#ifndef _BEBONE_CORE_ARENA_CONTAINER_H_
#define _BEBONE_CORE_ARENA_CONTAINER_H_

#include "noncopyable.h"
#include "arena_allocator.h"

namespace bebone::core {
    class ArenaContainer : private core::NonCopyable {
        private:
            ArenaAllocator data;
            ArenaAllocator indices;

        public:
            explicit ArenaContainer(const size_t& size) : data(size), indices(size) {

            }

            void* alloc(const size_t& size) noexcept {
                void* ptr = data.alloc(size);
                void** indexPtr = static_cast<void**>(indices.alloc(sizeof(void*)));

                *indexPtr = ptr;

                return ptr;
            }

            void clear() noexcept {
                data.clear();
                indices.clear();
            }

            [[nodiscard]] size_t size() const noexcept {
                return indices.allocated() / sizeof(void*);
            }

            [[nodiscard]] size_t allocated() const noexcept {
                return data.allocated() + indices.allocated();
            }

            [[nodiscard]] size_t capacity() const noexcept {
                return data.allocated() + indices.allocated();
            }

            void* at(const size_t& index) {
                void **ptr = static_cast<void**>(indices.data());
                return ptr[index];
            }
    };
}

#endif