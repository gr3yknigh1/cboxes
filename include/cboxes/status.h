#ifndef CBOXES_STATUS_H_
#define CBOXES_STATUS_H_

typedef enum cs_Status {
    cs_OK,
    cs_ERROR,
    cs_INDEX_ERROR,
    cs_OUT_OF_RANGE,
    cs_COLLECTION_IS_EMPTY,
    cs_NULL_REFERENCE_ERROR,
    cs_KEY_ERROR,
} cs_Status;

#endif // CBOXES_STATUS_H_
