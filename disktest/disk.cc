#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <sys/time.h>
using namespace std;
#define BUFSIZE 4000

int gbuf[BUFSIZE];



int main(void){
	
        struct timeval tv;

	int fd = open("./testfile",O_CREAT | O_RDWR );	
	int times = 10000;
	unsigned long long total = 0;
	for (int i = 0; i != times; i++ ){
	       	gettimeofday(&tv,NULL);
       		unsigned long long  start = static_cast<unsigned long long>(tv.tv_sec)*1000000 + tv.tv_usec;

	
		if ( write(fd, gbuf, BUFSIZE) != BUFSIZE ) {
			cout << "write error\n";
		}
		if  ( !fdatasync(fd) ){
			;	
		}else{
			cout << "fsync error\n";
		}
	       	gettimeofday(&tv,NULL);
       	 	unsigned long long end  = static_cast<unsigned long long>(tv.tv_sec)*1000000 + tv.tv_usec;
		total += (end - start);
		cout << "consumer time:" <<end - start << "us"  << endl;	
	}	
	cout << "average is :" << total / times << "us" << endl;

	return 0;
}
