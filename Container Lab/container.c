// When it's not having problems this has the features:

// 1. Container moves into a new namespace (mount, PID)
// 2. lib, lib64, etc, bin have been remounted
// 3. have a user in the container that has sudo?
// 4. full write access to the container without polluting the real filesystem?
// 5.
// 6.
// 7.
// 8.
// 9.
// 10.


#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sched.h>
#include <sys/stat.h>

int main(int argc, char** argv) {

	
	system("ps");
	
	char* directory = "newroot";
	mkdir(directory, 700);

	// unshare the namespace for the child
	int x = unshare(CLONE_NEWPID | CLONE_NEWNS);
	if (x == -1) {
		perror("unshare");
		exit(1);
	}		
	
	// First one works then error: "Cannot allocate memory" from the system call
	// overlay mount
	// lower is base
/*
	mkdir("bin_u", 700);
	mkdir("bin", 700);
	mkdir("bin_w", 700);
	x = system("mount -t overlay -o lowerdir=/bin,upperdir=bin_u,workdir=bin_w overlay bin");
	printf("x is %d\n", x);

	mkdir("etc_u", 700);
	mkdir("etc", 700);
	mkdir("etc_w", 700);
	x = system("mount -t overlay -o lowerdir=/etc,upperdir=etc_u,workdir=etc_w overlay etc");
	printf("x is %d\n", x);
	perror("system");
	
	mkdir("lib_u", 700);
	mkdir("lib", 700);
	mkdir("lib_w", 700);
	x = system("mount -t overlay -o lowerdir=/lib,upperdir=lib_u,workdir=lib_w overlay lib");
	printf("x is %d\n", x);
	
	mkdir("lib64_u", 700);
	mkdir("lib64", 700);
	mkdir("lib64_w", 700);
	x = system("mount -t overlay -o lowerdir=/lib64,upperdir=lib64_u,workdir=lib64_w overlay lib64");
	printf("x is %d\n", x);
*/

	system("mountFolders.sh");
	x = chroot(directory);
	if (x == -1) {
		perror("chroot");
	}

	
	int child = fork();

	if (child == 0) {

		printf("pid is %d\n", (int)getpid());

				

		char buf[128];
		char* idk = getcwd(&buf, 128); 
		printf("idk is: %s\n", idk);
		printf("buf is %s\n", buf);

		//x = system("ls bin");
		//printf("x is %d\n", x);
		x = system("ps");
		printf("x is %d\n", x);
	
	
/*
		struct rlimit rl;
		rl.rlim_cur = 1;
		rl.rlim_max = 2;
		setrlimit(RLIMIT_CPU, &rl);
	

		int i = 0;
		while (1) {
			i++;
		}
*/
		//sleep(20);
		//execlp("/bin/ls", "/bin/ls", NULL);


		// prints everything
		//execlp("/bin/ps", "/bin/ps", "aux", NULL);
		

	
		// setup filesystem
		// unshare mount namespace	

		// mount


	} else {
		int status;
		wait(&status);
//		rmdir(directory);
		puts("done waiting");
		exit(1);
	}


	return 0;
}
