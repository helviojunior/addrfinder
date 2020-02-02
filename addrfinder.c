/***************************************
addrfinder - windows address resolution program
by M4v3r1ck - Helvio Junior
   helvio_junior [at] hotmail [dot] com
   helviojunior.com.br

Based on arwin wrote by steve hanna v.01
   vividmachines.com
   shanna@uiuc.edu

Metasploit block_api hash algoritm
  https://github.com/rapid7/metasploit-framework/blob/master/external/source/shellcode/windows/x86/src/hash.py
  
compilling
  32 bits
     gcc.exe addrfinder.c -o addrfinder32.exe -m32
  64 bits
     gcc.exe addrfinder.c -o addrfinder64.exe -m64
********************************************/

#include <windows.h>
#include <stdio.h>
#include <ctype.h>

typedef struct {
   char *data;
   int size;
} unicode_data;

int ror(unsigned int dword, unsigned int bits){
	return (dword >> bits | dword << (32 - bits)) & 0xFFFFFFFF;
}

unicode_data unicode(char* string){
	unicode_data ret_data;
	char *str;
	int size = (strlen(string)*2)+2;
	size_t s2 = (int)size;
    str=(char*)malloc(s2);
    memset(str, 0, s2);
	int i = 0;
	int u = 0;
	for(i=0; i<strlen(string); i++){
		char s1 = toupper(string[i]);
		str[u] = s1;
		u += 2;
	}
	ret_data.data = (char *)str;
	ret_data.size = size;
	
	return  ret_data;
}


unsigned int hash(char* module, char* function){
	unsigned int module_hash = 0;
    unsigned int function_hash = 0;
    unsigned int h;
    int i;
    int bits = 13;
	unicode_data u_module;
    int sfn = strlen(function)+1;
    char *fn = malloc(sfn);
    memset(fn, 0, sfn);
    memcpy(fn, function, sfn-1);
    
    u_module = unicode(module);    
    for(i=0; i<u_module.size; i++){
		module_hash = ror(module_hash, bits);
        module_hash += (int)u_module.data[i];
	}
	
	for(i=0; i<sfn; i++){
		function_hash = ror(function_hash, bits);
        function_hash += (int)fn[i];
	}
    
    h = module_hash + function_hash & 0xFFFFFFFF;
    return h;
}

int main(int argc, char** argv)
{
    HMODULE hmod_libname;
    FARPROC fprc_func;
    unsigned int mh = 0;
    
    printf("addrfinder - windows address resolution program - by M4v3r1ck - v.01\n");
    if(argc < 3)
    {
        printf("%s <Library Name> <Function Name>\n",argv[0]);
        exit(-1);
    }

    hmod_libname = LoadLibrary(argv[1]);
    if(hmod_libname == NULL)
    {
        printf("[!] Error: could not load library!\n");
        exit(-1);
    }
    fprc_func = GetProcAddress(hmod_libname,argv[2]);
    
    if(fprc_func == NULL)
    {
        printf("[!] Error: could find the function in the library!\n");
        exit(-1);
    }
    
    printf("\n[+] %s!%s address found at 0x%p\n",argv[1],argv[2],fprc_func);

    mh = hash(argv[1], argv[2]); 
    printf("[+] %s!%s msf block_api hash is 0x%08X\n",argv[1],argv[2],mh);
    

}
