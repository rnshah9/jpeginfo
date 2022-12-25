#include <stdint.h>
#include <stdio.h>
#include <climits>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" void delete_file(char *name, int verbose_mode, int quiet_mode);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    FuzzedDataProvider provider(data, size);
    char* name = strdup(provider.ConsumeRandomLengthString(1000).c_str());
    int verbose_mode = provider.ConsumeIntegralInRange<int>(0, 1);
    int quiet_mode = provider.ConsumeIntegralInRange<int>(0, 1);

    delete_file(name, verbose_mode, quiet_mode);

    free(name);

    return 0;
}
