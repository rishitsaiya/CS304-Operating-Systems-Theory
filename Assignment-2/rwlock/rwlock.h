#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;

struct read_write_lock{
	int doRead; // reading
	int doWrite; //writing
	int waitNumberofReader; //wait_reader_num
	int waitNumberOfWriter; //wait_writer_num
	pthread_cond_t readerCV; //readers
	pthread_cond_t writerCV; //writers
	pthread_mutex_t mutex;
};

void InitalizeReadWriteLock(struct read_write_lock * rw);
void ReaderLock(struct read_write_lock * rw);
void ReaderUnlock(struct read_write_lock * rw);
void WriterLock(struct read_write_lock * rw);
void WriterUnlock(struct read_write_lock * rw);
