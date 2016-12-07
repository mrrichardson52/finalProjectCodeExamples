#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mutexA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexB = PTHREAD_MUTEX_INITIALIZER;


void *lockAB(void *arg) {
    pthread_mutex_lock(&mutexA);
    //use resource 1
    pthread_mutex_lock(&mutexB);
    //use resource 2
    
    pthread_mutex_unlock(&mutexB);
    pthread_mutex_unlock(&mutexA);
    return NULL;
}

void *lockBA(void *arg) {
    pthread_mutex_lock(&mutexB);
    // use resource 2
    pthread_mutex_lock(&mutexA);
    // use resource 1
    
    pthread_mutex_unlock(&mutexA);
    pthread_mutex_unlock(&mutexB);
    return NULL;
}

int main(int argc, char *argv[]) {
    
    // Create two threads
    pthread_t p1, p2;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setinheritsched(&attr,SCHED_RR);
    pthread_attr_setschedpolicy(&attr,SCHED_RR);
    int result;
    pthread_create(&p1, &attr, lockAB, NULL);
    pthread_create(&p2, &attr, lockBA, NULL);
    
    // join waits for the threads to finish
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    
    return 0;
}


vagrant@Xubuntu-Vagrant:~/ClionProjects/OS_Examples/FinalProjectExamples$ gcc -pthread -o Deadlock deadlock_example.cpp
vagrant@Xubuntu-Vagrant:~/ClionProjects/OS_Examples/FinalProjectExamples$ valgrind --tool=helgrind ./Deadlock
==5673== Helgrind, a thread error detector
==5673== Copyright (C) 2007-2015, and GNU GPL'd, by OpenWorks LLP et al.
==5673== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==5673== Command: ./Deadlock
==5673== ---Thread-Announcement------------------------------------------
==5673==
==5673== Thread #3 was created
==5673==    at 0x5163B1E: clone (clone.S:74)
==5673==    by 0x4E46189: create_thread (createthread.c:102)
==5673==    by 0x4E47EC3: pthread_create@@GLIBC_2.2.5 (pthread_create.c:679)
==5673==    by 0x4C34BB7: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5673==    by 0x4009BF: main (in /home/vagrant/ClionProjects/OS_Examples/FinalProjectExamples/Deadlock)
==5673==
==5673== ----------------------------------------------------------------
==5673==
==5673== Thread #3: lock order "0x6010A0 before 0x6010E0" violated
==5673==
==5673== Observed (incorrect) order is: acquisition of lock at 0x6010E0
==5673==    at 0x4C321BC: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5673==    by 0x400910: lockBA(void*) (in /home/vagrant/ClionProjects/OS_Examples/FinalProjectExamples/Deadlock)
==5673==    by 0x4C34DB6: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5673==    by 0x4E476F9: start_thread (pthread_create.c:333)
==5673==
==5673==  followed by a later acquisition of lock at 0x6010A0
==5673==    at 0x4C321BC: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5673==    by 0x40091A: lockBA(void*) (in /home/vagrant/ClionProjects/OS_Examples/FinalProjectExamples/Deadlock)
==5673==    by 0x4C34DB6: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5673==    by 0x4E476F9: start_thread (pthread_create.c:333)
==5673==
==5673== Required order was established by acquisition of lock at 0x6010A0
==5673==    at 0x4C321BC: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5673==    by 0x4008CB: lockAB(void*) (in /home/vagrant/ClionProjects/OS_Examples/FinalProjectExamples/Deadlock)
==5673==    by 0x4C34DB6: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5673==    by 0x4E476F9: start_thread (pthread_create.c:333)
==5673==
==5673==  followed by a later acquisition of lock at 0x6010E0
==5673==    at 0x4C321BC: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5673==    by 0x4008D5: lockAB(void*) (in /home/vagrant/ClionProjects/OS_Examples/FinalProjectExamples/Deadlock)
==5673==    by 0x4C34DB6: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5673==    by 0x4E476F9: start_thread (pthread_create.c:333)
==5673==
==5673==  Lock at 0x6010A0 was first observed
==5673==    at 0x4C321BC: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5673==    by 0x4008CB: lockAB(void*) (in /home/vagrant/ClionProjects/OS_Examples/FinalProjectExamples/Deadlock)
==5673==    by 0x4C34DB6: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5673==    by 0x4E476F9: start_thread (pthread_create.c:333)
==5673==  Address 0x6010a0 is 0 bytes inside data symbol "mutexA"
==5673==
==5673==  Lock at 0x6010E0 was first observed
==5673==    at 0x4C321BC: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5673==    by 0x4008D5: lockAB(void*) (in /home/vagrant/ClionProjects/OS_Examples/FinalProjectExamples/Deadlock)
==5673==    by 0x4C34DB6: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5673==    by 0x4E476F9: start_thread (pthread_create.c:333)
==5673==  Address 0x6010e0 is 0 bytes inside data symbol "mutexB"
==5673==
==5673== For counts of detected and suppressed errors, rerun with: -v
==5673== Use --history-level=approx or =none to gain increased speed, at
==5673== the cost of reduced accuracy of conflicting-access information
==5673== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 5 from 5)



