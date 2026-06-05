#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct luna_external_module luna_external_module_t;

typedef luna_external_module_t* (*luna_external_module_entry_t)();

#ifdef __cplusplus
}
#endif