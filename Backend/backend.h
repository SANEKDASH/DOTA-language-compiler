#ifndef BACKEND_HEADER
#define BACKEND_HEADER

#include "../Common/trees.h"
#include "../Common/NameTable.h"
#include "backend_common.h"

#include "FastList/list.h"
#include "ListDump/list_dump.h"

static const char *kAsmMainName = "main";

typedef enum
{
    kBackendSuccess,
    kMissingKeywordCode,
    kCantFindSuchVariable,
    kBackendUnknownNodeType,
    kBackendNullTree,
    kListConstructorError,
    kListDestructorError,
    kBackendUnknownOpcode,
    kBackendNotAssign,
    kBackendNotVarDecl,
    kCantFindNameTable,
    kBackendDumpAlreadyStarted,
    kBackendDumpAlreadyClosed,
    kBackendFailedAllocation,
    kCantFindVariable,
    kBackendLabelTableInitError,
    kBackendLabelTableDestroyError,
    kBackendAddressRequestsInitError,
    kBackendDestroyAddressRequestsError,
} BackendErrs_t;

static const int32_t kFuncLabelPosPoison          = -1;
static const int32_t kCommonLabelIdentifierPoison = -1;

struct Label
{
    uint32_t address;

    int32_t identification_number;

    int32_t func_pos;
};

struct LabelTable
{
    Label  *label_array;

    size_t  capacity;

    size_t  label_count;

    uint32_t identify_counter;
};

struct Request
{
    Instruction *jmp_instruction;

    int32_t func_pos;

    int32_t label_identifier;
};

static const size_t kBaseCallRequestArraySize = 8;

struct AddressRequests
{
    Request *requests;

    size_t capacity;

    size_t request_count;
};

struct BackendContext
{
    List            *instruction_list;

    size_t           cur_address;

    LabelTable      *label_table;

    AddressRequests *address_requests;
};

TreeErrs_t WriteAsmCodeInFile(LanguageContext *language_context,
                              const char      *output_file_name);


BackendErrs_t GetAsmInstructionsOutLanguageContext(BackendContext  *backend_context,
                                                   LanguageContext *language_context);

BackendErrs_t BackendContextInit   (BackendContext *backend_context);
BackendErrs_t BackendContextDestroy(BackendContext *backend_context);

#endif
