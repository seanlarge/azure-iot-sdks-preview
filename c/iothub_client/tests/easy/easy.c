// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>
#ifdef _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <stddef.h>
#include <string.h>


#include "testrunnerswitcher.h"
#include "umock_c.h"

#include "contains_awesomness.h"

DEFINE_ENUM_STRINGS(UMOCK_C_ERROR_CODE, UMOCK_C_ERROR_CODE_VALUES)

static void on_umock_c_error(UMOCK_C_ERROR_CODE error_code)
{
    char temp_str[256];
    (void)snprintf(temp_str, sizeof(temp_str), "umock_c reported error :%s", ENUM_TO_STRING(UMOCK_C_ERROR_CODE, error_code));
    ASSERT_FAIL(temp_str);
}

int EDM_SOMETHING_Compare(const EDM_SOMETHING a, const EDM_SOMETHING b)
{
    return a.q==b.q;

}

int EDM_SOMETHING_ToString(char* destination, size_t destinationSize, const EDM_SOMETHING a)
{
    (void)(destination, destinationSize, a);
    return 0;

}
BEGIN_TEST_SUITE(easy)

TEST_SUITE_INITIALIZE(TestSuiteInitialize)
{
    (void)umock_c_init(on_umock_c_error);
}

TEST_SUITE_CLEANUP(TestClassCleanup)
{
    umock_c_deinit();

}

TEST_FUNCTION_INITIALIZE(Setup)
{
    umock_c_reset_all_calls();
}

TEST_FUNCTION(zee_test)
{
    
    ///arrange
    EDM_SOMETHING a= {3};
    EDM_SOMETHING b= {4};

    ///act
    

    ///assert
    ASSERT_ARE_EQUAL(EDM_SOMETHING, a, b);

    ///cleanup

}

END_TEST_SUITE(easy);
