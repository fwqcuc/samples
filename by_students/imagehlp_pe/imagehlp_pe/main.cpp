#include "imagehlp_pe.h"

int main(int argc,char **argv){
	int ret;
    //ret = GetPeHeaders("d:\\study\\test.exe");
	//ret = GetPeImportTable("d:\\study\\test.exe");
	//ret = GetPeExportTable("d:\\study\\test.exe");
	//ret = GetPeTable("d:\\study\\test.exe");

	//ret = GetPeHeaders("d:\\study\\system32.dll");
	//ret = GetPeImportTable("d:\\study\\system32.dll");
	//ret = GetPeExportTable("d:\\study\\system32.dll");
	//ret = GetPeTable("d:\\study\\system32.dll");

	//ret = GetPeHeaders("d:\\study\\steam_api.dll");
	//ret = GetPeImportTable("d:\\study\\steam_api.dll");
	//ret = GetPeExportTable("d:\\study\\steam_api.dll");
	//ret = GetPeTable("d:\\study\\steam_api.dll");

    ret = GetPeHeaders(argv[1]);
	ret = GetPeTable(argv[1]);
	getchar();
	return ret;
}