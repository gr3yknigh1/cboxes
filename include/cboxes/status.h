#ifndef CBOXES_STATUS_H_
#define CBOXES_STATUS_H_

typedef enum cs_status {
    cs_OK,
    cs_ERROR,
    cs_INDEX_ERROR,
    cs_OUT_OF_RANGE,
    cs_COLLECTION_IS_EMPTY,
    cs_NULL_REFERENCE_ERROR,
    cs_KEY_ERROR,
} cs_status_t;

#endif // CBOXES_STATUS_H_
