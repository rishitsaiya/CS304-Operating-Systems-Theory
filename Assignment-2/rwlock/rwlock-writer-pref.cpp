#include "rwlock.h"

void InitalizeReadWriteLock(struct read_write_lock * rw){
  
  //	Write the code for initializing your read-write lock.
    rw->waitNumberOfWriter = 0; // Initial Wait count = 0
	rw->doWrite = 0; 
	rw->doRead = 0;
	// Mutex & CV Added
	pthread_mutex_init(&rw->mutex, NULL);
	pthread_cond_init(&rw->readerCV, NULL);
	pthread_cond_init(&rw->writerCV, NULL);
}

void ReaderLock(struct read_write_lock * rw){
  
  //	Write the code for aquiring read-write lock by the reader.
  	pthread_mutex_lock(&rw->mutex); //Lock
	while(rw->waitNumberOfWriter > 0 || rw->doWrite != 0){ //Spin Lock
		pthread_cond_wait(&rw->readerCV,&rw->mutex);
	}
	rw->doRead = rw->doRead + 1; // Increment Counter
	pthread_mutex_unlock(&rw->mutex); // Unlock
}

void ReaderUnlock(struct read_write_lock * rw){

  //	Write the code for releasing read-write lock by the reader.
	pthread_mutex_lock(&rw->mutex); // Lock
	rw->doRead = rw->doRead - 1; // Decrement Counter
	if(rw->doRead==0){ // Spin Lock
		pthread_cond_signal(&rw->writerCV);
	}
	pthread_mutex_unlock(&rw->mutex); // Unlock
}

void WriterLock(struct read_write_lock * rw){
  
  //	Write the code for aquiring read-write lock by the writer.
  	pthread_mutex_lock(&rw->mutex); // Lock
	rw->waitNumberOfWriter = rw->waitNumberOfWriter + 1; // Increment Counter
	while(rw->doRead > 0 || rw->doWrite > 0){ // Spin Lock
		pthread_cond_wait(&rw->writerCV,&rw->mutex);
	}
	rw->waitNumberOfWriter--; // Decrement Writer Counter
	rw->doWrite = rw->doWrite + 1; // Increment Count
	pthread_mutex_unlock(&rw->mutex); // Unlock
}

void WriterUnlock(struct read_write_lock * rw){

  //	Write the code for releasing read-write lock by the writer.
  	pthread_mutex_lock(&rw->mutex); // Lock
	rw->doWrite = rw->doWrite - 1; // Decrement Counter
	// Mutex & CV Added
	pthread_cond_signal(&rw->writerCV);
	pthread_cond_broadcast(&rw->readerCV);
	pthread_mutex_unlock(&rw->mutex);
}
