// Buffer cache.
//
// The buffer cache is a linked list of buf structures holding
// cached copies of disk block contents.  Caching disk blocks
// in memory reduces the number of disk reads and also provides
// a synchronization point for disk blocks used by multiple processes.
//
// Interface:
// * To get a buffer for a particular disk block, call bread.
// * After changing buffer data, call bwrite to write it to disk.
// * When done with the buffer, call brelse.
// * Do not use the buffer after calling brelse.
// * Only one process at a time can use a buffer,
//     so do not keep them longer than necessary.


#include "types.h"
#include "param.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "riscv.h"
#include "defs.h"
#include "fs.h"
#include "buf.h"

struct {
  struct spinlock lock;
  struct buf buf[NBUF];
} bcache;

struct bucket {
  struct spinlock lock;
  struct buf head;
}hashtable[MAXOPBLOCKS];

void
binit(void)
{
  struct buf *b;

  initlock(&bcache.lock, "bcache");
  for(b = bcache.buf; b < bcache.buf+NBUF; b++){
    initsleeplock(&b->lock, "buffer");
  }

  b = bcache.buf;
  for (int i = 0; i < MAXOPBLOCKS; i++) {
    initlock(&hashtable[i].lock, "bucket");
    for (int j = 0; j < NBUF / MAXOPBLOCKS; j++) {
      b->next = hashtable[i].head.next;
      hashtable[i].head.next = b;
      b->blockno = i;
      b++;
    }
  }
}

// Look through buffer cache for block on device dev.
// If not found, allocate a buffer.
// In either case, return locked buffer.
static struct buf*
bget(uint dev, uint blockno)
{
  struct buf *b;

  int id = blockno % MAXOPBLOCKS;
  struct bucket* bucket = hashtable + id;
  acquire(&bucket->lock);

  // Is the block already cached?
  for(b = bucket->head.next; b != 0; b = b->next){
    if(b->dev == dev && b->blockno == blockno){
      b->refcnt++;
      release(&bucket->lock);
      acquiresleep(&b->lock);
      return b;
    }
  }

  // Not cached.
  // searching in current bucket.
  struct buf* buckbuff = 0;

  for(b = bucket->head.next; b != 0; b = b->next)
    if(b->refcnt == 0) 
      buckbuff = b;

  if(buckbuff) {
    buckbuff->dev = dev;
    buckbuff->valid = 0;
    buckbuff->refcnt = 1;
    buckbuff->blockno = blockno;

    release(&bucket->lock);
    acquiresleep(&buckbuff->lock);
    return buckbuff;
  }

  // searching in other bucket.
  acquire(&bcache.lock);
  while (1) {
    for (b = bcache.buf; b < bcache.buf + NBUF; b++) 
        if (b->refcnt == 0) 
            buckbuff = b;

    if (buckbuff) {
        int buckid = buckbuff->blockno % MAXOPBLOCKS;
        acquire(&hashtable[buckid].lock);

        if (buckbuff->refcnt != 0) {
            release(&hashtable[buckid].lock);
            continue;
        }

        struct buf *curr = &hashtable[buckid].head;
        while (curr->next != buckbuff) 
            curr = curr->next;
        curr->next = curr->next->next;

        release(&hashtable[buckid].lock);
        buckbuff->next = hashtable[id].head.next;
        hashtable[id].head.next = buckbuff;

        release(&bcache.lock);
        buckbuff->dev = dev;
        buckbuff->valid = 0;
        buckbuff->refcnt = 1;
        buckbuff->blockno = blockno;

        release(&bucket->lock);
        acquiresleep(&buckbuff->lock);
        return buckbuff;
    } else {
        panic("bget: no buffers");
    }
  }
}

// Return a locked buf with the contents of the indicated block.
struct buf*
bread(uint dev, uint blockno)
{
  struct buf *b;

  b = bget(dev, blockno);
  if(!b->valid) {
    virtio_disk_rw(b, 0);
    b->valid = 1;
  }
  return b;
}

// Write b's contents to disk.  Must be locked.
void
bwrite(struct buf *b)
{
  if(!holdingsleep(&b->lock))
    panic("bwrite");
  virtio_disk_rw(b, 1);
}

// Release a locked buffer.
// Move to the head of the most-recently-used list.
void
brelse(struct buf *b)
{
  if(!holdingsleep(&b->lock))
    panic("brelse");

  releasesleep(&b->lock);

  int id = b->blockno % MAXOPBLOCKS;
  acquire(&hashtable[id].lock);
  b->refcnt--;
  
  release(&hashtable[id].lock);
}

void
bpin(struct buf *b) {
  int id = b->blockno % MAXOPBLOCKS;
  acquire(&hashtable[id].lock);
  b->refcnt++;
  release(&hashtable[id].lock);
}

void
bunpin(struct buf *b) {
  int id = b->blockno % MAXOPBLOCKS;
  acquire(&hashtable[id].lock);
  b->refcnt--;
  release(&hashtable[id].lock);
}