// When it's not having problems this has the features:

// 1. Container moves into a new namespace (mount, PID)
// 2. lib, lib64, etc, bin have been remounted
// 3. have a user in the container that has sudo
// 4. full write access to the container without polluting the real filesystem?
// 5. make multiple containers
// 6. good user experience ~
// 7. keep track of all containers 
// 8. networking thing X
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

int container_ids[128];

int main(int argc, char** argv) {

	int num_containers = 1;
	if (argc > 1) {
		num_containers = atoi(argv[1]);
		if (num_containers < 1) {
			printf("you dummy, you need to make at least one.\n");
			exit(1);
		}
	}
	printf("Creating %d containers!\n", num_containers);
	

	memset(&container_ids, 0, 128*sizeof(int));

	char directory[16];

	// Repeat for the number of containers wanted
	for (int i=0; i<num_containers; i++) {

		// making all the new directories
		memset(&directory, 0, 16);
		strcpy((char*)&directory, "newroot");
		char number[3];
		sprintf(number, "%d", i);
		strcat((char*)&directory, number);

		int x;
		// making dir
		x = mkdir(directory, S_IRUSR | S_IWUSR | S_IXUSR);
		printf("mkdir return value is %d\n", x);
		if (x == -1) {
			perror("mkdir");
			continue;
		}

		printf("created directory is: %s\n", directory);	


		// unshare the namespace for the child
		//if (i == 0) {
		//}


		printf("parent pid is %d\n", (int)getpid());
			
		int child = fork();

		if (child == -1) {
			perror("fork");
			continue;
		}


		if (child == 0) {

			x = unshare(CLONE_NEWPID | CLONE_NEWNS);
			if (x == -1) {
				perror("unshare");
				continue;
			}		


			int child2 = fork();

			if (child2 != -1 && child2 != 0) {
				exit(1);
			}
// START
			// First one works 
			// overlay mount
			// lower is base
			x = chdir(directory);
			printf("chdir return val is %d\n", x);
		
			// mount and create things
		///*
			mkdir("bin_u", S_IRUSR | S_IWUSR | S_IXUSR);
			mkdir("bin", S_IRUSR | S_IWUSR | S_IXUSR);
			mkdir("bin_w", S_IRUSR | S_IWUSR | S_IXUSR);
			x = system("mount -t overlay -o lowerdir=/bin,upperdir=bin_u,workdir=bin_w overlay bin");
			printf("x is %d\n", x);

			mkdir("etc_u", S_IRUSR | S_IWUSR | S_IXUSR);
			mkdir("etc", S_IRUSR | S_IWUSR | S_IXUSR);
			mkdir("etc_w", S_IRUSR | S_IWUSR | S_IXUSR);
			x = system("mount -t overlay -o lowerdir=/etc,upperdir=etc_u,workdir=etc_w overlay etc");
			printf("x is %d\n", x);
			perror("system");
			
			mkdir("lib_u", S_IRUSR | S_IWUSR | S_IXUSR);
			mkdir("lib", S_IRUSR | S_IWUSR | S_IXUSR);
			mkdir("lib_w",S_IRUSR | S_IWUSR | S_IXUSR);
			x = system("mount -t overlay -o lowerdir=/lib,upperdir=lib_u,workdir=lib_w overlay lib");
			printf("x is %d\n", x);
				
			mkdir("lib64_u",S_IRUSR | S_IWUSR | S_IXUSR);
			mkdir("lib64",S_IRUSR | S_IWUSR | S_IXUSR);
			mkdir("lib64_w",S_IRUSR | S_IWUSR | S_IXUSR);
			x = system("mount -t overlay -o lowerdir=/lib64,upperdir=lib64_u,workdir=lib64_w overlay lib64");
			printf("x is %d\n", x);
		//*/



		mkdir("proc", S_IRUSR | S_IWUSR | S_IXUSR);
		system("mount -t proc none proc");
			

		// change the root
		x = chroot(".");
		if (x == -1) {
			perror("chroot");
			continue;
		}
// END
				
		mkdir("/sayan", S_IRUSR | S_IWUSR | S_IXUSR);
		
			system("mount ; ls /etc");

			// print info
			printf("pid is %d\n", (int)getpid());
			printf("uid is %d\n", (int)getuid());

			char buf[128];
			char* idk = getcwd(&buf, 128); 
			printf("idk is: %s\n", idk);


			system("/bin/bash");
	
			while(1) {}	

		} else {
			container_ids[i] = child;
			//waitpid(child, &status, NULL);
			puts("done waiting");
			//exit(1);
			//chdir("..");
			//char z[100];
			//printf("cwd: %s\n", getcwd(z, 100));	
		}
	}

	int status;
	pid_t wpid;
	while ((wpid = wait(&status)) > 0);

	printf("container id: %d\n", container_ids[0]);
	printf("container id: %d\n", container_ids[1]);
	printf("container id: %d\n", container_ids[2]);

	return 0;
}
