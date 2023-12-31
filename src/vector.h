#ifndef BSON_VECTOR_H
#define BSON_VECTOR_H

#include <stddef.h>

typedef struct BsonVecMD {
    size_t length;
    size_t capacity;
    size_t stride;
} BsonVecMD;

void            *bson_vector_allocate(size_t capacity, size_t stride);
void             bson_vector_deallocate(void **vec);

const BsonVecMD *bson_vector_metadata(const void *vec);
size_t           bson_vector_length(void *vec);
size_t           bson_vector_capacity(void *vec);
size_t           bson_vector_stride(void *vec);
void            *bson_vector_grow(void *vec);
void             bson_vector_inc(void *vec);

void            *bson_vector_carr(void *vec);
void             bson_carr_deallocate(void **arr);
#define bson_carr_free(a)                           \
    bson_carr_deallocate((void *)(&a))

#define bson_vector_new(t)                          \
    ((t *)(bson_vector_allocate(0, sizeof(t))))
#define bson_vector_new_cap(t, c)                   \
    ((t *)(bson_vector_allocate(c, sizeof(t))))
#define bson_vector_free(p)                         \
    bson_vector_deallocate((void *)(&p))
#define bson_vector_push(p, v)                      \
do {                                                \
    size_t _private_len_ = bson_vector_length((void *)(p)); \
    p[_private_len_++] = v;                                 \
    if(_private_len_ >= bson_vector_capacity((void *)(p)))  \
        p = bson_vector_grow((void *)(p));                  \
    bson_vector_inc((void *)(p));                           \
} while(0)

#endif

